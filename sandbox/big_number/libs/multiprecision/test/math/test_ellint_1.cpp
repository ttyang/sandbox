///////////////////////////////////////////////////////////////
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_

#ifdef _MSC_VER
#  define _SCL_SECURE_NO_WARNINGS
#endif

#define BOOST_MATH_OVERFLOW_ERROR_POLICY ignore_error

#if !defined(TEST_MPF_50) && !defined(TEST_BACKEND) && !defined(TEST_CPP_DEC_FLOAT) && !defined(TEST_MPFR_50)
#  define TEST_MPF_50
#  define TEST_MPFR_50
#  define TEST_CPP_DEC_FLOAT

#ifdef _MSC_VER
#pragma message("CAUTION!!: No backend type specified so testing everything.... this will take some time!!")
#endif
#ifdef __GNUC__
#pragma warning "CAUTION!!: No backend type specified so testing everything.... this will take some time!!"
#endif

#endif

#if defined(TEST_MPF_50)
#include <boost/multiprecision/gmp.hpp>
#endif
#if defined(TEST_MPFR_50)
#include <boost/multiprecision/mpfr.hpp>
#endif
#ifdef TEST_BACKEND
#include <boost/multiprecision/concepts/mp_number_architypes.hpp>
#endif
#ifdef TEST_CPP_DEC_FLOAT
#include <boost/multiprecision/cpp_dec_float.hpp>
#endif

#define SC_(x) BOOST_STRINGIZE(x)
#define TEST_UDT

#include <boost/math/special_functions/ellint_1.hpp>
#include "libs/math/test/test_ellint_1.hpp"

void expected_results()
{
   //
   // Define the max and mean errors expected for
   // various compilers and platforms.
   //
   add_expected_result(
      ".*",                          // compiler
      ".*",                          // stdlib
      ".*",                          // platform
      ".*",                          // test type(s)
      ".*",                          // test data group
      ".*", 40, 20);                 // test function
   //
   // Finish off by printing out the compiler/stdlib/platform names,
   // we do this to make it easier to mark up expected error rates.
   //
   std::cout << "Tests run with " << BOOST_COMPILER << ", " 
      << BOOST_STDLIB << ", " << BOOST_PLATFORM << std::endl;
}


int test_main(int, char* [])
{
   using namespace boost::multiprecision;
   expected_results();
   //
   // Test at:
   // 18 decimal digits: tests 80-bit long double approximations
   // 30 decimal digits: tests 128-bit long double approximations
   // 35 decimal digits: tests arbitrary precision code
   //
#ifdef TEST_MPF_50
   test_spots(mp_number<gmp_float<18> >(), "mp_number<gmp_float<18> >");
   test_spots(mp_number<gmp_float<30> >(), "mp_number<gmp_float<30> >");
   test_spots(mp_number<gmp_float<35> >(), "mp_number<gmp_float<35> >");
#endif
#ifdef TEST_MPFR_50
   test_spots(mp_number<mpfr_float_backend<18> >(), "mp_number<mpfr_float_backend<18> >");
   test_spots(mp_number<mpfr_float_backend<30> >(), "mp_number<mpfr_float_backend<30> >");
   test_spots(mp_number<mpfr_float_backend<35> >(), "mp_number<mpfr_float_backend<35> >");
#endif
#ifdef TEST_CPP_DEC_FLOAT
   test_spots(mp_number<cpp_dec_float<18> >(), "mp_number<cpp_dec_float<18> >");
   test_spots(mp_number<cpp_dec_float<30> >(), "mp_number<cpp_dec_float<30> >");
   test_spots(mp_number<cpp_dec_float<35> >(), "mp_number<cpp_dec_float<35> >");
#endif
   return 0;
}

