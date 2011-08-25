/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_DISPATCH_ATTRIBUTES_HPP_INCLUDED
#define BOOST_DISPATCH_ATTRIBUTES_HPP_INCLUDED

#if defined(__GNUC__)
#define BOOST_DISPATCH_FORCE_INLINE __attribute__((always_inline))
#elif defined(_MSC_VER)
#define BOOST_DISPATCH_FORCE_INLINE __forceinline
#else
#define BOOST_DISPATCH_FORCE_INLINE inline
#endif

#if defined(__GNUC__)
#define BOOST_DISPATCH_NO_INLINE __attribute__((noinline))
#elif defined(_MSC_VER)
#define BOOST_DISPATCH_NO_INLINE __declspec(noinline)
#else
#define BOOST_DISPATCH_NO_INLINE
#endif

#if defined(__GNUC__)
#define BOOST_DISPATCH_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define BOOST_DISPATCH_DEPRECATED __declspec(deprecated)
#else
#define BOOST_DISPATCH_DEPRECATED
#endif

#endif
