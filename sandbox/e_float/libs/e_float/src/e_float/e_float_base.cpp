
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <e_float/e_float.hpp>
#include "../utility/util_lexical_cast.h"

namespace
{
  typedef enum enum_os_float_field_type
  {
    os_float_field_scientific,
    os_float_field_fixed,
    os_float_field_none
  }
  os_float_filed_type;
}

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
  static_cast<void>(f.rd_string(str.c_str()));
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

void e_float_base::wr_string(std::string& str, std::ostream& os) const
{
  // Assess the format flags.
  const std::ios::fmtflags my_flags = os.flags();

  // Obtain the showpos flag.
  const bool my_showpos = ((my_flags & std::ios::showpos) != static_cast<std::ios::fmtflags>(0u));

  // Handle INF and NaN.
  if(isnan()) { str = ((!isneg()) ? (my_showpos ? std::string("+INF") : std::string("INF")) : std::string("-INF")); return; }
  if(isinf()) { str = "INF"; return; }

  // Get the base-10 exponent.
  INT64 my_exp = get_order_exact();

  // Get the output stream's precision and limit it to max_digits10.
  // Erroneous negative precision will be set to the zero.
  const std::size_t os_precision  = ((os.precision() > std::streamsize(-1)) ? static_cast<std::size_t>(os.precision())
                                                                            : static_cast<std::size_t>(0u));

  // Determine the kind of output format requested (scientific, fixed, none).
  os_float_filed_type my_float_field;

  if     ((my_flags & std::ios::scientific) != static_cast<std::ios::fmtflags>(0u)) { my_float_field = os_float_field_scientific; }
  else if((my_flags & std::ios::fixed) != static_cast<std::ios::fmtflags>(0u))      { my_float_field = os_float_field_fixed; }
  else { my_float_field = os_float_field_none; }

  bool use_scientific = false;
  bool use_fixed = false;

  if     (my_float_field == os_float_field_scientific) { use_scientific = true; }
  else if(my_float_field == os_float_field_fixed)      { use_fixed = true; }
  else // os_float_field_none
  {
    if(my_exp < static_cast<INT64>(-4))
    {
      // The number is small in magnitude with a large, negative exponent.
      // Use exponential notation.
      use_scientific = true;
    }
    else if(my_exp >= (std::min)(static_cast<INT64>(std::numeric_limits<e_float>::digits10), (std::max)(static_cast<INT64>(os_precision), static_cast<INT64>(7))))
    {
      // The number is large in magnitude with a large, positive exponent.
      // Use exponential notation.
      use_scientific = true;
    }
    else
    {
      use_fixed = true;
    }
  }

  // Ascertain the number of digits requested from e_float.
  std::size_t the_number_of_digits_i_want_from_e_float = static_cast<std::size_t>(0u);
  const std::size_t max10_plus_one = static_cast<std::size_t>(std::numeric_limits<e_float>::max_digits10 + 1);

  if(use_scientific)
  {
    // The float-field is scientific. The number of digits is given by
    // (1 + the ostream's precision), not to exceed (max_digits10 + 1).
    const std::size_t prec_plus_one  = static_cast<std::size_t>(1u + os_precision);
    the_number_of_digits_i_want_from_e_float = (std::min)(max10_plus_one, prec_plus_one);
  }
  else if(use_fixed)
  {
    // The float-field is scientific. The number of all-digits depends
    // on the form of the number.

    if(my_exp >= static_cast<INT64>(0))
    {
      // If the number is larger than 1 in absolute value, then the number of
      // digits is given by the width of the integer part plus the ostream's
      // precision, not to exceed (max_digits10 + 1).
      const std::size_t exp_plus_one = static_cast<std::size_t>(my_exp + 1);
      const std::size_t exp_plus_one_plus_my_precision = static_cast<std::size_t>(exp_plus_one + os_precision);

      the_number_of_digits_i_want_from_e_float = (std::min)(exp_plus_one_plus_my_precision, max10_plus_one);
    }
    else
    {
      const INT64 exp_plus_one = static_cast<INT64>(my_exp + 1);
      const INT64 exp_plus_one_plus_my_precision = static_cast<INT64>(exp_plus_one + static_cast<INT64>(os_precision));

      the_number_of_digits_i_want_from_e_float = (std::min)(static_cast<std::size_t>((std::max)(exp_plus_one_plus_my_precision, static_cast<INT64>(0))), max10_plus_one);
    }
  }

  // Extract the rounded output string with the desired number of digits.
  get_output_string(str, my_exp, the_number_of_digits_i_want_from_e_float);

  // Obtain additional format information.
  const bool my_uppercase  = ((my_flags & std::ios::uppercase)  != static_cast<std::ios::fmtflags>(0u));
  const bool my_showpoint  = ((my_flags & std::ios::showpoint)  != static_cast<std::ios::fmtflags>(0u));

  // Write the output string in the desired format.
  if     (my_float_field == os_float_field_scientific) { wr_string_scientific(str, my_exp, os_precision, my_showpoint, my_uppercase); }
  else if(my_float_field == os_float_field_fixed)      { wr_string_fixed(str, my_exp, os_precision, my_showpoint); }
  else // os_float_field_none
  {
    (use_scientific ? wr_string_scientific(str, my_exp, os_precision, my_showpoint, my_uppercase, true)
                    : wr_string_fixed(str, my_exp, os_precision, my_showpoint, true));
  }

  // Append the sign.
  if     (isneg())    { str.insert(static_cast<std::size_t>(0u), "-"); }
  else if(my_showpos) { str.insert(static_cast<std::size_t>(0u), "+"); }

  // Handle std::setw(...), std::setfill(...), std::left, std::right, std::internal.
  const std::size_t my_width = ((os.width() >= static_cast<std::streamsize>(0)) ? static_cast<std::size_t>(os.width())
                                                                                : static_cast<std::size_t>(0u));

  if(my_width > str.length())
  {
    // Get the number of fill characters.
    const std::size_t n_fill = static_cast<std::size_t>(my_width - str.length());

    // Left-justify is the exception, std::right and std::internal justify right.
    const bool my_left = ((my_flags & std::ios::left)  != static_cast<std::ios::fmtflags>(0u));

    // Justify left or right and insert the fill characters.
    str.insert((my_left ? str.end() : str.begin()), n_fill, os.fill());
  }
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
