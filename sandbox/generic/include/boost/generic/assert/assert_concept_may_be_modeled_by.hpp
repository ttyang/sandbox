/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_ASSERT_ASSERT_CONCEPT_MAY_BE_MODELED_BY_IMPL_BY_HPP
#define BOOST_GENERIC_ASSERT_ASSERT_CONCEPT_MAY_BE_MODELED_BY_IMPL_BY_HPP

#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/seq_to_seq.hpp>
#include <boost/generic/detail/variadic_stringize.hpp>
#include <boost/preprocessor/seq/elem.hpp>

#define BOOST_GENERIC_ASSERT_CONCEPT_MAY_BE_MODELED_BY( concept_and_params )   \
BOOST_GENERIC_ASSERT_CONCEPT_MAY_BE_MODELED_BY_IMPL                            \
( BOOST_GENERIC_DETAIL_SEQ_TO_SEQ( concept_and_params ) )

// ToDo: Use BOOST_GENERIC_CONCEPT_MAY_BE_MODELED_BY underneath the hood
#define BOOST_GENERIC_ASSERT_CONCEPT_MAY_BE_MODELED_BY_IMPL( seq )             \
static_assert                                                                  \
( BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, seq ) )             \
  ::impl                                                                       \
  < BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, seq ) ) >         \
  ::types_are_valid::value                                                     \
, BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE_AFTER_RESCAN                         \
  ( BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, seq ) )           \
    is unable to be modeled by                                                 \
    { BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, seq ) ) }       \
    due to the following:                                                      \
  )                                                                            \
);                                                                             \
typename BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, seq ) )      \
::impl< BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, seq ) ) >     \
::descriptive_failure::type boost_generic_detail_assert();

#endif // BOOST_GENERIC_ASSERT_ASSERT_CONCEPT_MAY_BE_MODELED_BY_IMPL_BY_HPP
