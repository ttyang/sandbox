/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_TEMPLATE_DECL_HPP
#define BOOST_GENERIC_DETAIL_TEMPLATE_DECL_HPP

#include <boost/generic/detail/param_list.hpp>
#include <boost/generic/detail/eat.hpp>
#include <boost/generic/detail/eat_part_after_paren.hpp>
#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/num_args.hpp>
#include <boost/generic/detail/params_for_each.hpp>
#include <boost/generic/detail/rescan.hpp>
#include <boost/generic/detail/variadic_empty.hpp>
#include <boost/generic/detail/variadic_identity.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <utility> // For declval // ToDo: Remove this include

#define BOOST_GENERIC_AUTO_CONCEPT_MAP_TEMPLATE_PARAMS_MACRO( s, data, elem )  \
BOOST_GENERIC_DETAIL_RESCAN elem

#define BOOST_GENERIC_AUTO_CONCEPT_MAP_TEMPLATE_ARGS_MACRO( s, data, elem )    \
BOOST_GENERIC_DETAIL_EAT elem

#define BOOST_GENERIC_AUTO_CONCEPT_MAP_TEMPLATE_DECLVAL_ARGS_MACRO(s,data,elem)\
::std::declval< BOOST_GENERIC_DETAIL_EAT_PART_AFTER_PAREN( elem ) >()

#define BOOST_GENERIC_AUTO_CONCEPT_MAP_TEMPLATE_PARAMS( params )               \
BOOST_GENERIC_DETAIL_PARAMS_ENUM                                               \
( BOOST_GENERIC_AUTO_CONCEPT_MAP_TEMPLATE_PARAMS_MACRO, ~                      \
, params                                                                       \
)

#define BOOST_GENERIC_AUTO_CONCEPT_MAP_TEMPLATE_ARGS( params )                 \
BOOST_GENERIC_DETAIL_PARAMS_ENUM                                               \
( BOOST_GENERIC_AUTO_CONCEPT_MAP_TEMPLATE_ARGS_MACRO, ~                        \
, params                                                                       \
)

#define BOOST_GENERIC_AUTO_CONCEPT_MAP_TEMPLATE_DECLVAL_ARGS( params )         \
BOOST_GENERIC_DETAIL_PARAMS_ENUM                                               \
( BOOST_GENERIC_AUTO_CONCEPT_MAP_TEMPLATE_DECLVAL_ARGS_MACRO, ~                \
, params                                                                       \
)

#define BOOST_GENERIC_DETAIL_TEMPLATE_DECL( params )                           \
template< class BOOST_GENERIC_DETAIL_HEAD_WRAPPED_ARGUMENT( params )           \
          BOOST_PP_IIF                                                         \
          ( BOOST_PP_EQUAL( BOOST_GENERIC_DETAIL_NUM_WRAPPED_ARGS( params )    \
                          , 1                                                  \
                          )                                                    \
          , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                                \
          , BOOST_GENERIC_DETAIL_TEMPLATE_DECL_IMPL_NOT_FIRST                  \
          )( params )                                                          \
        >

#define BOOST_GENERIC_DETAIL_TEMPLATE_DECL_IMPL_NOT_FIRST( params )            \
BOOST_GENERIC_DETAIL_PARAMS_FOR_EACH                                           \
( BOOST_GENERIC_DETAIL_TEMPLATE_DECL_IMPL_MACRO, ~, params )

#define BOOST_GENERIC_DETAIL_TEMPLATE_DECL_IMPL_MACRO( r, data, elem )         \
, class elem

#endif // BOOST_GENERIC_DETAIL_TEMPLATE_DECL_HPP
