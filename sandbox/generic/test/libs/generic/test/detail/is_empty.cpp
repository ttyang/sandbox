/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/is_empty.hpp>

#if BOOST_GENERIC_DETAIL_IS_EMPTY() != 1
#error BOOST_GENERIC_DETAIL_IS_EMPTY does not return proper results for no args.
#endif

#if BOOST_GENERIC_DETAIL_IS_EMPTY( _1 ) != 0
#error BOOST_GENERIC_DETAIL_IS_EMPTY does not return proper results for 1 arg.
#endif

#if BOOST_GENERIC_DETAIL_IS_EMPTY( _1, _2, _3, _4, _5, _6 ) != 0
#error BOOST_GENERIC_DETAIL_IS_EMPTY does not return proper results.
#endif

#if BOOST_GENERIC_DETAIL_IS_EMPTY( () ) != 0
#error BOOST_GENERIC_DETAIL_IS_EMPTY does not return proper results for no args.
#endif

#if BOOST_GENERIC_DETAIL_IS_EMPTY( ( _1 ) ) != 0
#error BOOST_GENERIC_DETAIL_IS_EMPTY does not return proper results for 1 arg.
#endif

#if BOOST_GENERIC_DETAIL_IS_EMPTY( ( _1, _2, _3, _4, _5, _6 ) ) != 0
#error BOOST_GENERIC_DETAIL_IS_EMPTY does not return proper results.
#endif
