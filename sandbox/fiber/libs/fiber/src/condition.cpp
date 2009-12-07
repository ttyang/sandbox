
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "boost/fiber/condition.hpp"

#include <boost/assert.hpp>
#include <boost/thread.hpp>

#include <boost/fiber/detail/atomic.hpp>
#include <boost/fiber/utility.hpp>

namespace boost {
namespace fibers {

void
condition::wait_( mutex & mtx)
{
	{
		mutex::scoped_lock lk( enter_mtx_);
		BOOST_ASSERT( lk);
		detail::atomic_fetch_add( & waiters_, 1);
		mtx.unlock();
	}

	bool unlock_enter_mtx = false;
	for (;;)
	{
		while ( static_cast< uint32_t >( SLEEPING) == detail::atomic_load( & cmd_) )
			strategy_->wait_for_object( id_);

		mutex::scoped_lock lk( check_mtx_);
		BOOST_ASSERT( lk);

		uint32_t expected = static_cast< uint32_t >( NOTIFY_ONE);
		detail::atomic_compare_exchange_strong(
				& cmd_, & expected,
				static_cast< uint32_t >( SLEEPING) );
		if ( static_cast< uint32_t >( SLEEPING) == expected)
			continue;
		else if ( static_cast< uint32_t >( NOTIFY_ONE) == expected)
		{
			unlock_enter_mtx = true;
			detail::atomic_fetch_sub( & waiters_, 1);
			break;
		}
		else
		{
			unlock_enter_mtx = 1 == detail::atomic_fetch_sub( & waiters_, 1);
			if ( unlock_enter_mtx)
			{
				expected = static_cast< uint32_t >( NOTIFY_ALL);
				detail::atomic_compare_exchange_strong(
						& cmd_, & expected,
						static_cast< uint32_t >( SLEEPING) );
			}
			break;
		}
	}

	if ( unlock_enter_mtx)
		enter_mtx_.unlock();

	mtx.lock();
}

condition::~condition()
{ strategy_->unregister_object( id_); }

void
condition::notify_one()
{
	enter_mtx_.lock();

	if ( 0 == detail::atomic_load( & waiters_) )
	{
		enter_mtx_.unlock();
		return;
	}

	uint32_t cmd = static_cast< uint32_t >( NOTIFY_ONE);
	uint32_t expected = static_cast< uint32_t >( SLEEPING);
	while ( ! detail::atomic_compare_exchange_strong(
				& cmd_, & expected, cmd) )
		this_fiber::yield();
	
	strategy_->object_notify_one( id_);
}

void
condition::notify_all()
{
	enter_mtx_.lock();

	if ( 0 == detail::atomic_load( & waiters_) )
	{
		enter_mtx_.unlock();
		return;
	}

	uint32_t cmd = static_cast< uint32_t >( NOTIFY_ALL);
	uint32_t expected = static_cast< uint32_t >( SLEEPING);
	while ( ! detail::atomic_compare_exchange_strong(
				& cmd_, & expected, cmd) )
		this_fiber::yield();

	strategy_->object_notify_all( id_);
}

}}
