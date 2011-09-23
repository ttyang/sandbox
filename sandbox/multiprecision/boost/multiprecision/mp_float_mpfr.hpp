
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _MP_FLOAT_MPFR_HPP_
  #define _MP_FLOAT_MPFR_HPP_

  #include <cmath>
  #include <string>
  #include <climits>

  #include <boost/multiprecision/mp_float_base.hpp>

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

  namespace boost
  {
    namespace multiprecision
    {
      class mp_float_mpfr : public mp_float_base
      {
      public:
        static const boost::int32_t mp_float_digits    = static_cast<boost::int32_t>((static_cast<signed long long>(mp_float_digits10) * 2136LL) / 643LL);
        static const boost::int32_t mp_radix     = 2;

        static const boost::int64_t mp_float_max_exp   = static_cast<boost::int64_t>(LONG_MAX / static_cast<signed long>(2L)); // TBD: Ensure that (boost::int64_t >= long)
        static const boost::int64_t mp_float_min_exp   = static_cast<boost::int64_t>(LONG_MIN / static_cast<signed long>(2L)); // TBD: Ensure that (boost::int64_t >= long)
        static const boost::int64_t mp_float_max_exp10 = static_cast<boost::int64_t>((static_cast<signed long long>(mp_float_max_exp) * 643LL) / 2136LL);
        static const boost::int64_t mp_float_min_exp10 = static_cast<boost::int64_t>((static_cast<signed long long>(mp_float_min_exp) * 643LL) / 2136LL);

      private:
        static const boost::int32_t mp_float_digits2 = static_cast<boost::int32_t>((static_cast<signed long long>(mp_float_max_digits10) * 2136LL) / 643LL);
        ::mpfr_t rop;

      public:
        // Constructors
        mp_float_mpfr();
        mp_float_mpfr(const char n);
        mp_float_mpfr(const signed char n);
        mp_float_mpfr(const unsigned char n);
        mp_float_mpfr(const wchar_t n);
        mp_float_mpfr(const signed short n);
        mp_float_mpfr(const unsigned short n);
        mp_float_mpfr(const int n);
        mp_float_mpfr(const unsigned int n);
        mp_float_mpfr(const signed long n);
        mp_float_mpfr(const unsigned long n);
        mp_float_mpfr(const signed long long n);
        mp_float_mpfr(const unsigned long long n);
        mp_float_mpfr(const float f);
        mp_float_mpfr(const double d);
        mp_float_mpfr(const long double ld);
        mp_float_mpfr(const char* const s);
        mp_float_mpfr(const std::string& str);

        mp_float_mpfr(const mp_float_mpfr& f);
        mp_float_mpfr(const double mantissa, const boost::int64_t exponent);

        virtual ~mp_float_mpfr();

        virtual boost::int32_t cmp(const mp_float_mpfr& v) const;

        // Specific special values.
        virtual const mp_float_mpfr& my_value_nan(void) const;
        virtual const mp_float_mpfr& my_value_inf(void) const;

        virtual void precision(const boost::int32_t) { }

        // Basic operations.
        virtual mp_float_mpfr& operator= (const mp_float_mpfr& v);
        virtual mp_float_mpfr& operator+=(const mp_float_mpfr& v);
        virtual mp_float_mpfr& operator-=(const mp_float_mpfr& v);
        virtual mp_float_mpfr& operator*=(const mp_float_mpfr& v);
        virtual mp_float_mpfr& operator/=(const mp_float_mpfr& v);
        virtual mp_float_mpfr& add_unsigned_long_long(const unsigned long long n);
        virtual mp_float_mpfr& sub_unsigned_long_long(const unsigned long long n);
        virtual mp_float_mpfr& mul_unsigned_long_long(const unsigned long long n);
        virtual mp_float_mpfr& div_unsigned_long_long(const unsigned long long n);

        // Elementary primitives.
        virtual mp_float_mpfr& calculate_inv (void);
        virtual mp_float_mpfr& calculate_sqrt(void);
        virtual mp_float_mpfr& negate(void);

        // Comparison functions
        virtual bool isnan   (void) const;
        virtual bool isinf   (void) const;
        virtual bool isfinite(void) const;

        virtual bool iszero  (void) const;
        virtual bool isone   (void) const;
        virtual bool isint   (void) const;
        virtual bool isneg   (void) const;

        // Operators pre-increment and pre-decrement.
        virtual mp_float_mpfr& operator++(void);
        virtual mp_float_mpfr& operator--(void);

        // Conversion routines.
        virtual void               extract_parts             (double& mantissa, boost::int64_t& exponent) const;
        virtual double             extract_double            (void) const;
        virtual long double        extract_long_double       (void) const;
        virtual signed long long   extract_signed_long_long  (void) const;
        virtual unsigned long long extract_unsigned_long_long(void) const;
        virtual mp_float_mpfr            extract_integer_part      (void) const;
        virtual mp_float_mpfr            extract_decimal_part      (void) const;

        static mp_float_mpfr my_cbrt         (const mp_float_mpfr& x);
        static mp_float_mpfr my_rootn        (const mp_float_mpfr& x, const boost::uint32_t p);
        static mp_float_mpfr my_exp          (const mp_float_mpfr& x);
        static mp_float_mpfr my_log          (const mp_float_mpfr& x);
        static mp_float_mpfr my_sin          (const mp_float_mpfr& x);
        static mp_float_mpfr my_cos          (const mp_float_mpfr& x);
        static mp_float_mpfr my_tan          (const mp_float_mpfr& x);
        static mp_float_mpfr my_asin         (const mp_float_mpfr& x);
        static mp_float_mpfr my_acos         (const mp_float_mpfr& x);
        static mp_float_mpfr my_atan         (const mp_float_mpfr& x);
        static mp_float_mpfr my_sinh         (const mp_float_mpfr& x);
        static mp_float_mpfr my_cosh         (const mp_float_mpfr& x);
        static mp_float_mpfr my_tanh         (const mp_float_mpfr& x);
        static mp_float_mpfr my_asinh        (const mp_float_mpfr& x);
        static mp_float_mpfr my_acosh        (const mp_float_mpfr& x);
        static mp_float_mpfr my_atanh        (const mp_float_mpfr& x);
        static mp_float_mpfr my_gamma        (const mp_float_mpfr& x);
        static mp_float_mpfr my_riemann_zeta (const mp_float_mpfr& x);
        static mp_float_mpfr my_cyl_bessel_jn(const boost::int32_t n, const mp_float_mpfr& x);
        static mp_float_mpfr my_cyl_bessel_yn(const boost::int32_t n, const mp_float_mpfr& x);

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

      private:
        static void init(void);

        void from_unsigned_long_long(const unsigned long long u);
        void from_unsigned_long(const unsigned long u);

        virtual bool rd_string(const char* const s);

        virtual boost::int64_t get_order_exact(void) const;
        virtual boost::int64_t get_order_fast(void) const;
        virtual void get_output_string(std::string& str, boost::int64_t& my_exp, const std::size_t number_of_digits) const;
      };
    }
  }

#endif // _MP_FLOAT_MPFR_HPP_
