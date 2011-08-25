//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_SSE_SSE2_IS_GREATER_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_SSE_SSE2_IS_GREATER_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/sdk/simd/native_cast.hpp>
#include <boost/simd/include/constants/properties.hpp>
#include <boost/simd/include/functions/is_equal.hpp>
#include <boost/simd/include/functions/minus.hpp>
#include <boost/simd/include/functions/bitwise_or.hpp>
#include <boost/simd/include/functions/bitwise_and.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_greater_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                              ((simd_<double_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = { _mm_cmpgt_pd(a0,a1) };
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_greater_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<float_<A0>,boost::simd::tag::sse_>))
                              ((simd_<float_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = { _mm_cmpgt_ps(a0,a1) };
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_greater_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<unsigned_<A0>,boost::simd::tag::sse_>))
                              ((simd_<unsigned_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::as_integer<A0, signed>::type stype;
      return  native_cast<A0>
              ( boost::simd::gt ( native_cast<stype>(a0) - Signmask<stype>()
                        , native_cast<stype>(a1) - Signmask<stype>()
                        )
              );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_greater_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<int8_<A0>,boost::simd::tag::sse_>))
                              ((simd_<int8_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = { _mm_cmpgt_epi8(a0,a1)  };
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_greater_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<int16_<A0>,boost::simd::tag::sse_>))
                              ((simd_<int16_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = { _mm_cmpgt_epi16(a0,a1)  };
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_greater_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<int32_<A0>,boost::simd::tag::sse_>))
                              ((simd_<int32_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = { _mm_cmpgt_epi32(a0,a1)  };
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_greater_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<int64_<A0>,boost::simd::tag::sse_>))
                              ((simd_<int64_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::downgrade<A0, signed>::type type;
      type sa0 = { a0 };
      type sa1 = { a1 };
      type al  = { _mm_shuffle_epi32(sa0, _MM_SHUFFLE(2, 2, 0, 0)) };
      type bl  = { _mm_shuffle_epi32(sa1, _MM_SHUFFLE(2, 2, 0, 0)) };
      type ah  = { _mm_shuffle_epi32(sa0, _MM_SHUFFLE(3, 3, 1, 1)) };
      type bh  = { _mm_shuffle_epi32(sa1, _MM_SHUFFLE(3, 3, 1, 1)) };

      A0 that  = { boost::simd::gt(ah,bh) | (boost::simd::eq(ah,bh) & boost::simd::gt(al,bl)) };
      return that;
    }
  };
} } }

#endif
#endif
