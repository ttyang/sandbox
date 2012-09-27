/*==============================================================================
    Copyright (c) 2010, 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_CONCEPT_MAP_HPP
#define BOOST_GENERIC_CONCEPT_MAP_HPP

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS
#include <boost/mpl/identity.hpp>
#endif

#include <boost/generic/detail/assert_at_global_scope.hpp>
#include <boost/generic/detail/concept_is_valid.hpp>
#include <boost/generic/detail/concept_map/arg_dets.hpp>
#include <boost/generic/detail/concept_map/body_dets.hpp>
#include <boost/generic/detail/concept_map/concept_and_params_dets.hpp>
#include <boost/generic/detail/concept_map/map_specifier_visitor.hpp>
#include <boost/generic/detail/concept_map_template.hpp>
#include <boost/generic/detail/instantiate.hpp>
#include <boost/generic/detail/template_decl_details.hpp>
#include <boost/generic/detail/variadic_stringize.hpp>
#include <boost/generic/detail/wrap.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/control/iif.hpp>

#define BOOST_GENERIC_CONCEPT_MAP( ... )                                       \
BOOST_GENERIC_DETAIL_ASSERT_AT_GLOBAL_SCOPE                                    \
( "Concept maps must be defined at global scope." )                            \
BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL                                          \
( BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS( __VA_ARGS__ ) )

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL( dets )                          \
BOOST_PP_IIF( BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_IS_VALID( dets )       \
            , BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_VALID                      \
            , BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_INVALID                    \
            )( dets )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_ASSERT( dets )                        \
static_assert                                                                  \
( ::boost::generic::detail::concept_is_valid                                   \
  < BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_CONCEPT_AND_PARAMS( dets ) >     \
  ::value                                                                      \
, "Concept map does not satisfy the following requirements: "                  \
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE_AFTER_RESCAN                         \
  ( BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_CONCEPT_AND_PARAMS( dets ) )     \
);                                                                             \
                                                                               \
static_assert                                                                  \
( ::boost::mpl::identity                                                       \
  < decltype                                                                   \
    ( ::boost::generic::detail::instantiate                                    \
      < BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_CONCEPT_AND_PARAMS( dets ) > \
      ()                                                                       \
    )                                                                          \
  >::type::value                                                               \
, "This message should never be seen."                                         \
);

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_VALID( dets )                    \
namespace boost_generic_concept_map_detail {                                   \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETS_IS_VALID                             \
  ( BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_TEMPLATE_DETS( dets ) )          \
, BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETS_MAKE_TEMPLATE                        \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( template<> )                         \
)( BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_TEMPLATE_DETS( dets ) )           \
struct concept_map_                                                            \
       < BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_CONCEPT_AND_PARAMS( dets ) >\
{                                                                              \
  static bool const is_auto_concept_definition = false, is_usable = true;      \
                                                                               \
  struct boost_generic_concept_map_impl                                        \
  {                                                                            \
    BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_VISIT_BODY                       \
    ( dets, BOOST_GENERIC_DETAIL_MAP_SPECIFIER, ~ )                            \
  };                                                                           \
                                                                               \
  template< class BoostGenericDetailDummy = void >                             \
  struct instantiate                                                           \
  {                                                                            \
    typedef decltype                                                           \
    ( ::boost::generic::detail::instantiate_with_dummy                         \
      < BoostGenericDetailDummy                                                \
      , BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_CONCEPT_AND_PARAMS           \
        ( dets )                                                               \
      >()                                                                      \
    ) instantiate_;                                                            \
  };                                                                           \
};                                                                             \
                                                                               \
}                                                                              \
                                                                               \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETS_IS_VALID                             \
  ( BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_TEMPLATE_DETS( dets ) )          \
, BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                                          \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_ASSERT                                      \
)( dets )

#endif // BOOST_GENERIC_CONCEPT_MAP_HPP
