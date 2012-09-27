/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONCEPTS_EQUIVALENCE_RELATION_HPP
#define BOOST_GENERIC_STD_CONCEPT_CONCEPTS_EQUIVALENCE_RELATION_HPP

#include <boost/generic/auto_concept.hpp>
#include <boost/generic/std_concept/concepts/predicate.hpp>
#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/concepts/equivalence_relation.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// TODO possibly make this not auto (it's auto in N2914)

// [concept.comparison]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (EquivalenceRelation)( (typename) F, (typename) T )
, ( public Predicate<F, T, T> )

, ( axiom Reflexivity(F f, T a) { f(a, a) == true; } )

, ( axiom Symmetry(F f, T a, T b) {
      if (f(a, b))
        f(b, a) == true;
    }
  )

, ( axiom Transitivity(F f, T a, T b, T c) {
      if (f(a, b) && f(b, c))
        f(a, c) == true;
    }
  )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_CONCEPTS_EQUIVALENCE_RELATION_HPP
