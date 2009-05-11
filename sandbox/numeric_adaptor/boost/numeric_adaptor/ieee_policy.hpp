// Numeric Adaptor Library

// Copyright Barend Gehrels 2009, Geodan, Amsterdam
// Copyright Bruno Lalande 2009
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef NUMERIC_ADAPTOR_IEEE_POLICY_HPP_
#define NUMERIC_ADAPTOR_IEEE_POLICY_HPP_


#include <cmath>
#include <boost/numeric/conversion/cast.hpp>


template <typename T>
struct ieee_policy
{
    typedef T type;

    static inline void init(type& value) {}
    static inline void destruct(type& value) {}

    template <typename OtherType>
    static inline void set (type& value, const OtherType& v)   { value = boost::numeric_cast<T>(v); }

    static inline void copy(const type& source, type& dest) { dest = source; }

    static inline void add(type& r, const type& a, const type& b) { r = a + b; }
    static inline void subtract(type& r, const type& a, const type& b) { r = a - b; }
    static inline void multiply(type& r, const type& a, const type& b) { r = a * b; }
    static inline void divide(type& r, const type& a, const type& b) { r = a / b; }

    static inline void sqrt(type& r, const type& a) { r = std::sqrt(a); }
    static inline void cos(type& r, const type& a) { r = std::cos(a); }
    static inline void sin(type& r, const type& a) { r = std::sin(a); }

    template <typename OtherType>
    static inline OtherType big_numeric_cast(const type& v)
    {
        return boost::numeric_cast<OtherType>(v);
    }

    static inline int compare(const type& a, const type& b)
    {
        return a < b ? -1 : a > b ? 1 : 0;
    }
};


#endif
