/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONCEPTS_HAS_SWAP_HPP
#define BOOST_GENERIC_STD_CONCEPT_CONCEPTS_HAS_SWAP_HPP

#include <boost/generic/auto_concept.hpp>

//#include <algorithm>
//#include <utility>
//
//namespace boost { namespace generic { namespace std_concept {
//
//template< class L, class R >
//auto swap( L&& left_, R&& right_ )
//noexcept( noexcept( std::swap( std::declval< L >(), std::declval< R >() ) ) )
//-> decltype( std::swap( std::declval< L >(), std::declval< R >() ) )
//{
//  return std::swap( std::forward< L >( left_ ), std::forward< R >( right_ ) );
//}
//
//} } }

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/concepts/has_swap.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [concept.copymove]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (HasSwap)( (typename) T, (typename) U )
, ( (void)(swap)( (T), (U) ) )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_CONCEPTS_HAS_SWAP_HPP
