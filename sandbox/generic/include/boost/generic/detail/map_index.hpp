/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_MAP_INDEX_HPP
#define BOOST_GENERIC_DETAIL_MAP_INDEX_HPP

#include <boost/generic/limits.hpp>

namespace boost_generic_detail { namespace {

// ToDo: Use something other than static_assert when it's not available

template< unsigned MapIndex = BOOST_GENERIC_CONCEPT_MAX_CONCEPT_MAPS >
struct map_index : map_index< MapIndex - 1 >
{
  static_assert( MapIndex != BOOST_GENERIC_CONCEPT_MAX_CONCEPT_MAPS + 1
               , "Too many concept maps for type"
               );
  static unsigned const value_c = MapIndex;
  static unsigned value() { return value_c; }
};

template<>
struct map_index< 0 >
{
  static unsigned const value_c = 0;
  static unsigned value() { return value_c; }
};

} }

#endif // BOOST_GENERIC_DETAIL_MAP_INDEX_HPP
