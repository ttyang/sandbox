//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_FAST_FREXP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_FAST_FREXP_HPP_INCLUDED
#include <boost/mpl/vector.hpp>
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>
#include <math.h>
/////////////////////////////////////////////////////////////////////////////
// Compute fast_frexp(const A0& a0)
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::fast_frexp_, tag::cpu_, (A0)(A1)(A2)
                            , (scalar_< double_<A0> >)
                              (scalar_< double_<A1> >)
                              (scalar_< int32_<A2> >)
                            )
  { 
    typedef void result_type;
    inline void operator()(A0 const& a0,A1 & a1,A2 & a2) const
    {
      a1 = ::frexp(a0, &a2);
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::fast_frexp_, tag::cpu_, (A0)(A2)
                            , (scalar_< double_<A0> >)
                              (scalar_< int32_<A2> >)
                            )
  {
    typedef A0 result_type;    
    inline void operator()(A0 const& a0,A2 & a2) const
    {
      typedef typename dispatch::meta::as_integer<A0, signed>::type      int_type;
      A0 a1; 
      boost::simd::fast_frexp(a0, a1, a2);
      return a1; 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::fast_frexp_, tag::cpu_,
                            (A0),
                            (scalar_ < double_<A0> > )
                           )
  {
    typedef typename dispatch::meta::result_of<dispatch::meta::floating(A0)>::type mantissa;
    typedef typename dispatch::meta::as_integer<A0,signed>::type                   exponent;
    typedef boost::fusion::vector<mantissa,exponent>                               result_type;
    
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type res;
      int r1t;
      boost::fusion::at_c<0>(res) = ::frexp(a0, &r1t);
      boost::fusion::at_c<1>(res) = r1t;
      return res;
    }
  };



  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::fast_frexp_, tag::cpu_,
                            (A0),
                            (scalar_ < float_<A0> > )
                           )
  {
    typedef typename dispatch::meta::result_of<dispatch::meta::floating(A0)>::type mantissa;
    typedef typename dispatch::meta::as_integer<A0,signed>::type                   exponent;
    typedef boost::fusion::vector<mantissa,exponent>                               result_type;
    
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type res;
      boost::fusion::at_c<0>(res) = ::frexpf(a0, &boost::fusion::at_c<1>(res));
      return res;
    }
  };
} } }
#endif
