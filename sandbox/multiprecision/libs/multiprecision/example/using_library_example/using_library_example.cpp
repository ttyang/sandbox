//! \file

// Copyright Paul A. Bristow 2011.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file is written to be included from a Quickbook .qbk document.
// It can be compiled by the C++ compiler, and run. Any output can
// also be added here as comment or included or pasted in elsewhere.
// Caution: this file contains Quickbook markup as well as code
// and comments: don't change any of the special comment markups!

// This file also includes Doxygen-style documentation about the function of the code.
// See http://www.doxygen.org for details.

// Below are snippets of code that can be included into a Quickbook program.

//[using_library_example_1

/*` 

[h5 Multiprecision example using a pre-built library.]

Select the mp_float back-end big-number type
by defining BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_TYPE_xxx, for example,
as a compiler defined preprocessor macro.

For example [^#define BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_TYPE_EFX;]
in MS Project Properties, Preprocessor, Preprocessor definitions
or select backend type EFX (which has the Boost licence) below
with the #define below.
*/

#define BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_TYPE_EFX

/*`
[note If you have other files that use mp_float, they will all need this #define,
so a single project-wide definition may be more convenient.]

[warning Ensure that MS language extensions are NOT disabled.]

Includes are needed to use multiprecision, mp_float.hpp for arithmetic and trig functions,
and mp_float_functions.hpp to be able to use various constants.
*/

#include <boost/multiprecision/mp_float.hpp> 
#include <boost/multiprecision/mp_float_functions.hpp> // for constants.

//] [using_library_example_1] // This ends the snippet.

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::dec;
using std::hex;
using std::boolalpha;
using std::showpoint;

#include <iomanip>
using std::setprecision;
using std::setw;
#include <string>
using std::string;

#include <cassert>
#include <limits>

// using namespace boost::multiprecision; // Not recommended.

//[using_library_example_2
int main()
{
  using boost::multiprecision::mp_float;

  cout << "BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_DIGITS10 = " << BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_DIGITS10 << endl;

  cout.precision(std::numeric_limits<mp_float>::max_digits10);
  cout << "std::numeric_limits<multiprecision>::max_digits10  = " << std::numeric_limits<mp_float>::max_digits10 << endl;
  cout << "std::numeric_limits<multiprecision>::digits10  = " << std::numeric_limits<mp_float>::digits10 << endl;


//] [using_library_example_2]

//[using_library_example_3
  mp_float float_ten(10);

  mp_float float_hundred = boost::multiprecision::hundred();

  mp_float googol;
  googol = pow(float_ten, float_hundred);
  cout << "googol = " << showpoint << googol << endl; //  = 1.000000000000000000000000000000000000000000000000000000000e+100

  mp_float googolplex;
  googolplex = pow(float_ten, googol);
  cout << "googolplex = " << showpoint << googolplex << endl; // inf!

  mp_float mp_float_max = boost::multiprecision::value_max();
  cout << "std::numeric_limits<mp_float>::max() = " << std::numeric_limits<mp_float>::max() << endl;


  //cout << "boost::multiprecision::value_max() = " << showpoint << mp_float_max << endl;
  //] [using_library_example_3]

//[using_library_example_4

  using boost::multiprecision::pi; // Convenient to permit just pi().

  mp_float my_pi;
  my_pi = pi();
  cout << "boost::multiprecision::pi(); = " << pi() << endl;
  cout << " 4/3 pi(); = " << 4 * pi()/3 << endl;

//] [using_library_example_4]

//[using_library_example_5

  //mp_float r = 41/47; // zero!
  // mp_float r = (41.)/47; //
  //mp_float r = 41./47; // 1.190969240806423525258295702651707417479877984460367184892
  mp_float r = static_cast<mp_float>(41)/47; //

  mp_float t = tan (r);

  cout << "tan (41/47) = " << t << endl;

  //1.190969240806423525258295702651707417479877984460367184892

  //1.190969240806423433854995358643916551662102246296735478573
  //1.1909692408064234338549953586439165516621022462967354785730460059437472

//] [using_library_example_5]

} // int main()

/*

//[library_eg_output

 using_library_example.cpp
  Generating code
  Finished generating code
  using_library_example.vcxproj -> I:\boost-sandbox\multiprecision\libs\multiprecision\build\Release\using_library_example.exe
  BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_DIGITS10 = 50
  std::numeric_limits<multiprecision>::max_digits10  = 58
  std::numeric_limits<multiprecision>::digits10  = 50
  googol = 1.000000000000000000000000000000000000000000000000000000000e+100
  googolplex = inf
  std::numeric_limits<mp_float>::max() = 1.000000000000000000000000000000000000000000000000000000000e+003063937869882635617
  boost::multiprecision::pi(); = 3.141592653589793238462643383279502884197169399375105820975
   4/3 pi(); = 4.188790204786390984616857844372670512262892532500141094633
  tan (41/47) = 1.190969240806423433854995358643916551662102246296735478573

//] [/library_eg_output]



*/

