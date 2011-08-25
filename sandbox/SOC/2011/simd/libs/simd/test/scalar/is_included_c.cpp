//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.bitwise toolbox - is_included_c/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.bitwise components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// 
#include <boost/simd/toolbox/bitwise/include/functions/is_included_c.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/simd/include/functions/complement.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( is_included_c_integer__2_0,  BOOST_SIMD_INTEGRAL_TYPES)
{
  
  using boost::simd::is_included_c;
  using boost::simd::tag::is_included_c_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<is_included_c_(T,T)>::type r_t;
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
  NT2_TEST_EQUAL(is_included_c(boost::simd::Mone<T>(),boost::simd::Zero<T>()), true);
  NT2_TEST_EQUAL(is_included_c(boost::simd::One<T>(), boost::simd::One<T>()), false);
  NT2_TEST_EQUAL(is_included_c(boost::simd::One<T>(),boost::simd::Mone<T>()), false);
  NT2_TEST_EQUAL(is_included_c(boost::simd::One<T>(),boost::simd::Three<T>()), false);
  NT2_TEST_EQUAL(is_included_c(boost::simd::One<T>(),boost::simd::Two<T>()), true);
  NT2_TEST_EQUAL(is_included_c(boost::simd::One<T>(),boost::simd::Zero<T>()), true);
  NT2_TEST_EQUAL(is_included_c(boost::simd::Zero<T>(), boost::simd::Zero<T>()), true);
} // end of test for integer_
