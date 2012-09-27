/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPTS_SCONS_INTEGRAL_CONSTANT_EXPRESSION_TYPE_HPP
#define BOOST_GENERIC_STD_CONCEPTS_SCONS_INTEGRAL_CONSTANT_EXPRESSION_TYPE_HPP

#include <boost/generic/auto_concept.hpp>
#include <boost/generic/std_concept/concepts/true.hpp>
#include <boost/generic/std_concept/support_concepts/non_type_template_parameter_type.hpp>
#include <boost/generic/std_concept/support_concepts/scalar_type.hpp>

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS
#include <type_traits>
#endif

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/support_concepts/integral_constant_expression_type.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [concept.support]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (IntegralConstantExpressionType)( (typename) T )
, ( public (ScalarType< T >) (NonTypeTemplateParameterType< T >) )
, ( requires True< std::is_integral< T >::value || std::is_enum< T >::value > )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPTS_SCONS_INTEGRAL_CONSTANT_EXPRESSION_TYPE_HPP
