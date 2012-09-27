/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONCEPTS_EQUALITY_COMPARABLE_HPP
#define BOOST_GENERIC_STD_CONCEPT_CONCEPTS_EQUALITY_COMPARABLE_HPP

#include <boost/generic/auto_concept.hpp>
#include <boost/generic/std_concept/concepts/has_equal_to.hpp>
#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/concepts/equality_comparable.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [concept.comparison]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (EqualityComparable)( (typename) T ), ( public HasEqualTo<T, T> )
, ( (bool)(operator not_equal_to)( (const T&) a, (const T&) b ), {
      return !( a == b );
    }
  )
, ( axiom Consistency( T a, T b ) {
      (a == b) == !(a != b);
    }
  )
, ( axiom Reflexivity( T a ) {
      a == a;
    }
  )
, ( axiom Symmetry( T a, T b ) {
      if (a == b)
        b == a;
    }
  )
, ( axiom Transitivity( T a, T b, T c ) {
      if (a == b && b == c)
        a == c;
    }
  )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_CONCEPTS_EQUALITY_COMPARABLE_HPP
