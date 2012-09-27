/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_ARGS_TO_ARRAY
#define BOOST_GENERIC_DETAIL_ARGS_TO_ARRAY

#include <boost/generic/detail/num_args.hpp>

#define BOOST_GENERIC_DETAIL_ARGS_TO_ARRAY( ... )                              \
( BOOST_GENERIC_DETAIL_NUM_ARGS( __VA_ARGS__ )                                 \
, ( __VA_ARGS__ )                                                              \
)

#define BOOST_GENERIC_DETAIL_ARGS_TO_ARRAY_AFTER_RESCAN( ... )                 \
( BOOST_GENERIC_DETAIL_NUM_ARGS_AFTER_RESCAN( __VA_ARGS__ )                    \
, ( __VA_ARGS__ )                                                              \
)

#endif // BOOST_GENERIC_DETAIL_ARGS_TO_ARRAY
