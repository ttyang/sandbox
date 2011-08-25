//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_ERROR_DEBUG_HPP_INCLUDED
#define BOOST_SIMD_SDK_ERROR_DEBUG_HPP_INCLUDED

/*!
 * \file
 * \brief Control the way build mode affect Boost.Dispatch error handlign setting
 */

#if defined(DOXYGEN_ONLY)
//==============================================================================
/*!
 * \ingroup error_config
 * When defined -- usually via cmake --, force the compilation of Boost.Dispatch in Release
 * mode. In this mode, most error checking systems are off to ensure a high
 * level of performance. Use only when debuggign is done.
 *
 * Note that defining the classical \c NDEBUG symbol triggers \c BOOST_SIMD_SDK_RELEASE.
 */
//==============================================================================
#define BOOST_SIMD_RELEASE

//==============================================================================
/*!
 * \ingroup error_config
 * When defined -- usually via cmake --, force the compilation of Boost.Dispatch in Debug
 * mode. In this mode, most error checking systems are on to ensure a high
 * quality of debugging facilities. Performance are not guaranteed in Debug mode.
 */
//==============================================================================
#define BOOST_SIMD_DEBUG
#endif

//==============================================================================
// BOOST_SIMD_SDK_RELEASE is triggerable by NDEBUG
//==============================================================================
#if defined(NDEBUG)
#define BOOST_SIMD_RELEASE
#define BOOST_SIMD_DISABLE_ASSERTS
#define BOOST_DISABLE_ASSERTS
#endif

//==============================================================================
// Ensure consistencies between assertion settings
//==============================================================================
#if defined(BOOST_DISABLE_ASSERTS) && !defined(BOOST_SIMD_DISABLE_ASSERTS)
#define BOOST_SIMD_DISABLE_ASSERTS
#endif

//==============================================================================
// BOOST_SIMD_DEBUG removes all NDEBUG influence
// Note that defining BOOST_SIMD_DEBUG overrride any Release mode settings
//==============================================================================
#if defined(BOOST_SIMD_DEBUG)
#undef NDEBUG
#undef BOOST_SIMD_DISABLE_ASSERTS
#undef BOOST_DISABLE_ASSERTS
#endif

#endif
