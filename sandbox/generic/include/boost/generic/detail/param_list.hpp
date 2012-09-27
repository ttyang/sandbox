/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_PARAM_LIST_HPP
#define BOOST_GENERIC_DETAIL_PARAM_LIST_HPP

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS
#include <utility>
#endif

#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/list/fold_left.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/generic/detail/eat.hpp>
#include <boost/generic/detail/eat_part_after_paren.hpp>
#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/is_parenthesized.hpp>
#include <boost/generic/detail/num_args.hpp>
#include <boost/generic/detail/num_args_is_1.hpp>
#include <boost/generic/detail/params_for_each.hpp>
#include <boost/generic/detail/params_to_list.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/rescan.hpp>
#include <boost/generic/detail/simplify_variadic_param_list.hpp>
#include <boost/generic/detail/tail_arguments.hpp>
#include <boost/generic/detail/variadic_empty.hpp>
#include <boost/generic/detail/variadic_identity.hpp>

// Takes a suspected parameter list and yields a sequence result of the form
// (parenthesized_bit)(validity_bit)(void_bit)((param_part))((post_param_part))
// where parenthesized_bit is 1 if the argument starts parenthesized, else 0
// where validity_bit is 1 if the paramaeter list is valid, else 0
// where void_bit is 1 if the paramaeter list is nullary, else 0
// where (param_part) is a parenthesized param list
// where (post_param_part) is the part after the parameter list, parenthesized
// Note: the (param_part) element will not exist if the param list is invalid
// Note: A parameter list is of the form
//       ( (type) param_name, (other_type) other_param_name ... ) qualifiers
// Note: A void parameter list must be specified as ()
#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS( ... )                         \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( __VA_ARGS__ )                     \
, BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IMPL                                 \
, BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_NOT_PARENTHESIZED                    \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_AFTER_RESCAN( ... )            \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_AFTER_RESCAN_( (__VA_ARGS__) )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_AFTER_RESCAN_( ... )           \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS __VA_ARGS__

// Macros used to extract information from the yielded value of the above macro
#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_PARENTHESIZED( dets )       \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID( dets )               \
BOOST_PP_SEQ_ELEM( 1, dets )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID( dets )                \
BOOST_PP_SEQ_ELEM( 2, dets )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_LIST_PART( dets )        \
BOOST_PP_SEQ_ELEM( 3, dets )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_LIST_PART_AS_ARRAY(dets) \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_NUM_PARAMS( dets )                   \
, BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_LIST_PART( dets )              \
)

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_NUM_PARAMS( dets )             \
BOOST_GENERIC_DETAIL_NUM_WRAPPED_ARGS                                          \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_LIST_PART( dets ) )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID_TEMPLATE_PARAMS(dets) \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID( dets )                     \
, BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID_TEMPLATE_PARAMS_IMPL        \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                                  \
)( dets )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID_TEMPLATE_PARAMS_IMPL( \
                                                                           dets\
                                                                          )    \
BOOST_PP_COMPL                                                                 \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_HAS_POST_PARAM_LIST_PART( dets ) )

#if 0

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARE_ALL_CLASS_OR_TYPENAME(dets)\
BOOST_GENERIC_DETAIL_ARE_ALL_CLASS_OR_TYPENAME                                 \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_LIST_PART( dets ) )

#endif

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_POST_PARAM_LIST_PART( dets )   \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 4, dets ) )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_HAS_POST_PARAM_LIST_PART(dets) \
BOOST_PP_COMPL                                                                 \
( BOOST_GENERIC_DETAIL_IS_EMPTY                                                \
  ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_POST_PARAM_LIST_PART( dets ) )     \
)

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( dets )                 \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID( dets )          \
            , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                              \
            , BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS_IMPL              \
            )( dets )

#if 0

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_FORCED_NAME_PARAMS( dets, id ) \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID( dets )          \
            , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                              \
            , BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_FORCED_NAME_PARAMS_IMPL  \
            )( dets, id )

#endif

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_FORCED_NAME_ARGS( dets, id )   \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID( dets )          \
            , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                              \
            , BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_FORCED_NAME_ARGS_IMPL    \
            )( dets, id )

#if 0

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_AUGMENTED_PARAMS( dets, aug )  \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID( dets )          \
            , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                              \
            , BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_AUGMENTED_PARAMS_IMPL    \
            )( dets, aug )

#endif

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_EMPTY_NAME_AND_PARAMS( dets    \
                                                                     , name    \
                                                                     )         \
name()

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_NAME_AND_PARAMS_IMPL(dets,name)\
name( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( dets ) )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_NAME_AND_PARAMS( dets, name )  \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID( dets )          \
            , BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_EMPTY_NAME_AND_PARAMS    \
            , BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_NAME_AND_PARAMS_IMPL     \
            )( dets, name )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS_IMPL( dets )            \
BOOST_GENERIC_DETAIL_PARAMS                                                    \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_LIST_PART( dets ) )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_FORCED_NAME_PARAMS_IMPL( dets  \
                                                                       , id    \
                                                                       )       \
BOOST_GENERIC_DETAIL_FORCED_NAME_PARAMS                                        \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_LIST_PART( dets ), id )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_FORCED_NAME_ARGS_IMPL( dets    \
                                                                     , id      \
                                                                     )         \
BOOST_GENERIC_DETAIL_FORCED_NAME_ARGS                                          \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_LIST_PART( dets ), id )

#if 0

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_AUGMENTED_PARAMS_IMPL( dets    \
                                                                     , aug     \
                                                                     )         \
BOOST_GENERIC_DETAIL_AUGMENTED_PARAMS                                          \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_LIST_PART( dets ), aug )

#endif

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_TRAILING_PARAM_LIST( dets )    \
BOOST_PP_COMMA_IF                                                              \
( BOOST_PP_COMPL                                                               \
  ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID( dets ) )                  \
)                                                                              \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( dets )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS( dets )                   \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID( dets )          \
            , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                              \
            , BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS_IMPL                \
            )( dets )

#if 0

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_AUGMENTED_ARGS( dets, aug )    \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID( dets )          \
            , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                              \
            , BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_AUGMENTED_ARGS_IMPL      \
            )( dets, aug )

#endif

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS_IMPL( dets )              \
BOOST_GENERIC_DETAIL_ARGS                                                      \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_LIST_PART( dets ) )

#if 0

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_AUGMENTED_ARGS_IMPL( dets, aug)\
BOOST_GENERIC_DETAIL_AUGMENTED_ARGS                                            \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_LIST_PART( dets ), aug )

#endif

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_TRAILING_ARGS( dets )          \
BOOST_PP_COMMA_IF                                                              \
( BOOST_PP_COMPL                                                               \
  ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID( dets ) )                  \
)                                                                              \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS( dets )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_TYPES( dets )            \
BOOST_GENERIC_DETAIL_PARAM_TYPES                                               \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_LIST_PART( dets ) )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_TRAILING_PARAM_TYPES( dets )   \
BOOST_PP_COMMA_IF                                                              \
( BOOST_PP_COMPL                                                               \
  ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID( dets ) )                  \
)                                                                              \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_TYPES( dets )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARGS( dets )           \
BOOST_GENERIC_DETAIL_DECLVAL_ARGS                                              \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_LIST_PART( dets ) )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_FUN_CALL_DECLVAL_ARGS( dets )  \
BOOST_GENERIC_DETAIL_FUN_CALL_DECLVAL_ARGS                                     \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_LIST_PART( dets ) )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_I( dets, i )             \
BOOST_GENERIC_DETAIL_PARAM_TYPES_MACRO                                         \
( s, ~, 0                                                                      \
, BOOST_PP_ARRAY_ELEM                                                          \
  ( i, BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_LIST_PART_AS_ARRAY(dets) )\
)

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( dets, i )       \
BOOST_GENERIC_DETAIL_DECLVAL_ARGS_MACRO                                        \
( s, ~, 0                                                                      \
, BOOST_PP_ARRAY_ELEM                                                          \
  ( i, BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_LIST_PART_AS_ARRAY(dets) )\
)

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_TRAILING_DECLVAL_ARGS( dets )  \
BOOST_PP_COMMA_IF                                                              \
( BOOST_PP_COMPL                                                               \
  ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID( dets ) )                  \
)                                                                              \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARGS( dets )

// param_list is guaranteed to start parenthesized at this point
#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IMPL( ... )                    \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_EMPTY                                                \
  ( BOOST_GENERIC_DETAIL_REMOVE_PAREN                                          \
    ( BOOST_GENERIC_DETAIL_EAT_PART_AFTER_PAREN( __VA_ARGS__ ) )               \
  )                                                                            \
, BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_VOID_IMPL                            \
, BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_NONVOID_IMPL                         \
)( __VA_ARGS__ )

// Used to check validity when a nonbasic void parameter list is expected
#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_NONVOID_IMPL( ... )            \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED                                    \
  ( BOOST_GENERIC_DETAIL_HEAD_WRAPPED_ARGUMENT                                 \
    ( BOOST_GENERIC_DETAIL_EAT_PART_AFTER_PAREN( __VA_ARGS__ ) )               \
  )                                                                            \
, BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_NONBASIC_NONVOID_IMPL                \
, BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_INVALID_IMPL                         \
)( __VA_ARGS__ )

// Used to check validity when a nonbasic void parameter list is expected
#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_VOID_IMPL( ... )               \
( 1 )                                                                          \
( 1 )                                                                          \
( 1 )                                                                          \
( () )                                                                         \
( ( BOOST_GENERIC_DETAIL_EAT __VA_ARGS__ ) )

// The macro that yields the result for a nonbasic, nonvoid parameter list
#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_NONBASIC_NONVOID_IMPL( ... )   \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID_NONBASIC_IMPL( __VA_ARGS__ )\
, BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_FULLY_NONBASIC                       \
, BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_INVALID_IMPL                         \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_FULLY_NONBASIC_RESCAN( ... )   \
__VA_ARGS__

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_FULLY_NONBASIC( ... )          \
( 1 )( 1 )( 0 )                                                                \
( ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_FULLY_NONBASIC_RESCAN              \
    ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_SIMPLIFY_VARIADIC                \
      BOOST_GENERIC_DETAIL_EAT_PART_AFTER_PAREN( __VA_ARGS__ )                 \
    )                                                                          \
  )                                                                            \
)                                                                              \
( ( BOOST_GENERIC_DETAIL_EAT __VA_ARGS__ ) )





#if 0

#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_SIMPLIFY_VARIADIC_IMPL( ... )  \
if num_args > 3
  if empty( tail( args ) ) && empty( tail( tail( args) ) )
    eat_part_after_parent( head( args ) ) boost_generic_detail_variadic part_after_paren( head ) eat_variadic
  else
    head( args ) dont_eat_variadic
  ( tail( args ) )

#endif





// Yields 1 if a parameter list is fully nonbasic, else 0
#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID_NONBASIC_IMPL( ... )  \
BOOST_PP_LIST_FOLD_LEFT                                                        \
( BOOST_GENERIC_DETAIL_IS_NONBASIC_PARAM, 1                                    \
, BOOST_GENERIC_DETAIL_PARAMS_TO_LIST                                          \
  ( BOOST_GENERIC_DETAIL_EAT_PART_AFTER_PAREN( __VA_ARGS__ ) )                 \
)

// The macro that checks if a parameter is a valid nonbasic param
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_PARAM( s, state, param )              \
BOOST_PP_BITAND                                                                \
( state                                                                        \
, BOOST_PP_IIF                                                                 \
  ( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( param )                         \
  , BOOST_GENERIC_DETAIL_IS_NONBASIC_PARAM_IMPL                                \
  , BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                                \
  )( param )                                                                   \
)

#define BOOST_GENERIC_DETAIL_IS_NONBASIC_PARAM_IMPL( param )                   \
BOOST_PP_COMPL                                                                 \
( BOOST_GENERIC_DETAIL_IS_EMPTY                                                \
  ( BOOST_GENERIC_DETAIL_REMOVE_PAREN                                          \
    ( BOOST_GENERIC_DETAIL_EAT_PART_AFTER_PAREN( param ) )                     \
  )                                                                            \
)

// The macro that yields the result when the argument wasn't parenthesized
#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_NOT_PARENTHESIZED( ... )       \
( 0 )( 0 )( 0 )(())(())

// The macro that yields the result when the argument was partially nonbasic
#define BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_INVALID_IMPL( ... )            \
( 1 )( 0 )( 0 )                                                                \
( BOOST_GENERIC_DETAIL_EAT_PART_AFTER_PAREN( __VA_ARGS__ ) )                   \
( ( BOOST_GENERIC_DETAIL_EAT __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_PARAM_TYPES_MACRO( s, data, i, elem )             \
BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_KIND( elem )

#define BOOST_GENERIC_DETAIL_ARGS_MACRO( s, data, i, elem )                    \
BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_PASS_ARG( elem )

#define BOOST_GENERIC_DETAIL_FORCED_NAME_ARGS_MACRO( s, id, i, elem )          \
BOOST_GENERIC_DETAIL_FORCED_NAME_ARGS_MACRO_                                   \
( id, i, BOOST_GENERIC_DETAIL_EAT elem )

#define BOOST_GENERIC_DETAIL_FORCED_NAME_ARGS_MACRO_( id, i, elem )            \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_IS_EMPTY( elem )                            \
            , BOOST_GENERIC_DETAIL_FORCED_NAME_ARGS_MACRO_EMPTY                \
            , BOOST_GENERIC_DETAIL_FORCED_NAME_ARGS_MACRO_NONEMPTY             \
            )( id, i, elem )

#define BOOST_GENERIC_DETAIL_FORCED_NAME_ARGS_MACRO_EMPTY( id, i, elem )       \
BOOST_PP_CAT( id, i )

#define BOOST_GENERIC_DETAIL_FORCED_NAME_ARGS_MACRO_NONEMPTY( id, i, elem )    \
elem

#if 0

#define BOOST_GENERIC_DETAIL_AUGMENTED_ARGS_MACRO( s, aug, i, elem )           \
BOOST_PP_CAT( BOOST_GENERIC_DETAIL_EAT elem, aug )

#endif

#define BOOST_GENERIC_DETAIL_PARAMS_MACRO( s, data, i, elem )                  \
BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_KIND( elem )                             \
BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_NAME( elem )

#if 0

#define BOOST_GENERIC_DETAIL_FORCED_NAME_PARAMS_MACRO( s, id, i, elem )        \
BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_KIND
BOOST_GENERIC_DETAIL_FORCED_NAME_ARGS_MACRO( s, id, i, elem )

#endif

#if 0

#define BOOST_GENERIC_DETAIL_AUGMENTED_PARAMS_MACRO( s, data, i, elem )        \
BOOST_GENERIC_DETAIL_PARAM_TYPES_MACRO( s, data, i, elem )                     \
BOOST_GENERIC_DETAIL_AUGMENTED_ARGS_MACRO( s, data, i, elem )

#endif

#define BOOST_GENERIC_DETAIL_DECLVAL_ARGS_MACRO( s, data, i, elem )            \
::std::declval< BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_KIND_NAME( elem ) >()    \
BOOST_GENERIC_DETAIL_SIMPLIFIED_PARAM_DDD_IF_VARIADIC( elem )

#define BOOST_GENERIC_DETAIL_PARAM_TYPES( params )                             \
BOOST_GENERIC_DETAIL_PARAMS_ENUM                                               \
( BOOST_GENERIC_DETAIL_PARAM_TYPES_MACRO, ~                                    \
, params                                                                       \
)

#define BOOST_GENERIC_DETAIL_ARGS( params )                                    \
BOOST_GENERIC_DETAIL_PARAMS_ENUM                                               \
( BOOST_GENERIC_DETAIL_ARGS_MACRO, ~                                           \
, params                                                                       \
)

#if 0

#define BOOST_GENERIC_DETAIL_AUGMENTED_ARGS( params, aug )                     \
BOOST_GENERIC_DETAIL_PARAMS_ENUM                                               \
( BOOST_GENERIC_DETAIL_AUGMENTED_ARGS_MACRO, aug                               \
, params                                                                       \
)

#endif

#define BOOST_GENERIC_DETAIL_PARAMS( params )                                  \
BOOST_GENERIC_DETAIL_PARAMS_ENUM                                               \
( BOOST_GENERIC_DETAIL_PARAMS_MACRO, ~                                         \
, params                                                                       \
)

#if 0

#define BOOST_GENERIC_DETAIL_FORCED_NAME_PARAMS( params, id )                  \
BOOST_GENERIC_DETAIL_PARAMS_ENUM                                               \
( BOOST_GENERIC_DETAIL_FORCED_NAME_PARAMS_MACRO, id                            \
, params                                                                       \
)

#endif

#if 0

#define BOOST_GENERIC_DETAIL_FORCED_NAME_ARGS( params, id )                    \
BOOST_GENERIC_DETAIL_PARAMS_ENUM                                               \
( BOOST_GENERIC_DETAIL_FORCED_NAME_ARGS_MACRO, id                              \
, params                                                                       \
)

#endif

#if 0

#define BOOST_GENERIC_DETAIL_AUGMENTED_PARAMS( params, aug )                   \
BOOST_GENERIC_DETAIL_PARAMS_ENUM                                               \
( BOOST_GENERIC_DETAIL_AUGMENTED_PARAMS_MACRO, aug                             \
, params                                                                       \
)

#endif

#define BOOST_GENERIC_DETAIL_DECLVAL_ARGS( params )                            \
BOOST_GENERIC_DETAIL_PARAMS_ENUM                                               \
( BOOST_GENERIC_DETAIL_DECLVAL_ARGS_MACRO, ~                                   \
, params                                                                       \
)

#define BOOST_GENERIC_DETAIL_FUN_CALL_DECLVAL_ARGS( params )                   \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_NUM_WRAPPED_ARGS_IS_1( params )                         \
, BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                                          \
, BOOST_GENERIC_DETAIL_FUN_CALL_DECLVAL_ARGS_IMPL                              \
)( params )

#define BOOST_GENERIC_DETAIL_FUN_CALL_DECLVAL_ARGS_IMPL( params )              \
BOOST_GENERIC_DETAIL_DECLVAL_ARGS                                              \
( ( BOOST_GENERIC_DETAIL_TAIL_WRAPPED_ARGUMENTS( params ) ) )

// ToDo: Optimize this by not calling BOOST_GENERIC_DETAIL_PARAM_TYPES
#define BOOST_GENERIC_DETAIL_ARE_ALL_CLASS_OR_TYPENAME( params )               \
BOOST_PP_LIST_FOLD_LEFT                                                        \
( BOOST_GENERIC_DETAIL_IS_CLASS_OR_TYPENAME_MACRO, 1                           \
, BOOST_GENERIC_DETAIL_PARAMS_TO_LIST                                          \
  ( ( BOOST_GENERIC_DETAIL_PARAM_TYPES( params ) ) )                           \
)

#define BOOST_GENERIC_DETAIL_IS_CLASS_OR_TYPENAME_MACRO( d, state, param )     \
BOOST_PP_BITAND                                                                \
( state                                                                        \
, BOOST_PP_EQUAL                                                               \
  ( BOOST_GENERIC_DETAIL_NUM_ARGS_AFTER_RESCAN                                 \
    ( BOOST_PP_CAT( BOOST_GENERIC_DETAIL_IS_CLASS_OR_TYPENAME_HELPER_          \
                  , param                                                      \
                  )                                                            \
    )                                                                          \
  , 2                                                                          \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_IS_CLASS_OR_TYPENAME_HELPER_class    _1, _2
#define BOOST_GENERIC_DETAIL_IS_CLASS_OR_TYPENAME_HELPER_typename _1, _2

#endif // BOOST_GENERIC_DETAIL_PARAM_LIST_HPP
