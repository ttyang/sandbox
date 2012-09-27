/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY_HPP
#define BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY_HPP

#include <boost/generic/detail/variadic_empty.hpp>

#define BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( ... )                          \
__VA_ARGS__ BOOST_GENERIC_DETAIL_VARIADIC_EMPTY

#endif // BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY_HPP
