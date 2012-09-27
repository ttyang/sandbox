#ifndef BOOST_GENERIC_DETAIL_FUNCTION_CHECKER_VISITOR_HPP
#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKER_VISITOR_HPP

#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/rescan.hpp>
#include <boost/generic/detail/variadic_empty.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/identity.hpp>

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERaxiom( i, d, arg )

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERrequires( i, d, arg )

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERtypename( i, d, name, default_ )

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERconstrained_typename( i, d, constraint    \
                                                         , name, default_      \
                                                         )

// ToDo: Define
#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERmember_typename( i, d, this_type, name    \
                                                    , default_                 \
                                                    )

// ToDo: Define
#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERconstrained_member_typename(\
                                                                     i, d      \
                                                                   , constraint\
                                                                   , this_type \
                                                                   , name      \
                                                                   , default_  \
                                                                   )

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERfunction( i, d, return_type, name \
                                             , param_dets, default_            \
                                             )                                 \
template< BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, d ) )                   \
        , BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) )                   \
        , class BoostGenericDetailEnabler = void                               \
        >                                                                      \
struct BOOST_PP_CAT( boost_generic_detail_function_is_valid, i );              \
                                                                               \
template< BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, d ) )                   \
        , BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) )                   \
        >                                                                      \
struct BOOST_PP_CAT( boost_generic_detail_function_is_valid, i );              \
< BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, d ) )                           \
, BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) )                           \
, typename ::boost::is_convertible< decltype( name( args ) ), return_type >::type                     \
>

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERmember_function(                  \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , name       \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_PP_CAT( boost_generic_detail_function_is_valid, i )                      \
< BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, d ) )                           \
, BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) )                           \
>

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERstatic_member_function(           \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , name       \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_PP_CAT( boost_generic_detail_function_is_valid, i )                      \
< BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, d ) )                           \
, BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) )                           \
>

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKER_BASIC_OPERATOR(                  \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , operator_  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_PP_CAT( boost_generic_detail_function_is_valid, i )                      \
< BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, d ) )                           \
, BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) )                           \
>

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERprefix_unary_operator             \
BOOST_GENERIC_DETAIL_FUNCTION_CHECKER_BASIC_OPERATOR

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERpostfix_unary_operator            \
BOOST_GENERIC_DETAIL_FUNCTION_CHECKER_BASIC_OPERATOR

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERbinary_operator                   \
BOOST_GENERIC_DETAIL_FUNCTION_CHECKER_BASIC_OPERATOR

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERcall_operator( i, d               \
                                                                 , return_type \
                                                                 , param_dets  \
                                                                 , default_    \
                                                                 )             \
BOOST_PP_CAT( boost_generic_detail_function_is_valid, i )                      \
< BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, d ) )                           \
, BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) )                           \
>

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERcomma_operator( i, d       \
                                                                  , return_type\
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_PP_CAT( boost_generic_detail_function_is_valid, i )                      \
< BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, d ) )                           \
, BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) )                           \
>

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERarrow_operator( i, d       \
                                                                  , return_type\
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_PP_CAT( boost_generic_detail_function_is_valid, i )                      \
< BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, d ) )                           \
, BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) )                           \
>

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKER_MEMBER_OPERATOR(          \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , operator_  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_PP_CAT( boost_generic_detail_function_is_valid, i )                      \
< BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, d ) )                           \
, BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) )                           \
>

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERassign_operator( i, d      \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_PP_CAT( boost_generic_detail_function_is_valid, i )                      \
< BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, d ) )                           \
, BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) )                           \
>

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERallocation_operator               \
BOOST_GENERIC_DETAIL_FUNCTION_CHECKER_MEMBER_OPERATOR

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERdeallocation_operator             \
BOOST_GENERIC_DETAIL_FUNCTION_CHECKER_MEMBER_OPERATOR

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERconstructor( i, d          \
                                                               , this_type     \
                                                               , param_dets    \
                                                               , default_      \
                                                               )               \
BOOST_PP_CAT( boost_generic_detail_function_is_valid, i )                      \
< BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, d ) )                           \
, BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) )                           \
>

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERexplicit_constructor(      \
                                                                     i, d      \
                                                                   , this_type \
                                                                   , param_dets\
                                                                   , default_  \
                                                                   )           \
BOOST_PP_CAT( boost_generic_detail_function_is_valid, i )                      \
< BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, d ) )                           \
, BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) )                           \
>

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERdestructor( i, d, this_type\
                                                              , default_       \
                                                              )                \
BOOST_PP_CAT( boost_generic_detail_function_is_valid, i )                      \
< BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, d ) )                           \
, BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) )                           \
>

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERconversion( i, d           \
                                                              , target_type    \
                                                              , param_dets     \
                                                              , default_       \
                                                              )                \
BOOST_PP_CAT( boost_generic_detail_function_is_valid, i )                      \
< BOOST_PP_SEQ_ELEM( 0, d ), BOOST_PP_SEQ_ELEM( 1, d ) >

#define BOOST_GENERIC_DETAIL_FUNCTION_CHECKERexplicit_conversion(       \
                                                                    i, d       \
                                                                  , target_type\
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_PP_CAT( boost_generic_detail_function_is_valid, i )                      \
< BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, d ) )                           \
, BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) )                           \
>

#endif // BOOST_GENERIC_DETAIL_FUNCTION_CHECKER_VISITOR_HPP
