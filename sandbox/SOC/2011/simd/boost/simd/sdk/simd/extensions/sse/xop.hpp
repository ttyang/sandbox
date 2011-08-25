/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_SSE_XOP_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_SSE_XOP_HPP_INCLUDED

#if defined(__XOP__)
#  ifndef BOOST_SIMD_HAS_XOP_SUPPORT
#    define BOOST_SIMD_HAS_XOP_SUPPORT
#  endif
#elif defined(BOOST_SIMD_HAS_XOP_SUPPORT) && !defined(_MSC_VER)
#  undef BOOST_SIMD_HAS_XOP_SUPPORT
#endif

#if defined(BOOST_SIMD_HAS_XOP_SUPPORT) && !defined(BOOST_SIMD_HAS_FMA4_SUPPORT)
#  define BOOST_SIMD_HAS_FMA4_SUPPORT
#endif

#if !defined(BOOST_SIMD_DETECTED) && defined(BOOST_SIMD_HAS_XOP_SUPPORT)

////////////////////////////////////////////////////////////////////////////////
// Report XOP discovery
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_WARNING(XOP SIMD extension detected)

////////////////////////////////////////////////////////////////////////////////
// XOP extensions flags
////////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_DETECTED
#define BOOST_SIMD_XOP
#define BOOST_SIMD_SSE_FAMILY
#define BOOST_SIMD_STRING             "XOP"
#define BOOST_SIMD_STRING_LIST        "SSE2 SSE3 SSE4A SSSE3 SSE4_1 SSE4_2 AVX FMA4 XOP"
#define BOOST_SIMD_BYTES              32
#define BOOST_SIMD_BITS               256
#define BOOST_SIMD_CARDINALS          (2)(4)(8)(16)(32)
#define BOOST_SIMD_TAG_SEQ            (::boost::simd::tag::avx_)(::boost::simd::tag::sse_)
#define BOOST_SIMD_DEFAULT_EXTENSION  ::boost::simd::tag::avx_
#define BOOST_SIMD_DEFAULT_SITE       ::boost::simd::tag::avx_

// XOP header not standardized
#include <x86intrin.h>
#include <xopintrin.h>

#include <boost/simd/sdk/simd/extensions/meta/sse.hpp>
#include <boost/simd/sdk/simd/extensions/meta/avx.hpp>

#endif
#endif
