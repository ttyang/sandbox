
/*
    The Extended Integer (XInt) Library
    A fast, portable C++ library for multi-precision integer math
    Copyright 2010 by Chad Nelson

    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt

    See http://www.boost.org/libs/xint for library home page.
*/

/*! \file
    \brief Contains tests for the nothrow_integer type.
*/

#include <boost/xint/nothrow_integer.hpp>

#ifndef BOOST_XINT_SINGLE_TEST_PROGRAM
    #define BOOST_TEST_MAIN
#endif
#include <boost/test/unit_test.hpp>

namespace boost {
namespace xint {

BOOST_AUTO_TEST_CASE(test_nothrow_init) {
    nothrow_integer n1(5), n2(n1);
    BOOST_CHECK_EQUAL(n1, 5);
    BOOST_CHECK_EQUAL(n2, 5);

    // Test the any_integer constructor from a different type of
    // nothrow_integer's Not-a-Number value.
    nothrow_integer n3(nothrow_integer_t<std::allocator<detail::digit_t>, false,
        true>::nan());
    BOOST_CHECK(n3.is_nan());
}

BOOST_AUTO_TEST_CASE(test_copy_nan) {
    nothrow_integer n(nothrow_integer::nan());
    BOOST_CHECK(n.is_nan());
    nothrow_integer n2(n);
    BOOST_CHECK(n2.is_nan());
    n2 = n;
    BOOST_CHECK(n2.is_nan());
}

BOOST_AUTO_TEST_CASE(test_misc_fns_called_with_nan) {
    nothrow_integer n(nothrow_integer::nan());
    BOOST_CHECK_EQUAL(n.is_odd(), false);
    BOOST_CHECK_EQUAL(n.is_even(), false);
    BOOST_CHECK_EQUAL(n.hex_digits(), 0);
    BOOST_CHECK_EQUAL(n.sign(), 0);
    BOOST_CHECK_EQUAL(lowestbit(n, 12), 12); // 12 is just an arbitrary number
    BOOST_CHECK_EQUAL(highestbit(n, 12), 12);
    BOOST_CHECK_EQUAL(compare(n, 12), 2);
    BOOST_CHECK_EQUAL(compare(12, n), 2);
}

} // namespace xint
} // namespace boost
