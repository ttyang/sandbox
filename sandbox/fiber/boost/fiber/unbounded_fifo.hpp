
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_UNBOUNDED_FIFO_H
#define BOOST_FIBERS_UNBOUNDED_FIFO_H

#include <cstddef>

#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/optional.hpp>
#include <boost/utility.hpp>

#include <boost/fiber/condition.hpp>
#include <boost/fiber/detail/atomic.hpp>
#include <boost/fiber/exceptions.hpp>
#include <boost/fiber/mutex.hpp>
#include <boost/fiber/unique_lock.hpp>

#include <boost/config/abi_prefix.hpp>

namespace boost {
namespace fibers {

template< typename T >
class unbounded_fifo : private noncopyable
{

public:
	typedef optional< T >	value_type;

private:
	struct node
	{
		typedef intrusive_ptr< node >	ptr_t;

		uint32_t	use_count;
		value_type	va;
		ptr_t		next;

		node() :
			use_count( 0),
			va(),
			next()
		{}

		inline friend void intrusive_ptr_add_ref( node * p)
		{ ++p->use_count; }
		
		inline friend void intrusive_ptr_release( node * p)
		{ if ( --p->use_count == 0) delete p; }
	};

	volatile uint32_t		state_;
	typename node::ptr_t	head_;
	mutex					head_mtx_;
	typename node::ptr_t	tail_;
	mutex					tail_mtx_;
	condition				not_empty_cond_;

	bool active_() const
	{ return 0 == state_; }

	void deactivate_()
	{ detail::atomic_fetch_add( & state_, 1); }

	bool empty_()
	{ return head_ == get_tail_(); }

	typename node::ptr_t get_tail_()
	{
		mutex::scoped_lock lk( tail_mtx_);	
		typename node::ptr_t tmp = tail_;
		return tmp;
	}

	typename node::ptr_t pop_head_()
	{
		typename node::ptr_t old_head = head_;
		head_ = old_head->next;
		return old_head;
	}

public:
	unbounded_fifo() :
		state_( 0),
		head_( new node),
		head_mtx_(),
		tail_( head_),
		tail_mtx_(),
		not_empty_cond_()
	{}

	void deactivate()
	{ deactivate_(); }

	bool empty()
	{
		mutex::scoped_lock lk( head_mtx_);
		return empty_();
	}

	void put( T const& t)
	{
		typename node::ptr_t new_node( new node);
		{
			mutex::scoped_lock lk( tail_mtx_);

			tail_->va = t;
			tail_->next = new_node;
			tail_ = new_node;
		}
		not_empty_cond_.notify_one();
	}

	bool take( value_type & va)
	{
		mutex::scoped_lock lk( head_mtx_);
		bool empty = empty_();
		if ( ! active_() && empty)
			return false;
		if ( empty)
		{
			try
			{
				while ( active_() && empty_() )
					not_empty_cond_.wait( lk);
			}
			catch ( fiber_interrupted const&)
			{ return false; }
		}
		if ( ! active_() && empty_() )
			return false;
		swap( va, head_->va);
		pop_head_();
		return va;
	}

	bool take(
		value_type & va,
		posix_time::time_duration const& rel_time)
	{
		mutex::scoped_lock lk( head_mtx_);
		bool empty = empty_();
		if ( ! active_() && empty)
			return false;
		if ( empty)
		{
			try
			{
				while ( active_() && empty_() )
					if ( ! not_empty_cond_.timed_wait( lk, rel_time) )
						return false;
			}
			catch ( fiber_interrupted const&)
			{ return false; }
		}
		if ( ! active_() && empty_() )
			return false;
		swap( va, head_->va);
		pop_head_();
		return va;
	}

	bool try_take( value_type & va)
	{
		mutex::scoped_lock lk( head_mtx_);
		if ( empty_() )
			return false;
		swap( va, head_->va);
		pop_head_();
		return va;
	}
};

}}

#include <boost/config/abi_suffix.hpp>

#endif // BOOST_FIBERS_UNBOUNDED_FIFO_H
