/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_TRAILING_BASES_HPP
#define BOOST_GENERIC_DETAIL_TRAILING_BASES_HPP

#include <boost/generic/detail/params_for_each.hpp>
#include <boost/generic/detail/remove_paren.hpp>

#define BOOST_GENERIC_DETAIL_TRAILING_BASES( prefix, params )                  \
BOOST_GENERIC_DETAIL_PARAMS_FOR_EACH                                           \
( BOOST_GENERIC_DETAIL_TRAILING_BASES_MACRO, prefix                            \
, BOOST_GENERIC_DETAIL_PARAMS_TO_LIST( params )                                \
)

#define BOOST_GENERIC_DETAIL_TRAILING_BASES_MACRO( r, prefix, elem )           \
, prefix BOOST_GENERIC_REMOVE_PAREN( elem )

#endif // BOOST_GENERIC_DETAIL_TRAILING_BASES_HPP
