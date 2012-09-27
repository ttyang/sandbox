/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_TYPE_TRAITS_CONCEPT_MAY_BE_MODELED_BY_HPP
#define BOOST_GENERIC_TYPE_TRAITS_CONCEPT_MAY_BE_MODELED_BY_HPP

#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/seq_to_seq.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/seq/elem.hpp>

#define BOOST_GENERIC_CONCEPT_MAY_BE_MODELED_BY( concept_and_params )          \
::boost::mpl::bool_                                                            \
< BOOST_GENERIC_CONCEPT_MAY_BE_MODELED_BY_C( concept_and_params ) >

#define BOOST_GENERIC_CONCEPT_MAY_BE_MODELED_BY_C( concept_and_params )        \
BOOST_GENERIC_CONCEPT_MAY_BE_MODELED_BY_IMPL                                   \
( BOOST_GENERIC_DETAIL_SEQ_TO_SEQ( concept_and_params ) )

#define BOOST_GENERIC_CONCEPT_MAY_BE_MODELED_BY_IMPL( seq )                    \
( BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, seq ) )             \
  ::impl                                                                       \
  < BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, seq ) ) >         \
  ::types_are_valid::value                                                     \
)

#endif // BOOST_GENERIC_TYPE_TRAITS_CONCEPT_MAY_BE_MODELED_BY_HPP
