/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_ARRAY_TO_SEQ_HPP
#define BOOST_GENERIC_DETAIL_ARRAY_TO_SEQ_HPP

#include <boost/preprocessor/array/data.hpp>
#include <boost/preprocessor/array/size.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>

#define BOOST_GENERIC_DETAIL_ARRAY_TO_SEQ( array )                             \
BOOST_PP_TUPLE_TO_SEQ                                                          \
( BOOST_PP_ARRAY_SIZE( array )                                                 \
, BOOST_PP_ARRAY_DATA( array )                                                 \
)

#endif // BOOST_GENERIC_DETAIL_ARRAY_TO_SEQ_HPP
