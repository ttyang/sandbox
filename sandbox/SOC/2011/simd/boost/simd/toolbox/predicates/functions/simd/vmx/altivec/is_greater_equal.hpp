//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_VMX_ALTIVEC_IS_GREATER_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_VMX_ALTIVEC_IS_GREATER_EQUAL_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/sdk/simd/native_cast.hpp>
#include <boost/simd/include/functions/complement.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_greater_equal_, boost::simd::tag::altivec_, (A0)
                            , ((simd_<float_<A0>,boost::simd::tag::altivec_>))
                              ((simd_<float_<A0>,boost::simd::tag::altivec_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that   = { simd::native_cast<A0>(vec_cmpge(a0(),a1())) };
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_greater_equal_, boost::simd::tag::altivec_, (A0)
                            , ((simd_<arithmetic_<A0>,boost::simd::tag::altivec_>))
                              ((simd_<arithmetic_<A0>,boost::simd::tag::altivec_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 lt   = { simd::native_cast<A0>(vec_cmplt(a0(),a1())) };
      A0 that = { boost::simd::complement(lt) };
      return that;
    }
  };
} } }

#endif
#endif
