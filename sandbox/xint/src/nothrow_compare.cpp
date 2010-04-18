
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
    \brief Contains the the compare function and comparison operators for the \c
           nothrow_integer type.
*/

#include "../boost/xint/xint.hpp"

namespace boost {
namespace xint {

/*! \copydoc xint::compare(const integer&, const integer&, bool)

\note Returns 0 instead of throwing.
*/
int compare(const nothrow_integer &b1, const nothrow_integer &b2, bool ignoresign) {
    try {
        return compare(xint::integer(b1), xint::integer(b2));
    } catch (std::exception&) {
        return 0;
    }
}

namespace {
template <typename T>
bool cmp(const nothrow_integer &num1, const nothrow_integer &num2, const T& t) {
    try {
        return t(compare(xint::integer(num1), xint::integer(num2)), 0);
    } catch (std::exception&) {
        return false;
    }
}
} // namespace

bool operator!(const nothrow_integer &num1) {
    try {
        return operator!(xint::integer(num1));
    } catch (std::exception&) {
        return false;
    }
}

bool operator==(const nothrow_integer &num1, const nothrow_integer &num2) {
    return cmp(num1, num2, std::equal_to<int>()); }
bool operator!=(const nothrow_integer& num1, const nothrow_integer& num2) {
    return cmp(num1, num2, std::not_equal_to<int>()); }
bool operator<(const nothrow_integer& num1, const nothrow_integer& num2) {
    return cmp(num1, num2, std::less<int>()); }
bool operator>(const nothrow_integer& num1, const nothrow_integer& num2) {
    return cmp(num1, num2, std::greater<int>()); }
bool operator<=(const nothrow_integer& num1, const nothrow_integer& num2) {
    return cmp(num1, num2, std::less_equal<int>()); }
bool operator>=(const nothrow_integer& num1, const nothrow_integer& num2) {
    return cmp(num1, num2, std::greater_equal<int>()); }

} // namespace xint
} // namespace boost
