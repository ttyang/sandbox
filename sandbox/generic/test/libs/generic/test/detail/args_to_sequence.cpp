/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/args_to_sequence.hpp>
#include <boost/preprocessor/seq/cat.hpp>

void bar();

void foo()
{
  BOOST_PP_SEQ_CAT( BOOST_GENERIC_DETAIL_ARGS_TO_SEQUENCE( b, a, r ) )();
}
