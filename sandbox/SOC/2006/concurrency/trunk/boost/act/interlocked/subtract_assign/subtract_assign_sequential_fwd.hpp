/*=============================================================================
    Copyright (c) 2006, 2007 Matthew Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_ACT_INTERLOCKED_SUBTRACT_ASSIGN_SUBTRACT_ASSIGN_SEQ_FWD_HPP
#define BOOST_ACT_INTERLOCKED_SUBTRACT_ASSIGN_SUBTRACT_ASSIGN_SEQ_FWD_HPP

#include <boost/act/config/interlocked/has.hpp>

#if BOOST_ACT_INTERLOCKED_HAS( subtract_assign, sequential )

#include <boost/act/interlocked/detail/binary_forwarder_fwd.hpp>

#define BOOST_ACT_INTERLOCKED_DETAIL_BINARY_FORWARDER_FWD_INFO                 \
( subtract_assign, sequential, additive )

#include BOOST_ACT_INTERLOCKED_DETAIL_BINARY_FORWARDER_FWD()

#endif

#endif
