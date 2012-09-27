/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_HPP
#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_HPP

#include <boost/generic/detail/always_void.hpp>
#include <boost/generic/detail/dummy_type.hpp>
#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/nary_cat.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/type.hpp>
#include <boost/generic/detail/variadic_empty.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/utility/enable_if.hpp>
#include <utility>

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS( param_dets\
                                                                  , name_seq   \
                                                                  , i          \
                                                                  , return_type\
                                                                  , expression \
                                                                  )            \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_EMPTY( name_seq )                                    \
, BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                                          \
, BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS_                 \
)( param_dets, name_seq, i, return_type, expression )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS_MAC( r     \
                                                                       , data  \
                                                                       , elem  \
                                                                       )       \
static ::boost::generic::detail::type_< ::boost::generic::detail::dummy_type > \
BOOST_GENERIC_DETAIL_NARY_CAT                                                  \
( boost_generic_detail_fun_deducer_                                            \
, BOOST_PP_SEQ_ELEM( 0, data ), _, BOOST_PP_SEQ_ELEM( 0, elem )                \
)                                                                              \
( ... );                                                                       \
                                                                               \
template< class BOOST_PP_SEQ_ELEM( 1, elem ) >                                 \
static ::boost::generic::detail::type_< BOOST_PP_SEQ_ELEM( 1, elem ) >         \
BOOST_GENERIC_DETAIL_NARY_CAT                                                  \
( boost_generic_detail_fun_deducer_                                            \
, BOOST_PP_SEQ_ELEM( 0, data ), _, BOOST_PP_SEQ_ELEM( 0, elem )                \
)                                                                              \
BOOST_PP_SEQ_ELEM( 1, data );                                                  \
                                                                               \
template< BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS                       \
          ( BOOST_PP_SEQ_ELEM( 2, data ) )                                     \
        , class BoostGenericDetailEnabler = void                               \
        >                                                                      \
struct BOOST_GENERIC_DETAIL_NARY_CAT( boost_generic_detail_deduce_             \
                                    , BOOST_PP_SEQ_ELEM( 0, data ), _          \
                                    , BOOST_PP_SEQ_ELEM( 0, elem )             \
                                    )                                          \
  : ::boost::mpl::identity                                                     \
    < decltype( BOOST_GENERIC_DETAIL_NARY_CAT                                  \
                ( boost_generic_detail_fun_deducer_                            \
                , BOOST_PP_SEQ_ELEM( 0, data ), _                              \
                , BOOST_PP_SEQ_ELEM( 0, elem )                                 \
                )                                                              \
                ( ::boost::generic::detail::void_safe_declval                  \
                  < typename BOOST_PP_CAT( boost_generic_detail_return_type_   \
                                         , BOOST_PP_SEQ_ELEM( 0, data )        \
                                         )                                     \
                    < BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS             \
                      ( BOOST_PP_SEQ_ELEM( 2, data ) )                         \
                    >::type                                                    \
                  >()                                                          \
                )                                                              \
              )                                                                \
    >::type {};

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS_(          \
                                                                     param_dets\
                                                                  , name_seq   \
                                                                  , i          \
                                                                  , return_type\
                                                                  , expression \
                                                                  )            \
template< BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets )         \
        , class BoostGenericDetailEnabler = void                               \
        >                                                                      \
struct BOOST_PP_CAT( boost_generic_detail_return_type_, i )                    \
{ typedef ::boost::generic::detail::dummy_type type; };                        \
                                                                               \
template< BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) >       \
struct BOOST_PP_CAT( boost_generic_detail_return_type_, i )                    \
       < BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS( param_dets )            \
       , typename ::boost::generic::detail::always_void                        \
         < decltype expression >::type                                         \
       > { typedef decltype expression type; };                                \
                                                                               \
BOOST_PP_SEQ_FOR_EACH                                                          \
( BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS_MAC              \
, (i)(return_type)(param_dets)                                                 \
, name_seq                                                                     \
)

// Note: d here is:
// (concept_param_dets)((typename_seq))
// where typename_seq is either empty or a sequence with each element as:
// (unique_index)(typename_name)

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERaxiom( ... )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERrequires( ... )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERtypename( ... )


#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERconstrained_typename( ... )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERmember_typename( ... )


// ToDo: Define
#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERconstrained_member_typename(\
                                                                   ... )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERfunction( i, d, return_type \
                                                           , name, param_dets  \
                                                           , default_          \
                                                           )                   \
template< class T >                                                            \
friend typename ::boost::disable_if_c< sizeof(T) == sizeof(T) >::type name();  \
                                                                               \
BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS                    \
( BOOST_PP_SEQ_ELEM( 0, d )                                                    \
, BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) ), i            \
, return_type                                                                  \
, ( name( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARGS(param_dets) ) ) \
)

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERmember_function(            \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , name       \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS                    \
( BOOST_PP_SEQ_ELEM( 0, d )                                                    \
, BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) ), i            \
, return_type                                                                  \
, ( ::std::declval< BOOST_GENERIC_DETAIL_REMOVE_PAREN( this_type ) >()         \
      .name( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARGS(param_dets) )\
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERstatic_member_function(     \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , name       \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS                    \
( BOOST_PP_SEQ_ELEM( 0, d )                                                    \
, BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) ), i            \
, return_type                                                                  \
, ( BOOST_GENERIC_DETAIL_REMOVE_PAREN( this_type )                             \
    ::name( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARGS(param_dets) ) \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERprefix_unary_operator( i, d \
                                                                  , return_type\
                                                                  , operator_  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS                    \
( BOOST_PP_SEQ_ELEM( 0, d )                                                    \
, BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) ), i            \
, return_type                                                                  \
, ( operator_                                                                  \
    BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( param_dets, 0 )     \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERpostfix_unary_operator( i, d\
                                                                  , return_type\
                                                                  , operator_  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS                    \
( BOOST_PP_SEQ_ELEM( 0, d )                                                    \
, BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) ), i            \
, return_type                                                                  \
, ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( param_dets, 0 )     \
    operator_                                                                  \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERbinary_operator( i, d       \
                                                                  , return_type\
                                                                  , operator_  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS                    \
( BOOST_PP_SEQ_ELEM( 0, d )                                                    \
, BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) ), i            \
, return_type                                                                  \
, ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( param_dets, 0 )     \
    operator_                                                                  \
    BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( param_dets, 1 )     \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERcall_operator( i, d         \
                                                                , return_type  \
                                                                , param_dets   \
                                                                , default_     \
                                                                )              \
BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS                    \
( BOOST_PP_SEQ_ELEM( 0, d )                                                    \
, BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) ), i            \
, return_type                                                                  \
, ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( param_dets, 0 )     \
    ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_FUN_CALL_DECLVAL_ARGS            \
      ( param_dets )                                                           \
    )                                                                          \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERcomma_operator( i, d        \
                                                                 , return_type \
                                                                 , param_dets  \
                                                                 , default_    \
                                                                 )             \
BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS                    \
( BOOST_PP_SEQ_ELEM( 0, d )                                                    \
, BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) ), i            \
, return_type                                                                  \
, ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( param_dets, 0 )     \
  , BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( param_dets, 1 )     \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERarrow_operator( i, d        \
                                                                 , return_type \
                                                                 , param_dets  \
                                                                 , default_    \
                                                                 )             \
TODO_DEFINE_THIS

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERsubscript_operator(         \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS                    \
( BOOST_PP_SEQ_ELEM( 0, d )                                                    \
, BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) ), i            \
, return_type                                                                  \
, ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( param_dets, 0 )     \
    [BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( param_dets, 1 )]   \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERassign_operator( i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_CREATE_DEDUCERS                    \
( BOOST_PP_SEQ_ELEM( 0, d )                                                    \
, BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) ), i            \
, return_type                                                                  \
, (   ::std::declval< BOOST_GENERIC_DETAIL_REMOVE_PAREN( this_type )& >()      \
    = BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( param_dets, 0 )   \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERallocation_operator(        \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , operator_  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERdeallocation_operator(      \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , operator_  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERconstructor( i, d           \
                                                               , this_type     \
                                                               , param_dets    \
                                                               , default_      \
                                                               )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERexplicit_constructor(       \
                                                                     i, d      \
                                                                   , this_type \
                                                                   , param_dets\
                                                                   , default_  \
                                                                   )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERdestructor( i, d, this_type \
                                                             , default_        \
                                                             )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERconversion( i, d            \
                                                              , target_type    \
                                                              , param_dets     \
                                                              , default_       \
                                                              )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPERexplicit_conversion(        \
                                                                    i, d       \
                                                                  , target_type\
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )

#endif // BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_HELPER_HPP
