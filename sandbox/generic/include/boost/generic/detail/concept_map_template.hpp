/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_CONCEPT_MAP_TEMPLATE_HPP
#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_TEMPLATE_HPP

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS

#include <boost/generic/detail/concept_impl_of.hpp>
#include <type_traits>

#endif

namespace boost_generic_concept_map_detail {

template< class ConceptAndParams, class Enabler = void >
struct concept_map_
{
  static bool const is_auto_concept_definition
    = ::boost::generic::detail::concept_impl_of< ConceptAndParams >
      ::is_auto,
                    is_usable = is_auto_concept_definition;

  struct boost_generic_concept_map_impl {};

  template< class BoostGenericDetailDummy = int >
  struct instantiate
  {
    static_assert(    sizeof( BoostGenericDetailDummy )
                   != sizeof( BoostGenericDetailDummy )
                 , "No matching concept map."
                 );
    typedef ::std::true_type instantiate_;
  };
};

}

#endif // BOOST_GENERIC_DETAIL_CONCEPT_MAP_TEMPLATE_HPP
