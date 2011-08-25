//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.bitwise toolbox - firstbitset/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.bitwise components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// 
#include <boost/simd/toolbox/bitwise/include/functions/firstbitset.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( firstbitset_float_1_0,  (float))
{
  
  using boost::simd::firstbitset;
  using boost::simd::tag::firstbitset_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<firstbitset_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(firstbitset(boost::simd::Inf<T>()), 8388608u);
  NT2_TEST_EQUAL(firstbitset(boost::simd::Minf<T>()), 8388608u);
  NT2_TEST_EQUAL(firstbitset(boost::simd::Nan<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(firstbitset(boost::simd::Signmask<T>()), boost::simd::One<r_t>()+boost::simd::Valmax<r_t>()/2);
  NT2_TEST_EQUAL(firstbitset(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for float

NT2_TEST_CASE_TPL ( firstbitset_double_1_0,  (double))
{
  
  using boost::simd::firstbitset;
  using boost::simd::tag::firstbitset_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<firstbitset_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(firstbitset(boost::simd::Inf<T>()), 4503599627370496ull);
  NT2_TEST_EQUAL(firstbitset(boost::simd::Minf<T>()), 4503599627370496ull);
  NT2_TEST_EQUAL(firstbitset(boost::simd::Nan<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(firstbitset(boost::simd::Signmask<T>()), boost::simd::One<r_t>()+boost::simd::Valmax<r_t>()/2);
  NT2_TEST_EQUAL(firstbitset(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for double

NT2_TEST_CASE_TPL ( firstbitset_signed_int__1_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  
  using boost::simd::firstbitset;
  using boost::simd::tag::firstbitset_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<firstbitset_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(firstbitset(boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(firstbitset(boost::simd::Signmask<T>()), boost::simd::One<r_t>()+boost::simd::Valmax<r_t>()/2);
  NT2_TEST_EQUAL(firstbitset(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( firstbitset_unsigned_int__1_0,  BOOST_SIMD_UNSIGNED_TYPES)
{
  
  using boost::simd::firstbitset;
  using boost::simd::tag::firstbitset_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<firstbitset_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(firstbitset(boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(firstbitset(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for unsigned_int_
