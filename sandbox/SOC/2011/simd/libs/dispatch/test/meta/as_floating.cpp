/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::dispatch::meta::as_real"

#include <boost/simd/sdk/config/types.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that as_floating is correct w/r to original sign
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(as_floating)
{
  using boost::dispatch::meta::as_floating;
  using boost::is_same;

  NT2_TEST( (is_same<as_floating<double       >::type,double  >::value ));
  NT2_TEST( (is_same<as_floating<float        >::type,float   >::value ));
  NT2_TEST( (is_same<as_floating<boost::simd::int64_t >::type,double  >::value ));
  NT2_TEST( (is_same<as_floating<boost::simd::int32_t >::type,float   >::value ));
  NT2_TEST( (is_same<as_floating<boost::simd::uint64_t>::type,double  >::value ));
  NT2_TEST( (is_same<as_floating<boost::simd::uint32_t>::type,float   >::value ));
}
