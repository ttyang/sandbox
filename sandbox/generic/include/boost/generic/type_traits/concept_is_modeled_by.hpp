/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_TYPE_TRAITS_CONCEPT_IS_MODELED_BY_HPP
#define BOOST_GENERIC_TYPE_TRAITS_CONCEPT_IS_MODELED_BY_HPP

#include <boost/generic/detail/map_index.hpp>
#include <boost/generic/detail/piecewise_concept_maps.hpp>
#include <boost/generic/detail/type_stack.hpp>
#include <boost/generic/detail/remove_paren.hpp>

// Takes a concept and a set of types
#define BOOST_GENERIC_CONCEPT_IS_MODELED_BY( concept_in_paren_, ... )          \
::boost::is_convertible                                                        \
< BOOST_GENERIC_DETAIL_TAG_TYPE_OF( __VA_ARGS__ )*                             \
, BOOST_GENERIC_DETAIL_REMOVE_PAREN( concept_in_paren_ )*                      \
>

// Takes a concept and a set of types, yields a compile-time constant bool
#define BOOST_GENERIC_CONCEPT_IS_MODELED_BY_C( concept_in_paren_, ... )        \
( BOOST_GENERIC_CONCEPT_IS_MODELED_BY( concept_in_paren_, __VA_ARGS__ )::value )

#endif // BOOST_GENERIC_TYPE_TRAITS_CONCEPT_IS_MODELED_BY_HPP
