/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_HPP
#define BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_HPP

#include <boost/generic/detail/typename_details.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/seq/replace.hpp>

// a nested typename requirement is specified as:
//   ( typename name )

// Result form is the same as that of a nonnested typename
// Error macros take an additional argument -- the this_t argument
#define BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS( ... )                              \
BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_IMPL                                        \
( BOOST_GENERIC_DETAIL_TYPENAME_DETS( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_IMPL( typename_dets )               \
BOOST_PP_IIF                                                                        \
( BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_VALID( typename_dets )                      \
, BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_IMPL_VALID_NONEST                         \
, BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_IMPL_INVALID_NONEST                       \
)( typename_dets )

#define BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_IS_VALID                            \
BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_VALID

#define BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_IS_PARTIAL                          \
BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_PARTIAL

#define BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_NAME                                \
BOOST_GENERIC_DETAIL_TYPENAME_DETS_NAME

#define BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_DEFAULT                             \
BOOST_GENERIC_DETAIL_TYPENAME_DETS_DEFAULT

#define BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_HAS_DEFAULT                         \
BOOST_GENERIC_DETAIL_TYPENAME_DETS_HAS_DEFAULT

#define BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_IS_PARTIAL                          \
BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_PARTIAL

#define BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_ERRORS                              \
BOOST_GENERIC_DETAIL_TYPENAME_DETS_ERRORS

#define BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_HAS_ERRORS                          \
BOOST_GENERIC_DETAIL_TYPENAME_DETS_HAS_ERRORS

// ToDo: Properly define BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_IMPL_INVALID_NONEST
// Have it convert the "nonnested typename" errors to "nested typename " errors
#define BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_IMPL_INVALID_NONEST( typename_dets )\
typename_dets

#define BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_IMPL_VALID_NONEST( typename_dets )  \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_TYPENAME_DETS_HAS_DEFAULT( typename_dets )       \
            , BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_IMPL_DEFAULT                  \
            , BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( typename_dets )               \
            )( typename_dets )

// ToDo: Insert error about not allowing defaults
#define BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_IMPL_DEFAULT( typename_dets )       \
BOOST_PP_SEQ_REPLACE( typename_dets, 0, 0 )

// expands to macro( validity_bit, name, empty_or_default_in_paren )
// ToDo: pass error data as well for visitation
#define BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_VISIT( dets, this_t            \
                                                     , valid_macro, inv_macro  \
                                                     )                         \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_IS_VALID( dets )         \
            , BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_VISIT_IMPL_VALID         \
            , BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_VISIT_IMPL_INVALID       \
            )( dets, this_t, valid_macro, inv_macro )

#define BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_VISIT_IMPL_VALID( dets, this_t \
                                                                , valid_macro  \
                                                                , inv_macro    \
                                                                )              \
valid_macro( this_t, BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_NAME( dets ) )

#define BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_VISIT_IMPL_INVALID( dets       \
                                                                  , this_t     \
                                                                  , valid_macro\
                                                                  , inv_macro  \
                                                                  )            \
inv_macro( this_t, BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_ERRORS( dets ) )

#define BOOST_GENERIC_DETAIL_THIS_TYPENAME_ERROR_DEFAULT( dets, this_t )       \
"A nested typename requirement cannot have a default: typename "               \
BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE this_t "::"                            \
BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                        \
( BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_NAME( dets ) ) " = "                 \
BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                        \
( BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_DEFAULT( dets ) ) ";"

#endif // BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_HPP
