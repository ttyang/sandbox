/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_TAG_TYPE_HPP
#define BOOST_GENERIC_DETAIL_TAG_TYPE_HPP

#include <boost/generic/detail/type_stack.hpp>

namespace boost_generic_detail { namespace {

// Takes a type_stack of concept/concept map pairs
template< class ConceptMapTypes >
struct tag_type;

template< class... ConceptMap >
struct tag_type< type_stack< ConceptMap... > >
  : virtual ConceptMap::first... {};

} }

#endif // BOOST_GENERIC_DETAIL_TAG_TYPE_HPP
