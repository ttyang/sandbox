//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - logical_xor/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
/// 
#include <boost/simd/toolbox/arithmetic/include/functions/logical_xor.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( logical_xor_real__2_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using boost::simd::logical_xor;
  using boost::simd::tag::logical_xor_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<logical_xor_(T,T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef bool wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(logical_xor(T(0),T(1)), true, 0);
  NT2_TEST_ULP_EQUAL(logical_xor(T(3),T(0)), true, 0);
  NT2_TEST_ULP_EQUAL(logical_xor(boost::simd::Inf<T>(), boost::simd::Inf<T>()), false, 0);
  NT2_TEST_ULP_EQUAL(logical_xor(boost::simd::Minf<T>(), boost::simd::Minf<T>()), false, 0);
  NT2_TEST_ULP_EQUAL(logical_xor(boost::simd::Mone<T>(), boost::simd::Mone<T>()), false, 0);
  NT2_TEST_ULP_EQUAL(logical_xor(boost::simd::Nan<T>(), boost::simd::Nan<T>()), false, 0);
  NT2_TEST_ULP_EQUAL(logical_xor(boost::simd::One<T>(), boost::simd::One<T>()), false, 0);
  NT2_TEST_ULP_EQUAL(logical_xor(boost::simd::Zero<T>(), boost::simd::Zero<T>()), false, 0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( logical_xor_unsigned_int__2_0,  BOOST_SIMD_UNSIGNED_TYPES)
{
  
  using boost::simd::logical_xor;
  using boost::simd::tag::logical_xor_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<logical_xor_(T,T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef bool wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(logical_xor(boost::simd::One<T>(), boost::simd::One<T>()), false, 0);
  NT2_TEST_ULP_EQUAL(logical_xor(boost::simd::Zero<T>(), boost::simd::Zero<T>()), false, 0);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( logical_xor_signed_int__2_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  
  using boost::simd::logical_xor;
  using boost::simd::tag::logical_xor_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<logical_xor_(T,T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef bool wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(logical_xor(boost::simd::Mone<T>(), boost::simd::Mone<T>()), false, 0);
  NT2_TEST_ULP_EQUAL(logical_xor(boost::simd::One<T>(), boost::simd::One<T>()), false, 0);
  NT2_TEST_ULP_EQUAL(logical_xor(boost::simd::Zero<T>(), boost::simd::Zero<T>()), false, 0);
} // end of test for signed_int_
