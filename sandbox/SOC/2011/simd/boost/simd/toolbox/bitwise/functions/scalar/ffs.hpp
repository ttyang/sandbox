//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SCALAR_FFS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SCALAR_FFS_HPP_INCLUDED

#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/sdk/details/bitwise_cast.hpp>

#ifdef BOOST_MSVC
#include <intrin.h>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ffs_, tag::cpu_, (A0)
                            , (scalar_< type64_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type t1 = bitwise_cast<result_type>(a0);
      if(!t1) return 0;

    #if defined BOOST_MSVC && defined _WIN64
      unsigned long index;
      if(_BitScanForward64(&index, uint64_t(a0)))
          return index+1;
      return 0;
    #elif defined BOOST_MSVC
      unsigned long index;
      if (b_and(t1, (uint64_t(-1) >> 32)))
      {
        _BitScanForward(&index, uint32_t(t1));
        return index+1;
      }
      if(_BitScanForward(&index, uint32_t(t1 >> 32)))
        return 32+index+1;
      return 0;
    #else
      return __builtin_ffsll(t1);
    #endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ffs_, tag::cpu_
                            , (A0)
                            , (scalar_< type32_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type t1 = bitwise_cast<result_type>(a0);
    #ifdef BOOST_MSVC
      unsigned long index;
      if(_BitScanForward(&index, t1)) return index+1;
      return 0;
    #else
      return __builtin_ffs(t1);
    #endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ffs_, tag::cpu_ , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type t1 = bitwise_cast<result_type>(a0);
      return boost::simd::ffs(uint32_t(t1));
    }
  };
} } }

#endif

