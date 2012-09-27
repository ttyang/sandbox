/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPTS_SUPPORT_CONCEPTS_DERIVED_FROM_HPP
#define BOOST_GENERIC_STD_CONCEPTS_SUPPORT_CONCEPTS_DERIVED_FROM_HPP

#include <boost/generic/auto_concept.hpp>
#include <boost/generic/std_concept/concepts/true.hpp>
#include <boost/generic/std_concept/support_concepts/class_type.hpp>

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS

#include <boost/mpl/and.hpp>
#include <type_traits>

namespace boost { namespace generic { namespace std_concept { namespace detail {

template< class Base, class Derived >
struct is_public_base_of_impl
  : std::is_convertible< typename std::remove_cv< Derived >::type*, Base* > {};

template< class Base, class Derived >
struct is_public_base_of
  : mpl::and_< std::is_base_of< Base, Derived >
             , is_public_base_of_impl< Base, Derived >
             > {};

} } } }

#endif

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/support_concepts/derived_from.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// TODO make sure that this should only detect public bases

// [concept.support]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (DerivedFrom)( (typename) Derived, (typename) Base )
, ( requires ClassType< Derived > )
, ( requires ClassType< Base > )
, ( requires True< detail::is_public_base_of< Base, Derived >::value > )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPTS_SUPPORT_CONCEPTS_DERIVED_FROM_HPP
