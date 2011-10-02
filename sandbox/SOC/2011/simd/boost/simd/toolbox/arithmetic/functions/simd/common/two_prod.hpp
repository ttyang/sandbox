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

#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/functions/minus.hpp>
#include <boost/simd/include/functions/is_inf.hpp>
#include <boost/simd/include/functions/select.hpp>
#include <boost/simd/include/functions/two_split.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/bitwise_or.hpp>
#include <boost/simd/include/functions/bitwise_and.hpp>
#include <boost/simd/toolbox/arithmetic/functions/two_prod.hpp>

#include <boost/fusion/tuple.hpp>

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
    typedef typename boost::fusion::tuple<A0,A0> result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      result_type res;
      eval(a0,a1, boost::fusion::at_c<0>(res),boost::fusion::at_c<1>(res));
      return res;
    }

    private:
    inline void eval(A0 const& a, A0 const& b, A0& r0, A0& r1)const
    {
      r0 = a*b;
      A0 a1, a2, b1, b2, isinf; 
      isinf = b_and(b_or(is_inf(b), is_inf(a)), is_inf(r0)); 
      boost::fusion::tie(a1, a2) = two_split(a);
      boost::fusion::tie(b1, b2) = two_split(b);
      r1 = sel(isinf, Zero<A0>(), a2*b2 -(((r0-a1*b1)-a2*b1)-a1*b2));
    }
  };
} } }
#endif
