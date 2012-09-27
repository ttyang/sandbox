/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/signed_integral_like.hpp>

#include <boost/generic/assert.hpp>

BOOST_GENERIC_ASSERT( boost::generic::std_concept::SignedIntegralLike< signed char > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::SignedIntegralLike< short int > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::SignedIntegralLike< int > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::SignedIntegralLike< long int > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::SignedIntegralLike< long long int > );

BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::SignedIntegralLike< unsigned char > );
BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::SignedIntegralLike< unsigned short int > );
BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::SignedIntegralLike< unsigned int > );
BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::SignedIntegralLike< unsigned long int > );
BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::SignedIntegralLike< unsigned long long int > );

BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::SignedIntegralLike< float > );
BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::SignedIntegralLike< double > );
BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::SignedIntegralLike< long double > );

BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::SignedIntegralLike< void > );
