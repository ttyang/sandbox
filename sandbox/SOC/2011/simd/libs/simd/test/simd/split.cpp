//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 swar toolbox - split/simd Mode"
//COMMENTED
//////////////////////////////////////////////////////////////////////////////
// unit test behavior of swar components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
/// 
#include <boost/simd/toolbox/swar/include/functions/split.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/fusion/tuple.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>
//COMMENTED

NT2_TEST_CASE_TPL ( split_lt_64__1_0,  (boost::simd::int16_t)(boost::simd::uint16_t)(boost::simd::int32_t)(boost::simd::uint32_t)(boost::simd::int8_t)(boost::simd::uint8_t)(float))
{
  using boost::simd::split;
  using boost::simd::tag::split_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<split_(vT)>::type r_t;
  typedef typename boost::dispatch::meta::call<split_(T)>::type sr_t;
  typedef typename boost::dispatch::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


//   // specific values tests
//   typedef typename boost::simd::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
//   typedef typename boost::simd::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
//   {
//     r_t res = split(boost::simd::One<vT>());
//     NT2_TEST_EQUAL( boost::fusion::get<0>(res), boost::simd::One<r_t>());
//     NT2_TEST_EQUAL( boost::fusion::get<1>(res), boost::simd::One<r_t>());
//   }
//   {
//     r_t res = split(boost::simd::Zero<vT>());
//     NT2_TEST_EQUAL( boost::fusion::get<0>(res), boost::simd::Zero<r_t>());
//     NT2_TEST_EQUAL( boost::fusion::get<1>(res), boost::simd::Zero<r_t>());
//   }
} // end of test for lt_64_
