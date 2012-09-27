#ifndef BOOST_GENERIC_DETAIL_NO_RETURN_DETS_HPP
#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_HPP

#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/num_args_is_1.hpp>
#include <boost/generic/detail/num_args_is_2.hpp>
#include <boost/generic/detail/param_list.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/rescan.hpp>
#include <boost/generic/detail/seq_details.hpp>
#include <boost/generic/detail/starts_empty_or_parenthesized.hpp>
#include <boost/generic/detail/operator_dets.hpp>
#include <boost/generic/detail/this_mem_dets.hpp>
#include <boost/generic/detail/variadic_cat.hpp>
#include <boost/generic/detail/variadic_identity.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/seq/elem.hpp>

// No returns are either constructors, destructors, or conversion operators
// They are of the form:
//   optional_explicit (this(T))( params ) post_param_stuff
// -or-
//   (this(T) destroy)( params ) post_param_stuff
// -or-
//   optional_explicit (operator something)( params ) post_param_stuff
// Yields a result of the form:
//  (validity_bit)(partial_bit)(is_explicit_bit)
//  (is_constructor_bit)(is_destructor_bit)(is_conversion_bit)
//  (param_dets)(this_type_or_target_type)((def_or_empty))
#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS( ... )                             \
BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL                                       \
( BOOST_GENERIC_DETAIL_STARTS_WITH_EXPLICIT( __VA_ARGS__ ), __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_WRAPPED_NO_RETURN_DETS( wrapped_arg )             \
BOOST_GENERIC_DETAIL_NO_RETURN_DETS wrapped_arg

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL( is_explicit, ... )           \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_NUM_ARGS_IS_1( __VA_ARGS__ )                            \
, BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_NO_DEF                              \
, BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_NOT_1_PARAM                         \
)( is_explicit                                                                 \
 , BOOST_PP_IIF( is_explicit                                                   \
               , BOOST_GENERIC_DETAIL_EAT_EXPLICIT                             \
               , BOOST_GENERIC_DETAIL_SELF                                     \
               )( __VA_ARGS__ )                                                \
 )

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_VALID( dets )                   \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_PARTIAL( dets )                 \
BOOST_PP_SEQ_ELEM( 1, dets )

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_EXPLICIT( dets )                \
BOOST_PP_SEQ_ELEM( 2, dets )

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_CONSTRUCTOR( dets )             \
BOOST_PP_SEQ_ELEM( 3, dets )

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_DESTRUCTOR( dets )              \
BOOST_PP_SEQ_ELEM( 4, dets )

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_CONVERSION( dets )              \
BOOST_PP_SEQ_ELEM( 5, dets )

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_PARAM_DETS( dets )                 \
BOOST_PP_SEQ_ELEM( 6, dets )

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_THIS_TYPE( dets )                  \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 7, dets ) )

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_TARGET_TYPE                        \
BOOST_GENERIC_DETAIL_NO_RETURN_DETS_THIS_TYPE

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_DEFINITION( dets )                 \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 8, dets ) )

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_HAS_DEFINITION( dets )             \
BOOST_GENERIC_DETAIL_IS_EMPTY                                                  \
( BOOST_GENERIC_DETAIL_NO_RETURN_DETS_DEFINITION( dets ) )

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_NO_DEF( is_explicit, arg )    \
BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_WITH_DEF                              \
( is_explicit, BOOST_GENERIC_DETAIL_SEQ_DETS( arg ), )

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_NOT_1_PARAM(is_explicit,...)  \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_IS_EMPTY( __VA_ARGS__ )                     \
            , BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_INVALID                 \
            , BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_WITH_2_PARAMS           \
            )( is_explicit, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_INVALID( ... )                \
(0)(0)(0)(0)(0)(0)(~)(~)(())

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_PARTIAL( ... )                \
(0)(1)(0)(0)(0)(0)(~)(~)(())

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_WITH_2_PARAMS( is_exp, seq    \
                                                              , ...            \
                                                              )                \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_EMPTY_OR_PARENTHESIZED( __VA_ARGS__ )            \
, BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_INVALID                             \
, BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_WITH_DEF                            \
)( is_exp, BOOST_GENERIC_DETAIL_SEQ_DETS( seq ), __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_WITH_DEF(is_exp,seq_dets,...) \
BOOST_PP_IIF                                                                   \
( BOOST_PP_EQUAL( BOOST_GENERIC_DETAIL_SEQ_DETS_SIZE( seq_dets ), 2 )          \
, BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_WITH_DEF_IMPL                       \
, BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_INVALID                             \
)( is_exp                                                                      \
 , BOOST_GENERIC_DETAIL_SEQ_DETS_SEQ( seq_dets )                               \
 , BOOST_GENERIC_DETAIL_SEQ_DETS_EXTRA_DATA( seq_dets )                        \
 , __VA_ARGS__                                                                 \
 )

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_WITH_DEF_IMPL( is_exp, seq, ex\
                                                              , ...            \
                                                              )                \
BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_CHECK_PARAMS                          \
( is_exp, seq                                                                  \
, BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_AFTER_RESCAN                         \
  ( BOOST_PP_SEQ_ELEM( 1, seq ) ex )                                           \
, __VA_ARGS__                                                                  \
)

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_CHECK_PARAMS( is_exp, seq     \
                                                             , param_dets, ... \
                                                             )                 \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID( param_dets )   \
            , BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_VALID_STRUCTURE         \
            , BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_PARTIAL                 \
            )( is_exp                                                          \
             , BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, seq ) )\
             , param_dets                                                      \
             , __VA_ARGS__                                                     \
             )

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_VALID_STRUCTURE( is_exp, name \
                                                                , param_dets   \
                                                                , ...          \
                                                                )              \
BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_VALID_STRUCTURE_                      \
( is_exp, name, param_dets, BOOST_GENERIC_DETAIL_THIS_MEM_DETS( name )         \
, __VA_ARGS__                                                                  \
)

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_VALID_STRUCTURE_( is_exp, name\
                                                                , param_dets   \
                                                                , this_mem_dets\
                                                                , ...          \
                                                                )              \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IS_PARTIAL( this_mem_dets )   \
            , BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_MEMBER                  \
            , BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_NONMEMBER               \
            )( is_exp, name, param_dets, this_mem_dets, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_MEMBER( is_exp, name          \
                                                       , param_dets            \
                                                       , this_mem_dets, ...    \
                                                       )                       \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IS_VALID( this_mem_dets )                 \
, BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_MEMBER_                             \
, BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_PARTIAL                             \
)( is_exp, name, param_dets, this_mem_dets, __VA_ARGS__ )


#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_MEMBER_( is_exp, name         \
                                                        , param_dets           \
                                                        , this_mem_dets, ...   \
                                                        )                      \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_EMPTY                                                \
  ( BOOST_GENERIC_DETAIL_THIS_MEM_DETS_NAME( this_mem_dets ) )                 \
, BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_CONSTRUCTOR                         \
, BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_NOT_CONSTRUCTOR                     \
)( is_exp, name, param_dets, this_mem_dets, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_CONSTRUCTOR( is_exp, name     \
                                                            , param_dets       \
                                                            , this_mem_dets    \
                                                            , ...              \
                                                            )                  \
(1)(1)(is_exp)(1)(0)(0)(param_dets)                                            \
( ( BOOST_GENERIC_DETAIL_THIS_MEM_DETS_TYPE( this_mem_dets ) ) )               \
((__VA_ARGS__))

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_NOT_CONSTRUCTOR( is_exp, name \
                                                                , param_dets   \
                                                                , this_mem_dets\
                                                                , ...          \
                                                                )              \
BOOST_PP_IIF                                                                   \
( BOOST_PP_BITAND                                                              \
  ( BOOST_GENERIC_DETAIL_IS_DESTROY                                            \
    ( BOOST_GENERIC_DETAIL_THIS_MEM_DETS_NAME( this_mem_dets ) )               \
  , BOOST_PP_COMPL( is_exp )                                                   \
  )                                                                            \
, BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_DESTRUCTOR                          \
, BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_PARTIAL                             \
)( name, param_dets, this_mem_dets, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_DESTRUCTOR( name, param_dets  \
                                                           , this_mem_dets     \
                                                           , ...               \
                                                           )                   \
(1)(1)(0)(0)(1)(0)(param_dets)                                                 \
( ( BOOST_GENERIC_DETAIL_THIS_MEM_DETS_TYPE( this_mem_dets ) ) )               \
((__VA_ARGS__))

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_NONMEMBER( is_exp, name       \
                                                          , param_dets         \
                                                          , this_mem_dets, ... \
                                                          )                    \
BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_NONMEMBER_                            \
( is_exp, name, param_dets, this_mem_dets                                      \
, BOOST_GENERIC_DETAIL_CONVERSION_OPERATOR_DETS( name )                        \
, __VA_ARGS__                                                                  \
)

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_NONMEMBER_( is_exp, name      \
                                                           , param_dets        \
                                                           , this_mem_dets     \
                                                           , op_dets, ...      \
                                                           )                   \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_CONVERSION_OPERATOR_DETS_IS_PARTIAL( op_dets )          \
, BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_CONVERSION_OP                       \
, BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_PARTIAL                             \
)( is_exp, name, param_dets, this_mem_dets, op_dets, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_CONVERSION_OP( is_exp, name   \
                                                              , param_dets     \
                                                              , this_mem_dets  \
                                                              , op_dets, ...   \
                                                              )                \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_CONVERSION_OPERATOR_DETS_IS_VALID( op_dets )            \
, BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_VALID_CONVERSION                    \
, BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_PARTIAL                             \
)( is_exp, name, param_dets, this_mem_dets, op_dets, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IMPL_VALID_CONVERSION( is_exp, name\
                                                                , param_dets   \
                                                                , this_mem_dets\
                                                                , op_dets, ... \
                                                                )              \
(1)(1)(is_exp)(0)(0)(1)(param_dets)                                            \
((BOOST_GENERIC_DETAIL_CONVERSION_OPERATOR_DETS_TYPE(op_dets)))                \
((__VA_ARGS__))

// Begin "is destroy" macros
#define BOOST_GENERIC_DETAIL_IS_DESTROY( ... )                                 \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_WITH_DESTROY( __VA_ARGS__ )                      \
, BOOST_GENERIC_DETAIL_IS_DESTROY_                                             \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                                  \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_IS_DESTROY_( ... )                                \
BOOST_GENERIC_DETAIL_IS_EMPTY( BOOST_GENERIC_DETAIL_EAT_DESTROY( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_STARTS_WITH_DESTROY( ... )                        \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_EMPTY_OR_PARENTHESIZED( __VA_ARGS__ )            \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                                  \
, BOOST_GENERIC_DETAIL_STARTS_WITH_DESTROY_IMPL                                \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_STARTS_WITH_DESTROY_IMPL( ... )                   \
BOOST_GENERIC_DETAIL_NUM_ARGS_AFTER_RESCAN_IS_2                                \
( BOOST_GENERIC_DETAIL_VARIADIC_CAT                                            \
  ( BOOST_GENERIC_DETAIL_STARTS_WITH_DESTROY                                   \
  , BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ )                          \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_STARTS_WITH_DESTROYdestroy ,

// Begin "eat destroy" macros
#define BOOST_GENERIC_DETAIL_EAT_DESTROY( ... )                                \
BOOST_GENERIC_DETAIL_VARIADIC_CAT                                              \
( BOOST_GENERIC_DETAIL_EAT_DESTROY, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_EAT_DESTROYdestroy

// Begin "starts with explicit" macros
#define BOOST_GENERIC_DETAIL_IS_EXPLICIT( ... )                                \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_WITH_EXPLICIT( __VA_ARGS__ )                     \
, BOOST_GENERIC_DETAIL_IS_EXPLICIT_                                            \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                                  \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_IS_EXPLICIT_( ... )                               \
BOOST_GENERIC_DETAIL_IS_EMPTY                                                  \
( BOOST_GENERIC_DETAIL_EAT_EXPLICIT( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_STARTS_WITH_EXPLICIT( ... )                       \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_EMPTY_OR_PARENTHESIZED( __VA_ARGS__ )            \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                                  \
, BOOST_GENERIC_DETAIL_STARTS_WITH_EXPLICIT_IMPL                               \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_STARTS_WITH_EXPLICIT_IMPL( ... )                  \
BOOST_GENERIC_DETAIL_NUM_ARGS_AFTER_RESCAN_IS_2                                \
( BOOST_GENERIC_DETAIL_VARIADIC_CAT                                            \
  ( BOOST_GENERIC_DETAIL_STARTS_WITH_EXPLICIT                                  \
  , BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ )                          \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_STARTS_WITH_EXPLICITexplicit ,

// Begin "eat explicit" macros
#define BOOST_GENERIC_DETAIL_EAT_EXPLICIT( ... )                               \
BOOST_GENERIC_DETAIL_VARIADIC_CAT                                              \
( BOOST_GENERIC_DETAIL_EAT_EXPLICIT, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_EAT_EXPLICITexplicit

#endif // BOOST_GENERIC_DETAIL_NO_RETURN_DETS_HPP
