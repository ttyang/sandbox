
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _MP_FLOAT_FUNCTIONS_HPP_
  #define _MP_FLOAT_FUNCTIONS_HPP_

  #include <vector>
  #include <deque>

  #include <boost/multiprecision/mp_float.hpp>
  #include <boost/multiprecision/mp_complex.hpp>

  namespace boost
  {
    namespace multiprecision
    {
      inline boost::int32_t max_iteration(void) { return static_cast<boost::int32_t>(10000); }
      inline boost::int64_t tol(void)           { return static_cast<boost::int64_t>(boost::multiprecision::mp_float::mp_float_max_digits10); }

      inline boost::multiprecision::mp_float fabs(const boost::multiprecision::mp_float& x) { return (x.isneg() ? boost::multiprecision::mp_float(x).negate() : x); }

      boost::multiprecision::mp_float floor(const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float ceil (const boost::multiprecision::mp_float& x);
      boost::int32_t                  sgn  (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float ldexp(const boost::multiprecision::mp_float& v, int e);
      boost::multiprecision::mp_float frexp(const boost::multiprecision::mp_float& v, int* expon);
      boost::multiprecision::mp_float fmod (const boost::multiprecision::mp_float& v1, const boost::multiprecision::mp_float& v2);

             bool isnan(const double x);
      inline bool isnan(const boost::multiprecision::mp_float& x)       { return x.isnan(); }
      inline bool isnan(const boost::multiprecision::mp_complex& z)     { return z.isnan(); }

             bool isfinite(const double x);
      inline bool isfinite(const boost::multiprecision::mp_float& x)    { return x.isfinite(); }
      inline bool isfinite(const boost::multiprecision::mp_complex& z)  { return z.isfinite(); }

             bool isinf(const double x);
      inline bool isinf(const boost::multiprecision::mp_float& x)       { return x.isinf(); }
      inline bool isinf(const boost::multiprecision::mp_complex& z)     { return z.isinf(); }

      inline bool isneg(const double x)          { return (x < 0.0); }
      inline bool isneg(const boost::multiprecision::mp_float& x)       { return x.isneg(); }
      inline bool isneg(const boost::multiprecision::mp_complex& z)     { return z.isneg(); }

      inline boost::multiprecision::mp_float abs (const boost::multiprecision::mp_float& x) { return boost::multiprecision::fabs(x); }
      inline boost::multiprecision::mp_float real(const boost::multiprecision::mp_float& x) { return x; }
      inline boost::multiprecision::mp_float imag(const boost::multiprecision::mp_float&)   { return boost::multiprecision::zero(); }

      inline bool ispos(const double x)                             { return !isneg(x); }
      inline bool ispos(const boost::multiprecision::mp_float& x)   { return !x.isneg(); }
      inline bool ispos(const boost::multiprecision::mp_complex& z) { return !z.isneg(); }

             bool isint(const double x);
      inline bool isint(const boost::multiprecision::mp_float& x)   { return x.isint(); }
      inline bool isint(const boost::multiprecision::mp_complex& z) { return z.isint(); }

      inline bool isone(const double x)                             { return (::fabs(1.0 - x) < (std::numeric_limits<double>::min)() * 2); }
      inline bool isone(const boost::multiprecision::mp_float& x)   { return x.isone(); }
      inline bool isone(const boost::multiprecision::mp_complex& z) { return z.isone(); }

      inline bool iszero(const double x)                             { return (::fabs(x) < (std::numeric_limits<double>::min)() * 2); }
      inline bool iszero(const boost::multiprecision::mp_float& x)   { return x.iszero(); }
      inline bool iszero(const boost::multiprecision::mp_complex& z) { return z.iszero(); }

      boost::multiprecision::mp_float integer_part(const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float decimal_part(const boost::multiprecision::mp_float& x);

      void to_parts(const boost::multiprecision::mp_float& x, double& mantissa, boost::int64_t& exponent);

      inline double to_double(const double& x) { return x; }
             double to_double(const boost::multiprecision::mp_float& x);
             double to_double(const boost::multiprecision::mp_complex& z);

      inline boost::int64_t order_of(const double x)                           { return static_cast<boost::int64_t>(static_cast<boost::int32_t>(::log10(x) + (std::numeric_limits<double>::epsilon() * 0.9))); }
      inline boost::int64_t order_of(const boost::multiprecision::mp_float& x) { return x.order(); }

      boost::int64_t to_int64(const double x);
      boost::int64_t to_int64(const boost::multiprecision::mp_float& x);
      boost::int64_t to_int64(const boost::multiprecision::mp_complex& z);

      boost::int32_t to_int32(const double x);
      boost::int32_t to_int32(const boost::multiprecision::mp_float& x);
      boost::int32_t to_int32(const boost::multiprecision::mp_complex& z);

      bool small_arg(const double x);
      bool small_arg(const boost::multiprecision::mp_float& x);
      bool small_arg(const boost::multiprecision::mp_complex& z);

      bool large_arg(const double x);
      bool large_arg(const boost::multiprecision::mp_float& x);
      bool large_arg(const boost::multiprecision::mp_complex& z);

      bool near_one(const double x);
      bool near_one(const boost::multiprecision::mp_float& x);
      bool near_one(const boost::multiprecision::mp_complex& z);

      bool near_int(const double x);
      bool near_int(const boost::multiprecision::mp_float& x);
      bool near_int(const boost::multiprecision::mp_complex& z);

      const boost::multiprecision::mp_float& two                     (void);
      const boost::multiprecision::mp_float& three                   (void);
      const boost::multiprecision::mp_float& four                    (void);
      const boost::multiprecision::mp_float& five                    (void);
      const boost::multiprecision::mp_float& six                     (void);
      const boost::multiprecision::mp_float& seven                   (void);
      const boost::multiprecision::mp_float& eight                   (void);
      const boost::multiprecision::mp_float& nine                    (void);
      const boost::multiprecision::mp_float& ten                     (void);
      const boost::multiprecision::mp_float& twenty                  (void);
      const boost::multiprecision::mp_float& thirty                  (void);
      const boost::multiprecision::mp_float& forty                   (void);
      const boost::multiprecision::mp_float& fifty                   (void);
      const boost::multiprecision::mp_float& hundred                 (void);
      const boost::multiprecision::mp_float& two_hundred             (void);
      const boost::multiprecision::mp_float& three_hundred           (void);
      const boost::multiprecision::mp_float& four_hundred            (void);
      const boost::multiprecision::mp_float& five_hundred            (void);
      const boost::multiprecision::mp_float& thousand                (void);
      const boost::multiprecision::mp_float& two_k                   (void);
      const boost::multiprecision::mp_float& three_k                 (void);
      const boost::multiprecision::mp_float& four_k                  (void);
      const boost::multiprecision::mp_float& five_k                  (void);
      const boost::multiprecision::mp_float& ten_k                   (void);
      const boost::multiprecision::mp_float& twenty_k                (void);
      const boost::multiprecision::mp_float& thirty_k                (void);
      const boost::multiprecision::mp_float& forty_k                 (void);
      const boost::multiprecision::mp_float& fifty_k                 (void);
      const boost::multiprecision::mp_float& hundred_k               (void);
      const boost::multiprecision::mp_float& million                 (void);
      const boost::multiprecision::mp_float& ten_M                   (void);
      const boost::multiprecision::mp_float& hundred_M               (void);
      const boost::multiprecision::mp_float& billion                 (void);
      const boost::multiprecision::mp_float& trillion                (void);
      const boost::multiprecision::mp_float& googol                  (void);
      const boost::multiprecision::mp_float& int64_min               (void);
      const boost::multiprecision::mp_float& int64_max               (void);
      const boost::multiprecision::mp_float& int32_min               (void);
      const boost::multiprecision::mp_float& int32_max               (void);
      const boost::multiprecision::mp_float& unsigned_long_long_max  (void);
      const boost::multiprecision::mp_float& signed_long_long_max    (void);
      const boost::multiprecision::mp_float& signed_long_long_min    (void);
      const boost::multiprecision::mp_float& double_min              (void);
      const boost::multiprecision::mp_float& double_max              (void);
      const boost::multiprecision::mp_float& long_double_min         (void);
      const boost::multiprecision::mp_float& long_double_max         (void);
      const boost::multiprecision::mp_float& one_minus               (void);
      const boost::multiprecision::mp_float& tenth                   (void);
      const boost::multiprecision::mp_float& eighth                  (void);
      const boost::multiprecision::mp_float& sixteenth               (void);
      const boost::multiprecision::mp_float& fifth                   (void);
      const boost::multiprecision::mp_float& quarter                 (void);
      const boost::multiprecision::mp_float& third                   (void);
      const boost::multiprecision::mp_float& two_third               (void);
      const boost::multiprecision::mp_float& four_third              (void);
      const boost::multiprecision::mp_float& three_half              (void);
      const boost::multiprecision::mp_float& sqrt2                   (void);
      const boost::multiprecision::mp_float& sqrt3                   (void);
      const boost::multiprecision::mp_float& pi                      (void);
      const boost::multiprecision::mp_float& pi_half                 (void);
      const boost::multiprecision::mp_float& pi_quarter              (void);
      const boost::multiprecision::mp_float& pi_squared              (void);
      const boost::multiprecision::mp_float& two_pi                  (void);
      const boost::multiprecision::mp_float& sqrt_pi                 (void);
      const boost::multiprecision::mp_float& degree                  (void);
      const boost::multiprecision::mp_float& exp1                    (void);
      const boost::multiprecision::mp_float& ln2                     (void);
      const boost::multiprecision::mp_float& ln3                     (void);
      const boost::multiprecision::mp_float& ln10                    (void);
      const boost::multiprecision::mp_float& log10_2                 (void);
      const boost::multiprecision::mp_float& golden_ratio            (void);
      const boost::multiprecision::mp_float& euler_gamma             (void);
      const boost::multiprecision::mp_float& catalan                 (void);
      const boost::multiprecision::mp_float& khinchin                (void);
      const boost::multiprecision::mp_float& glaisher                (void);
      const boost::multiprecision::mp_float& extreme_value_skewness  (void);
      const boost::multiprecision::mp_float& rayleigh_skewness       (void);
      const boost::multiprecision::mp_float& rayleigh_kurtosis       (void);
      const boost::multiprecision::mp_float& rayleigh_kurtosis_excess(void);

      boost::multiprecision::mp_float pow2    (const boost::int64_t p);
      boost::multiprecision::mp_float pown    (const boost::multiprecision::mp_float& x, const boost::int64_t p);
      boost::multiprecision::mp_float inv     (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float sqrt    (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float cbrt    (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float rootn   (const boost::multiprecision::mp_float& x, const boost::int32_t p);
      boost::multiprecision::mp_float exp     (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float log     (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float log10   (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float loga    (const boost::multiprecision::mp_float& a, const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float log1p   (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float log1p1m2(const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float pow     (const boost::multiprecision::mp_float& x, const boost::multiprecision::mp_float& a);
      void    sincos  (const boost::multiprecision::mp_float& x, boost::multiprecision::mp_float* const p_sin, boost::multiprecision::mp_float* const p_cos);
      boost::multiprecision::mp_float sin     (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float cos     (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float tan     (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float csc     (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float sec     (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float cot     (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float asin    (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float acos    (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float atan    (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float atan2   (const boost::multiprecision::mp_float& y, const boost::multiprecision::mp_float& x);
      void    sinhcosh(const boost::multiprecision::mp_float& x, boost::multiprecision::mp_float* const p_sin, boost::multiprecision::mp_float* const p_cos);
      boost::multiprecision::mp_float sinh    (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float cosh    (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float tanh    (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float asinh   (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float acosh   (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float atanh   (const boost::multiprecision::mp_float& x);

      boost::multiprecision::mp_float hyp0F0(const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float hyp0F1(const boost::multiprecision::mp_float& b, const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float hyp1F0(const boost::multiprecision::mp_float& a, const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float hyp1F1(const boost::multiprecision::mp_float& a, const boost::multiprecision::mp_float& b, const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float hyp2F0(const boost::multiprecision::mp_float& a, const boost::multiprecision::mp_float& b, const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float hyp2F1(const boost::multiprecision::mp_float& a, const boost::multiprecision::mp_float& b, const boost::multiprecision::mp_float& c, const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float hypPFQ(const std::deque<boost::multiprecision::mp_float>& a, const  std::deque<boost::multiprecision::mp_float>& b, const boost::multiprecision::mp_float& x);

      boost::multiprecision::mp_float gamma          (const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float gamma_near_n   (const boost::int32_t n, const boost::multiprecision::mp_float& x);
      boost::multiprecision::mp_float factorial      (const boost::uint32_t n);
      boost::multiprecision::mp_float factorial2     (const  boost::int32_t n);
      boost::multiprecision::mp_float binomial       (const boost::uint32_t n, const boost::uint32_t k);
      boost::multiprecision::mp_float binomial       (const boost::uint32_t n, const boost::multiprecision::mp_float& y);
      boost::multiprecision::mp_float binomial       (const boost::multiprecision::mp_float& x, const boost::uint32_t k);
      boost::multiprecision::mp_float binomial       (const boost::multiprecision::mp_float& x, const boost::multiprecision::mp_float& y);
      boost::multiprecision::mp_float pochhammer     (const boost::multiprecision::mp_float& x, const boost::uint32_t n);
      boost::multiprecision::mp_float pochhammer     (const boost::multiprecision::mp_float& x, const boost::multiprecision::mp_float& a);
      boost::multiprecision::mp_float bernoulli      (const boost::uint32_t n);
      void    bernoulli_table(std::vector<boost::multiprecision::mp_float>& bn, const boost::uint32_t n);
      void    prime          (const boost::uint32_t n, std::deque<boost::uint32_t>& primes);
      boost::multiprecision::mp_float riemann_zeta   (const boost::int32_t n);
      boost::multiprecision::mp_float riemann_zeta   (const boost::multiprecision::mp_float& s);
    }
  }

  namespace boost
  {
    namespace multiprecision
    {
      inline boost::multiprecision::mp_float norm(const boost::multiprecision::mp_complex& z) { return z.norm(); }
             boost::multiprecision::mp_float abs (const boost::multiprecision::mp_complex& z);
             boost::multiprecision::mp_float arg (const boost::multiprecision::mp_complex& z);
      inline boost::multiprecision::mp_float real(const boost::multiprecision::mp_complex& z) { return z.real(); }
      inline boost::multiprecision::mp_float imag(const boost::multiprecision::mp_complex& z) { return z.imag(); }

      inline boost::multiprecision::mp_complex conj(const boost::multiprecision::mp_complex& z) { return boost::multiprecision::mp_complex(z.real(), -z.imag()); }
      inline boost::multiprecision::mp_complex iz  (const boost::multiprecision::mp_complex& z) { const boost::multiprecision::mp_float tmp(z.real()); return boost::multiprecision::mp_complex(-z.imag(), tmp); }

      boost::multiprecision::mp_complex polar   (const boost::multiprecision::mp_float& mod, const boost::multiprecision::mp_float& arg);
      boost::multiprecision::mp_complex sin     (const boost::multiprecision::mp_complex& z);
      boost::multiprecision::mp_complex cos     (const boost::multiprecision::mp_complex& z);
      boost::multiprecision::mp_complex tan     (const boost::multiprecision::mp_complex& z);
      void       sincos  (const boost::multiprecision::mp_complex& z, boost::multiprecision::mp_complex* const p_sin, boost::multiprecision::mp_complex* const p_cos);
      boost::multiprecision::mp_complex csc     (const boost::multiprecision::mp_complex& z);
      boost::multiprecision::mp_complex sec     (const boost::multiprecision::mp_complex& z);
      boost::multiprecision::mp_complex cot     (const boost::multiprecision::mp_complex& z);
      boost::multiprecision::mp_complex asin    (const boost::multiprecision::mp_complex& z);
      boost::multiprecision::mp_complex acos    (const boost::multiprecision::mp_complex& z);
      boost::multiprecision::mp_complex atan    (const boost::multiprecision::mp_complex& z);
      boost::multiprecision::mp_complex inv     (const boost::multiprecision::mp_complex& z);
      boost::multiprecision::mp_complex sqrt    (const boost::multiprecision::mp_complex& z);
      boost::multiprecision::mp_complex exp     (const boost::multiprecision::mp_complex& z);
      boost::multiprecision::mp_complex log     (const boost::multiprecision::mp_complex& z);
      boost::multiprecision::mp_complex log10   (const boost::multiprecision::mp_complex& z);
      boost::multiprecision::mp_complex loga    (const boost::multiprecision::mp_complex& a, const boost::multiprecision::mp_complex& z);
      boost::multiprecision::mp_complex pown    (const boost::multiprecision::mp_complex& z, const boost::int64_t p);
      boost::multiprecision::mp_complex pow     (const boost::multiprecision::mp_complex& z, const boost::multiprecision::mp_complex& a);
      boost::multiprecision::mp_complex rootn   (const boost::multiprecision::mp_complex& z, const boost::int32_t p);
      boost::multiprecision::mp_complex sinh    (const boost::multiprecision::mp_complex& z);
      boost::multiprecision::mp_complex cosh    (const boost::multiprecision::mp_complex& z);
      boost::multiprecision::mp_complex tanh    (const boost::multiprecision::mp_complex& z);
      void       sinhcosh(const boost::multiprecision::mp_complex& z, boost::multiprecision::mp_complex* const p_sinh, boost::multiprecision::mp_complex* const p_cosh);
      boost::multiprecision::mp_complex asinh   (const boost::multiprecision::mp_complex& z);
      boost::multiprecision::mp_complex acosh   (const boost::multiprecision::mp_complex& z);
      boost::multiprecision::mp_complex atanh   (const boost::multiprecision::mp_complex& z);

      boost::multiprecision::mp_complex gamma       (const boost::multiprecision::mp_complex& z);
      boost::multiprecision::mp_complex pochhammer  (const boost::multiprecision::mp_complex& z, const boost::uint32_t n);
      boost::multiprecision::mp_complex pochhammer  (const boost::multiprecision::mp_complex& z, const boost::multiprecision::mp_complex& a);
      boost::multiprecision::mp_complex riemann_zeta(const boost::multiprecision::mp_complex& s);
    }
  }

#endif // _MP_FLOAT_FUNCTIONS_HPP_
