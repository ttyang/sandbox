#ifndef BOOST_GENERIC_DETAIL_COMPLETED_CONCEPT_MAP_BASES_HPP
#define BOOST_GENERIC_DETAIL_COMPLETED_CONCEPT_MAP_BASES_HPP

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS

#include <boost/generic/detail/concept_impl_of.hpp>

namespace boost { namespace generic { namespace detail {

template< class ConceptMap, class... ConceptAndParams >
struct completed_concept_map_bases
  : virtual concept_impl_of< ConceptAndParams >::type::template
            boost_generic_detail_completed_concept_map_from_concept
            < ConceptMap, ConceptAndParams >::type... {};
//
//template< class ConceptMap, class ConceptAndParams >
//struct completed_concept_map_bases< ConceptMap, ConceptAndParams >
//  : virtual concept_impl_of< ConceptAndParams >::type::template
//            boost_generic_detail_completed_concept_map_from_concept
//            < ConceptMap, ConceptAndParams >::type {};
//
//template< class ConceptMap, class ConceptAndParams >
//struct completed_concept_map_bases< ConceptMap, ConceptAndParams >
//  : virtual concept_impl_of< ConceptAndParams >::type::template
//            boost_generic_detail_completed_concept_map_from_concept
//            < ConceptMap, ConceptAndParams >::type {};

} } }

#endif

#endif // BOOST_GENERIC_DETAIL_COMPLETED_CONCEPT_MAP_BASES_HPP
