/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_TYPENAME_DETAILS_HPP
#define BOOST_GENERIC_DETAIL_TYPENAME_DETAILS_HPP

#include <boost/generic/detail/eat.hpp>
#include <boost/generic/detail/eat_part_after_paren.hpp>
#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/is_parenthesized.hpp>
#include <boost/generic/detail/num_args.hpp>
#include <boost/generic/detail/num_args_is_1.hpp>
#include <boost/generic/detail/num_args_is_2.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/starts_empty_or_parenthesized.hpp>
#include <boost/generic/detail/this_mem_dets.hpp>
#include <boost/generic/detail/variadic_cat.hpp>
#include <boost/generic/detail/variadic_empty.hpp>
#include <boost/generic/detail/variadic_identity.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/seq/elem.hpp>

// a typename requirement is specified as:
//   typename name
// -or-
//   typename name, default_type

// Result is of the form:
// (validity_bit)(name)((default_value_in_paren_or_empty))(is_partial_bit)
// ((error_msg_seq))(nested_dets)((constraint))
#define BOOST_GENERIC_DETAIL_TYPENAME_DETS( ... )                              \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_WITH_TYPENAME( __VA_ARGS__ )                     \
, BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_IS_TYPENAME                          \
, BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_NO_TYPENAME                          \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_NO_TYPENAME( ... )             \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( __VA_ARGS__ )         \
            , BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_CONSTRAINED_TYPENAME     \
            , BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_INVALID                  \
            )( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_CONSTRAINED_TYPENAME( ... )    \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED                                    \
  ( BOOST_GENERIC_DETAIL_EAT_WRAPPED( __VA_ARGS__ ) )                          \
, BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_INVALID                              \
, BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_CONSTRAINED_TYPENAME_                \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_CONSTRAINED_TYPENAME_( ... )   \
BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_IS_TYPENAME_                           \
( BOOST_GENERIC_DETAIL_EAT_PART_AFTER_PAREN( __VA_ARGS__ )                     \
, __VA_ARGS__                                                                  \
)

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_CONSTRAINED_TYPENAME_IMPL(     \
                                                                     constraint\
                                                                   , ...       \
                                                                   )           \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_NUM_WRAPPED_ARGS_IS_1( constraint )         \
            , BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_IS_TYPENAME_             \
            , BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_PARTIAL                  \
            )( constraint, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_WRAPPED_TYPENAME_DETS( wrapped_arg )              \
BOOST_GENERIC_DETAIL_TYPENAME_DETS wrapped_arg

// expands to macro( validity_bit, name, empty_or_default_in_paren )
// ToDo: pass error data as well for visitation
#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_VISIT(dets, valid_macro, inv_macro) \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_VALID( dets )              \
            , BOOST_GENERIC_DETAIL_TYPENAME_DETS_VISIT_IMPL_VALID              \
            , BOOST_GENERIC_DETAIL_TYPENAME_DETS_VISIT_IMPL_INVALID            \
            )( dets, valid_macro, invalid_macro )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_VISIT_IMPL_VALID( dets, valid_macro \
                                                           , inv_macro         \
                                                           )                   \
valid_macro( BOOST_GENERIC_DETAIL_TYPENAME_DETS_NAME( dets )                   \
           , BOOST_GENERIC_DETAIL_TYPENAME_DETS_DEFAULT( dets )                \
           )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_VISIT_IMPL_INVALID( dets            \
                                                             , valid_macro     \
                                                             , inv_macro       \
                                                             )                 \
inv_macro( BOOST_GENERIC_DETAIL_TYPENAME_DETS_ERRORS( dets ) )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_VISIT_VALID( dets, macro )          \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_VALID( dets )              \
            , macro                                                            \
            , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                              \
            )( BOOST_GENERIC_DETAIL_TYPENAME_DETS_NAME( name )                 \
             , BOOST_GENERIC_DETAIL_TYPENAME_DETS_DEFAULT( name )              \
             )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_VISIT_INVALID( dets, macro )        \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_VALID( dets )              \
            , macro                                                            \
            , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                              \
            )( BOOST_GENERIC_DETAIL_TYPENAME_DETS_NAME( name )                 \
             , BOOST_GENERIC_DETAIL_TYPENAME_DETS_DEFAULT( name )              \
             )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_IS_TYPENAME( ... )             \
BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_IS_TYPENAME_                           \
( (), __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_IS_TYPENAME_( constraint, ... )\
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_NUM_ARGS_IS_1( __VA_ARGS__ )                            \
, BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_NO_DEF                               \
, BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_NOT_1_PARAM                          \
)( constraint, BOOST_GENERIC_DETAIL_EAT_TYPENAME_OR_CONSTRAINT( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_VALID( dets )                    \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_NESTED_DETS( dets )                 \
BOOST_PP_SEQ_ELEM( 5, dets )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_NESTED( dets )                   \
BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IS_VALID                                    \
( BOOST_GENERIC_DETAIL_TYPENAME_DETS_NESTED_DETS( dets ) )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_TYPE( dets )                        \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_NESTED( dets )                         \
, BOOST_GENERIC_DETAIL_TYPENAME_DETS_TYPE_                                     \
, BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                                          \
)( dets )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_TYPE_( dets )                       \
BOOST_GENERIC_DETAIL_THIS_MEM_DETS_TYPE                                        \
( BOOST_GENERIC_DETAIL_TYPENAME_DETS_NESTED_DETS( dets ) )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_VALID_WITHOUT_DEFAULT( dets )    \
BOOST_PP_BITAND                                                                \
( BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_VALID( dets )                          \
, BOOST_PP_COMPL( BOOST_GENERIC_DETAIL_TYPENAME_DETS_HAS_DEFAULT( dets ) )     \
)

// ToDo: Properly define this once constraints are implemented
#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_CONSTRAINT( dets )                  \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 6, dets ) )

// ToDo: Properly define this once constraints are implemented
#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_CONSTRAINED( dets )              \
BOOST_PP_COMPL                                                                 \
( BOOST_GENERIC_DETAIL_IS_EMPTY                                                \
  ( BOOST_GENERIC_DETAIL_TYPENAME_DETS_CONSTRAINT( dets ) )                    \
)

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_NAME( dets )                        \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_NESTED( dets )             \
            , BOOST_GENERIC_DETAIL_TYPENAME_DETS_NAME_NESTED                   \
            , BOOST_GENERIC_DETAIL_TYPENAME_DETS_NAME_NONNESTED                \
            )( dets )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_NAME_NESTED( dets )                 \
BOOST_GENERIC_DETAIL_THIS_MEM_DETS_NAME                                        \
( BOOST_GENERIC_DETAIL_TYPENAME_DETS_NESTED_DETS( dets ) )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_NAME_NONNESTED( dets )              \
BOOST_PP_SEQ_ELEM( 1, dets )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_PARTIAL( dets )                  \
BOOST_PP_SEQ_ELEM( 3, dets )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_ERRORS( dets )                      \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 4, dets ) )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_HAS_ERRORS( dets )                  \
BOOST_PP_COMPL                                                                 \
( BOOST_GENERIC_DETAIL_IS_EMPTY                                                \
  ( BOOST_GENERIC_DETAIL_TYPENAME_DETS_ERRORS( dets ) )                        \
)

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_HAS_DEFAULT( dets )                 \
BOOST_PP_COMPL                                                                 \
( BOOST_GENERIC_DETAIL_IS_EMPTY                                                \
  ( BOOST_GENERIC_DETAIL_TYPENAME_DETS_DEFAULT_IMPL( dets ) )                  \
)

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_DEFAULT( dets )                     \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_TYPENAME_DETS_HAS_DEFAULT( dets )           \
            , BOOST_GENERIC_DETAIL_REMOVE_PAREN                                \
            , BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY                           \
              ( BOOST_GENERIC_DETAIL_TYPENAME_DETS_DEFAULT_IMPL( dets ) )      \
            )( BOOST_GENERIC_DETAIL_TYPENAME_DETS_DEFAULT_IMPL( dets ) )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_DEFAULT_IMPL( dets )                \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 2, dets ) )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_NO_DEF( constraint, arg )      \
BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_WITH_DEF                               \
( constraint, BOOST_GENERIC_DETAIL_THIS_MEM_DETS( arg ), arg, )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_NOT_1_PARAM( constraint,  ... )\
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_IS_EMPTY( __VA_ARGS__ )                     \
            , BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_PARTIAL                  \
            , BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_AT_LEAST_2_PARAMS        \
            )( constraint                                                      \
             , BOOST_GENERIC_DETAIL_THIS_MEM_DETS                              \
               ( BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ ) )           \
             , __VA_ARGS__                                                     \
             )

// ToDo: Branch with better error if a nested typename requirement has a default
#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_AT_LEAST_2_PARAMS( constraint  \
                                                                 ,this_mem_dets\
                                                                 , name, ...   \
                                                                 )             \
BOOST_PP_IIF                                                                   \
( BOOST_PP_BITOR                                                               \
  ( BOOST_GENERIC_DETAIL_STARTS_EMPTY_OR_PARENTHESIZED( __VA_ARGS__ )          \
  , BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IS_PARTIAL( this_mem_dets )             \
  )                                                                            \
, BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_PARTIAL                              \
, BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_WITH_DEF                             \
)( constraint, this_mem_dets, name, ( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_WITH_DEF( constraint           \
                                                        , this_mem_dets, name  \
                                                        , def                  \
                                                        )                      \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_EMPTY_OR_PARENTHESIZED( name )                   \
, BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_PARTIAL                              \
, BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_VALID                                \
)( constraint, this_mem_dets, name, def )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_VALID( constraint              \
                                                     , this_mem_dets, name, def\
                                                     )                         \
(1)                                                                            \
(name)                                                                         \
((def))                                                                        \
(1)                                                                            \
(())                                                                           \
(this_mem_dets)                                                                \
(constraint)

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_PARTIAL( ... )                 \
(0)                                                                            \
(name_of_invalid_typename_requirement)                                         \
(())                                                                           \
(1)                                                                            \
((("Invalid typename declaration")))                                           \
(~)                                                                            \
(())

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_IMPL_INVALID( ... )                 \
(0)                                                                            \
(name_of_invalid_typename_requirement)                                         \
(())                                                                           \
(0)                                                                            \
((("Invalid typename declaration")))                                           \
(~)                                                                            \
(())

#define BOOST_GENERIC_DETAIL_STARTS_WITH_TYPENAME( ... )                       \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_EMPTY_OR_PARENTHESIZED( __VA_ARGS__ )            \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                                  \
, BOOST_GENERIC_DETAIL_STARTS_WITH_TYPENAME_IMPL                               \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_STARTS_WITH_TYPENAME_IMPL( ... )                  \
BOOST_GENERIC_DETAIL_NUM_ARGS_AFTER_RESCAN_IS_2                                \
( BOOST_GENERIC_DETAIL_VARIADIC_CAT                                            \
  ( BOOST_GENERIC_DETAIL_STARTS_WITH_TYPENAME                                  \
  , BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ )                          \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_STARTS_WITH_TYPENAMEtypename ,

#define BOOST_GENERIC_DETAIL_EAT_TYPENAME( ... )                               \
BOOST_GENERIC_DETAIL_VARIADIC_CAT                                              \
( BOOST_GENERIC_DETAIL_EAT_TYPENAME, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_EAT_TYPENAMEtypename

#define BOOST_GENERIC_DETAIL_EAT_TYPENAME_OR_CONSTRAINT( ... )                 \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( __VA_ARGS__ )         \
            , BOOST_GENERIC_DETAIL_EAT_WRAPPED                                 \
            , BOOST_GENERIC_DETAIL_EAT_TYPENAME                                \
            )( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_TYPENAME_ERROR_DEFAULT_NOT_PAREN( dets )          \
"The default of a typename requirement must be parenthesized: ( typename "     \
BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                        \
( BOOST_GENERIC_DETAIL_TYPENAME_DETS_NAME( dets ) ) " )"

#define BOOST_GENERIC_DETAIL_TYPENAME_ERROR_DEFAULT_NOT_PAREN( dets )          \
"The default of a typename requirement must be parenthesized: ( typename "     \
BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                        \
( BOOST_GENERIC_DETAIL_TYPENAME_DETS_NAME( dets ) ) " )"

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_NATIVE_DECL( dets )                 \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_TYPENAME_DETS_HAS_DEFAULT( dets )           \
            , BOOST_GENERIC_DETAIL_TYPENAME_DETS_NATIVE_DECL_IMPL_NO_DEF       \
            , BOOST_GENERIC_DETAIL_TYPENAME_DETS_NATIVE_DECL_IMPL_DEF          \
            )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_NATIVE_DECL_IMPL_NO_DEF( dets )     \
typename BOOST_GENERIC_DETAIL_TYPENAME_DETS_NAME( dets )

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_NATIVE_DECL_IMPL_DEF( dets )        \
BOOST_GENERIC_DETAIL_TYPENAME_DETS_NATIVE_DECL_IMPL_NO_DEF( dets ) =           \
BOOST_GENERIC_DETAIL_TYPENAME_DETS_DEFAULT( dets );

#define BOOST_GENERIC_DETAIL_TYPENAME_DETS_NATIVE_DECL_STR( dets )             \
BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                        \
( BOOST_GENERIC_DETAIL_TYPENAME_DETS_NATIVE_DECL( dets ) )

#endif // BOOST_GENERIC_DETAIL_TYPENAME_DETAILS_HPP
