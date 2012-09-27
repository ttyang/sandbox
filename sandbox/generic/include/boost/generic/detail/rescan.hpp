/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_RESCAN_HPP
#define BOOST_GENERIC_DETAIL_RESCAN_HPP

#include <boost/generic/detail/wrap.hpp>

#define BOOST_GENERIC_DETAIL_SELF( ... ) __VA_ARGS__

#define BOOST_GENERIC_DETAIL_RESCAN( ... )                                     \
BOOST_GENERIC_DETAIL_RESCAN_IMPL BOOST_GENERIC_DETAIL_WRAP( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_RESCAN_IMPL( ... ) __VA_ARGS__

#endif // BOOST_GENERIC_DETAIL_RESCAN_HPP
