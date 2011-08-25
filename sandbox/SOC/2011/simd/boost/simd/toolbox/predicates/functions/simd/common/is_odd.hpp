//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_COMMON_IS_ODD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_COMMON_IS_ODD_HPP_INCLUDED

#include <boost/simd/toolbox/predicates/functions/is_odd.hpp>
#include <boost/simd/include/functions/minus.hpp>
#include <boost/simd/include/functions/bitwise_and.hpp>
#include <boost/simd/include/functions/is_even.hpp>
#include <boost/simd/include/functions/is_nez.hpp>
#include <boost/simd/include/constants/one.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::is_odd_, tag::cpu_,
                         (A0)(X),
                         ((simd_<arithmetic_<A0>,X>))
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return is_nez(a0 & One<A0>());
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::is_odd_, tag::cpu_,
                         (A0)(X),
                         ((simd_<real_<A0>,X>))
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return is_even(a0-One<A0>());
    }
  };
} } }
#endif
