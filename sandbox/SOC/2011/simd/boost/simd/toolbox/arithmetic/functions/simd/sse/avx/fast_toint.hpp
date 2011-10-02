//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_FAST_TOINT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_FAST_TOINT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/simd/include/functions/make.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::fast_toint_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<double_<A0>,boost::simd::tag::avx_>))
                       )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type; 
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return make<result_type>(a0[0],a0[1], a0[2],a0[3]); //TODO with _mm_cvttpd_epi32
    }
  };

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::fast_toint_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<single_<A0>,boost::simd::tag::avx_>))
                       )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type; 
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      result_type that =  {_mm256_cvttps_epi32(a0)};
      return  that;
    }
  };
} } }
#endif
#endif
