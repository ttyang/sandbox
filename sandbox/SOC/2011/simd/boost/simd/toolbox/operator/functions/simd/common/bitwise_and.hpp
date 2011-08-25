//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_BITWISE_AND_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_BITWISE_AND_HPP_INCLUDED

#include <boost/simd/sdk/simd/native_cast.hpp>

#include <boost/mpl/logical.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF(boost::simd::tag::bitwise_and_, tag::cpu_,
                                (A0)(A1)(X),
                                (boost::mpl::not_< boost::is_same<A0, A1> >),
                                (boost::simd::tag::bitwise_and_( simd_<arithmetic_<A0>,X>
                                                  , simd_<arithmetic_<A1>,X>
                                                  )
                                ),
                                ((simd_<arithmetic_<A0>,X>))
                                ((simd_<arithmetic_<A1>,X>))
                              )
  {
    typedef A0 result_type;
    
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return bitwise_and(a0, simd::native_cast<A0>(a1));
    }
  };
} } }

#endif
