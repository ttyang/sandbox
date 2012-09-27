/*==============================================================================
    Copyright (c) 2011, 2012 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/support_concepts/arithmetic_type.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::ArithmeticType;

BOOST_GENERIC_ASSERT( ArithmeticType< float > );
BOOST_GENERIC_ASSERT( ArithmeticType< double > );
BOOST_GENERIC_ASSERT( ArithmeticType< long double > );
BOOST_GENERIC_ASSERT( ArithmeticType< signed char > );
BOOST_GENERIC_ASSERT( ArithmeticType< short int > );
BOOST_GENERIC_ASSERT( ArithmeticType< int > );
BOOST_GENERIC_ASSERT( ArithmeticType< long int > );
BOOST_GENERIC_ASSERT( ArithmeticType< long long int > );
BOOST_GENERIC_ASSERT( ArithmeticType< unsigned char > );
BOOST_GENERIC_ASSERT( ArithmeticType< unsigned short int > );
BOOST_GENERIC_ASSERT( ArithmeticType< unsigned long int > );
BOOST_GENERIC_ASSERT( ArithmeticType< unsigned long long int > );

struct not_arithmetic_like {};

BOOST_GENERIC_ASSERT_NOT( ArithmeticType< not_arithmetic_like > );
BOOST_GENERIC_ASSERT_NOT( ArithmeticType< void > );
