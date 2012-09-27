/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/num_args.hpp>

#if BOOST_GENERIC_DETAIL_NUM_ARGS() != 0
#error BOOST_GENERIC_DETAIL_NUM_ARGS does not return proper results for no args.
#endif

#if BOOST_GENERIC_DETAIL_NUM_ARGS( _1 ) != 1
#error BOOST_GENERIC_DETAIL_NUM_ARGS does not return proper results for 1 arg.
#endif

#if BOOST_GENERIC_DETAIL_NUM_ARGS( _1, _2, _3, _4, _5, _6 ) != 6
#error BOOST_GENERIC_DETAIL_NUM_ARGS does not return proper results.
#endif

#if BOOST_GENERIC_DETAIL_NUM_WRAPPED_ARGS( () ) != 0
#error BOOST_GENERIC_DETAIL_NUM_WRAPPED_ARGS does not return proper results for no args.
#endif

#if BOOST_GENERIC_DETAIL_NUM_WRAPPED_ARGS( ( _1 ) ) != 1
#error BOOST_GENERIC_DETAIL_NUM_WRAPPED_ARGS does not return proper results for 1 arg.
#endif

#if BOOST_GENERIC_DETAIL_NUM_WRAPPED_ARGS( ( _1, _2, _3, _4, _5, _6 ) ) != 6
#error BOOST_GENERIC_DETAIL_NUM_WRAPPED_ARGS does not return proper results.
#endif
