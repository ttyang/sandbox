//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_LOAD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_LOAD_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_, boost::simd::tag::altivec_
                            , (A0)(A1)(A2)
                            , (iterator_< scalar_< fundamental_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_<simd_<arithmetic_<A2>,boost::simd::tag::altivec_> >))
                            )
  {

    typedef typename A2::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      result_type that = { vec_ld(a1*16,a0) };
      return that;
    }
  };
} } }

#include <boost/simd/toolbox/operator/functions/simd/vmx/altivec/load_offset.hpp>

#endif
#endif
