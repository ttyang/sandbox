//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SCALAR_ROR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SCALAR_ROR_HPP_INCLUDED

#include <boost/simd/toolbox/bitwise/functions/ror.hpp>
#include <boost/simd/include/functions/bitwise_or.hpp>
#include <boost/simd/include/functions/shli.hpp>
#include <boost/simd/include/functions/shri.hpp>
#include <boost/simd/sdk/details/bitwise_cast.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ror_, tag::cpu_, (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return b_or(shri(a0, a1), shli(a0, (sizeof(A0)*CHAR_BIT-a1)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ror_, tag::cpu_, (A0)(A1)
                            , (scalar_< floating_<A0> >)(scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename dispatch::meta::as_integer<A0, unsigned>::type itype;
      const itype ia0 = bitwise_cast<itype>(a0);
      return bitwise_cast<result_type>(
                                        shri(ia0,a1) |
                                        shli(ia0, (sizeof(A0)*CHAR_BIT-a1))
                                      ); 
    }
  };
} } }

#endif
