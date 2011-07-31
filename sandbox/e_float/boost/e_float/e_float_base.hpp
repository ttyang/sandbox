
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
  #include <string>

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

  // Create a loud link error if the e_float headers mismatch a Lib or DLL.
  template<const INT32 digits10> INT32 digits_match_lib_dll(void);
  template<> INT32 digits_match_lib_dll<E_FLOAT_DIGITS10>(void);

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

    static const std::string::size_type& width_of_exponent_field(void);

    virtual ~e_float_base() { }

    // Specific special values.
    virtual const e_float_base& my_value_nan(void) const = 0;
    virtual const e_float_base& my_value_inf(void) const = 0;
    virtual const e_float_base& my_value_max(void) const = 0;
    virtual const e_float_base& my_value_min(void) const = 0;

    virtual INT32 cmp(const e_float&) const = 0;

    virtual void precision(const INT32) = 0;

    // Basic operations.
    virtual e_float_base& operator= (const e_float&) = 0;
    virtual e_float_base& operator+=(const e_float&) = 0;
    virtual e_float_base& operator-=(const e_float&) = 0;
    virtual e_float_base& operator*=(const e_float&) = 0;
    virtual e_float_base& operator/=(const e_float&) = 0;
    virtual e_float_base& mul_by_int(const INT32) = 0;
    virtual e_float_base& div_by_int(const INT32) = 0;

    virtual e_float_base& calculate_inv (void) = 0;
    virtual e_float_base& calculate_sqrt(void) = 0;

    // Comparison functions
    virtual bool isnan   (void) const = 0;
    virtual bool isinf   (void) const = 0;
    virtual bool isfinite(void) const = 0;

    virtual bool iszero (void) const = 0;
    virtual bool isone  (void) const = 0;
    virtual bool isint  (void) const = 0;
    virtual bool isneg  (void) const = 0;
            bool ispos  (void) const { return !isneg(); }

    virtual e_float_base& negate(void) = 0;

    // Operators pre-increment and pre-decrement
    virtual e_float_base& operator++(void) = 0;
    virtual e_float_base& operator--(void) = 0;

    // Argument range and check functions
    virtual INT64 order(void) const = 0;

    // Conversion routines
    virtual void    extract_parts       (double&, INT64&) const = 0;
    virtual double  extract_double      (void) const = 0;
    virtual INT64   extract_int64       (void) const = 0;
    virtual e_float extract_integer_part(void) const = 0;
    virtual e_float extract_decimal_part(void) const = 0;

    // Formated Output routine.
    virtual void wr_string(std::string&, std::ostream&) const = 0;
    virtual bool rd_string(const char* const) = 0;

    // Specific higher functions which might be present in the MP implementation.
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
    e_float_base()
    {
      digits_match_lib_dll_is_ok = (::digits_match_lib_dll<E_FLOAT_DIGITS10>() == E_FLOAT_DIGITS10);
    }

  private:
    static bool digits_match_lib_dll_is_ok;
  };

  std::ostream& operator<<(std::ostream& os, const e_float_base& f);
  std::istream& operator>>(std::istream& is, e_float_base& f);

#endif // _E_FLOAT_BASE_HPP_
