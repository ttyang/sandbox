/*=============================================================================
    Copyright (c) 2006, 2007 Matthew Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_ACT_INTERLOCKED_MUL_ASSIGN_MUL_ASSIGN_ACQ_REL_HPP
#define BOOST_ACT_INTERLOCKED_MUL_ASSIGN_MUL_ASSIGN_ACQ_REL_HPP

#include <boost/act/interlocked/detail/binary_forwarder.hpp>

#define BOOST_ACT_INTERLOCKED_DETAIL_BINARY_FORWARDER_INFO                     \
( multiply_assign, acq_rel, *, not_additive )

#include BOOST_ACT_INTERLOCKED_DETAIL_BINARY_FORWARDER()

#endif
