
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TASK_DETAIL_POOL_CALLABLE_H
#define BOOST_TASK_DETAIL_POOL_CALLABLE_H

#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/utility.hpp>

#include <boost/task/detail/config.hpp>
#include <boost/task/detail/interrupter.hpp>
#include <boost/task/task.hpp>

#include <boost/config/abi_prefix.hpp>

# if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable:4251 4275)
# endif

namespace boost { namespace task
{
namespace detail
{
class BOOST_TASK_DECL pool_callable
{
private:
	friend class scoped_guard;

	struct impl
	{
		virtual ~impl() {}
		virtual void run() = 0;
		virtual void set( shared_ptr< thread > &) = 0;
		virtual void reset() = 0;
	};

	template< typename R >
	class impl_wrapper : public impl
	{
	private:
		task< R >		t_;
		detail::interrupter	i_;

	public:
# if defined(BOOST_HAS_RVALUE_REFS)
		impl_wrapper(
			task< R > && t,
			detail::interrupter const& i)
		: t_( t), i_( i)
		{}
# else
		impl_wrapper(
			boost::detail::thread_move_t< task< R > > t,
			detail::interrupter const& i)
		: t_( t), i_( i)
		{}
# endif

		void run()
		{ t_(); }

		void set( shared_ptr< thread > & thrd)
		{ i_.set( thrd); }

		void reset()
		{ i_.reset(); }
	};

	shared_ptr< impl >	impl_;

public:
	class scoped_guard : public noncopyable
	{
	private:
		pool_callable	&	ca_;
	
	public:
		scoped_guard( pool_callable &, shared_ptr< thread > &);
	
		~scoped_guard();
	};

	pool_callable();

# if defined(BOOST_HAS_RVALUE_REFS)
	template< typename R >
	pool_callable(
		task< R > && t,
		detail::interrupter const& i)
	: impl_( new impl_wrapper<  R >( t, i) )
	{}
# else
	template< typename R >
	pool_callable(
		boost::detail::thread_move_t< task< R > > t,
		detail::interrupter const& i)
	: impl_( new impl_wrapper<  R >( t, i) )
	{}
# endif

	void operator()();

	bool empty() const;

	void clear();
};
}}}

# if defined(BOOST_MSVC)
# pragma warning(pop)
# endif

#include <boost/config/abi_suffix.hpp>

#endif // BOOST_TASK_DETAIL_POOL_CALLABLE_H

