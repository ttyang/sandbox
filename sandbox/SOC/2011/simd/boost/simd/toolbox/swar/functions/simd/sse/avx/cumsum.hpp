//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_CUMSUM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_CUMSUM_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/toolbox/swar/functions/cumsum.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/sdk/simd/native_cast.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::cumsum_, boost::simd::tag::avx_,
                         (A0),
                         ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename meta::scalar_of<A0>::type sctype;
      typedef simd::native<sctype, boost::simd::tag::sse_ >  svtype;
      svtype a000 = { _mm256_extractf128_si256(a0, 0)};
      svtype a011 = { _mm256_extractf128_si256(a0, 1)};
      //      std::cout << " == a000 " << a000 << std::endl;
      //      std::cout << " == a011 " << a011 << std::endl;
       svtype a00 =  cumsum(a000);
       svtype a01 =  cumsum(a011);
      svtype z = splat<svtype>(a00[meta::cardinal_of<svtype>::value-1]);
      //      std::cout << " == a00 " << a00 << std::endl;
      //      std::cout << " == a01 " << a01 << std::endl;
      //      std::cout << " == z   " << z   << std::endl;
      A0 that = simd::native_cast<A0>(_mm256_insertf128_si256(that,a00, 0));
      that =  simd::native_cast<A0>(_mm256_insertf128_si256(that, a01+z, 1))              ;
      return that;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::cumsum_, boost::simd::tag::avx_,
                         (A0),
                         ((simd_<double_<A0>,boost::simd::tag::avx_>))
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename meta::scalar_of<A0>::type sctype;
      typedef simd::native<sctype, boost::simd::tag::sse_ >  svtype;
      svtype a000 = { _mm256_extractf128_pd(a0, 0)};
      svtype a011 = { _mm256_extractf128_pd(a0, 1)};
      svtype a00 =  cumsum(a000);
      svtype a01 =  cumsum(a011);
      svtype z = splat<svtype>(a00[meta::cardinal_of<svtype>::value-1]);
      A0 that = simd::native_cast<A0>(_mm256_insertf128_pd(that,a00, 0));
      that =  simd::native_cast<A0>(_mm256_insertf128_pd(that, a01+z, 1))                 ;
      return that;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::cumsum_, boost::simd::tag::avx_,
                         (A0),
                         ((simd_<single_<A0>,boost::simd::tag::avx_>))
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
//       cout << "pb de gcc 4.5 ?" << std::endl;
      typedef typename meta::scalar_of<A0>::type sctype;
      typedef simd::native<sctype, boost::simd::tag::sse_ >  svtype;
//       std::cout << " == a0 " << a0 << std::endl;
      svtype a011;
      a011=  _mm256_extractf128_ps(a0, 1);
      svtype a000;
      a000 =  _mm256_extractf128_ps(a0, 0);
//       std::cout << " == a000 " << a000 << std::endl;
//       std::cout << " == a011 " << a011 << std::endl;
      svtype a00 =  cumsum(a000);
      svtype a01 =  cumsum(a011);
      svtype z = splat<svtype>(a00[meta::cardinal_of<svtype>::value-1]);
//       std::cout << " == a00 " << a00 << std::endl;
//       std::cout << " == a01 " << a01 << std::endl;
//       std::cout << " == z   " << z   << std::endl;
      A0 that = {_mm256_insertf128_ps(that,a00, 0)};
      that =  _mm256_insertf128_ps(that, a01+z, 1);
      return that;
    }
  };
} } }
#endif
#endif
