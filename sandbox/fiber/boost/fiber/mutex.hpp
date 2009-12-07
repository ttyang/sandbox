
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
//  based on boost::interprocess::sync::interprocess_mutex

#ifndef BOOST_FIBERS_MUTEX_H
#define BOOST_FIBERS_MUTEX_H

#include <boost/cstdint.hpp>
#include <boost/thread/locks.hpp>
#include <boost/utility.hpp>

#include <boost/fiber/object/id.hpp>
#include <boost/fiber/scheduler.hpp>
#include <boost/fiber/strategy.hpp>

namespace boost {
namespace fibers {

class mutex : private noncopyable
{
private:
	volatile uint32_t	state_;
	object::id			id_;
	strategy::ptr_t		strategy_;

public:
	typedef unique_lock< mutex >			scoped_lock;

	template< typename Strategy >
	mutex( scheduler< Strategy > & sched) :
		state_( 0),
		id_( * this),
		strategy_( sched.strategy_)
	{ strategy_->register_object( id_); }

	~mutex();

	void lock();

	bool try_lock();

	void unlock();
};

typedef mutex try_mutex;

}}

#endif // BOOST_FIBERS_MUTEX_H
