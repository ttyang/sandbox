//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompnoneing file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_SSE4_1_NONE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_SSE4_1_NONE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE4_1_SUPPORT

#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/constants/true.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::none_, boost::simd::tag::sse4_1_,
                        (A0),
                        ((simd_<arithmetic_<A0>,boost::simd::tag::sse_>))
                       )
  {
    typedef bool result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return _mm_test_all_zeros(a0, True<A0>()) ;
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::none_, boost::simd::tag::sse4_1_,
                        (A0),
                        ((simd_<floating_<A0>,boost::simd::tag::sse_>))
                       )
  {
    typedef bool result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<A0>::type iA0; 
      return none(bitwise_cast<iA0>(a0)) ;
    }
  };
} } }  
#endif
#endif
