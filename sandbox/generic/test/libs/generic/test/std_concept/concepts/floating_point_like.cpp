/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/floating_point_like.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::FloatingPointLike;

BOOST_GENERIC_ASSERT( FloatingPointLike< float > );
BOOST_GENERIC_ASSERT( FloatingPointLike< double > );
BOOST_GENERIC_ASSERT( FloatingPointLike< long double > );

BOOST_GENERIC_ASSERT_NOT( FloatingPointLike< char > );
BOOST_GENERIC_ASSERT_NOT( FloatingPointLike< int > );
BOOST_GENERIC_ASSERT_NOT( FloatingPointLike< void > );
BOOST_GENERIC_ASSERT_NOT( FloatingPointLike< void() > );
