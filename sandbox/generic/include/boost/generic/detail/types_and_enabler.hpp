#ifndef BOOST_GENERIC_DETAIL_TYPES_AND_ENABLER_HPP
#define BOOST_GENERIC_DETAIL_TYPES_AND_ENABLER_HPP

#include <type_traits>

namespace boost { namespace generic { namespace detail {

struct types_and_enabler_enabler_type;

template< class... T >
struct types_and_enabler;

template< class... T > struct variadic_always_false : std::false_type {};

// Default definition, only used when size == 0
template< class... T >
struct last_arg
{
  static_assert( variadic_always_false< T... >::value
               , "last_arg not defined for empty template argument lists"
               );
};

template< class Head, class... Tail >
struct last_arg : last_arg< Tail > {};

template< class OnlyElement >
struct last_arg
{
  typedef OnlyElement type;
};

// ToDo: Eventually remove these checks for better compile times
template< class... T >
struct types_and_enabler
{
  static_assert( std::is_same< typename last_arg< T... >::type
                             , types_and_enabler_enabler_type
                             >::value
               , "The last argument to types_and_enabler must be the enabler"
               );
};

} } }

// Requires at least 1 type
#define BOOST_GENERIC_DETAIL_TYPES_AND_ENABLER( types_in_paren_ )              \
BOOST_GENERIC_DETAIL_TYPES_AND_ENABLER_IMPL types_in_paren_

#define BOOST_GENERIC_DETAIL_TYPES_AND_ENABLER_IMPL( ... )                     \
::boost::generic::detail::types_and_enabler                                    \
< __VA_ARGS__                                                                  \
, ::boost::generic::detail::types_and_enabler_enabler_type                     \
>

#endif // BOOST_GENERIC_DETAIL_TYPES_AND_ENABLER_HPP
