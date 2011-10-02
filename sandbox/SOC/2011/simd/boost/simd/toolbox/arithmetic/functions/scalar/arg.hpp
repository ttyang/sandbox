//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_ARG_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_ARG_HPP_INCLUDED
#include <boost/simd/include/constants/pi.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/functions/is_gez.hpp>
#include <boost/simd/include/functions/is_ltz.hpp>
#include <boost/simd/include/functions/is_nan.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is signed_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::arg_, tag::cpu_
                            , (A0)
                            , (scalar_< signed_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::result_of<boost::dispatch::meta::floating(A0)>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return (is_ltz(a0))*Pi<result_type>();
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::arg_, tag::cpu_
                            , (A0)
                            , (scalar_< unsigned_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::result_of<boost::dispatch::meta::floating(A0)>::type result_type;

    inline result_type operator()(const A0&)const
    {
      return Zero<result_type>();
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::arg_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::result_of<boost::dispatch::meta::floating(A0)>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      if (is_nan(a0)) return a0;
      if (is_gez(a0)) return Zero<A0>();
      return Pi<A0>();
    }
  };
} } }


#endif
