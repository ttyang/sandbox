
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <boost/multiprecision/mp_float.hpp>
#include <boost/multiprecision/mp_float_functions.hpp>

#include "examples.h"

namespace
{
  template<typename T, const int N>
  struct integer_value_template
  {
    static const T& value(void)
    {
      static const T the_value(N);
      return the_value;
    }
  };

  std::complex<double> operator+(const boost::int32_t n, const std::complex<double>& x) { return std::complex<double>(n + x.real(),  x.imag()); }
  std::complex<double> operator-(const boost::int32_t n, const std::complex<double>& x) { return std::complex<double>(n - x.real(),  x.imag()); }
  std::complex<double> operator*(const boost::int32_t n, const std::complex<double>& x) { return std::complex<double>(n * x.real(),  n * x.imag()); }
  std::complex<double> operator/(const boost::int32_t n, const std::complex<double>& x) { return std::complex<double>(n * x.real(), -n * x.imag()) / std::norm(x); }

  std::complex<double> operator+(const std::complex<double>& x, const boost::int32_t n) { return std::complex<double>(x.real() + n, x.imag()); }
  std::complex<double> operator-(const std::complex<double>& x, const boost::int32_t n) { return std::complex<double>(x.real() - n, x.imag()); }
  std::complex<double> operator*(const std::complex<double>& x, const boost::int32_t n) { return std::complex<double>(x.real() * n, x.imag() * n); }
  std::complex<double> operator/(const std::complex<double>& x, const boost::int32_t n) { return std::complex<double>(x.real() / n, x.imag() / n); }

  typedef enum enum_orthogonal_polynomial_type
  {
    orthogonal_polynomial_type_undefined,
    orthogonal_polynomial_type_chebyshev_t,
    orthogonal_polynomial_type_chebyshev_u,
    orthogonal_polynomial_type_laguerre_l,
    orthogonal_polynomial_type_hermite_h
  }
  orthogonal_polynomial_type;

  template<typename T>
  void orthogonal_polynomial_template(const T& x,
                                      const boost::uint32_t n,
                                      const orthogonal_polynomial_type polynomial_type,
                                      std::vector<T>& results)
  {
    // Compute the value of an orthogonal polynomial of one of the following types:
    // Chebyshev 1st, Chebyshev 2nd, Laguerre, or Hermite

    results.clear();
    results.reserve(static_cast<std::size_t>(n + 1u));

    T y0 = integer_value_template<T, 1>::value();

    results.push_back(y0);

    if(n == static_cast<boost::uint32_t>(0u)) { return; }

    T y1;

    if(polynomial_type == orthogonal_polynomial_type_chebyshev_t)
    {
      y1 = x;
    }
    else if(polynomial_type == orthogonal_polynomial_type_laguerre_l)
    {
      y1 = static_cast<boost::int32_t>(1) - x;
    }
    else
    {
      y1 = x * static_cast<boost::int32_t>(2);
    }

    results.push_back(y1);

    if(n == static_cast<boost::uint32_t>(1u)) { return; }

    T a = integer_value_template<T, 2>::value();
    T b = integer_value_template<T, 0>::value();
    T c = integer_value_template<T, 1>::value();

    T yk;

    // Calculate higher orders using the recurrence relation.
    // The direction of stability is upward recurrence.
    for(boost::int32_t k = static_cast<boost::int32_t>(2); k <= static_cast<boost::int32_t>(n); k++)
    {
      if(polynomial_type == orthogonal_polynomial_type_laguerre_l)
      {
        a = integer_value_template<T, -1>::value() / k;
        b = integer_value_template<T, 2>::value() + a;
        c = integer_value_template<T, 1>::value() + a;
      }
      else if(polynomial_type == orthogonal_polynomial_type_hermite_h)
      {
        c = integer_value_template<T, 2>::value() * static_cast<boost::int32_t>(k - static_cast<boost::int32_t>(1));
      }

      yk = (((a * x) + b) * y1) - (c * y0);

      y0 = y1;
      y1 = yk;

      results.push_back(yk);
    }
  }
}

void examples::nr_010::chebyshev_t(const boost::uint32_t n, const double& x, std::vector<double>& results) { ::orthogonal_polynomial_template(x, n, ::orthogonal_polynomial_type_chebyshev_t, results); }
void examples::nr_010::chebyshev_u(const boost::uint32_t n, const double& x, std::vector<double>& results) { ::orthogonal_polynomial_template(x, n, ::orthogonal_polynomial_type_chebyshev_t, results); }
void examples::nr_010::hermite    (const boost::uint32_t n, const double& x, std::vector<double>& results) { ::orthogonal_polynomial_template(x, n, ::orthogonal_polynomial_type_laguerre_l,  results); }
void examples::nr_010::laguerre   (const boost::uint32_t n, const double& x, std::vector<double>& results) { ::orthogonal_polynomial_template(x, n, ::orthogonal_polynomial_type_hermite_h,   results); }

void examples::nr_010::chebyshev_t(const boost::uint32_t n, const std::complex<double>& x, std::vector<std::complex<double> >& results) { ::orthogonal_polynomial_template(x, n, ::orthogonal_polynomial_type_chebyshev_t, results); }
void examples::nr_010::chebyshev_u(const boost::uint32_t n, const std::complex<double>& x, std::vector<std::complex<double> >& results) { ::orthogonal_polynomial_template(x, n, ::orthogonal_polynomial_type_chebyshev_t, results); }
void examples::nr_010::hermite    (const boost::uint32_t n, const std::complex<double>& x, std::vector<std::complex<double> >& results) { ::orthogonal_polynomial_template(x, n, ::orthogonal_polynomial_type_laguerre_l,  results); }
void examples::nr_010::laguerre   (const boost::uint32_t n, const std::complex<double>& x, std::vector<std::complex<double> >& results) { ::orthogonal_polynomial_template(x, n, ::orthogonal_polynomial_type_hermite_h,   results); }

void examples::nr_010::chebyshev_t(const boost::uint32_t n, const boost::multiprecision::mp_float& x, std::vector<boost::multiprecision::mp_float>& results) { ::orthogonal_polynomial_template(x, n, ::orthogonal_polynomial_type_chebyshev_t, results); }
void examples::nr_010::chebyshev_u(const boost::uint32_t n, const boost::multiprecision::mp_float& x, std::vector<boost::multiprecision::mp_float>& results) { ::orthogonal_polynomial_template(x, n, ::orthogonal_polynomial_type_chebyshev_t, results); }
void examples::nr_010::hermite    (const boost::uint32_t n, const boost::multiprecision::mp_float& x, std::vector<boost::multiprecision::mp_float>& results) { ::orthogonal_polynomial_template(x, n, ::orthogonal_polynomial_type_laguerre_l,  results); }
void examples::nr_010::laguerre   (const boost::uint32_t n, const boost::multiprecision::mp_float& x, std::vector<boost::multiprecision::mp_float>& results) { ::orthogonal_polynomial_template(x, n, ::orthogonal_polynomial_type_hermite_h,   results); }

void examples::nr_010::chebyshev_t(const boost::uint32_t n, const boost::multiprecision::mp_complex& x, std::vector<boost::multiprecision::mp_complex>& results) { ::orthogonal_polynomial_template(x, n, ::orthogonal_polynomial_type_chebyshev_t, results); }
void examples::nr_010::chebyshev_u(const boost::uint32_t n, const boost::multiprecision::mp_complex& x, std::vector<boost::multiprecision::mp_complex>& results) { ::orthogonal_polynomial_template(x, n, ::orthogonal_polynomial_type_chebyshev_t, results); }
void examples::nr_010::hermite    (const boost::uint32_t n, const boost::multiprecision::mp_complex& x, std::vector<boost::multiprecision::mp_complex>& results) { ::orthogonal_polynomial_template(x, n, ::orthogonal_polynomial_type_laguerre_l,  results); }
void examples::nr_010::laguerre   (const boost::uint32_t n, const boost::multiprecision::mp_complex& x, std::vector<boost::multiprecision::mp_complex>& results) { ::orthogonal_polynomial_template(x, n, ::orthogonal_polynomial_type_hermite_h,   results); }
