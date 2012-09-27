/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/unsigned_integral_like.hpp>

#include <boost/generic/assert.hpp>

BOOST_GENERIC_ASSERT( boost::generic::std_concept::UnsignedIntegralLike< unsigned char > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::UnsignedIntegralLike< unsigned short int > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::UnsignedIntegralLike< unsigned int > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::UnsignedIntegralLike< unsigned long int > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::UnsignedIntegralLike< unsigned long long int > );

BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::UnsignedIntegralLike< signed char > );
BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::UnsignedIntegralLike< signed short int > );
BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::UnsignedIntegralLike< signed int > );
BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::UnsignedIntegralLike< signed long int > );
BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::UnsignedIntegralLike< signed long long int > );

BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::UnsignedIntegralLike< float > );
BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::UnsignedIntegralLike< double > );
BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::UnsignedIntegralLike< long double > );

BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::UnsignedIntegralLike< void > );
