//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_TWO_PROD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_TWO_PROD_HPP_INCLUDED
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/two_split.hpp>
#include <boost/simd/include/functions/is_inf.hpp>
#include <boost/simd/include/functions/select.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::two_prod_, tag::cpu_,
                           (A0)(X),
                           ((simd_<arithmetic_<A0>,X>))
                           ((simd_<arithmetic_<A0>,X>))
                          )
  {
      typedef A0                    str_t;
      typedef typename boost::fusion::tuple<str_t, str_t> result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      result_type res;
      eval(a0,a1, boost::fusion::at_c<0>(res),boost::fusion::at_c<1>(res));
      return res;
    }
  private:
    template<class AA0,class AA1,class R0,class R1> inline void
    eval(AA0 const& a, AA1 const& b, R0& r0, R1& r1)const
    {
      r0  = a*b;
      AA0 isinf = b_and(b_or(is_inf(b), is_inf(a)), is_inf(r0)); 
      AA0 a1, a2, b1, b2;
      boost::fusion::tie(a1, a2) = two_split(a);
      boost::fusion::tie(b1, b2) = two_split(b);
      r1 = sel(isinf, Zero<R1>(), a2*b2 -(((r0-a1*b1)-a2*b1)-a1*b2));
    }
  };
} } }
#endif
