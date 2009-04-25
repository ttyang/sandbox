
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TASK_LAUNCH_H
#define BOOST_TASK_LAUNCH_H

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include <boost/task/default_pool.hpp>
#include <boost/task/detail/interrupter.hpp>
#include <boost/task/detail/thread_callable.hpp>
#include <boost/task/handle.hpp>
#include <boost/task/pool.hpp>
#include <boost/task/task.hpp>

namespace boost { namespace task
{
template< typename R >
handle< R > launch_in_pool( task< R > t)
{ return get_default_pool().submit( t); }

template<
	typename R,
	typename Attr
>
handle< R > launch_in_pool(
	task< R > t,
	Attr const& attr)
{ return get_default_pool().submit( t, attr); }

template<
	typename Channel,
	typename R
>
handle< R > launch_in_pool(
	pool< Channel > & pool,
	task< R > t)
{ return pool.submit( t); }

template<
	typename Channel,
	typename R,
	typename Attr
>
handle< R > launch_in_pool(
	pool< Channel > & pool,
	task< R > t,
	Attr const& attr)
{ return pool.submit( t, attr); }


template< typename R >
handle< R > launch_in_thread( task< R > t)
{
	detail::interrupter intr;
	detail::thread_callable ca( t, intr);

	shared_ptr< thread > thrd( new thread( ca) );
	ca.set( thrd);

	return handle< R >( t.get_id(), t.get_future(), intr);
}
} }

#endif // BOOST_TASK_LAUNCH_H
