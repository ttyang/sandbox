/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPTS_SUPPORT_CONCEPTS_LITERAL_TYPE_HPP
#define BOOST_GENERIC_STD_CONCEPTS_SUPPORT_CONCEPTS_LITERAL_TYPE_HPP

#include <boost/generic/auto_concept.hpp>
#include <boost/generic/std_concept/concepts/true.hpp>
#include <boost/generic/std_concept/support_concepts/value_type.hpp>

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS
#include <boost/mpl/and.hpp>

#include <boost/mpl/or.hpp>
#include <type_traits>

// ToDo: Make this work with intrinsics

// ToDo: Define concept maps for builtin literal types

namespace boost { namespace generic { namespace std_concept { namespace detail {

template< class T >
struct is_array_of_literal_types;

// ToDo: Check if this should not include incomplete array types
template< class T >
struct is_builtin_literal_type
  : mpl::or_
    < std::is_scalar< T >
    , is_array_of_literal_types< T >
    > {};

template< class T >
struct is_array_of_literal_types_impl
  : is_builtin_literal_type< typename std::remove_all_extents< T >::type > {};

template< class T >
struct is_array_of_literal_types
  : mpl::and_< std::is_array< T >, is_array_of_literal_types_impl< T > > {};

template< class T >
struct is_literal : is_builtin_literal_type< T > {};

} } } }

#endif

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/support_concepts/literal_type.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [concept.support]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (LiteralType)( (typename) T ), ( public ValueType< T > )
, ( requires True< detail::is_literal< T >::value > )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPTS_SUPPORT_CONCEPTS_LITERAL_TYPE_HPP
