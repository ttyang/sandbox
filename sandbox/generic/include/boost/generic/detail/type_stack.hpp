/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_TYPE_STACK_HPP
#define BOOST_GENERIC_DETAIL_TYPE_STACK_HPP

// ToDo: Optimize this with preprocessing

#include <boost/generic/limits.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/size_t.hpp>

#ifdef BOOST_NO_VARIADIC_TEMPLATES

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#endif


namespace boost_generic_detail {

#ifndef BOOST_NO_VARIADIC_TEMPLATES

// Used with decltype in return types to get SFINAE
template< class... T >
struct type_stack {};

#else

// Used with decltype in return types to get SFINAE
template< BOOST_PP_ENUM_BINARY_PARAMS
          ( BOOST_PP_INC( BOOST_GENERIC_MAX_CONCEPT_ARITY )
          , class T, = void BOOST_PP_INTERCEPT
          )
        >
struct type_stack;

#endif // End no variadic template check

template< class TypeStack, class Elem >
struct push;

template< class TypeStack >
struct pop;

template< class TypeStack, class Elem >
struct has;


template< class TypeStack, class Predicate >
struct contains_match;

struct no_match;

template< class TypeStack >
struct size;

template< class TypeStack, class Predicate >
struct find_if;

#ifndef BOOST_NO_VARIADIC_TEMPLATES

template< class F >
void for_each( type_stack<> seq, F fun ) {}

template< class Head, class... T, class F >
void for_each( type_stack< Head, T... > seq, F fun )
{
  fun( Head() );
  for_each( type_stack< T... >(), fun );
}

template< class... T, class Elem >
struct push< type_stack< T... >, Elem >
{
  typedef type_stack< Elem, T... > type;
};

template< class Head, class... T >
struct pop< type_stack< Head, T... > >
{
  typedef type_stack< T... > type;
};

template< class Elem >
struct has< type_stack<>, Elem >
  : boost::mpl::false_ {};

template< class Head, class... T, class Elem >
struct has< type_stack< Head, T... >, Elem >
  : has< typename pop< type_stack< T... > >::type, Elem > {};

template< class Elem, class... T >
struct has< type_stack< Elem, T... >, Elem >
  : boost::mpl::true_ {};

template< class Predicate >
struct contains_match< type_stack<>, Predicate >
  : boost::mpl::false_ {};

template< class Head, class... T, class Predicate >
struct contains_match< type_stack< Head, T... >, Predicate >
  : boost::mpl::or_
    < typename boost::mpl::apply
      < Predicate
      , Head
      >
      ::type
    , contains_match< type_stack< T... >, Predicate >
    > {};

template< class... T >
struct size< type_stack< T... > > : ::boost::mpl::size_t< sizeof...( T ) > {};

template< class Predicate >
struct find_if< type_stack<>, Predicate >
{
  typedef no_match type;
};

template< class Head, class... T, class Predicate >
struct find_if< type_stack< Head, T... >, Predicate >
  : boost::mpl::if_
    < typename boost::mpl::apply
      < Predicate
      , Head
      >
      ::type
    , boost::mpl::identity< Head >
    , find_if< type_stack< T... >, Predicate >
    >
    ::type {};

#else

#define BOOST_GENERIC_DETAIL_TYPE_STACK_FOR_EACH_CALL_FUN_MAC( z, n, text )    \
fun( BOOST_PP_CAT( T, n )() );

#define BOOST_GENERIC_DETAIL_TYPE_STACK_FOR_EACH_MAC( z, n, test )             \
template< BOOST_PP_ENUM_PARAMS_Z( z, n, class T )                              \
          BOOST_PP_COMMA_IF( n )                                               \
          class F                                                              \
        >                                                                      \
void for_each                                                                  \
     ( type_stack< BOOST_PP_ENUM_PARAMS_Z( z, n, T ) > seq                     \
     , F fun                                                                   \
     )                                                                         \
{                                                                              \
  BOOST_PP_ENUM_ ## z                                                          \
  ( n, BOOST_GENERIC_DETAIL_TYPE_STACK_FOR_EACH_CALL_FUN_MAC, ~ )              \
}

BOOST_PP_REPEAT( BOOST_PP_INC( BOOST_GENERIC_MAX_CONCEPT_ARITY )
               , BOOST_GENERIC_DETAIL_TYPE_STACK_FOR_EACH_MAC
               , ~
               )

#undef BOOST_GENERIC_DETAIL_TYPE_STACK_FOR_EACH_MAC
#undef BOOST_GENERIC_DETAIL_TYPE_STACK_FOR_EACH_CALL_FUN_MAC

#define BOOST_GENERIC_DETAIL_TYPE_STACK_PUSH_MAC( z, n, test )                 \
template< BOOST_PP_ENUM_PARAMS_Z( z, n, class T )                              \
          BOOST_PP_COMMA_IF( n )                                               \
          class Elem                                                           \
        >                                                                      \
struct push< type_stack< BOOST_PP_ENUM_PARAMS_Z( z, n, T ) >, Elem >           \
{                                                                              \
  typedef type_stack< Elem BOOST_PP_ENUM_TRAILING_PARAMS_Z( z, n, T ) > type;  \
};


BOOST_PP_REPEAT( BOOST_PP_INC( BOOST_GENERIC_MAX_CONCEPT_ARITY )
               , BOOST_GENERIC_DETAIL_TYPE_STACK_PUSH_MAC
               , ~
               )

#undef BOOST_GENERIC_DETAIL_TYPE_STACK_PUSH_MAC

#define BOOST_GENERIC_DETAIL_TYPE_STACK_POP_MAC( z, n, test )                  \
template< class Head                                                           \
          BOOST_PP_ENUM_TRAILING_PARAMS_Z( z, n, class T )                     \
        >                                                                      \
struct pop< type_stack< Head BOOST_PP_ENUM_TRAILING_PARAMS_Z( z, n, T ) > >    \
{                                                                              \
  typedef type_stack< BOOST_PP_ENUM_PARAMS_Z( z, n, T ) > type;                \
};

BOOST_PP_REPEAT( BOOST_GENERIC_MAX_CONCEPT_ARITY
               , BOOST_GENERIC_DETAIL_TYPE_STACK_POP_MAC
               , ~
               )

#undef BOOST_GENERIC_DETAIL_TYPE_STACK_POP_MAC

#endif // End no variadic template check

}

#endif // BOOST_GENERIC_DETAIL_TYPE_STACK_HPP
