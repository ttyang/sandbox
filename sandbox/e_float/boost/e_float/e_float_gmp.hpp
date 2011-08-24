
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _E_FLOAT_GMP_HPP_
  #define _E_FLOAT_GMP_HPP_

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

  #if defined(__GNUC__)
    #include <tr1/array>
  #else
    #include <array>
  #endif

  #include <boost/e_float/e_float_base.hpp>

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

  namespace gmp
  {
    class e_float : public ::e_float_base
    {
    public:
      static const INT32 ef_digits    = static_cast<INT32>((static_cast<signed long long>(ef_digits10) * 2136LL) / 643LL);
      static const INT32 ef_radix     = static_cast<INT32>(2);

      static const INT64 ef_max_exp   = static_cast<INT64>(LONG_MAX - 31LL); // TBD: Ensure that (INT64 >= long)
      static const INT64 ef_min_exp   = static_cast<INT64>(LONG_MIN + 31LL); // TBD: Ensure that (INT64 >= long)
      static const INT64 ef_max_exp10 = static_cast<INT64>((static_cast<signed long long>(ef_max_exp) * 643LL) / 2136LL);
      static const INT64 ef_min_exp10 = static_cast<INT64>((static_cast<signed long long>(ef_min_exp) * 643LL) / 2136LL);

    private:
      static const INT32 ef_digits2 = static_cast<INT32>((static_cast<signed long long>(ef_max_digits10) * 2136LL) / 643LL);

      typedef enum enum_fpclass
      {
        ef_finite,
        ef_inf_pos,
        ef_inf_neg,
        ef_NaN
      }
      t_fpclass;

      t_fpclass fpclass;
      INT32     prec_elem;
      ::mpf_t   rop;

    public:
      // Constructors
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
      explicit e_float(const ::mpf_t& op);

    public:
      virtual INT32 cmp(const e_float& v) const;

      // Specific special values.
      virtual const e_float& my_value_nan(void) const;
      virtual const e_float& my_value_inf(void) const;

      virtual void precision(const INT32 prec_digits);

      // Basic operations.
      virtual e_float& operator= (const e_float& v);
      virtual e_float& operator+=(const e_float& v);
      virtual e_float& operator-=(const e_float& v);
      virtual e_float& operator*=(const e_float& v);
      virtual e_float& operator/=(const e_float& v);
      virtual e_float& add_unsigned_long_long(const unsigned long long n);
      virtual e_float& sub_unsigned_long_long(const unsigned long long n);
      virtual e_float& mul_unsigned_long_long(const unsigned long long n);
      virtual e_float& div_unsigned_long_long(const unsigned long long n);

      // Elementary primitives.
      virtual e_float& calculate_inv (void);
      virtual e_float& calculate_sqrt(void);
      virtual e_float& negate(void);

      // Comparison functions
      virtual bool isnan   (void) const { return  (fpclass == ef_NaN); }
      virtual bool isinf   (void) const { return ((fpclass == ef_inf_pos) || (fpclass == ef_inf_neg)); }
      virtual bool isfinite(void) const { return  (fpclass == ef_finite); }

      virtual bool iszero (void) const;
      virtual bool isone  (void) const;
      virtual bool isint  (void) const;
      virtual bool isneg  (void) const;

      // Operators pre-increment and pre-decrement
      virtual e_float& operator++(void);
      virtual e_float& operator--(void);

      // Conversion routines
      virtual void               extract_parts             (double& mantissa, INT64& exponent) const;
      virtual double             extract_double            (void) const;
      virtual long double        extract_long_double       (void) const;
      virtual signed long long   extract_signed_long_long  (void) const;
      virtual unsigned long long extract_unsigned_long_long(void) const;
      virtual e_float            extract_integer_part      (void) const;
      virtual e_float            extract_decimal_part      (void) const;

    private:
      static const INT64& max_exp2(void);
      static const INT64& min_exp2(void);

      static void init(void);

      void from_unsigned_long_long(const unsigned long long u);
      void from_unsigned_long(const unsigned long u);

      virtual bool rd_string(const char* const s);

      virtual INT64 get_order_exact(void) const;
      virtual INT64 get_order_fast(void) const;
      virtual void get_output_string(std::string& str, INT64& my_exp, const std::size_t number_of_digits) const;
    };
  }

#endif // _E_FLOAT_GMP_HPP_
