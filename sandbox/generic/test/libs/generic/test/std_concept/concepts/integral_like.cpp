/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/integral_like.hpp>

#include <boost/generic/assert.hpp>

BOOST_GENERIC_ASSERT( boost::generic::std_concept::IntegralLike< signed char > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::IntegralLike< short int > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::IntegralLike< int > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::IntegralLike< long int > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::IntegralLike< long long int > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::IntegralLike< unsigned char > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::IntegralLike< unsigned short int > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::IntegralLike< unsigned long int > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::IntegralLike< unsigned long long int > );

BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::IntegralLike< float > );
BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::IntegralLike< double > );
BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::IntegralLike< long double > );
BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::IntegralLike< void > );
BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::IntegralLike< char* > );
