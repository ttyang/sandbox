/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPES_VISITOR_HPP
#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPES_VISITOR_HPP

#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/param_list.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPESaxiom( ... )

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPESrequires( ... )

// ToDo: Only do this if a default is not present
#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPEStypename( i, d, name      \
                                                            , default_         \
                                                            )                  \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_IS_WRAPPED_EMPTY( default_ )                \
            , BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPES_NO_DEF             \
            , BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPES_WITH_DEF           \
            )( i, d, name )

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPES_NO_DEF( i, d, name )     \
typedef typename BOOST_PP_CAT( boost_generic_detail_first_pass, name )         \
        < BoostGenericDetailImplConceptMap >::type name;

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPES_WITH_DEF( i, d, name )   \
typedef typename BOOST_PP_CAT( boost_generic_detail_first_pass, name )         \
        < BoostGenericDetailImplConceptMap                                     \
        , BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_AUGMENTED_ARGS               \
          ( d, BoostGenericDetailImpl )                                        \
        >::type name;

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPESconstrained_typename( i, d\
                                                                  , constraint \
                                                                  , name       \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPEStypename( i, d, name, default_ )

// ToDo: Define
#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPESmember_typename( i, d      \
                                                                   , this_type \
                                                                   , name      \
                                                                   , default_  \
                                                                   )


// ToDo: Define
#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPESconstrained_member_typename(\
                                                                     i, d      \
                                                                   , constraint\
                                                                   , this_type \
                                                                   , name      \
                                                                   , default_  \
                                                                   )

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPESfunction( ... )

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPESmember_function( ... )

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPESstatic_member_function(...)

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPESprefix_unary_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPESpostfix_unary_operator(...)

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPESbinary_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPEScall_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPEScomma_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPESarrow_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPESsubscript_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPESassign_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPESallocation_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPESdeallocation_operator(...)

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPESconstructor( ... )

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPESexplicit_constructor( ... )

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPESdestructor( ... )

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPESconversion( ... )

#define BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPESexplicit_conversion( ... )

#endif // BOOST_GENERIC_DETAIL_TYPEDEF_FIRST_PASS_TYPES_VISITOR_HPP
