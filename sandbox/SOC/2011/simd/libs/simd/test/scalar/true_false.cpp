/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::constants true/false"

#include <boost/simd/include/constants/true_false.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test value of true/false constants for every base real types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( true_false_value, BOOST_SIMD_TYPES )
{
  NT2_TEST_EQUAL( boost::simd::False<T>(), static_cast<T>(0) );
  NT2_TEST_EQUAL( boost::simd::True<T>() , static_cast<T>(1) );
}
