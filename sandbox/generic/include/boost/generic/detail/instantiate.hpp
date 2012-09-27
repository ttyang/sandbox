#ifndef BOOST_GENERIC_DETAIL_INSTANTIATE_HPP
#define BOOST_GENERIC_DETAIL_INSTANTIATE_HPP

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS

#include <boost/generic/detail/concept_impl_of.hpp>
#include <boost/generic/detail/concept_map_template.hpp>
#include <boost/generic/detail/is_concept.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <utility>

namespace boost { namespace generic { namespace detail {

mpl::true_ boost_generic_detail_instantiate_impl( ... );

template< class... ConceptAndParams >
decltype
( boost_generic_detail_instantiate_impl
  ( std::declval< ConceptAndParams >()... )
)
instantiate();

template< class Dummy, class... ConceptAndParams >
decltype
( boost_generic_detail_instantiate_impl
  ( std::declval< ConceptAndParams >()... )
)
instantiate_with_dummy();

template< class ConceptAndParams >
decltype
( boost_generic_detail_instantiate_impl
  ( std::declval
    < typename mpl::if_c< concept_impl_of< ConceptAndParams >::is_auto
                        , ConceptAndParams
                        , int
                        >
                        ::type
    >()
  )
)
instantiate_if_auto();

template< class ConceptAndParams >
decltype
( boost_generic_detail_instantiate_impl
  ( std::declval
    < typename mpl::if_c<    concept_impl_of< ConceptAndParams >::is_auto
                          || concept_impl_of< ConceptAndParams >::is_specialized
                        , ConceptAndParams
                        , int
                        >
                        ::type
    >()
  )
)
instantiate_if_auto_or_specialized();

template< class... ConceptAndParams >
decltype
( boost_generic_detail_instantiate_impl
  ( std::declval
    < typename boost_generic_concept_map_detail::concept_map_
      < ConceptAndParams >::template instantiate<>::instantiate_
    >()...
  )
)
instantiate_map();

} } }

#endif

#endif // BOOST_GENERIC_DETAIL_INSTANTIATE_HPP
