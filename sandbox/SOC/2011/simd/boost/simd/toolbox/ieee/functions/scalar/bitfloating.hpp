//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_BITFLOATING_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_BITFLOATING_HPP_INCLUDED
#include <boost/dispatch/meta/as_real.hpp>
#include <boost/simd/include/constants/digits.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::bitfloating_, tag::cpu_,
                             (A0),
                             (scalar_<arithmetic_<A0> > )
                            )
  {
    typedef typename dispatch::meta::as_real<A0>::type result_type; 
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return a0 >= Zero<A0>() ?
	bitwise_cast<result_type>(a0) :
	bitwise_cast<result_type>((One<A0>() << (8*sizeof(A0)-1))-a0);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::bitfloating_, tag::cpu_,
                             (A0),
                             (scalar_<unsigned_<A0> > )
                            )
  {
    typedef typename dispatch::meta::as_real<A0>::type result_type; 
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return boost::simd::bitwise_cast<result_type>(a0); 
    }
  };
} } }
#endif
