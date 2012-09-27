/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/is_operator.hpp>

#if BOOST_GENERIC_DETAIL_IS_OPERATOR_NAME( foo )
#error "foo" recognized as operator name.
#endif

#if BOOST_GENERIC_DETAIL_IS_OPERATOR_NAME()
#error Empty argument recognized as operator name.
#endif

#if BOOST_GENERIC_DETAIL_IS_OPERATOR_NAME( plus extra stuff )
#error "plus" with extra stuff recognized as operator name.
#endif

#if !BOOST_GENERIC_DETAIL_IS_OPERATOR_NAME( plus )
#error "plus" not recognized as operator name.
#endif

#if !BOOST_GENERIC_DETAIL_IS_OPERATOR_NAME( new )
#error "new" not recognized as operator name.
#endif

#if BOOST_GENERIC_DETAIL_IS_MEMBER_OPERATOR_NAME( minus )
#error "minus" not recognized as member operator name.
#endif

#if !BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATOR_NAME( minus )
#error "minus" recognized as nonmember operator name.
#endif

#if !BOOST_GENERIC_DETAIL_IS_MEMBER_OPERATOR_NAME( delete )
#error "delete" not recognized as member operator name.
#endif

#if BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATOR_NAME( delete )
#error "delete" recognized as nonmember operator name.
#endif
