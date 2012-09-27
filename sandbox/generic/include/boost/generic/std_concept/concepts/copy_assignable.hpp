/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONCEPTS_COPY_ASSIGNABLE_HPP
#define BOOST_GENERIC_STD_CONCEPT_CONCEPTS_COPY_ASSIGNABLE_HPP

#include <boost/generic/auto_concept.hpp>
#include <boost/generic/std_concept/concepts/has_assign.hpp>
#include <boost/generic/std_concept/concepts/move_assignable.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>
#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/concepts/copy_assignable.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [concept.copymove]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (CopyAssignable)( (typename) T )
, ( public (HasAssign<T, const T&>)
           (MoveAssignable<T>)
  )
, ( typename result_type, typename HasAssign<T, const T&>::result_type )
, ( requires SameType< result_type
                     , typename HasAssign<T, const T&>::result_type
                     >
  )
, ( axiom CopyPreservation( (T&) x, (T) y ) {
      (x = y, x) == y;
    }
  )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_CONCEPTS_COPY_ASSIGNABLE_HPP
