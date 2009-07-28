
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TASK_DETAIL_WORKER_H
#define BOOST_TASK_DETAIL_WORKER_H

#include <cstddef>
#include <utility>

#include <boost/assert.hpp>
#include <boost/function.hpp>
#include <boost/random.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/utility.hpp>

#include <boost/task/callable.hpp>
#include <boost/task/detail/config.hpp>
#include <boost/task/detail/fiber.hpp>
#include <boost/task/detail/guard.hpp>
#include <boost/task/detail/interrupter.hpp>
#include <boost/task/detail/wsq.hpp>
#include <boost/task/poolsize.hpp>
#include <boost/task/scanns.hpp>
#include <boost/task/semaphore.hpp>

#include <boost/config/abi_prefix.hpp>

# if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable:4251 4275)
# endif

namespace boost { namespace task {
namespace detail
{

struct worker_base
{
	virtual ~worker_base() {}

	virtual const thread::id get_id() const = 0;

	virtual void join() const = 0;

	virtual void interrupt() const = 0;

	virtual void put( callable const&) = 0;

	virtual bool try_steal( callable &) = 0;

	virtual void signal_shutdown() = 0;

	virtual void signal_shutdown_now() = 0;

	virtual void run() = 0;

	virtual void reschedule_until( function< bool() > const&) = 0;

	virtual bool block() = 0;
};

template<
	typename Pool,
	typename Worker
>
class worker_object : public worker_base,
					  private noncopyable
{
private:
	class random_idx
	{
	private:
		rand48 rng_;
		uniform_int<> six_;
		variate_generator< rand48 &, uniform_int<> > die_;

	public:
		random_idx( std::size_t size)
		:
		rng_(),
		six_( 0, size - 1),
		die_( rng_, six_)
		{}

		std::size_t operator()()
		{ return die_(); }
	};

	Pool					&	pool_;
	shared_ptr< thread >		thrd_;
	shared_ptr< fiber >			fib_;
	wsq				 			wsq_;
	semaphore					shtdwn_sem_;
	semaphore					shtdwn_now_sem_;
	bool						shtdwn_;
	posix_time::time_duration	asleep_;
	scanns						max_scns_;
	std::size_t					scns_;
	random_idx					rnd_idx_;

	void execute_( callable & ca)
	{
		BOOST_ASSERT( ! ca.empty() );
		guard grd( pool_.active_worker_);
		{
			context_guard lk( ca, thrd_);
			ca();
		}
		ca.clear();
		BOOST_ASSERT( ca.empty() );
	}

	bool take_global_callable_(
			callable & ca,
			posix_time::time_duration const& asleep)
	{ return pool_.channel_.take( ca, asleep); }

	bool try_take_global_callable_( callable & ca)
	{ return pool_.channel_.try_take( ca); }

	bool try_take_local_callable_( callable & ca)
	{ return wsq_.try_take( ca); }
	
	bool try_steal_other_callable_( callable & ca)
	{
		std::size_t idx( rnd_idx_() );
		for ( std::size_t j( 0); j < pool_.wg_.size(); ++j)
		{
			Worker other( pool_.wg_[idx]);
			if ( this_thread::get_id() == other.get_id() ) continue;
			if ( ++idx >= pool_.wg_.size() ) idx = 0;
			if ( other.try_steal( ca) )
				return true;
		}
		return false;
	}

	void run_()
	{
		callable ca;
		while ( ! shutdown_() )
		{
			if ( try_take_local_callable_( ca) || 
				 try_take_global_callable_( ca) ||
				 try_steal_other_callable_( ca) )
			{
				execute_( ca);
				scns_ = 0;
			}
			else
			{
				guard grd( pool_.idle_worker_);
				if ( shutdown_() ) return;
				++scns_;
				if ( scns_ >= max_scns_)
				{
					// should the comparation be atomic or
					// at least the read of idle_worker_ be atomic ?
					if ( pool_.size_() == pool_.idle_worker_)
					{
						if ( take_global_callable_( ca, asleep_) )
							execute_( ca);
					}
					else
						try
						{ this_thread::sleep( asleep_); }
						catch ( thread_interrupted const&)
						{ return; }
					scns_ = 0;
				}
				else
					this_thread::yield();
			}
		}
	}

	bool shutdown_()
	{
		if ( shutdown__() && get_pool().channel_.empty() )
			return true;
		else if ( shutdown_now__() )
			return true;
		return false;
	}

	bool shutdown__()
	{
		if ( ! shtdwn_)
			shtdwn_ = shtdwn_sem_.try_wait();
		return shtdwn_;
	}
	
	bool shutdown_now__()
	{ return shtdwn_now_sem_.try_wait(); }

public:
	worker_object(
		Pool & pool,
		poolsize const& psize,
		posix_time::time_duration const& asleep,
		scanns const& max_scns,
		function< void() > const& fn)
	:
	pool_( pool),
	thrd_( new thread( fn) ),
	fib_(),
	wsq_(),
	shtdwn_sem_( 0),
	shtdwn_now_sem_( 0),
	shtdwn_( false),
	asleep_( asleep),
	max_scns_( max_scns),
	scns_( 0),
	rnd_idx_( psize)
	{ BOOST_ASSERT( ! fn.empty() ); }

	const thread::id get_id() const
	{ return thrd_->get_id(); }

	void join() const
	{ thrd_->join(); }

	void
	interrupt() const
	{ thrd_->interrupt(); }

	void signal_shutdown()
	{ shtdwn_sem_.post(); }
	
	void signal_shutdown_now()
	{ shtdwn_now_sem_.post(); }

	void put( callable const& ca)
	{
		BOOST_ASSERT( ! ca.empty() );
		wsq_.put( ca);
	}

	bool try_steal( callable & ca)
	{ return wsq_.try_steal( ca); }

	Pool & get_pool() const
	{ return pool_; }

	void run()
	{
		BOOST_ASSERT( get_id() == this_thread::get_id() );

		fiber::convert_thread_to_fiber();
		shared_ptr< fiber > fib(
			new fiber(
				bind(
					& worker_object::run_,
					this),
				64000) );
		fib_.swap( fib);
		fib_->run();
		BOOST_ASSERT( fib_->exited() );
		fib_.reset();
	}

	void reschedule_until( function< bool() > const& pred)
	{
		callable ca;
		while ( ! pred() /* && ! shutdown_() */)
		{
			if ( try_take_local_callable_( ca) )
			{
				execute_( ca);
				scns_ = 0;
			}
			else
			{
				guard grd( get_pool().idle_worker_);
				if ( shutdown_() ) return;
				++scns_;
				if ( scns_ >= max_scns_)
				{
					this_thread::sleep( asleep_);
					scns_ = 0;
				}
				else
					this_thread::yield();
			}
		}
	}

	bool block()
	{ return ! shutdown_(); }
};

class BOOST_TASK_DECL worker
{
private:
	static thread_specific_ptr< worker >	tss_;

	shared_ptr< worker_base >	impl_;

public:
	template< typename Pool >
	worker(
		Pool & pool,
		poolsize const& psize,
		posix_time::time_duration const& asleep,
		scanns const& max_scns,
		function< void() > const& fn)
	:
	impl_(
		new worker_object< Pool, worker >(
			pool,
			psize,
			asleep,
			max_scns,
			fn) )
	{}

	const thread::id get_id() const;

	void join() const;
	void interrupt() const;
	void signal_shutdown();
	void signal_shutdown_now();

	void put( callable const&);
	bool try_steal( callable &);

	template< typename Pool >
	Pool & get_pool() const
	{
		worker_object< Pool, worker > * p( dynamic_cast< worker_object< Pool, worker > * >( impl_.get() ) );
		BOOST_ASSERT( p);
		return p->get_pool();
	}

	void run();
	void reschedule_until( function< bool() > const&);
	bool block();

	static worker * tss_get();
};

}}}

# if defined(BOOST_MSVC)
# pragma warning(pop)
# endif

#include <boost/config/abi_suffix.hpp>

#endif // BOOST_TASK_DETAIL_WORKER_H

