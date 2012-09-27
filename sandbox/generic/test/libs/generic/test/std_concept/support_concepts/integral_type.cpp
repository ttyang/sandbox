/*==============================================================================
    Copyright (c) 2011, 2012 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/support_concepts/integral_type.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::IntegralType;

BOOST_GENERIC_ASSERT( IntegralType< char > );
BOOST_GENERIC_ASSERT( IntegralType< unsigned char > );
BOOST_GENERIC_ASSERT( IntegralType< signed char > );
BOOST_GENERIC_ASSERT( IntegralType< int > );
BOOST_GENERIC_ASSERT( IntegralType< short > );
BOOST_GENERIC_ASSERT( IntegralType< long > );
BOOST_GENERIC_ASSERT( IntegralType< long long > );
BOOST_GENERIC_ASSERT( IntegralType< unsigned > );
BOOST_GENERIC_ASSERT( IntegralType< unsigned short > );
BOOST_GENERIC_ASSERT( IntegralType< unsigned long > );
BOOST_GENERIC_ASSERT( IntegralType< unsigned long long > );
BOOST_GENERIC_ASSERT( IntegralType< bool > );

BOOST_GENERIC_ASSERT_NOT( IntegralType< float > );
BOOST_GENERIC_ASSERT_NOT( IntegralType< double > );
BOOST_GENERIC_ASSERT_NOT( IntegralType< long double > );
BOOST_GENERIC_ASSERT_NOT( IntegralType< char* > );
BOOST_GENERIC_ASSERT_NOT( IntegralType< void > );
