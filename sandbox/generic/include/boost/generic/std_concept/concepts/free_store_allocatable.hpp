/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONCEPTS_FREE_STORE_ALLOCATABLE_HPP
#define BOOST_GENERIC_STD_CONCEPT_CONCEPTS_FREE_STORE_ALLOCATABLE_HPP

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS
#include <cstddef>
#include <new>
#endif

#include <boost/generic/auto_concept.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/concepts/free_store_allocatable.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [concept.memory]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (FreeStoreAllocatable)( (typename) T )
, ( (void*)(this(T) operator new)( (std::size_t) size ) )
, ( (void)(this(T) operator delete)( (void*) ) )
, ( (void*)(this(T) operator new_array)( (std::size_t) size ), {
      return T::operator new(size);
    }
  )
, ( (void)(this(T) operator delete_array)( (void*) ptr ), {
      return T::operator delete(ptr);
    }
  )
, ( (void*)(this(T) operator new)( (std::size_t) size, (const std::nothrow_t&) ), {
      try {
        return T::operator new(size);
      } catch(...) {
        return 0;
      }
    }
  )
, ( (void*)(this(T) operator new_array)( (std::size_t) size, (const std::nothrow_t&) ), {
      try {
        return T::operator new[](size);
      } catch(...) {
        return 0;
      }
    }
  )
, ( (void)(this(T) operator delete)( (void*) ptr, (const std::nothrow_t&) ), {
      T::operator delete(ptr);
    }
  )
, ( (void)(this(T) operator delete_array)( (void*) ptr, (const std::nothrow_t&) ), {
      T::operator delete[](ptr);
    }
  )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_CONCEPTS_FREE_STORE_ALLOCATABLE_HPP
