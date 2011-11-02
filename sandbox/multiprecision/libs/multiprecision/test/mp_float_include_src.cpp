
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Copyright Paul A. Bristow 2011.

//#include <boost/multiprecision/mp_float_inc_src.hpp> // contains the source .cpp files below.

// #define BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_TYPE_EFX
// Assume defined by preprocessor setting?

#include <boost/multiprecision/mp_float.hpp>
#include <boost/multiprecision/mp_float_functions.hpp>

#include <libs/multiprecision/src/backends/float/mp_float.cpp>
#include <libs/multiprecision/src/backends/float/mp_float_base.cpp>
#include <libs/multiprecision/src/backends/float/efx/mp_float_efx.cpp>

#include <libs/multiprecision/src/functions/constants/constants.cpp>
#include <libs/multiprecision/src/functions/elementary/elementary_complex.cpp>
#include <libs/multiprecision/src/functions/elementary/elementary_hyper_g.cpp>
#include <libs/multiprecision/src/functions/elementary/elementary_math.cpp>
#include <libs/multiprecision/src/functions/elementary/elementary_trans.cpp>
#include <libs/multiprecision/src/functions/elementary/elementary_trig.cpp>
