/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONCEPTS_STRICT_WEAK_ORDER_HPP
#define BOOST_GENERIC_STD_CONCEPT_CONCEPTS_STRICT_WEAK_ORDER_HPP

#include <boost/generic/auto_concept.hpp>
#include <boost/generic/std_concept/concepts/predicate.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/concepts/strict_weak_order.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [concept.comparison]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (StrictWeakOrder)( (typename) F, (typename) T ), ( public Predicate<F,T,T> )
, ( axiom Irreflexivity(F f, T a) { f(a, a) == false; } )
, ( axiom Antisymmetry(F f, T a, T b) {
      if (f(a, b))
        f(b, a) == false;
    }
  )
, ( axiom Transitivity(F f, T a, T b, T c) {
      if (f(a, b) && f(b, c))
        f(a, c) == true;
    }
  )
, ( axiom TransitivityOfEquivalence(F f, T a, T b, T c) {
      if (!f(a, b) && !f(b, a) && !f(b, c) && !f(c, b))
        (!f(a, c) && !f(c, a)) == true;
    }
  )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_CONCEPTS_STRICT_WEAK_ORDER_HPP
