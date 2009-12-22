
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_SPIN_UNBOUNDED_FIFO_H
#define BOOST_FIBERS_SPIN_UNBOUNDED_FIFO_H

#include <cstddef>

#include <boost/atomic.hpp>
#include <boost/config.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/optional.hpp>
#include <boost/utility.hpp>

#include <boost/fiber/exceptions.hpp>
#include <boost/fiber/spin/condition.hpp>
#include <boost/fiber/spin/mutex.hpp>

#include <boost/config/abi_prefix.hpp>

namespace boost {
namespace fibers {
namespace spin {

template< typename T >
class unbounded_fifo
{
public:
	typedef optional< T >	value_type;

private:
	class impl : private noncopyable
	{
	private:
		struct node
		{
			typedef intrusive_ptr< node >	ptr;

			atomic< std::size_t >	use_count;
			value_type				va;
			ptr						next;

			node() :
				use_count( 0),
				va(),
				next()
			{}

			inline friend void intrusive_ptr_add_ref( node * p)
			{ p->use_count.fetch_add( 1, memory_order_relaxed); }
			
			inline friend void intrusive_ptr_release( node * p)
			{
				if ( p->use_count.fetch_sub( 1, memory_order_release) == 1)
				{
					atomic_thread_fence( memory_order_acquire);
					delete p;
				}
			}
		};

		enum state
		{
			ACTIVE = 0,
			DEACTIVE
		};

		atomic< state >			state_;
		typename node::ptr		head_;
		mutable mutex			head_mtx_;
		typename node::ptr		tail_;
		mutable mutex			tail_mtx_;
		condition				not_empty_cond_;
		atomic< std::size_t >	use_count_;

		bool active_() const
		{ return ACTIVE == state_.load(); }

		void deactivate_()
		{ state_.store( DEACTIVE); }

		bool empty_() const
		{ return head_ == get_tail_(); }

		typename node::ptr get_tail_() const
		{
			mutex::scoped_lock lk( tail_mtx_);	
			typename node::ptr tmp = tail_;
			return tmp;
		}

		typename node::ptr pop_head_()
		{
			typename node::ptr old_head = head_;
			head_ = old_head->next;
			return old_head;
		}

	public:
		impl() :
			state_( ACTIVE),
			head_( new node() ),
			head_mtx_(),
			tail_( head_),
			tail_mtx_(),
			not_empty_cond_(),
			use_count_( 0)
		{}

		void deactivate()
		{ deactivate_(); }

		bool empty() const
		{
			mutex::scoped_lock lk( head_mtx_);
			return empty_();
		}

		void put( T const& t)
		{
			typename node::ptr new_node( new node() );
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

		bool try_take( value_type & va)
		{
			mutex::scoped_lock lk( head_mtx_);
			if ( empty_() )
				return false;
			swap( va, head_->va);
			pop_head_();
			return va;
		}

		inline friend void intrusive_ptr_add_ref( impl * p)
		{ p->use_count_.fetch_add( 1, memory_order_relaxed); }
		
		inline friend void intrusive_ptr_release( impl * p)
		{
			if ( p->use_count_.fetch_sub( 1, memory_order_release) == 1)
			{
				atomic_thread_fence( memory_order_acquire);
				delete p;
			}
		}
	};

	intrusive_ptr< impl >	impl_;

public:
	unbounded_fifo() :
		impl_( new impl() )
	{}

	void deactivate()
	{ impl_->deactivate(); }

	bool empty()
	{ return impl_->empty(); }

	void put( T const& t)
	{ impl_->put( t); }

	bool take( value_type & va)
	{ return impl_->take( va); }

	bool try_take( value_type & va)
	{ return impl_->try_take( va); }
};

}}}

#include <boost/config/abi_suffix.hpp>

#endif // BOOST_FIBERS_SPIN_UNBOUNDED_FIFO_H
