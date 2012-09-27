/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_PARAMS_FOR_EACH_HPP
#define BOOST_GENERIC_DETAIL_PARAMS_FOR_EACH_HPP

#include <boost/generic/detail/num_args.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/params_to_list.hpp>
#include <boost/generic/detail/args_to_sequence.hpp>
#include <boost/generic/detail/tail_arguments.hpp>
#include <boost/generic/detail/variadic_empty.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/list/for_each.hpp>
#include <boost/preprocessor/list/for_each_i.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

#define BOOST_GENERIC_DETAIL_PARAMS_FOR_EACH( macro, data, params )            \
BOOST_PP_LIST_FOR_EACH                                                         \
( macro, data, BOOST_GENERIC_DETAIL_PARAMS_TO_LIST_AFTER_RESCAN( params ) )

#define BOOST_GENERIC_DETAIL_PARAMS_FOR_EACH_1( macro, data, params )          \
BOOST_PP_SEQ_FOR_EACH                                                          \
( macro, data                                                                  \
, BOOST_GENERIC_DETAIL_WRAPPED_ARGS_TO_SEQUENCE( params )                      \
)

#define BOOST_GENERIC_DETAIL_PARAMS_FOR_EACH_I( macro, data, params )          \
BOOST_PP_LIST_FOR_EACH_I( macro, data                                          \
                        , BOOST_GENERIC_DETAIL_PARAMS_TO_LIST( params )        \
                        )

// ToDo: Don't pass 0, deduce the correct value
#define BOOST_GENERIC_DETAIL_PARAMS_ENUM_CALL_MACRO( macro, data, params )     \
macro( 0, data, 0, BOOST_GENERIC_DETAIL_REMOVE_PAREN( params ) )

// ToDo: Don't pass 0, deduce the correct value
#define BOOST_GENERIC_DETAIL_PARAMS_ENUM_SIZE_GREATER_THAN_1(macro,data,params)\
macro( 0, data, 0, BOOST_GENERIC_DETAIL_HEAD_WRAPPED_ARGUMENT( params ) )      \
BOOST_PP_LIST_FOR_EACH_I                                                       \
( BOOST_GENERIC_DETAIL_PARAMS_ENUM_COMMA_CALL_MACRO                            \
, (macro)(data)                                                                \
, BOOST_GENERIC_DETAIL_PARAMS_TO_LIST                                          \
  ( ( BOOST_GENERIC_DETAIL_TAIL_WRAPPED_ARGUMENTS( params ) ) )                \
)

#define BOOST_GENERIC_DETAIL_PARAMS_ENUM_COMMA_CALL_MACRO(s,macro_data,i,param)\
, BOOST_PP_SEQ_ELEM( 0, macro_data )                                           \
  ( s, BOOST_PP_SEQ_ELEM( 1, macro_data ), BOOST_PP_INC( i ), param )

#define BOOST_GENERIC_DETAIL_PARAMS_ENUM( macro, data, params )                \
BOOST_PP_IIF                                                                   \
( BOOST_PP_EQUAL( BOOST_GENERIC_DETAIL_NUM_WRAPPED_ARGS( params ), 1 )         \
, BOOST_GENERIC_DETAIL_PARAMS_ENUM_CALL_MACRO                                  \
, BOOST_GENERIC_DETAIL_PARAMS_ENUM_SIZE_NOT_1                                  \
)( macro, data, params )

#define BOOST_GENERIC_DETAIL_PARAMS_ENUM_SIZE_NOT_1( macro, data, params )     \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_IS_WRAPPED_EMPTY( params )                  \
            , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                              \
            , BOOST_GENERIC_DETAIL_PARAMS_ENUM_SIZE_GREATER_THAN_1             \
            )( macro, data, params )

#endif // BOOST_GENERIC_DETAIL_PARAMS_FOR_EACH_HPP
