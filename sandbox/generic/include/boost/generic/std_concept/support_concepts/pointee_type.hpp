/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPTS_SUPPORT_CONCEPTS_POINTEE_TYPE_HPP
#define BOOST_GENERIC_STD_CONCEPTS_SUPPORT_CONCEPTS_POINTEE_TYPE_HPP

#include <boost/generic/auto_concept.hpp>
#include <boost/generic/std_concept/concepts/true.hpp>

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS

#include <boost/function_types/is_function.hpp>
#include <boost/function_types/property_tags.hpp>
#include <type_traits>

namespace boost { namespace generic { namespace std_concept { namespace detail {

template< class T >
struct safe_is_function
  : function_types::is_function< T, function_types::non_cv > {};

template< class T >
struct safe_is_function< T& > : std::integral_constant< bool, false > {};

template< class T >
struct safe_is_function< T&& > : std::integral_constant< bool, false > {};

} } } }

#endif

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/support_concepts/pointee_type.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [concept.support]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (PointeeType)( (typename) T )
, ( requires True
             <    std::is_object< T >::value
               || std::is_void< T >::value
               || detail::safe_is_function< T >::value
             >
  )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPTS_SUPPORT_CONCEPTS_POINTEE_TYPE_HPP
