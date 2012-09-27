/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENT_HPP
#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENT_HPP

#include <boost/generic/detail/interpreted_requirement.hpp>
#include <boost/generic/detail/is_empty.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>

// BOOST_GENERIC_DETAIL_SEMICOLON_IF_EMPTY takes:
//   ()
// -or-
//   (default_)
// if (), it yields ;
// else, it yields nothing
#define BOOST_GENERIC_DETAIL_SEMICOLON_IF_EMPTY( def_or_empty_in_paren )       \
BOOST_PP_EXPR_IIF                                                              \
( BOOST_GENERIC_DETAIL_IS_WRAPPED_EMPTY( def_or_empty_in_paren ), ; )

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTaxiom                           \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTaxiom

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTrequires( i, d, arg )           \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTrequires( i, d, arg );

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTtypename( i, d, name, default_ )\
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTtypename( i, d, name, default_ );

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTconstrained_typename( i, d      \
                                                                   , constraint\
                                                                   , name      \
                                                                   , default_  \
                                                                   )           \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTconstrained_typename               \
( i, d, constraint, name, default_ );

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTmember_typename( i, d, this_type\
                                                              , name, default_ \
                                                              )                \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTmember_typename                    \
( i, d, this_type, name, default_ );

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTconstrained_member_typename(    \
                                                                     i, d      \
                                                                   , constraint\
                                                                   , this_type \
                                                                   , name      \
                                                                   , default_  \
                                                                   )           \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTconstrained_member_typename        \
( i, d, constraint, this_type, name, default_ );

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTfunction( i, d, return_type     \
                                                       , name, param_dets      \
                                                       , default_              \
                                                       )                       \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTfunction                           \
( i, d, return_type, name, param_dets, default_ )                              \
BOOST_GENERIC_DETAIL_SEMICOLON_IF_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTmember_function( i, d           \
                                                              , return_type    \
                                                              , this_type, name\
                                                              , param_dets     \
                                                              , default_       \
                                                              )                \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTmember_function                    \
( i, d, return_type, this_type, name, param_dets, default_ )                   \
BOOST_GENERIC_DETAIL_SEMICOLON_IF_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTstatic_member_function(         \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , name       \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTstatic_member_function             \
( i, d, return_type, this_type, name, param_dets, default_ )                   \
BOOST_GENERIC_DETAIL_SEMICOLON_IF_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTprefix_unary_operator(          \
                                                                   i, d        \
                                                                 , return_type \
                                                                 , operator_   \
                                                                 , param_dets  \
                                                                 , default_    \
                                                                 )             \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTprefix_unary_operator              \
( i, d, return_type, operator_, param_dets, default_ )                         \
BOOST_GENERIC_DETAIL_SEMICOLON_IF_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTpostfix_unary_operator(         \
                                                                   i, d        \
                                                                 , return_type \
                                                                 , operator_   \
                                                                 , param_dets  \
                                                                 , default_    \
                                                                 )             \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTpostfix_unary_operator             \
( i, d, return_type, operator_, param_dets, default_ )                         \
BOOST_GENERIC_DETAIL_SEMICOLON_IF_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTbinary_operator( i, d           \
                                                              , return_type    \
                                                              , operator_      \
                                                              , param_dets     \
                                                              , default_       \
                                                              )                \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTbinary_operator                    \
( i, d, return_type, operator_, param_dets, default_ )                         \
BOOST_GENERIC_DETAIL_SEMICOLON_IF_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTcall_operator( i, d             \
                                                            , return_type      \
                                                            , param_dets       \
                                                            , default_         \
                                                            )                  \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTcall_operator                      \
( i, d, return_type, param_dets, default_ )                                    \
BOOST_GENERIC_DETAIL_SEMICOLON_IF_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTcomma_operator( i, d            \
                                                             , return_type     \
                                                             , param_dets      \
                                                             , default_        \
                                                             )                 \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTcomma_operator                     \
( i, d, return_type, param_dets, default_ )                                    \
BOOST_GENERIC_DETAIL_SEMICOLON_IF_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTarrow_operator( i, d            \
                                                             , return_type     \
                                                             , param_dets      \
                                                             , default_        \
                                                             )                 \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTarrow_operator                     \
( i, d, return_type, param_dets, default_ )                                    \
BOOST_GENERIC_DETAIL_SEMICOLON_IF_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTassign_operator( i, d           \
                                                              , return_type    \
                                                              , this_type      \
                                                              , param_dets     \
                                                              , default_       \
                                                              )                \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTassign_operator                    \
( i, d, return_type, this_type, param_dets, default_ )                         \
BOOST_GENERIC_DETAIL_SEMICOLON_IF_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTallocation_operator( i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , operator_  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTallocation_operator                \
( i, d, return_type, this_type, operator_, param_dets, default_ )              \
BOOST_GENERIC_DETAIL_SEMICOLON_IF_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTdeallocation_operator(          \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , operator_  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTdeallocation_operator              \
( i, d, return_type, this_type, operator_, param_dets, default_ )              \
BOOST_GENERIC_DETAIL_SEMICOLON_IF_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTconstructor( i, d, this_type    \
                                                          , param_dets         \
                                                          , default_           \
                                                          )                    \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTconstructor                        \
( i, d, this_type, param_dets, default_ )                                      \
BOOST_GENERIC_DETAIL_SEMICOLON_IF_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTexplicit_constructor( i, d      \
                                                                   , this_type \
                                                                   , param_dets\
                                                                   , default_  \
                                                                   )           \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTexplicit_constructor               \
( i, d, this_type, param_dets, default_ )                                      \
BOOST_GENERIC_DETAIL_SEMICOLON_IF_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTdestructor( i, d, this_type     \
                                                         , default_            \
                                                         )                     \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTdestructor                         \
( i, d, this_type, default_ )                                                  \
BOOST_GENERIC_DETAIL_SEMICOLON_IF_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTconversion( i, d, target_type   \
                                                         , param_dets          \
                                                         , default_            \
                                                         )                     \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTconversion                         \
( i, d, target_type, param_dets, default_ )                                    \
BOOST_GENERIC_DETAIL_SEMICOLON_IF_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENTexplicit_conversion( i, d       \
                                                                  , target_type\
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_INTERPRETED_REQUIREMENTexplicit_conversion                \
( i, d, target_type, param_dets, default_ )                                    \
BOOST_GENERIC_DETAIL_SEMICOLON_IF_EMPTY( default_ )

#endif // BOOST_GENERIC_DETAIL_NATIVE_REQUIREMENT_HPP
