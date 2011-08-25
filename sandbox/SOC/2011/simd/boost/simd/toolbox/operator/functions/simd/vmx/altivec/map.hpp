//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_MAP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_MAP_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/toolbox/operator/specific/details/maybe_genmask.hpp>
#include <boost/dispatch/extension/parameters.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

////////////////////////////////////////////////////////////////////////////////
// Implement a SIMD map that apply a given function to any Altivec vector types
// This is done by enumerating all cases of function calls over the different
// vector cardinal and function arity.
////////////////////////////////////////////////////////////////////////////////

#define M6(z,n,t) typename meta::scalar_of<BOOST_PP_CAT(A,BOOST_PP_INC(n))>::type
#define M5(z,n,t) (A##n)
#define M4(z,n,t) BOOST_PP_CAT(a,BOOST_PP_INC(n))[t]
#define M3(z,n,t) details::maybe_genmask<stype>(a0(BOOST_PP_ENUM(t,M4,n)))
#define M2(z,n,t) ((simd_< BOOST_PP_TUPLE_ELEM(2,0,t) <BOOST_PP_CAT(A, BOOST_PP_INC(n))>, boost::simd::tag::altivec_>))

#define M0(z,n,t)                                                             \
namespace boost { namespace simd                             \
{                                                                             \
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::map_,boost::simd::tag::altivec_                      \
                            , BOOST_PP_REPEAT(BOOST_PP_INC(n), M5,t)          \
                            , (unspecified_<A0>)BOOST_PP_REPEAT(n,M2,t)       \
                            )                                                 \
  {                                                                           \
    typedef typename meta::                                                   \
    result_of< typename meta::                                                \
               strip<A0>::type const( BOOST_PP_ENUM(n,M6,~) )                 \
             >::type                                                          \
    rtype;                                                                    \
    typedef typename details::                                                \
    as_native< A0                                                             \
             , rtype                                                          \
             , typename meta::scalar_of<A1>::type                             \
             >::type                                                          \
    stype;                                                                    \
    typedef simd::native<stype, boost::simd::tag::altivec_> result_type;                   \
                                                                              \
    BOOST_SIMD_FUNCTOR_CALL(BOOST_PP_INC(n))                              \
    {                                                                         \
      result_type that = {{BOOST_PP_ENUM(BOOST_PP_TUPLE_ELEM(2,1,t),M3,n)}};  \
      return that;                                                            \
    }                                                                         \
  };                                                                          \
} } }                                                                         \
/**/

#define BOOST_SIMD_MAP_CALL(T,C)                      \
BOOST_PP_REPEAT_FROM_TO(1,BOOST_DISPATCH_MAX_ARITY,M0, (T,C) ) \
/**/

BOOST_SIMD_MAP_CALL(float_  ,  4 )
BOOST_SIMD_MAP_CALL(ints32_ ,  4 )
BOOST_SIMD_MAP_CALL(ints16_ ,  8 )
BOOST_SIMD_MAP_CALL(ints8_  , 16 )

#undef BOOST_SIMD_MAP_CALL
#undef M6
#undef M5
#undef M4
#undef M3
#undef M2
#undef M1
#undef M0

#endif
#endif
