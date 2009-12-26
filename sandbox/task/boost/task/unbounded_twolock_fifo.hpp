
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TASKS_UNBOUNDED_TWOLOCK_FIFO_H
#define BOOST_TASKS_UNBOUNDED_TWOLOCK_FIFO_H

#include <cstddef>

#include <boost/assert.hpp>
#include <boost/bind.hpp>
#include <boost/cstdint.hpp>
#include <boost/foreach.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/shared_mutex.hpp>

#include <boost/task/callable.hpp>
#include <boost/task/detail/atomic.hpp>
#include <boost/task/detail/meta.hpp>
#include <boost/task/exceptions.hpp>

#include <boost/config/abi_prefix.hpp>

namespace boost {
namespace tasks {

class unbounded_twolock_fifo
{
public:
	typedef detail::has_no_attribute	attribute_tag_type;
	typedef callable					value_type;

private:
	struct node
	{
		typedef shared_ptr< node >	sptr_t;

		value_type	va;
		sptr_t		next;
	};

	volatile uint32_t	state_;
	node::sptr_t		head_;
	mutex				head_mtx_;
	node::sptr_t		tail_;
	mutex				tail_mtx_;
	condition			not_empty_cond_;

	bool active_() const
	{ return 0 == state_; }

	void deactivate_()
	{ detail::atomic_fetch_add( & state_, 1); }

	bool empty_()
	{ return head_ == get_tail_(); }

	node::sptr_t get_tail_()
	{
		lock_guard< mutex > lk( tail_mtx_);	
		node::sptr_t tmp = tail_;
		return tmp;
	}

	node::sptr_t pop_head_()
	{
		node::sptr_t old_head = head_;
		head_ = old_head->next;
		return old_head;
	}

public:
	unbounded_twolock_fifo() :
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
		unique_lock< mutex > lk( head_mtx_);
		return empty_();
	}

	void put( value_type const& va)
	{
		node::sptr_t new_node( new node);
		{
			unique_lock< mutex > lk( tail_mtx_);
			tail_->va = va;
			tail_->next = new_node;
			tail_ = new_node;
		}
		not_empty_cond_.notify_one();
	}

	bool take( value_type & va)
	{
		unique_lock< mutex > lk( head_mtx_);
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
			catch ( thread_interrupted const&)
			{ return false; }
		}
		if ( ! active_() && empty_() )
			return false;
		va.swap( head_->va);
		pop_head_();
		return ! va.empty();
	}

	template< typename Duration >
	bool take(
		value_type & va,
		Duration const& rel_time)
	{
		unique_lock< mutex > lk( head_mtx_);
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
			catch ( thread_interrupted const&)
			{ return false; }
		}
		if ( ! active_() && empty_() )
			return false;
		va.swap( head_->va);
		pop_head_();
		return ! va.empty();
	}

	bool try_take( value_type & va)
	{
		unique_lock< mutex > lk( head_mtx_);
		if ( empty_() )
			return false;
		va.swap( head_->va);
		pop_head_();
		return ! va.empty();
	}
};

}}

#include <boost/config/abi_suffix.hpp>

#endif // BOOST_TASKS_UNBOUNDED_TWOLOCK_FIFO_H
