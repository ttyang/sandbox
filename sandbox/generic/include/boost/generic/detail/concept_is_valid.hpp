#ifndef BOOST_GENERIC_DETAIL_CONCEPT_IS_VALID_HPP
#define BOOST_GENERIC_DETAIL_CONCEPT_IS_VALID_HPP

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS

#include <boost/generic/detail/concept_impl_of.hpp>
#include <boost/generic/detail/concept_map_template.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp>

namespace boost { namespace generic { namespace detail {

template< class ConceptAndParams >
struct concept_is_valid_impl
  : concept_impl_of< ConceptAndParams >::type::
    template boost_generic_detail_is_valid< ConceptAndParams > {};

// ToDo: Create a default here that pulls the proper concept map
template< class ConceptAndParams >
struct concept_is_valid
  : mpl::and_< boost::mpl::bool_
               < ::boost_generic_concept_map_detail::concept_map_
                 < ConceptAndParams >::is_usable
               >
             , concept_is_valid_impl< ConceptAndParams >
             > {};

} } }

#endif

#endif // BOOST_GENERIC_DETAIL_CONCEPT_IS_VALID_HPP
