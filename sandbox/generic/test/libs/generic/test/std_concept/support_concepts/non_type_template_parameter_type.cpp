/*==============================================================================
    Copyright (c) 2011, 2012 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/support_concepts/non_type_template_parameter_type.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::NonTypeTemplateParameterType;

BOOST_GENERIC_ASSERT( NonTypeTemplateParameterType< int > );
BOOST_GENERIC_ASSERT( NonTypeTemplateParameterType< bool > );
BOOST_GENERIC_ASSERT( NonTypeTemplateParameterType< char > );

enum enum_type { a = 0 };

BOOST_GENERIC_ASSERT( NonTypeTemplateParameterType< enum_type > );

BOOST_GENERIC_ASSERT( NonTypeTemplateParameterType< void* > );
BOOST_GENERIC_ASSERT( NonTypeTemplateParameterType< int* > );
BOOST_GENERIC_ASSERT( NonTypeTemplateParameterType< int(*)() > );
BOOST_GENERIC_ASSERT( NonTypeTemplateParameterType< int& > );
BOOST_GENERIC_ASSERT( NonTypeTemplateParameterType< int(&)() > );

struct struct_type {};

BOOST_GENERIC_ASSERT_NOT( NonTypeTemplateParameterType< void > );
BOOST_GENERIC_ASSERT_NOT( NonTypeTemplateParameterType< float > );
BOOST_GENERIC_ASSERT_NOT( NonTypeTemplateParameterType< struct_type > );
BOOST_GENERIC_ASSERT_NOT( NonTypeTemplateParameterType< int[] > );
BOOST_GENERIC_ASSERT_NOT( NonTypeTemplateParameterType< int[4] > );
