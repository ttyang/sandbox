#ifndef BOOST_GENERIC_DETAIL_AXIOM_DETS_HPP
#define BOOST_GENERIC_DETAIL_AXIOM_DETS_HPP

#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/num_args_is_2.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/starts_empty_or_parenthesized.hpp>
#include <boost/generic/detail/variadic_cat.hpp>
#include <boost/generic/detail/variadic_identity.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/seq/elem.hpp>

// Takes axioms of the form:
//   axiom something_not_empty
//
// Yields results in the form:
// (validity_bit)(partial_bit)((something_not_empty))

#define BOOST_GENERIC_DETAIL_AXIOM_DETS( ... )                                 \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_STARTS_WITH_AXIOM( __VA_ARGS__ )            \
            , BOOST_GENERIC_DETAIL_AXIOM_DETS_IMPL                             \
            , BOOST_GENERIC_DETAIL_AXIOM_DETS_IMPL_INVALID                     \
            )( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_WRAPPED_AXIOM_DETS( wrapped_arg )                 \
BOOST_GENERIC_DETAIL_AXIOM_DETS wrapped_arg

#define BOOST_GENERIC_DETAIL_AXIOM_DETS_IS_VALID( dets )                       \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_AXIOM_DETS_IS_PARTIAL( dets )                     \
BOOST_PP_SEQ_ELEM( 1, dets )

#define BOOST_GENERIC_DETAIL_AXIOM_DETS_ARG( dets )                            \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 2, dets ) )

#define BOOST_GENERIC_DETAIL_AXIOM_DETS_IMPL( ... )                            \
BOOST_GENERIC_DETAIL_AXIOM_DETS_IMPL_                                          \
( BOOST_GENERIC_DETAIL_EAT_AXIOM( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_AXIOM_DETS_IMPL_( ... )                           \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_STARTS_EMPTY_OR_PARENTHESIZED( __VA_ARGS__ )\
            , BOOST_GENERIC_DETAIL_AXIOM_DETS_IMPL_PARTIAL                     \
            , BOOST_GENERIC_DETAIL_AXIOM_DETS_IMPL_VALID                       \
            )( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_AXIOM_DETS_IMPL_INVALID( ... )                    \
(0)(0)((__VA_ARGS__))

#define BOOST_GENERIC_DETAIL_AXIOM_DETS_IMPL_PARTIAL( ... )                    \
(0)(1)((__VA_ARGS__))

#define BOOST_GENERIC_DETAIL_AXIOM_DETS_IMPL_VALID( ... )                      \
(1)(1)((__VA_ARGS__))

// Begin "starts with axiom" macros
#define BOOST_GENERIC_DETAIL_STARTS_WITH_AXIOM( ... )                          \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_EMPTY_OR_PARENTHESIZED( __VA_ARGS__ )            \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                                  \
, BOOST_GENERIC_DETAIL_STARTS_WITH_AXIOM_IMPL                                  \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_STARTS_WITH_AXIOM_IMPL( ... )                     \
BOOST_GENERIC_DETAIL_NUM_ARGS_AFTER_RESCAN_IS_2                                \
( BOOST_GENERIC_DETAIL_VARIADIC_CAT                                            \
  ( BOOST_GENERIC_DETAIL_STARTS_WITH_AXIOM                                     \
  , BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ )                          \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_STARTS_WITH_AXIOMaxiom ,

// Begin "eat axiom" macros
#define BOOST_GENERIC_DETAIL_EAT_AXIOM( ... )                                  \
BOOST_GENERIC_DETAIL_VARIADIC_CAT                                              \
( BOOST_GENERIC_DETAIL_EAT_AXIOM, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_EAT_AXIOMaxiom

#endif // BOOST_GENERIC_DETAIL_AXIOM_DETS_HPP
