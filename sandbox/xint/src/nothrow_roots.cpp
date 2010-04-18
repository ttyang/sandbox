
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
    \brief Contains the definitions for \c nothrow_integer functions related to
           roots of a number.
*/

#include "../boost/xint/xint.hpp"

namespace boost {
namespace xint {

//! \copydoc xint::sqrt(const integer&)
nothrow_integer sqrt(const nothrow_integer& n) {
    try {
        return nothrow_integer(sqrt(xint::integer(n)));
    } catch (std::exception&) {
        return nothrow_integer::nan();
    }
}

} // namespace xint
} // namespace boost
