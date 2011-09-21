
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <algorithm>

#include <boost/multiprecision/mp_float.hpp>
#include <boost/lexical_cast.hpp>

using boost::multiprecision::mp_float_base;
using boost::multiprecision::mp_float;

namespace
{
  typedef enum enum_os_float_field_type
  {
    os_float_field_scientific,
    os_float_field_fixed,
    os_float_field_none
  }
  os_float_field_type;

  void wr_string_scientific(std::string& str,
                            const boost::int64_t my_exp,
                            const std::size_t os_precision,
                            const bool my_showpoint,
                            const bool my_uppercase,
                            const bool trim_trailing_zeros = false);

  void wr_string_fixed(std::string& str,
                       const boost::int64_t my_exp,
                       const std::size_t os_precision,
                       const bool my_showpoint,
                       const bool trim_trailing_zeros = false);

  void special_handle_string_not_finite(std::string& str,
                                        const mp_float& f,
                                        const bool my_showpos,
                                        const bool my_uppercase);

  void special_extend_string_to_precision(std::string& str, const std::size_t os_precision);
}

bool mp_float_base::digits_match_lib_dll_is_ok;

// Create a loud link error if the digits in the
// mp_float headers mismatch those in a Lib or DLL.
template<> boost::int32_t boost::multiprecision::digits_match_lib_dll<mp_float_base::mp_digits10>(void) { return mp_float_base::mp_digits10; }

std::ostream& boost::multiprecision::operator<<(std::ostream& os, const mp_float_base& f)
{
  std::string str;
  f.wr_string(str, os);
  return (os << str);
}

std::istream& boost::multiprecision::operator>>(std::istream& is, mp_float_base& f)
{
  std::string str;
  static_cast<void>(is >> str);
  static_cast<void>(f.rd_string(str.c_str()));
  return is;
}

const mp_float& mp_float_base::my_value_max(void) const
{
  static const std::string str_max =   std::string("9." + std::string(static_cast<std::size_t>(mp_max_digits10), static_cast<char>('9')))
                                     + std::string("e+" + boost::lexical_cast<std::string>(std::numeric_limits<mp_float>::max_exponent10));
  static const mp_float val_max(str_max);
  return val_max;
}

const mp_float& mp_float_base::my_value_min(void) const
{
  static const mp_float val_min("1.0e" + boost::lexical_cast<std::string>(std::numeric_limits<mp_float>::min_exponent10));
  return val_min;
}

mp_float& mp_float_base::add_signed_long_long(const signed long long n)
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

  return static_cast<mp_float&>(*this);
}

mp_float& mp_float_base::sub_signed_long_long(const signed long long n)
{
  return add_signed_long_long(static_cast<signed long long>(-n));
}

mp_float& mp_float_base::mul_signed_long_long(const signed long long n)
{
  const bool b_neg = (n < static_cast<signed long long>(0));

  mul_unsigned_long_long((!b_neg) ? static_cast<unsigned long long>(n) : static_cast<unsigned long long>(-n));

  if(b_neg) { negate(); }

  return static_cast<mp_float&>(*this);
}

mp_float& mp_float_base::div_signed_long_long(const signed long long n)
{
  const bool b_neg = (n < static_cast<signed long long>(0));

  div_unsigned_long_long((!b_neg) ? static_cast<unsigned long long>(n) : static_cast<unsigned long long>(-n));

  if(b_neg) { negate(); }

  return static_cast<mp_float&>(*this);
}

void mp_float_base::wr_string(std::string& str, std::ostream& os) const
{
  // Assess the format flags.
  const std::ios::fmtflags my_flags = os.flags();

  // Obtain the showpos flag.
  const bool my_showpos   = ((my_flags & std::ios::showpos)   != static_cast<std::ios::fmtflags>(0u));
  const bool my_uppercase = ((my_flags & std::ios::uppercase) != static_cast<std::ios::fmtflags>(0u));

  // Use special handling for non-finite numbers (inf and nan).
  if(!isfinite()) { ::special_handle_string_not_finite(str, static_cast<const mp_float&>(*this), my_showpos, my_uppercase); return; }

  // Get the base-10 exponent.
  boost::int64_t my_exp = get_order_exact();

  // Get the output stream's precision and limit it to max_digits10.
  // Erroneous zero or negative precision (theoretically impossible)
  // will be set to ostream's default precision.
  static const std::stringstream str_default;
  static const std::streamsize   prec_default = str_default.precision();

  const std::size_t os_precision  = ((os.precision() <= static_cast<std::streamsize>(0)) ? static_cast<std::size_t>(prec_default) : static_cast<std::size_t>(os.precision()));

  // Determine the kind of output format requested (scientific, fixed, none).
  os_float_field_type my_float_field;

  if     ((my_flags & std::ios::scientific) != static_cast<std::ios::fmtflags>(0u)) { my_float_field = os_float_field_scientific; }
  else if((my_flags & std::ios::fixed) != static_cast<std::ios::fmtflags>(0u))      { my_float_field = os_float_field_fixed; }
  else { my_float_field = os_float_field_none; }

  bool use_scientific = false;
  bool use_fixed = false;

  if     (my_float_field == os_float_field_scientific) { use_scientific = true; }
  else if(my_float_field == os_float_field_fixed)      { use_fixed = true; }
  else // os_float_field_none
  {
    // Set up the range for dynamic detection of scientific notation.
    // If the exponent is less than -4 or larger than a precision-dependent
    // positive bound, then scientific notation is used.
    static const boost::int64_t neg_bound_for_scientific_neg_exp = static_cast<boost::int64_t>(-4);
           const boost::int64_t min_bound_for_scientific_pos_exp = (std::max)(static_cast<boost::int64_t>(os_precision), static_cast<boost::int64_t>(prec_default));
           const boost::int64_t pos_bound_for_scientific_pos_exp = (std::min)(static_cast<boost::int64_t>(std::numeric_limits<mp_float>::digits10), min_bound_for_scientific_pos_exp);

    if(   (my_exp < neg_bound_for_scientific_neg_exp)
       || (my_exp >= pos_bound_for_scientific_pos_exp)
      )
    {
      use_scientific = true;
    }
    else
    {
      use_fixed = true;
    }
  }

  // Ascertain the number of digits requested from mp_float.
  std::size_t the_number_of_digits_i_want_from_e_float = static_cast<std::size_t>(0u);
  const std::size_t max10_plus_one = static_cast<std::size_t>(std::numeric_limits<mp_float>::max_digits10 + 1);

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

    if(my_exp >= static_cast<boost::int64_t>(0))
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
      const boost::int64_t exp_plus_one = static_cast<boost::int64_t>(my_exp + 1);
      const boost::int64_t exp_plus_one_plus_my_precision = static_cast<boost::int64_t>(exp_plus_one + static_cast<boost::int64_t>(os_precision));

      the_number_of_digits_i_want_from_e_float = (std::min)(static_cast<std::size_t>((std::max)(exp_plus_one_plus_my_precision, static_cast<boost::int64_t>(0))), max10_plus_one);
    }
  }

  // If the float field is not set, reduce the number of digits requested
  // from mp_float such that it neither exceeds the ostream's precision
  // nor mp_float's max_digits10.
  if(my_float_field == os_float_field_none)
  {
    const std::size_t max_digits = (std::min)(os_precision, static_cast<std::size_t>(std::numeric_limits<mp_float>::max_digits10));
    the_number_of_digits_i_want_from_e_float = (std::min)(the_number_of_digits_i_want_from_e_float, max_digits);
  }

  // Extract the rounded output string with the desired number of digits.
  get_output_string(str, my_exp, the_number_of_digits_i_want_from_e_float);

  // Obtain additional format information.
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

namespace
{
  void special_handle_string_not_finite(std::string& str,
                                        const mp_float& f,
                                        const bool my_showpos,
                                        const bool my_uppercase)
  {
    // Handle INF and NaN.
    if(f.isinf())
    {
      if(my_uppercase)
      {
        str = ((!f.isneg()) ? (my_showpos ? std::string("+INF") : std::string("INF")) : std::string("-INF"));
      }
      else
      {
        str = ((!f.isneg()) ? (my_showpos ? std::string("+inf") : std::string("inf")) : std::string("-inf"));
      }
    }
    else
    {
      str = (my_uppercase ? std::string("NAN") : std::string("nan"));
    }
  }

  void wr_string_scientific(std::string& str,
                            const boost::int64_t my_exp,
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

    // Trim the trailing zeros, where the trim-characteristics depend on the showpoint flag.
    if(trim_trailing_zeros)
    {
      const std::string::const_reverse_iterator rit_non_zero = std::find_if(str.rbegin(), str.rend(), mp_float_base::char_is_nonzero_predicate);

      if(rit_non_zero != str.rbegin())
      {
        const std::size_t ofs = str.length() - std::distance<std::string::const_reverse_iterator>(str.rbegin(), rit_non_zero);
        str.erase(str.begin() + ofs, str.end());
      }
    }

    // Perform the final manipulations on the digits of the string.
    if(my_showpoint)
    {
      if(trim_trailing_zeros) { ::special_extend_string_to_precision(str, os_precision); }
    }
    else
    {
      // Remove the trailing decimal point if necessary.
      if(*(str.end() - 1u) == static_cast<char>('.'))
      {
        str.erase(str.end() - 1u, str.end());
      }
    }

    // Append the exponent in uppercase or lower case, including its sign.
    const bool   b_exp_is_neg = (my_exp < static_cast<boost::int64_t>(0));
    const boost::uint64_t u_exp        = static_cast<boost::uint64_t>(!b_exp_is_neg ? my_exp : static_cast<boost::int64_t>(-my_exp));

    str += (my_uppercase ? "E" : "e");
    str += (b_exp_is_neg ? "-" : "+");
    std::string str_exp = boost::lexical_cast<std::string>(static_cast<boost::int64_t>(u_exp));

    // Format the exponent string to have a width that is an even multiple of three.
    const std::size_t str_exp_len      = str_exp.length();
    const std::size_t str_exp_len_mod3 = static_cast<std::size_t>(str_exp_len % 3u);
    const std::size_t str_exp_len_pad  = ((str_exp_len_mod3 != static_cast<std::size_t>(0u)) ? static_cast<std::size_t>(3u - (str_exp_len % 3u))
                                                                                             : static_cast<std::size_t>(0u));

    str += std::string(str_exp_len_pad, static_cast<char>('0'));
    str += str_exp;
  }

  void wr_string_fixed(std::string& str,
                       const boost::int64_t my_exp,
                       const std::size_t os_precision,
                       const bool my_showpoint,
                       const bool trim_trailing_zeros)
  {
    const std::size_t input_str_len = str.length();

    if(my_exp < static_cast<boost::int64_t>(0))
    {
      // The number is less than one in magnitude. Insert the decimal
      // point using "0." as well as the needed number of leading zeros.
      const std::size_t minus_exp_minus_one = static_cast<std::size_t>(-my_exp - 1);
      const std::string str_zero_insert((std::min)(minus_exp_minus_one, os_precision), static_cast<char>('0'));

      const boost::int64_t n_pad = static_cast<boost::int64_t>(static_cast<boost::int64_t>(os_precision) - static_cast<boost::int64_t>(str.length() + str_zero_insert.length()));

      str.insert(0u, "0." + str_zero_insert);

      // Zero-extend the string to the given precision if necessary.
      if(n_pad > static_cast<boost::int64_t>(0))
      {
        str.insert(str.end(), static_cast<std::size_t>(n_pad), static_cast<char>('0'));
      }
    }
    else
    {
      // Insert the decimal point.
      const std::size_t my_exp_plus_one = static_cast<std::size_t>(my_exp + 1);

      // The number string is not large enough to hold the integer part of the number.
      // Zero extend the integer part of the string.
      if(input_str_len < my_exp_plus_one)
      {
        str.insert(str.end(), static_cast<std::size_t>(my_exp_plus_one- str.length()), static_cast<char>('0'));
      }

      str.insert(my_exp_plus_one, ".");

      // Zero-extend the string to the given precision if necessary.
      const boost::int64_t n_pad = static_cast<boost::int64_t>(os_precision) - static_cast<boost::int64_t>(static_cast<boost::int64_t>(str.length() - 1u) - (my_exp + 1));

      if(n_pad > static_cast<boost::int64_t>(0))
      {
        str.insert(str.end(), static_cast<std::size_t>(n_pad), static_cast<char>('0'));
      }
    }

    // Trim the trailing zeros, where the trim-characteristics depend on the showpoint flag.
    if(trim_trailing_zeros)
    {
      const std::string::const_reverse_iterator rit_non_zero = std::find_if(str.rbegin(), str.rend(), mp_float_base::char_is_nonzero_predicate);

      if(rit_non_zero != str.rbegin())
      {
        const std::size_t ofs = str.length() - std::distance<std::string::const_reverse_iterator>(str.rbegin(), rit_non_zero);
        str.erase(str.begin() + ofs, str.end());
      }
    }

    // Perform the final manipulations on the digits of the string.
    if(my_showpoint)
    {
      if(trim_trailing_zeros) { ::special_extend_string_to_precision(str, os_precision); }
    }
    else
    {
      // Remove the trailing decimal point if necessary.
      if(*(str.end() - 1u) == static_cast<char>('.'))
      {
        str.erase(str.end() - 1u, str.end());
      }
    }
  }

  void special_extend_string_to_precision(std::string& str, const std::size_t os_precision)
  {
    // This is the special case of showpoint in combination with
    // a non-fixed, non-scientific representation. The string has
    // to be zero extended such that the total width of its entire
    // non-zero part exactly equals the precision.

    // Check if the number is less than 1.
    if(   (str.at(static_cast<std::size_t>(0u)) == static_cast<char>('0'))
       && (str.at(static_cast<std::size_t>(1u)) == static_cast<char>('.'))
      )
    {
      if(str.length() == static_cast<std::size_t>(2u))
      {
        // This string represents zero and needs zero extension.
        str.insert(str.end(), os_precision, static_cast<char>('0'));
      }
      else
      {
        // This is a non-zero decimal less than 1 that needs zero extension.
        const std::string::const_iterator it_non_zero = std::find_if(str.begin() + 2u, str.end(), mp_float_base::char_is_nonzero_predicate);
        const std::size_t len_non_zero_part = std::distance<std::string::const_iterator>(it_non_zero, str.end());
        const std::size_t u_pad = static_cast<std::size_t>(os_precision - len_non_zero_part);
        str.insert(str.end(), u_pad, static_cast<char>('0'));
      }
    }
    else
    {
      // This is a number greater than or equal to 1 that needs zero extension.
      const std::size_t u_pad = static_cast<std::size_t>(os_precision - static_cast<std::size_t>(str.length() - static_cast<std::size_t>(1u)));
      str.insert(str.end(), u_pad, static_cast<char>('0'));
    }
  }
}

mp_float mp_float_base::my_ldexp        (const mp_float&, int)            { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_frexp        (const mp_float&, int*)           { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_fmod         (const mp_float&, const mp_float&) { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_cbrt         (const mp_float&)                 { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_rootn        (const mp_float&, const boost::uint32_t)   { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_exp          (const mp_float&)                 { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_log          (const mp_float&)                 { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_sin          (const mp_float&)                 { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_cos          (const mp_float&)                 { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_tan          (const mp_float&)                 { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_asin         (const mp_float&)                 { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_acos         (const mp_float&)                 { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_atan         (const mp_float&)                 { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_sinh         (const mp_float&)                 { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_cosh         (const mp_float&)                 { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_tanh         (const mp_float&)                 { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_asinh        (const mp_float&)                 { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_acosh        (const mp_float&)                 { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_atanh        (const mp_float&)                 { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_gamma        (const mp_float&)                 { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_riemann_zeta (const mp_float&)                 { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_cyl_bessel_jn(const boost::int32_t, const mp_float&)    { return std::numeric_limits<mp_float>::quiet_NaN(); }
mp_float mp_float_base::my_cyl_bessel_yn(const boost::int32_t, const mp_float&)    { return std::numeric_limits<mp_float>::quiet_NaN(); }

/*
#include <iostream>
#include <boost/array>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <regex>

namespace
{
  struct regex_matcher
  {
  private:
    regex_matcher();
    const regex_matcher& operator=(const regex_matcher&);

    std::match_results<std::string::const_iterator>& results;
    const std::string& str;

  public:
    regex_matcher(std::match_results<std::string::const_iterator>& mr, const std::string& s) : results(mr), str(s) { }

    regex_matcher(const regex_matcher& rxm) : results(rxm.results), str(rxm.str) { }

    bool operator()(const std::regex& rx) const { return std::regex_match(str, results, rx); }
  };

  template<typename T>
  std::string lexical_cast(const T& t)
  {
    std::stringstream ss;
    ss << t;
    return ss.str();
  }
}

bool rd_string(const std::string& str)
{
  // Use regular expressions to do a preliminary parse of the input string.

  // Here is the key to the upcoming regular expressions.
  // [1] = sign(s)
  // [2] = leading zeros
  // [3] = mantissa
  // [4] = dot
  // [5] = decimal part
  // [6] = exponent letter e or E
  // [7] = exponent sign + or -
  // [8] = exponent's leading zeros
  // [9] = exponent value
  static const std::array<std::regex, 6u> the_regs_data =
  {{
    std::regex("([+|-]*)([0]*)([0-9]+)([.])([0-9]*)([e|E])([+|-]*)([0]*)([0-9]+)"), // Exponent with dot, integer part required.
    std::regex("([+|-]*)([0]*)([0-9]*)([.])([0-9]+)([e|E])([+|-]*)([0]*)([0-9]+)"), // Exponent with dot, decimal part required.
    std::regex("([+|-]*)([0]*)([0-9]+)()()([e|E])([+|-]*)([0]*)([0-9]+)"),          // Exponent no dot, integer part required.
    std::regex("([+|-]*)([0]*)([0-9]+)([.])([0-9]*)()()()()"),                      // Fixed with dot, integer part required.
    std::regex("([+|-]*)([0]*)([0-9]*)([.])([0-9]+)()()()()"),                      // Fixed with dot, decimal part required.
    std::regex("([+|-]*)([0]*)([0-9]+)()()()()()()")                                // Fixed no dot.
  }};

  static const std::vector<std::regex> the_regs(the_regs_data.begin(), the_regs_data.end());

  std::match_results<std::string::const_iterator> mr;

  const std::vector<std::regex>::const_iterator it_rx = std::find_if(the_regs.begin(), the_regs.end(), ::regex_matcher(mr, str));

  const bool b_match = (it_rx != the_regs.end());

  (b_match ? std::cout << "Match OK: index = " << std::distance(the_regs.begin(), it_rx) << std::endl
           : std::cout << "Match failed!" << std::endl);

  for(std::match_results<std::string::const_iterator>::const_iterator it_mr = mr.begin(); it_mr != mr.end(); ++it_mr)
  {
    std::cout << "mr-index: " + lexical_cast(std::distance(mr.begin(), it_mr)) << ", " << *it_mr << std::endl;
  }

  std::cout << std::endl;

  return b_match;
}

int main(void)
{
  std::string str;

  for(;;)
  {
    std::cout << "Enter FP string: ";
    std::cin >> str;

    if(str == "exit") { break; }

    static_cast<void>(rd_string(str));
  }
}
*/
