/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_AUTO_CONCEPT_MAP_HPP
#define BOOST_GENERIC_AUTO_CONCEPT_MAP_HPP

#include <boost/generic/detail/assert_at_global_scope.hpp>
#include <boost/generic/detail/auto_concept_map/arg_details.hpp>
#include <boost/generic/detail/params_for_each.hpp>
#include <boost/generic/detail/piecewise_concept_maps.hpp>
#include <boost/generic/detail/template_decl.hpp>
#include <boost/generic/detail/unique_id.hpp>
#include <boost/generic/concept_map.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/control/iif.hpp>

//BOOST_GENERIC_AUTO_CONCEPT_MAP
//( ( (class) T )
//, ( boost::generic::std_concept::DefaultConstructible ), ( T )
//)

/*
BOOST_GENERIC_DETAIL_REGISTER_CONCEPT_MAP_AUTO arguments:
concept_in_paren_      \
                                                 , template_params_in_paren_   \
                                                 , types_in_paren_             \
                                                 , condition_in_parem_         \
                                                 , impl_name_in_paren_         \

*/

// ToDo: Remove
#if 1

// Format is template params, concept map name, concept name, the concept args
// and then the named arguments if any
#define BOOST_GENERIC_AUTO_CONCEPT_MAP( template_decl_, ... )                  \
BOOST_GENERIC_DETAIL_ASSERT_AT_GLOBAL_SCOPE                                    \
( "Concept maps must be defined at global scope" )                             \
BOOST_GENERIC_AUTO_CONCEPT_MAP_IMPL                                            \
( BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS( template_decl_            \
                                                   , __VA_ARGS__               \
                                                   )                           \
)

#define BOOST_GENERIC_AUTO_CONCEPT_MAP_IMPL( arg_dets )                        \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETS_HAS_ERRORS( arg_dets )        \
, BOOST_GENERIC_AUTO_CONCEPT_MAP_IMPL_ERRORS                                   \
, BOOST_GENERIC_AUTO_CONCEPT_MAP_IMPL_NO_ERRORS                                \
)( BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETS_TPL_DETS( arg_dets )         \
 , BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETS_CONCEPT_NAME_PARAM_DETS      \
   ( arg_dets )                                                                \
 , BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETS_ERRORS( arg_dets )           \
 , BOOST_GENERIC_DETAIL_UNIQUE_ID_()                                           \
 )

#define BOOST_GENERIC_AUTO_CONCEPT_MAP_IMPL_ERRORS( tpl_dets, np_dets, errors  \
                                                  , id                         \
                                                  )                            \
BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_EMIT_ERRORS_( errors )

#define BOOST_GENERIC_AUTO_CONCEPT_MAP_IMPL_NO_ERRORS( tpl_dets, np_dets       \
                                                     , errors, id              \
                                                     )                         \
namespace boost_generic_detail {                                               \
typedef struct                                                                 \
{                                                                              \
  template< BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( tpl_dets ) >       \
  struct concept_map_impl                                                      \
  {                                                                            \
  };                                                                           \
} id;                                                                          \
}                                                                              \
BOOST_GENERIC_DETAIL_REGISTER_CONCEPT_MAP_AUTO                                 \
( ( BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_CONCEPT_NAME( np_dets ) )        \
, ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( tpl_dets ) )               \
, ( BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_CONCEPT_PARAMS( np_dets ) )      \
, ( ::boost::mpl::true_ )                                                      \
, ( ::boost_generic_detail::id::concept_map_impl                               \
    < BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS( tpl_dets ) >               \
  )                                                                            \
)

#else

// Format is template params, concept map name, concept name, the concept args
// and then the named arguments if any
#define BOOST_GENERIC_AUTO_CONCEPT_MAP( template_decl_, ... )                  \
BOOST_GENERIC_DETAIL_ASSERT_AT_GLOBAL_SCOPE                                    \
( "Concept maps must be defined at global scope" )                             \
BOOST_GENERIC_AUTO_CONCEPT_MAP_IMPL                                            \
( BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS( template_decl_            \
                                                   , __VA_ARGS__               \
                                                   )                           \
)

#define BOOST_GENERIC_AUTO_CONCEPT_MAP_IMPL( auto_concept_map_arg_details )    \
namespace boost_generic_detail {                                               \
template< BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_TEMPLATE_PARAMS                \
          ( template_params_ )                                                 \
        >                                                                      \
struct concept_map_name_                                                       \
{                                                                              \
};                                                                             \
}                                                                              \
BOOST_GENERIC_DETAIL_REGISTER_CONCEPT_MAP_AUTO                                 \
( concept_in_paren_                                                            \
, ( BOOST_GENERIC_AUTO_CONCEPT_MAP_TEMPLATE_PARAMS( template_params_ ) )       \
, BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ )                            \
, ( ::boost::mpl::true_ )                                                      \
, ( concept_map_name_                                                          \
    < BOOST_GENERIC_AUTO_CONCEPT_MAP_TEMPLATE_ARGS( template_params_ ) >       \
  )                                                                            \
)

#endif

#endif // BOOST_GENERIC_AUTO_CONCEPT_MAP_HPP
