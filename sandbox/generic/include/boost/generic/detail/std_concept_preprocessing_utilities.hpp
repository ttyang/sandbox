/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_STD_CONCEPT_PREPROCESSING_UTILITIES_HPP
#define BOOST_GENERIC_DETAIL_STD_CONCEPT_PREPROCESSING_UTILITIES_HPP

#include <boost/generic/detail/nary_cat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#ifdef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS

#define BOOST_GENERIC_PREPROCESSED_HEADER                                      \
<boost/generic/detail/preprocess_concepts_error.hpp>

#define BOOST_GENERIC_CREATE_LINE_DIRECTIVE( line_num ) #line line_num         \
BOOST_PP_STRINGIZE                                                             \
BOOST_PP_EMPTY()                                                               \
( BOOST_GENERIC_DETAIL_NARY_CAT                                                \
  BOOST_PP_EMPTY()                                                             \
  ( BOOST_GENERIC_PREPROCESSED_, ROOT, eric/std_                               \
  , BOOST_GENERIC_PREPROCESSED_HEADER_NAME, pp                                 \
  )                                                                            \
)

#else

#ifndef BOOST_GENERIC_USE_NATIVE_CONCEPTS

#define BOOST_GENERIC_PREPROCESSED_HEADER                                      \
BOOST_GENERIC_DETAIL_NARY_CAT                                                  \
( <boost/generic/std_, BOOST_GENERIC_PREPROCESSED_HEADER_NAME, ei > )

#else

#define BOOST_GENERIC_PREPROCESSED_HEADER                                      \
BOOST_GENERIC_DETAIL_NARY_CAT                                                  \
( <boost/generic/std_, BOOST_GENERIC_PREPROCESSED_HEADER_NAME, ni > )

#endif

#define BOOST_GENERIC_CREATE_LINE_DIRECTIVE( dummy_param )

#endif

#endif // BOOST_GENERIC_DETAIL_STD_CONCEPT_PREPROCESSING_UTILITIES_HPP
