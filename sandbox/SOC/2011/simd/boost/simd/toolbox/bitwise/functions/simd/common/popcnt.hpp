//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_COMMON_POPCNT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_COMMON_POPCNT_HPP_INCLUDED

#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/functions/rem.hpp>
#include <boost/simd/include/functions/shri.hpp>
#include <boost/simd/include/constants/digits.hpp>
#include <boost/simd/include/functions/bitwise_notand.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::popcnt_, tag::cpu_, (A0)(X)
                            , ((simd_<int8_<A0>,X>))
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      const result_type m1  = boost::simd::integral_constant<result_type,0x55>(); //binary: 0101...
      const result_type m2  = boost::simd::integral_constant<result_type,0x33>(); //binary: 00110011..
      const result_type m4  = boost::simd::integral_constant<result_type,0x0f>(); //binary:  4 zeros,  4 ones ...
      result_type x = simd::native_cast<result_type>(a0);
      x -= (shri(x, 1)) & m1;             //put count of each 2 bits into those 2 bits
      x = (x & m2) + (shri(x, 2) & m2); //put count of each 4 bits into those 4 bits
      x = (x + shri(x, 4)) & m4;        //put count of each 8 bits into those 8 bits
      return x & boost::simd::integral_constant<result_type,0x7f > ();
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::popcnt_, tag::cpu_, (A0)(X)
                            , ((simd_<int64_<A0>,X>))
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      const result_type m1  = boost::simd::integral_constant<result_type,0x5555555555555555ULL>(); //binary: 0101...
      const result_type m2  = boost::simd::integral_constant<result_type,0x3333333333333333ULL>(); //binary: 00110011..
      const result_type m4  = boost::simd::integral_constant<result_type,0x0f0f0f0f0f0f0f0fULL>(); //binary:  4 zeros,  4 ones ...
      result_type x = simd::native_cast<result_type>(a0);
      x -= (shri(x, 1)) & m1;             //put count of each 2 bits into those 2 bits
      x = (x & m2) + (shri(x, 2) & m2); //put count of each 4 bits into those 4 bits
      x = (x + shri(x, 4)) & m4;        //put count of each 8 bits into those 8 bits
      x += shri(x, 8);  //put count of each 16 bits into their lowest 8 bits
      x += shri(x, 16);  //put count of each 32 bits into their lowest 8 bits
      x += shri(x, 32);  //put count of each 64 bits into their lowest 8 bits
      return x & boost::simd::integral_constant<result_type,0x7f > ();
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::popcnt_, tag::cpu_, (A0)(X)
                            , ((simd_<int16_<A0>,X>))
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      const result_type m1  = boost::simd::integral_constant<result_type,0x5555>(); //binary: 0101...
      const result_type m2  = boost::simd::integral_constant<result_type,0x3333>(); //binary: 00110011..
      const result_type m4  = boost::simd::integral_constant<result_type,0x0f0f>(); //binary:  4 zeros,  4 ones ...
      result_type x = simd::native_cast<result_type>(a0);
      x -= (shri(x, 1)) & m1;             //put count of each 2 bits into those 2 bits
      x = (x & m2) + (shri(x, 2) & m2); //put count of each 4 bits into those 4 bits
      x = (x + shri(x, 4)) & m4;        //put count of each 8 bits into those 8 bits
      x += shri(x, 8);  //put count of each 16 bits into their lowest 8 bits
      return x & boost::simd::integral_constant<result_type,0x7f > ();
      }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::popcnt_, tag::cpu_, (A0)(X)
                            , ((simd_<int32_<A0>,X>))
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      const result_type m1  = boost::simd::integral_constant<result_type,0x55555555>(); //binary: 0101...
      const result_type m2  = boost::simd::integral_constant<result_type,0x33333333>(); //binary: 00110011..
      const result_type m4  = boost::simd::integral_constant<result_type,0x0f0f0f0f>(); //binary:  4 zeros,  4 ones ...
      result_type x = simd::native_cast<result_type>(a0);
      x -= (shri(x, 1)) & m1;             //put count of each 2 bits into those 2 bits
      x = (x & m2) + (shri(x, 2) & m2); //put count of each 4 bits into those 4 bits
      x = (x + shri(x, 4)) & m4;        //put count of each 8 bits into those 8 bits
      x += shri(x, 8);  //put count of each 16 bits into their lowest 8 bits
      x += shri(x, 16);  //put count of each 32 bits into their lowest 8 bits
      return x & boost::simd::integral_constant<result_type,0x7f > ();
      }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::popcnt_, tag::cpu_, (A0)(X)
                            , ((simd_<real_<A0>,X>))
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return popcnt(simd::native_cast<result_type>(a0));
    }
  };
} } }

#endif
