#ifndef BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETAILS_HPP
#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETAILS_HPP

#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/is_parenthesized.hpp>
#include <boost/generic/detail/num_args.hpp>
#include <boost/generic/detail/operator_dets.hpp>
#include <boost/generic/detail/param_list.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/seq_details.hpp>
#include <boost/generic/detail/starts_empty_or_parenthesized.hpp>
#include <boost/generic/detail/this_mem_dets.hpp>
#include <boost/generic/detail/variadic_empty.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/seq/elem.hpp>

// ToDo: Add support for trailing return type declarations and templates
// A function decl is of the form:
//   optional_static (return_type)( name )( params ) qualifiers, {default_impl}
// Specifiers are optional, and a comma and default implementation is optional

// Result format is
//   (validity_bit)((return_type))(name)(param_list_details)((default_impl_))
//   (is_partial_bit)((error_msg_seq))(nested_name_dets)(operator_dets)
// default_impl is empty if none is provided, otherwise it's a parenthesized
// definition
#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS( ... )                         \
BOOST_PP_IIF                                                                   \
( BOOST_PP_EQUAL( BOOST_GENERIC_DETAIL_NUM_ARGS( __VA_ARGS__ ), 1 )            \
, BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_NO_DEF                          \
, BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_NOT_1_PARAM                     \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_WRAPPED_FUNCTION_DECL_DETS( wrapped_arg )         \
BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS wrapped_arg

// expands to:
// macro(validity_bit, (return_type), name, param_list_details
//      , (definition) -or- empty parameter if no defition
//      )
#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_VISIT( dets, valid_macro       \
                                                     , invalid_macro           \
                                                     )                         \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_VALID( dets )         \
            , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_VISIT_IMPL_VALID         \
            , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_VISIT_IMPL_INVALID       \
            )( dets, valid_macro, invalid_macro )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_VISIT_IMPL_VALID( dets         \
                                                                , valid_macro  \
                                                                , invalid_macro\
                                                                )              \
valid_macro( ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_RETURN_TYPE( dets ) )   \
           , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_NAME( dets )              \
           , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_PARAM_LIST_DETS( dets )   \
           , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_DEFINITION_IMPL( dets )   \
           )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_VISIT_IMPL_INVALID( dets       \
                                                                  , valid_macro\
                                                                  , inv_macro  \
                                                                  )            \
inv_macro( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_ERRORS( dets ) )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_VALID( dets )               \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_RETURN_TYPE( dets )            \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, dets ) )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_RAW_NAME( dets )               \
BOOST_PP_SEQ_ELEM( 2, dets )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_NAME( dets )                   \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_MEMBER_FUNCTION(dets) \
            , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_NAME_                    \
            , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_RAW_NAME                 \
            )( dets )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_NAME_( dets )                  \
BOOST_GENERIC_DETAIL_THIS_MEM_DETS_NAME                                        \
( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_THIS_MEM_DETS( dets ) )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_THIS_TYPE( dets )              \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_MEMBER_FUNCTION(dets) \
            , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_THIS_TYPE_               \
            , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                              \
            )( dets )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_THIS_TYPE_( dets )             \
BOOST_GENERIC_DETAIL_THIS_MEM_DETS_TYPE                                        \
( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_THIS_MEM_DETS( dets ) )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_VALID( dets )               \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_VALID_WITHOUT_DEFINITION(   \
                                                                         dets )\
BOOST_PP_BITAND                                                                \
( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_VALID( dets )                     \
, BOOST_PP_COMPL                                                               \
  ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_HAS_DEFINITION( dets ) )           \
)

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_PARTIAL( dets )             \
BOOST_PP_SEQ_ELEM( 5, dets )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_THIS_MEM_DETS( dets )          \
BOOST_PP_SEQ_ELEM( 7, dets )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_OPERATOR_DETS( dets )          \
BOOST_PP_SEQ_ELEM( 8, dets )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_MEMBER_OPERATOR_NAME( dets )   \
BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_NAME                                 \
( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_OPERATOR_DETS( dets ) )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_NONMEMBER_OPERATOR_NAME( dets )\
BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_NAME                              \
( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_OPERATOR_DETS( dets ) )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_OPERATOR_NAME( dets )          \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_MEMBER_FUNCTION( dets )           \
, BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_NAME                               \
, BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_NAME                            \
)( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_OPERATOR_DETS( dets ) )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_OPERATOR( dets )               \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_MEMBER_FUNCTION( dets )           \
, BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_MEMBER_OPERATOR                      \
, BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_NONMEMBER_OPERATOR                   \
)( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_OPERATOR_DETS( dets ) )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_MEMBER_OPERATOR( dets )        \
BOOST_GENERIC_DETAIL_OPERATOR                                                  \
( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_MEMBER_OPERATOR_NAME( dets ) )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_NONMEMBER_OPERATOR( dets )     \
BOOST_GENERIC_DETAIL_OPERATOR                                                  \
( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_NONMEMBER_OPERATOR_NAME( dets ) )

// ToDo: Fix this once static member function requirements are implemented
#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_STATIC( dets ) 0

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_MEMBER_FUNCTION( dets )     \
BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IS_VALID                                    \
( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_THIS_MEM_DETS( dets ) )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_OPERATOR( dets )            \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_MEMBER_FUNCTION( dets )           \
, BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IS_VALID                           \
, BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IS_VALID                        \
)( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_OPERATOR_DETS( dets ) )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_ERRORS( dets )                 \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 6, dets ) )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_HAS_ERRORS( dets )             \
BOOST_PP_COMPL                                                                 \
( BOOST_GENERIC_DETAIL_IS_EMPTY                                                \
  ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_ERRORS( dets ) )                   \
)

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_RETURN_TYPE( dets )            \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, dets ) )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_PARAM_LIST_DETS( dets )        \
BOOST_PP_SEQ_ELEM( 3, dets )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_DEFINITION( dets )             \
BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_DEFINITION_IMPL( dets )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_HAS_DEFINITION( dets )         \
BOOST_PP_COMPL                                                                 \
( BOOST_GENERIC_DETAIL_IS_EMPTY                                                \
  ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_DEFINITION_IMPL( dets ) )          \
)

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_DEFINITION_IMPL( dets )        \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 4, dets ) )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_NO_DEF( arg )             \
BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_WITH_DEF                          \
( BOOST_GENERIC_DETAIL_SEQ_DETS( arg ), )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_NOT_1_PARAM( ... )        \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_IS_EMPTY( __VA_ARGS__ )                     \
            , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_INVALID             \
            , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_WITH_2_PARAMS       \
            )( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_WITH_2_PARAMS( seq, ... ) \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_EMPTY_OR_PARENTHESIZED( __VA_ARGS__ )            \
, BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_INVALID                         \
, BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_WITH_DEF                        \
)( BOOST_GENERIC_DETAIL_SEQ_DETS( seq ), __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_WITH_DEF( dets, ... )     \
BOOST_PP_IIF                                                                   \
( BOOST_PP_EQUAL( BOOST_GENERIC_DETAIL_SEQ_DETS_SIZE( dets ), 3 )              \
, BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_WITH_DEF_IMPL                   \
, BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_PARTIAL                         \
)( BOOST_GENERIC_DETAIL_SEQ_DETS_SEQ( dets )                                   \
 , BOOST_GENERIC_DETAIL_SEQ_DETS_EXTRA_DATA( dets )                            \
 , __VA_ARGS__                                                                 \
 )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_WITH_DEF_IMPL(seq,ex,...) \
BOOST_PP_IIF                                                                   \
( BOOST_PP_BITAND                                                              \
  ( BOOST_PP_COMPL                                                             \
    ( BOOST_GENERIC_DETAIL_IS_WRAPPED_EMPTY( BOOST_PP_SEQ_ELEM( 0, seq ) ) )   \
  , BOOST_PP_EQUAL                                                             \
    ( BOOST_GENERIC_DETAIL_NUM_WRAPPED_ARGS( BOOST_PP_SEQ_ELEM( 1, seq ) ), 1 )\
  )                                                                            \
, BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_CHECK_PARAMS                    \
, BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_PARTIAL                         \
)( seq                                                                         \
 , BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS( BOOST_PP_SEQ_ELEM( 2, seq ) ex )   \
 , __VA_ARGS__                                                                 \
 )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_CHECK_PARAMS( seq         \
                                                              , param_dets, ...\
                                                              )                \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID( param_dets )   \
            , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_VALID_STRUCTURE     \
            , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_PARTIAL             \
            )( BOOST_PP_SEQ_ELEM( 0, seq )                                     \
             , BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, seq ) )\
             , param_dets                                                      \
             , __VA_ARGS__                                                     \
             )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_VALID_STRUCTURE(          \
                                                                    return_type\
                                                                  , name       \
                                                                  , param_dets \
                                                                  , ...        \
                                                                  )            \
BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_VALID_STRUCTURE_                  \
( return_type, name, param_dets, BOOST_GENERIC_DETAIL_THIS_MEM_DETS( name )    \
, __VA_ARGS__                                                                  \
)

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_VALID_STRUCTURE_(         \
                                                                  return_type  \
                                                                , name         \
                                                                , param_dets   \
                                                                , this_mem_dets\
                                                                , ...          \
                                                                )              \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IS_VALID( this_mem_dets )     \
            , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_MEMBER              \
            , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_NONMEMBER           \
            )( return_type, name, param_dets, this_mem_dets, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_MEMBER( return_type, name \
                                                           , param_dets        \
                                                           , this_mem_dets     \
                                                           , ...               \
                                                           )                   \
BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_MEMBER_                           \
( return_type, name, param_dets, this_mem_dets                                 \
, BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS                                    \
  ( BOOST_GENERIC_DETAIL_THIS_MEM_DETS_NAME( this_mem_dets ) )                 \
, __VA_ARGS__                                                                  \
)

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_MEMBER_( return_type, name\
                                                            , param_dets       \
                                                            , this_mem_dets    \
                                                            , op_dets          \
                                                            , ...              \
                                                            )                  \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IS_VALID( op_dets )                \
, BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_MEMBER_OP                       \
, BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_MEMBER_NONOP                    \
)( return_type, name, param_dets, this_mem_dets, op_dets, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_MEMBER_OP( return_type    \
                                                              , name           \
                                                              , param_dets     \
                                                              , this_mem_dets  \
                                                              , op_dets        \
                                                              , ...            \
                                                              )                \
(1)                                                                            \
(return_type)                                                                  \
(name)                                                                         \
(param_dets)                                                                   \
((__VA_ARGS__))                                                                \
(1)                                                                            \
(())                                                                           \
(this_mem_dets)                                                                \
(op_dets)

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_MEMBER_NONOP( return_type \
                                                                , name         \
                                                                , param_dets   \
                                                                , this_mem_dets\
                                                                , op_dets      \
                                                                , ...          \
                                                                )              \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IS_PARTIAL( op_dets )              \
, BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_MEMBER_BADOP                    \
, BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_MEMBER_VALID                    \
)( return_type, name, param_dets, this_mem_dets, op_dets, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_MEMBER_BADOP( return_type \
                                                                , name         \
                                                                , param_dets   \
                                                                , this_mem_dets\
                                                                , op_dets      \
                                                                , ...          \
                                                                )              \
(0)                                                                            \
(return_type)                                                                  \
(name)                                                                         \
(param_dets)                                                                   \
((__VA_ARGS__))                                                                \
(1)                                                                            \
(())                                                                           \
(this_mem_dets)                                                                \
(op_dets)

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_MEMBER_VALID( return_type \
                                                                , name         \
                                                                , param_dets   \
                                                                , this_mem_dets\
                                                                , op_dets      \
                                                                , ...          \
                                                                )              \
(1)                                                                            \
(return_type)                                                                  \
(name)                                                                         \
(param_dets)                                                                   \
((__VA_ARGS__))                                                                \
(1)                                                                            \
(())                                                                           \
(this_mem_dets)                                                                \
(op_dets)

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_NONMEMBER( return_type    \
                                                              , name           \
                                                              , param_dets     \
                                                              , this_mem_dets  \
                                                              , ...            \
                                                              )                \
BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_NONMEMBER_                        \
( return_type, name, param_dets, this_mem_dets                                 \
, BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS( name )                         \
, __VA_ARGS__                                                                  \
)

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_NONMEMBER_( return_type   \
                                                               , name          \
                                                               , param_dets    \
                                                               , this_mem_dets \
                                                               , op_dets       \
                                                               , ...           \
                                                               )               \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IS_VALID( op_dets )             \
, BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_NONMEMBER_OP                    \
, BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_NONOP                           \
)( return_type, name, param_dets, this_mem_dets, op_dets, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_NONMEMBER_OP( return_type \
                                                                , name         \
                                                                , param_dets   \
                                                                , this_mem_dets\
                                                                , op_dets      \
                                                                , ...          \
                                                                )              \
(1)                                                                            \
(return_type)                                                                  \
(name)                                                                         \
(param_dets)                                                                   \
((__VA_ARGS__))                                                                \
(1)                                                                            \
(())                                                                           \
(this_mem_dets)                                                                \
(op_dets)

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_NONOP( return_type, name  \
                                                          , param_dets         \
                                                          , this_mem_dets      \
                                                          , op_dets            \
                                                          , ...                \
                                                          )                    \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IS_PARTIAL( op_dets )           \
, BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_BADOP                           \
, BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_VALID                           \
)( return_type, name, param_dets, this_mem_dets, op_dets, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_BADOP( return_type, name  \
                                                          , param_dets         \
                                                          , this_mem_dets      \
                                                          , op_dets            \
                                                          , ...                \
                                                          )                    \
(0)                                                                            \
(return_type)                                                                  \
(name)                                                                         \
(param_dets)                                                                   \
((__VA_ARGS__))                                                                \
(1)                                                                            \
(())                                                                           \
(this_mem_dets)                                                                \
(op_dets)

#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_VALID( return_type, name  \
                                                          , param_dets         \
                                                          , this_mem_dets      \
                                                          , op_dets            \
                                                          , ...                \
                                                          )                    \
(1)                                                                            \
(return_type)                                                                  \
(name)                                                                         \
(param_dets)                                                                   \
((__VA_ARGS__))                                                                \
(1)                                                                            \
(())                                                                           \
(this_mem_dets)                                                                \
(op_dets)

// ToDo: Chang param dets struct member to invalid params
#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_INVALID( ... )            \
(0)                                                                            \
((return_type_of_invalid_function_decl))                                       \
(name_of_invalid_function_decl)                                                \
(())                                                                           \
(())                                                                           \
(0)                                                                            \
((("Invalid function declaration.")))

// ToDo: Chang param dets struct member to invalid params
#define BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IMPL_PARTIAL( ... )            \
(0)                                                                            \
((return_type_of_invalid_function_decl))                                       \
(name_of_invalid_function_decl)                                                \
(())                                                                           \
(())                                                                           \
(1)                                                                            \
((("Invalid function declaration.")))

#endif // BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETAILS_HPP
