
//! \file

// Copyright Paul A. Bristow 2011.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Some really simple examples of using mp_float.

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
#include <limits> // for std::numeric_limits

#include <boost/multiprecision/mp_float.hpp>

#include <boost/multiprecision/mp_float_functions.hpp> // for constants.

// Select the mp_float back-end big-number type
// by defining BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_TYPE_xxx, for example,
// as a compiler defined preprocessor macro.

// For example #define BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_TYPE_EFX; in project properties.
// Ensure that MS language extensions are NOT disabled.

// Need to include .cpp files:
// constants.cpp

int main()
{

  using boost::multiprecision::mp_float;

  // Display all the std::numeric_limits values.

  cout << boolalpha << endl;
  cout << "std::numeric_limits<mp_float>::max_digits10 is " << std::numeric_limits<mp_float>::max_digits10 << endl;
  cout << "std::numeric_limits<mp_float>::digits10 is " << std::numeric_limits<mp_float>::digits10 << endl;
  cout << "std::numeric_limits<mp_float>::digits is " << std::numeric_limits<mp_float>::digits << endl;
  cout << "std::numeric_limits<mp_float>::radix is " << std::numeric_limits<mp_float>::radix << endl;
  cout << "std::numeric_limits<mp_float>::epsilon() is " << std::numeric_limits<mp_float>::epsilon() << endl;

  cout << "std::numeric_limits<mp_float>::has_infinity is " << std::numeric_limits<mp_float>::has_infinity << endl;
  cout << "std::numeric_limits<mp_float>::infinity() is " << std::numeric_limits<mp_float>::infinity() << endl;
  cout << "std::numeric_limits<mp_float>::has_quiet_NaN is " << std::numeric_limits<mp_float>::has_quiet_NaN << endl;
  cout << "std::numeric_limits<mp_float>::quiet_NaN() is " << std::numeric_limits<mp_float>::quiet_NaN() << endl;


  cout << "std::numeric_limits<mp_float>::round_error() is " << std::numeric_limits<mp_float>::round_error() << endl;
  cout << "std::numeric_limits<mp_float>::max() is " << std::numeric_limits<mp_float>::max() << endl;
  cout << "std::numeric_limits<mp_float>::min() is " << std::numeric_limits<mp_float>::min() << endl;
  cout << "std::numeric_limits<mp_float>::max_exponent is " << std::numeric_limits<mp_float>::max_exponent << endl;
  cout << "std::numeric_limits<mp_float>::min_exponent is " << std::numeric_limits<mp_float>::min_exponent << endl;

  cout << "std::numeric_limits<mp_float>::max_exponent10 is " << std::numeric_limits<mp_float>::max_exponent10 << endl;
  cout << "std::numeric_limits<mp_float>::min_exponent10 is " << std::numeric_limits<mp_float>::min_exponent10 << endl;

  mp_float my_float;
  cout << "mp_float default my_float; = " << my_float << endl;  // Default construction is zero.

  my_float = 1.23456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890;
  //  my_float = 1.2345678901234566904321354741114191710948944091796875
  //                               ^
  // BUT see the catastrophic loss of accuracy starting at the 17th decimal digit!
  // (std::numeric_limits<double>>::max_digits10 = 17)

  // Change to maximum precision to show all significant digits and then show again.
  cout.precision(std::numeric_limits<mp_float>::max_digits10);
  cout << "cout.precision(std::numeric_limits<mp_float>::max_digits10); is " <<  cout.precision() << endl;
  cout << "my_float = " << my_float << endl;  //

  // Construct from string with far more digits than max_digits10.
  mp_float d("1.23456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");

  cout << "mp_float d constructed from string " << d << endl;  // 1.234567890123456789012345678901234567890123456789012345679
  // No loss of accuracy until the 57th digit.

  my_float = 2.0; // IS allowed - implicit conversion from double (by only the accuracy of double).
  // And the accuracy will not necessarily be the same on all platforms and implementations!

  my_float = 2;  // IS allowed - implicit conversion from int.

  mp_float my_float_double = mp_float(2.); // Construct from double.
  mp_float my_float_int = mp_float(2); // Construct from int.

  { // Show a few display features.
    cout.precision(6);   // Reset to default precision = 6.
    cout << "my_float from long string = " << d << endl;  // my_float from long string = 1.23457
    // Default precision = 6, so doesn't show much of the potential accuracy!

    // Return to showing all possibly significant digits.
    cout.precision(std::numeric_limits<mp_float>::max_digits10);

    // Force display of trailing zero decimal digits with showpoint manipulator.
    mp_float my_float_int(mp_float(2));
    cout << my_float_int << endl; // Just "2", no decimal point and no trailing zeros.
    cout << "mp_float my_float_int(mp_float(2)); = " << showpoint << my_float << endl;
    //  2.000000000000000000000000000000000000000000000000000000000

    my_float  *= 2;
    cout <<"my_float *= 2; = " << showpoint << my_float << endl;

    BOOST_ASSERT(my_float == 4.);

  } // Display features.

  { // multiprecision Constants.

    using boost::multiprecision::half;

    cout << "half = "  << half << endl; // 01369B60 - address not value!
    cout << "half() = "  << half() << endl; // 

    cout << boost::multiprecision::mp_float_efx::mp_radix << endl; // 10
    cout << boost::multiprecision::mp_float_efx::mp_elem_digits10 << endl; // 8
    cout << boost::multiprecision::mp_float_efx::mp_float_digits10_extra << endl; // 8
    cout << boost::multiprecision::mp_float_efx::mp_float_max_digits10 << endl; // 8

    using boost::multiprecision::two;

    cout << "two = " << two << endl; // NO! - it's a function call that you want - this returns the address!

    cout << "boost::multiprecision::two() = " << two() << endl;

    cout << "boost::multiprecision::golden_ratio()  "<< boost::multiprecision::golden_ratio() << endl;

    mp_float my_pi;

    my_pi = boost::multiprecision::pi();

    cout << "boost::multiprecision::pi() " << my_pi << endl;
  }


} // int main()

/*

Output is

 simple_example_1.vcxproj -> I:\boost-sandbox\multiprecision\libs\multiprecision\build\Release\simple_example_1.exe
  
  std::numeric_limits<mp_float>::max_digits10 is 58
  std::numeric_limits<mp_float>::digits10 is 50
  std::numeric_limits<mp_float>::digits is 50
  std::numeric_limits<mp_float>::radix is 10
  std::numeric_limits<mp_float>::epsilon() is 1e-049
  std::numeric_limits<mp_float>::has_infinity is true
  std::numeric_limits<mp_float>::infinity() is inf
  std::numeric_limits<mp_float>::has_quiet_NaN is true
  std::numeric_limits<mp_float>::quiet_NaN() is nan
  std::numeric_limits<mp_float>::round_error() is 0.5
  std::numeric_limits<mp_float>::max() is 1e+003063937869882635617
  std::numeric_limits<mp_float>::min() is 1e-003063937869882635616
  std::numeric_limits<mp_float>::max_exponent is 9223372036854775795
  std::numeric_limits<mp_float>::min_exponent is -9223372036854775795
  std::numeric_limits<mp_float>::max_exponent10 is 3063937869882635616
  std::numeric_limits<mp_float>::min_exponent10 is -3063937869882635616
  mp_float default my_float; = 0
  cout.precision(std::numeric_limits<mp_float>::max_digits10); is 58
  my_float = 1.2345678901234566904321354741114191710948944091796875
  mp_float d constructed from string 1.234567890123456789012345678901234567890123456789012345679
  my_float from long string = 1.23457
  2
  mp_float my_float_int(mp_float(2)); = 2.000000000000000000000000000000000000000000000000000000000
  my_float *= 2; = 4.000000000000000000000000000000000000000000000000000000000
  half = 00D3A070
  half() = 0.5000000000000000000000000000000000000000000000000000000000
  10
  8
  8
  58
  two = 00D3BA60
  boost::multiprecision::two() = 2.000000000000000000000000000000000000000000000000000000000
  boost::multiprecision::golden_ratio()  1.618033988749894848204586834365638117720309179805762862135
  boost::multiprecision::pi() 3.141592653589793238462643383279502884197169399375105820975

  */