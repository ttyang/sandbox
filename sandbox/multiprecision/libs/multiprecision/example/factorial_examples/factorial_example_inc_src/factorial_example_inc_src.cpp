
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Copyright Ronald Garcia 2002.
// Copyright Paul A. Bristow 2011.

#include <iostream>

#define BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_TYPE_EFX

#include <boost/multiprecision/mp_float.hpp>
#include <boost/multiprecision/mp_float_functions.hpp>

//#include <boost/multiprecision/mp_float_inc_src.hpp> // contains the source .cpp files below.

#include <libs/multiprecision/src/backends/float/mp_float.cpp>
#include <libs/multiprecision/src/backends/float/mp_float_base.cpp>
#include <libs/multiprecision/src/backends/float/efx/mp_float_efx.cpp>

#include <libs/multiprecision/src/functions/constants/constants.cpp>
#include <libs/multiprecision/src/functions/elementary/elementary_complex.cpp>
#include <libs/multiprecision/src/functions/elementary/elementary_hyper_g.cpp>
#include <libs/multiprecision/src/functions/elementary/elementary_math.cpp>
#include <libs/multiprecision/src/functions/elementary/elementary_trans.cpp>
#include <libs/multiprecision/src/functions/elementary/elementary_trig.cpp>

int main()
{
  using std::cout;
  using std::endl;
  
  using boost::multiprecision::mp_float;

  cout.precision(std::numeric_limits<mp_float>::max_digits10);
  // Show all potentially significant digits (default 50).

  // 42 factorial = 42!
  mp_float value;
  value = 1;
  for(int i = 1; i <= 42; ++i)
  {
    value *= i;
    cout << i << "! = " << value << endl;
  }

  return 0;
} // int main()


/*

Output:

factorial_example_inc_src.vcxproj -> I:\boost-sandbox\multiprecision\libs\multiprecision\build\Release\factorial_example_inc_src.exe
  1! = 1
  2! = 2
  3! = 6
  4! = 24
  5! = 120
  6! = 720
  7! = 5040
  8! = 40320
  9! = 362880
  10! = 3628800
  11! = 39916800
  12! = 479001600
  13! = 6227020800
  14! = 87178291200
  15! = 1307674368000
  16! = 20922789888000
  17! = 355687428096000
  18! = 6402373705728000
  19! = 121645100408832000
  20! = 2432902008176640000
  21! = 51090942171709440000
  22! = 1124000727777607680000
  23! = 25852016738884976640000
  24! = 620448401733239439360000
  25! = 15511210043330985984000000
  26! = 403291461126605635584000000
  27! = 10888869450418352160768000000
  28! = 304888344611713860501504000000
  29! = 8841761993739701954543616000000
  30! = 265252859812191058636308480000000
  31! = 8222838654177922817725562880000000
  32! = 263130836933693530167218012160000000
  33! = 8683317618811886495518194401280000000
  34! = 295232799039604140847618609643520000000
  35! = 10333147966386144929666651337523200000000
  36! = 371993326789901217467999448150835200000000
  37! = 13763753091226345046315979581580902400000000
  38! = 523022617466601111760007224100074291200000000
  39! = 20397882081197443358640281739902897356800000000
  40! = 815915283247897734345611269596115894272000000000
  41! = 33452526613163807108170062053440751665152000000000
  42! = 1.405006117752879898543142606244511569936384e+051
*/
