/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PREPROCESSOR_INCLUDE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PREPROCESSOR_INCLUDE_HPP_INCLUDED

#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/dispatch/details/preprocessor.hpp>
#include <boost/simd/sdk/simd/preprocessor/sse.hpp>
#include <boost/simd/sdk/simd/preprocessor/vmx.hpp>

#ifndef BOOST_SIMD_DETECTED
  #define BOOST_SIMD_RELATIVE_INCLUDE_BASE(B,F) BOOST_PP_STRINGIZE(B()simd/none/F) 
#endif

#define BOOST_SIMD_RELATIVE_INCLUDE(B,F)  BOOST_SIMD_RELATIVE_INCLUDE_BASE(B,F)

#endif

