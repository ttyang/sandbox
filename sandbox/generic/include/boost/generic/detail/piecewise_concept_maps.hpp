/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_PIECEWISE_CONCEPT_MAPS_HPP
#define BOOST_GENERIC_DETAIL_PIECEWISE_CONCEPT_MAPS_HPP

#include <boost/generic/detail/assert_at_global_scope.hpp>
#include <boost/generic/detail/map_index.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/params_for_each.hpp>
#include <boost/generic/detail/type_stack.hpp>
#include <boost/generic/detail/tag_type.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost_generic_detail { namespace {

template< class ThisConcept = void, class ThisConceptMap = void
        , class OtherConceptMaps = void
        >
struct piecewise_concept_maps_t
{
  typedef ThisConcept    this_concept;
  typedef ThisConceptMap this_concept_map;
  typedef typename OtherConceptMaps::next_index_t num_concept_maps_t;
  static num_concept_maps_t num_concept_maps();
  typedef map_index< num_concept_maps_t::value_c + 1 > next_index_t;
  typedef typename OtherConceptMaps::concept_maps old_concept_maps;
  // ToDo: Check for conclicts
  // static_assert when unresolved conflict with information that says the file
  // and line number of the conflicting declarations (file and line number in
  // the static_assert requires c++0x user-defined literals
  typedef typename push< old_concept_maps
                       , boost::mpl::pair< this_concept, this_concept_map >
                       >::type
          concept_maps;
  typedef tag_type< concept_maps > tag_t;
  static next_index_t next_index();
  static tag_t tag() { return tag_t(); }
  template< class ConceptType >
  decltype( OtherConceptMaps::concept_map_to_concept( ConceptType() ) )
  concept_map_to_concept( ConceptType );
  ThisConceptMap concept_map_to_concept( ThisConcept );
};

template< class >
struct no_nested_type {};

template<>
struct piecewise_concept_maps_t<>
{
  static map_index< 0 > num_concept_maps();
  typedef map_index< 1 > next_index_t;
  static next_index_t next_index();
  typedef type_stack<> concept_maps;
  typedef tag_type< concept_maps > tag_t;
  static tag_t tag() { return tag_t(); }
  template< class ConceptType >
  typename no_nested_type< ConceptType >::type
  concept_map_to_concept( ConceptType );
};

piecewise_concept_maps_t<> boost_generic_detail_concept_maps_of( ... );

template< class Concept, class Types
        , class ConceptMap, class CallerConceptMap
        >
struct piecewise_concept_maps_impl_impl
{
  typedef piecewise_concept_maps_t
          < Concept
          , ConceptMap
          , decltype
            ( boost_generic_detail_concept_maps_of
              ( Types()
              , map_index<>()
              , CallerConceptMap()
              )
            )
          > type;

  static type construct();
};

template< class Concept, class Types
        , class ConceptMap, class CallerConceptMap
        >
struct piecewise_concept_maps_impl
{
  static_assert
  ( sizeof( Concept ) != sizeof( Concept )
  , "Error in Boost.Generic, please contact the library maintainer."
  );
};

template< class Concept, class... T
        , class ConceptMap, class CallerConceptMap
        >
struct piecewise_concept_maps_impl
       < Concept, type_stack< T... >
       , ConceptMap, CallerConceptMap
       >
  : boost::mpl::if_
    < typename Concept::template impl< T... >
      ::template is_valid_concept_map< ConceptMap >
    , piecewise_concept_maps_impl_impl
      < Concept, type_stack< T... >, ConceptMap, CallerConceptMap >
    , boost::mpl::empty_base
    >::type {};

template< class Concept, class Types, class ConceptMap >
struct piecewise_concept_maps_impl
       < Concept, Types, ConceptMap, ConceptMap > {};

template< class Concept, class Types, class ConceptMap
        , class CallerConceptMap, class Condition
        >
struct piecewise_concept_maps_conditional_impl
  : boost::mpl::if_
    < Condition
    , piecewise_concept_maps_impl
      < Concept, Types, ConceptMap, CallerConceptMap >
    , boost::mpl::empty_base
    >::type {};

template< class Concept, class Types, class ConceptMap
        , class Condition
        >
struct piecewise_concept_maps_conditional_impl
       < Concept, Types, ConceptMap, ConceptMap, Condition > {};

} }

#define BOOST_GENERIC_DETAIL_REGISTER_CONCEPT_MAP_TMP( concept_in_paren_       \
                                                 , template_params_in_paren_   \
                                                 , types_in_paren_             \
                                                 , impl_name_in_paren_         \
                                                 )                             \
BOOST_GENERIC_DETAIL_ASSERT_AT_GLOBAL_SCOPE                                    \
( "Concept maps must be defined at global scope" )                             \
namespace boost_generic_detail { namespace {                                   \
template< BOOST_GENERIC_DETAIL_REMOVE_PAREN( template_params_in_paren_ )       \
        , class BoostGenericDetailCallerConceptMap = int                       \
        >                                                                      \
BOOST_GENERIC_DETAIL_PIECEWISE_CONCEPT_MAPS_TYPE( concept_in_paren_            \
                                                , types_in_paren_              \
                                                , impl_name_in_paren_          \
                                                )                              \
boost_generic_detail_concept_maps_of                                           \
( type_stack< BOOST_GENERIC_DETAIL_REMOVE_PAREN( types_in_paren_ ) >           \
, decltype                                                                     \
  ( BOOST_GENERIC_DETAIL_PIECEWISE_CONCEPT_MAPS( concept_in_paren_             \
                                               , types_in_paren_               \
                                               , impl_name_in_paren_           \
                                               )                               \
    .next_index()                                                              \
  ) const&                                                                     \
, BoostGenericDetailCallerConceptMap = int()                                   \
);                                                                             \
} }

#define BOOST_GENERIC_DETAIL_REGISTER_CONCEPT_MAP_AUTO( concept_in_paren_      \
                                                 , template_params_in_paren_   \
                                                 , types_in_paren_             \
                                                 , condition_in_parem_         \
                                                 , impl_name_in_paren_         \
                                                 )                             \
BOOST_GENERIC_DETAIL_ASSERT_AT_GLOBAL_SCOPE                                    \
( "Concept maps must be defined at global scope" )                             \
namespace boost_generic_detail { namespace {                                   \
template< BOOST_GENERIC_DETAIL_REMOVE_PAREN( template_params_in_paren_ )       \
        , class BoostGenericDetailCallerConceptMap = int                       \
        >                                                                      \
BOOST_GENERIC_DETAIL_PIECEWISE_CONCEPT_MAPS_AUTO_TYPE( concept_in_paren_       \
                                                , types_in_paren_              \
                                                , condition_in_parem_          \
                                                , impl_name_in_paren_          \
                                                )                              \
boost_generic_detail_concept_maps_of                                           \
( type_stack< BOOST_GENERIC_DETAIL_REMOVE_PAREN( types_in_paren_ ) >           \
, decltype                                                                     \
  ( BOOST_GENERIC_DETAIL_PIECEWISE_CONCEPT_MAPS_AUTO( concept_in_paren_        \
                                                    , types_in_paren_          \
                                                    , condition_in_parem_      \
                                                    , impl_name_in_paren_      \
                                                    )                          \
    .next_index()                                                              \
  ) const&                                                                     \
, BoostGenericDetailCallerConceptMap = int()                                   \
);                                                                             \
} }

#define BOOST_GENERIC_DETAIL_REGISTER_CONCEPT_MAP( concept_in_paren_           \
                                                 , types_in_paren_             \
                                                 , impl_name_in_paren_         \
                                                 )                             \
BOOST_GENERIC_DETAIL_ASSERT_AT_GLOBAL_SCOPE                                    \
( "Concept maps must be defined at global scope" )                             \
namespace boost_generic_detail { namespace {                                   \
template< class BoostGenericDetailCallerConceptMap = int >                     \
BOOST_GENERIC_DETAIL_PIECEWISE_CONCEPT_MAPS_TYPE( concept_in_paren_            \
                                                , types_in_paren_              \
                                                , impl_name_in_paren_          \
                                                )                              \
boost_generic_detail_concept_maps_of                                           \
( type_stack< BOOST_GENERIC_DETAIL_REMOVE_PAREN( types_in_paren_ ) >           \
, decltype                                                                     \
  ( BOOST_GENERIC_DETAIL_PIECEWISE_CONCEPT_MAPS( concept_in_paren_             \
                                               , types_in_paren_               \
                                               , impl_name_in_paren_           \
                                               )                               \
    .next_index()                                                              \
  ) const&                                                                     \
, BoostGenericDetailCallerConceptMap = int()                                   \
);                                                                             \
} }

#define BOOST_GENERIC_DETAIL_PIECEWISE_CONCEPT_MAPS( concept_in_paren_         \
                                                   , types_in_paren_           \
                                                   , impl_name_in_paren_       \
                                                   )                           \
piecewise_concept_maps_impl                                                    \
< BOOST_GENERIC_DETAIL_REMOVE_PAREN( concept_in_paren_ )                       \
, type_stack< BOOST_GENERIC_DETAIL_REMOVE_PAREN( types_in_paren_ ) >           \
, BOOST_GENERIC_DETAIL_REMOVE_PAREN( impl_name_in_paren_ )                     \
, BoostGenericDetailCallerConceptMap                                           \
>::construct()

#define BOOST_GENERIC_DETAIL_PIECEWISE_CONCEPT_MAPS_AUTO( concept_in_paren_    \
                                                        , types_in_paren_      \
                                                        , condition_in_parem_  \
                                                        , impl_name_in_paren_  \
                                                        )                      \
piecewise_concept_maps_conditional_impl                                        \
< BOOST_GENERIC_DETAIL_REMOVE_PAREN( concept_in_paren_ )                       \
, type_stack< BOOST_GENERIC_DETAIL_REMOVE_PAREN( types_in_paren_ ) >           \
, BOOST_GENERIC_DETAIL_REMOVE_PAREN( impl_name_in_paren_ )                     \
, BoostGenericDetailCallerConceptMap                                           \
, BOOST_GENERIC_DETAIL_REMOVE_PAREN( condition_in_parem_ )                     \
>::construct()

#define BOOST_GENERIC_DETAIL_PIECEWISE_CONCEPT_MAPS_AUTO_TYPE(concept_in_paren_\
                                                        , types_in_paren_      \
                                                        , condition_in_parem_  \
                                                        , impl_name_in_paren_  \
                                                        )                      \
decltype                                                                       \
( BOOST_GENERIC_DETAIL_PIECEWISE_CONCEPT_MAPS_AUTO( concept_in_paren_          \
                                                  , types_in_paren_            \
                                                  , condition_in_parem_        \
                                                  , impl_name_in_paren_        \
                                                  )                            \
)

#define BOOST_GENERIC_DETAIL_PIECEWISE_CONCEPT_MAPS_TYPE( concept_in_paren_    \
                                                        , types_in_paren_      \
                                                        , impl_name_in_paren_  \
                                                        )                      \
decltype( BOOST_GENERIC_DETAIL_PIECEWISE_CONCEPT_MAPS                          \
          ( concept_in_paren_, types_in_paren_, impl_name_in_paren_ )          \
        )

#define BOOST_GENERIC_DETAIL_TAG_OF( ... )                                     \
BOOST_GENERIC_DETAIL_TAG_TYPE_OF( __VA_ARGS__ )()

#define BOOST_GENERIC_DETAIL_TAG_TYPE_OF( ... )                                \
decltype                                                                       \
( boost_generic_detail_concept_maps_of                                         \
  ( ::boost_generic_detail::type_stack< __VA_ARGS__ >()                        \
  , ::boost_generic_detail::map_index<>()                                      \
  ).tag()                                                                      \
)

#define BOOST_GENERIC_DETAIL_NUM_CONCEPT_MAPS( ... )                           \
::boost::mpl::integral_c                                                       \
< unsigned, BOOST_GENERIC_DETAIL_NUM_CONCEPT_MAPS_C( __VA_ARGS__ ) >

#define BOOST_GENERIC_DETAIL_NUM_CONCEPT_MAPS_C( ... )                         \
::boost::mpl::identity                                                         \
< decltype                                                                     \
  ( boost_generic_detail_concept_maps_of                                       \
    ( ::boost_generic_detail::type_stack< __VA_ARGS__ >()                      \
    , ::boost_generic_detail::map_index<>()                                    \
    ).num_concept_maps()                                                       \
  )                                                                            \
>::type::value_c

#define BOOST_GENERIC_DETAIL_NEXT_INDEX( ... )                                 \
::boost::mpl::integral_c                                                       \
< unsigned, BOOST_GENERIC_DETAIL_NEXT_INDEX_C( __VA_ARGS__ ) >

#define BOOST_GENERIC_DETAIL_NEXT_INDEX_TYPE( ... )                            \
decltype                                                                       \
( boost_generic_detail_concept_maps_of                                         \
  ( ::boost_generic_detail::type_stack< __VA_ARGS__ >()                        \
  , ::boost_generic_detail::map_index<>()                                      \
  ).next_index()                                                               \
)

#define BOOST_GENERIC_DETAIL_NEXT_INDEX_C( ... )                               \
::boost::mpl::identity                                                         \
< BOOST_GENERIC_DETAIL_NEXT_INDEX_TYPE( __VA_ARGS__ ) >::type::value_c

#endif // BOOST_GENERIC_DETAIL_PIECEWISE_CONCEPT_MAPS_HPP
