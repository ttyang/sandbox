#ifndef BOOST_GENERIC_DETAIL_NESTED_NAME_DETS_HPP
#define BOOST_GENERIC_DETAIL_NESTED_NAME_DETS_HPP

#define BOOST_GENERIC_DETAIL_NESTED_NAME_DETS( ... )                           \
BOOST_PP_IIF                                                                   \
( BOOST_PP_EQUAL                                                               \
  ( BOOST_GENERIC_DETAIL_NUM_ARGS( __VA_ARGS__ ), 1 )                          \
, BOOST_GENERIC_DETAIL_NESTED_NAME_DETS_IMPL                                   \
, BOOST_GENERIC_DETAIL_NESTED_NAME_DETS_IMPL_INVALID                           \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_NESTED_NAME_DETS_IMPL( arg )                      \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_STARTS_WITH_THIS( arg )                     \
            , BOOST_GENERIC_DETAIL_NESTED_NAME_DETS_IMPL_HAS_THIS              \
            , BOOST_GENERIC_DETAIL_NESTED_NAME_DETS_IMPL_INVALID               \
            )( arg )

#define BOOST_GENERIC_DETAIL_STARTS_WITH_THIS( ... )                           \
BOOST_GENERIC_DETAIL_STARTS_WITH_THIS_IMPL                                     \
( BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_STARTS_WITH_THIS_IMPL( arg )                      \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( arg )                 \
            , BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                      \
            , BOOST_GENERIC_DETAIL_STARTS_WITH_THIS_IMPL_NO_PAREN              \
            )( arg )

#define BOOST_GENERIC_DETAIL_STARTS_WITH_THIS_IMPL_NO_PAREN( arg )             \
BOOST_PP_EQUAL                                                                 \
( BOOST_GENERIC_DETAIL_NUM_ARGS_AFTER_RESCAN                                   \
  ( BOOST_GENERIC_DETAIL_VARIADIC_CAT                                          \
    ( BOOST_GENERIC_DETAIL_STARTS_WITH_THIS_IMPL, arg foo )                    \
  )                                                                            \
, 2                                                                            \
)

#define BOOST_GENERIC_DETAIL_STARTS_WITH_THIS_IMPLthis ,

#define BOOST_GENERIC_DETAIL_EAT_THIS( ... )                                   \
BOOST_GENERIC_DETAIL_VARIADIC_CAT( BOOST_GENERIC_DETAIL_EAT_THIS, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_EAT_THIS

(typename (Container<int>) iterator

(void)((Container<int>)begin)( (int) foo )

#endif // BOOST_GENERIC_DETAIL_NESTED_NAME_DETS_HPP
