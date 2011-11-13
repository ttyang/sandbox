
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _MP_FLOAT_EFX_2004_02_08_HPP_
  #define _MP_FLOAT_EFX_2004_02_08_HPP_

  #if defined(__INTEL_COMPILER)
    #pragma warning (disable:981)
  #endif

  #include <cmath>
  #include <string>

  #include <boost/array.hpp>
  #include <boost/multiprecision/mp_float_base.hpp>

  namespace boost
  {
    namespace multiprecision
    {
      class mp_float_efx : public mp_float_base
      {
      public:
        static const boost::int32_t mp_float_digits = mp_float_digits10;
        static const boost::int32_t mp_radix        = static_cast<boost::int32_t>(10);

        static const boost::int64_t mp_float_max_exp   = static_cast<boost::int64_t>(+9223372036854775795LL);
        static const boost::int64_t mp_float_min_exp   = static_cast<boost::int64_t>(-9223372036854775795LL);
        static const boost::int64_t mp_float_max_exp10 = static_cast<boost::int64_t>(+3063937869882635616LL); // Approx. [mp_float_max_exp / log10(2)], also an even multiple of 8
        static const boost::int64_t mp_float_min_exp10 = static_cast<boost::int64_t>(-3063937869882635616LL);
        static const boost::int32_t mp_elem_digits10   = static_cast<boost::int32_t>(8);

      private:
        static const boost::int32_t mp_float_digits10_num_base = static_cast<boost::int32_t>((mp_float_max_digits10 / mp_elem_digits10) + (((mp_float_max_digits10 % mp_elem_digits10) != 0) ? 1 : 0));
        static const boost::int32_t mp_elem_number       = static_cast<boost::int32_t>(mp_float_digits10_num_base + 2);

        typedef enum enum_fpclass
        {
          mp_finite,
          mp_inf,
          mp_NaN
        }
        t_fpclass;

        static const boost::int32_t mp_elem_mask = static_cast<boost::int32_t>(100000000);

        typedef boost::array<boost::uint32_t, static_cast<std::size_t>(mp_elem_number)> array_type;

        array_type data;
        boost::int64_t      exp;
        bool       neg;
        t_fpclass  fpclass;
        boost::int32_t      prec_elem;

      public:
        // Constructors
        mp_float_efx() : data     (),
                         exp      (static_cast<boost::int64_t>(0)),
                         neg      (false),
                         fpclass  (mp_finite),
                         prec_elem(mp_elem_number) { }

        mp_float_efx(const char n);
        mp_float_efx(const signed char n);
        mp_float_efx(const unsigned char n);
        mp_float_efx(const wchar_t n);
        mp_float_efx(const signed short n);
        mp_float_efx(const unsigned short n);
        mp_float_efx(const int n);
        mp_float_efx(const unsigned int n);
        mp_float_efx(const signed long n);
        mp_float_efx(const unsigned long n);
        mp_float_efx(const signed long long n);
        mp_float_efx(const unsigned long long n);
        mp_float_efx(const float f);
        mp_float_efx(const double d);
        mp_float_efx(const long double ld);
        mp_float_efx(const char* const s);
        mp_float_efx(const std::string& str);

        mp_float_efx(const mp_float_efx& f) : data     (f.data),
                                              exp      (f.exp),
                                              neg      (f.neg),
                                              fpclass  (f.fpclass),
                                              prec_elem(f.prec_elem) { }

        // Constructor from mantissa and exponent.
        mp_float_efx(const double mantissa, const boost::int64_t exponent);

        virtual ~mp_float_efx() { }

        virtual boost::int32_t cmp(const mp_float_efx& v) const;

        // Specific special values.
        virtual const mp_float_efx& my_value_nan(void) const;
        virtual const mp_float_efx& my_value_inf(void) const;

        virtual void precision(const boost::int32_t prec_digits);

        // Basic operations.
        virtual mp_float_efx& operator= (const mp_float_efx& v);
        virtual mp_float_efx& operator+=(const mp_float_efx& v);
        virtual mp_float_efx& operator-=(const mp_float_efx& v);
        virtual mp_float_efx& operator*=(const mp_float_efx& v);
        virtual mp_float_efx& operator/=(const mp_float_efx& v);
        virtual mp_float_efx& add_unsigned_long_long(const unsigned long long n);
        virtual mp_float_efx& sub_unsigned_long_long(const unsigned long long n);
        virtual mp_float_efx& mul_unsigned_long_long(const unsigned long long n);
        virtual mp_float_efx& div_unsigned_long_long(const unsigned long long n);

        // Elementary primitives.
        virtual mp_float_efx& calculate_inv (void);
        virtual mp_float_efx& calculate_sqrt(void);
        virtual mp_float_efx& negate(void) { if(!iszero()) { neg = (!neg); } return *this; }

        // Comparison functions
        virtual bool isnan   (void) const { return (fpclass == mp_NaN); }
        virtual bool isinf   (void) const { return (fpclass == mp_inf); }
        virtual bool isfinite(void) const { return (fpclass == mp_finite); }

        virtual bool iszero (void) const;
        virtual bool isone  (void) const;
        virtual bool isint  (void) const;
        virtual bool isneg  (void) const { return neg; }

        // Operators pre-increment and pre-decrement
        virtual mp_float_efx& operator++(void);
        virtual mp_float_efx& operator--(void);

        // Conversion routines
        virtual void               extract_parts             (double& mantissa, boost::int64_t& exponent) const;
        virtual double             extract_double            (void) const;
        virtual long double        extract_long_double       (void) const;
        virtual signed long long   extract_signed_long_long  (void) const;
        virtual unsigned long long extract_unsigned_long_long(void) const;
        virtual mp_float_efx       extract_integer_part      (void) const;
        virtual mp_float_efx       extract_decimal_part      (void) const;

      private:
        static bool data_elem_is_non_zero_predicate(const boost::uint32_t& d) { return (d != static_cast<boost::uint32_t>(0u)); }
        static bool data_elem_is_non_nine_predicate(const boost::uint32_t& d) { return (d != static_cast<boost::uint32_t>(mp_float_efx::mp_elem_mask - 1)); }

        void from_unsigned_long_long(const unsigned long long u);
        void from_unsigned_long(const unsigned long u);

        boost::int32_t cmp_data(const array_type& vd) const;

        static void mul_loop_uv(const boost::uint32_t* const u, const boost::uint32_t* const v, boost::uint32_t* const w, const boost::int32_t p);
        static boost::uint32_t mul_loop_n(boost::uint32_t* const u, boost::uint32_t n, const boost::int32_t p);
        static boost::uint32_t div_loop_n(boost::uint32_t* const u, boost::uint32_t n, const boost::int32_t p);

        virtual boost::int64_t get_order_exact(void) const { return get_order_fast(); }
        virtual boost::int64_t get_order_fast (void) const;
        virtual void get_output_string(std::string& str, boost::int64_t& my_exp, const std::size_t number_of_digits) const;

        virtual bool rd_string(const char* const s);
      };
    }
  }

#endif // _MP_FLOAT_EFX_2004_02_08_HPP_
