/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENT_HPP
#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENT_HPP

#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/rescan.hpp>
#include <boost/generic/detail/variadic_empty.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/identity.hpp>

// BOOST_GENERIC_DETAIL_EQ_DEFAULT_OR_EMPTY takes:
//   ()
// -or-
//   (default_)
// if (), it yields nothing
// else, it yields = default_
#define BOOST_GENERIC_DETAIL_EQ_DEFAULT_OR_EMPTY( def_or_empty_in_paren )      \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_IS_WRAPPED_EMPTY( def_or_empty_in_paren )   \
            , BOOST_PP_EMPTY                                                   \
            , BOOST_GENERIC_DETAIL_EQ_DEFAULT                                  \
            ) def_or_empty_in_paren

#define BOOST_GENERIC_DETAIL_EQ_DEFAULT( ... ) = __VA_ARGS__

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTaxiom( i, d, arg )         \
axiom BOOST_GENERIC_DETAIL_REMOVE_PAREN( arg )

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTrequires( i, d, arg )      \
requires BOOST_GENERIC_DETAIL_REMOVE_PAREN( arg )

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTtypename( i, d, name       \
                                                            , default_         \
                                                            )                  \
typename name BOOST_GENERIC_DETAIL_EQ_DEFAULT_OR_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTconstrained_typename( i, d \
                                                                   , constraint\
                                                                   , name      \
                                                                   , default_  \
                                                                   )           \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( constraint )                                \
name BOOST_GENERIC_DETAIL_EQ_DEFAULT_OR_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTmember_typename( i, d      \
                                                                   , this_type \
                                                                   , name      \
                                                                   , default_  \
                                                                   )           \
typename BOOST_GENERIC_DETAIL_REMOVE_PAREN                                     \
( this_type )::name BOOST_GENERIC_DETAIL_EQ_DEFAULT_OR_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTconstrained_member_typename(\
                                                                     i, d      \
                                                                   , constraint\
                                                                   , this_type \
                                                                   , name      \
                                                                   , default_  \
                                                                   )           \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( constraint )                                \
BOOST_GENERIC_DETAIL_REMOVE_PAREN                                              \
( this_type )::name BOOST_GENERIC_DETAIL_EQ_DEFAULT_OR_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTfunction( i, d, return_type\
                                                            , name, param_dets \
                                                            , default_         \
                                                            )                  \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( return_type )                               \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_NAME_AND_PARAMS( param_dets, name )    \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_POST_PARAM_LIST_PART( param_dets )     \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( default_ )

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTmember_function(           \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , name       \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( return_type )                               \
BOOST_GENERIC_DETAIL_REMOVE_PAREN                                              \
( this_type )::BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_NAME_AND_PARAMS         \
( param_dets, name )                                                           \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_POST_PARAM_LIST_PART( param_dets )     \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( default_ )

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTstatic_member_function(    \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , name       \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
static                                                                         \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTmember_function                    \
( i, d, return_type, this_type, name, param_dets, default_ )

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENT_BASIC_OPERATOR(           \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , operator_  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTfunction                           \
( i, d, return_type, operator operator_, param_dets, default_ )

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTprefix_unary_operator      \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENT_BASIC_OPERATOR

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTpostfix_unary_operator     \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENT_BASIC_OPERATOR

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTbinary_operator            \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENT_BASIC_OPERATOR

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTcall_operator( i, d        \
                                                                 , return_type \
                                                                 , param_dets  \
                                                                 , default_    \
                                                                 )             \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENT_BASIC_OPERATOR                    \
( i, d, return_type, (), param_dets, default_ )

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTcomma_operator( i, d       \
                                                                  , return_type\
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( return_type ) operator ,                    \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) )               \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_POST_PARAM_LIST_PART( param_dets )     \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( default_ )

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTarrow_operator( i, d       \
                                                                  , return_type\
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENT_BASIC_OPERATOR                    \
( i, d, return_type, ->, param_dets, default_ )

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENT_MEMBER_OPERATOR(          \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , operator_  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTmember_function                    \
( i, d, return_type, this_type, operator operator_, param_dets, default_ )

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTassign_operator( i, d      \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENT_MEMBER_OPERATOR                   \
( i, d, return_type, this_type, =, param_dets, default_ )

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTallocation_operator        \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENT_MEMBER_OPERATOR

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTdeallocation_operator      \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENT_MEMBER_OPERATOR

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTconstructor( i, d          \
                                                               , this_type     \
                                                               , param_dets    \
                                                               , default_      \
                                                               )               \
BOOST_GENERIC_DETAIL_REMOVE_PAREN                                              \
( this_type )::BOOST_GENERIC_DETAIL_REMOVE_PAREN                               \
( this_type )( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) )  \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_POST_PARAM_LIST_PART( param_dets )     \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( default_ )

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTexplicit_constructor(      \
                                                                     i, d      \
                                                                   , this_type \
                                                                   , param_dets\
                                                                   , default_  \
                                                                   )           \
explicit                                                                       \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTconstructor                        \
( i, d, this_type, param_dets, default_ )

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTdestructor( i, d, this_type\
                                                              , default_       \
                                                              )                \
BOOST_GENERIC_DETAIL_REMOVE_PAREN                                              \
( this_type )::~BOOST_GENERIC_DETAIL_REMOVE_PAREN( this_type )()               \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( default_ )

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTconversion( i, d           \
                                                              , target_type    \
                                                              , param_dets     \
                                                              , default_       \
                                                              )                \
operator BOOST_GENERIC_DETAIL_REMOVE_PAREN                                     \
( target_type )( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) )\
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_POST_PARAM_LIST_PART( param_dets )     \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( default_ )

#define BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTexplicit_conversion(       \
                                                                    i, d       \
                                                                  , target_type\
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
explicit                                                                       \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTconversion                         \
( i, d, target_type, param_dets, default_ )

#endif // BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENT_HPP
