#ifndef BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFS_VISITOR_HPP
#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFS_VISITOR_HPP

#include <boost/generic/detail/dummy_type.hpp>
#include <boost/generic/detail/param_list.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFSaxiom( ... )

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFSrequires( ... )

// d here is:
//   concept_param_dets
#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFStypename( i, d, name, default_ )   \
typedef typename ::boost::mpl::eval_if                                         \
        < ::boost::generic::detail::is_dummy_type                              \
          < typename boost_generic_detail_typename_deducers::name >            \
        , typename boost_generic_detail_typename_deducers::template            \
          BOOST_PP_CAT( boost_generic_detail_deduce, name )                    \
          < BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS( d ) >                \
        , ::boost::mpl::identity                                               \
          < typename boost_generic_detail_typename_deducers::name >            \
        >::type name;

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFSconstrained_typename( i, d         \
                                                                , constraint   \
                                                                , name         \
                                                                , default_     \
                                                                )              \
BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFStypename( i, d, name, default_ )

// ToDo: Define
#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFSmember_typename( i, d, this_type   \
                                                           , name              \
                                                           , default_          \
                                                           )


// ToDo: Define
#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFSconstrained_member_typename(       \
                                                                     i, d      \
                                                                   , constraint\
                                                                   , this_type \
                                                                   , name      \
                                                                   , default_  \
                                                                   )

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFSfunction( ... )

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFSmember_function( ... )

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFSstatic_member_function(...)

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFSprefix_unary_operator( ... )

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFSpostfix_unary_operator(...)

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFSbinary_operator( ... )

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFScall_operator( ... )

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFScomma_operator( ... )

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFSarrow_operator( ... )

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFSsubscript_operator( ... )

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFSassign_operator( ... )

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFSallocation_operator( ... )

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFSdeallocation_operator(...)

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFSconstructor( ... )

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFSexplicit_constructor( ... )

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFSdestructor( ... )

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFSconversion( ... )

#define BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFSexplicit_conversion( ... )

#endif // BOOST_GENERIC_DETAIL_ACTUAL_TYPEDEFS_VISITOR_HPP
