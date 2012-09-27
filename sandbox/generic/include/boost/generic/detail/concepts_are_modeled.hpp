#ifndef BOOST_GENERIC_DETAIL_CONCEPTS_ARE_MODELED_HPP
#define BOOST_GENERIC_DETAIL_CONCEPTS_ARE_MODELED_HPP

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS

#include <boost/generic/detail/type.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace generic { namespace detail {

template< class ConceptMap
        , class... ConceptAndParams
        >
struct concepts_are_modeled
{
  static_assert( sizeof( ConceptMap ) != sizeof( ConceptMap )
               , "Library error. Contact maintainer."
               );
};

template< class ConceptMap
        , class FirstConceptAndParams
        , class... ConceptAndParams
        >
struct concepts_are_modeled
       < ConceptMap, FirstConceptAndParams, ConceptAndParams... >
  : mpl::and_< concepts_are_modeled< ConceptMap, FirstConceptAndParams >
             , concepts_are_modeled< ConceptMap, ConceptAndParams... >
             > {};

template< class ConceptMap
        , class ConceptAndParams
        >
struct concepts_are_modeled< ConceptMap, ConceptAndParams >
  : concept_impl_of< ConceptAndParams >::type::
    template boost_generic_detail_is_valid< ConceptAndParams, ConceptMap > {};

} } }

#endif

#endif // BOOST_GENERIC_DETAIL_CONCEPTS_ARE_MODELED_HPP
