//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_TOINT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_TOINT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/toolbox/arithmetic/functions/toint.hpp>
#include <boost/simd/include/functions/make.hpp>
#include <boost/simd/include/functions/is_nan.hpp>
#include <boost/simd/include/functions/bitwise_andnot.hpp>
#include <boost/simd/include/functions/is_equal.hpp>
#include <boost/simd/include/functions/select.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::toint_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<double_<A0>,boost::simd::tag::avx_>))
                       )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type; 
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      const A0 aa0 = b_andnot(a0, is_nan(a0)); 
      return select(eq(aa0, Inf<A0>()),
        Inf<result_type>(),
        make<result_type>(aa0[0],aa0[1],aa0[2],aa0[3])
      );
    }
  };

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::toint_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<single_<A0>,boost::simd::tag::avx_>))
                       )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type; 
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      A0 aa0 = b_andnot(a0, is_nan(a0)); 
      result_type that =  {_mm256_cvttps_epi32(aa0)};
      return  select(eq(aa0, Inf<A0>()), Inf<result_type>(), that);
    }
  };
} } }

#endif
#endif
