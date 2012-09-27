/*==============================================================================
    Copyright (c) 2011, 2012 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/support_concepts/variable_type.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::VariableType;

BOOST_GENERIC_ASSERT( VariableType< int > );
BOOST_GENERIC_ASSERT( VariableType< int[4] > );
BOOST_GENERIC_ASSERT( VariableType< int& > );
BOOST_GENERIC_ASSERT( VariableType< int(&)() > );
BOOST_GENERIC_ASSERT( VariableType< int(&)[4] > );

struct variable_type {};

BOOST_GENERIC_ASSERT( VariableType< variable_type > );

struct not_variable_type { virtual void foo() = 0; };

BOOST_GENERIC_ASSERT_NOT( VariableType< not_variable_type > );
BOOST_GENERIC_ASSERT_NOT( VariableType< void > );
BOOST_GENERIC_ASSERT_NOT( VariableType< int() > );
