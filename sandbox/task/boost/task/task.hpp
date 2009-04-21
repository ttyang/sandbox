
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TASK_TASK_H
#define BOOST_TASK_TASK_H

#include <exception>
#include <ios>
#include <new>
#include <stdexcept>
#include <typeinfo>

#include <boost/preprocessor/repetition.hpp>
#include <boost/thread.hpp>
#include <boost/thread/thread_time.hpp>
#include <boost/utility/result_of.hpp>

#include <boost/task/detail/interrupter.hpp>
#include <boost/task/future.hpp>
#include <boost/task/exceptions.hpp>
#include <boost/task/handle.hpp>

namespace boost { namespace task
{
namespace detail
{
class callable;
}

template< typename Channel >
class pool;

template< typename R >
class task
{
private:
	template< typename Channel >
	friend class pool;
	friend class detail::callable;

	struct impl
	{
		promise< R >			prom;
		shared_future< R >		fut;
		detail::interrupter		intr;

		impl()
		:
		prom(),
		fut( prom.get_future() ),
		intr()
		{}

		virtual ~impl()
		{ intr.reset(); }

		virtual void operator()() = 0;
	};

	template< typename Fn >
	class impl_wrapper : public impl
	{
	private:
		Fn		fn_;

	public:
		impl_wrapper( Fn const& fn)
		: fn_( fn)
		{}

		void operator()() // throw()
		{
			try
			{ impl::prom.set_value( fn_() ); }
			catch ( thread_interrupted const&)
			{ impl::prom.set_exception( copy_exception( task_interrupted() ) ); }
			catch ( boost::exception const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::ios_base::failure const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::domain_error const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::invalid_argument const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::length_error const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::out_of_range const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::logic_error const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::overflow_error const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::range_error const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::underflow_error const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::runtime_error const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::bad_alloc const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::bad_cast const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::bad_typeid const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::bad_exception const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch(...)
			{ impl::prom.set_exception( current_exception() ); }
		}
	};

	shared_ptr< impl >	impl_;

public:
	task()
	: impl_()
	{}

	template< typename Fn >
	task( Fn const& fn)
	: impl_( new impl_wrapper< Fn >( fn) )
	{}

	const handle< R > get_handle()
	{ return handle< R >( impl_->fut, impl_->intr); }

	void swap( task< R > & other) // throw()
	{ impl_.swap( other.impl_); }

	void operator()() // throw()
	{ ( * impl_)(); }

	template< typename F >
	void set_wait_callback( F const& f)
	{ impl_->prom.set_wait_callback( f); }
};

template<>
class task< void >
{
private:
	template< typename Channel >
	friend class pool;
	friend class detail::callable;

	struct impl
	{
		promise< void >			prom;
		shared_future< void >	fut;
		detail::interrupter		intr;

		impl()
		:
		prom(),
		fut( prom.get_future() ),
		intr()
		{}

		virtual ~impl()
		{ intr.reset(); }

		virtual void operator()() = 0;
	};

	template< typename Fn >
	class impl_wrapper : public impl
	{
	private:
		Fn		fn_;

	public:
		impl_wrapper( Fn const& fn)
		: fn_( fn)
		{}

		void operator()() // throw()
		{
			try
			{
				fn_();
				impl::prom.set_value();
			}
			catch ( thread_interrupted const&)
			{ impl::prom.set_exception( copy_exception( task_interrupted() ) ); }
			catch ( boost::exception const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::ios_base::failure const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::domain_error const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::invalid_argument const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::length_error const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::out_of_range const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::logic_error const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::overflow_error const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::range_error const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::underflow_error const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::runtime_error const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::bad_alloc const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::bad_cast const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::bad_typeid const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch ( std::bad_exception const& e)
			{ impl::prom.set_exception( copy_exception( e) ); }
			catch(...)
			{ impl::prom.set_exception( current_exception() ); }
		}
	};

	shared_ptr< impl >	impl_;

public:
	task()
	: impl_()
	{}

	template< typename Fn >
	task( Fn const& fn)
	: impl_( new impl_wrapper< Fn >( fn) )
	{}

	const handle< void > get_handle()
	{ return handle< void >( impl_->fut, impl_->intr); }

	void swap( task< void > & other) // throw()
	{ impl_.swap( other.impl_); }

	void operator()() // throw()
	{ ( * impl_)(); }

	template< typename F >
	void set_wait_callback( F const& f)
	{ impl_->prom.set_wait_callback( f); }
};

template< typename Fn >
task< typename result_of< Fn() >::type > make_task( Fn fn)
{ return task< typename boost::result_of< Fn() >::type >( fn); }

# ifndef BOOST_TASK_MAKE_TASK_MAX_ARITY
#   define BOOST_TASK_MAKE_TASK_MAX_ARITY 10
# endif

# define BOOST_TASK_MAKE_TASK_FUNC_ARG(z, n, unused) \
   BOOST_PP_CAT(A, n) BOOST_PP_CAT(a, n)
# define BOOST_ENUM_TASK_MAKE_TASK_FUNC_ARGS(n) BOOST_PP_ENUM(n, BOOST_TASK_MAKE_TASK_FUNC_ARG, ~)

# define BOOST_TASK_MAKE_TASK_FUNCTION(z, n, unused)	\
template<												\
	typename Fn,										\
	BOOST_PP_ENUM_PARAMS(n, typename A)					\
>														\
task< typename result_of< Fn( BOOST_PP_ENUM_PARAMS(n, A)) >::type >		\
make_task( Fn fn, BOOST_ENUM_TASK_MAKE_TASK_FUNC_ARGS(n))				\
{ return make_task( boost::bind( fn, BOOST_PP_ENUM_PARAMS(n, a))); }

BOOST_PP_REPEAT_FROM_TO( 1, BOOST_TASK_MAKE_TASK_MAX_ARITY, BOOST_TASK_MAKE_TASK_FUNCTION, ~)

# undef BOOST_TASK_MAKE_TASK_FUNCTION
# undef BOOST_TASK_MAKE_TASK_FUNC_ARG
# undef BOOST_ENUM_TASK_MAKE_TASK_FUNC_ARGS

}}

#endif // BOOST_TASK_TASK_H
