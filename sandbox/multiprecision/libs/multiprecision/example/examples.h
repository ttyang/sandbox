
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _EXAMPLES_2010_01_02_H_
  #define _EXAMPLES_2010_01_02_H_

  #include <vector>
  #include <complex>

  #include <boost/cstdint.hpp>
  #include <boost/multiprecision/mp_float.hpp>
  #include <boost/multiprecision/mp_float_functions.hpp>

  namespace examples
  {
    namespace nr_001
    {
      void basic_usage_real(void);
    }

    namespace nr_002
    {
      void basic_usage_imag(void);
    }

    namespace nr_005
    {
      boost::multiprecision::mp_float recursive_trapezoid_j0     (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float recursive_trapezoid_j0_test(void);
    }

    namespace nr_008
    {
      boost::multiprecision::mp_float gauss_laguerre_airy_a(const boost::multiprecision::mp_float& x);
    }

    namespace nr_010
    {
      void chebyshev_t(const boost::uint32_t n, const double& x, std::vector<double>& results);
      void chebyshev_u(const boost::uint32_t n, const double& x, std::vector<double>& results);
      void hermite    (const boost::uint32_t n, const double& x, std::vector<double>& results);
      void laguerre   (const boost::uint32_t n, const double& x, std::vector<double>& results);

      void chebyshev_t(const boost::uint32_t n, const std::complex<double>& x, std::vector<std::complex<double> >& results);
      void chebyshev_u(const boost::uint32_t n, const std::complex<double>& x, std::vector<std::complex<double> >& results);
      void hermite    (const boost::uint32_t n, const std::complex<double>& x, std::vector<std::complex<double> >& results);
      void laguerre   (const boost::uint32_t n, const std::complex<double>& x, std::vector<std::complex<double> >& results);

      void chebyshev_t(const boost::uint32_t n, const boost::multiprecision::mp_float& x, std::vector<boost::multiprecision::mp_float>& results);
      void chebyshev_u(const boost::uint32_t n, const boost::multiprecision::mp_float& x, std::vector<boost::multiprecision::mp_float>& results);
      void hermite    (const boost::uint32_t n, const boost::multiprecision::mp_float& x, std::vector<boost::multiprecision::mp_float>& results);
      void laguerre   (const boost::uint32_t n, const boost::multiprecision::mp_float& x, std::vector<boost::multiprecision::mp_float>& results);

      void chebyshev_t(const boost::uint32_t n, const boost::multiprecision::mp_complex& x, std::vector<boost::multiprecision::mp_complex>& results);
      void chebyshev_u(const boost::uint32_t n, const boost::multiprecision::mp_complex& x, std::vector<boost::multiprecision::mp_complex>& results);
      void hermite    (const boost::uint32_t n, const boost::multiprecision::mp_complex& x, std::vector<boost::multiprecision::mp_complex>& results);
      void laguerre   (const boost::uint32_t n, const boost::multiprecision::mp_complex& x, std::vector<boost::multiprecision::mp_complex>& results);
    }
  }

#endif // _EXAMPLES_2010_01_02_H_
