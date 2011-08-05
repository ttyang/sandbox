
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <e_float/e_float.hpp>
#include "../utility/util_lexical_cast.h"

bool e_float_base::digits_match_lib_dll_is_ok;

// Create a loud link error if the digits in the
// e_float headers mismatch those in a Lib or DLL.
template<> INT32 digits_match_lib_dll<e_float_base::ef_digits10>(void) { return e_float_base::ef_digits10; }

std::ostream& operator<<(std::ostream& os, const e_float_base& f)
{
  std::string str;
  f.wr_string(str, os);
  return (os << str);
}

std::istream& operator>>(std::istream& is, e_float_base& f)
{
  std::string str;
  static_cast<void>(is >> str);
  const bool b_read = f.rd_string(str.c_str());
  static_cast<void>(b_read);
  return is;
}

e_float& e_float_base::add_signed_long_long(const signed long long n)
{
  if(n < static_cast<signed long long>(0))
  {
    negate();
    add_unsigned_long_long(static_cast<unsigned long long>(-n));
    negate();
  }
  else
  {
    add_unsigned_long_long(static_cast<unsigned long long>(n));
  }

  return static_cast<e_float&>(*this);
}

e_float& e_float_base::sub_signed_long_long(const signed long long n)
{
  return add_signed_long_long(static_cast<signed long long>(-n));
}

e_float& e_float_base::mul_signed_long_long(const signed long long n)
{
  const bool b_neg = (n < static_cast<signed long long>(0));

  mul_unsigned_long_long((!b_neg) ? static_cast<unsigned long long>(n) : static_cast<unsigned long long>(-n));

  if(b_neg) { negate(); } return static_cast<e_float&>(*this);
}

e_float& e_float_base::div_signed_long_long(const signed long long n)
{
  const bool b_neg = (n < static_cast<signed long long>(0));

  div_unsigned_long_long((!b_neg) ? static_cast<unsigned long long>(n) : static_cast<unsigned long long>(-n));

  if(b_neg) { negate(); } return static_cast<e_float&>(*this);
}

void e_float_base::wr_string_scientific(std::string& str,
                                        const INT64 my_exp,
                                        const std::size_t os_precision,
                                        const bool my_showpoint,
                                        const bool my_uppercase,
                                        const bool trim_trailing_zeros)
{
  if(os_precision > static_cast<std::size_t>(str.length() - 1u))
  {
    // Zero-extend the string to the given precision if necessary.
    const std::size_t n_pad = static_cast<std::size_t>(os_precision - (str.length() - 1u));

    str.insert(str.end(), n_pad, static_cast<char>('0'));
  }

  // Insert the decimal point.
  str.insert(static_cast<std::size_t>(1u), ".");

  // Remove all trailing zeros if necessary.
  if(trim_trailing_zeros)
  {
    const std::string::const_reverse_iterator rit_non_zero = std::find_if(str.rbegin(), str.rend(), char_is_nonzero_predicate);

    if(rit_non_zero != str.rbegin())
    {
      const std::size_t ofs = str.length() - std::distance<std::string::const_reverse_iterator>(str.rbegin(), rit_non_zero);
      str.erase(str.begin() + ofs, str.end());
    }
  }

  // Remove the trailing decimal point if necessary.
  if((*(str.end() - 1u) == static_cast<char>('.')) && (!my_showpoint))
  {
    str.erase(str.end() - 1u, str.end());
  }

  // Append the exponent in uppercase or lower case, including its sign.
  const bool   b_exp_is_neg = (my_exp < static_cast<INT64>(0));
  const UINT64 u_exp        = static_cast<UINT64>(!b_exp_is_neg ? my_exp : static_cast<INT64>(-my_exp));

  str += (my_uppercase ? "E" : "e");
  str += (b_exp_is_neg ? "-" : "+");
  std::string str_exp = Util::lexical_cast(static_cast<INT64>(u_exp));

  // Format the exponent string to have a width that is an even multiple of three.
  const std::size_t str_exp_len      = str_exp.length();
  const std::size_t str_exp_len_mod3 = static_cast<std::size_t>(str_exp_len % 3u);
  const std::size_t str_exp_len_pad  = ((str_exp_len_mod3 != static_cast<std::size_t>(0u)) ? static_cast<std::size_t>(3u - (str_exp_len % 3u))
                                                                                           : static_cast<std::size_t>(0u));

  str += std::string(str_exp_len_pad, static_cast<char>('0'));
  str += str_exp;
}

void e_float_base::wr_string_fixed(std::string& str,
                                   const INT64 my_exp,
                                   const std::size_t os_precision,
                                   const bool my_showpoint,
                                   const bool trim_trailing_zeros)
{
  const std::size_t str_len = str.length();

  if(my_exp < static_cast<INT64>(0))
  {
    // The number is less than one in magnitude. Insert the decimal
    // point using "0" or "0." as well as the needed leading zeros.
    const std::size_t minus_exp_minus_one = static_cast<std::size_t>(-my_exp - 1);
    const std::string str_zero_insert((std::min)(minus_exp_minus_one, os_precision), static_cast<char>('0'));

    str.insert(0u, "0." + str_zero_insert);

    const INT64 n_pad = static_cast<INT64>(static_cast<INT64>(os_precision) - static_cast<INT64>(str_len + str_zero_insert.length()));

    if(n_pad > static_cast<INT64>(0))
    {
      str.insert(str.end(), static_cast<std::size_t>(n_pad), static_cast<char>('0'));
    }
  }
  else
  {
    // Insert the decimal point.
    const std::size_t my_exp_plus_one = static_cast<std::size_t>(my_exp + 1);

    str.insert(my_exp_plus_one, ".");

    // Zero-extend the string to the given precision if necessary.
    const INT64 n_pad = static_cast<INT64>(os_precision) - static_cast<INT64>(static_cast<INT64>(str_len) - (my_exp + 1));

    if(n_pad > static_cast<INT64>(0))
    {
      str.insert(str.end(), static_cast<std::size_t>(n_pad), static_cast<char>('0'));
    }
  }

  // Remove all trailing zeros if necessary.
  if(trim_trailing_zeros)
  {
    const std::string::const_reverse_iterator rit_non_zero = std::find_if(str.rbegin(), str.rend(), char_is_nonzero_predicate);

    if(rit_non_zero != str.rbegin())
    {
      const std::size_t ofs = str.length() - std::distance<std::string::const_reverse_iterator>(str.rbegin(), rit_non_zero);
      str.erase(str.begin() + ofs, str.end());
    }
  }

  // Remove the trailing decimal point if necessary.
  if((*(str.end() - 1u) == static_cast<char>('.')) && (!my_showpoint))
  {
    str.erase(str.end() - 1u, str.end());
  }
}

e_float e_float_base::my_ldexp        (const e_float&, int)            { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_frexp        (const e_float&, int*)           { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_fmod         (const e_float&, const e_float&) { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_cbrt         (const e_float&)                 { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_rootn        (const e_float&, const UINT32)   { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_exp          (const e_float&)                 { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_log          (const e_float&)                 { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_sin          (const e_float&)                 { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_cos          (const e_float&)                 { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_tan          (const e_float&)                 { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_asin         (const e_float&)                 { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_acos         (const e_float&)                 { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_atan         (const e_float&)                 { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_sinh         (const e_float&)                 { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_cosh         (const e_float&)                 { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_tanh         (const e_float&)                 { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_asinh        (const e_float&)                 { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_acosh        (const e_float&)                 { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_atanh        (const e_float&)                 { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_gamma        (const e_float&)                 { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_riemann_zeta (const e_float&)                 { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_cyl_bessel_jn(const INT32, const e_float&)    { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_cyl_bessel_yn(const INT32, const e_float&)    { return std::numeric_limits<e_float>::quiet_NaN(); }
