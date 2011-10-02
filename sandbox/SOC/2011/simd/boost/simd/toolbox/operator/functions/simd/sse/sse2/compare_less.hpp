//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_COMPARE_LESS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_COMPARE_LESS_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/include/functions/is_less.hpp>
#include <boost/simd/include/functions/is_greater.hpp>
#include <boost/simd/include/functions/reversebits.hpp>
#include <boost/simd/toolbox/operator/functions/simd/common/details/compare_less_helper.hpp>

// #ifndef NT2_COMPARE_LESS_HELPER
// #define NT2_COMPARE_LESS_HELPER
// ////////////////////////////////////////////////////////////////////////////////
// // Local shared helper
// ////////////////////////////////////////////////////////////////////////////////
// namespace boost { namespace simd { namespace details
// {
//   template<class T>
//   inline bool compare_less_helper(T mask_lt, T mask_gt)
//   {
//     unsigned int mlt = boost::simd::reversebits(mask_lt);
//     unsigned int mgt = boost::simd::reversebits(mask_gt);
//     return (mlt > mgt) && mlt; 
//   }
// } } }
// #endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::compare_less_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                              ((simd_<double_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef bool result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      unsigned int mask_a_lt_b =  _mm_movemask_pd(lt(a0,a1));
      unsigned int mask_a_gt_b =  _mm_movemask_pd(gt(a0,a1));
      return boost::simd::details::compare_less_helper(mask_a_lt_b,mask_a_gt_b);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::compare_less_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                              ((simd_<single_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef bool result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      unsigned int mask_a_lt_b =  _mm_movemask_ps(lt(a0,a1));
      unsigned int mask_a_gt_b =  _mm_movemask_ps(gt(a0,a1));
      return boost::simd::details::compare_less_helper(mask_a_lt_b,mask_a_gt_b);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::compare_less_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<integer_<A0>,boost::simd::tag::sse_>))
                              ((simd_<integer_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef bool result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      unsigned int mask_a_lt_b =  _mm_movemask_epi8(lt(a0,a1));
      unsigned int mask_a_gt_b =  _mm_movemask_epi8(gt(a0,a1));
      return boost::simd::details::compare_less_helper(mask_a_lt_b,mask_a_gt_b);
    }
  };
} } }

#endif
#endif
