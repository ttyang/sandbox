//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/math/concepts/real_concept.hpp>
#include <boost/test/included/test_exec_monitor.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/math/tools/stats.hpp>
#include <boost/math/tools/test.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/array.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/math/special_functions/cbrt.hpp>

#include "handle_test_result.hpp"

//
// DESCRIPTION:
// ~~~~~~~~~~~~
//
// This file tests the function cbrt.  The accuracy tests
// use values generated with NTL::RR at 1000-bit precision
// and our generic versions of these functions.
//
// Note that when this file is first run on a new platform many of
// these tests will fail: the default accuracy is 1 epsilon which
// is too tight for most platforms.  In this situation you will 
// need to cast a human eye over the error rates reported and make
// a judgement as to whether they are acceptable.  Either way please
// report the results to the Boost mailing list.  Acceptable rates of
// error are marked up below as a series of regular expressions that
// identify the compiler/stdlib/platform/data-type/test-data/test-function
// along with the maximum expected peek and RMS mean errors for that
// test.
//

void expected_results()
{
   //
   // Define the max and mean errors expected for
   // various compilers and platforms.
   //

   //
   // Finish off by printing out the compiler/stdlib/platform names,
   // we do this to make it easier to mark up expected error rates.
   //
   std::cout << "Tests run with " << BOOST_COMPILER << ", " 
      << BOOST_STDLIB << ", " << BOOST_PLATFORM << std::endl;
}


template <class T>
void do_test_cbrt(const T& data, const char* type_name, const char* test_name)
{
   typedef typename T::value_type row_type;
   typedef typename row_type::value_type value_type;

   typedef value_type (*pg)(value_type);
   pg funcp = boost::math::cbrt;

   boost::math::tools::test_result<value_type> result;

   std::cout << "Testing " << test_name << " with type " << type_name
      << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

   //
   // test cbrt against data:
   //
   result = boost::math::tools::test(
      data, 
      boost::lambda::bind(funcp, 
         boost::lambda::ret<value_type>(boost::lambda::_1[1])), 
      boost::lambda::ret<value_type>(boost::lambda::_1[0]));
   result += boost::math::tools::test(
      data, 
      boost::lambda::bind(funcp, 
         -boost::lambda::ret<value_type>(boost::lambda::_1[1])), 
      -boost::lambda::ret<value_type>(boost::lambda::_1[0]));
   handle_test_result(result, data[result.worst()], result.worst(), type_name, "boost::math::cbrt", test_name);
   std::cout << std::endl;
}
template <class T>
void test_cbrt(T, const char* name)
{
   //
   // The actual test data is rather verbose, so it's in a separate file
   //
   // The contents are as follows, each row of data contains
   // three items, input value a, input value b and erf(a, b):
   // 
#  include "cbrt_data.ipp"

   do_test_cbrt(cbrt_data, name, "cbrt Function");

}

int test_main(int, char* [])
{
   test_cbrt(0.1F, "float");
   test_cbrt(0.1, "double");
   test_cbrt(0.1L, "long double");
#ifndef BOOST_MATH_NO_REAL_CONCEPT_TESTS
   test_cbrt(boost::math::concepts::real_concept(0.1), "real_concept");
#endif
   return 0;
}


