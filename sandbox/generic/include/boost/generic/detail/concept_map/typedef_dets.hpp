#ifndef BOOST_GENERIC_DETAIL_CONCEPT_MAP_TYPEDEF_DETS_HPP
#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_TYPEDEF_DETS_HPP

#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/num_args_is_2.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/starts_empty_or_parenthesized.hpp>
#include <boost/generic/detail/variadic_cat.hpp>
#include <boost/generic/detail/variadic_identity.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/seq/elem.hpp>

// Yields result in the format:
//   (validity_bit)(partial_bit)((def))(error_in_quotes)
#define BOOST_GENERIC_DETAIL_TYPEDEF_DETS( ... )                               \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_STARTS_WITH_TYPEDEF( __VA_ARGS__ )          \
            , BOOST_GENERIC_DETAIL_TYPEDEF_DETS_IMPL                           \
            , BOOST_GENERIC_DETAIL_TYPEDEF_IMPL_NOT_TYPEDEF                    \
            )( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_WRAPPED_TYPEDEF_DETS( wrapped_arg )               \
BOOST_GENERIC_DETAIL_TYPEDEF_DETS wrapped_arg

#define BOOST_GENERIC_DETAIL_TYPEDEF_DETS_IMPL( ... )                          \
BOOST_GENERIC_DETAIL_TYPEDEF_DETS_IMPL_                                        \
( BOOST_GENERIC_DETAIL_EAT_TYPEDEF( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_TYPEDEF_DETS_IMPL_( ... )                         \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_STARTS_EMPTY_OR_PARENTHESIZED( __VA_ARGS__ )\
            , BOOST_GENERIC_DETAIL_TYPEDEF_DETS_IMPL_EMPTY_OR_PARENTHESIZED    \
            , BOOST_GENERIC_DETAIL_TYPEDEF_DETS_IMPL_VALID                     \
            )( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_TYPEDEF_DETS_IMPL_VALID( ... )                    \
(1)(1)((__VA_ARGS__))("No error.")

#define BOOST_GENERIC_DETAIL_TYPEDEF_DETS_IMPL_EMPTY_OR_PARENTHESIZED( ... )   \
(0)(1)(())("Invalid typedef.")

#define BOOST_GENERIC_DETAIL_TYPEDEF_IMPL_NOT_TYPEDEF( ... )                   \
(0)(0)(())("Not a typedef.")

#define BOOST_GENERIC_DETAIL_TYPEDEF_DETS_IS_VALID( dets )                     \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_TYPEDEF_DETS_IS_PARTIAL( dets )                   \
BOOST_PP_SEQ_ELEM( 1, dets )

#define BOOST_GENERIC_DETAIL_TYPEDEF_DETS_DEFINITION( dets )                   \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 2, dets ) )

#define BOOST_GENERIC_DETAIL_TYPEDEF_DETS_STATEMENT( dets )                    \
typedef BOOST_GENERIC_DETAIL_TYPEDEF_DETS_DEFINITION( dets );

#define BOOST_GENERIC_DETAIL_STARTS_WITH_TYPEDEF( ... )                        \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_EMPTY_OR_PARENTHESIZED( __VA_ARGS__ )            \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                                  \
, BOOST_GENERIC_DETAIL_STARTS_WITH_TYPEDEF_IMPL                                \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_STARTS_WITH_TYPEDEF_IMPL( ... )                   \
BOOST_GENERIC_DETAIL_NUM_ARGS_AFTER_RESCAN_IS_2                                \
( BOOST_GENERIC_DETAIL_VARIADIC_CAT                                            \
  ( BOOST_GENERIC_DETAIL_STARTS_WITH_TYPEDEF                                   \
  , BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ )                          \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_STARTS_WITH_TYPEDEFtypedef ,

#define BOOST_GENERIC_DETAIL_EAT_TYPEDEF( ... )                                \
BOOST_GENERIC_DETAIL_VARIADIC_CAT                                              \
( BOOST_GENERIC_DETAIL_EAT_TYPEDEF, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_EAT_TYPEDEFtypedef

#endif // BOOST_GENERIC_DETAIL_CONCEPT_MAP_TYPEDEF_DETS_HPP
