//  (C) Copyright 2009-2011 Frederic Bron.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include "check_integral_constant.hpp"

#ifdef TEST_STD
#  include <type_traits>
#else
#  include <boost/type_traits/can_call_division.hpp>
#endif

#define BOOST_TT_TRAIT_NAME can_call_division
#define BOOST_TT_TRAIT_OP /


#include "can_call_binary_operators.hpp"

void specific() {
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void, bool const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void, void* const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool, bool const volatile, int const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool, double, int & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool, double volatile &, int const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool, void* volatile, bool const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool, void* const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool, int* const, int volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool, int* const volatile &, int volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const, bool const, bool volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const, void*, int const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const, void*, int volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const, void* const &, int const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const, int* const, bool const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const, int* const volatile, int & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool volatile, bool const &, bool const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool volatile, int volatile & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool volatile, double, int volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool volatile, double &, int >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool volatile, double const &, int const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool volatile, double const volatile &, int volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool volatile, int* &, bool const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool volatile, int* const &, bool volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const volatile, bool const volatile &, int const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const volatile, int const volatile, bool const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const volatile, double, int const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const volatile, double volatile, bool const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const volatile, void* &, int >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool &, bool const, int const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool &, double &, bool volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool &, double volatile &, bool const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool &, int* const volatile, int const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const &, bool const volatile, bool const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const &, bool const &, bool const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const &, int, int const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const &, int const volatile & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const &, void* volatile, bool volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool volatile &, void* const volatile, bool >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool volatile &, void* const &, bool volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool volatile &, int* const, bool const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const volatile &, bool, bool >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const volatile &, bool &, int volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const volatile &, double const, bool const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const volatile &, void* const volatile, int const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const volatile &, int*, int >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< bool const volatile &, int* volatile &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int, bool const, int volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int, int const volatile, int & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int, int &, int const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int, int*, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int, int* const, bool volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int, int* &, bool volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int, int* const &, bool const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int, int* const volatile &, bool volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int, int* const volatile &, int const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const, bool, int volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const, bool volatile &, int >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const, void* &, bool const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const, int* const &, int const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int volatile, bool const &, bool volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int volatile, bool const volatile &, int const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int volatile, int const volatile &, int const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int volatile, double, bool volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int volatile, void* const volatile, int const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const volatile, int const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const volatile, int const &, int const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const volatile, int volatile &, bool >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const volatile, int const volatile &, int const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const volatile, double &, int const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const volatile, void* const volatile, bool const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const volatile, void* &, bool >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int &, bool volatile &, int & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int &, bool const volatile & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int &, double &, bool >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int &, int*, int const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const &, double volatile &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const &, double const volatile &, bool const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const &, void*, int const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const &, int* volatile &, int const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int volatile &, bool, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int volatile &, bool &, int const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int volatile &, int &, int const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int volatile &, double, int const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int volatile &, double volatile, bool const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int volatile &, void*, bool const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int volatile &, int* const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const volatile &, bool const volatile, bool >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const volatile &, int volatile &, bool const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const volatile &, double &, bool const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const volatile &, double const &, bool & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const volatile &, void* const volatile, bool >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const volatile &, int* const volatile, bool & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int const volatile &, int* const volatile &, bool volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double, int &, bool const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double, int const &, int volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double, double, bool const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double, double volatile, bool >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double, void* const volatile, bool const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double, void* &, int const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double, void* &, int const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double, int* volatile, int >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double, int* const volatile, bool volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double, int* const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double, int* volatile &, bool >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double, int* volatile &, int volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double const, bool const volatile &, bool >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double const, double &, int & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double const, double volatile &, bool >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double volatile, bool const volatile, bool const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double volatile, void*, int volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double volatile, void* const volatile, int const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double volatile, void* const volatile &, bool const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double volatile, int*, bool const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double volatile, int* const, bool volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double volatile, int* volatile, bool const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double volatile, int* &, int volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double const volatile, double volatile, bool const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double const volatile, double const volatile, int volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double const volatile, double volatile &, int const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double const volatile, void* volatile &, bool >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double const volatile, int* volatile &, bool & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double &, int const volatile, bool >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double &, double const volatile, int const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double &, double &, int const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double &, void* const &, bool & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double &, int* const, bool const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double &, int* volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double &, int* const &, bool volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double const &, double const volatile, bool volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double const &, void* &, bool const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double volatile &, int &, bool & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double volatile &, double volatile, int volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double volatile &, int* const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double volatile &, int* const &, bool const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double const volatile &, bool, bool & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double const volatile &, bool const, bool & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double const volatile &, bool const &, bool const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< double const volatile &, bool volatile &, bool const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void*, bool const, int volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void*, bool volatile &, int const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void*, int const, int const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void*, double >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void*, double const volatile, bool const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void*, double volatile &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const, bool const volatile, int const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const, bool &, int volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const, int volatile, bool volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const, int volatile, int const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const, int const volatile, bool volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const, int const volatile, int const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const, int const volatile &, bool const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const, double const volatile &, bool const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const, void* const volatile &, bool const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* volatile, int volatile, bool volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* volatile, void* const volatile, int const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* volatile, int*, int >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const volatile, double volatile &, bool const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const volatile, void*, int const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const volatile, void* &, bool >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const volatile, int*, bool & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const volatile, int* const volatile, bool volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* &, bool const &, int const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* &, int, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* &, int* volatile, int const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* &, int* const volatile &, int const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const &, bool const &, int volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const &, int const, int const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const &, int volatile, bool const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const &, double volatile, bool const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const &, double volatile, bool const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const &, double const volatile, int const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const &, double const volatile &, int volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const &, void* const volatile &, bool const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const &, void* const volatile &, int volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* volatile &, bool volatile &, bool volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* volatile &, double &, int volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* volatile &, void* const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* volatile &, void* const &, bool & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const volatile &, bool, bool const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const volatile &, bool, bool volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const volatile &, bool volatile, bool const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const volatile &, bool volatile, bool const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const volatile &, bool const &, bool const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const volatile &, int const volatile &, int const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const volatile &, double const volatile &, int volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const volatile &, void* const volatile, bool const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const volatile &, void* const &, bool volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const volatile &, int* volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const volatile &, int* volatile, bool >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const volatile &, int* const &, int >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< void* const volatile &, int* volatile &, int const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int*, bool, bool const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int*, bool const &, int & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int*, bool const volatile &, int >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int*, int volatile &, bool volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int*, double const volatile &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int*, double const volatile &, bool const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const, bool, int const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const, bool const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const, double &, bool volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const, double volatile &, int const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const, int* const, bool const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* volatile, bool const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* volatile, void* &, bool const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* volatile, void* const volatile &, int const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const volatile, bool, bool >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const volatile, bool const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const volatile, int const, bool const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const volatile, int const, int const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const volatile, double const volatile, bool const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const volatile, double &, bool volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const volatile, void* volatile, int volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const volatile, void* const &, int const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const volatile, int*, int volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const volatile, int* const volatile &, int const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* &, int, int const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* &, int volatile, bool volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* &, int const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* &, void* const, bool volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* &, void* volatile, int const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* &, void* volatile &, int & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* &, void* const volatile &, int >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const &, bool const &, bool & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const &, bool volatile &, bool const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const &, bool volatile &, bool & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const &, int, int volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const &, int const &, int const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const &, double volatile, bool volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const &, double &, int volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const &, double volatile &, int & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const &, void*, bool const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const &, void* volatile, bool const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const &, void* const volatile, bool >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const &, int*, bool const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const &, int*, bool const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const &, int* const volatile &, bool volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* volatile &, bool &, int volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* volatile &, int const volatile, bool volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* volatile &, double const volatile, int const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* volatile &, void*, bool const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* volatile &, void*, bool volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* volatile &, void* const volatile, bool const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* volatile &, void* &, int const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* volatile &, void* const volatile &, bool const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* volatile &, int* volatile &, int const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* volatile &, int* const volatile &, int const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const volatile &, bool, int const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const volatile &, int const volatile, int const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const volatile &, int const &, int volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::BOOST_TT_TRAIT_NAME< int* const volatile &, double const volatile &, int const volatile & >::value), 0);

}

TT_TEST_BEGIN(BOOST_TT_TRAIT_NAME)
   common();
   specific();
TT_TEST_END
