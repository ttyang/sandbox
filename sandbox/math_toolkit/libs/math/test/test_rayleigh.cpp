// Copyright John Maddock 2006.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// test_rayleigh.cpp

#define BOOST_MATH_THROW_ON_DOMAIN_ERROR
#define BOOST_MATH_THROW_ON_OVERFLOW_ERROR

#ifdef _MSC_VER
#  pragma warning(disable: 4127) // conditional expression is constant.
#  pragma warning(disable: 4100) // unreferenced formal parameter.
#  pragma warning(disable: 4512) // assignment operator could not be generated.
#  pragma warning(disable: 4510) // default constructor could not be generated.
#  pragma warning(disable: 4610) // can never be instantiated - user defined constructor required.
//#  pragma warning(disable: 4535) // calling _set_se_translator() requires /EHa (in Boost.test)
// Enable C++ Exceptions Yes With SEH Exceptions (/EHa) prevents warning 4535.
#endif

#include <boost/math/concepts/real_concept.hpp> // for real_concept
#include <boost/math/distributions/rayleigh.hpp>
	 using boost::math::rayleigh_distribution;

#include <boost/test/included/test_exec_monitor.hpp> // Boost.Test
#include <boost/test/floating_point_comparison.hpp>

#include <iostream>
	using std::cout;
	using std::endl;
	using std::setprecision;

template <class RealType>
void test_spot(RealType s, RealType x, RealType p, RealType q, RealType tolerance)
{
   BOOST_CHECK_CLOSE(
      ::boost::math::cdf(
         rayleigh_distribution<RealType>(s),
         x),
         p,
			tolerance); // %
   BOOST_CHECK_CLOSE(
      ::boost::math::cdf(
         complement(rayleigh_distribution<RealType>(s),
         x)),
         q,
			tolerance); // %
   // Special extra tests for p and q near to unity.
   if(p < 0.999)
   {
      BOOST_CHECK_CLOSE(
         ::boost::math::quantile(
            rayleigh_distribution<RealType>(s),
            p),
            x,
			   tolerance); // %
   }
   if(q < 0.999)
   {
      BOOST_CHECK_CLOSE(
         ::boost::math::quantile(
            complement(rayleigh_distribution<RealType>(s),
            q)),
            x,
			   tolerance); // %
   }
} // void test_spot

template <class RealType>
void test_spots(RealType T)
{
   using namespace std; // ADL of std names.
   // Basic sanity checks.
   // 50 eps as a percentage, up to a maximum of double precision
   // (that's the limit of our test data: obtained by punching
   // numbers into a calculator).
   RealType tolerance = (std::max)(
      static_cast<RealType>(boost::math::tools::epsilon<double>()),
      boost::math::tools::epsilon<RealType>());
   tolerance *= 10 * 100; // 10 eps as a percent
	cout << "Tolerance for type " << typeid(T).name()  << " is " << tolerance << " %" << endl;

  using namespace boost::math::constants;

   // Things that are errors:
   rayleigh_distribution<RealType> dist(0.5);

   BOOST_CHECK_THROW(
       quantile(dist,
       RealType(1.)), // quantile unity should overflow.
       std::overflow_error);
   BOOST_CHECK_THROW(
       quantile(complement(dist,
       RealType(0.))), // quantile complement zero should overflow.
       std::overflow_error);
   BOOST_CHECK_THROW(
       pdf(dist, RealType(-1)), // Bad negative x.
       std::domain_error);
   BOOST_CHECK_THROW(
       cdf(dist, RealType(-1)), // Bad negative x.
       std::domain_error);
   BOOST_CHECK_THROW(
       cdf(rayleigh_distribution<RealType>(-1), // bad sigma < 0
       RealType(1)),
       std::domain_error);
   BOOST_CHECK_THROW(
       cdf(rayleigh_distribution<RealType>(0), // bad sigma == 0
       RealType(1)),
       std::domain_error);
   BOOST_CHECK_THROW(
       quantile(dist, RealType(-1)), // negative quantile probability.
       std::domain_error);
   BOOST_CHECK_THROW(
       quantile(dist, RealType(2)), // > unity  quantile probability.
       std::domain_error);

   test_spot(
      static_cast<RealType>(1.L), // sigma
      static_cast<RealType>(1.L), // x
      static_cast<RealType>(1 - exp_minus_half<RealType>()), // p
      static_cast<RealType>(exp_minus_half<RealType>()), // q
      tolerance);

   test_spot(
      static_cast<RealType>(0.5L), // sigma
      static_cast<RealType>(0.5L), // x
      static_cast<RealType>(1 - exp_minus_half<RealType>()), // p
      static_cast<RealType>(exp_minus_half<RealType>()), //q
      tolerance);

   test_spot(
      static_cast<RealType>(3.L), // sigma
      static_cast<RealType>(3.L), // x
      static_cast<RealType>(1 - exp_minus_half<RealType>()), // p
      static_cast<RealType>(exp_minus_half<RealType>()), //q
      tolerance);

   BOOST_CHECK_CLOSE(
      ::boost::math::pdf(
         rayleigh_distribution<RealType>(1.L),
         static_cast<RealType>(1.L)),              // x
         static_cast<RealType>(exp_minus_half<RealType>()), // probability.
			tolerance); // %
   BOOST_CHECK_CLOSE(
      ::boost::math::pdf(
         rayleigh_distribution<RealType>(0.5L),
         static_cast<RealType>(0.5L)),              // x
         static_cast<RealType>(2 * exp_minus_half<RealType>()), // probability.
			tolerance); // %
   BOOST_CHECK_CLOSE(
      ::boost::math::pdf(
         rayleigh_distribution<RealType>(2.L),
         static_cast<RealType>(2.L)),              // x
         static_cast<RealType>(exp_minus_half<RealType>() /2),  // probability.
			tolerance); // %

   BOOST_CHECK_CLOSE(
      ::boost::math::mean(
         rayleigh_distribution<RealType>(1.L)),
         static_cast<RealType>(root_half_pi<RealType>()),
			tolerance); // %
   BOOST_CHECK_CLOSE(
      ::boost::math::variance(
         rayleigh_distribution<RealType>(root_two<RealType>())),
         static_cast<RealType>(four_minus_pi<RealType>()),
			tolerance * 100); // %

   BOOST_CHECK_CLOSE(
      ::boost::math::mode(
         rayleigh_distribution<RealType>(1.L)),
         static_cast<RealType>(1.L),
			tolerance); // %

   BOOST_CHECK_CLOSE(
      ::boost::math::median(
         rayleigh_distribution<RealType>(1.L)),
         static_cast<RealType>(sqrt(log(4.L))),  // sigma * sqrt(log_four)
			tolerance); // %

   BOOST_CHECK_CLOSE(
      ::boost::math::skewness(
         rayleigh_distribution<RealType>(1.L)),
         static_cast<RealType>(2.L * root_pi<RealType>()) * (pi<RealType>() - 3) / (pow((4 - pi<RealType>()), static_cast<RealType>(1.5L))),
			tolerance * 100); // %

   BOOST_CHECK_CLOSE(
      ::boost::math::skewness(
         rayleigh_distribution<RealType>(1.L)),
         static_cast<RealType>(0.63111065781893713819189935154422777984404221106391L),
			tolerance * 100); // %

   BOOST_CHECK_CLOSE(
      ::boost::math::kurtosis_excess(
         rayleigh_distribution<RealType>(1.L)),
         static_cast<RealType>(0.2450893006876380628486604106197544154170667057995L),
			tolerance * 1000); // %

   BOOST_CHECK_CLOSE(
      ::boost::math::kurtosis(
         rayleigh_distribution<RealType>(1.L)),
         static_cast<RealType>(3.2450893006876380628486604106197544154170667057995L),
			tolerance * 100); // %


   BOOST_CHECK_CLOSE(
      ::boost::math::kurtosis_excess(rayleigh_distribution<RealType>(2)),
      ::boost::math::kurtosis(rayleigh_distribution<RealType>(2)) -3,
			tolerance* 100); // %
   return;

} // template <class RealType>void test_spots(RealType)

int test_main(int, char* [])
{
  // Check that can generate rayleigh distribution using the two convenience methods:
	boost::math::rayleigh ray1(1.); // Using typedef
	rayleigh_distribution<> ray2(1.); // Using default RealType double.

  using namespace boost::math::constants;
	// Basic sanity-check spot values.

  // Double only tests.
   BOOST_CHECK_CLOSE_FRACTION(
      ::boost::math::pdf(
      rayleigh_distribution<double>(1.),
      static_cast<double>(1)), // x
      static_cast<double>(exp_minus_half<double>()), // p
			1e-15); // %

   BOOST_CHECK_CLOSE_FRACTION(
      ::boost::math::pdf(
      rayleigh_distribution<double>(0.5),
      static_cast<double>(0.5)), // x
      static_cast<double>(2 * exp_minus_half<double>()), // p
			1e-15); // %

   BOOST_CHECK_CLOSE_FRACTION(
      ::boost::math::pdf(
      rayleigh_distribution<double>(2.),
      static_cast<double>(2)), // x
      static_cast<double>(exp_minus_half<double>() /2 ), // p
			1e-15); // %

   BOOST_CHECK_CLOSE_FRACTION(
      ::boost::math::cdf(
      rayleigh_distribution<double>(1.),
      static_cast<double>(1)), // x
      static_cast<double>(1- exp_minus_half<double>()), // p
			1e-15); // %

   BOOST_CHECK_CLOSE_FRACTION(
      ::boost::math::cdf(
      rayleigh_distribution<double>(2.),
      static_cast<double>(2)), // x
      static_cast<double>(1- exp_minus_half<double>()), // p
			1e-15); // %

   BOOST_CHECK_CLOSE_FRACTION(
      ::boost::math::cdf(
      rayleigh_distribution<double>(3.),
      static_cast<double>(3)), // x
      static_cast<double>(1- exp_minus_half<double>()), // p
			1e-15); // %

   BOOST_CHECK_CLOSE_FRACTION(
      ::boost::math::cdf(
      rayleigh_distribution<double>(4.),
      static_cast<double>(4)), // x
      static_cast<double>(1- exp_minus_half<double>()), // p
			1e-15); // %

   BOOST_CHECK_CLOSE_FRACTION(
      ::boost::math::cdf(complement(
      rayleigh_distribution<double>(4.),
      static_cast<double>(4))), // x
      static_cast<double>(exp_minus_half<double>()), // q = 1 - p
			1e-15); // %

   BOOST_CHECK_CLOSE_FRACTION(
      ::boost::math::quantile(
      rayleigh_distribution<double>(4.),
      static_cast<double>(1- exp_minus_half<double>())), // x
      static_cast<double>(4), // p
			1e-15); // %

   BOOST_CHECK_CLOSE_FRACTION(
      ::boost::math::quantile(complement(
      rayleigh_distribution<double>(4.),
      static_cast<double>(exp_minus_half<double>()))), // x
      static_cast<double>(4), // p
			1e-15); // %

	// (Parameter value, arbitrarily zero, only communicates the floating point type).
  test_spots(0.0F); // Test float. OK at decdigits = 0 tolerance = 0.0001 %
  test_spots(0.0); // Test double. OK at decdigits 7, tolerance = 1e07 %
#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
  test_spots(0.0L); // Test long double.
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))
  test_spots(boost::math::concepts::real_concept(0.)); // Test real concept.
#endif
#else
   std::cout << "<note>The long double tests have been disabled on this platform "
      "either because the long double overloads of the usual math functions are "
      "not available at all, or because they are too inaccurate for these tests "
      "to pass.</note>" << std::cout;
#endif

   return 0;
} // int test_main(int, char* [])

/*

Output is:

------ Build started: Project: test_rayleigh_dist, Configuration: Debug Win32 ------
Compiling...
test_rayleigh.cpp
Linking...
Autorun "i:\boost-06-05-03-1300\libs\math\test\Math_test\debug\test_rayleigh.exe"
Running 1 test case...
Tolerance for type float is 5.96046e-006 %
Tolerance for type double is 1.11022e-014 %
Tolerance for type long double is 1.11022e-014 %
Tolerance for type class boost::math::concepts::real_concept is 1.11022e-014 %
*** No errors detected





*/

