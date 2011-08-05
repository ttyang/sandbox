
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _E_FLOAT_MPFR_HPP_
  #define _E_FLOAT_MPFR_HPP_

  #include <cmath>
  #include <string>

  #if defined(__GNUC__)
    #include <tr1/array>
  #else
    #include <array>
  #endif

  #include <e_float/e_float_base.hpp>

  // Declare the types of MPFR.
  extern "C"
  {
    typedef unsigned long     mpfr_prec_t;
    typedef int               mpfr_sign_t;
    typedef long int          mp_exp_t;
    typedef unsigned long int mp_limb_t;

    #define mp_prec_t mpfr_prec_t
    #define mp_rnd_t  mpfr_rnd_t

    typedef struct
    {
      mpfr_prec_t _mpfr_prec;
      mpfr_sign_t _mpfr_sign;
      mp_exp_t    _mpfr_exp;
      mp_limb_t*  _mpfr_d;
    }
    __mpfr_struct;

    #define __gmp_const const

    typedef __mpfr_struct mpfr_t[1];
    typedef __mpfr_struct* mpfr_ptr;
    typedef __gmp_const __mpfr_struct* mpfr_srcptr;

    typedef enum
    {
      GMP_RNDNA   = -1,
      GMP_RNDN    =  0,
      GMP_RNDZ    =  1,
      GMP_RNDU    =  2,
      GMP_RNDD    =  3,
      GMP_RND_MAX =  4
    }
    mpfr_rnd_t;
  }

  namespace mpfr
  {
    class e_float : public ::e_float_base
    {
    public:

      static const INT32 ef_digits    = static_cast<INT32>(((static_cast<INT64>(ef_digits10) * 3322LL) + 500LL) / 1000LL);
      static const INT32 ef_radix     = 2;

      static const INT64 ef_max_exp   = static_cast<INT64>(+1073741822LL);
      static const INT64 ef_min_exp   = static_cast<INT64>(-1073741822LL);
      static const INT64 ef_max_exp10 = static_cast<INT64>(+323228496LL);
      static const INT64 ef_min_exp10 = static_cast<INT64>(-323228496LL);

    private:

      static const INT32 ef_digits2 = static_cast<INT32>(((static_cast<INT64>(ef_digits10_tol) * 3322LL) + 500LL) / 1000LL);

    private:

      ::mpfr_t rop;

    public:

      e_float();
      e_float(const char n);
      e_float(const signed char n);
      e_float(const unsigned char n);
      e_float(const wchar_t n);
      e_float(const signed short n);
      e_float(const unsigned short n);
      e_float(const signed int n);
      e_float(const unsigned int n);
      e_float(const signed long n);
      e_float(const unsigned long n);
      e_float(const signed long long n);
      e_float(const unsigned long long n);
      e_float(const float f);
      e_float(const double d);
      e_float(const long double ld);
      e_float(const char* const s);
      e_float(const std::string& str);

      e_float(const e_float& f);
      e_float(const double mantissa, const INT64 exponent);

      virtual ~e_float();


    private:

      static void init(void);

      void from_unsigned_long_long(const unsigned long long u);
      void from_unsigned_long(const unsigned long u);

    public:

      virtual INT32 cmp(const e_float& v) const;

      virtual const e_float& my_value_nan(void) const;
      virtual const e_float& my_value_inf(void) const;
      virtual const e_float& my_value_max(void) const;
      virtual const e_float& my_value_min(void) const;

      virtual void precision(const INT32) { }

      virtual e_float& operator= (const e_float& v);
      virtual e_float& operator+=(const e_float& v);
      virtual e_float& operator-=(const e_float& v);
      virtual e_float& operator*=(const e_float& v);
      virtual e_float& operator/=(const e_float& v);
      virtual e_float& add_unsigned_long_long(const unsigned long long n);
      virtual e_float& sub_unsigned_long_long(const unsigned long long n);
      virtual e_float& mul_unsigned_long_long(const unsigned long long n);
      virtual e_float& div_unsigned_long_long(const unsigned long long n);

      virtual e_float& calculate_inv (void);
      virtual e_float& calculate_sqrt(void);

      virtual bool isnan   (void) const;
      virtual bool isinf   (void) const;
      virtual bool isfinite(void) const;

      virtual bool iszero  (void) const;
      virtual bool isone   (void) const;
      virtual bool isint   (void) const;
      virtual bool isneg   (void) const;

      virtual e_float& negate(void);

      virtual e_float& operator++(void);
      virtual e_float& operator--(void);

      virtual void    extract_parts       (double& mantissa, INT64& exponent) const;
      virtual double  extract_double      (void) const;
      virtual INT64   extract_int64       (void) const;
      virtual e_float extract_integer_part(void) const;
      virtual e_float extract_decimal_part(void) const;

      virtual INT64 order(void) const;

      static e_float my_cbrt         (const e_float& x);
      static e_float my_rootn        (const e_float& x, const UINT32 p);
      static e_float my_exp          (const e_float& x);
      static e_float my_log          (const e_float& x);
      static e_float my_sin          (const e_float& x);
      static e_float my_cos          (const e_float& x);
      static e_float my_tan          (const e_float& x);
      static e_float my_asin         (const e_float& x);
      static e_float my_acos         (const e_float& x);
      static e_float my_atan         (const e_float& x);
      static e_float my_sinh         (const e_float& x);
      static e_float my_cosh         (const e_float& x);
      static e_float my_tanh         (const e_float& x);
      static e_float my_asinh        (const e_float& x);
      static e_float my_acosh        (const e_float& x);
      static e_float my_atanh        (const e_float& x);
      static e_float my_gamma        (const e_float& x);
      static e_float my_riemann_zeta (const e_float& x);
      static e_float my_cyl_bessel_jn(const INT32 n, const e_float& x);
      static e_float my_cyl_bessel_yn(const INT32 n, const e_float& x);

    private:

      virtual void wr_string(std::string& str, std::ostream& os) const;
      virtual bool rd_string(const char* const s);

    public:

      virtual bool has_its_own_cbrt         (void) const { return true; }
      virtual bool has_its_own_rootn        (void) const { return true; }
      virtual bool has_its_own_exp          (void) const { return true; }
      virtual bool has_its_own_log          (void) const { return true; }
      virtual bool has_its_own_sin          (void) const { return true; }
      virtual bool has_its_own_cos          (void) const { return true; }
      virtual bool has_its_own_tan          (void) const { return true; }
      virtual bool has_its_own_asin         (void) const { return true; }
      virtual bool has_its_own_acos         (void) const { return true; }
      virtual bool has_its_own_atan         (void) const { return true; }
      virtual bool has_its_own_sinh         (void) const { return true; }
      virtual bool has_its_own_cosh         (void) const { return true; }
      virtual bool has_its_own_tanh         (void) const { return true; }
      virtual bool has_its_own_asinh        (void) const { return true; }
      virtual bool has_its_own_acosh        (void) const { return true; }
      virtual bool has_its_own_atanh        (void) const { return true; }
      virtual bool has_its_own_gamma        (void) const { return false; }
      virtual bool has_its_own_riemann_zeta (void) const { return false; }
      virtual bool has_its_own_cyl_bessel_jn(void) const { return false; }
      virtual bool has_its_own_cyl_bessel_yn(void) const { return false; }
    };
  }

#endif // _E_FLOAT_MPFR_HPP_
