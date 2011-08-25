//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_COMMON_HI_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_COMMON_HI_HPP_INCLUDED

#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/functions/shri.hpp>
#include <boost/simd/include/constants/digits.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::hi_, tag::cpu_, (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<result_type>::type int_type;

      BOOST_STATIC_CONSTANT(int_type, shift = sizeof(int_type)*4);
      BOOST_STATIC_CONSTANT(int_type, pattern = int_type(int_type(-1)<<shift));

      result_type that(shri((boost::simd::integral_constant<result_type,pattern>()&a0),shift));
      return that;
    }
  };
} } }

#endif
