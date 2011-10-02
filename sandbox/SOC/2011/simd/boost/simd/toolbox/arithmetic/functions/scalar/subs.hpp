//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_SUBS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_SUBS_HPP_INCLUDED

#include <boost/simd/toolbox/arithmetic/functions/subs.hpp>
#include <boost/simd/include/functions/saturate.hpp>
#include <boost/simd/include/functions/adds.hpp>
#include <boost/simd/include/functions/is_greater.hpp>
#include <boost/simd/include/functions/is_equal.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/dispatch/meta/upgrade.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is integer_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::subs_, tag::cpu_
                            , (A0)
                            , (scalar_< integer_<A0> >)(scalar_< integer_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::upgrade<A0>::type utype; 
      return A0(boost::simd::saturate<A0>(utype(a0)-utype(a1))); 
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::subs_, tag::cpu_
                            , (A0)
                            , (scalar_< unsigned_<A0> >)(scalar_< unsigned_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if (gt(a0, a1))
        return a0-a1;
      else
        return Zero<A0>(); 
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::subs_, tag::cpu_
                            , (A0)
                            , (scalar_< int64_<A0> >)(scalar_< int64_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if (eq(a1, Valmin<A0>()))
      {
        if (a0 >= Mone<A0>()) return Valmax<A0>(); 
          return adds(adds(a0, Valmax<A0>()),One<A0>());
      }
      return boost::simd::adds(a0, -a1);     
    }
  };
} } }




#endif
