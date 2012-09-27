/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_PARAMS_TO_LIST_HPP
#define BOOST_GENERIC_DETAIL_PARAMS_TO_LIST_HPP

#include <boost/generic/detail/num_args.hpp>
#include <boost/generic/detail/wrap.hpp>
#include <boost/preprocessor/tuple/to_list.hpp>

#define BOOST_GENERIC_DETAIL_PARAMS_TO_LIST( params_in_paren )                 \
BOOST_PP_TUPLE_TO_LIST                                                         \
( BOOST_GENERIC_DETAIL_NUM_WRAPPED_ARGS( params_in_paren )                     \
, params_in_paren                                                              \
)

#define BOOST_GENERIC_DETAIL_PARAMS_TO_LIST_AFTER_RESCAN( params_in_paren )    \
BOOST_GENERIC_DETAIL_PARAMS_TO_LIST BOOST_GENERIC_DETAIL_WRAP( params_in_paren )

#endif // BOOST_GENERIC_DETAIL_PARAMS_TO_LIST_HPP
