//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.predicates toolbox - is_invalid/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.predicates components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 21/02/2011
/// 
#include <boost/simd/toolbox/predicates/include/functions/is_invalid.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/simd/sdk/meta/logical.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>


NT2_TEST_CASE_TPL ( is_invalid_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::is_invalid;
  using boost::simd::tag::is_invalid_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<is_invalid_(vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(is_invalid(-boost::simd::Zero<vT>())[0]!=0, boost::simd::False<sr_t>());
  NT2_TEST_EQUAL(is_invalid(boost::simd::Half<vT>())[0]!=0, boost::simd::False<sr_t>());
  NT2_TEST_EQUAL(is_invalid(boost::simd::Inf<vT>())[0]!=0, boost::simd::True<sr_t>());
  NT2_TEST_EQUAL(is_invalid(boost::simd::Minf<vT>())[0]!=0, boost::simd::True<sr_t>());
  NT2_TEST_EQUAL(is_invalid(boost::simd::Mone<vT>())[0]!=0, boost::simd::False<sr_t>());
  NT2_TEST_EQUAL(is_invalid(boost::simd::Nan<vT>())[0]!=0, boost::simd::True<sr_t>());
  NT2_TEST_EQUAL(is_invalid(boost::simd::One<vT>())[0]!=0, boost::simd::False<sr_t>());
  NT2_TEST_EQUAL(is_invalid(boost::simd::Quarter<vT>())[0]!=0, boost::simd::False<sr_t>());
  NT2_TEST_EQUAL(is_invalid(boost::simd::Two<vT>())[0]!=0, boost::simd::False<sr_t>());
  NT2_TEST_EQUAL(is_invalid(boost::simd::Zero<vT>())[0]!=0, boost::simd::False<sr_t>());
} // end of test for floating_
