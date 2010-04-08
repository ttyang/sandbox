
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
    \brief Contains the definitions for functions related to roots of a number.
*/

#include "../boost/xint/xint.hpp"

namespace boost {
namespace xint {

namespace core {
integer sqrt(const integer& n) {
    if (n.sign() < 0) throw cannot_represent("library cannot represent "
        "imaginary values (tried to take sqrt of negative number)");
    if (n.sign() == 0) return integer::zero();

    // Initial guess is half the length of n, in bits
    integer guess;
    setbit(guess, log2(n)/2);

    // Now refine it until we're as close as integers can get
    while (1) {
        integer guess2=(guess + (n/guess)) >> 1;
        if (guess == guess2) break;
        guess=guess2;
    }

    return guess;
}
} // namespace core

/*! \brief Calculate the square root of \c an integer.

\param[in] n The value to operate on.

\returns The largest integer that, when squared, is less than or equal to \c n.
If \c n is not a perfect square, then this value will not be the exact square
root.

\exception xint::cannot_represent if \c n is negative.
*/
integer sqrt(const integer& n) {
    try {
        return integer(sqrt(core::integer(n)));
    } catch (std::exception&) {
        if (exceptions_allowed()) throw;
        return integer::nan();
    }
}

} // namespace xint
} // namespace boost
