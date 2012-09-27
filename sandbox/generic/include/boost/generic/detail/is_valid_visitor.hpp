#ifndef BOOST_GENERIC_DETAIL_IS_VALID_VISITOR_HPP
#define BOOST_GENERIC_DETAIL_IS_VALID_VISITOR_HPP

#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/rescan.hpp>
#include <boost/generic/detail/variadic_empty.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/identity.hpp>

#define BOOST_GENERIC_DETAIL_FUNCTION_IS_VALID_PARAM( i, d )                   \
BOOST_PP_CAT( boost_generic_detail_function_is_valid, i )                      \
< BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, d ) )                           \
  BOOST_PP_COMMA_IIF                                                           \
  ( BOOST_PP_COMPL( BOOST_GENERIC_DETAIL_IS_WRAPPED_EMPTY                      \
                    ( BOOST_PP_SEQ_ELEM( 1, d ) )                              \
                  )                                                            \
  )                                                                            \
  BOOST_PP_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) )                           \
>,


#define BOOST_GENERIC_DETAIL_IS_VALIDaxiom( i, d, arg )

#define BOOST_GENERIC_DETAIL_IS_VALIDrequires( i, d, arg )                     \
::boost::generic::detail::concept_is_valid                                     \
< BOOST_GENERIC_DETAIL_REMOVE_PAREN( arg ) >,

#define BOOST_GENERIC_DETAIL_IS_VALIDtypename( i, d, name, default_ )          \
::boost::generic::detail::is_not_dummy_type< name >,

#define BOOST_GENERIC_DETAIL_IS_VALIDconstrained_typename( i, d, constraint    \
                                                         , name, default_      \
                                                         )                     \
::boost::generic::detail::is_not_dummy_type< name >,                           \
::boost::generic::detail::concept_is_valid< constraint< name > >,

// ToDo: Define
#define BOOST_GENERIC_DETAIL_IS_VALIDmember_typename( i, d, this_type, name    \
                                                    , default_                 \
                                                    )

// ToDo: Define
#define BOOST_GENERIC_DETAIL_IS_VALIDconstrained_member_typename(\
                                                                     i, d      \
                                                                   , constraint\
                                                                   , this_type \
                                                                   , name      \
                                                                   , default_  \
                                                                   )

#define BOOST_GENERIC_DETAIL_IS_VALIDfunction( i, d, return_type, name         \
                                             , param_dets, default_            \
                                             )                                 \
BOOST_GENERIC_DETAIL_FUNCTION_IS_VALID_PARAM( i, d )

#define BOOST_GENERIC_DETAIL_IS_VALIDmember_function(           \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , name       \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_FUNCTION_IS_VALID_PARAM( i, d )

#define BOOST_GENERIC_DETAIL_IS_VALIDstatic_member_function(    \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , name       \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_FUNCTION_IS_VALID_PARAM( i, d )

#define BOOST_GENERIC_DETAIL_IS_VALID_BASIC_OPERATOR(           \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , operator_  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_FUNCTION_IS_VALID_PARAM( i, d )

#define BOOST_GENERIC_DETAIL_IS_VALIDprefix_unary_operator      \
BOOST_GENERIC_DETAIL_IS_VALID_BASIC_OPERATOR

#define BOOST_GENERIC_DETAIL_IS_VALIDpostfix_unary_operator     \
BOOST_GENERIC_DETAIL_IS_VALID_BASIC_OPERATOR

#define BOOST_GENERIC_DETAIL_IS_VALIDbinary_operator            \
BOOST_GENERIC_DETAIL_IS_VALID_BASIC_OPERATOR

#define BOOST_GENERIC_DETAIL_IS_VALIDcall_operator( i, d        \
                                                                 , return_type \
                                                                 , param_dets  \
                                                                 , default_    \
                                                                 )             \
BOOST_GENERIC_DETAIL_FUNCTION_IS_VALID_PARAM( i, d )
#define BOOST_GENERIC_DETAIL_IS_VALIDcomma_operator( i, d       \
                                                                  , return_type\
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_FUNCTION_IS_VALID_PARAM( i, d )

#define BOOST_GENERIC_DETAIL_IS_VALIDarrow_operator( i, d       \
                                                                  , return_type\
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_FUNCTION_IS_VALID_PARAM( i, d )

#define BOOST_GENERIC_DETAIL_IS_VALID_MEMBER_OPERATOR(          \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , operator_  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_FUNCTION_IS_VALID_PARAM( i, d )

#define BOOST_GENERIC_DETAIL_IS_VALIDassign_operator( i, d      \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_FUNCTION_IS_VALID_PARAM( i, d )

#define BOOST_GENERIC_DETAIL_IS_VALIDallocation_operator        \
BOOST_GENERIC_DETAIL_IS_VALID_MEMBER_OPERATOR

#define BOOST_GENERIC_DETAIL_IS_VALIDdeallocation_operator      \
BOOST_GENERIC_DETAIL_IS_VALID_MEMBER_OPERATOR

#define BOOST_GENERIC_DETAIL_IS_VALIDconstructor( i, d          \
                                                               , this_type     \
                                                               , param_dets    \
                                                               , default_      \
                                                               )               \
BOOST_GENERIC_DETAIL_FUNCTION_IS_VALID_PARAM( i, d )

#define BOOST_GENERIC_DETAIL_IS_VALIDexplicit_constructor(      \
                                                                     i, d      \
                                                                   , this_type \
                                                                   , param_dets\
                                                                   , default_  \
                                                                   )           \
BOOST_GENERIC_DETAIL_FUNCTION_IS_VALID_PARAM( i, d )

#define BOOST_GENERIC_DETAIL_IS_VALIDdestructor( i, d, this_type, default_ )   \
BOOST_GENERIC_DETAIL_FUNCTION_IS_VALID_PARAM( i, d )

#define BOOST_GENERIC_DETAIL_IS_VALIDconversion( i, d, target_type, param_dets \
                                               , default_                      \
                                               )                               \
BOOST_GENERIC_DETAIL_FUNCTION_IS_VALID_PARAM( i, d )

#define BOOST_GENERIC_DETAIL_IS_VALIDexplicit_conversion(       \
                                                                    i, d       \
                                                                  , target_type\
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_FUNCTION_IS_VALID_PARAM( i, d )

#endif // BOOST_GENERIC_DETAIL_IS_VALID_VISITOR_HPP
