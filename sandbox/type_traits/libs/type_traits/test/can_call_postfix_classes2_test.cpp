//  (C) Copyright 2009-2011 Frederic Bron.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include "check_integral_constant.hpp"

#include <boost/type_traits/can_call.hpp>
#include "can_call_postfix_classes.hpp"

TT_TEST_BEGIN(BOOST_TT_TRAIT_NAME)
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C036, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C036 const, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C036 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C036 const, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C036 volatile, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C036 volatile, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C036 const volatile, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C036 const volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C036 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C036 const &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C036 const volatile &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C036 const volatile &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C036 const volatile &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C037, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C037, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C037, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C037 const, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C037 const, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C037 volatile, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C037 volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C037 volatile, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C037 const volatile, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C037 const volatile, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C037 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C037 &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C037 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C037 const volatile &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C037 const volatile &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C038, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C038, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C038, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C038 const, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C038 const, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C038 volatile, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C038 volatile, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C038 const volatile, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C038 const volatile, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C038 const volatile, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C038 const volatile, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C038 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C038 &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C038 const &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C038 const &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C038 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C038 volatile &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C038 volatile &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C038 volatile &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C038 const volatile &, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C039, ret volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C039, ret const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C039, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C039, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C039 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C039 const, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C039 volatile, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C039 volatile, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C039 volatile, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C039 volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C039 const volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C039 const volatile, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C039 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C039 &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C039 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C039 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C039 const &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C039 volatile &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C039 volatile &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C039 const volatile &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C040, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C040 volatile, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C040 volatile, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C040 volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C040 const volatile, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C040 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C040 volatile &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C040 volatile &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C040 volatile &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C041, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C041 const, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C041 const, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C041 &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C041 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C041 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C041 volatile &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C041 volatile &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C041 volatile &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C041 const volatile &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C041 const volatile &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C042, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C042, ret const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C042 const, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C042 volatile, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C042 volatile, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C042 volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C042 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C042 &, ret const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C042 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C042 &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C042 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C042 const &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C042 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C042 const &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C042 volatile &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C042 const volatile &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C043 volatile, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C043 const volatile, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C043 const volatile, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C043 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C043 const &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C043 const &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C043 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C043 const &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C043 const &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C043 const &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C043 volatile &, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C043 const volatile &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C043 const volatile &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C044, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C044, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C044 volatile, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C044 volatile, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C044 volatile, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C044 const volatile, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C044 const volatile, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C044 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C044 volatile &, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C044 const volatile &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C044 const volatile &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C045, void >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C045, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C045, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C045 const, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C045 const, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C045 volatile, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C045 const volatile, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C045 const volatile, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C045 &, void >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C045 &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C045 const &, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C045 volatile &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C045 const volatile &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C046, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C046, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C046 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C046 volatile, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C046 volatile, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C046 const volatile, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C046 const volatile, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C046 const volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C046 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C046 &, ret volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C046 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C046 const &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C046 const &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C046 volatile &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C046 const volatile &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C047, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C047 const, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C047 const, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C047 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C047 const, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C047 volatile, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C047 const volatile, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C047 &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C047 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C047 const &, ret volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C047 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C047 const volatile &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C048, ret volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C048, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C048, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C048 volatile, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C048 const volatile, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C048 const volatile, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C048 const volatile, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C048 const volatile, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C048 &, ret volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C048 &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C048 const &, ret volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C048 volatile &, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C048 const volatile &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C049, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C049 const, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C049 const, ret volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C049 const, ret const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C049 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C049 const, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C049 const, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C049 volatile, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C049 const volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C049 &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C049 const &, ret volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C049 const &, ret const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C049 const volatile &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C049 const volatile &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C050, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C050, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C050 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C050 const, ret volatile & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C050 volatile, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C050 const volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C050 &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C050 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C050 &, ret volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C050 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C050 const &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C050 const &, ret & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C050 const &, ret volatile & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C050 const volatile &, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C050 const volatile &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C051, ret const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C051, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C051 volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C051 const volatile, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C051 const volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C051 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C051 &, ret volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C051 &, ret const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C051 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C051 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C051 const volatile &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C052, ret volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C052, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C052 volatile, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C052 volatile, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C052 volatile, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C052 &, ret volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C052 &, ret volatile & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C052 const &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C052 volatile &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C052 volatile &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C052 volatile &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C052 volatile &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C052 const volatile &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C052 const volatile &, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C052 const volatile &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C053, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C053, ret const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C053, ret const volatile & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C053 volatile, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C053 volatile, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C053 const volatile, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C053 const volatile, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C053 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C053 &, ret const volatile & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C053 const &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C053 const &, ret volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C053 const &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C053 volatile &, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_post_increment< C053 const volatile &, ret volatile & >::value), 0);
TT_TEST_END