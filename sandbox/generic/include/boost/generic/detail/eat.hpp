/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_EAT_HPP
#define BOOST_GENERIC_DETAIL_EAT_HPP

#define BOOST_GENERIC_DETAIL_EAT( ... )

#define BOOST_GENERIC_DETAIL_EAT_WRAPPED( ... )                                \
BOOST_GENERIC_DETAIL_EAT __VA_ARGS__

#endif // BOOST_GENERIC_DETAIL_EAT_HPP
