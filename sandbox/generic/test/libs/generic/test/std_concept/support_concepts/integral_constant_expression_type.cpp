/*==============================================================================
    Copyright (c) 2011, 2012 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/support_concepts/integral_constant_expression_type.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::IntegralConstantExpressionType;

BOOST_GENERIC_ASSERT( IntegralConstantExpressionType< int > );
BOOST_GENERIC_ASSERT( IntegralConstantExpressionType< char > );
BOOST_GENERIC_ASSERT( IntegralConstantExpressionType< bool > );

enum integral_constant_expression_type { foo = 1 };

BOOST_GENERIC_ASSERT( IntegralConstantExpressionType< integral_constant_expression_type > );

struct not_integral_constant_expression_type {};

BOOST_GENERIC_ASSERT_NOT( IntegralConstantExpressionType< not_integral_constant_expression_type > );
BOOST_GENERIC_ASSERT_NOT( IntegralConstantExpressionType< void > );
BOOST_GENERIC_ASSERT_NOT( IntegralConstantExpressionType< float > );
BOOST_GENERIC_ASSERT_NOT( IntegralConstantExpressionType< int* > );
BOOST_GENERIC_ASSERT_NOT( IntegralConstantExpressionType< int[] > );
BOOST_GENERIC_ASSERT_NOT( IntegralConstantExpressionType< int() > );
BOOST_GENERIC_ASSERT_NOT( IntegralConstantExpressionType< int& > );
