//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_POSMAX_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_POSMAX_HPP_INCLUDED
#include <boost/dispatch/meta/strip.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::posmax_, tag::cpu_,
                         (A0)(X),
                         ((simd_<arithmetic_<A0>,X>))
                        )
  {
      typedef typename meta::scalar_of<A0>::type stype;
      typedef typename dispatch::meta::as_integer<stype, signed>::type result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename meta::scalar_of<A0>::type type;
      int p = 0;
      type m = a0[0];
      for(size_t i=1; i < boost::simd::meta::cardinal_of<A0>::value; i++)// TODO UNROLL
      {
        if (m < a0[i]){m = a0[i]; p = i; }
      }
      return p;
    }
  };
} } }
#endif
