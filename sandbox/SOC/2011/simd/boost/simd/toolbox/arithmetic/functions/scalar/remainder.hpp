//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_REMAINDER_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_REMAINDER_HPP_INCLUDED
#include <boost/simd/include/functions/abs.hpp>
#include <boost/simd/include/functions/negate.hpp>
//#include <boost/simd/include/functions/idivfix.hpp>
#include <boost/simd/include/functions/idivround.hpp>
#include <boost/simd/include/functions/divround.hpp>

/////////////////////////////////////////////////////////////////////////////
// The remainder() function computes the remainder of dividing x by y.  The
// return value is x-n*y, where n is the value x / y, rounded to the nearest
// integer.  If the boost::simd::absolute value of x-n*y is 0.5, n is chosen to be even.
// The drem function is just an alias for the same thing.
/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::remainder_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)(scalar_< arithmetic_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if (!a1) return a0; 
	return a0-boost::simd::idivround(a0, a1)*a1; 
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::remainder_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)(scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return a0-divround(a0, a1)*a1; 
    }
  };
} } }


#endif
