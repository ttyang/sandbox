//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.ieee toolbox - saturate_at/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.ieee components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 20/03/2011
///

//COMMENTED
//#include <boost/simd/toolbox/ieee/include/functions/saturate_at.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>


NT2_TEST_CASE_TPL ( saturate_at_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
//   using boost::simd::saturate_at;
//   using boost::simd::tag::saturate_at_;
//   using boost::simd::load; 
//   using boost::simd::native;
//   using boost::simd::meta::cardinal_of;
//   typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
//   typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
//   typedef native<T,ext_t>                        n_t;
//   typedef n_t                                     vT;
//   typedef typename boost::dispatch::meta::as_integer<T>::type iT;
//   typedef native<iT,ext_t>                       ivT;
//   typedef typename boost::dispatch::meta::call<saturate_at_<boost::simd::tag::Pi>(vT)>::type r_t;
//   typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
//   typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
//   double ulpd;
//   ulpd=0.0;

} // end of test for real_
