/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETAILS_HPP
#define BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETAILS_HPP

#include <boost/generic/detail/is_parenthesized.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/seq_size.hpp>
#include <boost/generic/detail/seq_to_seq.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/comparison/not_equal.hpp>
#include <boost/preprocessor/logical/not.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/seq.hpp>

// Input is a concept name and parameters of the form:
// ( concept_name )( parameters, ... )
#define BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS( data )                      \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( data )                            \
, BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_IMPL_PAREN                         \
, BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_IMPL_NOT_PAREN                     \
)( data )

// This is called internally once it's determined that the argument starts
// parenthesized. Here, we check to make sure that "data" is in the form of a 2
// element variadic sequence. If it is not, we abort.
#define BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_IMPL_PAREN( data )           \
BOOST_PP_IIF                                                                   \
( BOOST_PP_EQUAL( BOOST_GENERIC_DETAIL_SEQ_SIZE( data ), 2 )                   \
, BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_IMPL_VALID_SIZE                    \
, BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_IMPL_INVALID_SIZE                  \
)( data )

// This is called internally once it's determined that "data" is a 2 element
// variadic sequence. At this point we do no further error checking and assume
// that the data is in the proper format.
#define BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_IMPL_VALID_SIZE( data )      \
BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_IMPL_VALID_SIZE_IMPL                 \
( BOOST_GENERIC_DETAIL_SEQ_TO_SEQ( data ) )

// Yields formatted concept name and param details -- no errors found
// The 0 in the first seq elem here means that we found no errors.
#define BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_IMPL_VALID_SIZE_IMPL( data ) \
( 0 )                                                                          \
( BOOST_PP_SEQ_HEAD( data ) )                                                  \
( BOOST_PP_SEQ_ELEM( 1, data ) )

// Yields error information when data is not a 2 element sequence
// The 1 in the first seq elem here means that data wasn't even a sequence
#define BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_IMPL_NOT_PAREN( data )       \
( 1 )                                                                          \
( ~ )                                                                          \
( ~ )

// Yields error information when data is not a 2 element sequence
// The 2 in the first seq elem here means that the sequence was not size 2
#define BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_IMPL_INVALID_SIZE( data )    \
( 2 )                                                                          \
( ~ )                                                                          \
( ~ )

// Yields 1 is the name and params were in a valid format
#define BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_IS_VALID( dets )             \
BOOST_PP_NOT( BOOST_PP_SEQ_ELEM( 0, dets ) )

#define BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_IS_PARENTHESIZED( dets )     \
BOOST_PP_NOT_EQUAL( BOOST_PP_SEQ_ELEM( 0, dets ), 1 )

// Yields the concept name
#define BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_CONCEPT_NAME( dets )         \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, dets ) )

// Yields the params
#define BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_CONCEPT_PARAMS( dets )       \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 2, dets ) )

#endif // BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETAILS_HPP
