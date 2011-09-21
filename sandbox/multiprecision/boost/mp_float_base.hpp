
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _MP_FLOAT_BASE_2004_02_08_HPP_
  #define _MP_FLOAT_BASE_2004_02_08_HPP_

  #include <iostream>
  #include <limits>
  #include <string>
  #include <cmath>

  #include <boost/cstdint.hpp>

  // Select the number of decimal digits in mp_float
  // by setting the value of BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_DIGITS10.
  // The supported range is 30-300.
  // Note: This is a compile-time constant.

  #if !defined(BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_DIGITS10)
    #define BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_DIGITS10 50
  #endif
  #define BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_DIGITS10_LIMIT 300

  namespace boost
  {
    namespace multiprecision
    {
    #if defined(BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_TYPE_EFX)
      class mp_float_efx;
      typedef mp_float_efx mp_float;
    #elif defined(BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_TYPE_GMP)
      class mp_float_gmp;
      typedef mp_float_gmp mp_float;
    #elif defined(BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_TYPE_MPFR)
      class mp_float_mpfr;
      typedef mp_float_mpfr mp_float;
    #else
      #error The MP float type is undefined! Define the mp_float type!
    #endif
    }
  }

  namespace boost
  {
    namespace multiprecision
    {
      class mp_float_base
      {
      public:
        static const boost::int32_t mp_digits10_setting = BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_DIGITS10;
        static const boost::int32_t mp_digits10_limit   = BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_DIGITS10_LIMIT;
        static const boost::int32_t mp_digits10         = ((mp_digits10_setting < static_cast<boost::int32_t>(30)) ? static_cast<boost::int32_t>(30) : ((mp_digits10_setting > mp_digits10_limit) ? mp_digits10_limit : mp_digits10_setting));
        static const boost::int32_t mp_digits10_extra   = static_cast<boost::int32_t>(((static_cast<boost::int64_t>(mp_digits10) * 15LL) + 50LL) / 100LL);
        static const boost::int32_t mp_max_digits10     = static_cast<boost::int32_t>(mp_digits10 + ((mp_digits10_extra < static_cast<boost::int32_t>(5)) ? static_cast<boost::int32_t>(5) : ((mp_digits10_extra > static_cast<boost::int32_t>(30)) ? static_cast<boost::int32_t>(30) : mp_digits10_extra)));

        virtual ~mp_float_base() { }

        // Specific special values.
        virtual const mp_float& my_value_nan(void) const = 0;
        virtual const mp_float& my_value_inf(void) const = 0;
        const mp_float& my_value_max(void) const;
        const mp_float& my_value_min(void) const;

        virtual void precision(const boost::int32_t) = 0;

        // Basic operations.
        virtual mp_float& operator= (const mp_float&) = 0;
        virtual mp_float& operator+=(const mp_float&) = 0;
        virtual mp_float& operator-=(const mp_float&) = 0;
        virtual mp_float& operator*=(const mp_float&) = 0;
        virtual mp_float& operator/=(const mp_float&) = 0;
        virtual mp_float& add_unsigned_long_long(const unsigned long long) = 0;
        virtual mp_float& sub_unsigned_long_long(const unsigned long long) = 0;
        virtual mp_float& mul_unsigned_long_long(const unsigned long long) = 0;
        virtual mp_float& div_unsigned_long_long(const unsigned long long) = 0;

        mp_float& add_signed_long_long(const signed long long);
        mp_float& sub_signed_long_long(const signed long long);
        mp_float& mul_signed_long_long(const signed long long);
        mp_float& div_signed_long_long(const signed long long);

        // Elementary primitives.
        virtual mp_float& calculate_inv (void) = 0;
        virtual mp_float& calculate_sqrt(void) = 0;
        virtual mp_float& negate(void) = 0;

        // Comparison functions.
        virtual boost::int32_t cmp(const mp_float&) const = 0;

        virtual bool isnan   (void) const = 0;
        virtual bool isinf   (void) const = 0;
        virtual bool isfinite(void) const = 0;

        virtual bool iszero(void) const = 0;
        virtual bool isone (void) const = 0;
        virtual bool isint (void) const = 0;
        virtual bool isneg (void) const = 0;
                bool ispos (void) const { return (!isneg()); }

        // Operators pre-increment and pre-decrement.
        virtual mp_float_base& operator++(void) = 0;
        virtual mp_float_base& operator--(void) = 0;

        // Fast order-10 range check.
        boost::int64_t order(void) const { return get_order_fast(); }

        // Conversion routines.
        virtual void               extract_parts             (double&, boost::int64_t&) const = 0;
        virtual double             extract_double            (void) const = 0;
        virtual long double        extract_long_double       (void) const = 0;
        virtual signed long long   extract_signed_long_long  (void) const = 0;
        virtual unsigned long long extract_unsigned_long_long(void) const = 0;
        virtual mp_float            extract_integer_part     (void) const = 0;
        virtual mp_float            extract_decimal_part     (void) const = 0;

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

        static mp_float my_ldexp        (const mp_float&, int);
        static mp_float my_frexp        (const mp_float&, int*);
        static mp_float my_fmod         (const mp_float&, const mp_float&);
        static mp_float my_cbrt         (const mp_float&);
        static mp_float my_rootn        (const mp_float&, const boost::uint32_t);
        static mp_float my_exp          (const mp_float&);
        static mp_float my_log          (const mp_float&);
        static mp_float my_sin          (const mp_float&);
        static mp_float my_cos          (const mp_float&);
        static mp_float my_tan          (const mp_float&);
        static mp_float my_asin         (const mp_float&);
        static mp_float my_acos         (const mp_float&);
        static mp_float my_atan         (const mp_float&);
        static mp_float my_sinh         (const mp_float&);
        static mp_float my_cosh         (const mp_float&);
        static mp_float my_tanh         (const mp_float&);
        static mp_float my_asinh        (const mp_float&);
        static mp_float my_acosh        (const mp_float&);
        static mp_float my_atanh        (const mp_float&);
        static mp_float my_gamma        (const mp_float&);
        static mp_float my_riemann_zeta (const mp_float&);
        static mp_float my_cyl_bessel_jn(const boost::int32_t, const mp_float&);
        static mp_float my_cyl_bessel_yn(const boost::int32_t, const mp_float&);

        static bool char_is_nonzero_predicate(const char& c) { return (c != static_cast<char>('0')); }

      protected:
        inline mp_float_base();

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

            boost::uint32_t n2 = 0u;

            for(boost::uint32_t i = static_cast<boost::uint32_t>(0u); i < static_cast<boost::uint32_t>(std::numeric_limits<native_float_type>::digits); i++)
            {
              // Extract the mantissa of the floating-point type in base-2
              // (yes, one bit at a time) and store it in an unsigned long long.
              // TBD: Is this really portable?
              man *= 2;

              n2   = static_cast<boost::uint32_t>(man);
              man -= static_cast<native_float_type>(n2);

              if(n2 != static_cast<boost::uint32_t>(0u))
              {
                u |= 1u;
              }

              if(i < static_cast<boost::uint32_t>(std::numeric_limits<native_float_type>::digits - 1))
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

        virtual boost::int64_t get_order_exact(void) const = 0;
        virtual boost::int64_t get_order_fast(void) const = 0;
        virtual void get_output_string(std::string& str, boost::int64_t& my_exp, const std::size_t number_of_digits) const = 0;
      };

      // Create a loud link error if the digits in the
      // mp_float headers mismatch those in a Lib or DLL.
      template<const boost::int32_t digits10> boost::int32_t digits_match_lib_dll(void);        // There's no function body here.
      template<> boost::int32_t digits_match_lib_dll<mp_float_base::mp_digits10>(void); // The function body is in mp_float_base.cpp.

      inline mp_float_base::mp_float_base()
      {
        digits_match_lib_dll_is_ok = (digits_match_lib_dll<mp_digits10>() == mp_digits10);
      }

      std::ostream& operator<<(std::ostream& os, const mp_float_base& f);
      std::istream& operator>>(std::istream& is, mp_float_base& f);
    }
  }

#endif // _MP_FLOAT_BASE_2004_02_08_HPP_
