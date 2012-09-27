/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_HEAD_ARGUMENT_HPP
#define BOOST_GENERIC_DETAIL_HEAD_ARGUMENT_HPP

#define BOOST_GENERIC_DETAIL_HEAD_WRAPPED_ARGUMENT( args )                     \
BOOST_GENERIC_DETAIL_HEAD_ARGUMENT args

#define BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( ... )                              \
BOOST_GENERIC_DETAIL_HEAD_ARGUMENT_IMPL( __VA_ARGS__, _0 )

#define BOOST_GENERIC_DETAIL_HEAD_ARGUMENT_IMPL( head, ... ) head

#define BOOST_GENERIC_DETAIL_HEAD_ARGUMENT_AFTER_RESCAN( ... )                 \
BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ )

#endif // BOOST_GENERIC_DETAIL_HEAD_ARGUMENT_HPP
