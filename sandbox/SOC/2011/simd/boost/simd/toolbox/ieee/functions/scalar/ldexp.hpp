//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_LDEXP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_LDEXP_HPP_INCLUDED
#include <boost/simd/include/constants/properties.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/constants/real.hpp>

#include <boost/simd/include/functions/is_finite.hpp>
#include <boost/simd/include/functions/is_nez.hpp>
#include <boost/simd/include/functions/bitwise_andnot.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ldexp_, tag::cpu_, (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< integer_<A1> >)
                            )
  {
    typedef typename dispatch::meta::result_of<dispatch::meta::arithmetic(A0,A1)>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2) { return (a1>0)?(a0<<a1):(a0>>a1); }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ldexp_, tag::cpu_, (A0)(A1)
                            , (scalar_< real_<A0> >)(scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      // No denormal provision
      typedef typename dispatch::meta::as_integer<result_type, unsigned>::type  int_type;

      // clear exponent in x
      result_type const x(b_andnot(a0, Ldexpmask<result_type>()));

      // extract exponent and compute the new one
      int_type e    = b_and(Ldexpmask<result_type>(), a0);
      e += int_type(a1) << Nbmantissabits<result_type>(); //nmb;
      if (is_nez(a0)&&is_finite(a0)) return  b_or(x, e);
      return a0;
    }
  };
} } }

#endif
