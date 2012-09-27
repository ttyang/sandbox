/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/operator_dets.hpp>

#define NONMEMBER_OPERATOR_NO_OPERATOR                                         \
BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS( foo )

#define INVALID_NONMEMBER_OPERATOR                                             \
BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS( operator foo )

#define NONMEMBER_MEMBER_OPERATOR                                              \
BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS( operator new )

#define VALID_NONMEMBER_OPERATOR                                               \
BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS( operator plus )

///// NONMEMBER_OPERATOR_NO_OPERATOR
#if BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IS_VALID( NONMEMBER_OPERATOR_NO_OPERATOR )
#error "foo" considered valid nonmember operator.
#endif

#if BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IS_PARTIAL( NONMEMBER_OPERATOR_NO_OPERATOR )
#error "foo" considered partial nonmember operator.
#endif

///// INVALID_NONMEMBER_OPERATOR
#if BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IS_VALID( INVALID_NONMEMBER_OPERATOR )
#error Invalid operator considered valid nonmember operator.
#endif

#if !BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IS_PARTIAL( INVALID_NONMEMBER_OPERATOR )
#error Invalid operator not considered partial nonmember operator.
#endif

///// NONMEMBER_MEMBER_OPERATOR
#if BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IS_VALID( NONMEMBER_MEMBER_OPERATOR )
#error "operator new" considered valid nonmember operator.
#endif

#if !BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IS_PARTIAL( NONMEMBER_MEMBER_OPERATOR )
#error "operator new" not considered partial nonmember operator.
#endif

///// VALID_NONMEMBER_OPERATOR
#if !BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IS_VALID( VALID_NONMEMBER_OPERATOR )
#error "operator plus" not considered valid nonmember operator.
#endif

#if !BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IS_PARTIAL( VALID_NONMEMBER_OPERATOR )
#error "operator plus" not considered partial nonmember operator.
#endif


/////
#define MEMBER_OPERATOR_NO_OPERATOR                                            \
BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS( foo )

#define INVALID_MEMBER_OPERATOR                                                \
BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS( operator foo )

#define MEMBER_NONMEMBER_OPERATOR                                              \
BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS( operator plus )

#define VALID_MEMBER_OPERATOR                                                  \
BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS( operator new )

///// MEMBER_OPERATOR_NO_OPERATOR
#if BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IS_VALID( MEMBER_OPERATOR_NO_OPERATOR )
#error "foo" considered valid member operator.
#endif

#if BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IS_PARTIAL( MEMBER_OPERATOR_NO_OPERATOR )
#error "foo" considered partial member operator.
#endif

///// INVALID_MEMBER_OPERATOR
#if BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IS_VALID( INVALID_MEMBER_OPERATOR )
#error Invalid operator considered valid member operator.
#endif

#if !BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IS_PARTIAL( INVALID_MEMBER_OPERATOR )
#error Invalid operator not considered partial member operator.
#endif

///// MEMBER_NONMEMBER_OPERATOR
#if BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IS_VALID( MEMBER_NONMEMBER_OPERATOR )
#error "operator plus" considered valid member operator.
#endif

#if !BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IS_PARTIAL( MEMBER_NONMEMBER_OPERATOR )
#error "operator plus" not considered partial member operator.
#endif

///// VALID_MEMBER_OPERATOR
#if !BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IS_VALID( VALID_MEMBER_OPERATOR )
#error "operator new" not considered valid member operator.
#endif

#if !BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IS_PARTIAL( VALID_MEMBER_OPERATOR )
#error "operator new" not considered partial member operator.
#endif

