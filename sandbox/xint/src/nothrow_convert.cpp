
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
    \brief Contains the conversion functions for the \c nothrow_integer type.

    Note that the xint::to<T> function is not here, because it's a template
    function and must be defined in a header file.
*/

#include "../boost/xint/xint.hpp"

namespace boost {
namespace xint {

using namespace detail;

/*! \copydoc xint::to_string(const integer&, size_t, bool)

\note Returns an empty std::string instead of throwing.

\par
If \c n is Not-a-Number, returns the string \c \#NaN#.
*/
std::string to_string(const nothrow_integer& n, size_t base, bool uppercase) {
    try {
        return to_string(xint::integer(n), base, uppercase);
    } catch (std::exception&) {
        return std::string();
    }
}

/*! \copydoc xint::from_string

\note If the string is \c \#NaN#, then it will return \ref nan "Not-a-Number".
*/
nothrow_integer nothrow_from_string(const std::string& str, size_t base) {
    try {
        if (str==detail::nan_text) return nothrow_integer::nan();
        return nothrow_integer(xint::from_string(str, base));
    } catch (std::exception&) {
        return nothrow_integer::nan();
    }
}

//! \copydoc xint::from_binary
nothrow_integer nothrow_from_binary(const std::string& str) {
    try {
        return nothrow_integer(xint::from_binary(str));
    } catch (std::exception&) {
        return nothrow_integer::nan();
    }
}

/*! \copydoc xint::to_binary(const integer&)

\par Returns an empty std::string instead of throwing.
*/
std::string to_binary(const nothrow_integer& n) {
    try {
        return to_binary(xint::integer(n));
    } catch (std::exception&) {
        return std::string();
    }
}

} // namespace xint
} // namespace boost
