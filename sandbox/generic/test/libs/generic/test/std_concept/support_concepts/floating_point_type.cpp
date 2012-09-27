/*==============================================================================
    Copyright (c) 2011, 2012 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/support_concepts/floating_point_type.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::FloatingPointType;

BOOST_GENERIC_ASSERT( FloatingPointType< float > );
BOOST_GENERIC_ASSERT( FloatingPointType< double > );
BOOST_GENERIC_ASSERT( FloatingPointType< long double > );

BOOST_GENERIC_ASSERT_NOT( FloatingPointType< char > );
BOOST_GENERIC_ASSERT_NOT( FloatingPointType< unsigned char > );
BOOST_GENERIC_ASSERT_NOT( FloatingPointType< signed char > );
BOOST_GENERIC_ASSERT_NOT( FloatingPointType< int > );
BOOST_GENERIC_ASSERT_NOT( FloatingPointType< short > );
BOOST_GENERIC_ASSERT_NOT( FloatingPointType< long > );
BOOST_GENERIC_ASSERT_NOT( FloatingPointType< long long > );
BOOST_GENERIC_ASSERT_NOT( FloatingPointType< unsigned > );
BOOST_GENERIC_ASSERT_NOT( FloatingPointType< unsigned short > );
BOOST_GENERIC_ASSERT_NOT( FloatingPointType< unsigned long > );
BOOST_GENERIC_ASSERT_NOT( FloatingPointType< unsigned long long > );
BOOST_GENERIC_ASSERT_NOT( FloatingPointType< bool > );

BOOST_GENERIC_ASSERT_NOT( FloatingPointType< void > );
BOOST_GENERIC_ASSERT_NOT( FloatingPointType< char* > );
