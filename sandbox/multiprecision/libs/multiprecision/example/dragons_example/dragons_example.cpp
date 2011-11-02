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

#include <iostream>

int main()
{
  using std::cout;
  using std::endl;
  
  using boost::multiprecision::mp_float;
  using boost::multiprecision::one;
  using boost::multiprecision::pi;
  using boost::multiprecision::exp1;

  cout.precision(std::numeric_limits<mp_float>::max_digits10);
  // Show all potentially significant digits (default 58).

//[dragons_example_1

//`[h4 Pitfalls in Constructing [^mp_float] variables]

//`Construction of `mp_float` from all `int` types is always exact.
  mp_float i(12345); 
  cout << "mp_float i(12345); = " << i << endl; // mp_float i(12345); = 12345

//` Construction from `integer` literal string is always exact.
  mp_float is("12345"); // Construction from integer string is always exact.
  cout << "mp_float i(\"12345\"); = " << is << endl; // mp_float i("12345"); = 12345

//` Construction from `double` with integral value is always exact.
  mp_float id(12345.);
  cout << "mp_float i(12345.); = " << id << endl; //   mp_float i(12345.); = 12345

//` Construction from `float` with integral value is always exact.
  mp_float ifl(12345.F); // Construction from float with integral value is always exact.
  cout << "mp_float i(12345.F); = " << ifl << endl; //   mp_float i(12345.F); = 12345

/*` The examples above work because the value is integral, with zero fractional part,
  but if the fraction part is *not zero*, we are about to make a mistake.
*/
  mp_float v1234567890 = 1.23456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890;
  //       v1234567890 = 1.2345678901234566904321354741114191710948944091796875
  //                                      ^

/*`See the catastrophic loss of accuracy starting at the 17th decimal digit!
(`std::numeric_limits<double>::max_digits10` = 17 for the common 64-bit representation).

When the uncertainty of value is known to be more than the precision of the type
(typical when it is a measurement - few are known to 17 decimal digit accuracy)
there may be no loss of information : for a mathematical constant, every digit is meaningful. 
*/

/*`[h4 Pitfalls in Constructing [^mp_float] fractions].
Creating fractions from integer numerator in C++ is always dangerous
because the result is probably NOT integral!
This is a mistake that everyone writing C++ makes at least once.
The numerator should always be a floating-point type, built-in like `double`, or `mp_float`,
whatever the desired result type, also always a floating-point type.
*/
  const double seventh = 1/7; // seventh == Zero!

//`Using `mp_float` is no different, and the dangers are the same.  

  const mp_float z = 1/7; // zero!
  cout << "const mp_float r = 1/7; = " << z << endl;

//`The simplest way is to ensure that the numerator is of type `mp_float`.

  const mp_float r = mp_float(1)/7; //   const mp_float r = 1/7; = 0
  cout << "const mp_float r = mp_float(1)/7 = " << r << endl;
  // const mp_float r = mp_float(1)/7 = 0.1428571428571428571428571428571428571428571428571428571429

/*` 
Some believe there are advantages (stylistic and compile efficiency)
to being explicit for the denominator too, for example,
specifying the type `int32_t` with a `static_cast`, thus `static_cast<int32_t>`
*/
  const mp_float one_seventh = one() / static_cast<int32_t>(7);
  cout << "const mp_float one_twelfth = one() / static_cast<int32_t>(7) = " << one_seventh << endl;

/*`[h4 How to do it wrong!]

Sadly it is all too easy to do it wrong, as the examples before show.
If we create unity as a `double`, we will avoid the `int`/`int` pitfall,
but sow the seeds of falling into another pit.
*/
  const mp_float s = mp_float(1.0)/7; //  Unity as a `double`.
  cout << "const mp_float r = mp_float(1.0)/7 = " << s << endl;

/*`Works OK because integers can always be stored exactly as `double` (`float` and `long double`),

So if we want `pi/2`, here are some ways to get the wrong (or at least inaccurate) answer!
*/
  const mp_float not_half_pi1 = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679/2;
  cout << "not_half_pi1 = " << not_half_pi1 << endl;

  const mp_float not_half_pi2 = mp_float(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679)/2;
  cout << "not_half_pi2 = " << not_half_pi2 << endl;

//` and if you want worse, construct using a `float` by adding F

  const mp_float not_half_pi3 = mp_float(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679F)/2;
  cout << "not_half_pi3 = " << not_half_pi3 << endl;

 //` and perhaps a bit better, use a `long double` by adding L

  const mp_float not_half_pi4 = mp_float(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679L)/2;
  cout << "not_half_pi4 = " << not_half_pi4 << endl;

//` To get the correct result you need to construct from a [*decimal digit string] of sufficient length.

  const mp_float half_pi1 = mp_float("3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679")/2;
  cout  << "half_pi1 =     " << half_pi1 << endl;

//`  Or most simply, use a built-in constant.
  const mp_float half_pi2 = pi()/2;
  cout << "half_pi2 =     " << half_pi2 << endl;

/*`Of course, one could argue that the constant [^pi/2] should be provided to avoid a run-time computation.

and there are other pits awaiting. One might be tempted to get Euler's number ['e] by writing

  mp_float e(exp(1));

but discover that it doesn't compile because exp is not defined for integer arguments,
and so alter '1' to '1.' 
*/

  mp_float e(exp(1.)); 
  
 /*` getting 2.7182818284590450907955982984276488423347473144531
 
 which is close to the expected  .7182818284590452353602874713526624977572470937,
 but is only accurate to 17 decimal digits!

 [warning Be very careful to ensure that the right function is called by, for example,
 using [^static_cast<mp_float>(1)], and using an int 1, not double 1.0!]
 */
  mp_float eok(exp(static_cast<mp_float>(1))); 
  cout << "mp_float e(exp(static_cast<mp_float>(1)); " << eok << endl;
  // 2.7182818284590452353602874713526624977572470937

//`Of course, the real answer is to use the mp_float constant function thoughtfully provided.

  cout << "e = " << exp1() << endl;

//] [/dragons_example_1]    
  return 0;
} // int main()


/*
//[dragons_example_output
dragons_example.cpp(100): warning C4189: 'seventh' : local variable is initialized but not referenced
  Generating code
  Finished generating code
  dragons_example.vcxproj -> I:\boost-sandbox\multiprecision\libs\multiprecision\build\Release\dragons_example.exe
  mp_float i(12345); = 12345
  mp_float i("12345"); = 12345
  mp_float i(12345.); = 12345
  mp_float i(12345.F); = 12345
  const mp_float r = 1/7; = 0
  const mp_float r = mp_float(1)/7 = 0.1428571428571428571428571428571428571428571428571428571429
  const mp_float one_twelfth = one() / static_cast<int32_t>(7) = 0.1428571428571428571428571428571428571428571428571428571429
  const mp_float r = mp_float(1.0)/7 = 0.1428571428571428571428571428571428571428571428571428571429
  not_half_pi1 = 1.5707963267948965579989817342720925807952880859375
  not_half_pi2 = 1.5707963267948965579989817342720925807952880859375
  not_half_pi3 = 1.57079637050628662109375
  not_half_pi4 = 1.5707963267948965579989817342720925807952880859375
  half_pi1 =     1.570796326794896619231321691639751442098584699687552910487
  half_pi2 =     1.570796326794896619231321691639751442098584699687552910487
  mp_float e(exp(static_cast<mp_float>(1)); 2.718281828459045235360287471352662497757247093699959574967
   e = 2.718281828459045235360287471352662497757247093699959574967
  
//] [/dragons_example_output]

*/
