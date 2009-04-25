
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TASK_DETAIL_THREAD_CALLABLE_H
#define BOOST_TASK_DETAIL_THREAD_CALLABLE_H

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/utility.hpp>

#include <boost/task/detail/config.hpp>
#include <boost/task/detail/interrupter.hpp>
#include <boost/task/semaphore.hpp>
#include <boost/task/task.hpp>

#include <boost/config/abi_prefix.hpp>

namespace boost { namespace task
{
namespace detail
{
class BOOST_TASK_DECL thread_callable
{
private:
	struct impl
	{
		virtual ~impl() {}
		virtual void run() = 0;
		virtual void set( shared_ptr< thread > &) = 0;
	};

	template< typename R >
	class impl_wrapper : public impl
	{
	private:
		task< R >			t_;
		detail::interrupter	i_;
		semaphore			sem_;

	public:
		impl_wrapper(
			task< R > const& t,
			detail::interrupter const& i)
		: t_( t), i_( i), sem_( 0)
		{}

		void run()
		{
			sem_.wait();
			t_();
		}

		void set( shared_ptr< thread > & thrd)
		{
			i_.set( thrd);
			sem_.post();
		}
	};

	shared_ptr< impl >	impl_;

public:
	template< typename R >
	thread_callable(
		task< R > const& t,
		detail::interrupter const& i)
	: impl_( new impl_wrapper<  R >( t, i) )
	{}

	void operator()();

	void set( shared_ptr< thread > &);
};
} } }

#include <boost/config/abi_suffix.hpp>

#endif // BOOST_TASK_DETAIL_THREAD_CALLABLE_H

