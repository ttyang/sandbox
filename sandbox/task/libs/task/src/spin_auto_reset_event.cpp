
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "boost/task/spin_auto_reset_event.hpp"

#include <boost/thread.hpp>

#include <boost/task/detail/atomic.hpp>
#include <boost/task/utility.hpp>

namespace boost {
namespace task {

spin_auto_reset_event::spin_auto_reset_event( bool isset) :
	state_(
		isset ?
		static_cast< uint32_t >( SET) :
		static_cast< uint32_t >( RESET) )
{}

void
spin_auto_reset_event::set()
{ detail::atomic_exchange( & state_, static_cast< uint32_t >( SET) ); }

void
spin_auto_reset_event::wait()
{
	uint32_t expected = static_cast< uint32_t >( SET);
	while ( ! detail::atomic_compare_exchange_strong(
			& state_, & expected,
			static_cast< uint32_t >( RESET) ) )
	{
		this_thread::interruption_point();
		if ( this_task::runs_in_pool() )
			this_task::block();
		else
			this_thread::yield();
		this_thread::interruption_point();
		expected = static_cast< uint32_t >( SET);
	}
}

bool
spin_auto_reset_event::wait( system_time const& abs_time)
{
	if ( get_system_time() >= abs_time) return false;

	uint32_t expected = static_cast< uint32_t >( SET);
	while ( ! detail::atomic_compare_exchange_strong(
			& state_, & expected,
			static_cast< uint32_t >( RESET) ) )
	{
		this_thread::interruption_point();
		if ( this_task::runs_in_pool() )
			this_task::block();
		else
			this_thread::yield();	
		this_thread::interruption_point();
	
		if ( get_system_time() >= abs_time) return false;
		expected = static_cast< uint32_t >( SET);
	}

	return true;
}

}}
