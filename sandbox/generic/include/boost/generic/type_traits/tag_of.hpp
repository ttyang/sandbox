/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_TYPE_TRAITS_TAG_OF_HPP
#define BOOST_GENERIC_TYPE_TRAITS_TAG_OF_HPP

#include <boost/generic/detail/piecewise_concept_maps.hpp>

// Takes a comma separated list of types, yields a tag object that represents
// all of the concepts that combination of types models
#define BOOST_GENERIC_TAG_OF BOOST_GENERIC_DETAIL_TAG_OF

// Takes a comma separated list of types, yields a tag type that represents all
// of the concepts that combination of types models
#define BOOST_GENERIC_TAG_TYPE_OF BOOST_GENERIC_DETAIL_TAG_TYPE_OF

#endif // BOOST_GENERIC_TYPE_TRAITS_TAG_OF_HPP
