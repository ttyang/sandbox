
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_SPIN_BARRIER_H
#define BOOST_FIBERS_SPIN_BARRIER_H

#include <boost/cstdint.hpp>
#include <boost/utility.hpp>

#include <boost/fiber/spin_condition.hpp>
#include <boost/fiber/spin_mutex.hpp>

namespace boost {
namespace fibers {

class spin_barrier : private noncopyable
{
private:
	uint32_t		initial_;
	uint32_t		current_;
	bool			cycle_;
	spin_mutex		mtx_;
	spin_condition		cond_;

public:
	spin_barrier( uint32_t);

	bool wait();
};

}}

#endif // BOOST_FIBERS_SPIN_BARRIER_H
