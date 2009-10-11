
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TASK_SPIN_COUNT_DOWN_EVENT_H
#define BOOST_TASK_SPIN_COUNT_DOWN_EVENT_H

#include <boost/cstdint.hpp>
#include <boost/thread/thread_time.hpp>
#include <boost/utility.hpp>

#include <boost/task/spin_mutex.hpp>

namespace boost {
namespace task {

class spin_count_down_event : private noncopyable
{
private:
	uint32_t			initial_;
	volatile uint32_t	current_;

public:
	explicit spin_count_down_event( uint32_t);

	uint32_t initial() const;

	uint32_t current() const;

	bool is_set() const;

	void set();

	void wait();

	bool wait( system_time const&);

	template< typename TimeDuration >
	bool wait( TimeDuration const& rel_time)
	{ return wait( get_system_time() + rel_time); }
};

}}

#endif // BOOST_TASK_SPIN_COUNT_DOWN_EVENT_H
