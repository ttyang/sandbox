//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_SUM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_SUM_HPP_INCLUDED

#include <boost/simd/toolbox/reduction/functions/sum.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::sum_, tag::cpu_,
                      (A0)(X),
                      ((simd_<arithmetic_<A0>,X>))
                     )
  {
    typedef typename meta::scalar_of<A0>::type   result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef result_type     type;
      return boost::fusion::fold(a0,Zero<type>(),dispatch::functor<boost::simd::tag::plus_>());
    }
  };
} } }
#endif
