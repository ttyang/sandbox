//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.ieee toolbox - bitfloating/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.ieee components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 04/12/2010
/// 
#include <boost/simd/toolbox/ieee/include/functions/bitfloating.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/simd/include/functions/bitinteger.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>


NT2_TEST_CASE_TPL ( bitfloating_int_convert__1_0,  BOOST_SIMD_SIMD_INT_CONVERT_TYPES)
{
  using boost::simd::bitfloating;
  using boost::simd::tag::bitfloating_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<bitfloating_(vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;

} // end of test for int_convert_

NT2_TEST_CASE_TPL ( bitfloating_uint_convert__1_0,  BOOST_SIMD_SIMD_UINT_CONVERT_TYPES)
{
  using boost::simd::bitfloating;
  using boost::simd::tag::bitfloating_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<bitfloating_(vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;

} // end of test for uint_convert_
