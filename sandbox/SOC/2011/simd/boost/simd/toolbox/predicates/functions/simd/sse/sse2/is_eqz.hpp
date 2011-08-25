//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_SSE_SSE2_IS_EQZ_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_SSE_SSE2_IS_EQZ_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/toolbox/predicates/functions/is_eqz.hpp>
#include <boost/simd/include/functions/bitwise_and.hpp>
#include <boost/simd/sdk/meta/templatize.hpp>
#include <boost/simd/sdk/simd/native_cast.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_eqz_, boost::simd::tag::sse2_, (A0)
                            , ((simd_<int64_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef boost::simd::native<int32_t,boost::simd::tag::sse_> type;
      const type tmp1 = is_eqz(boost::simd::native_cast<type>(a0));
      const type tmp2 = {_mm_shuffle_epi32(tmp1, _MM_SHUFFLE(2, 3, 0, 1))};
      return boost::simd::native_cast<A0>(b_and(tmp1, tmp2));
    }
  };
} } }

#endif
#endif
