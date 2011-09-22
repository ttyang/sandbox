
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _MP_FLOAT_GMP_HPP_
  #define _MP_FLOAT_GMP_HPP_

  #if defined(__INTEL_COMPILER)
    #pragma warning (disable:193)
    #pragma warning (disable:981)
  #endif

  #if defined(_MSC_VER)
    #pragma warning (disable:4127)
  #endif

  #include <cmath>
  #include <climits>
  #include <string>

  #include <boost/multiprecision/mp_float_base.hpp>

  // Declare the types of GMP.
  extern "C"
  {
    typedef long int          mp_size_t;
    typedef long int          mp_exp_t;
    typedef unsigned long int mp_limb_t;

    typedef struct struct__mpf_struct
    {
      int _mp_prec;
      int _mp_size;
      mp_exp_t _mp_exp;
      mp_limb_t *_mp_d;
    }
    __mpf_struct;

    typedef       __mpf_struct mpf_t[1];
    typedef       __mpf_struct* mpf_ptr;
    typedef const __mpf_struct* mpf_srcptr;
  }

  namespace boost
  {
    namespace multiprecision
    {
      class mp_float_gmp : public mp_float_base
      {
      public:
        static const boost::int32_t mp_float_digits    = static_cast<boost::int32_t>((static_cast<signed long long>(mp_float_digits10) * 2136LL) / 643LL);
        static const boost::int32_t mp_radix     = static_cast<boost::int32_t>(2);

        static const boost::int64_t mp_float_max_exp   = static_cast<boost::int64_t>(LONG_MAX - 31LL); // TBD: Ensure that (boost::int64_t >= long)
        static const boost::int64_t mp_float_min_exp   = static_cast<boost::int64_t>(LONG_MIN + 31LL); // TBD: Ensure that (boost::int64_t >= long)
        static const boost::int64_t mp_float_max_exp10 = static_cast<boost::int64_t>((static_cast<signed long long>(mp_float_max_exp) * 643LL) / 2136LL);
        static const boost::int64_t mp_float_min_exp10 = static_cast<boost::int64_t>((static_cast<signed long long>(mp_float_min_exp) * 643LL) / 2136LL);

      private:
        static const boost::int32_t mp_float_digits2 = static_cast<boost::int32_t>((static_cast<signed long long>(mp_float_max_digits10) * 2136LL) / 643LL);

        typedef enum enum_fpclass
        {
          mp_finite,
          mp_inf_pos,
          mp_inf_neg,
          mp_NaN
        }
        t_fpclass;

        t_fpclass fpclass;
        boost::int32_t     prec_elem;
        ::mpf_t   rop;

      public:
        // Constructors
        mp_float_gmp();
        mp_float_gmp(const char n);
        mp_float_gmp(const signed char n);
        mp_float_gmp(const unsigned char n);
        mp_float_gmp(const wchar_t n);
        mp_float_gmp(const signed short n);
        mp_float_gmp(const unsigned short n);
        mp_float_gmp(const signed int n);
        mp_float_gmp(const unsigned int n);
        mp_float_gmp(const signed long n);
        mp_float_gmp(const unsigned long n);
        mp_float_gmp(const signed long long n);
        mp_float_gmp(const unsigned long long n);
        mp_float_gmp(const float f);
        mp_float_gmp(const double d);
        mp_float_gmp(const long double ld);
        mp_float_gmp(const char* const s);
        mp_float_gmp(const std::string& str);

        mp_float_gmp(const mp_float_gmp& f);
        mp_float_gmp(const double mantissa, const boost::int64_t exponent);

        virtual ~mp_float_gmp();

      private:
        explicit mp_float_gmp(const ::mpf_t& op);

      public:
        virtual boost::int32_t cmp(const mp_float_gmp& v) const;

        // Specific special values.
        virtual const mp_float_gmp& my_value_nan(void) const;
        virtual const mp_float_gmp& my_value_inf(void) const;

        virtual void precision(const boost::int32_t prec_digits);

        // Basic operations.
        virtual mp_float_gmp& operator= (const mp_float_gmp& v);
        virtual mp_float_gmp& operator+=(const mp_float_gmp& v);
        virtual mp_float_gmp& operator-=(const mp_float_gmp& v);
        virtual mp_float_gmp& operator*=(const mp_float_gmp& v);
        virtual mp_float_gmp& operator/=(const mp_float_gmp& v);
        virtual mp_float_gmp& add_unsigned_long_long(const unsigned long long n);
        virtual mp_float_gmp& sub_unsigned_long_long(const unsigned long long n);
        virtual mp_float_gmp& mul_unsigned_long_long(const unsigned long long n);
        virtual mp_float_gmp& div_unsigned_long_long(const unsigned long long n);

        // Elementary primitives.
        virtual mp_float_gmp& calculate_inv (void);
        virtual mp_float_gmp& calculate_sqrt(void);
        virtual mp_float_gmp& negate(void);

        // Comparison functions
        virtual bool isnan   (void) const { return  (fpclass == mp_NaN); }
        virtual bool isinf   (void) const { return ((fpclass == mp_inf_pos) || (fpclass == mp_inf_neg)); }
        virtual bool isfinite(void) const { return  (fpclass == mp_finite); }

        virtual bool iszero (void) const;
        virtual bool isone  (void) const;
        virtual bool isint  (void) const;
        virtual bool isneg  (void) const;

        // Operators pre-increment and pre-decrement
        virtual mp_float_gmp& operator++(void);
        virtual mp_float_gmp& operator--(void);

        // Conversion routines
        virtual void               extract_parts             (double& mantissa, boost::int64_t& exponent) const;
        virtual double             extract_double            (void) const;
        virtual long double        extract_long_double       (void) const;
        virtual signed long long   extract_signed_long_long  (void) const;
        virtual unsigned long long extract_unsigned_long_long(void) const;
        virtual mp_float_gmp            extract_integer_part      (void) const;
        virtual mp_float_gmp            extract_decimal_part      (void) const;

      private:
        static const boost::int64_t& max_exp2(void);
        static const boost::int64_t& min_exp2(void);

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

#endif // _MP_FLOAT_GMP_HPP_
