/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/is_parenthesized.hpp>

#if BOOST_GENERIC_DETAIL_IS_PARENTHESIZED() == 1
#error Empty arg detected as parenthesized.
#endif

#if BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED() == 1
#error Empty arg detected as starting parenthesized.
#endif

#if BOOST_GENERIC_DETAIL_IS_PARENTHESIZED( _1 ) == 1
#error Unparenthesized 1 arg detected as parenthesized.
#endif

#if BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( _1 ) == 1
#error Unparenthesized 1 arg detected as starting parenthesized.
#endif

#if BOOST_GENERIC_DETAIL_IS_PARENTHESIZED( _1, _2, _3 ) == 1
#error Unparenthesized 3 args detected as parenthesized.
#endif

#if BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( _1, _2, _3 ) == 1
#error Unparenthesized 3 args detected as starting parenthesized.
#endif

#if BOOST_GENERIC_DETAIL_IS_PARENTHESIZED( () extra data ) == 1
#error Parentheses with extra data detected as parenthesized.
#endif

#if BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( () extra data ) != 1
#error Parentheses with extra data detected as not starting parenthesized.
#endif

#if BOOST_GENERIC_DETAIL_IS_PARENTHESIZED( () ) != 1
#error Parentheses detected as not parenthesized.
#endif

#if BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( () ) != 1
#error Parentheses detected as not starting parenthesized.
#endif
