///////////////////////////////////////////////////////////////
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_

#include <boost/detail/lightweight_test.hpp>

#if !defined(TEST_MPF50) && !defined(TEST_MPF) && !defined(TEST_BACKEND) && !defined(TEST_MPZ) && !defined(TEST_E_FLOAT) && !defined(TEST_MPFR) && !defined(TEST_MPFR_50)
#  define TEST_MPF50
#  define TEST_MPF
#  define TEST_BACKEND
#  define TEST_MPZ
#  define TEST_MPFR
#  define TEST_MPFR_50
#  define TEST_E_FLOAT

#ifdef _MSC_VER
#pragma message("CAUTION!!: No backend type specified so testing everything.... this will take some time!!")
#endif
#ifdef __GNUC__
#pragma warning "CAUTION!!: No backend type specified so testing everything.... this will take some time!!"
#endif

#endif

#if defined(TEST_MPF50) || defined(TEST_MPF) || defined(TEST_MPZ)
#include <boost/math/big_number/gmp.hpp>
#endif
#ifdef TEST_BACKEND
#include <boost/math/concepts/big_number_architypes.hpp>
#endif
#ifdef TEST_E_FLOAT
#include <boost/math/big_number/e_float.hpp>
#endif
#if defined(TEST_MPFR) || defined(TEST_MPFR_50)
#include <boost/math/big_number/mpfr.hpp>
#endif

#define PRINT(x)\
   std::cout << BOOST_STRINGIZE(x) << " = " << std::numeric_limits<Number>::x << std::endl;

template <class Number>
void test()
{
   //
   // Note really a test just yet, but we can at least print out all the values:
   //
   std::cout << "numeric_limits values for type " << typeid(Number).name() << std::endl;

   PRINT(is_specialized);
   PRINT(min());
   PRINT(max());
   PRINT(lowest());
   PRINT(digits);
   PRINT(digits10);
   PRINT(max_digits10);
   PRINT(is_signed);
   PRINT(is_integer);
   PRINT(is_exact);
   PRINT(radix);
   PRINT(epsilon());
   PRINT(round_error());
   PRINT(min_exponent);
   PRINT(min_exponent10);
   PRINT(max_exponent);
   PRINT(max_exponent10);
   PRINT(has_infinity);
   PRINT(has_quiet_NaN);
   PRINT(has_signaling_NaN);
   PRINT(has_denorm);
   PRINT(has_denorm_loss);
   PRINT(infinity());
   PRINT(quiet_NaN());
   PRINT(signaling_NaN());
   PRINT(denorm_min());
   PRINT(is_iec559);
   PRINT(is_bounded);
   PRINT(is_modulo);
   PRINT(traps);
   PRINT(tinyness_before);
   PRINT(round_style);
}


int main()
{
#ifdef TEST_BACKEND
   test<boost::math::big_number<boost::math::concepts::big_number_backend_real_architype> >();
#endif
#ifdef TEST_MPF50
   test<boost::math::mpf_real_50>();
#endif
#ifdef TEST_MPF
   boost::math::mpf_real::default_precision(1000);
   /*
   boost::math::mpf_real r;
   r.precision(50);
   BOOST_TEST(r.precision() >= 50);
   */
   BOOST_TEST(boost::math::mpf_real::default_precision() == 1000);
   test<boost::math::mpf_real>();
#endif
#ifdef TEST_MPZ
   test<boost::math::mpz_int>();
#endif
#ifdef TEST_E_FLOAT
   test<boost::math::e_float>();
#endif
#ifdef TEST_MPFR
   test<boost::math::mpfr_real>();
#endif
#ifdef TEST_MPFR_50
   test<boost::math::mpfr_real_50>();
#endif
   return boost::report_errors();
}

