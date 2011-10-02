//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SCALAR_BITWISE_NOTAND_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SCALAR_BITWISE_NOTAND_HPP_INCLUDED

#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/functions/complement.hpp>
#include <boost/simd/include/functions/bitwise_and.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::bitwise_notand_, tag::cpu_, (A0)(A1), 
				 (boost::mpl::bool_<sizeof(A0) == sizeof(A1)>), 				 
                                 ( boost::simd::tag::bitwise_notand_
				  ( scalar_<arithmetic_<A0> >, 
				    scalar_<arithmetic_<A1> >
				    )
				  ), 
                               (scalar_< arithmetic_<A0> >)
                               (scalar_< arithmetic_<A1> >)
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename dispatch::meta::as_integer<A0, unsigned>::type bts;
      return bitwise_cast<A0>(b_and(b_not(bitwise_cast<bts>(a0)),
					 bitwise_cast<bts>(a1)
					 )
				   ); 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_notand_, tag::cpu_, (A0)(A1)
                            , (scalar_< bool_<A0> >)
                              (scalar_< bool_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2) { return !a0 && a1; }
  };
} } }

#endif
