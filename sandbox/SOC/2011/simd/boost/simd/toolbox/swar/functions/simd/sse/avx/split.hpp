//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_SPLIT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_SPLIT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/simd/sdk/meta/templatize.hpp>
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/simd/include/constants/digits.hpp>
#include <boost/fusion/tuple.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::split_, boost::simd::tag::avx_,
				    (A0)(A1),
				    ((simd_<single_<A0>,boost::simd::tag::avx_>))
				    ((simd_<double_<A1>,boost::simd::tag::avx_>))
				    ((simd_<double_<A1>,boost::simd::tag::avx_>))
				    )
  {
    typedef int result_type; 
    inline int operator()(const A0 & a0,  A1& a1, A1& a2)const
    {
      a1 = _mm256_cvtps_pd(_mm256_extractf128_ps(a0, 0)) ;
      a2 = _mm256_cvtps_pd(_mm256_extractf128_ps(a0, 1)) ;
      return 0;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::split_, boost::simd::tag::avx_,
				    (A0),
				    ((simd_<single_<A0>,boost::simd::tag::avx_>))
				    )
  {
    typedef typename dispatch::meta::upgrade<A0>::type                 utype;
    typedef boost::fusion::tuple<utype,utype>                    result_type;
    

    inline result_type operator()(const A0 & a0)const
    {
      result_type res; 
      split(a0, boost::fusion::at_c<0>(res), boost::fusion::at_c<1>(res));
      return res;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::split_, boost::simd::tag::avx_
                                      , (A0)(A1)
                                      , (boost::mpl::and_ <
                                            boost::mpl::not_< boost::is_same<A0, typename dispatch::meta::upgrade<A0>::type> >,
                                            boost::is_same<A1, typename dispatch::meta::upgrade<A0>::type>
                                        >)
                                      , (boost::simd::tag::split_(simd_<arithmetic_<A0>,boost::simd::tag::avx_>
                                                                 ,simd_<arithmetic_<A1>,boost::simd::tag::avx_>
                                                                 ,simd_<arithmetic_<A1>,boost::simd::tag::avx_>
                                                                 )
                                        ),
                                        ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                                        ((simd_<arithmetic_<A1>,boost::simd::tag::avx_>))
                                        ((simd_<arithmetic_<A1>,boost::simd::tag::avx_>))
                                      ) 
  {
    typedef int result_type;
    inline int operator()(const A0 & a0,  A1& a1, A1& a2)const
    {
      typedef typename dispatch::meta::scalar_of<A0>::type sA0;
      typedef typename dispatch::meta::scalar_of<A1>::type sA1;
      typedef native<sA1,tag::sse_> A1_sse_;
      typedef native<sA0,tag::sse_> A0_sse_;
      A0_sse_ a00 = {_mm256_extractf128_si256(a0, 0)};
      A0_sse_ a01 = {_mm256_extractf128_si256(a0, 1)};
      A1_sse_ ha000, ha001; 
      split(a00, ha000, ha001);
      a1 = _mm256_insertf128_si256(a1, ha000, 0);
      a1 = _mm256_insertf128_si256(a1, ha001, 1); 
      A1_sse_ ha010, ha011; 
      split(a01, ha010, ha011);
      a2 = _mm256_insertf128_si256(a2, ha010, 0);
      a2 = _mm256_insertf128_si256(a2, ha011, 1); 
      return 0;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::split_, boost::simd::tag::avx_,
				    (A0),
				    ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
				    )
  {
    typedef typename dispatch::meta::upgrade<A0>::type                 utype;
    typedef boost::fusion::tuple<utype,utype>                    result_type;
    

    inline result_type operator()(const A0 & a0)const
    {
      result_type res; 
      split(a0, boost::fusion::at_c<0>(res), boost::fusion::at_c<1>(res));
      return res;
    }
  };

  
} } }
#endif
#endif
