#ifndef BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_VISITOR_HPP
#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_VISITOR_HPP

#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/rescan.hpp>
#include <boost/generic/detail/variadic_empty.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/identity.hpp>

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_TYPES( d )                 \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, d ) )

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_FUNS( d )                  \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) )

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORaxiom( i, d, arg )

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORrequires( i, d, arg )

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORtypename( i, d, name        \
                                                            , default_         \
                                                            )                  \
((BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_TYPES(d)((i)(name))))            \
((BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_FUNS(d)))

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORconstrained_typename( i, d \
                                                                   , constraint\
                                                                   , name      \
                                                                   , default_  \
                                                                   )           \
BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORtypename( i, d, name, default_ )

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORmember_typename( i, d      \
                                                                   , this_type \
                                                                   , name      \
                                                                   , default_  \
                                                                   )

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORconstrained_member_typename(\
                                                                     i, d      \
                                                                   , constraint\
                                                                   , this_type \
                                                                   , name      \
                                                                   , default_  \
                                                                   )

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_INSERT_FUN( i )            \
((BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_TYPES(d)))                       \
((BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_FUNS(d)((i))))

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORfunction( i, d, return_type \
                                                            , name, param_dets \
                                                            , default_         \
                                                            )                  \
BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_INSERT_FUN( i )


#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORmember_function( i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , name       \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_INSERT_FUN( i )

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORstatic_member_function(     \
                                                                    i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , name       \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_INSERT_FUN( i )

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_BASIC_OPERATOR( i, d       \
                                                                  , return_type\
                                                                  , operator_  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_INSERT_FUN( i )

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORprefix_unary_operator       \
BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_BASIC_OPERATOR

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORpostfix_unary_operator      \
BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_BASIC_OPERATOR

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORbinary_operator             \
BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_BASIC_OPERATOR

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORcall_operator( i, d         \
                                                                 , return_type \
                                                                 , param_dets  \
                                                                 , default_    \
                                                                 )             \
BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_INSERT_FUN( i )

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORcomma_operator( i, d        \
                                                                 , return_type \
                                                                 , param_dets  \
                                                                 , default_    \
                                                                 )             \
BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_INSERT_FUN( i )

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORarrow_operator( i, d        \
                                                                  , return_type\
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_INSERT_FUN( i )

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORassign_operator( i, d       \
                                                                  , return_type\
                                                                  , this_type  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_INSERT_FUN( i )

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORallocation_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORdeallocation_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORconstructor( i, d           \
                                                              , this_type      \
                                                              , param_dets     \
                                                              , default_       \
                                                              )

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORexplicit_constructor(       \
                                                                     i, d      \
                                                                   , this_type \
                                                                   , param_dets\
                                                                   , default_  \
                                                                   )

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORdestructor( i, d, this_type \
                                                              , default_       \
                                                              )

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORconversion( i, d            \
                                                              , target_type    \
                                                              , param_dets     \
                                                              , default_       \
                                                              )

#define BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATORexplicit_conversion(        \
                                                                    i, d       \
                                                                  , target_type\
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )


#endif // BOOST_GENERIC_DETAIL_TYPE_AND_FUN_SEPARATOR_VISITOR_HPP
