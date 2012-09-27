/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_CONCEPT_HPP
#define BOOST_GENERIC_CONCEPT_HPP

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS
#include <type_traits>
#endif

#include <boost/generic/detail/and.hpp>
#include <boost/generic/detail/concept/arg_details.hpp>
#include <boost/generic/detail/concept/emulator.hpp>
#include <boost/generic/detail/concept/emulator_state.hpp>
#include <boost/generic/detail/completed_concept_map_bases.hpp>
#include <boost/generic/detail/concept_map_template.hpp>
#include <boost/generic/detail/concepts_are_modeled.hpp>
//#include <boost/generic/detail/actual_typedefs_visitor.hpp>
//#include <boost/generic/detail/deduce_typename_helper_visitor.hpp>
//#include <boost/generic/detail/deduce_typename_visitor.hpp>
//#include <boost/generic/detail/first_pass_type_metafun_visitor.hpp>
//#include <boost/generic/detail/function_sequence_visitor.hpp>
//#include <boost/generic/detail/static_assert_visitor.hpp>
#include <boost/generic/detail/concept_impl_of.hpp>
#include <boost/generic/detail/concept_map_template.hpp>
#include <boost/generic/detail/instantiate.hpp>
#include <boost/generic/detail/is_concept.hpp>
#include <boost/generic/detail/namespace.hpp>
#include <boost/generic/detail/type.hpp>
//#include <boost/generic/detail/typedef_first_pass_types_visitor.hpp>
//#include <boost/generic/detail/typename_sequence_vistor.hpp>
//#include <boost/generic/detail/typename_visitor.hpp>
#include <boost/generic/detail/variadic_empty.hpp>
#include <boost/preprocessor/control/iif.hpp>

#define BOOST_GENERIC_CONCEPT( ... )                                           \
BOOST_GENERIC_DETAIL_ASSERT_AT_GLOBAL_SCOPE                                    \
( "The BOOST_GENERIC_CONCEPT macro must be invoked at global scope. "          \
  "To make a concept inside a namespace, use a namespace parameter."           \
)                                                                              \
BOOST_GENERIC_CONCEPT_DETAIL_IMPL_                                             \
( BOOST_GENERIC_DETAIL_NAMESPACE_DETS                                          \
  ( BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ ) )                        \
, __VA_ARGS__                                                                  \
)

#define BOOST_GENERIC_CONCEPT_DETAIL_IMPL_( namespace_dets, ... )              \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_NAMESPACE( namespace_dets )           \
, BOOST_GENERIC_CONCEPT_DETAIL_IMPL_NAMESPACE                                  \
, BOOST_GENERIC_CONCEPT_DETAIL_NO_NAMESPACE                                    \
)( namespace_dets, __VA_ARGS__ )

#define BOOST_GENERIC_CONCEPT_DETAIL_IMPL_NAMESPACE( namespace_dets, ... )     \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_VALID( namespace_dets )   \
            , BOOST_GENERIC_CONCEPT_DETAIL_VALID_NAMESPACE                     \
            , BOOST_GENERIC_CONCEPT_DETAIL_INVALID_NAMESPACE                   \
            )( namespace_dets, __VA_ARGS__ )

#define BOOST_GENERIC_CONCEPT_DETAIL_VALID_NAMESPACE(namespace_dets,...)       \
BOOST_GENERIC_CONCEPT_IMPL                                                     \
( 0, namespace_dets                                                            \
, BOOST_GENERIC_DETAIL_CONCEPT_DETS                                            \
  ( BOOST_GENERIC_DETAIL_TAIL_ARGUMENTS( __VA_ARGS__ ) )                       \
)

#define BOOST_GENERIC_CONCEPT_DETAIL_INVALID_NAMESPACE(namespace_dets,...)     \
static_assert                                                                  \
( false, "Invalid namespace parameter of BOOST_GENERIC_CONCEPT." );

#define BOOST_GENERIC_CONCEPT_DETAIL_NO_NAMESPACE( namespace_dets, ... )       \
BOOST_GENERIC_CONCEPT_IMPL                                                     \
( 0, namespace_dets, BOOST_GENERIC_DETAIL_CONCEPT_DETS( __VA_ARGS__ ) )

#define BOOST_GENERIC_CONCEPT_IMPL( auto_concept_bit, namespace_dets, dets )   \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_CONCEPT_DETS_IS_VALID( dets )               \
            , BOOST_GENERIC_CONCEPT_IMPL_VALID                                 \
            , BOOST_GENERIC_CONCEPT_IMPL_INVALID                               \
            )( auto_concept_bit, namespace_dets, dets )

#define BOOST_GENERIC_CONCEPT_IMPL_VALID( auto_concept_bit, namespace_dets     \
                                        , dets                                 \
                                        )                                      \
BOOST_GENERIC_CONCEPT_IMPL_VALID_                                              \
( auto_concept_bit                                                             \
, namespace_dets                                                               \
, dets                                                                         \
, BOOST_GENERIC_DETAIL_CONCEPT_DETS_FOLD_BODY                                  \
  ( dets, BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR                                \
  , BOOST_GENERIC_DETAIL_CONCEPT_EMPTY_EMULATOR_STATE()                        \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_THIS_TYPENAME( r, data, elem )                    \
typename data::elem,

#define BOOST_GENERIC_DETAIL_TYPEDEF_TYPENAMES_MAC( r, data, elem )            \
typedef typename data::elem elem;

#define BOOST_GENERIC_DETAIL_INSTANTIATE_IF_AUTO( dets )                       \
template< BOOST_GENERIC_DETAIL_CONCEPT_DETS_PARAMS( dets ) >                   \
decltype                                                                       \
( boost_generic_detail_instantiate                                             \
  ( ::std::declval                                                             \
    < BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME( dets )                   \
      < BOOST_GENERIC_DETAIL_CONCEPT_DETS_ARGS( dets ) >                       \
    >()                                                                        \
  )                                                                            \
)                                                                              \
boost_generic_detail_instantiate_if_auto                                       \
( ::boost::generic::detail::type_                                              \
  < BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME( dets )                     \
    < BOOST_GENERIC_DETAIL_CONCEPT_DETS_ARGS( dets ) >                         \
  >                                                                            \
);

#define BOOST_GENERIC_DETAIL_ACTUAL_DEDUCERS_MAC( r, num_funs, name )          \
template< class BoostGenericDetailConceptMap                                   \
        , class BoostGenericDetailParams, class BoostGenericDetailTypenames    \
        >                                                                      \
struct BOOST_PP_CAT( boost_generic_detail_deduce, name )                       \
  : BOOST_GENERIC_DETAIL_NARY_CAT                                              \
    ( boost_generic_detail_deduce_, num_funs, name )                           \
    < BoostGenericDetailConceptMap                                             \
    , BoostGenericDetailParams, BoostGenericDetailTypenames                    \
    > {};

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEF_MAC( r, data, name )               \
typedef typename ::boost::mpl::eval_if                                         \
        < ::boost::generic::detail::is_dummy_type                              \
          < typename boost_generic_detail_first_pass                           \
            < BoostGenericDetailConceptMap                                     \
            , BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, data ) )\
            >::name                                                            \
          >                                                                    \
        , BOOST_GENERIC_DETAIL_NARY_CAT( boost_generic_detail_deduce_          \
                                       , BOOST_PP_SEQ_ELEM( 2, data )          \
                                       , name                                  \
                                       )                                       \
          < BoostGenericDetailConceptMap                                       \
          , boost_generic_detail_params                                        \
            < BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, data ) )\
            >                                                                  \
          , ::boost::generic::detail::type_list                                \
            < BOOST_GENERIC_DETAIL_REMOVE_PAREN                                \
              ( BOOST_PP_SEQ_ELEM( 1, data ) )                                 \
            >                                                                  \
          >                                                                    \
        , ::boost::mpl::identity                                               \
          < typename boost_generic_detail_first_pass                           \
            < BoostGenericDetailConceptMap                                     \
            , BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, data ) )\
            >::name                                                            \
          >                                                                    \
        >::type name;

#define BOOST_GENERIC_DETAIL_REQUIRES_ARE_VALID_0_WITH_PARENTS( dets )         \
template< class, class, class, class = void >                                  \
struct boost_generic_detail_requires_are_valid_0 : ::std::false_type {};       \
                                                                               \
template< class BoostGenericDetailConceptMap                                   \
        , BOOST_GENERIC_DETAIL_CONCEPT_DETS_PARAMS( dets )                     \
        , class BoostGenericDetailTypenames                                    \
        >                                                                      \
struct boost_generic_detail_requires_are_valid_0                               \
       < BoostGenericDetailConceptMap                                          \
       , boost_generic_detail_params                                           \
         < BOOST_GENERIC_DETAIL_CONCEPT_DETS_ARGS( dets ) >                    \
       , BoostGenericDetailTypenames                                           \
       , typename ::boost::generic::detail::always_void                        \
         < BOOST_GENERIC_DETAIL_CONCEPT_DETS_PARENTS( dets ) >::type           \
       >                                                                       \
  : ::boost::generic::detail::concepts_are_modeled                             \
    < BoostGenericDetailConceptMap                                             \
    , BOOST_GENERIC_DETAIL_CONCEPT_DETS_PARENTS( dets )                        \
    > {};

#define BOOST_GENERIC_DETAIL_REQUIRES_ARE_VALID_0_NO_PARENTS( dets )           \
template< class, class, class >                                                \
struct boost_generic_detail_requires_are_valid_0 : ::boost::mpl::true_ {};

#define BOOST_GENERIC_DETAIL_COMPLETED_MAP_BASES_WITH_PARENTS( dets )          \
    : virtual boost::generic::detail::completed_concept_map_bases              \
      < BoostGenericDetailConceptMap                                           \
      , BOOST_GENERIC_DETAIL_CONCEPT_DETS_PARENTS( dets )                      \
      >

#define BOOST_GENERIC_DETAIL_CONCEPT_PARENT_ASSERTS( dets )                    \
static_assert                                                                  \
( ::boost::mpl::identity                                                       \
  < decltype                                                                   \
    ( ::boost::generic::detail::instantiate                                    \
      < BOOST_GENERIC_DETAIL_CONCEPT_DETS_PARENTS( dets ) >()                  \
    )                                                                          \
  >::type::value                                                               \
, "This message should never be seen."                                         \
);

#define BOOST_GENERIC_DETAIL_EMPTY_AUTO_CONCEPT_MAP( namespace_dets, dets )    \
namespace boost_generic_concept_map_detail {                                   \
                                                                               \
template< BOOST_GENERIC_DETAIL_CONCEPT_DETS_PARAMS( dets ) >                   \
struct concept_map_                                                            \
       < ::BOOST_GENERIC_DETAIL_NAMESPACE_DETS_ACCESS_NAMESPACE                \
           ( namespace_dets )                                                  \
         BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME_AND_ARGS( dets )       \
       >                                                                       \
{                                                                              \
  static bool const is_auto_concept_definition = true, is_usable = true;       \
                                                                               \
  struct boost_generic_concept_map_impl {};                                    \
                                                                               \
  template< class BoostGenericDetailDummy = void >                             \
  struct instantiate                                                           \
  {                                                                            \
    typedef decltype                                                           \
    ( ::boost::generic::detail::instantiate_with_dummy                         \
      < BoostGenericDetailDummy                                                \
      , ::BOOST_GENERIC_DETAIL_NAMESPACE_DETS_ACCESS_NAMESPACE                 \
           ( namespace_dets )                                                  \
          BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME( dets )               \
        < BOOST_GENERIC_DETAIL_CONCEPT_DETS_ARGS( dets ) >                     \
      >()                                                                      \
    ) instantiate_;                                                            \
  };                                                                           \
};                                                                             \
                                                                               \
}

#define BOOST_GENERIC_DETAIL_ACTUAL_DEDUCERS_IMPL( num_funs, typename_seq )    \
BOOST_GENERIC_DETAIL_PARAMS_FOR_EACH                                           \
( BOOST_GENERIC_DETAIL_ACTUAL_DEDUCERS_MAC, num_funs, typename_seq )

#define BOOST_GENERIC_DETAIL_TYPEDEF_TYPENAMES_IMPL( typename_seq )            \
BOOST_GENERIC_DETAIL_PARAMS_FOR_EACH                                           \
( BOOST_GENERIC_DETAIL_TYPEDEF_TYPENAMES_MAC                                   \
, boost_generic_detail_completed_concept_map                                   \
, typename_seq                                                                 \
)

#define BOOST_GENERIC_DETAIL_THIS_TYPENAME_IMPL( typename_seq )                \
BOOST_GENERIC_DETAIL_PARAMS_FOR_EACH                                           \
( BOOST_GENERIC_DETAIL_THIS_TYPENAME                                           \
, boost_generic_detail_completed_concept_map_                                  \
, typename_seq                                                                 \
)

#define BOOST_GENERIC_CONCEPT_IMPL_VALID_( auto_concept_bit, namespace_dets    \
                                         , dets, state                         \
                                         )                                     \
BOOST_GENERIC_DETAIL_NAMESPACE_DETS_OPEN_NAMESPACE( namespace_dets )           \
                                                                               \
template< BOOST_GENERIC_DETAIL_CONCEPT_DETS_PARAMS( dets ) >                   \
class BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME( dets );                  \
                                                                               \
namespace boost_generic_concept_impl_detail {                                  \
struct BOOST_PP_CAT( boost_generic_detail_concept_impl                         \
                   , BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME( dets )    \
                   )                                                           \
{                                                                              \
  struct boost_generic_detail_tag                                              \
  {                                                                            \
    static bool const is_auto_concept = auto_concept_bit == 1;                 \
  };                                                                           \
                                                                               \
  template< BOOST_GENERIC_DETAIL_CONCEPT_DETS_PARAMS( dets ) >                 \
  struct boost_generic_detail_params;                                          \
                                                                               \
  template< class BoostGenericDetailConceptAndParams >                         \
  struct boost_generic_detail_params_from_concept;                             \
                                                                               \
  template< BOOST_GENERIC_DETAIL_CONCEPT_DETS_PARAMS( dets ) >                 \
  struct boost_generic_detail_params_from_concept                              \
         < BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME( dets )              \
           < BOOST_GENERIC_DETAIL_CONCEPT_DETS_ARGS( dets ) >                  \
         >                                                                     \
  { typedef boost_generic_detail_params                                        \
            < BOOST_GENERIC_DETAIL_CONCEPT_DETS_ARGS( dets ) > type;           \
  };                                                                           \
                                                                               \
  BOOST_PP_IIF( BOOST_GENERIC_DETAIL_CONCEPT_DETS_HAS_PUBLIC( dets )           \
              , BOOST_GENERIC_DETAIL_REQUIRES_ARE_VALID_0_WITH_PARENTS         \
              , BOOST_GENERIC_DETAIL_REQUIRES_ARE_VALID_0_NO_PARENTS           \
              )( dets )                                                        \
                                                                               \
  BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_FIRST_PASS_TYPE_METAFUNCTIONS    \
  ( state )                                                                    \
                                                                               \
  template< class BoostGenericDetailConceptMap                                 \
          , BOOST_GENERIC_DETAIL_CONCEPT_DETS_PARAMS( dets )                   \
          >                                                                    \
  struct boost_generic_detail_first_pass                                       \
  {                                                                            \
    BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_FIRST_PASS_TYPEDEFS( state )   \
  };                                                                           \
                                                                               \
  BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_DEDUCER_HELPERS( state )         \
                                                                               \
  BOOST_PP_IIF                                                                 \
  ( BOOST_GENERIC_DETAIL_IS_EMPTY                                              \
    ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TYPENAME_ARGS( state ) )     \
  , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                                        \
  , BOOST_GENERIC_DETAIL_ACTUAL_DEDUCERS_IMPL                                  \
  )( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state )        \
   , ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TYPENAME_ARGS( state ) )    \
   )                                                                           \
                                                                               \
  template< class, class >                                                     \
  struct boost_generic_detail_is_valid_;                                       \
                                                                               \
  template< class BoostGenericDetailConceptMap                                 \
          , class BoostGenericDetailParams                                     \
          , class = void                                                       \
          >                                                                    \
  struct boost_generic_detail_parent_concepts                                  \
  {                                                                            \
    typedef ::std::false_type boost_generic_detail_parent_sub_succeeded;       \
  };                                                                           \
                                                                               \
  template< class BoostGenericDetailConceptMap                                 \
          , BOOST_GENERIC_DETAIL_CONCEPT_DETS_PARAMS( dets )                   \
          >                                                                    \
  struct boost_generic_detail_parent_concepts                                  \
         < BoostGenericDetailConceptMap                                        \
         , boost_generic_detail_params                                         \
           < BOOST_GENERIC_DETAIL_CONCEPT_DETS_ARGS( dets ) >                  \
         , typename ::boost::generic::detail::always_void                      \
           < BOOST_PP_IIF                                                      \
             ( BOOST_GENERIC_DETAIL_CONCEPT_DETS_HAS_PUBLIC( dets )            \
             , BOOST_GENERIC_DETAIL_CONCEPT_DETS_PARENTS                       \
             , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                             \
             )( dets )                                                         \
           >::type                                                             \
         >                                                                     \
    BOOST_PP_IIF( BOOST_GENERIC_DETAIL_CONCEPT_DETS_HAS_PUBLIC( dets )         \
                , BOOST_GENERIC_DETAIL_COMPLETED_MAP_BASES_WITH_PARENTS        \
                , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                          \
                )( dets )                                                      \
  {                                                                            \
    typedef ::std::true_type boost_generic_detail_parent_sub_succeeded;        \
  };                                                                           \
                                                                               \
  template< class BoostGenericDetailConceptMap                                 \
          , BOOST_GENERIC_DETAIL_CONCEPT_DETS_PARAMS( dets )                   \
          >                                                                    \
  struct boost_generic_detail_completed_concept_map                            \
    : boost_generic_detail_parent_concepts                                     \
      < BoostGenericDetailConceptMap                                           \
      , boost_generic_detail_params                                            \
        < BOOST_GENERIC_DETAIL_CONCEPT_DETS_ARGS( dets ) >                     \
      >                                                                        \
  {                                                                            \
  private:                                                                     \
    typedef boost_generic_detail_first_pass                                    \
            < BoostGenericDetailConceptMap                                     \
            , BOOST_GENERIC_DETAIL_CONCEPT_DETS_ARGS( dets )                   \
            > boost_generic_detail_typename_deducers;                          \
                                                                               \
    typedef boost_generic_detail_completed_concept_map                         \
            BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME( dets );            \
  public:                                                                      \
    BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_ACTUAL_CONCEPT_MAP_BODY        \
    ( state, BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_PARAM_DETS( dets ) )    \
  private:                                                                     \
    template< class, class >                                                   \
    friend struct boost_generic_detail_is_valid_;                              \
                                                                               \
    typedef boost_generic_detail_completed_concept_map                         \
            boost_generic_detail_completed_concept_map_;                       \
                                                                               \
    typedef boost_generic_detail_params                                        \
            < BOOST_GENERIC_DETAIL_CONCEPT_DETS_ARGS( dets ) >                 \
            boost_generic_detail_params_;                                      \
                                                                               \
    typedef ::boost::generic::detail::type_list                                \
            < BOOST_PP_IIF                                                     \
              ( BOOST_GENERIC_DETAIL_IS_EMPTY                                  \
                ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TYPENAME_ARGS    \
                  ( state )                                                    \
                )                                                              \
              , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                            \
              , BOOST_GENERIC_DETAIL_THIS_TYPENAME_IMPL                        \
              )( ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TYPENAME_ARGS   \
                   ( state )                                                   \
                 )                                                             \
               )                                                               \
              void                                                             \
            >                                                                  \
            boost_generic_detail_typenames;                                    \
  public:                                                                      \
    struct boost_generic_detail_is_valid                                       \
      : ::boost::generic::detail::and_                                         \
        < typename boost_generic_detail_completed_concept_map                  \
          ::boost_generic_detail_parent_sub_succeeded                          \
        , BOOST_PP_CAT                                                         \
          ( boost_generic_detail_requires_are_valid_                           \
          , BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_REQUIRES( state )  \
          )< boost_generic_detail_completed_concept_map                        \
           , boost_generic_detail_params_, boost_generic_detail_typenames      \
           >                                                                   \
       BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_IS_VALID_CONDITIONS\
          ( state )                                                            \
        > {};                                                                  \
  };                                                                           \
                                                                               \
  template< class, class >                                                     \
  struct boost_generic_detail_completed_concept_map_from_concept;              \
                                                                               \
  template< class BoostGenericDetailConceptMap                                 \
          , BOOST_GENERIC_DETAIL_CONCEPT_DETS_PARAMS( dets )                   \
          >                                                                    \
  struct boost_generic_detail_completed_concept_map_from_concept               \
         < BoostGenericDetailConceptMap                                        \
         , BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME( dets )              \
           < BOOST_GENERIC_DETAIL_CONCEPT_DETS_ARGS( dets ) >                  \
         >                                                                     \
  {                                                                            \
    typedef boost_generic_detail_completed_concept_map                         \
            < BoostGenericDetailConceptMap                                     \
            , BOOST_GENERIC_DETAIL_CONCEPT_DETS_ARGS( dets )                   \
            > type;                                                            \
  };                                                                           \
                                                                               \
  template< BOOST_GENERIC_DETAIL_CONCEPT_DETS_PARAMS( dets )                   \
          , class BoostGenericDetailConceptMap                                 \
          >                                                                    \
  struct boost_generic_detail_is_valid_                                        \
         < BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME( dets )              \
           < BOOST_GENERIC_DETAIL_CONCEPT_DETS_ARGS( dets ) >                  \
         , BoostGenericDetailConceptMap                                        \
         >                                                                     \
    : boost_generic_detail_completed_concept_map                               \
      < BoostGenericDetailConceptMap                                           \
      , BOOST_GENERIC_DETAIL_CONCEPT_DETS_ARGS( dets )                         \
      >::boost_generic_detail_is_valid {};                                     \
                                                                               \
  template< class BoostGenericDetailConceptAndParams                           \
          , class BoostGenericDetailConceptMap                                 \
              = typename ::boost_generic_concept_map_detail::concept_map_      \
                < BoostGenericDetailConceptAndParams >                         \
                ::boost_generic_concept_map_impl                               \
          >                                                                    \
  struct boost_generic_detail_is_valid                                         \
    : boost_generic_detail_is_valid_                                           \
      < BoostGenericDetailConceptAndParams                                     \
      , BoostGenericDetailConceptMap                                           \
      >::type {};                                                              \
};                                                                             \
}                                                                              \
                                                                               \
typedef boost_generic_concept_impl_detail::                                    \
        BOOST_PP_CAT( boost_generic_detail_concept_impl                        \
                    , BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME( dets )   \
                    )                                                          \
        BOOST_PP_CAT( BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME( dets )   \
                    , BoostGenericDetailImpl                                   \
                    );                                                         \
                                                                               \
template< BOOST_GENERIC_DETAIL_CONCEPT_DETS_PARAMS( dets ) >                   \
class BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME( dets )                   \
  : boost_generic_concept_impl_detail::                                        \
    BOOST_PP_CAT( boost_generic_detail_concept_impl                            \
                , BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME( dets )       \
                )::                                                            \
    boost_generic_detail_completed_concept_map                                 \
    < typename ::boost_generic_concept_map_detail::concept_map_                \
      < BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME_AND_ARGS( dets ) >      \
      ::boost_generic_concept_map_impl                                         \
    , BOOST_GENERIC_DETAIL_CONCEPT_DETS_ARGS( dets )                           \
    >                                                                          \
{                                                                              \
  typedef boost_generic_concept_impl_detail::                                  \
          BOOST_PP_CAT( boost_generic_detail_concept_impl                      \
                      , BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME( dets ) \
                      )                                                        \
          boost_generic_detail_concept_impl;                                   \
                                                                               \
  typedef typename boost_generic_detail_concept_impl::template                 \
          boost_generic_detail_completed_concept_map                           \
          < typename ::boost_generic_concept_map_detail::concept_map_          \
            < BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME_AND_ARGS( dets ) >\
            ::boost_generic_concept_map_impl                                   \
          , BOOST_GENERIC_DETAIL_CONCEPT_DETS_ARGS( dets )                     \
          >                                                                    \
          boost_generic_detail_completed_concept_map;                          \
                                                                               \
  typedef boost_generic_detail_concept_impl::boost_generic_detail_params       \
          < BOOST_GENERIC_DETAIL_CONCEPT_DETS_ARGS( dets ) >                   \
          boost_generic_detail_params;                                         \
                                                                               \
  struct parent_concept_asserts_substitution_failure { struct instantiate; };  \
                                                                               \
  struct parent_concept_asserts                                                \
  {                                                                            \
    struct instantiate;                                                        \
                                                                               \
    BOOST_PP_IIF( BOOST_GENERIC_DETAIL_CONCEPT_DETS_HAS_PUBLIC( dets )         \
                , BOOST_GENERIC_DETAIL_CONCEPT_PARENT_ASSERTS                  \
                , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                          \
                )( dets )                                                      \
  };                                                                           \
                                                                               \
  typedef typename ::std::conditional                                          \
          < boost_generic_detail_completed_concept_map                         \
            ::boost_generic_detail_parent_sub_succeeded::value                 \
          , parent_concept_asserts                                             \
          , parent_concept_asserts_substitution_failure                        \
          >::type::instantiate parent_concept_asserts_;                        \
                                                                               \
  static_assert( boost_generic_detail_completed_concept_map                    \
                 ::boost_generic_detail_parent_sub_succeeded::value            \
               , "parameters unable to be substituted into parent concepts "   \
                 "(guess: doing so may form a reference to void)."             \
               );                                                              \
public:                                                                        \
  BOOST_PP_IIF                                                                 \
  ( BOOST_GENERIC_DETAIL_IS_EMPTY                                              \
    ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TYPENAME_ARGS( state ) )     \
  , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                                        \
  , BOOST_GENERIC_DETAIL_TYPEDEF_TYPENAMES_IMPL                                \
  )( ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TYPENAME_ARGS( state ) ) )  \
private:                                                                       \
  typedef ::boost::generic::detail::type_list                                  \
          < BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TYPENAME_ARGS( state ) \
            BOOST_PP_COMMA_IF                                                  \
            ( BOOST_PP_COMPL                                                   \
              ( BOOST_GENERIC_DETAIL_IS_EMPTY                                  \
                ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TYPENAME_ARGS    \
                  ( state )                                                    \
                )                                                              \
              )                                                                \
            )                                                                  \
            void                                                               \
          >                                                                    \
          boost_generic_detail_typenames;                                      \
                                                                               \
  BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_CONCEPT_BODY( state )            \
};                                                                             \
                                                                               \
BOOST_GENERIC_DETAIL_NAMESPACE_DETS_CLOSE_NAMESPACE( namespace_dets )          \
                                                                               \
namespace boost { namespace generic { namespace detail {                       \
                                                                               \
template< BOOST_GENERIC_DETAIL_CONCEPT_DETS_PARAMS( dets ) >                   \
struct is_concept                                                              \
       < ::BOOST_GENERIC_DETAIL_NAMESPACE_DETS_ACCESS_NAMESPACE                \
           ( namespace_dets )                                                  \
         BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME( dets )                \
         < BOOST_GENERIC_DETAIL_CONCEPT_DETS_ARGS( dets ) >                    \
       > : mpl::true_ {};                                                      \
                                                                               \
template< BOOST_GENERIC_DETAIL_CONCEPT_DETS_PARAMS( dets ) >                   \
struct concept_impl_of                                                         \
       < ::BOOST_GENERIC_DETAIL_NAMESPACE_DETS_ACCESS_NAMESPACE                \
           ( namespace_dets )                                                  \
         BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME( dets )                \
         < BOOST_GENERIC_DETAIL_CONCEPT_DETS_ARGS( dets ) >                    \
       >                                                                       \
{                                                                              \
  static bool const is_specialized = false;                                    \
  static bool const is_auto = auto_concept_bit;                                \
                                                                               \
  typedef ::BOOST_GENERIC_DETAIL_NAMESPACE_DETS_ACCESS_NAMESPACE               \
            ( namespace_dets )                                                 \
          boost_generic_concept_impl_detail::                                  \
          BOOST_PP_CAT( boost_generic_detail_concept_impl                      \
                      , BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME( dets ) \
                      )                                                        \
          type;                                                                \
};                                                                             \
                                                                               \
} } }                                                                          \
                                                                               \
BOOST_PP_IIF( auto_concept_bit                                                 \
            , BOOST_GENERIC_DETAIL_EMPTY_AUTO_CONCEPT_MAP                      \
            , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                              \
            )( namespace_dets, dets )

#endif // BOOST_GENERIC_CONCEPT_HPP
