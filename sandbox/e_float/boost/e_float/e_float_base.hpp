
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _E_FLOAT_BASE_HPP_
  #define _E_FLOAT_BASE_HPP_

  #if defined(__GNUC__)
    #include <tr1/array>
  #else
    #include <array>
  #endif

  #include <iostream>
  #include <limits>
  #include <string>
  #include <cmath>

  #include <e_float/e_float_types.hpp>

  // Select the number of decimal digits in e_float
  // by setting the value of E_FLOAT_DIGITS10.
  // The supported range is 30-300.
  // Note: This is a compile-time constant.

  #define E_FLOAT_DIGITS10     100
  #define E_FLOAT_DIGITS10_MAX 300

  #if defined(E_FLOAT_TYPE_EFX)
    namespace efx { class e_float; }
    using efx::e_float;
  #elif defined(E_FLOAT_TYPE_GMP)
    namespace gmp { class e_float; }
    using gmp::e_float;
  #elif defined(E_FLOAT_TYPE_MPFR)
    namespace mpfr { class e_float; }
    using mpfr::e_float;
  #else
    #error The e_float type is undefined! Define the e_float type!
  #endif

  class e_float_base
  {
  public:

    // The value of ef_digits10_setting is the desired number of decimal digits
    // of precision in the e_float implementation. It is limited to the range of
    // 30...300 decimal digits. The digit tolerance is invariant and it is set
    // to be 15 percent (or maximally 150 digits) larger than ef_digits10.
    // All of these quantities are invariant and they are set at compile time.
    static const INT32 ef_digits10_setting = E_FLOAT_DIGITS10;
    static const INT32 ef_digits10_max     = E_FLOAT_DIGITS10_MAX;
    static const INT32 ef_digits10         = ((ef_digits10_setting < 30) ? 30 : ((ef_digits10_setting > ef_digits10_max) ? ef_digits10_max : ef_digits10_setting));
    static const INT32 ef_digits10_extra   = static_cast<INT32>(((static_cast<INT64>(ef_digits10) * 15LL) + 50LL) / 100LL);
    static const INT32 ef_digits10_tol     = static_cast<INT32>(ef_digits10 + ((ef_digits10_extra < 15) ? 15 : ((ef_digits10_extra > 150) ? 150 : ef_digits10_extra)));

    virtual ~e_float_base() { }

    // Specific special values.
    virtual const e_float& my_value_nan(void) const = 0;
    virtual const e_float& my_value_inf(void) const = 0;
    virtual const e_float& my_value_max(void) const = 0;
    virtual const e_float& my_value_min(void) const = 0;

    virtual void precision(const INT32) = 0;

    // Basic operations.
    virtual e_float& operator= (const e_float&) = 0;
    virtual e_float& operator+=(const e_float&) = 0;
    virtual e_float& operator-=(const e_float&) = 0;
    virtual e_float& operator*=(const e_float&) = 0;
    virtual e_float& operator/=(const e_float&) = 0;
    virtual e_float& add_unsigned_long_long(const unsigned long long) = 0;
    virtual e_float& sub_unsigned_long_long(const unsigned long long) = 0;
    virtual e_float& mul_unsigned_long_long(const unsigned long long) = 0;
    virtual e_float& div_unsigned_long_long(const unsigned long long) = 0;

    e_float& add_signed_long_long(const signed long long);
    e_float& sub_signed_long_long(const signed long long);
    e_float& mul_signed_long_long(const signed long long);
    e_float& div_signed_long_long(const signed long long);

    // Elementary primitives.
    virtual e_float& calculate_inv (void) = 0;
    virtual e_float& calculate_sqrt(void) = 0;
    virtual e_float& negate(void) = 0;

    // Comparison functions.
    virtual INT32 cmp(const e_float&) const = 0;

    virtual bool isnan   (void) const = 0;
    virtual bool isinf   (void) const = 0;
    virtual bool isfinite(void) const = 0;

    virtual bool iszero (void) const = 0;
    virtual bool isone  (void) const = 0;
    virtual bool isint  (void) const = 0;
    virtual bool isneg  (void) const = 0;
            bool ispos  (void) const { return (!isneg()); }

    // Operators pre-increment and pre-decrement.
    virtual e_float_base& operator++(void) = 0;
    virtual e_float_base& operator--(void) = 0;

    // Fast order-10 range check.
    INT64 order(void) const { return get_order_fast(); }

    // Conversion routines.
    virtual void               extract_parts             (double&, INT64&) const = 0;
    virtual double             extract_double            (void) const = 0;
    virtual long double        extract_long_double       (void) const = 0;
    virtual signed long long   extract_signed_long_long  (void) const = 0;
    virtual unsigned long long extract_unsigned_long_long(void) const = 0;
    virtual e_float            extract_integer_part      (void) const = 0;
    virtual e_float            extract_decimal_part      (void) const = 0;

    // Formated Output routine.
    void wr_string(std::string& str, std::ostream& os) const;
    virtual bool rd_string(const char* const) = 0;

    // Cast operators with all built-in types.
    operator char() const               { return (std::numeric_limits<char>::is_signed ? static_cast<char>   (extract_signed_long_long()) : static_cast<char>   (extract_unsigned_long_long())); }
    operator wchar_t() const            { return (std::numeric_limits<char>::is_signed ? static_cast<wchar_t>(extract_signed_long_long()) : static_cast<wchar_t>(extract_unsigned_long_long())); }
    operator signed char() const        { return static_cast<signed char>       (extract_signed_long_long()); }
    operator signed short() const       { return static_cast<signed short>      (extract_signed_long_long()); }
    operator signed int() const         { return static_cast<signed int>        (extract_signed_long_long()); }
    operator signed long() const        { return static_cast<signed long>       (extract_signed_long_long()); }
    operator signed long long() const   { return static_cast<signed long long>  (extract_signed_long_long()); }
    operator unsigned char() const      { return static_cast<unsigned char>     (extract_unsigned_long_long()); }
    operator unsigned short() const     { return static_cast<unsigned short>    (extract_unsigned_long_long()); }
    operator unsigned int() const       { return static_cast<unsigned int>      (extract_unsigned_long_long()); }
    operator unsigned long() const      { return static_cast<unsigned long>     (extract_unsigned_long_long()); }
    operator unsigned long long() const { return static_cast<unsigned long long>(extract_unsigned_long_long()); }
    operator float() const              { return static_cast<float>(extract_double()); }
    operator double() const             { return extract_double(); }
    operator long double() const        { return extract_long_double(); }

    // Specific higher functions which might be present in the MP implementation.
    virtual bool has_its_own_ldexp        (void) const { return false; }
    virtual bool has_its_own_frexp        (void) const { return false; }
    virtual bool has_its_own_fmod         (void) const { return false; }
    virtual bool has_its_own_cbrt         (void) const { return false; }
    virtual bool has_its_own_rootn        (void) const { return false; }
    virtual bool has_its_own_exp          (void) const { return false; }
    virtual bool has_its_own_log          (void) const { return false; }
    virtual bool has_its_own_sin          (void) const { return false; }
    virtual bool has_its_own_cos          (void) const { return false; }
    virtual bool has_its_own_tan          (void) const { return false; }
    virtual bool has_its_own_asin         (void) const { return false; }
    virtual bool has_its_own_acos         (void) const { return false; }
    virtual bool has_its_own_atan         (void) const { return false; }
    virtual bool has_its_own_sinh         (void) const { return false; }
    virtual bool has_its_own_cosh         (void) const { return false; }
    virtual bool has_its_own_tanh         (void) const { return false; }
    virtual bool has_its_own_asinh        (void) const { return false; }
    virtual bool has_its_own_acosh        (void) const { return false; }
    virtual bool has_its_own_atanh        (void) const { return false; }
    virtual bool has_its_own_gamma        (void) const { return false; }
    virtual bool has_its_own_riemann_zeta (void) const { return false; }
    virtual bool has_its_own_cyl_bessel_jn(void) const { return false; }
    virtual bool has_its_own_cyl_bessel_yn(void) const { return false; }

    static e_float my_ldexp        (const e_float&, int);
    static e_float my_frexp        (const e_float&, int*);
    static e_float my_fmod         (const e_float&, const e_float&);
    static e_float my_cbrt         (const e_float&);
    static e_float my_rootn        (const e_float&, const UINT32);
    static e_float my_exp          (const e_float&);
    static e_float my_log          (const e_float&);
    static e_float my_sin          (const e_float&);
    static e_float my_cos          (const e_float&);
    static e_float my_tan          (const e_float&);
    static e_float my_asin         (const e_float&);
    static e_float my_acos         (const e_float&);
    static e_float my_atan         (const e_float&);
    static e_float my_sinh         (const e_float&);
    static e_float my_cosh         (const e_float&);
    static e_float my_tanh         (const e_float&);
    static e_float my_asinh        (const e_float&);
    static e_float my_acosh        (const e_float&);
    static e_float my_atanh        (const e_float&);
    static e_float my_gamma        (const e_float&);
    static e_float my_riemann_zeta (const e_float&);
    static e_float my_cyl_bessel_jn(const INT32, const e_float&);
    static e_float my_cyl_bessel_yn(const INT32, const e_float&);

  protected:
    inline e_float_base();

    static bool char_is_nonzero_predicate(const char& c) { return (c != static_cast<char>('0')); }

    // Emphasize: This template class can be used with native floating-point
    // types like float, double and long double. Note: For long double,
    // you need to verify that the mantissa fits in unsigned long long.
    template<typename native_float_type>
    class native_float_parts
    {
    public:
      native_float_parts(const native_float_type f) : u(0uLL), e(0) { make_parts(f); }

      const unsigned long long& get_mantissa(void) const { return u; }
      const int& get_exponent(void) const { return e; }

    private:
      native_float_parts();
      native_float_parts(const native_float_parts&);
      const native_float_parts& operator=(const native_float_parts&);

      unsigned long long u;
      int e;

      void make_parts(const native_float_type f)
      {
        if(f == static_cast<native_float_type>(0.0)) { return; }

        // Get the fraction and base-2 exponent.
        native_float_type man = ::frexp(f, &e);

        UINT32 n2 = 0u;

        for(UINT32 i = static_cast<UINT32>(0u); i < static_cast<UINT32>(std::numeric_limits<native_float_type>::digits); i++)
        {
          // Extract the mantissa of the floating-point type in base-2
          // (yes, one bit at a time) and store it in an unsigned long long.
          // TBD: Is this really portable?
          man *= 2;

          n2   = static_cast<UINT32>(man);
          man -= static_cast<native_float_type>(n2);

          if(n2 != static_cast<UINT32>(0u))
          {
            u |= 1u;
          }

          if(i < static_cast<UINT32>(std::numeric_limits<native_float_type>::digits - 1))
          {
            u <<= 1u;
          }
        }

        // Ensure that the value is normalized and adjust the exponent.
        u |= static_cast<unsigned long long>(1uLL << (std::numeric_limits<native_float_type>::digits - 1));
        e -= 1;
      }
    };

  private:
    static bool digits_match_lib_dll_is_ok;

    virtual INT64 get_order_exact(void) const = 0;
    virtual INT64 get_order_fast(void) const = 0;
    virtual void get_output_string(std::string& str, INT64& my_exp, const std::size_t number_of_digits) const = 0;

    static void wr_string_scientific(std::string& str,
                                     const INT64 my_exp,
                                     const std::size_t os_precision,
                                     const bool my_showpoint,
                                     const bool my_uppercase,
                                     const bool trim_trailing_zeros = false);

    static void wr_string_fixed(std::string& str,
                                const INT64 my_exp,
                                const std::size_t os_precision,
                                const bool my_showpoint,
                                const bool trim_trailing_zeros = false);
  };

  // Create a loud link error if the digits in the
  // e_float headers mismatch those in a Lib or DLL.
  template<const INT32 digits10> INT32 digits_match_lib_dll(void);        // There's no function body here.
  template<> INT32 digits_match_lib_dll<e_float_base::ef_digits10>(void); // The function body is in e_float_base.cpp.

  inline e_float_base::e_float_base()
  {
    digits_match_lib_dll_is_ok = (::digits_match_lib_dll<ef_digits10>() == ef_digits10);
  }

  std::ostream& operator<<(std::ostream& os, const e_float_base& f);
  std::istream& operator>>(std::istream& is, e_float_base& f);

#endif // _E_FLOAT_BASE_HPP_
