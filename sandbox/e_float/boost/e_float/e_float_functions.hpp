
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _E_FLOAT_FUNCTIONS_HPP_
  #define _E_FLOAT_FUNCTIONS_HPP_

  #include <vector>
  #include <deque>

  #include <boost/e_float/e_float.hpp>
  #include <boost/e_float/e_float_complex.hpp>

  namespace ef
  {
    inline INT32   max_iteration(void)    { return static_cast<INT32>(10000); }
    inline INT64   tol (void)             { return static_cast<INT64>(e_float::ef_max_digits10); }
    inline e_float fabs(const e_float& x) { return (x.isneg() ? e_float(x).negate() : x); }

    e_float floor(const e_float& x);
    e_float ceil (const e_float& x);
    INT32   sgn  (const e_float& x);
    e_float ldexp(const e_float& v, int e);
    e_float frexp(const e_float& v, int* expon);
    e_float fmod (const e_float& v1, const e_float& v2);

           bool isnan(const double x);
    inline bool isnan(const e_float& x)        { return x.isnan(); }
    inline bool isnan(const ef_complex& z)     { return z.isnan(); }

           bool isfinite(const double x);
    inline bool isfinite(const e_float& x)     { return x.isfinite(); }
    inline bool isfinite(const ef_complex& z)  { return z.isfinite(); }

           bool isinf(const double x);
    inline bool isinf(const e_float& x)        { return x.isinf(); }
    inline bool isinf(const ef_complex& z)     { return z.isinf(); }

    inline bool isneg(const double x)          { return (x < 0.0); }
    inline bool isneg(const e_float& x)        { return x.isneg(); }
    inline bool isneg(const ef_complex& z)     { return z.isneg(); }

    inline e_float abs (const e_float& x)      { return ef::fabs(x); }
    inline e_float real(const e_float& x)      { return x; }
    inline e_float imag(const e_float&)        { return ef::zero(); }

    inline bool ispos(const double x)          { return !isneg(x); }
    inline bool ispos(const e_float& x)        { return !x.isneg(); }
    inline bool ispos(const ef_complex& z)     { return !z.isneg(); }

           bool isint(const double x);
    inline bool isint(const e_float& x)        { return x.isint(); }
    inline bool isint(const ef_complex& z)     { return z.isint(); }

    inline bool isone(const double x)          { return (::fabs(1.0 - x) < (std::numeric_limits<double>::min)() * 2); }
    inline bool isone(const e_float& x)        { return x.isone(); }
    inline bool isone(const ef_complex& z)     { return z.isone(); }

    inline bool iszero(const double x)         { return (::fabs(x) < (std::numeric_limits<double>::min)() * 2); }
    inline bool iszero(const e_float& x)       { return x.iszero(); }
    inline bool iszero(const ef_complex& z)    { return z.iszero(); }

    e_float integer_part(const e_float& x);
    e_float decimal_part(const e_float& x);

    void to_parts(const e_float& x, double& mantissa, INT64& exponent);

    inline double to_double(const double& x)   { return x; }
           double to_double(const e_float& x);
           double to_double(const ef_complex& z);

    inline INT64 order_of(const double x)   { return static_cast<INT64>(static_cast<INT32>(::log10(x))); }
    inline INT64 order_of(const e_float& x) { return x.order(); }

    INT64 to_int64(const double x);
    INT64 to_int64(const e_float& x);
    INT64 to_int64(const ef_complex& z);

    INT32 to_int32(const double x);
    INT32 to_int32(const e_float& x);
    INT32 to_int32(const ef_complex& z);

    bool small_arg(const double x);
    bool small_arg(const e_float& x);
    bool small_arg(const ef_complex& z);

    bool large_arg(const double x);
    bool large_arg(const e_float& x);
    bool large_arg(const ef_complex& z);

    bool near_one(const double x);
    bool near_one(const e_float& x);
    bool near_one(const ef_complex& z);

    bool near_int(const double x);
    bool near_int(const e_float& x);
    bool near_int(const ef_complex& z);

    const e_float& two                     (void);
    const e_float& three                   (void);
    const e_float& four                    (void);
    const e_float& five                    (void);
    const e_float& six                     (void);
    const e_float& seven                   (void);
    const e_float& eight                   (void);
    const e_float& nine                    (void);
    const e_float& ten                     (void);
    const e_float& twenty                  (void);
    const e_float& thirty                  (void);
    const e_float& forty                   (void);
    const e_float& fifty                   (void);
    const e_float& hundred                 (void);
    const e_float& two_hundred             (void);
    const e_float& three_hundred           (void);
    const e_float& four_hundred            (void);
    const e_float& five_hundred            (void);
    const e_float& thousand                (void);
    const e_float& two_k                   (void);
    const e_float& three_k                 (void);
    const e_float& four_k                  (void);
    const e_float& five_k                  (void);
    const e_float& ten_k                   (void);
    const e_float& twenty_k                (void);
    const e_float& thirty_k                (void);
    const e_float& forty_k                 (void);
    const e_float& fifty_k                 (void);
    const e_float& hundred_k               (void);
    const e_float& million                 (void);
    const e_float& ten_M                   (void);
    const e_float& hundred_M               (void);
    const e_float& billion                 (void);
    const e_float& trillion                (void);
    const e_float& googol                  (void);
    const e_float& int64_min               (void);
    const e_float& int64_max               (void);
    const e_float& int32_min               (void);
    const e_float& int32_max               (void);
    const e_float& unsigned_long_long_max  (void);
    const e_float& signed_long_long_max    (void);
    const e_float& signed_long_long_min    (void);
    const e_float& double_min              (void);
    const e_float& double_max              (void);
    const e_float& long_double_min         (void);
    const e_float& long_double_max         (void);
    const e_float& one_minus               (void);
    const e_float& tenth                   (void);
    const e_float& eighth                  (void);
    const e_float& sixteenth               (void);
    const e_float& fifth                   (void);
    const e_float& quarter                 (void);
    const e_float& third                   (void);
    const e_float& two_third               (void);
    const e_float& four_third              (void);
    const e_float& three_half              (void);
    const e_float& sqrt2                   (void);
    const e_float& sqrt3                   (void);
    const e_float& pi                      (void);
    const e_float& pi_half                 (void);
    const e_float& pi_quarter              (void);
    const e_float& pi_squared              (void);
    const e_float& two_pi                  (void);
    const e_float& sqrt_pi                 (void);
    const e_float& degree                  (void);
    const e_float& exp1                    (void);
    const e_float& ln2                     (void);
    const e_float& ln3                     (void);
    const e_float& ln10                    (void);
    const e_float& log10_2                 (void);
    const e_float& golden_ratio            (void);
    const e_float& euler_gamma             (void);
    const e_float& catalan                 (void);
    const e_float& khinchin                (void);
    const e_float& glaisher                (void);
    const e_float& extreme_value_skewness  (void);
    const e_float& rayleigh_skewness       (void);
    const e_float& rayleigh_kurtosis       (void);
    const e_float& rayleigh_kurtosis_excess(void);

    e_float pow2    (const INT64 p);
    e_float pown    (const e_float& x, const INT64 p);
    e_float inv     (const e_float& x);
    e_float sqrt    (const e_float& x);
    e_float cbrt    (const e_float& x);
    e_float rootn   (const e_float& x, const INT32 p);
    e_float exp     (const e_float& x);
    e_float log     (const e_float& x);
    e_float log10   (const e_float& x);
    e_float loga    (const e_float& a, const e_float& x);
    e_float log1p   (const e_float& x);
    e_float log1p1m2(const e_float& x);
    e_float pow     (const e_float& x, const e_float& a);
    void    sincos  (const e_float& x, e_float* const p_sin, e_float* const p_cos);
    e_float sin     (const e_float& x);
    e_float cos     (const e_float& x);
    e_float tan     (const e_float& x);
    e_float csc     (const e_float& x);
    e_float sec     (const e_float& x);
    e_float cot     (const e_float& x);
    e_float asin    (const e_float& x);
    e_float acos    (const e_float& x);
    e_float atan    (const e_float& x);
    e_float atan2   (const e_float& y, const e_float& x);
    void    sinhcosh(const e_float& x, e_float* const p_sin, e_float* const p_cos);
    e_float sinh    (const e_float& x);
    e_float cosh    (const e_float& x);
    e_float tanh    (const e_float& x);
    e_float asinh   (const e_float& x);
    e_float acosh   (const e_float& x);
    e_float atanh   (const e_float& x);

    e_float hyp0F0(const e_float& x);
    e_float hyp0F1(const e_float& b, const e_float& x);
    e_float hyp1F0(const e_float& a, const e_float& x);
    e_float hyp1F1(const e_float& a, const e_float& b, const e_float& x);
    e_float hyp2F0(const e_float& a, const e_float& b, const e_float& x);
    e_float hyp2F1(const e_float& a, const e_float& b, const e_float& c, const e_float& x);
    e_float hypPFQ(const std::deque<e_float>& a, const  std::deque<e_float>& b, const e_float& x);

    e_float gamma          (const e_float& x);
    e_float gamma_near_n   (const INT32 n, const e_float& x);
    e_float factorial      (const UINT32 n);
    e_float factorial2     (const  INT32 n);
    e_float binomial       (const UINT32 n, const UINT32 k);
    e_float binomial       (const UINT32 n, const e_float& y);
    e_float binomial       (const e_float& x, const UINT32 k);
    e_float binomial       (const e_float& x, const e_float& y);
    e_float pochhammer     (const e_float& x, const UINT32 n);
    e_float pochhammer     (const e_float& x, const e_float& a);
    e_float bernoulli      (const UINT32 n);
    void    bernoulli_table(std::vector<e_float>& bn, const UINT32 n);
    void    prime          (const UINT32 n, std::deque<UINT32>& primes);
    e_float riemann_zeta   (const INT32 n);
    e_float riemann_zeta   (const e_float& s);
  }

  namespace efz
  {
    std::complex<double> to_double(const ef_complex& z);

    inline e_float norm(const ef_complex& z) { return z.norm(); }
           e_float abs (const ef_complex& z);
           e_float arg (const ef_complex& z);
    inline e_float real(const ef_complex& z) { return z.real(); }
    inline e_float imag(const ef_complex& z) { return z.imag(); }

    inline ef_complex conj(const ef_complex& z) { return ef_complex(z.real(), -z.imag()); }
    inline ef_complex iz  (const ef_complex& z) { const e_float tmp(z.real()); return ef_complex(-z.imag(), tmp); }

    ef_complex polar   (const e_float& mod, const e_float& arg);
    ef_complex sin     (const ef_complex& z);
    ef_complex cos     (const ef_complex& z);
    ef_complex tan     (const ef_complex& z);
    void       sincos  (const ef_complex& z, ef_complex* const p_sin, ef_complex* const p_cos);
    ef_complex csc     (const ef_complex& z);
    ef_complex sec     (const ef_complex& z);
    ef_complex cot     (const ef_complex& z);
    ef_complex asin    (const ef_complex& z);
    ef_complex acos    (const ef_complex& z);
    ef_complex atan    (const ef_complex& z);
    ef_complex inv     (const ef_complex& z);
    ef_complex sqrt    (const ef_complex& z);
    ef_complex exp     (const ef_complex& z);
    ef_complex log     (const ef_complex& z);
    ef_complex log10   (const ef_complex& z);
    ef_complex loga    (const ef_complex& a, const ef_complex& z);
    ef_complex pown    (const ef_complex& z, const INT64 p);
    ef_complex pow     (const ef_complex& z, const ef_complex& a);
    ef_complex rootn   (const ef_complex& z, const INT32 p);
    ef_complex sinh    (const ef_complex& z);
    ef_complex cosh    (const ef_complex& z);
    ef_complex tanh    (const ef_complex& z);
    void       sinhcosh(const ef_complex& z, ef_complex* const p_sinh, ef_complex* const p_cosh);
    ef_complex asinh   (const ef_complex& z);
    ef_complex acosh   (const ef_complex& z);
    ef_complex atanh   (const ef_complex& z);

    ef_complex gamma       (const ef_complex& z);
    ef_complex pochhammer  (const ef_complex& z, const UINT32 n);
    ef_complex pochhammer  (const ef_complex& z, const ef_complex& a);
    ef_complex riemann_zeta(const ef_complex& s);
  }

#endif // _E_FLOAT_FUNCTIONS_HPP_
