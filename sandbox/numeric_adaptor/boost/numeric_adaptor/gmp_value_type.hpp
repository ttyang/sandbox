// Numeric Adaptor Library
//
// Copyright Barend Gehrels 2009, Geodan, Amsterdam
// Copyright Bruno Lalande 2009
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef NUMERIC_ADAPTOR_GMP_VALUE_TYPE_HPP
#define NUMERIC_ADAPTOR_GMP_VALUE_TYPE_HPP


#include <gmp.h>


namespace boost { namespace numeric_adaptor {


struct gmp_value_type
{
    gmp_value_type()
    {
        mpf_init(m_value);
    }

    gmp_value_type(double v)
    {
        mpf_init(m_value);
        mpf_set_d(m_value, v);
    }

    gmp_value_type(mpf_t& v)
    {
        mpf_init(m_value);
        mpf_set(m_value, v);
    }

    gmp_value_type(gmp_value_type const& other)
    {
        mpf_init(m_value);
        mpf_set(m_value, other.m_value);
    }

    ~gmp_value_type()
    {
        mpf_clear(m_value);
    }

    operator double() const
    {
        return mpf_get_d(m_value);
    }

    friend inline gmp_value_type operator+(
        gmp_value_type const& a,
        gmp_value_type const& b)
    {
        gmp_value_type r;
        mpf_add(r.m_value, a.m_value, b.m_value);
        return r;
    }

    gmp_value_type& operator+=(gmp_value_type const& other)
    {
        mpf_add(m_value, m_value, other.m_value);
        return *this;
    }

    friend inline gmp_value_type operator-(
        gmp_value_type const& a,
        gmp_value_type const& b)
    {
        gmp_value_type r;
        mpf_sub(r.m_value, a.m_value, b.m_value);
        return r;
    }

    gmp_value_type& operator-=(gmp_value_type const& other)
    {
        mpf_sub(m_value, m_value, other.m_value);
        return *this;
    }

    friend inline gmp_value_type operator*(
        gmp_value_type const& a,
        gmp_value_type const& b)
    {
        gmp_value_type r;
        mpf_mul(r.m_value, a.m_value, b.m_value);
        return r;
    }

    gmp_value_type& operator*=(gmp_value_type const& other)
    {
        mpf_mul(m_value, m_value, other.m_value);
        return *this;
    }

    friend inline gmp_value_type operator/(
        gmp_value_type const& a,
        gmp_value_type const& b)
    {
        gmp_value_type r;
        mpf_div(r.m_value, a.m_value, b.m_value);
        return r;
    }

    gmp_value_type& operator/=(gmp_value_type const& other)
    {
        mpf_div(m_value, m_value, other.m_value);
        return *this;
    }

    mpf_t m_value;
};


} // namespace numeric_adaptor


numeric_adaptor::gmp_value_type sqrt(numeric_adaptor::gmp_value_type const& v)
{
    numeric_adaptor::gmp_value_type r;
    mpf_sqrt(r.m_value, v.m_value);
    return r;
}

numeric_adaptor::gmp_value_type cos(numeric_adaptor::gmp_value_type const& v)
{
    return numeric_adaptor::gmp_value_type(std::cos(v));
}

numeric_adaptor::gmp_value_type sin(numeric_adaptor::gmp_value_type const& v)
{
    return numeric_adaptor::gmp_value_type(std::sin(v));
}

numeric_adaptor::gmp_value_type tan(numeric_adaptor::gmp_value_type const& v)
{
    return numeric_adaptor::gmp_value_type(std::tan(v));
}

numeric_adaptor::gmp_value_type atan(numeric_adaptor::gmp_value_type const& v)
{
    return numeric_adaptor::gmp_value_type(std::atan(v));
}

numeric_adaptor::gmp_value_type hypot(
    numeric_adaptor::gmp_value_type const& a,
    numeric_adaptor::gmp_value_type const& b)
{
    numeric_adaptor::gmp_value_type r;
    mpf_t aa;
    mpf_init(aa);
    mpf_mul(aa, a.m_value, a.m_value);
    mpf_t bb;
    mpf_init(bb);
    mpf_mul(bb, b.m_value, b.m_value);
    mpf_add(r.m_value, aa, bb);
    mpf_clear(aa);
    mpf_clear(bb);
    mpf_sqrt(r.m_value, r.m_value);
    return r;
}


} // namespace boost


#endif
