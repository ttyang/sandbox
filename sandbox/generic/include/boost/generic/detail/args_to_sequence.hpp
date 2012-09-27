/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_ARGS_TO_SEQUENCE_HPP
#define BOOST_GENERIC_DETAIL_ARGS_TO_SEQUENCE_HPP

#include <boost/generic/detail/num_args.hpp>
#include <boost/generic/detail/wrap.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>

#define BOOST_GENERIC_DETAIL_ARGS_TO_SEQUENCE( ... )                           \
BOOST_PP_TUPLE_TO_SEQ( BOOST_GENERIC_DETAIL_NUM_ARGS( __VA_ARGS__ )            \
                     , ( __VA_ARGS__ )                                         \
                     )

#define BOOST_GENERIC_DETAIL_WRAPPED_ARGS_TO_SEQUENCE( arg )                   \
BOOST_GENERIC_DETAIL_ARGS_TO_SEQUENCE arg

#endif // BOOST_GENERIC_DETAIL_ARGS_TO_SEQUENCE_HPP
