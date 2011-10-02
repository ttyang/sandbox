//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 operator toolbox - map/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of operator components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// 
#include <boost/simd/toolbox/operator/include/functions/map.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>
//COMMENTED

NT2_TEST_CASE_TPL ( map_integer__2_0,  BOOST_SIMD_INTEGRAL_TYPES)
{
  
//   using boost::simd::map;
//   using boost::simd::tag::map_;
//   typedef typename boost::dispatch::meta::as_integer<T>::type iT;
//   typedef typename boost::dispatch::meta::call<map_(T,T)>::type r_t;
//   typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
//   typedef T wished_r_t;


//   // return type conformity test 
//   NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
//   std::cout << std::endl; 
//   double ulpd;
//   ulpd=0.0;


//   // specific values tests
//   NT2_TEST_EQUAL(map(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<r_t>());
//   NT2_TEST_EQUAL(map(boost::simd::One<T>(),boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
//   NT2_TEST_EQUAL(map(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
// } // end of test for integer_

// NT2_TEST_CASE_TPL ( map_real__2_0,  BOOST_SIMD_REAL_TYPES)
// {
  
//   using boost::simd::map;
//   using boost::simd::tag::map_;
//   typedef typename boost::dispatch::meta::as_integer<T>::type iT;
//   typedef typename boost::dispatch::meta::call<map_(T,T)>::type r_t;
//   typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
//   typedef T wished_r_t;


//   // return type conformity test 
//   NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
//   std::cout << std::endl; 
//   double ulpd;
//   ulpd=0.0;


//   // specific values tests
//   NT2_TEST_EQUAL(map(boost::simd::Inf<T>(), boost::simd::Inf<T>()), boost::simd::Inf<r_t>());
//   NT2_TEST_EQUAL(map(boost::simd::Minf<T>(), boost::simd::Minf<T>()), boost::simd::Minf<r_t>());
//   NT2_TEST_EQUAL(map(boost::simd::Nan<T>(), boost::simd::Nan<T>()), boost::simd::Nan<r_t>());
//   NT2_TEST_EQUAL(map(boost::simd::One<T>(),boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
//   NT2_TEST_EQUAL(map(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for floating_
