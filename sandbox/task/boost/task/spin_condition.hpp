
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TASK_SPIN_CONDITION_H
#define BOOST_TASK_SPIN_CONDITION_H

#include <boost/cstdint.hpp>
#include <boost/thread/thread_time.hpp>
#include <boost/utility.hpp>

#include <boost/task/exceptions.hpp>
#include <boost/task/spin_mutex.hpp>

namespace boost {
namespace task {

class spin_condition : private noncopyable
{
private:
	enum command
	{
		SLEEPING = 0,
		NOTIFY_ONE,
		NOTIFY_ALL
	};

	volatile uint32_t	cmd_;
	volatile uint32_t	waiters_;
	spin_mutex			enter_mtx_;
	spin_mutex			check_mtx_;

	spin_condition( spin_condition const&);
	spin_condition & operator=( spin_condition const&);

	void wait_( spin_mutex &);
	bool wait_( spin_mutex &, system_time const&);
	void notify_( command);

public:
	spin_condition();

	void notify_one();

	void notify_all();

	template< typename Lock >
	void wait( Lock & lk)
	{
		if ( ! lk)
			throw lock_error();
		wait_( * lk.mutex() );
	}

	template<
		typename Lock,
		typename Pred
	>
	void wait( Lock & lk, Pred pred)
	{
		if ( ! lk)
			throw lock_error();

		while ( ! pred() )
			wait_( * lk.mutex() );
	}

	template< typename Lock >
	bool timed_wait( Lock & lk, system_time const& abs_time)
	{
		if ( abs_time.is_infinity() )
		{
			wait_( lk);
			return true;
		}

		if ( ! lk)
			throw lock_error();
		return wait_( * lk.mutex(), abs_time);
	}

	template<
		typename Lock,
		typename Pred
	>
	bool timed_wait( Lock & lk, system_time const& abs_time, Pred pred)
	{
		if ( abs_time.is_infinity() )
		{
			wait_( lk, pred);
			return true;
		}

		if ( ! lk)
			throw lock_error();

		while ( ! pred() )
			if ( ! wait_( * lk.mutex(), abs_time) )
				return pred();
		return true;
	}

	template<
		typename Lock,
		typename TimeDuration
	>
	bool timed_wait( Lock & lk, TimeDuration const& rel_time)
	{ return timed_wait( lk, get_system_time() + rel_time); }

	template<
		typename Lock,
		typename TimeDuration,
		typename Pred
	>
	bool timed_wait( Lock & lk, TimeDuration const& rel_time, Pred pred)
	{ return timed_wait( lk, get_system_time() + rel_time, pred); }
};

}}

#endif // BOOST_TASK_SPIN_CONDITION_H
