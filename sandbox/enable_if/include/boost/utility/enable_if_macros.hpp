/*==============================================================================
    Copyright (c) 2011, 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#ifndef BOOST_ENABLE_IF_MACROS_HPP
#define BOOST_ENABLE_IF_MACROS_HPP

#include <boost/config.hpp>

// TODO: Add check for relaxed typename rule
#if    defined( BOOST_NO_VARIADIC_MACROS )                                     \
    || defined( BOOST_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS )                      \
    || defined( BOOST_NO_DECLTYPE )

#define BOOST_NO_ENABLE_IF_MACRO

#else

#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/array/data.hpp>
#include <boost/preprocessor/array/pop_front.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/variadic_seq_to_seq.hpp>
#include <boost/preprocessor/tuple/enum.hpp>
#include <boost/preprocessor/tuple/to_array.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/type_traits/function_traits.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/variadic_macro_data/vmd_is_begin_parens.hpp>

////////////////////////////////////////////////////////////////////////////////
// Requires C++11 features:
//   Default template arguments to function templates
//   Variadic macros
//   Relaxed typename rule
//   decltype
//
// Example Usage:
//
// struct foo
// {
//   typedef float value_type;
//   template< BOOST_ENABLE_IF( boost::is_floating_point< value_type > ) >
//   operator long double() const { return 0.l; }
// };
//
////////////////////////////////////////////////////////////////////////////////

namespace boost { namespace enable_if_detail {

enum enabler_type { enabler_type_enabler };

template< class Dummy, bool C >
struct enable_if_c_impl : boost::enable_if_c< C, enabler_type > {};

template< class Dummy, bool C >
struct disable_if_c_impl : boost::enable_if_c< !C, enabler_type > {};

template< class Dummy, bool C, class LazyType >
struct lazy_enable_if_c_impl : boost::enable_if_c< C, LazyType > {};

template< class Dummy, bool C, class LazyType >
struct lazy_disable_if_c_impl : boost::enable_if_c< !C, LazyType > {};

template< class Dummy, class C >
struct enable_if_impl : boost::enable_if_c< C::value, enabler_type > {};

template< class Dummy, class C >
struct disable_if_impl : boost::enable_if_c< !C::value, enabler_type > {};

template< class Dummy, class C, class LazyType >
struct lazy_enable_if_impl : boost::enable_if_c< C::value, LazyType > {};

template< class Dummy, class C, class LazyType >
struct lazy_disable_if_impl : boost::enable_if_c< !C::value, LazyType > {};

template< class... T >
struct always_enabler_type { typedef enabler_type type; };

template< class... T > struct always_true { static bool const value = true; };

template< class... T > struct always_void { typedef void type; };

} }

#define BOOST_DECLARE_ENABLE_IF_PARAM_NO_DEFAULT() class

#define BOOST_DECLARE_ENABLE_IF_PARAM() class = void

#define BOOST_TYPE_ENABLE_IF( ... )                                            \
typename ::boost::enable_if_c< __VA_ARGS__::value >::type

#define BOOST_TYPE_ENABLE_IF_C( ... )                                          \
typename ::boost::enable_if_c< __VA_ARGS__ >::type

#define BOOST_TYPE_DISABLE_IF( ... )                                           \
typename ::boost::enable_if_c< !__VA_ARGS__::value >::type

#define BOOST_TYPE_DISABLE_IF_C( ... )                                         \
typename ::boost::enable_if_c< !__VA_ARGS__ >::type

#define BOOST_ENABLE_IF_C( ... )                                               \
BOOST_ENABLE_IF_DEFINITION_C( __VA_ARGS__ )                                    \
= ::boost::enable_if_detail::enabler_type_enabler

#define BOOST_ENABLE_IF_DEFINITION_C( ... )                                    \
class BoostDetailEnableIfDependentType = void,                                 \
typename ::boost::enable_if_detail::enable_if_c_impl                           \
< BoostDetailEnableIfDependentType                                             \
, ( __VA_ARGS__ )                                                              \
>::type

#define BOOST_DISABLE_IF_C( ... )                                              \
BOOST_DISABLE_IF_DEFINITION_C( __VA_ARGS__ )                                   \
= ::boost::enable_if_detail::enabler_type_enabler

#define BOOST_DISABLE_IF_DEFINITION_C( ... )                                   \
class BoostDetailDisableIfDependentType = void,                                \
typename ::boost::enable_if_detail::disable_if_c_impl                          \
< BoostDetailDisableIfDependentType                                            \
, ( __VA_ARGS__ )                                                              \
>::type

#define BOOST_ENABLE_IF( ... )                                                 \
class BoostDetailEnableIfDependentType = void,                                 \
typename ::boost::enable_if_detail::enable_if_impl                             \
< BoostDetailEnableIfDependentType                                             \
, __VA_ARGS__                                                                  \
>::type = ::boost::enable_if_detail::enabler_type_enabler

#define BOOST_DISABLE_IF( ... )                                                \
class BoostDetailDisableIfDependentType = void,                                \
typename ::boost::enable_if_detail::disable_if_impl                            \
< BoostDetailDisableIfDependentType                                            \
, __VA_ARGS__                                                                  \
>::type = ::boost::enable_if_detail::enabler_type_enabler

#define BOOST_DISABLE() BOOST_DISABLE_IF_C( true )

#define BOOST_DISABLED_FUNCTION( name ) template< BOOST_DISABLE() > void name();

#define BOOST_LAZY( ... ) BOOST_LAZY_ENABLE_IF_C( true, __VA_ARGS__ )

#define BOOST_ENABLE_IF_EXPR( ... )                                            \
BOOST_PP_IIF( BOOST_VMD_IS_BEGIN_PARENS( __VA_ARGS__ )                         \
            , BOOST_ENABLE_IF_EXPR_IMPL_WITH_PAREN                             \
            , BOOST_ENABLE_IF_EXPR_IMPL_NO_PAREN                               \
            )( __VA_ARGS__ )

#define BOOST_ENABLE_IF_EXPR_IMPL_NO_PAREN( ... )                              \
typename ::boost::enable_if_detail::always_enabler_type                        \
< decltype( __VA_ARGS__ ) >::type                                              \
= ::boost::enable_if_detail::enabler_type_enabler

#define BOOST_ENABLE_IF_EXPR_IMPL_WITH_PAREN( ... )                            \
typename ::boost::enable_if_detail::always_enabler_type                        \
< void BOOST_PP_SEQ_FOR_EACH( BOOST_ENABLE_IF_EXPR_SEQ_MACRO, ~                \
                            , BOOST_PP_VARIADIC_SEQ_TO_SEQ( __VA_ARGS__ )      \
                            )                                                  \
>::type = ::boost::enable_if_detail::enabler_type_enabler

#define BOOST_ENABLE_IF_EXPR_SEQ_MACRO( r, data, elem ) , decltype elem

#define BOOST_LAZY_ENABLE_IF_EXPR( expressions, ... )                          \
BOOST_PP_IIF( BOOST_VMD_IS_BEGIN_PARENS( expressions )                         \
            , BOOST_LAZY_ENABLE_IF_EXPR_IMPL_WITH_PAREN                        \
            , BOOST_LAZY_ENABLE_IF_EXPR_IMPL_NO_PAREN                          \
            )( expressions, __VA_ARGS__ )

#define BOOST_LAZY_ENABLE_IF_EXPR_IMPL_NO_PAREN( expression, ... )             \
typename ::boost::enable_if_detail::always_enabler_type                        \
< decltype( expression ) >::type                                               \
= ::boost::enable_if_detail::enabler_type_enabler                              \
BOOST_PP_SEQ_FOR_EACH                                                          \
( BOOST_LAZY_ENABLE_IF_EXPR_DETAIL_MACRO                                       \
, ::boost::enable_if_detail::always_true< decltype( expression ) >::value      \
, BOOST_PP_VARIADIC_TO_SEQ( __VA_ARGS__ )                                      \
)

#define BOOST_LAZY_ENABLE_IF_EXPR_IMPL_WITH_PAREN( expressions, ... )          \
typename ::boost::enable_if_detail::always_enabler_type                        \
< void BOOST_PP_SEQ_FOR_EACH( BOOST_ENABLE_IF_EXPR_SEQ_MACRO, ~                \
                            , BOOST_PP_VARIADIC_SEQ_TO_SEQ( expressions )      \
                            )                                                  \
>::type = ::boost::enable_if_detail::enabler_type_enabler                      \
BOOST_PP_SEQ_FOR_EACH                                                          \
( BOOST_LAZY_ENABLE_IF_EXPR_DETAIL_MACRO                                       \
, ( ::boost::enable_if_detail::always_true                                     \
    < void BOOST_PP_SEQ_FOR_EACH( BOOST_ENABLE_IF_EXPR_SEQ_MACRO, ~            \
                                , BOOST_PP_VARIADIC_SEQ_TO_SEQ( expressions )  \
                                )                                              \
    >::value                                                                   \
  )                                                                            \
, BOOST_PP_VARIADIC_TO_SEQ( __VA_ARGS__ )                                      \
)

#define BOOST_LAZY_ENABLE_IF_EXPR_DETAIL_MACRO( r, condition, lazy_init )      \
, class BOOST_PP_TUPLE_ELEM( 0, lazy_init )                                    \
= typename ::boost::enable_if_c                                                \
< condition                                                                    \
, BOOST_PP_TUPLE_ENUM( BOOST_DETAIL_TUPLE_POP_FRONT( lazy_init ) )             \
>::type

#define BOOST_LAZY_ENABLE_IF_C_DETAIL_MACRO( r, condition, lazy_init )         \
, class BOOST_PP_TUPLE_ELEM( 0, lazy_init )                                    \
= typename ::boost::enable_if_detail::lazy_enable_if_c_impl                    \
< BoostDetailEnableIfDependentType                                             \
, condition                                                                    \
, BOOST_PP_TUPLE_ENUM( BOOST_DETAIL_TUPLE_POP_FRONT( lazy_init ) )             \
>::type

#define BOOST_LAZY_ENABLE_IF_C( condition, ... )                               \
class BoostDetailEnableIfDependentType = void,                                 \
typename ::boost::enable_if_detail::enable_if_c_impl                           \
< BoostDetailEnableIfDependentType                                             \
, ( condition )                                                                \
>::type = ::boost::enable_if_detail::enabler_type_enabler                      \
BOOST_PP_SEQ_FOR_EACH                                                          \
( BOOST_LAZY_ENABLE_IF_C_DETAIL_MACRO, ( condition )                           \
, BOOST_PP_VARIADIC_TO_SEQ( __VA_ARGS__ )                                      \
)

#define BOOST_LAZY_ENABLE_IF_DETAIL_MACRO( r, condition, lazy_init )           \
, class BOOST_PP_TUPLE_ELEM( 0, lazy_init )                                    \
= typename ::boost::enable_if_detail::lazy_enable_if_impl                      \
< BoostDetailEnableIfDependentType                                             \
, BOOST_DETAIL_REMOVE_PARENTHESES_IF_WRAPPED( condition )                      \
, BOOST_PP_TUPLE_ENUM( BOOST_DETAIL_TUPLE_POP_FRONT( lazy_init ) )             \
>::type

#define BOOST_LAZY_ENABLE_IF( meta_value_in_parentheses, ... )                 \
class BoostDetailEnableIfDependentType = void,                                 \
typename ::boost::enable_if_detail::enable_if_impl                             \
< BoostDetailEnableIfDependentType                                             \
, BOOST_DETAIL_REMOVE_PARENTHESES_IF_WRAPPED( meta_value_in_parentheses )      \
>::type = ::boost::enable_if_detail::enabler_type_enabler                      \
BOOST_PP_SEQ_FOR_EACH                                                          \
( BOOST_LAZY_ENABLE_IF_DETAIL_MACRO, meta_value_in_parentheses                 \
, BOOST_PP_VARIADIC_TO_SEQ( __VA_ARGS__ )                                      \
)

#define BOOST_LAZY_DISABLE_IF_C_DETAIL_MACRO( r, condition, lazy_init )        \
, class BOOST_PP_TUPLE_ELEM( 0, lazy_init )                                    \
= typename ::boost::enable_if_detail::lazy_disable_if_c_impl                   \
< BoostDetailEnableIfDependentType                                             \
, condition                                                                    \
, BOOST_PP_TUPLE_ENUM( BOOST_DETAIL_TUPLE_POP_FRONT( lazy_init ) )             \
>::type

#define BOOST_LAZY_DISABLE_IF_C( condition, ... )                              \
class BoostDetailEnableIfDependentType = void,                                 \
typename ::boost::enable_if_detail::disable_if_c_impl                          \
< BoostDetailEnableIfDependentType                                             \
, ( condition )                                                                \
>::type = ::boost::enable_if_detail::enabler_type_enabler                      \
BOOST_PP_SEQ_FOR_EACH                                                          \
( BOOST_LAZY_DISABLE_IF_C_DETAIL_MACRO, ( condition )                          \
, BOOST_PP_VARIADIC_TO_SEQ( __VA_ARGS__ )                                      \
)

#define BOOST_LAZY_DISABLE_IF_DETAIL_MACRO( r, condition, lazy_init )          \
, class BOOST_PP_TUPLE_ELEM( 0, lazy_init )                                    \
= typename ::boost::enable_if_detail::lazy_disable_if_impl                     \
< BoostDetailEnableIfDependentType                                             \
, BOOST_DETAIL_REMOVE_PARENTHESES_IF_WRAPPED( condition )                      \
, BOOST_PP_TUPLE_ENUM( BOOST_DETAIL_TUPLE_POP_FRONT( lazy_init ) )             \
>::type

#define BOOST_LAZY_DISABLE_IF( meta_value_in_parentheses, ... )                \
class BoostDetailEnableIfDependentType = void,                                 \
typename ::boost::enable_if_detail::disable_if_impl                            \
< BoostDetailEnableIfDependentType                                             \
, BOOST_DETAIL_REMOVE_PARENTHESES_IF_WRAPPED( meta_value_in_parentheses )      \
>::type = ::boost::enable_if_detail::enabler_type_enabler                      \
BOOST_PP_SEQ_FOR_EACH                                                          \
( BOOST_LAZY_DISABLE_IF_DETAIL_MACRO, meta_value_in_parentheses                \
, BOOST_PP_VARIADIC_TO_SEQ( __VA_ARGS__ )                                      \
)

// Each expression must appear in parentheses or there should be exactly one
// expression without parentheses
#define BOOST_TYPE_ENABLE_IF_EXPR( ... )                                       \
BOOST_PP_IIF( BOOST_VMD_IS_BEGIN_PARENS( __VA_ARGS__ )                         \
            , BOOST_TYPE_ENABLE_IF_EXPR_IMPL_WITH_PAREN                        \
            , BOOST_TYPE_ENABLE_IF_EXPR_IMPL_NO_PAREN                          \
            )( __VA_ARGS__ )

#define BOOST_TYPE_ENABLE_IF_EXPR_IMPL_WITH_PAREN( ... )                       \
typename ::boost::enable_if_detail::always_void                                \
< void BOOST_PP_SEQ_FOR_EACH( BOOST_ENABLE_IF_EXPR_SEQ_MACRO, ~                \
                            , BOOST_PP_VARIADIC_SEQ_TO_SEQ( __VA_ARGS__ )      \
                            )                                                  \
>::type

#define BOOST_TYPE_ENABLE_IF_EXPR_IMPL_NO_PAREN( ... )                         \
typename ::boost::enable_if_detail::always_void< decltype( __VA_ARGS__ ) >::type

#define BOOST_DETAIL_VARIADIC_IDENTITY( ... ) __VA_ARGS__

#define BOOST_DETAIL_REMOVE_PARENTHESES_IF_WRAPPED( ... )                      \
BOOST_PP_IIF( BOOST_VMD_IS_BEGIN_PARENS( __VA_ARGS__ )                         \
            , BOOST_PP_TUPLE_ENUM                                              \
            , BOOST_DETAIL_VARIADIC_IDENTITY                                   \
            )( __VA_ARGS__ )

#define BOOST_DETAIL_TUPLE_POP_FRONT( tuple )                                  \
BOOST_PP_ARRAY_DATA                                                            \
( BOOST_PP_ARRAY_POP_FRONT( BOOST_PP_TUPLE_TO_ARRAY( tuple ) ) )

#endif

#endif // BOOST_ENABLE_IF_MACROS_HPP
