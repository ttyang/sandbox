/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/is_seq_nil.hpp>

#if BOOST_GENERIC_DETAIL_IS_SEQ_NIL( (foo)(bar) )
#error Sequence detected as BOOST_PP_SEQ_NIL
#endif

#if BOOST_GENERIC_DETAIL_IS_SEQ_NIL()
#error Empty argument detected as BOOST_PP_SEQ_NIL
#endif

#if !BOOST_GENERIC_DETAIL_IS_SEQ_NIL( BOOST_PP_SEQ_NIL )
#error BOOST_PP_SEQ_NIL not detected as BOOST_PP_SEQ_NIL
#endif

// ToDo: Add check for BOOST_PP_SEQ_NIL with data after it
