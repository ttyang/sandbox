//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_IS_SIMD_LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_IS_SIMD_LOGICAL_HPP_INCLUDED
#include <boost/simd/include/functions/is_equal.hpp>
#include <boost/simd/include/functions/bitwise_all.hpp>
#include <boost/simd/include/functions/genmask.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_simd_logical_, tag::cpu_,(A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef bool result_type;
    BOOST_SIMD_FUNCTOR_CALL(1) {
      typedef typename boost::dispatch::meta::as_integer<A0>::type iA0; 
      return bitwise_all(eq(bitwise_cast<iA0>(a0), genmask(bitwise_cast<iA0>(a0))));
    }
  };
} } }

#endif
