//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_COMMON_BITS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_COMMON_BITS_HPP_INCLUDED

#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bits_, tag::cpu_,(A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned>::type  result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return simd::native_cast<result_type>(a0);
    }
  };
} } }

#endif
