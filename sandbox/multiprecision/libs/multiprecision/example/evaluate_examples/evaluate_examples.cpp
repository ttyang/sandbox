//! \file

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Copyright Paul A. Bristow 2011.

// This file is written to be included from a Quickbook .qbk document.
// It can be compiled by the C++ compiler, and run. Any output can
// also be added here as comment or included or pasted in elsewhere.
// Caution: this file contains Quickbook markup as well as code
// and comments: don't change any of the special comment markups!

// This file also includes Doxygen-style documentation about the function of the code.
// See http://www.doxygen.org for details.

// Below are snippets of code that can be included into a Quickbook program.

/*`
As always, we select the mp_float back-end big-number type
by defining BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_TYPE_xxx, for example,
as a compiler defined preprocessor macro.
*/
#define BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_TYPE_EFX

#include <boost/multiprecision/mp_float.hpp>
#include <boost/multiprecision/mp_float_functions.hpp>

// Source files.
#include <libs/multiprecision/src/backends/float/mp_float.cpp>
#include <libs/multiprecision/src/backends/float/mp_float_base.cpp>
#include <libs/multiprecision/src/backends/float/efx/mp_float_efx.cpp>

#include <libs/multiprecision/src/functions/constants/constants.cpp>
#include <libs/multiprecision/src/functions/elementary/elementary_complex.cpp>
#include <libs/multiprecision/src/functions/elementary/elementary_hyper_g.cpp>
#include <libs/multiprecision/src/functions/elementary/elementary_math.cpp>
#include <libs/multiprecision/src/functions/elementary/elementary_trans.cpp>
#include <libs/multiprecision/src/functions/elementary/elementary_trig.cpp>

#include <libs/multiprecision/src/functions/gamma/gamma.cpp>
#include <libs/multiprecision/src/functions/gamma/factorial.cpp>
#include <libs/multiprecision/src/functions/gamma/factorial2.cpp>

#include <libs/multiprecision/src/functions/integer/prime.cpp>
#include <libs/multiprecision/src/functions/integer/prime_factor.cpp>
#include <libs/multiprecision/src/functions/integer/bernoulli_b.cpp>
#include <libs/multiprecision/src/functions/zeta/zeta.cpp>

#include <libs/multiprecision/src/utility/util_digit_scale.cpp>
#include <libs/multiprecision/src/utility/util_timer.cpp>
#include <libs/multiprecision/src/utility/util_power_j_pow_x.cpp>

#include <libs/multiprecision/src/functions/tables/a000142.cpp>
#include <libs/multiprecision/src/functions/tables/a000367.cpp>
#include <libs/multiprecision/src/functions/tables/a002445.cpp>
#include <libs/multiprecision/src/functions/tables/a006882.cpp>
#include <libs/multiprecision/src/functions/tables/a007318.cpp>

#include <iostream>

int main()
{
  using std::cout;
  using std::endl;

  using boost::multiprecision::mp_float;
  using boost::multiprecision::one;
  using boost::multiprecision::pi;

//[evaluate_examples

/*`For these examples, we could set the stream precision to show all potentially significant digits.
`using std::numeric_limits<mp_float>::max_digits10`
but some of these digits are 'noisy' and not exact, so we could also chose to show only those
that are guaranteed correctly rounded, using `std::numeric_limits<mp_float>::digits10`.
The default is 50 if the macro `BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_DIGITS10` controlling
the precision not overridden.
*/
  cout.precision(std::numeric_limits<mp_float>::digits10);

/*`[h4 Examples of evaluating [^mp_float] variables]

Shows examples of evaluating constants and evaluating mathematical functions using mp_float.

[h5 Examples of large integers]

Construction of `mp_float` from all integer types is always exact
(unless they overflow `std::numeric_limits<mp_float>::digits10` digits).
*/
  mp_float i(12345);
  cout << "mp_float i(12345); = " << i << endl; // mp_float i(12345); = 12345

//` And much large integers can be stored (exactly).
  int32_t i32max = std::numeric_limits<int32_t>::max();  //
  cout << "i32max = " << i32max << endl; // i32max = 2147483647
//`But there are dangers for the unwary!
  mp_float i64p = i32max + i32max; // Danger - overflow int32_t so = -2!
  mp_float i64m (i32max * i32max); // Danger - overflow int32_t so = 1!

//` So ensure that you always construct or assign from an mp_float, for example:

  mp_float i64 = mp_float(i32max); //
  cout << "mp_float i32max = " << i64 << endl; // 2147483647
  i64 *= i32max;
  cout << "mp_float i32max * i32max = " << i64 << endl; // 4611686014132420609

  int64_t i64max = std::numeric_limits<int64_t>::max();
  cout << "i64max = " << i64max << endl; // 9223372036854775807

  mp_float i128 = i64max;
  cout << "mp_float i64max = " << i128 << endl; // 9223372036854775807
  i128 *= i64max;
  cout << "mp_float i64max * i64max = " << i128 << endl; // 85070591730234615847396907784232501249

//`And you can also construct `mp_float` from a decimal digit string.
  mp_float is1("12345678901234567890123456789012345678901234567890");
  cout << "is1 = " << is1 << endl; // 12345678901234567890123456789012345678901234567890

/*`But when the size is too big (> `numeric_limits<mp_float>::digits10`),
it ceases to be exact and is partly held in mp_float floating-point exponent.
*/

  mp_float isov("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
  cout << "is = " << isov << endl; // 1.234567890123456789012345678901234567890123456789012345679e+119

/*`So some large integers can be handled easily and exactly
  (if less efficiently than a true big integer package).
*/

/*`[h5 Examples of [^mp_float] constants]
Many of the usual suspects are available quickly and conveniently.
*/
  mp_float my_pi(pi());
  cout << " pi() = " << my_pi << endl; // 3.1415926535897932384626433832795028841971693993751


//`  Or most simply, use a built-in constant.
  const mp_float half_pi2 = pi()/2;
  cout << "half_pi2 =     " << half_pi2 << endl; // 1.5707963267948966192313216916397514420985846996876

//` Of course, one could argue that the constant `pi/2` should be provided to avoid a run-time computation.

/*`Other well known constants are available as functions.
[@http://en.wikipedia.org/wiki/E_constant Euler's number e]

To use `mp_float` constants is it often convenient to avoid tedious full specifications, for example:
*/

  using boost::multiprecision::exp1;
  using boost::multiprecision::sqrt2;
  using boost::multiprecision::sqrt3;
  using boost::multiprecision::sqrt_pi;
  using boost::multiprecision::gamma;
  using boost::multiprecision::riemann_zeta;


/*`[warning `mp_float e(exp(1.))` will [*only be accurate to double precision!]
But `exp(static_cast<mp_float>(1))` will give full accuracy.]

However, the right way is to use the `mp_float` function `exp1` to get `e`.

*/
  mp_float e(exp1());
  cout << "Euler's number e = " << e << endl;

  cout << "Euler-Mascheroni gamma = " << boost::multiprecision::euler_gamma() << endl;

  mp_float sqrt_3(sqrt(static_cast<mp_float>(3)));

  cout << "sqrt(3) = " << sqrt_3 << endl; // 1.7320508075688772935274463415058723669428052538104

//`But there is also a function sqrt3() provided for [radic]3

  cout << "sqrt3() = " << sqrt3() << endl; // 1.7320508075688772935274463415058723669428052538104

//`There are not just plain vanilla functions, for example the gamma function

  cout << "gamma(mp_float(1993)/733) = " << gamma(mp_float(1993)/733) << endl;
  // 1.5683282929651009293238041703928088537599945734689

/*`And the zeta [zeta] function, for example used to compute the
[@http://en.wikipedia.org/wiki/Riemann_zeta_function Riemann zeta function]
of the prime number 3, [zeta](3),
(also known as [@http://en.wikipedia.org/wiki/Ap%C3%A9ry Aperys] constant).
 */
  cout << "zeta(3) = " << riemann_zeta(mp_float(3)) << endl;
    //  1.2020569031595942853997381615114499907649862923405

//] [/evaluate_examples]
  return 0;
} // int main()


/*
//[evaluate_examples_output

 evaluate_examples.vcxproj -> I:\boost-sandbox\multiprecision\libs\multiprecision\build\Release\evaluate_examples.exe
  mp_float i(12345); = 12345
  i32max = 2147483647
  mp_float i32max = 2147483647
  mp_float i32max * i32max = 4611686014132420609
  i64max = 9223372036854775807
  mp_float i64max = 9223372036854775807
  mp_float i64max * i64max = 85070591730234615847396907784232501249
  is1 = 12345678901234567890123456789012345678901234567890
  is = 1.234567890123456789012345678901234567890123456789e+119
   pi() = 3.1415926535897932384626433832795028841971693993751
  half_pi2 =     1.5707963267948966192313216916397514420985846996876
  Euler number e = 2.7182818284590452353602874713526624977572470937
  Euler-Mascheroni gamma = 0.57721566490153286060651209008240243104215933593992
  sqrt(3) = 1.7320508075688772935274463415058723669428052538104
  sqrt3() = 1.7320508075688772935274463415058723669428052538104
  gamma(mp_float(1993)/733) = 1.5683282929651009293238041703928088537599945734689
  zeta(3) = 1.2020569031595942853997381615114499907649862923405

//] [/evaluate_examples_output]

*/
