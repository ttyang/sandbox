
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_FIBER_H
#define BOOST_FIBERS_FIBER_H

#include <cstddef>
#include <iostream>

#include <boost/bind.hpp>
#include <boost/config.hpp>
#include <boost/preprocessor/repetition.hpp>
#include <boost/move/move.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility.hpp>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/info.hpp>

#include <boost/config/abi_prefix.hpp>

# if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable:4251 4275)
# endif

namespace boost {
namespace fibers {

#define BOOST_FIBER_DEFAULT_STACKSIZE 64000

template< typename Strategy >
class scheduler;
class strategy;

class BOOST_FIBER_DECL fiber
{
private:
	template< typename Strategy >
	friend class scheduler;
	friend class strategy;

	static void convert_thread_to_fiber();
	static void convert_fiber_to_thread();

	BOOST_COPYABLE_AND_MOVABLE( fiber);

	detail::info_base::ptr_t	info_base_;

	explicit fiber( detail::info_base::ptr_t);

	void init_();

	detail::info_base::ptr_t info_() const;

	void switch_to_( fiber &);

	template< typename Fn >
	static detail::info_base::ptr_t make_info_(
		std::size_t stack_size, Fn fn)
	{
		return detail::info_base::ptr_t(
			new detail::info< Fn >( fn, stack_size) );
	}

	template< typename Fn >
	static detail::info_base::ptr_t make_info_(
		std::size_t stack_size, BOOST_RV_REF( Fn) fn)
	{
		return detail::info_base::ptr_t(
			new detail::info< Fn >( fn, stack_size) );
	}

public:
	class id;

	fiber();

	template< typename Fn >
	explicit fiber( Fn fn) :
		info_base_( make_info_( BOOST_FIBER_DEFAULT_STACKSIZE, fn) )
	{ init_(); }

	template< typename Fn >
	explicit fiber( std::size_t stack_size, Fn fn) :
		info_base_( make_info_( stack_size, fn) )
	{ init_(); }

#define BOOST_FIBER_ARG(z, n, unused) \
   BOOST_PP_CAT(A, n) BOOST_PP_CAT(a, n)
#define BOOST_ENUM_FIBER_ARGS(n) BOOST_PP_ENUM(n, BOOST_FIBER_ARG, ~)

#define BOOST_FIBER_FIBER_CTOR(z, n, unused) \
	template< typename Fn, BOOST_PP_ENUM_PARAMS(n, typename A) > \
	fiber( Fn fn, BOOST_ENUM_FIBER_ARGS(n)) : \
		info_base_( \
			make_info_( \
				BOOST_FIBER_DEFAULT_STACKSIZE, \
				boost::bind( boost::type< void >(), fn, BOOST_PP_ENUM_PARAMS(n, a)) ) ) \
	{ init_(); } \
	\
	template< typename Fn, BOOST_PP_ENUM_PARAMS(n, typename A) > \
	fiber( std::size_t stack_size, Fn fn, BOOST_ENUM_FIBER_ARGS(n)) : \
		info_base_( \
			make_info_( \
				stack_size, \
				boost::bind( boost::type< void >(), fn, BOOST_PP_ENUM_PARAMS(n, a)) ) ) \
	{ init_(); }

#ifndef BOOST_FIBER_MAX_ARITY
#define BOOST_FIBER_MAX_ARITY 10
#endif

BOOST_PP_REPEAT_FROM_TO( 1, BOOST_FIBER_MAX_ARITY, BOOST_FIBER_FIBER_CTOR, ~)

#undef BOOST_FIBER_FIBER_CTOR

	template< typename Fn >
	explicit fiber( BOOST_RV_REF( Fn) fn) :
		info_base_( make_info_( BOOST_FIBER_DEFAULT_STACKSIZE, fn) )
	{ init_(); }

	template< typename Fn >
	explicit fiber( std::size_t stack_size, BOOST_RV_REF( Fn) fn) :
		info_base_( make_info_( stack_size, fn) )
	{ init_(); }

	fiber( fiber const& other);

	fiber & operator=( BOOST_COPY_ASSIGN_REF( fiber) other);

	fiber( BOOST_RV_REF( fiber) other);

	fiber & operator=( BOOST_RV_REF( fiber) other);

	typedef detail::info_base::ptr_t::unspecified_bool_type	unspecified_bool_type;

	operator unspecified_bool_type() const;

	bool operator!() const;

	void swap( fiber & other);

	id get_id() const;

	bool operator==( fiber const& other) const;
	bool operator!=( fiber const& other) const;

	bool is_alive() const;

	int priority() const;

	void priority( int);

	void interrupt();

	bool interruption_requested() const;

	void cancel();

	void join();
};

class fiber::id
{
private:
	friend class fiber;

	detail::info_base::ptr_t	info_;

	explicit id( detail::info_base::ptr_t info) :
		info_( info)
	{}

public:
	id() :
		info_()
	{}

	bool operator==( id const& other) const
	{ return info_ == other.info_; }

	bool operator!=( id const& other) const
	{ return info_ != other.info_; }
	
	bool operator<( id const& other) const
	{ return info_ < other.info_; }
	
	bool operator>( id const& other) const
	{ return other.info_ < info_; }
	
	bool operator<=( id const& other) const
	{ return !( other.info_ < info_); }
	
	bool operator>=( id const& other) const
	{ return ! ( info_ < other.info_); }

	template< typename charT, class traitsT >
	friend std::basic_ostream< charT, traitsT > &
	operator<<( std::basic_ostream< charT, traitsT > & os, id const& other)
	{
		if ( other.info_)
			return os << other.info_;
		else
			return os << "{not-a-fiber}";
	}
};

template< typename Fn >
fiber make_fiber( Fn fn)
{ return fiber( fn); }

template< typename Fn >
fiber make_fiber( std::size_t stack_size, Fn fn)
{ return fiber( stack_size, fn); }

#define BOOST_FIBER_MAKE_FIBER_FUNCTION(z, n, unused) \
template< typename Fn, BOOST_PP_ENUM_PARAMS(n, typename A) > \
fiber make_fiber( Fn fn, BOOST_ENUM_FIBER_ARGS(n)) \
{ return fiber( fn, BOOST_PP_ENUM_PARAMS(n, a) ); } \
\
template< typename Fn, BOOST_PP_ENUM_PARAMS(n, typename A) > \
fiber make_fiber( std::size_t stack_size, Fn fn, BOOST_ENUM_FIBER_ARGS(n)) \
{ return fiber( stack_size, fn, BOOST_PP_ENUM_PARAMS(n, a) ); }

BOOST_PP_REPEAT_FROM_TO( 1, BOOST_FIBER_MAX_ARITY, BOOST_FIBER_MAKE_FIBER_FUNCTION, ~)

#undef BOOST_FIBER_MAKE_FIBER_FUNCTION
#undef BOOST_ENUM_FIBER_ARGS
#undef BOOST_FIBER_ARG
#undef BOOST_FIBER_MAX_ARITY

#undef BOOST_FIBER_DEFAULT_STACKSIZE

}

using fibers::fiber;

inline
void swap( fiber & l, fiber & r)
{ return l.swap( r); }

}

# if defined(BOOST_MSVC)
# pragma warning(pop)
# endif

#include <boost/config/abi_suffix.hpp>

#endif // BOOST_FIBERS_FIBER_H
