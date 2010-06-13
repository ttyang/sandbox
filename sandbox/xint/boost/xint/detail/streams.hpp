
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
    \brief Contains the stream input/output code for raw_integer types.

    This file will be included by the library itself when needed.
*/

#ifndef BOOST_INCLUDED_XINT_RAW_STREAMS_HPP
#define BOOST_INCLUDED_XINT_RAW_STREAMS_HPP

namespace boost {
namespace xint {
namespace detail {
//! @cond detail

template <typename charT, typename traits, bitsize_t Bits, bool Secure, class \
    Alloc>
inline std::basic_ostream<charT,traits>& operator<<(std::basic_ostream<charT,
    traits>& out, const BOOST_XINT_RAWINT n)
{
    int base=((out.flags() & std::ios::hex) ? 16
        : (out.flags() & std::ios::oct) ? 8
        : 10);
    bool upperCase=(out.flags() & std::ios::uppercase ? true : false);

    int nsign = (n.is_zero() ? 0 : n.negative ? -1 : 1);
    if ((out.flags() & std::ios::showpos) && nsign >= 0) out << "+";

    if (out.flags() & std::ios::showbase) {
        if (nsign < 0) out << "-";

        if (base == 16 && upperCase) out << "0X";
        else if (base == 16) out << "0x";
        else if (base == 8) out << "0";

        out << to_string<charT>(n.abs(), base, upperCase);
    } else {
        out << to_string<charT>(n, base, upperCase);
    }
    return out;
}

template <typename charT, typename traits, bitsize_t Bits, bool Secure, class \
    Alloc>
inline std::basic_istream<charT,traits>& operator>>(std::basic_istream<charT,
    traits>& in, BOOST_XINT_RAWINT& n)
{
    int hex=(in.flags() & std::ios::hex) ? 1 : 0;
    int dec=(in.flags() & std::ios::dec) ? 1 : 0;
    int oct=(in.flags() & std::ios::oct) ? 1 : 0;
    int count=hex+dec+oct;

    std::size_t base=autobase;
    if (count == 1) {
        if (hex) base = 16;
        else if (oct) base = 8;
        else base = 10;
    } else if (count > 1) base = 10;
    // else auto-base

    std::string s;
    if (in.peek()=='+') {
        in.ignore();
    } else if (in.peek()=='-') {
        in.ignore();
        s.push_back('-');
    }

    if (base==autobase) {
        if (in.peek()=='0') {
            in.ignore();
            int c=in.peek();
            if (c=='x' || c=='X') {
                in.ignore();
                base=16;
            } else base=8;
        } else base=10;
    }

    while (in) {
        int c=in.peek();
        if ((base==8 && (c>='0' && c<='7')) ||
            (base==10 && (c>='0' && c<='9')) ||
            (base==16 && ((c>='0' && c<='9') || (c>='a' && c<='f') ||
                (c>='A' && c<='F'))))
        {
            in.ignore();
            s.push_back(char(c));
        } else break;
    }

    try {
        n.from_string(s, base);
    } catch (std::exception&) {
        // Catch invalid strings
        in.setstate(std::ios::failbit);
    }

    return in;
}

//! @endcond detail
} // namespace detail
} // namespace xint
} // namespace boost

#endif // BOOST_INCLUDED_XINT_RAW_STREAMS_HPP
