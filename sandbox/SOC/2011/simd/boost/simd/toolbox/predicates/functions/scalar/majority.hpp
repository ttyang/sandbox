//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SCALAR_MAJORITY_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SCALAR_MAJORITY_HPP_INCLUDED

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::majority_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< fundamental_<A0> >)(scalar_< fundamental_<A1> >)(scalar_< fundamental_<A2> >)
                            )
  {

    typedef bool result_type;

    BOOST_SIMD_FUNCTOR_CALL(3)
    {
        return (a0&&a1)||(a1&&a2)||(a2&&a0);
    }
  };
} } }


#endif
