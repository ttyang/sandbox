
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "boost/fiber/spin/count_down_event.hpp"

#include <boost/fiber/detail/atomic.hpp>
#include <boost/fiber/spin/mutex.hpp>
#include <boost/fiber/utility.hpp>

namespace boost {
namespace fibers {
namespace spin {

count_down_event::count_down_event( uint32_t initial) :
	initial_( initial),
	current_( initial_)
{}

uint32_t
count_down_event::initial() const
{ return initial_; }

uint32_t
count_down_event::current() const
{ return detail::atomic_load( & current_); }

bool
count_down_event::is_set() const
{ return 0 == detail::atomic_load( & current_); }

void
count_down_event::set()
{
	for (;;)
	{
		if ( 0 == detail::atomic_load( & current_) )
			return;
		uint32_t expected = current_;
		if ( detail::atomic_compare_exchange_strong( & current_, & expected, expected - 1) )
			return;
	}
}

void
count_down_event::wait()
{
	while ( 0 != detail::atomic_load( & current_) )
		this_fiber::yield();	
}

}}}
