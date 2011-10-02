/*******************************************************************************
 *         Copyright 2003-2011 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_AVX_IS_INCLUDED_C_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_AVX_IS_INCLUDED_C_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_included_c_, boost::simd::tag::avx_
                            , (A0)
                            , ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                              ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                            )
  {
    typedef bool result_type;
    inline result_type operator()(A0 const& a0,A0 const& a1) const
    {
      return _mm256_testz_si256(a1, a0);
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_included_c_, boost::simd::tag::avx_
                            , (A0)
                            , ((simd_<floating_<A0>,boost::simd::tag::avx_>))
                              ((simd_<floating_<A0>,boost::simd::tag::avx_>))
                            )
  {
    typedef bool result_type;
    inline result_type operator()(A0 const& a0,A0 const& a1) const
    {
      typedef typename boost::dispatch::meta::as_integer<A0>::type iA0; 
      return is_included_c(bitwise_cast<iA0>(a0), bitwise_cast<iA0>(a1));
    }
  };
  
} } }

#endif
#endif
