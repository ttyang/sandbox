/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_HPP
#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_HPP

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS

#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>
#include <cstddef>
#include <new>
#include <type_traits>

#endif

#include <boost/generic/detail/always_void.hpp>
#include <boost/generic/detail/concept/emulator_state.hpp>
#include <boost/generic/detail/concept_is_valid.hpp>
#include <boost/generic/detail/deduction_result.hpp>
#include <boost/generic/detail/dummy_type.hpp>
#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/is_not_same.hpp>
#include <boost/generic/detail/nary_cat.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/rescan.hpp>
#include <boost/generic/detail/type_list.hpp>
#include <boost/generic/detail/variadic_empty.hpp>
#include <boost/generic/detail/variadic_stringize.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/replace.hpp>
#include <boost/preprocessor/seq/subseq.hpp>
#include <boost/preprocessor/stringize.hpp>

namespace boost { namespace generic { namespace detail {

template< class T >
struct identity_unless_void
{
  typedef T type;
};

template<> struct identity_unless_void< void > {};
template<> struct identity_unless_void< void const > {};
template<> struct identity_unless_void< void volatile > {};
template<> struct identity_unless_void< void volatile const > {};

template< class T, class Params, class Enabler = void >
struct operator_new_checker_nonnested : mpl::false_ {};

template< class T, class... P >
struct operator_new_checker_nonnested
       < T, type_list< std::size_t, P... >
       , typename always_void
         < decltype( new( ::std::declval< P >()... ) T ) >::type
       >
  : mpl::true_ {};

template< class T, class... Params >
struct operator_new_checker
  : operator_new_checker_nonnested< T, type_list< Params... > > {};

template< class T, class Params, class Enabler = void >
struct operator_new_array_checker_nonnested : mpl::false_ {};

template< class T, class... P >
struct operator_new_array_checker_nonnested
       < T, type_list< std::size_t, P... >
       , typename always_void
         < decltype( new( ::std::declval< P >()... ) T[1] ) >::type
       >
  : mpl::true_ {};

template< class T, class... Params >
struct operator_new_array_checker
  : operator_new_array_checker_nonnested< T, type_list< Params... > > {};

template< class T, class Params, class Enabler = void >
struct operator_delete_checker_nested : mpl::false_ {};

template< class T, class... P >
struct operator_delete_checker_nested
       < T, type_list< P... >
       , typename always_void
         < decltype( T::operator delete( ::std::declval< P >()... ) ) >::type
       > : mpl::true_ {};

template< class T, class Params, class Enabler = void >
struct operator_delete_checker_nonnested : mpl::false_ {};

template< class T >
struct operator_delete_checker_nonnested
       < T, type_list< void* >
       , typename always_void
         < decltype( delete std::declval< T* >() ) >::type
       >
  : mpl::true_ {};

template< class T, class H, class... P >
struct operator_delete_checker_nonnested
       < T, type_list< void*, H, P... >
       , typename always_void
         < decltype( operator delete( ::std::declval< void* >()
                                    , ::std::declval< H >()
                                    , ::std::declval< P >()...
                                    )
                   )
         >::type
       >
  : mpl::true_ {};

template< class T, class... Params >
struct operator_delete_checker
  : mpl::or_< operator_delete_checker_nested< T, type_list< Params... > >
            , operator_delete_checker_nonnested< T, type_list< Params... > >
            > {};

template< class T, class Params, class Enabler = void >
struct operator_delete_array_checker_nested : mpl::false_ {};

template< class T, class... P >
struct operator_delete_array_checker_nested
       < T, type_list< P... >
       , typename always_void
         < decltype( T::operator delete[]( ::std::declval< P >()... ) ) >::type
       > : mpl::true_ {};

template< class T, class Params, class Enabler = void >
struct operator_delete_array_checker_nonnested : mpl::false_ {};

template< class T, class... P >
struct operator_delete_array_checker_nonnested
       < T, type_list< P... >
       , typename always_void
         < decltype( operator delete[]( ::std::declval< P >()... ) ) >::type
       >
  : mpl::true_ {};

template< class T, class... Params >
struct operator_delete_array_checker
  : mpl::or_< operator_delete_array_checker_nested< T, type_list< Params... > >
            , operator_delete_array_checker_nonnested
              < T, type_list< Params... > >
            > {};

struct allocation_operator_tag_new {};
struct deallocation_operator_tag_delete {};

template< class Tag, class T, class... Params >
typename enable_if_c
< mpl::and_< is_same< Tag, allocation_operator_tag_new >
           , operator_new_checker< T, Params... >
           >::value
>::type*
allocation_operator_fun();

template< class Tag, class T, class... Params >
typename enable_if_c
< mpl::and_< is_same< Tag, allocation_operator_tag_new[] >
           , operator_new_array_checker< T, Params... >
           >::value
>::type*
allocation_operator_fun();

template< class Tag, class T, class... Params >
typename enable_if_c
< mpl::and_< is_same< Tag, deallocation_operator_tag_delete >
           , operator_delete_checker< T, Params... >
           >::value
>::type
deallocation_operator_fun();

template< class Tag, class T, class... Params >
typename enable_if_c
< mpl::and_< is_same< Tag, deallocation_operator_tag_delete[] >
           , operator_delete_array_checker< T, Params... >
           >::value
>::type
deallocation_operator_fun();

template< class T >
struct has_builtin_arrow_impl : mpl::false_ {};

template< class T >
struct has_builtin_arrow_impl< T* > : std::is_object< T > {};

template< class T >
struct remove_ref_decay_and_remove_cv
  : std::remove_cv
    < typename std::decay< typename std::remove_reference< T >::type >::type >
{};

template< class T >
struct has_builtin_arrow
  : has_builtin_arrow_impl
    < typename remove_ref_decay_and_remove_cv< T >::type > {};

template< class T >
struct overloaded_arrow_return_type
{
  typedef decltype( std::declval< T >().operator->() ) type;
};

template< class T >
struct operator_arrow_return_type
  : mpl::if_c< has_builtin_arrow< T >::value
             , remove_ref_decay_and_remove_cv< T >
             , overloaded_arrow_return_type< T >
             >::type {};

template< class T, class Enabler = void >
struct has_overloaded_arrow : mpl::false_ {};

template< class T >
struct has_overloaded_arrow
       < T, typename always_void< decltype( std::declval< T >().operator->() ) >
            ::type
       >
  : mpl::true_ {};

template< class T >
typename lazy_enable_if_c
< mpl::or_< has_builtin_arrow< T >, has_overloaded_arrow< T > >::value
, operator_arrow_return_type< T >
>::type
operator_arrow_fun();

template< class T, class Types >
struct is_constructible_ref;

template< class T >
struct is_constructible_ref
       < T
       , type_list<>
       > : mpl::false_ {};

template< class T, class Type >
struct is_constructible_ref
       < T
       , type_list< Type >
       > : std::is_convertible< Type, T > {};

template< class T, class... Types >
struct is_constructible_ref
       < T
       , type_list< Types... >
       > : mpl::false_ {};

template< class T, class Types, class Enabler = void >
struct is_constructible_nonref : ::boost::mpl::false_ {};

template< class T, class... Types >
struct is_constructible_nonref
       < T
       , type_list< Types... >
       , typename always_void
         < decltype( T( std::declval< Types >()... ) ) >::type
       > : mpl::true_ {};


template< class T, class Types >
struct is_constructible
  : std::conditional
    < std::is_reference< T >::value
    , is_constructible_ref< T, Types >
    , is_constructible_nonref< T, Types >
    >::type  {};

template< class T, class Types >
typename enable_if_c
< mpl::and_< std::is_object< typename std::remove_reference< T >::type >
           , is_constructible< T, Types >
           >::value
, T&&
>::type
constructor_fun();

template< class T, class Enabler = void >
struct is_destructible : mpl::false_ {};

template< class T >
struct is_destructible
       < T, decltype( std::declval< T >().~T() ) >
  : mpl::true_ {};

template< class T >
typename enable_if_c
< mpl::or_
  < std::is_reference< T >
  , mpl::and_< std::is_object< T >
             , is_destructible< T >
             >
  >::value
>::type
destructor_fun();

template< class From, class To >
struct is_convertible_or_target_is_void
  : std::is_convertible< From, To > {};

template< class From >
struct is_convertible_or_target_is_void< From, void > : std::true_type {};

template< class From >
struct is_convertible_or_target_is_void< From, void const > : std::true_type {};

template< class From >
struct is_convertible_or_target_is_void< From, void volatile >
  : std::true_type {};

template< class From >
struct is_convertible_or_target_is_void< From, void const volatile >
  : std::true_type {};

} } }

#define BOOST_GENERIC_DETAIL_REQUIRES_STATIC_ASSERT( arg )                     \
static_assert                                                                  \
( ::boost::generic::detail::concept_is_valid                                   \
  < BOOST_GENERIC_DETAIL_REMOVE_PAREN( arg ) >::value                          \
, "requires "                                                                  \
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE arg                                  \
);

#define BOOST_GENERIC_DETAIL_EMULATOR_STATIC_ASSERT_TYPENAME( concept_, name ) \
static_assert                                                                  \
( ::boost::generic::detail::is_not_same                                        \
  < typename concept_::name, ::boost::generic::detail::no_deduction >::value   \
, "typename '" BOOST_PP_STRINGIZE( name )                                      \
  "' was not explicitly satisfied and cannot be deduced."                      \
);                                                                             \
static_assert                                                                  \
( ::boost::generic::detail::is_not_same                                        \
  < typename concept_::name                                                    \
  , ::boost::generic::detail::ambiguous_deduction                              \
  >::value                                                                     \
, "typename '" BOOST_PP_STRINGIZE( name )                                      \
  "' was not explicitly satisfied and deduction results in ambiguity."         \
);

#define BOOST_GENERIC_DETAIL_EMULATOR_STATIC_ASSERT_CONSTRAINED_TYPENAME(      \
                                                                     concept_  \
                                                                   , name      \
                                                                   , constraint\
                                                                   )           \
BOOST_GENERIC_DETAIL_EMULATOR_STATIC_ASSERT_TYPENAME( concept_, name )         \
static_assert                                                                  \
( ::boost::mpl::or_                                                            \
  < ::boost::is_same                                                           \
    < typename concept_::name, ::boost::generic::detail::no_deduction >        \
  , ::boost::is_same                                                           \
    < typename concept_::name, ::boost::generic::detail::ambiguous_deduction > \
  , ::boost::generic::detail::concept_is_valid                                 \
    < constraint< typename concept_::name > >                                  \
  >::value                                                                     \
, "typename '" BOOST_PP_STRINGIZE( name ) "' does not model '"                 \
  BOOST_PP_STRINGIZE( constraint ) "'."                                        \
);

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEF( name, params, typename_a )        \
typedef typename ::boost::mpl::eval_if_c                                       \
        < ::boost::generic::detail::is_dummy_type                              \
          < typename boost_generic_detail_typename_deducers::name >::value     \
        , BOOST_PP_CAT( boost_generic_detail_deduce, name )                    \
          < BoostGenericDetailConceptMap                                       \
          , boost_generic_detail_params                                        \
            < BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS( params ) >         \
          , ::boost::generic::detail::type_list                                \
            < BOOST_GENERIC_DETAIL_REMOVE_PAREN( typename_a )                  \
              BOOST_PP_COMMA_IF                                                \
              ( BOOST_PP_COMPL                                                 \
                ( BOOST_GENERIC_DETAIL_IS_WRAPPED_EMPTY( typename_a ) )        \
              ) void**********                                                 \
            >                                                                  \
          >                                                                    \
        , ::boost::mpl::identity                                               \
          < typename boost_generic_detail_typename_deducers::name >            \
        >::type name;

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS( state     \
                                                                  , param_dets \
                                                                  , i          \
                                                                  , return_type\
                                                                  , expression \
                                                                  )            \
BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS_                   \
( param_dets, i, return_type, expression                                       \
, BOOST_PP_INC                                                                 \
  ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ) )       \
, ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_TYPENAME_PARAMS       \
    ( state )                                                                  \
  )                                                                            \
, ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TYPENAME_ARGS( state ) )       \
, BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_REQUIRES( state )            \
)

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS_MAC( r     \
                                                                       , data  \
                                                                       , elem  \
                                                                       )       \
template< class BoostGenericDetailParams, class BoostGenericDetailTypenames >  \
struct BOOST_GENERIC_DETAIL_NARY_CAT                                           \
( boost_generic_detail_impl_funs_deduce_, BOOST_PP_SEQ_ELEM( 0, data ), elem );\
                                                                               \
template< BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS                       \
          ( BOOST_PP_SEQ_ELEM( 3, data ) )                                     \
        , BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 4, data ) )    \
          class... BoostGenericDetailOtherTypenames                            \
        >                                                                      \
struct BOOST_GENERIC_DETAIL_NARY_CAT                                           \
( boost_generic_detail_impl_funs_deduce_, BOOST_PP_SEQ_ELEM( 0, data ), elem ) \
< boost_generic_detail_params                                                  \
  < BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS                               \
    ( BOOST_PP_SEQ_ELEM( 3, data ) )                                           \
  >                                                                            \
, ::boost::generic::detail::type_list                                          \
  < BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 5, data ) )          \
    BoostGenericDetailOtherTypenames...                                        \
  >                                                                            \
>                                                                              \
{                                                                              \
                                                                               \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 6, data ) )              \
                                                                               \
static ::boost::generic::detail::type_< ::boost::generic::detail::dummy_type > \
boost_generic_detail_fun_deducer( ... );                                       \
                                                                               \
template< class elem >                                                         \
static                                                                         \
::boost::generic::detail::type_< elem >                                        \
boost_generic_detail_fun_deducer                                               \
( ::boost::generic::detail::type_                                              \
  < BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, data ) ) >        \
);                                                                             \
};                                                                             \
                                                                               \
template< class BoostGenericDetailConceptMap                                   \
        , class BoostGenericDetailParams, class BoostGenericDetailTypenames    \
        >                                                                      \
struct BOOST_GENERIC_DETAIL_NARY_CAT( boost_generic_detail_impl_this_deduce_   \
                                    , BOOST_PP_SEQ_ELEM( 0, data ), elem       \
                                    )                                          \
  : ::boost::mpl::identity                                                     \
    < decltype( BOOST_GENERIC_DETAIL_NARY_CAT                                  \
                ( boost_generic_detail_impl_funs_deduce_                       \
                , BOOST_PP_SEQ_ELEM( 0, data ), elem                           \
                )< BoostGenericDetailParams, BoostGenericDetailTypenames >::   \
                boost_generic_detail_fun_deducer                               \
                ( ::boost::generic::detail::type_                              \
                  < typename BOOST_PP_CAT( boost_generic_detail_return_type_   \
                                         , BOOST_PP_SEQ_ELEM( 0, data )        \
                                         )                                     \
                    < BoostGenericDetailConceptMap                             \
                    , BoostGenericDetailParams, BoostGenericDetailTypenames    \
                    >                                                          \
                    ::type                                                     \
                  >()                                                          \
                )                                                              \
              )                                                                \
    >::type {};                                                                \
                                                                               \
template< class BoostGenericDetailConceptMap                                   \
        , class BoostGenericDetailParams, class BoostGenericDetailTypenames    \
        >                                                                      \
struct BOOST_GENERIC_DETAIL_NARY_CAT( boost_generic_detail_this_deduce_        \
                                    , BOOST_PP_SEQ_ELEM( 0, data ), elem       \
                                    )                                          \
  : ::boost::mpl::if_c                                                         \
    < BOOST_PP_CAT( boost_generic_detail_requires_are_valid_                   \
                  , BOOST_PP_SEQ_ELEM( 2, data )                               \
                  )                                                            \
      < BoostGenericDetailConceptMap                                           \
      , BoostGenericDetailParams, BoostGenericDetailTypenames                  \
      >::value                                                                 \
    , BOOST_GENERIC_DETAIL_NARY_CAT( boost_generic_detail_impl_this_deduce_    \
                                   , BOOST_PP_SEQ_ELEM( 0, data ), elem        \
                                   )                                           \
      < BoostGenericDetailConceptMap                                           \
      , BoostGenericDetailParams, BoostGenericDetailTypenames                  \
      >                                                                        \
    , ::boost::generic::detail::type_< ::boost::generic::detail::dummy_type >  \
    >::type {};                                                                \
                                                                               \
template< class BoostGenericDetailConceptMap                                   \
        , class BoostGenericDetailParams, class BoostGenericDetailTypenames    \
        >                                                                      \
struct BOOST_GENERIC_DETAIL_NARY_CAT( boost_generic_detail_deduce_             \
                                    , BOOST_PP_SEQ_ELEM( 0, data ), elem       \
                                    )                                          \
  : ::boost::generic::detail::deduction_result                                 \
    < typename BOOST_GENERIC_DETAIL_NARY_CAT                                   \
      ( boost_generic_detail_deduce_                                           \
      , BOOST_PP_DEC( BOOST_PP_SEQ_ELEM( 0, data ) ), elem                     \
      )< BoostGenericDetailConceptMap                                          \
       , BoostGenericDetailParams, BoostGenericDetailTypenames                 \
       >::type                                                                 \
    , BOOST_GENERIC_DETAIL_NARY_CAT( boost_generic_detail_this_deduce_         \
                                   , BOOST_PP_SEQ_ELEM( 0, data ), elem        \
                                   )                                           \
      < BoostGenericDetailConceptMap                                           \
      , BoostGenericDetailParams, BoostGenericDetailTypenames                  \
      >                                                                        \
    > {};

#define BOOST_GENERIC_DETAIL_AUGMENT_TYPENAME_PARAMS_MAC( r, aug, elem )       \
class BOOST_PP_CAT( aug, elem ),

#define BOOST_GENERIC_DETAIL_AUGMENT_TYPENAME_ARGS_MAC( r, aug, elem )         \
BOOST_PP_CAT( aug, elem ),

#define BOOST_GENERIC_DETAIL_TYPEDEF_DEDUCE_TYPENAMES_MAC( r, aug, elem )      \
typedef BOOST_PP_CAT( aug, elem ) elem;

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS_EMPTY(     \
                                                                     param_dets\
                                                                  , i          \
                                                                  , return_type\
                                                                  , expression \
                                                                  , num_fun    \
                                                                  , typename_p \
                                                                  , typename_a \
                                                                  , num_reqs   \
                                                                  )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS_NONEMPTY(  \
                                                                     param_dets\
                                                                  , i          \
                                                                  , return_type\
                                                                  , expression \
                                                                  , num_fun    \
                                                                  , typename_p \
                                                                  , typename_a \
                                                                  , num_reqs   \
                                                                  )            \
BOOST_GENERIC_DETAIL_PARAMS_FOR_EACH_1                                         \
( BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS_MAC              \
, (num_fun)                                                                    \
  (return_type)                                                                \
  (num_reqs)                                                                   \
  (param_dets)                                                                 \
  (( BOOST_GENERIC_DETAIL_PARAMS_FOR_EACH                                      \
     ( BOOST_GENERIC_DETAIL_AUGMENT_TYPENAME_PARAMS_MAC, BoostGenericDetailAug \
     , typename_a                                                              \
     )                                                                         \
  ))                                                                           \
  (( BOOST_GENERIC_DETAIL_PARAMS_FOR_EACH                                      \
     ( BOOST_GENERIC_DETAIL_AUGMENT_TYPENAME_ARGS_MAC, BoostGenericDetailAug   \
     , typename_a                                                              \
     )                                                                         \
  ))                                                                           \
  (( BOOST_GENERIC_DETAIL_PARAMS_FOR_EACH                                      \
     ( BOOST_GENERIC_DETAIL_TYPEDEF_DEDUCE_TYPENAMES_MAC, BoostGenericDetailAug\
     , typename_a                                                              \
     )                                                                         \
  ))                                                                           \
, typename_a                                                                   \
)

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS_(          \
                                                                     param_dets\
                                                                  , i          \
                                                                  , return_type\
                                                                  , expression \
                                                                  , num_fun    \
                                                                  , typename_p \
                                                                  , typename_a \
                                                                  , num_reqs   \
                                                                  )            \
                                                                               \
template< class BoostGenericDetailParams                                       \
        , class BoostGenericDetailTypenames                                    \
        , class BoostGenericDetailEnabler = void                               \
        >                                                                      \
struct BOOST_PP_CAT( boost_generic_detail_return_type_impl_, num_fun )         \
{ typedef ::boost::generic::detail::dummy_type type; };                        \
                                                                               \
template< BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets )         \
          BOOST_GENERIC_DETAIL_REMOVE_PAREN( typename_p )                      \
        , class... BoostGenericDetailOtherTypenames                            \
        >                                                                      \
struct BOOST_PP_CAT( boost_generic_detail_return_type_impl_, num_fun )         \
       < boost_generic_detail_params                                           \
         < BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS( param_dets ) >        \
       , ::boost::generic::detail::type_list                                   \
         < BOOST_GENERIC_DETAIL_REMOVE_PAREN( typename_a )                     \
           BOOST_PP_COMMA_IF                                                   \
           ( BOOST_PP_COMPL                                                    \
             ( BOOST_GENERIC_DETAIL_IS_WRAPPED_EMPTY( typename_a ) )           \
           )                                                                   \
           BoostGenericDetailOtherTypenames...                                 \
         >                                                                     \
       , typename ::boost::generic::detail::always_void                        \
         < decltype ( expression ) >::type                                     \
       > { typedef decltype expression type; };                                \
                                                                               \
template< class BoostGenericDetailConceptMap                                   \
        , class BoostGenericDetailParams                                       \
        , class BoostGenericDetailTypenames                                    \
        >                                                                      \
struct BOOST_PP_CAT( boost_generic_detail_return_type_, num_fun )              \
  : ::boost::mpl::if_c                                                         \
    < BOOST_PP_CAT( boost_generic_detail_requires_are_valid_, num_reqs )       \
      < BoostGenericDetailConceptMap                                           \
      , BoostGenericDetailParams, BoostGenericDetailTypenames                  \
      >::value                                                                 \
    , BOOST_PP_CAT( boost_generic_detail_return_type_impl_, num_fun )          \
      < BoostGenericDetailParams, BoostGenericDetailTypenames >                \
    , ::boost::mpl::identity< ::boost::generic::detail::dummy_type >           \
    >::type {};                                                                \
                                                                               \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_WRAPPED_EMPTY( typename_a )                          \
, BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                                          \
, BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS_NONEMPTY         \
)( param_dets, i, return_type, expression, num_fun                             \
 , typename_p, typename_a, num_reqs                                            \
 )


#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUN_NO_DEF( i, param_dets     \
                                                           , name              \
                                                           , default_          \
                                                           ,trailing_typename_p\
                                                           , typename_a        \
                                                           , num_reqs          \
                                                           )                   \
BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUN_PROVIDED                          \
( i, boost_generic_detail_first_pass, name )

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUN_PROVIDED( i, root, name ) \
template< class BoostGenericDetailConceptMap                                   \
        , class BoostGenericDetailEnabler = void                               \
        >                                                                      \
struct BOOST_PP_CAT( root, name )                                              \
{ typedef ::boost::generic::detail::dummy_type_< i > type; };                  \
                                                                               \
template< class BoostGenericDetailConceptMap >                                 \
struct BOOST_PP_CAT( root, name )                                              \
       < BoostGenericDetailConceptMap                                          \
       , typename ::boost::generic::detail::always_void                        \
         < typename BoostGenericDetailConceptMap::name >::type                 \
       > { typedef typename BoostGenericDetailConceptMap::name type; };

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUN_NO_DEF_( i, param_dets    \
                                                            , root, name       \
                                                            )                  \
template< class BoostGenericDetailConceptMap                                   \
        , class BoostGenericDetailEnabler = void                               \
        >                                                                      \
struct BOOST_PP_CAT( root, name )                                              \
{ typedef ::boost::generic::detail::dummy_type_< i > type; };                  \
                                                                               \
template< class BoostGenericDetailConceptMap >                                 \
struct BOOST_PP_CAT( root, name )                                              \
       < BoostGenericDetailConceptMap                                          \
       , typename ::boost::generic::detail::always_void                        \
         < typename BoostGenericDetailConceptMap::name >::type                 \
       > { typedef typename BoostGenericDetailConceptMap::name type; };


#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUN_WITH_DEF( i, param_dets   \
                                                          , name               \
                                                          , default_           \
                                                          , trailing_typename_p\
                                                          , typename_a         \
                                                          , num_reqs           \
                                                          )                    \
BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUN_PROVIDED                          \
( i, boost_generic_detail_provided, name )                                     \
                                                                               \
template< class BoostGenericDetailParams                                       \
        , class BoostGenericDetailTypenames                                    \
        , class BoostGenericDetailEnabler = void                               \
        >                                                                      \
struct BOOST_PP_CAT( boost_generic_detail_typename_default, name )             \
{ typedef ::boost::generic::detail::dummy_type_< i > type; };                  \
                                                                               \
template< BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets )         \
          BOOST_GENERIC_DETAIL_REMOVE_PAREN( trailing_typename_p )             \
        , class... BoostGenericDetailOtherTypenames                            \
        >                                                                      \
struct BOOST_PP_CAT( boost_generic_detail_typename_default, name )             \
       < boost_generic_detail_params                                           \
         < BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS( param_dets ) >        \
        , ::boost::generic::detail::type_list                                  \
          < BOOST_GENERIC_DETAIL_REMOVE_PAREN( typename_a )                    \
            BOOST_PP_COMMA_IF                                                  \
           ( BOOST_PP_COMPL                                                    \
             ( BOOST_GENERIC_DETAIL_IS_WRAPPED_EMPTY( typename_a ) )           \
           )                                                                   \
           BoostGenericDetailOtherTypenames...                                 \
          >                                                                    \
       , typename ::boost::generic::detail::always_void                        \
         < BOOST_GENERIC_DETAIL_REMOVE_PAREN( default_ ) >::type               \
       >                                                                       \
{                                                                              \
  typedef BOOST_GENERIC_DETAIL_REMOVE_PAREN( default_ ) type;                  \
};                                                                             \
                                                                               \
template< class BoostGenericDetailConceptMap                                   \
        , class BoostGenericDetailParams                                       \
        , class BoostGenericDetailTypenames                                    \
        , class BoostGenericDetailProvidedName                                 \
            = typename BOOST_PP_CAT( boost_generic_detail_provided, name )     \
              < BoostGenericDetailConceptMap >::type                           \
        >                                                                      \
struct BOOST_PP_CAT( boost_generic_detail_first_pass, name )                   \
  : ::boost::mpl::if_c                                                         \
    < ::boost::mpl::and_                                                       \
      < ::boost::generic::detail::is_dummy_type                                \
        < BoostGenericDetailProvidedName >                                     \
      , BOOST_PP_CAT( boost_generic_detail_requires_are_valid_, num_reqs )     \
        < BoostGenericDetailConceptMap                                         \
        , BoostGenericDetailParams, BoostGenericDetailTypenames                \
        >                                                                      \
      >::value                                                                 \
    , BOOST_PP_CAT( boost_generic_detail_typename_default, name )              \
      < BoostGenericDetailParams, BoostGenericDetailTypenames >                \
    , ::boost::mpl::identity< BoostGenericDetailProvidedName >                 \
    >::type {};

// BOOST_GENERIC_DETAIL_EQ_DEFAULT_OR_EMPTY takes:
//   ()
// -or-
//   (default_)
// if (), it yields nothing
// else, it yields = default_
#define BOOST_GENERIC_DETAIL_EQ_DEFAULT_OR_EMPTY( def_or_empty_in_paren )      \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_IS_WRAPPED_EMPTY( def_or_empty_in_paren )   \
            , BOOST_PP_EMPTY                                                   \
            , BOOST_GENERIC_DETAIL_EQ_DEFAULT                                  \
            ) def_or_empty_in_paren

#define BOOST_GENERIC_DETAIL_EQ_DEFAULT( ... ) = __VA_ARGS__

// ToDo: Possibly check axiom syntax somewhere
#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORaxiom( state, concept_, dets, i   \
                                                  , arg                        \
                                                  )                            \
state

#define BOOST_GENERIC_DETAIL_EMULATOR_REQUIRES_ARE_VALID( state, dets, i, arg  \
                                                        , trailing_typename_p  \
                                                        , typename_a           \
                                                        )                      \
template< class BoostGenericDetailParams, class BoostGenericDetailTypenames    \
        , class = void                                                         \
        >                                                                      \
struct BOOST_PP_CAT                                                            \
       ( boost_generic_detail_impl_requires_are_valid_                         \
       , BOOST_PP_INC                                                          \
         ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_REQUIRES( state ) ) \
       ) : ::std::integral_constant< bool, false > {};                         \
                                                                               \
template< BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( dets )               \
          BOOST_GENERIC_DETAIL_REMOVE_PAREN( trailing_typename_p )             \
        , class... BoostGenericDetailOtherTypenames                            \
        >                                                                      \
struct BOOST_PP_CAT                                                            \
       ( boost_generic_detail_impl_requires_are_valid_                         \
       , BOOST_PP_INC                                                          \
         ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_REQUIRES( state ) ) \
       )                                                                       \
       < boost_generic_detail_params                                           \
         < BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS( dets ) >              \
       , ::boost::generic::detail::type_list                                   \
         < BOOST_GENERIC_DETAIL_REMOVE_PAREN( typename_a )                     \
           BOOST_PP_COMMA_IF                                                   \
           ( BOOST_PP_COMPL                                                    \
             ( BOOST_GENERIC_DETAIL_IS_EMPTY                                   \
               ( BOOST_GENERIC_DETAIL_REMOVE_PAREN( typename_a ) )             \
             )                                                                 \
           )                                                                   \
           BoostGenericDetailOtherTypenames...                                 \
         >                                                                     \
       , typename ::boost::generic::detail::always_void                        \
         < BOOST_GENERIC_DETAIL_REMOVE_PAREN( arg ) >::type                    \
       >                                                                       \
  : ::boost::generic::detail::concept_is_valid                                 \
    < BOOST_GENERIC_DETAIL_REMOVE_PAREN( arg ) > {};                           \
                                                                               \
template< class BoostGenericDetailConceptMap                                   \
        , class BoostGenericDetailParams, class BoostGenericDetailTypenames    \
        >                                                                      \
struct BOOST_PP_CAT                                                            \
       ( boost_generic_detail_requires_are_valid_                              \
       , BOOST_PP_INC                                                          \
         ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_REQUIRES( state ) ) \
       )                                                                       \
  : ::boost::mpl::and_                                                         \
    < BOOST_PP_CAT                                                             \
      ( boost_generic_detail_requires_are_valid_                               \
      , BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_REQUIRES( state )      \
      )                                                                        \
      < BoostGenericDetailConceptMap                                           \
      , BoostGenericDetailParams, BoostGenericDetailTypenames                  \
      >                                                                        \
    , BOOST_PP_CAT                                                             \
      ( boost_generic_detail_impl_requires_are_valid_                          \
      , BOOST_PP_INC                                                           \
        ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_REQUIRES( state ) )  \
      )                                                                        \
      < BoostGenericDetailParams, BoostGenericDetailTypenames >                \
    > {};

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPES_NO_DEF( params, name     \
                                                            , typename_a       \
                                                            )                  \
typedef typename BOOST_PP_CAT( boost_generic_detail_first_pass, name )         \
        < BoostGenericDetailConceptMap >::type name;

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPES_WITH_DEF( params, name   \
                                                              , typename_a     \
                                                              )                \
typedef typename BOOST_PP_CAT( boost_generic_detail_first_pass, name )         \
        < BoostGenericDetailConceptMap                                         \
        , boost_generic_detail_params                                          \
          < BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS( params ) >           \
        , ::boost::generic::detail::type_list                                  \
          < BOOST_GENERIC_DETAIL_REMOVE_PAREN( typename_a )                    \
            BOOST_PP_COMMA_IF                                                  \
            ( BOOST_PP_COMPL                                                   \
              ( BOOST_GENERIC_DETAIL_IS_WRAPPED_EMPTY( typename_a ) )          \
            ) void******                                                       \
          >                                                                    \
        >::type name;

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPES( params, name, default_  \
                                                     , typename_a              \
                                                     )                         \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_IS_WRAPPED_EMPTY( default_ )                \
            , BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPES_NO_DEF             \
            , BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPES_WITH_DEF           \
            )( params, name, typename_a )

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORrequires( state, concept_, dets, i\
                                                     , arg                     \
                                                     )                         \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_FIRST_PASS_TYPE_METAFUNCTIONS    \
  (state)                                                                      \
  BOOST_GENERIC_DETAIL_EMULATOR_REQUIRES_ARE_VALID                             \
  ( state, dets, i, arg                                                        \
  ,( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_TYPENAME_PARAMS      \
     ( state )                                                                 \
   )                                                                           \
  , ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TYPENAME_ARGS( state ) )     \
  )                                                                            \
 )                                                                             \
)                                                                              \
BOOST_PP_SEQ_SUBSEQ( state, 1, 3 )                                             \
(( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_CONCEPT_BODY( state )           \
   BOOST_GENERIC_DETAIL_REQUIRES_STATIC_ASSERT( arg )                          \
 )                                                                             \
)                                                                              \
BOOST_PP_SEQ_SUBSEQ( state, 5, 2 )                                             \
(BOOST_PP_INC                                                                  \
 ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_REQUIRES( state ) )         \
)                                                                              \
BOOST_PP_SEQ_REST_N( 8, state )

#define BOOST_GENERIC_DETAIL_EMULATOR_FIRST_PASS_TYPE_META( dets, i, name      \
                                                          , default_           \
                                                          , trailing_typename_p\
                                                          , typename_a         \
                                                          , num_reqs           \
                                                          )                    \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_IS_WRAPPED_EMPTY( default_ )                \
            , BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUN_NO_DEF              \
            , BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUN_WITH_DEF            \
            )( i, dets, name, default_                                         \
             , trailing_typename_p, typename_a, num_reqs                       \
             )

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_DUMMY_DEDUCER( name, num_funs )  \
template< class, class, class >                                                \
struct BOOST_GENERIC_DETAIL_NARY_CAT                                           \
       ( boost_generic_detail_deduce_, num_funs, name )                        \
{                                                                              \
  typedef ::boost::generic::detail::no_deduction type;                         \
};                                                                             \

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORtypename( state, concept_, dets, i\
                                                     , name, default_          \
                                                     )                         \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_FIRST_PASS_TYPE_METAFUNCTIONS    \
  ( state )                                                                    \
  BOOST_GENERIC_DETAIL_EMULATOR_FIRST_PASS_TYPE_META                           \
  ( dets, i, name, default_                                                    \
  , ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_TYPENAME_PARAMS     \
      ( state )                                                                \
    )                                                                          \
  , ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TYPENAME_ARGS( state ) )     \
  , BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_REQUIRES(state)            \
  )                                                                            \
 )                                                                             \
)                                                                              \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_FIRST_PASS_TYPEDEFS( state )     \
  BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPES                                \
  ( dets, name, default_                                                       \
  , ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TYPENAME_ARGS( state ) )     \
  )                                                                            \
 )                                                                             \
)                                                                              \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_DEDUCER_HELPERS( state )         \
  BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_DUMMY_DEDUCER                          \
  ( name, BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ) ) \
))                                                                             \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_CONCEPT_MAP_BODY( state )        \
  BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEF                                          \
  ( name, dets                                                                 \
  , (BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TYPENAME_ARGS( state ))       \
  )                                                                            \
))                                                                             \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_CONCEPT_BODY( state )            \
  BOOST_GENERIC_DETAIL_EMULATOR_STATIC_ASSERT_TYPENAME( concept_, name )       \
))                                                                             \
(( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_TYPENAME_PARAMS(state) \
 , class name                                                                  \
))                                                                             \
(( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_TYPENAME_ARGS(state)   \
 , name                                                                        \
))                                                                             \
BOOST_PP_SEQ_SUBSEQ( state, 7, 2 )                                             \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_IS_VALID_CONDITIONS     \
  ( state )                                                                    \
 , ::boost::generic::detail::is_not_deduction_error< name >                    \
))

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORconstrained_typename( state       \
                                                                 , concept_    \
                                                                 , dets, i     \
                                                                 , constraint  \
                                                                 , name        \
                                                                 , default_    \
                                                                 )             \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_FIRST_PASS_TYPE_METAFUNCTIONS    \
  ( state )                                                                    \
  BOOST_GENERIC_DETAIL_EMULATOR_FIRST_PASS_TYPE_META                           \
  ( dets, i, name, default_                                                    \
  , ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_TYPENAME_PARAMS     \
      ( state )                                                                \
    )                                                                          \
  , ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TYPENAME_ARGS( state ) )     \
  , BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_REQUIRES(state)            \
  )                                                                            \
  BOOST_GENERIC_DETAIL_EMULATOR_REQUIRES_ARE_VALID                             \
  ( state, dets, i, ( constraint< name > )                                     \
  ,( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_TYPENAME_PARAMS      \
     ( state )                                                                 \
   , class name                                                                \
   )                                                                           \
  , ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TYPENAME_ARGS( state )       \
      BOOST_PP_COMMA_IF                                                        \
      ( BOOST_PP_COMPL                                                         \
        ( BOOST_GENERIC_DETAIL_IS_EMPTY                                        \
          ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_TYPENAME_ARGS \
            ( state )                                                          \
          )                                                                    \
        )                                                                      \
      ) name                                                                   \
    )                                                                          \
  )                                                                            \
 )                                                                             \
)                                                                              \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_FIRST_PASS_TYPEDEFS( state )     \
  BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPES                                \
  ( dets, name, default_                                                       \
  , ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TYPENAME_ARGS( state ) )     \
  )                                                                            \
 )                                                                             \
)                                                                              \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_DEDUCER_HELPERS( state )         \
  BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_DUMMY_DEDUCER                          \
  ( name, BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ) ) \
))                                                                             \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_CONCEPT_MAP_BODY( state )        \
  BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEF                                          \
  ( name, dets                                                                 \
  , (BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TYPENAME_ARGS( state ))       \
  )                                                                            \
))                                                                             \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_CONCEPT_BODY( state )            \
  BOOST_GENERIC_DETAIL_EMULATOR_STATIC_ASSERT_CONSTRAINED_TYPENAME             \
  ( concept_, name, constraint )                                               \
))                                                                             \
(( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_TYPENAME_PARAMS(state) \
 , class name                                                                  \
))                                                                             \
(( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_TYPENAME_ARGS(state)   \
 , name                                                                        \
))                                                                             \
(BOOST_PP_INC                                                                  \
 ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_REQUIRES( state ) )         \
)                                                                              \
(BOOST_PP_SEQ_ELEM( 8, state ))                                                \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_IS_VALID_CONDITIONS     \
  ( state )                                                                    \
 , ::boost::generic::detail::is_not_deduction_error< name >                    \
))

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORmember_typename( state, concept_  \
                                                            , dets, i          \
                                                            , this_type, name  \
                                                            , default_         \
                                                            )                  \
state

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORconstrained_member_typename(      \
                                                                     state     \
                                                                   , concept_  \
                                                                   , dets, i   \
                                                                   , constraint\
                                                                   , this_type \
                                                                   , name      \
                                                                   , default_  \
                                                                   )           \
state

#define BOOST_GENERIC_DETAIL_STATIC_ASSERT_STRINGIZE_EXPAND( ... ) __VA_ARGS__

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORfunction( state, concept_, dets, i\
                                                     , return_type, name       \
                                                     , param_dets, default_    \
                                                     )                         \
BOOST_PP_SEQ_SUBSEQ( state, 0, 2 )                                             \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_DEDUCER_HELPERS( state )         \
  template< class BoostGenericDetailBoostGenericDetailT >                      \
  friend typename ::boost::disable_if_c                                        \
  <    sizeof( BoostGenericDetailBoostGenericDetailT )                         \
    == sizeof( BoostGenericDetailBoostGenericDetailT )                         \
  >::type name();                                                              \
  BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS                  \
  ( state, dets, i, return_type                                                \
  , ( name(BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARGS(param_dets)) ) \
  )                                                                            \
))                                                                             \
(BOOST_PP_SEQ_ELEM( 3, state ))                                                \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_CONCEPT_BODY( state )            \
  static_assert                                                                \
  ( ::boost::generic::detail::is_not_dummy_type                                \
    < typename boost_generic_detail_concept_impl                               \
      ::template BOOST_PP_CAT                                                  \
      ( boost_generic_detail_return_type_                                      \
      , BOOST_PP_INC                                                           \
        ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ) ) \
      )                                                                        \
      < boost_generic_detail_completed_concept_map                             \
      , boost_generic_detail_params, boost_generic_detail_typenames            \
      >::type                                                                  \
    >::value                                                                   \
  , "requires "                                                                \
    BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE return_type " "                    \
    BOOST_PP_STRINGIZE( name ) "( "                                            \
    BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                    \
    BOOST_GENERIC_DETAIL_WRAP                                                  \
    ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) ) " )"      \
  );                                                                           \
  static_assert                                                                \
  ( ::boost::mpl::or_                                                          \
    < ::boost::generic::detail::is_dummy_type                                  \
      < typename boost_generic_detail_concept_impl                             \
        ::template BOOST_PP_CAT                                                \
        ( boost_generic_detail_return_type_                                    \
        , BOOST_PP_INC                                                         \
          ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ))\
        )                                                                      \
        < boost_generic_detail_completed_concept_map                           \
        , boost_generic_detail_params, boost_generic_detail_typenames          \
        >::type                                                                \
      >                                                                        \
    , ::boost::generic::detail::is_convertible_or_target_is_void               \
      < typename boost_generic_detail_concept_impl                             \
        ::template BOOST_PP_CAT                                                \
        ( boost_generic_detail_return_type_                                    \
        , BOOST_PP_INC                                                         \
          ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ))\
        )                                                                      \
        < boost_generic_detail_completed_concept_map                           \
        , boost_generic_detail_params, boost_generic_detail_typenames          \
        >::type                                                                \
      , BOOST_GENERIC_DETAIL_REMOVE_PAREN( return_type )                       \
      >                                                                        \
    >::value                                                                   \
  , "the return type of " BOOST_PP_STRINGIZE( name ) "( "                      \
    BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                    \
    BOOST_GENERIC_DETAIL_WRAP                                                  \
    ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) ) " ) "     \
    "is not convertible to "                                                   \
    BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE return_type " "                    \
  );                                                                           \
))                                                                             \
BOOST_PP_SEQ_SUBSEQ( state, 5, 3 )                                             \
(BOOST_PP_INC                                                                  \
 ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ) )        \
)                                                                              \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_IS_VALID_CONDITIONS     \
  ( state )                                                                    \
 , ::boost::generic::detail::is_not_dummy_type                                 \
   < typename BOOST_PP_CAT                                                     \
     ( boost_generic_detail_return_type_                                       \
     , BOOST_PP_INC                                                            \
       ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ) )  \
     )                                                                         \
     < boost_generic_detail_completed_concept_map                              \
     , boost_generic_detail_params_, boost_generic_detail_typenames            \
     >::type                                                                   \
   >                                                                           \
 , ::boost::generic::detail::is_convertible_or_target_is_void                  \
   < typename BOOST_PP_CAT                                                     \
     ( boost_generic_detail_return_type_                                       \
     , BOOST_PP_INC                                                            \
       ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ))   \
     )                                                                         \
     < boost_generic_detail_completed_concept_map                              \
     , boost_generic_detail_params_, boost_generic_detail_typenames            \
     >::type                                                                   \
   , BOOST_GENERIC_DETAIL_REMOVE_PAREN( return_type )                          \
   >                                                                           \
))
#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_ASSOC_FUN_UNCHECKED_RETURN( state\
                                                       , concept_, dets        \
                                                       , i, return_type        \
                                                       , default_, expression  \
                                                       , assert_msg            \
                                                       )                       \
BOOST_PP_SEQ_SUBSEQ( state, 0, 2 )                                             \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_DEDUCER_HELPERS( state )         \
  BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS                  \
  ( state, dets, i, return_type                                                \
  , expression                                                                 \
  )                                                                            \
))                                                                             \
(BOOST_PP_SEQ_ELEM( 3, state ))                                                \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_CONCEPT_BODY( state )            \
  static_assert                                                                \
  ( ::boost::generic::detail::is_not_dummy_type                                \
    < typename boost_generic_detail_concept_impl                               \
      ::template BOOST_PP_CAT                                                  \
      ( boost_generic_detail_return_type_                                      \
      , BOOST_PP_INC                                                           \
        ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ) ) \
      )                                                                        \
      < boost_generic_detail_completed_concept_map                             \
      , boost_generic_detail_params, boost_generic_detail_typenames            \
      >::type                                                                  \
    >::value                                                                   \
  , "requires "                                                                \
    assert_msg                                                                 \
  );                                                                           \
))                                                                             \
BOOST_PP_SEQ_SUBSEQ( state, 5, 3 )                                             \
(BOOST_PP_INC                                                                  \
 ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ) )        \
)                                                                              \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_IS_VALID_CONDITIONS     \
  ( state )                                                                    \
 , ::boost::generic::detail::is_not_dummy_type                                 \
   < typename BOOST_PP_CAT                                                     \
     ( boost_generic_detail_return_type_                                       \
     , BOOST_PP_INC                                                            \
       ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ) )  \
     )                                                                         \
     < boost_generic_detail_completed_concept_map                              \
     , boost_generic_detail_params_, boost_generic_detail_typenames            \
     >::type                                                                   \
   >                                                                           \
))

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_ASSOC_FUN( state, concept_, dets \
                                                       , i, return_type        \
                                                       , default_, expression  \
                                                       , assert_msg            \
                                                       , return_assert_msg     \
                                                       )                       \
BOOST_PP_SEQ_SUBSEQ( state, 0, 2 )                                             \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_DEDUCER_HELPERS( state )         \
  BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS                  \
  ( state, dets, i, return_type                                                \
  , expression                                                                 \
  )                                                                            \
))                                                                             \
(BOOST_PP_SEQ_ELEM( 3, state ))                                                \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_CONCEPT_BODY( state )            \
  static_assert                                                                \
  ( ::boost::generic::detail::is_not_dummy_type                                \
    < typename boost_generic_detail_concept_impl                               \
      ::template BOOST_PP_CAT                                                  \
      ( boost_generic_detail_return_type_                                      \
      , BOOST_PP_INC                                                           \
        ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ) ) \
      )                                                                        \
      < boost_generic_detail_completed_concept_map                             \
      , boost_generic_detail_params, boost_generic_detail_typenames            \
      >::type                                                                  \
    >::value                                                                   \
  , "requires "                                                                \
    assert_msg                                                                 \
  );                                                                           \
  static_assert                                                                \
  ( ::boost::mpl::or_                                                          \
    < ::boost::generic::detail::is_dummy_type                                  \
      < typename boost_generic_detail_concept_impl                             \
        ::template BOOST_PP_CAT                                                \
        ( boost_generic_detail_return_type_                                    \
        , BOOST_PP_INC                                                         \
          ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ))\
        )                                                                      \
        < boost_generic_detail_completed_concept_map                           \
        , boost_generic_detail_params, boost_generic_detail_typenames          \
        >::type                                                                \
      >                                                                        \
    , ::boost::generic::detail::is_convertible_or_target_is_void               \
      < typename boost_generic_detail_concept_impl                             \
        ::template BOOST_PP_CAT                                                \
        ( boost_generic_detail_return_type_                                    \
        , BOOST_PP_INC                                                         \
          ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ))\
        )                                                                      \
        < boost_generic_detail_completed_concept_map                           \
        , boost_generic_detail_params, boost_generic_detail_typenames          \
        >::type                                                                \
      , BOOST_GENERIC_DETAIL_REMOVE_PAREN( return_type )                       \
      >                                                                        \
    >::value                                                                   \
  , "the return type of " return_assert_msg " is not convertible to "          \
    BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE return_type                        \
  );                                                                           \
))                                                                             \
BOOST_PP_SEQ_SUBSEQ( state, 5, 3 )                                             \
(BOOST_PP_INC                                                                  \
 ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ) )        \
)                                                                              \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_IS_VALID_CONDITIONS     \
  ( state )                                                                    \
 , ::boost::generic::detail::is_not_dummy_type                                 \
   < typename BOOST_PP_CAT                                                     \
     ( boost_generic_detail_return_type_                                       \
     , BOOST_PP_INC                                                            \
       ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ) )  \
     )                                                                         \
     < boost_generic_detail_completed_concept_map                              \
     , boost_generic_detail_params_, boost_generic_detail_typenames            \
     >::type                                                                   \
   >                                                                           \
 , ::boost::generic::detail::is_convertible_or_target_is_void                  \
   < typename BOOST_PP_CAT                                                     \
     ( boost_generic_detail_return_type_                                       \
     , BOOST_PP_INC                                                            \
       ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ))   \
     )                                                                         \
     < boost_generic_detail_completed_concept_map                              \
     , boost_generic_detail_params_, boost_generic_detail_typenames            \
     >::type                                                                   \
   , BOOST_GENERIC_DETAIL_REMOVE_PAREN( return_type )                          \
   >                                                                           \
))

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORmember_function( state, concept_  \
                                                            , dets, i          \
                                                            , return_type      \
                                                            , this_type        \
                                                            , name             \
                                                            , param_dets       \
                                                            , default_         \
                                                            )                  \
BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_ASSOC_FUN                                \
( state, concept_, dets, i, return_type, default_                              \
, ( ::std::declval< BOOST_GENERIC_DETAIL_REMOVE_PAREN( this_type ) >()         \
    .name( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARGS(param_dets) )  \
  )                                                                            \
, BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE return_type " "                      \
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE this_type "::"                       \
  BOOST_PP_STRINGIZE( name ) "( "                                              \
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                      \
  BOOST_GENERIC_DETAIL_WRAP                                                    \
  ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) ) " )"        \
, BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE this_type "::"                       \
  BOOST_PP_STRINGIZE( name ) "( "                                              \
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                      \
  BOOST_GENERIC_DETAIL_WRAP                                                    \
  ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) ) " )"        \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORstatic_member_function(           \
                                                                    state      \
                                                                  , concept_   \
                                                                  , dets, i    \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , name       \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_ASSOC_FUN                                \
( state, concept_, dets, i, return_type, default_                              \
, ( BOOST_GENERIC_DETAIL_REMOVE_PAREN( this_type )                             \
    ::name(BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARGS(param_dets))   \
  )                                                                            \
, " static " BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE return_type " "           \
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE this_type "::"                       \
  BOOST_PP_STRINGIZE( name ) "( "                                              \
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                      \
  BOOST_GENERIC_DETAIL_WRAP                                                    \
  ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) ) " )"        \
, BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE this_type "::"                       \
  BOOST_PP_STRINGIZE( name ) "( "                                              \
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                      \
  BOOST_GENERIC_DETAIL_WRAP                                                    \
  ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) ) " )"        \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_ASSOC_OP( state, concept_, dets  \
                                                      , i, return_type         \
                                                      , operator_, param_dets  \
                                                      , default_, expression   \
                                                      )                        \
BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_ASSOC_FUN                                \
( state, concept_, dets, i, return_type, default_                              \
, expression                                                                   \
, BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE return_type " operator "             \
  BOOST_PP_STRINGIZE( operator_ ) "( "                                         \
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                      \
  BOOST_GENERIC_DETAIL_WRAP                                                    \
  ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) ) " )"        \
, "operator "                                                                  \
  BOOST_PP_STRINGIZE( operator_ ) "( "                                         \
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                      \
  BOOST_GENERIC_DETAIL_WRAP                                                    \
  ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) ) " )"        \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORprefix_unary_operator( state      \
                                                                  , concept_   \
                                                                  , dets, i    \
                                                                  , return_type\
                                                                  , operator_  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_ASSOC_OP                                 \
( state, concept_, dets, i, return_type, operator_, param_dets, default_       \
, ( operator_                                                                  \
    BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( param_dets, 0 )     \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORpostfix_unary_operator( state     \
                                                                  , concept_   \
                                                                  , dets, i    \
                                                                  , return_type\
                                                                  , operator_  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_ASSOC_OP                                 \
( state, concept_, dets, i, return_type, operator_, param_dets, default_       \
, ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( param_dets, 0 )     \
    operator_                                                                  \
  )                                                                            \
)


#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORbinary_operator( state, concept_  \
                                                            , dets, i          \
                                                            , return_type      \
                                                            , operator_        \
                                                            , param_dets       \
                                                            , default_         \
                                                            )                  \
BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_ASSOC_OP                                 \
( state, concept_, dets, i, return_type, operator_, param_dets, default_       \
, ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( param_dets, 0 )     \
    operator_                                                                  \
    BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( param_dets, 1 )     \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORcall_operator( state, concept_    \
                                                          , dets, i            \
                                                          , return_type        \
                                                          , param_dets         \
                                                          , default_           \
                                                          )                    \
BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_ASSOC_OP                                 \
( state, concept_, dets, i, return_type, (), param_dets, default_              \
, ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( param_dets, 0 )     \
    ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_FUN_CALL_DECLVAL_ARGS            \
      ( param_dets )                                                           \
    )                                                                          \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORcomma_operator( state, concept_   \
                                                           , dets, i           \
                                                           , return_type       \
                                                           , param_dets        \
                                                           , default_          \
                                                           )                   \
BOOST_PP_SEQ_SUBSEQ( state, 0, 2 )                                             \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_DEDUCER_HELPERS( state )         \
  BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS                  \
  ( state, dets, i, return_type                                                \
  , (   BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( param_dets, 0 ) \
      , BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( param_dets, 1 ) \
    )                                                                          \
  )                                                                            \
))                                                                             \
(BOOST_PP_SEQ_ELEM( 3, state ))                                                \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_CONCEPT_BODY( state )            \
  static_assert                                                                \
  ( ::boost::generic::detail::is_not_dummy_type                                \
    < typename boost_generic_detail_concept_impl                               \
      ::template BOOST_PP_CAT                                                  \
      ( boost_generic_detail_return_type_                                      \
      , BOOST_PP_INC                                                           \
        ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ) ) \
      )                                                                        \
      < boost_generic_detail_completed_concept_map                             \
      , boost_generic_detail_params, boost_generic_detail_typenames            \
      >::type                                                                  \
    >::value                                                                   \
  , "requires "                                                                \
    BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE return_type " operator ,( "        \
    BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                    \
    BOOST_GENERIC_DETAIL_WRAP                                                  \
    ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) ) " )"      \
  );                                                                           \
  static_assert                                                                \
  ( ::boost::mpl::or_                                                          \
    < ::boost::generic::detail::is_dummy_type                                  \
      < typename boost_generic_detail_concept_impl                             \
        ::template BOOST_PP_CAT                                                \
        ( boost_generic_detail_return_type_                                    \
        , BOOST_PP_INC                                                         \
          ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ))\
        )                                                                      \
        < boost_generic_detail_completed_concept_map                           \
        , boost_generic_detail_params, boost_generic_detail_typenames          \
        >::type                                                                \
      >                                                                        \
    , ::boost::generic::detail::is_convertible_or_target_is_void               \
      < typename boost_generic_detail_concept_impl                             \
        ::template BOOST_PP_CAT                                                \
        ( boost_generic_detail_return_type_                                    \
        , BOOST_PP_INC                                                         \
          ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ))\
        )                                                                      \
        < boost_generic_detail_completed_concept_map                           \
        , boost_generic_detail_params, boost_generic_detail_typenames          \
        >::type                                                                \
      , BOOST_GENERIC_DETAIL_REMOVE_PAREN( return_type )                       \
      >                                                                        \
    >::value                                                                   \
  , "the return type of operator ,( "                                          \
    BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                    \
    BOOST_GENERIC_DETAIL_WRAP                                                  \
    ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) ) " ) "     \
    "is not convertible to "                                                   \
    BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE return_type " "                    \
  );                                                                           \
))                                                                             \
BOOST_PP_SEQ_SUBSEQ( state, 5, 3 )                                             \
(BOOST_PP_INC                                                                  \
 ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ) )        \
)                                                                              \
((BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_IS_VALID_CONDITIONS     \
  ( state )                                                                    \
 , ::boost::generic::detail::is_not_dummy_type                                 \
   < typename BOOST_PP_CAT                                                     \
     ( boost_generic_detail_return_type_                                       \
     , BOOST_PP_INC                                                            \
       ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ) )  \
     )                                                                         \
     < boost_generic_detail_completed_concept_map                              \
     , boost_generic_detail_params_, boost_generic_detail_typenames            \
     >::type                                                                   \
   >                                                                           \
 , ::boost::generic::detail::is_convertible_or_target_is_void                  \
   < typename BOOST_PP_CAT                                                     \
     ( boost_generic_detail_return_type_                                       \
     , BOOST_PP_INC                                                            \
       ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state ))   \
     )                                                                         \
     < boost_generic_detail_completed_concept_map                              \
     , boost_generic_detail_params_, boost_generic_detail_typenames            \
     >::type                                                                   \
   , BOOST_GENERIC_DETAIL_REMOVE_PAREN( return_type )                          \
   >                                                                           \
))

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORarrow_operator( state, concept_   \
                                                           , dets, i           \
                                                           , return_type       \
                                                           , param_dets        \
                                                           , default_          \
                                                           )                   \
BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_ASSOC_OP                                 \
( state, concept_, dets, i, return_type, ->, param_dets, default_              \
, ( ::boost::generic::detail::operator_arrow_fun                               \
    < BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_I( param_dets, 0 ) >()     \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORsubscript_operator( state         \
                                                               , concept_      \
                                                               , dets, i       \
                                                               , return_type   \
                                                               , param_dets    \
                                                               , default_      \
                                                               )               \
BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_ASSOC_OP                                 \
( state, concept_, dets, i, return_type, operator_, param_dets, default_       \
, ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( param_dets, 0 )     \
    [BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( param_dets, 1 )]   \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_MEMBER_OPERATOR( state, dets, i  \
                                                             , return_type     \
                                                             , this_type       \
                                                             , operator_       \
                                                             , param_dets      \
                                                             , default_        \
                                                             , expression      \
                                                             )                 \
BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_ASSOC_FUN                                \
( state, concept_, dets, i, return_type, default_                              \
, expression                                                                   \
, BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE return_type " "                      \
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE this_type "::operator "              \
  BOOST_PP_STRINGIZE( operator_ ) "( "                                         \
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                      \
  BOOST_GENERIC_DETAIL_WRAP                                                    \
  ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) ) " )"        \
, BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE this_type "::operator "              \
  BOOST_PP_STRINGIZE( operator_ ) "( "                                         \
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                      \
  BOOST_GENERIC_DETAIL_WRAP                                                    \
  ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) ) " )"        \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORassign_operator( state, concept_  \
                                                            , dets, i          \
                                                            , return_type      \
                                                            , this_type        \
                                                            , param_dets       \
                                                            , default_         \
                                                            )                  \
BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_MEMBER_OPERATOR                          \
( state, dets, i, return_type, this_type, =, param_dets, default_              \
, (   ::std::declval< BOOST_GENERIC_DETAIL_REMOVE_PAREN( this_type )& >()      \
    = BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( param_dets, 0 )   \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORallocation_operator( state        \
                                                                , concept_     \
                                                                , dets, i      \
                                                                , return_type  \
                                                                , this_type    \
                                                                , operator_    \
                                                                , param_dets   \
                                                                , default_     \
                                                                )              \
BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_MEMBER_OPERATOR                          \
( state, dets, i, return_type, this_type, operator_, param_dets, default_      \
, ( ::boost::generic::detail::allocation_operator_fun                          \
    < ::boost::generic::detail::                                               \
      BOOST_PP_CAT( allocation_operator_tag_, operator_ )                      \
    , BOOST_GENERIC_DETAIL_REMOVE_PAREN( this_type )                           \
    , BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_TYPES( param_dets )        \
    >()                                                                        \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORdeallocation_operator( state      \
                                                                  , concept_   \
                                                                  , dets, i    \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , operator_  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_MEMBER_OPERATOR                          \
( state, dets, i, return_type, this_type, operator_, param_dets, default_      \
, ( ::boost::generic::detail::deallocation_operator_fun                        \
    < ::boost::generic::detail::                                               \
      BOOST_PP_CAT( deallocation_operator_tag_, operator_ )                    \
    , BOOST_GENERIC_DETAIL_REMOVE_PAREN( this_type )                           \
    , BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_TYPES( param_dets )        \
    >()                                                                        \
  )                                                                            \
)

// ToDo: Fix this to only construct explicitly if not 1 argument
#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORconstructor( state, concept_, dets\
                                                        , i, this_type         \
                                                        , param_dets, default_ \
                                                        )                      \
BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_ASSOC_FUN_UNCHECKED_RETURN               \
( state, concept_, dets, i, this_type, default_                                \
, ( ( ::boost::generic::detail::constructor_fun                                \
      < BOOST_GENERIC_DETAIL_REMOVE_PAREN( this_type )                         \
      , ::boost::generic::detail::type_list                                    \
         < BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_TYPES( param_dets ) > \
      >()                                                                      \
    )                                                                          \
  )                                                                            \
, BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE this_type "::"                       \
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE this_type "( "                       \
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                      \
  BOOST_GENERIC_DETAIL_WRAP                                                    \
  ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) ) " )"        \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORexplicit_constructor( state       \
                                                                 , concept_    \
                                                                 , dets, i     \
                                                                 , this_type   \
                                                                 , param_dets  \
                                                                 , default_    \
                                                                 )             \
BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_ASSOC_FUN_UNCHECKED_RETURN               \
( state, concept_, dets, i, this_type, default_                                \
, ( ( ::boost::generic::detail::constructor_fun                                \
      < BOOST_GENERIC_DETAIL_REMOVE_PAREN( this_type )                         \
      , ::boost::generic::detail::type_list                                    \
         < BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_TYPES( param_dets ) > \
      >()                                                                      \
    )                                                                          \
  )                                                                            \
, "explicit " BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE this_type "::"           \
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE this_type "( "                       \
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                      \
  BOOST_GENERIC_DETAIL_WRAP                                                    \
  ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) ) " )"        \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORdestructor( state, concept_, dets \
                                                       , i, this_type, default_\
                                                       )                       \
BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_ASSOC_FUN_UNCHECKED_RETURN               \
( state, concept_, dets, i, ( void ), default_                                 \
, ( ::boost::generic::detail::destructor_fun                                   \
    < BOOST_GENERIC_DETAIL_REMOVE_PAREN( this_type ) >()                       \
  )                                                                            \
, BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE this_type "::~"                      \
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE this_type "()"                       \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORconversion( state, concept_, dets \
                                                       , i, target_type        \
                                                       , param_dets, default_  \
                                                       )                       \
BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_ASSOC_FUN_UNCHECKED_RETURN               \
( state, concept_, dets, i, target_type, default_                              \
, ( ( typename ::std::enable_if                                                \
      < ::std::is_convertible                                                  \
        < BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_I( param_dets, 0 )     \
        , BOOST_GENERIC_DETAIL_REMOVE_PAREN( target_type )                     \
        >::value                                                               \
      , int                                                                    \
      >::type()                                                                \
    )                                                                          \
  )                                                                            \
, "operator " BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE target_type "( "         \
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                      \
  BOOST_GENERIC_DETAIL_WRAP                                                    \
  ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) ) " )"        \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATORexplicit_conversion( state        \
                                                                , concept_     \
                                                                , dets         \
                                                                , i            \
                                                                , target_type  \
                                                                , param_dets   \
                                                                , default_     \
                                                                )              \
BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_ASSOC_FUN_UNCHECKED_RETURN               \
( state, concept_, dets, i, target_type, default_                              \
, ( ( typename ::boost::generic::detail::identity_unless_void                  \
      < BOOST_GENERIC_DETAIL_REMOVE_PAREN( target_type ) >::type               \
    )                                                                          \
    BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( param_dets, 0 )     \
  )                                                                            \
, "explicit operator " BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE target_type "( "\
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                      \
  BOOST_GENERIC_DETAIL_WRAP                                                    \
  ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) ) " )"        \
)

#endif // BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_HPP
