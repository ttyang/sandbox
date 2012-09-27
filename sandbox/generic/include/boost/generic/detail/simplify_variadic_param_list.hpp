/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_SIMPLIFY_VARIADIC_PARAM_LIST_HPP
#define BOOST_GENERIC_DETAIL_SIMPLIFY_VARIADIC_PARAM_LIST_HPP

#include <boost/generic/detail/eat_part_after_paren.hpp>
#include <boost/generic/detail/eat.hpp>
#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/tail_arguments.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/greater.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/array/enum.hpp>
#include <boost/preprocessor/array/remove.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_SIMPLIFY_VARIADIC( ... )       \
BOOST_PP_SEQ_ENUM                                                              \
( BOOST_PP_SEQ_TRANSFORM                                                       \
  ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_SIMPLIFY_VARIADIC_MAC, ~           \
  , BOOST_PP_VARIADIC_TO_SEQ( __VA_ARGS__ )                                    \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_IS_VARIADIC( param )             \
BOOST_PP_SEQ_ELEM( 0, param )

#define BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_DDD_IF_VARIADIC( param )         \
BOOST_PP_EXPR_IIF                                                              \
( BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_IS_VARIADIC( param )                   \
, ...                                                                          \
)

#define BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_KIND_NAME( param )               \
BOOST_GENERIC_DETAIL_REMOVE_PAREN                                              \
( BOOST_GENERIC_DETAIL_EAT_PART_AFTER_PAREN( BOOST_PP_SEQ_ELEM( 1, param ) ) )

#define BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_KIND( param )                    \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_IS_VARIADIC( param )                   \
, BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_KIND_VARIADIC                          \
, BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_KIND_NAME                              \
)( param )

#define BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_KIND_VARIADIC( param )           \
BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_KIND_NAME( param )...

#define BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_NAME( param )                    \
BOOST_PP_EXPAND( BOOST_GENERIC_DETAIL_EAT BOOST_PP_SEQ_ELEM( 1, param ) )

#define BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_PASS_ARG( param )                \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_IS_VARIADIC( param )                   \
, BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_PASS_ARG_VARIADIC                      \
, BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_NAME                                   \
)( param )

#define BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_PASS_ARG_VARIADIC( param )       \
BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_NAME( param )...

// This macro is only called if there are at least 3 commas
#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_SIMPLIFY_VARIADIC_IMPL_MAY(    \
                                                                  param_size   \
                                                                , wrapped_param\
                                                                , name )       \
BOOST_PP_IIF                                                                   \
( BOOST_PP_BITAND                                                              \
  ( BOOST_PP_BITAND                                                            \
    ( BOOST_GENERIC_DETAIL_IS_EMPTY                                            \
      (BOOST_PP_ARRAY_ELEM                                                     \
       (BOOST_PP_DEC(param_size),(param_size,wrapped_param)))                  \
    , BOOST_GENERIC_DETAIL_IS_EMPTY                                            \
      (BOOST_PP_ARRAY_ELEM                                                     \
       (BOOST_PP_DEC(BOOST_PP_DEC(param_size)),(param_size,wrapped_param)))    \
    )                                                                          \
  , BOOST_GENERIC_DETAIL_IS_EMPTY                                              \
    (BOOST_PP_ARRAY_ELEM                                                       \
     (BOOST_PP_DEC                                                             \
      (BOOST_PP_DEC(BOOST_PP_DEC(param_size))),(param_size,wrapped_param)))    \
  )                                                                            \
, BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_SIMPLIFY_VARIADIC_IMPL_YES           \
, BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_SIMPLIFY_VARIADIC_IMPL_NO            \
)( param_size, wrapped_param, name )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_SIMPLIFY_VARIADIC_IMPL_YES(    \
                                                                  param_size   \
                                                                , wrapped_param\
                                                                , name )       \
( 1 )                                                                          \
( ( BOOST_PP_ARRAY_ENUM                                                        \
    ( BOOST_PP_ARRAY_REMOVE                                                    \
      ( BOOST_PP_ARRAY_REMOVE                                                  \
        ( BOOST_PP_ARRAY_REMOVE                                                \
          ( (param_size,wrapped_param), BOOST_PP_DEC( param_size ) )           \
        , BOOST_PP_DEC( BOOST_PP_DEC( param_size ) )                           \
        )                                                                      \
      , BOOST_PP_DEC( BOOST_PP_DEC( BOOST_PP_DEC( param_size ) ) )             \
      )                                                                        \
    )                                                                          \
  )                                                                            \
  name                                                                         \
)

// This is only called when the param is not variadic
#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_SIMPLIFY_VARIADIC_IMPL_NO(     \
                                                                  param_size   \
                                                                , wrapped_param\
                                                                , name )       \
( 0 ) ( wrapped_param name )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_SIMPLIFY_VARIADIC_MAC(s,d,elem)\
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_SIMPLIFY_VARIADIC_IMPL                 \
( BOOST_PP_TUPLE_SIZE                                                          \
  ( BOOST_GENERIC_DETAIL_EAT_PART_AFTER_PAREN( elem ) )                        \
, BOOST_GENERIC_DETAIL_EAT_PART_AFTER_PAREN( elem )                            \
, BOOST_PP_EXPAND( BOOST_GENERIC_DETAIL_EAT elem )                             \
)

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_SIMPLIFY_VARIADIC_IMPL(        \
                                                                  param_size   \
                                                                , wrapped_param\
                                                                , name )       \
BOOST_PP_IIF                                                                   \
( BOOST_PP_GREATER( param_size, 3 )                                            \
, BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_SIMPLIFY_VARIADIC_IMPL_MAY           \
, BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_SIMPLIFY_VARIADIC_IMPL_NO            \
)( param_size, wrapped_param, name )

#endif // BOOST_GENERIC_DETAIL_SIMPLIFY_VARIADIC_PARAM_LIST_HPP
