
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_MANUAL_RESET_EVENT_H
#define BOOST_FIBERS_MANUAL_RESET_EVENT_H

#include <boost/cstdint.hpp>
#include <boost/utility.hpp>

#include <boost/fiber/object/id.hpp>
#include <boost/fiber/mutex.hpp>

namespace boost {
namespace fibers {

class manual_reset_event : private noncopyable
{
private:
	enum state_t
	{
		RESET = 0,
		SET
	};

	volatile uint32_t	state_;
	volatile uint32_t	waiters_;
	mutex				enter_mtx_;
	object::id			id_;

public:
	explicit manual_reset_event( bool = false);

	~manual_reset_event();

	void set();

	void reset();

	void wait();

	bool try_wait();
};

}}

#endif // BOOST_FIBERS_MANUAL_RESET_EVENT_H
