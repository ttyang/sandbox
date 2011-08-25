//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_COMMON_NEGIF_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_COMMON_NEGIF_HPP_INCLUDED

#include <boost/simd/sdk/meta/size.hpp>
#include <boost/simd/include/functions/is_true.hpp>
#include <boost/simd/include/functions/select.hpp>
#include <boost/simd/include/constants/properties.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::negif_, tag::cpu_, (A0)(A1)(X)
                                , (boost::mpl::equal_to < boost::mpl::sizeof_<A0>
                                                        , boost::mpl::sizeof_<A1>
                                                        >
                                  )
                                , (boost::simd::tag::negif_( simd_<arithmetic_<A0>,X>
                                              , simd_<signed_<A1>,X>
                                              )
                                  )
                                , ((simd_<arithmetic_<A0>,X>))
                                  ((simd_<signed_<A1>,X>))
                       )
  {
    typedef A1 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2) { return  sel(is_true(a0),-a1,a1); }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::negif_, tag::cpu_, (A0)(A1)(X)
                                , (boost::mpl::equal_to < boost::mpl::sizeof_<A0>
                                                        , boost::mpl::sizeof_<A1>
                                                        >
                                  )
                                , (boost::simd::tag::negif_( simd_<arithmetic_<A0>,X>
                                              , simd_<real_<A1>,X>
                                              )
                                  )
                                , ((simd_<arithmetic_<A0>,X>))
                                  ((simd_<real_<A1>,X>))
                       )
  {
    typedef A1 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2) { return b_xor(a1,b_and(is_true(a0),boost::simd::Signmask<A0>())); }
  };
} } }

#endif
