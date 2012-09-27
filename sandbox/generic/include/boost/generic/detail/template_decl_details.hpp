/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAILS_TEMPLATE_DECL_DETAILS_HPP
#define BOOST_GENERIC_DETAILS_TEMPLATE_DECL_DETAILS_HPP

#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/is_parenthesized.hpp>
#include <boost/generic/detail/num_args.hpp>
#include <boost/generic/detail/param_list.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/seq_to_seq.hpp>
#include <boost/generic/detail/variadic_cat.hpp>
#include <boost/generic/detail/variadic_identity.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/seq/elem.hpp>

//Result is:
//  (has_param_dets)(param_dets)
#define BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETAILS( ... )                      \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_IS_PARENTHESIZED( __VA_ARGS__ )             \
            , BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETAILS_IMPL_PAREN            \
            , BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETAILS_IMPL_INVALID          \
            )( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETS_HAS_PARAM_DETS( dets )         \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETS_PARAM_DETS( dets )             \
BOOST_PP_SEQ_ELEM( 1, dets )

#define BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETS_IS_VALID( dets )               \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETS_HAS_PARAM_DETS( dets )   \
            , BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETS_IS_VALID_IMPL            \
            , BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                      \
            )( dets )

#define BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETS_MAKE_TEMPLATE( dets )          \
template< BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS                       \
          ( BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETS_PARAM_DETS( dets ) )       \
        >

#define BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETS_IS_VALID_IMPL( dets )          \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID_TEMPLATE_PARAMS               \
( BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETS_PARAM_DETS( dets ) )

#define BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETAILS_IMPL_PAREN( ... )           \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_STARTS_WITH_TEMPLATE                        \
              ( BOOST_GENERIC_DETAIL_REMOVE_PAREN( __VA_ARGS__ ) )             \
            , BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETAILS_IMPL_TEMPLATE         \
            , BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETAILS_IMPL_INVALID          \
            )( BOOST_GENERIC_DETAIL_REMOVE_PAREN( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETAILS_IMPL_INVALID( ... )         \
(0)(no_param_dets)

#define BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETAILS_IMPL_TEMPLATE( ... )        \
BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETAILS_IMPL_TEMPLATE_IMPL                  \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS                                      \
  ( BOOST_GENERIC_DETAIL_EAT_TEMPLATE( __VA_ARGS__ ) )                         \
)

#define BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETAILS_IMPL_TEMPLATE_IMPL( dets )  \
( 1 )( dets )

#define BOOST_GENERIC_DETAIL_STARTS_WITH_TEMPLATE( ... )                       \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( __VA_ARGS__ )         \
            , BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                      \
            , BOOST_GENERIC_DETAIL_STARTS_WITH_TEMPLATE_SINGLE_ARG             \
            )( BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ ) )

// ToDo: First check that it's not starting with parentheses
#define BOOST_GENERIC_DETAIL_STARTS_WITH_TEMPLATE_SINGLE_ARG( arg )            \
BOOST_PP_EQUAL                                                                 \
( BOOST_GENERIC_DETAIL_NUM_ARGS_AFTER_RESCAN                                   \
  ( BOOST_PP_CAT( BOOST_GENERIC_DETAIL_STARTS_WITH_TEMPLATE_IMPL, arg ) )      \
, 2                                                                            \
)

#define BOOST_GENERIC_DETAIL_STARTS_WITH_TEMPLATE_IMPLtemplate ~,~

#define BOOST_GENERIC_DETAIL_EAT_TEMPLATE( ... )                               \
BOOST_GENERIC_DETAIL_VARIADIC_CAT                                              \
( BOOST_GENERIC_DETAIL_EAT_TEMPLATE, __VA_ARGS__)

#define BOOST_GENERIC_DETAIL_EAT_TEMPLATEtemplate

#endif // BOOST_GENERIC_DETAILS_TEMPLATE_DECL_DETAILS_HPP
