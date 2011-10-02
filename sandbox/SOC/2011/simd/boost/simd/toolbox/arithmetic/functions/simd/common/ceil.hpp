//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_CEIL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_CEIL_HPP_INCLUDED
#include <boost/simd/include/constants/digits.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/round2even.hpp>
#include <boost/simd/include/functions/seladd.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ceil_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return a0;
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ceil_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {

    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      const A0 d0 = round2even(a0);
      return seladd(lt(d0,a0),d0,One<A0>());
    }
  };
} } }


#endif
