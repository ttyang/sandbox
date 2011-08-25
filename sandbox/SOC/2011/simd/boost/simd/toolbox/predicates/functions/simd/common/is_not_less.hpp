//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_COMMON_IS_NOT_LESS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_COMMON_IS_NOT_LESS_HPP_INCLUDED

#include <boost/simd/toolbox/predicates/functions/is_not_less.hpp>
#include <boost/simd/include/functions/complement.hpp>
#include <boost/simd/include/functions/is_less.hpp>
#include <boost/simd/include/functions/is_greater_equal.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_not_less_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return b_not(lt(a0,a1));
    }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is integer_
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::is_not_less_, tag::cpu_,
                              (A0)(X),
                              ((simd_<integer_<A0>,X>))
                              ((simd_<integer_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return ge(a0,a1);
    }
  };
} } }

#endif
