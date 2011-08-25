//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_PROD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_PROD_HPP_INCLUDED

#include <boost/simd/toolbox/reduction/functions/prod.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::prod_, tag::cpu_,
                       (A0)(X),
                       ((simd_<arithmetic_<A0>,X>))
                      )
  {
    typedef typename meta::scalar_of<A0>::type   result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef result_type     type;
      return boost::fusion::fold(a0,One<type>(),dispatch::functor<boost::simd::tag::multiplies_>());
    }
  };
} } }
#endif
