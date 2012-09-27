/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONCEPTS_HAS_VIRTUAL_DESTRUCTOR_HPP
#define BOOST_GENERIC_STD_CONCEPT_CONCEPTS_HAS_VIRTUAL_DESTRUCTOR_HPP

#include <boost/generic/auto_concept.hpp>
#include <boost/generic/std_concept/concepts/has_destructor.hpp>
#include <boost/generic/std_concept/concepts/true.hpp>
#include <boost/generic/std_concept/support_concepts/polymorphic_class.hpp>
#include <boost/type_traits/has_virtual_destructor.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/concepts/has_virtual_destructor.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [concept.destruct]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (HasVirtualDestructor)( (typename) T )
, ( public (HasDestructor<T>) (PolymorphicClass<T>) )
, ( requires True< has_virtual_destructor< T >::value > )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_CONCEPTS_HAS_VIRTUAL_DESTRUCTOR_HPP
