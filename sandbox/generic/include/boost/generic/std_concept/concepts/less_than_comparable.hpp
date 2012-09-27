/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONCEPTS_LESS_THAN_COMPARABLE_HPP
#define BOOST_GENERIC_STD_CONCEPT_CONCEPTS_LESS_THAN_COMPARABLE_HPP

#include <boost/generic/auto_concept.hpp>
#include <boost/generic/std_concept/concepts/has_less.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/concepts/less_than_comparable.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [concept.comparison]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (LessThanComparable)( (typename) T ), ( public HasLess< T, T > )
, ( (bool)(operator greater)( (const T&) a, (const T&) b), { return b < a; } )
, ( (bool)(operator less_equal)( (const T&) a, (const T&) b), { return !(b < a); } )
, ( (bool)(operator greater_equal)( (const T&) a, (const T&) b), { return !(a < b); } )
, ( axiom Consistency(T a, T b) {
      (a > b) == (b < a);
      (a <= b) == !(b < a);
      (a >= b) == !(a < b);
    }
  )
, ( axiom Irreflexivity(T a) { (a < a) == false; } )
, ( axiom Antisymmetry(T a, T b) {
      if (a < b)
        (b < a) == false;
    }
  )
, ( axiom Transitivity(T a, T b, T c) {
      if (a < b && b < c)
        (a < c) == true;
    }
  )
, ( axiom TransitivityOfEquivalence(T a, T b, T c) {
      if (!(a < b) && !(b < a) && !(b < c) && !(c < b))
        (!(a < c) && !(c < a)) == true;
    }
  )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_CONCEPTS_LESS_THAN_COMPARABLE_HPP
