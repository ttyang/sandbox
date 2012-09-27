#ifndef BOOST_GENERIC_DETAIL_STATIC_ASSERT_VISITOR_HPP
#define BOOST_GENERIC_DETAIL_STATIC_ASSERT_VISITOR_HPP

#include <boost/generic/assert.hpp>
#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/is_not_same.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/rescan.hpp>
#include <boost/generic/detail/variadic_empty.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/identity.hpp>

#define BOOST_GENERIC_DETAIL_STATIC_ASSERTaxiom( i, d, arg )

#define BOOST_GENERIC_DETAIL_STATIC_ASSERTrequires( i, d, arg )                \
BOOST_GENERIC_ASSERT( BOOST_GENERIC_DETAIL_REMOVE_PAREN( arg ) );

#define BOOST_GENERIC_DETAIL_STATIC_ASSERTtypename( i, d, name, default_ )     \
typedef typename BOOST_GENERIC_DETAIL_REMOVE_PAREN( d )::name name;            \
static_assert                                                                  \
( ::boost::generic::detail::is_not_same                                        \
  < name, ::boost::generic::detail::no_deduction >::value                      \
, "typename '" BOOST_PP_STRINGIZE( name )                                      \
  "' was not explicitly satisfied and cannot be deduced."                      \
);                                                                             \
static_assert                                                                  \
( ::boost::generic::detail::is_not_same                                        \
  < name, ::boost::generic::detail::ambiguous_deduction >::value               \
, "typename '" BOOST_PP_STRINGIZE( name )                                      \
  "' was not explicitly satisfied and deduction results in ambiguity."         \
);

#define BOOST_GENERIC_DETAIL_STATIC_ASSERTconstrained_typename( i, d           \
                                                                   , constraint\
                                                                   , name      \
                                                                   , default_  \
                                                                   )           \
BOOST_GENERIC_DETAIL_STATIC_ASSERTtypename( i, d, name, default_ )             \
BOOST_GENERIC_DETAIL_STATIC_ASSERT                                             \
( BOOST_GENERIC_DETAIL_REMOVE_PAREN( constraint )< name > );

// ToDo: Define
#define BOOST_GENERIC_DETAIL_STATIC_ASSERTmember_typename( i, d      \
                                                                   , this_type \
                                                                   , name      \
                                                                   , default_  \
                                                                   )

// ToDo: Define
#define BOOST_GENERIC_DETAIL_STATIC_ASSERTconstrained_member_typename(\
                                                                     i, d      \
                                                                   , constraint\
                                                                   , this_type \
                                                                   , name      \
                                                                   , default_  \
                                                                   )

#define BOOST_GENERIC_DETAIL_STATIC_ASSERTfunction( i, d, return_type          \
                                                            , name, param_dets \
                                                            , default_         \
                                                            )

#define BOOST_GENERIC_DETAIL_STATIC_ASSERTmember_function(           \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , name       \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )

#define BOOST_GENERIC_DETAIL_STATIC_ASSERTstatic_member_function(    \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , name       \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )

#define BOOST_GENERIC_DETAIL_STATIC_ASSERT_BASIC_OPERATOR(           \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , operator_  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )

#define BOOST_GENERIC_DETAIL_STATIC_ASSERTprefix_unary_operator      \
BOOST_GENERIC_DETAIL_STATIC_ASSERT_BASIC_OPERATOR

#define BOOST_GENERIC_DETAIL_STATIC_ASSERTpostfix_unary_operator     \
BOOST_GENERIC_DETAIL_STATIC_ASSERT_BASIC_OPERATOR

#define BOOST_GENERIC_DETAIL_STATIC_ASSERTbinary_operator            \
BOOST_GENERIC_DETAIL_STATIC_ASSERT_BASIC_OPERATOR

#define BOOST_GENERIC_DETAIL_STATIC_ASSERTcall_operator( i, d        \
                                                                 , return_type \
                                                                 , param_dets  \
                                                                 , default_    \
                                                                 )

#define BOOST_GENERIC_DETAIL_STATIC_ASSERTcomma_operator( i, d       \
                                                                  , return_type\
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )

#define BOOST_GENERIC_DETAIL_STATIC_ASSERTarrow_operator( i, d       \
                                                                  , return_type\
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )

#define BOOST_GENERIC_DETAIL_STATIC_ASSERTsubscript_operator( i, d       \
                                                                  , return_type\
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )

#define BOOST_GENERIC_DETAIL_STATIC_ASSERT_MEMBER_OPERATOR(          \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , operator_  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )

#define BOOST_GENERIC_DETAIL_STATIC_ASSERTassign_operator( i, d      \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )

#define BOOST_GENERIC_DETAIL_STATIC_ASSERTallocation_operator        \
BOOST_GENERIC_DETAIL_STATIC_ASSERT_MEMBER_OPERATOR

#define BOOST_GENERIC_DETAIL_STATIC_ASSERTdeallocation_operator      \
BOOST_GENERIC_DETAIL_STATIC_ASSERT_MEMBER_OPERATOR

#define BOOST_GENERIC_DETAIL_STATIC_ASSERTconstructor( i, d          \
                                                               , this_type     \
                                                               , param_dets    \
                                                               , default_      \
                                                               )

#define BOOST_GENERIC_DETAIL_STATIC_ASSERTexplicit_constructor(      \
                                                                     i, d      \
                                                                   , this_type \
                                                                   , param_dets\
                                                                   , default_  \
                                                                   )

#define BOOST_GENERIC_DETAIL_STATIC_ASSERTdestructor( i, d, this_type\
                                                              , default_       \
                                                              )
#define BOOST_GENERIC_DETAIL_STATIC_ASSERTconversion( i, d           \
                                                              , target_type    \
                                                              , param_dets     \
                                                              , default_       \
                                                              )

#define BOOST_GENERIC_DETAIL_STATIC_ASSERTexplicit_conversion( i, d            \
                                                             , target_type     \
                                                             , param_dets      \
                                                             , default_        \
                                                             )

#endif // BOOST_GENERIC_DETAIL_STATIC_ASSERT_VISITOR_HPP
