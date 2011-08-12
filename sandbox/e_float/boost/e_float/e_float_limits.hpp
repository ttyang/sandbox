
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _E_FLOAT_LIMITS_HPP_
  #define _E_FLOAT_LIMITS_HPP_

  #include <limits>

  namespace ef
  {
    const e_float& zero     (void);
    const e_float& one      (void);
    const e_float& half     (void);
    const e_float& value_min(void);
    const e_float& value_max(void);
    const e_float& value_eps(void);
    const e_float& value_inf(void);
    const e_float& value_nan(void);
  }

  // Specialization of std::numeric_limits<e_float>.
  namespace std
  {
    template <> class numeric_limits<e_float>
    {
    public:
      static const bool                    is_specialized    = true;
      static const bool                    is_signed         = true;
      static const bool                    is_integer        = false;
      static const bool                    is_exact          = false;
      static const bool                    is_bounded        = true;
      static const bool                    is_modulo         = false;
      static const bool                    is_iec559         = false;
      static const int                     digits            = e_float::ef_digits;
      static const int                     digits10          = e_float::ef_digits10;
      static const int                     max_digits10      = e_float::ef_max_digits10;
      static const INT64                   min_exponent      = e_float::ef_min_exp;      // Type differs from int.
      static const INT64                   min_exponent10    = e_float::ef_min_exp10;    // Type differs from int.
      static const INT64                   max_exponent      = e_float::ef_max_exp;      // Type differs from int.
      static const INT64                   max_exponent10    = e_float::ef_max_exp10;    // Type differs from int.
      static const int                     radix             = e_float::ef_radix;
      static const std::float_round_style  round_style       = std::round_to_nearest;
      static const bool                    has_infinity      = true;
      static const bool                    has_quiet_NaN     = true;
      static const bool                    has_signaling_NaN = false;
      static const std::float_denorm_style has_denorm        = std::denorm_absent;
      static const bool                    has_denorm_loss   = false;
      static const bool                    traps             = false;
      static const bool                    tinyness_before   = false;

      static const e_float& (min)        (void) throw() { return ef::value_min(); }
      static const e_float& (max)        (void) throw() { return ef::value_max(); }
      static const e_float& lowest       (void) throw() { return ef::zero(); }
      static const e_float& epsilon      (void) throw() { return ef::value_eps(); }
      static const e_float& round_error  (void) throw() { return ef::half(); }
      static const e_float& infinity     (void) throw() { return ef::value_inf(); }
      static const e_float& quiet_NaN    (void) throw() { return ef::value_nan(); }
      static const e_float& signaling_NaN(void) throw() { return ef::zero(); }
      static const e_float& denorm_min   (void) throw() { return ef::zero(); }
    };
  }

#endif // _E_FLOAT_LIMITS_HPP_
