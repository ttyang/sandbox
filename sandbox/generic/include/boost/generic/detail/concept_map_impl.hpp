/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_CONCEPT_MAP_IMPL_HPP
#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_IMPL_HPP

//#include <type_traits>

namespace boost { namespace generic { namespace detail {

template< class ConceptAndParams >
struct concept_map_impl
  : std::conditional< concept_impl_of< ConceptAndParams >::is_auto
                    ,
{
  static bool const is_specialized = false;
  static bool const is_auto = false;

//  struct type
//  {
//    template< class >
//    struct boost_generic_detail_is_valid : std::false_type {};
//  };
};

} } }

#endif // BOOST_GENERIC_DETAIL_CONCEPT_MAP_IMPL_HPP
