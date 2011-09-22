
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cstdarg>

#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/multiprecision/mp_float_functions.hpp>
#include <boost/multiprecision/utility/util_numeric_cast.hpp>
#include "mp_float_mpfr_protos.h"

using boost::multiprecision::mp_float_mpfr;

namespace
{
  const double& d_log2(void)
  {
    static const double value_log2 = 0.3010299956639811952137389;
    return value_log2;
  }
}

void mp_float_mpfr::init(void)
{
  static bool precision_is_initialized;

  if(precision_is_initialized == false)
  {
    precision_is_initialized = true;
    ::mpfr_set_default_prec(static_cast<mp_prec_t>(mp_float_digits2 + static_cast<boost::int32_t>(4)));
  }
}

mp_float_mpfr::mp_float_mpfr() { init(); ::mpfr_init(rop); }

mp_float_mpfr::mp_float_mpfr(const char n)    { init(); const bool b_neg = (std::numeric_limits<char>::is_signed    ? (n < static_cast<char>   (0)) : false); from_unsigned_long((!b_neg) ? static_cast<unsigned long>(n) : static_cast<unsigned long>(-n)); if(b_neg) { ::mpfr_neg(rop, rop, GMP_RNDN); } }
mp_float_mpfr::mp_float_mpfr(const wchar_t n) { init(); const bool b_neg = (std::numeric_limits<wchar_t>::is_signed ? (n < static_cast<wchar_t>(0)) : false); from_unsigned_long((!b_neg) ? static_cast<unsigned long>(n) : static_cast<unsigned long>(-n)); if(b_neg) { ::mpfr_neg(rop, rop, GMP_RNDN); } }

mp_float_mpfr::mp_float_mpfr(const signed char n)      { init(); const bool b_neg = (n < static_cast<signed char>(0));      from_unsigned_long     ((!b_neg) ? static_cast<unsigned long>     (n) : static_cast<unsigned long>     (-n)); if(b_neg) { ::mpfr_neg(rop, rop, GMP_RNDN); } }
mp_float_mpfr::mp_float_mpfr(const signed short n)     { init(); const bool b_neg = (n < static_cast<signed short>(0));     from_unsigned_long     ((!b_neg) ? static_cast<unsigned long>     (n) : static_cast<unsigned long>     (-n)); if(b_neg) { ::mpfr_neg(rop, rop, GMP_RNDN); } }
mp_float_mpfr::mp_float_mpfr(const signed int n)       { init(); const bool b_neg = (n < static_cast<signed int>(0));       from_unsigned_long     ((!b_neg) ? static_cast<unsigned long>     (n) : static_cast<unsigned long>     (-n)); if(b_neg) { ::mpfr_neg(rop, rop, GMP_RNDN); } }
mp_float_mpfr::mp_float_mpfr(const signed long n)      { init(); const bool b_neg = (n < static_cast<signed long>(0));      from_unsigned_long     ((!b_neg) ? static_cast<unsigned long>     (n) : static_cast<unsigned long>     (-n)); if(b_neg) { ::mpfr_neg(rop, rop, GMP_RNDN); } }
mp_float_mpfr::mp_float_mpfr(const signed long long n) { init(); const bool b_neg = (n < static_cast<signed long long>(0)); from_unsigned_long_long((!b_neg) ? static_cast<unsigned long long>(n) : static_cast<unsigned long long>(-n)); if(b_neg) { ::mpfr_neg(rop, rop, GMP_RNDN); } }

mp_float_mpfr::mp_float_mpfr(const unsigned char n)      {  init(); from_unsigned_long     (static_cast<unsigned long>     (n)); }
mp_float_mpfr::mp_float_mpfr(const unsigned short n)     {  init(); from_unsigned_long     (static_cast<unsigned long>     (n)); }
mp_float_mpfr::mp_float_mpfr(const unsigned int n)       {  init(); from_unsigned_long     (static_cast<unsigned long>     (n)); }
mp_float_mpfr::mp_float_mpfr(const unsigned long n)      {  init(); from_unsigned_long     (static_cast<unsigned long>     (n)); }
mp_float_mpfr::mp_float_mpfr(const unsigned long long n) {  init(); from_unsigned_long_long(static_cast<unsigned long long>(n)); }

mp_float_mpfr::mp_float_mpfr(const float f)
{
  init();

  const bool b_neg = (f < 0.0f);

  if(!boost::multiprecision::isfinite(static_cast<double>(f)))
  {
    (boost::multiprecision::isnan(static_cast<double>(f)) ? mpfr_set_nan(rop) : ((!b_neg) ? ::mpfr_set_inf(rop, 1) : ::mpfr_set_inf(rop, -1)));
    return;
  }

  if(f == 0.0f)
  {
    mpfr_init_set_ui(rop, 0uL, GMP_RNDN);
    return;
  }

  const built_in_float_parts<float> fb((!b_neg) ? f : -f);

  // Create an mp_float_mpfr from the fractional part of the
  // mantissa expressed as an unsigned long long.
  from_unsigned_long_long(fb.get_mantissa());

  // Scale the unsigned long long representation to the fractional
  // part of the float and multiply with the base-2 exponent.
  const int p2 = fb.get_exponent() - (std::numeric_limits<float>::digits - 1);

  if(p2 != 0) { mpfr_mul_2si(rop, rop, static_cast<signed long>(p2), GMP_RNDN); }

  if(b_neg)
  {
    ::mpfr_neg(rop, rop, GMP_RNDN);
  }
}

mp_float_mpfr::mp_float_mpfr(const double d)       { init(); mpfr_init_set_d(rop, d, GMP_RNDN); }
mp_float_mpfr::mp_float_mpfr(const long double ld) { init(); mpfr_init_set_ld(rop, ld, GMP_RNDN); }
mp_float_mpfr::mp_float_mpfr(const mp_float_mpfr& f)     { init(); mpfr_init_set(rop, f.rop, GMP_RNDN); }

mp_float_mpfr::mp_float_mpfr(const char* s)          { init(); static_cast<void>(rd_string(s)); }
mp_float_mpfr::mp_float_mpfr(const std::string& str) { init(); static_cast<void>(rd_string(str.c_str())); }

mp_float_mpfr::mp_float_mpfr(const double mantissa, const boost::int64_t exponent)
{
  init();

  const bool mantissa_is_iszero = (::fabs(mantissa) < ((std::numeric_limits<double>::min)() * 2.0));

  if(mantissa_is_iszero)
  {
    if(exponent == static_cast<boost::int64_t>(0))
    {
      mpfr_init_set(rop, (boost::multiprecision::one()).rop, GMP_RNDN);
    }
    else
    {
      mpfr_init_set(rop, (boost::multiprecision::zero()).rop, GMP_RNDN);
    }
  }
  else
  {
    mpfr_init_set(rop, (boost::multiprecision::zero()).rop, GMP_RNDN);
    operator=(mp_float_mpfr(mantissa));
    operator*=(mp_float_mpfr("1E" + boost::lexical_cast<std::string>(exponent)));
  }
}

mp_float_mpfr::~mp_float_mpfr()
{
  ::mpfr_clear(rop);
}

void mp_float_mpfr::from_unsigned_long_long(const unsigned long long u)
{
  if(u <= static_cast<unsigned long long>((std::numeric_limits<unsigned long>::max)()))
  {
    from_unsigned_long(static_cast<unsigned long>(u));
  }
  else
  {
    static_cast<void>(::mpfr_init_set_str(rop, boost::lexical_cast<std::string>(u).c_str(), 10, GMP_RNDN));
  }
}

void mp_float_mpfr::from_unsigned_long(const unsigned long u)
{
  mpfr_init_set_ui(rop, u, GMP_RNDN);
}

const mp_float_mpfr& mp_float_mpfr::my_value_nan(void) const
{
  static const mp_float_mpfr val;
  return val;
}

const mp_float_mpfr& mp_float_mpfr::my_value_inf(void) const
{
  static const mp_float_mpfr inf = boost::multiprecision::one() / boost::multiprecision::zero();
  return inf;
}

mp_float_mpfr& mp_float_mpfr::operator=(const mp_float_mpfr& v)
{
  static_cast<void>(::mpfr_set(rop, v.rop, GMP_RNDN));
  return *this;
}

mp_float_mpfr& mp_float_mpfr::operator+=(const mp_float_mpfr& v)
{
  static_cast<void>(::mpfr_add(rop, rop, v.rop, GMP_RNDN));
  return *this;
}

mp_float_mpfr& mp_float_mpfr::operator-=(const mp_float_mpfr& v)
{
  static_cast<void>(::mpfr_sub(rop, rop, v.rop, GMP_RNDN));
  return *this;
}

mp_float_mpfr& mp_float_mpfr::operator*=(const mp_float_mpfr& v)
{
  static_cast<void>(::mpfr_mul(rop, rop, v.rop, GMP_RNDN));
  return *this;
}

mp_float_mpfr& mp_float_mpfr::operator/=(const mp_float_mpfr& v)
{
  static_cast<void>(::mpfr_div(rop, rop, v.rop, GMP_RNDN));
  return *this;
}

mp_float_mpfr& mp_float_mpfr::add_unsigned_long_long(const unsigned long long n)
{
  if(n > static_cast<unsigned long long>((std::numeric_limits<unsigned long>::max)()))
  {
    operator+=(mp_float_mpfr(n));
  }
  else
  {
    static_cast<void>(::mpfr_add_ui(rop, rop, static_cast<unsigned long>(n), GMP_RNDN));
  }

  return *this;
}

mp_float_mpfr& mp_float_mpfr::sub_unsigned_long_long(const unsigned long long n)
{
  if(n > static_cast<unsigned long long>((std::numeric_limits<unsigned long>::max)()))
  {
    operator-=(mp_float_mpfr(n));
  }
  else
  {
    static_cast<void>(::mpfr_sub_ui(rop, rop, static_cast<unsigned long>(n), GMP_RNDN));
  }

  return *this;
}

mp_float_mpfr& mp_float_mpfr::mul_unsigned_long_long(const unsigned long long n)
{
  if(n > static_cast<unsigned long long>((std::numeric_limits<unsigned long>::max)()))
  {
    operator*=(mp_float_mpfr(n));
  }
  else
  {
    static_cast<void>(::mpfr_mul_ui(rop, rop, static_cast<unsigned long>(n), GMP_RNDN));
  }

  return *this;
}

mp_float_mpfr& mp_float_mpfr::div_unsigned_long_long(const unsigned long long n)
{
  if(n > static_cast<unsigned long long>((std::numeric_limits<unsigned long>::max)()))
  {
    operator/=(mp_float_mpfr(n));
  }
  else
  {
    static_cast<void>(::mpfr_div_ui(rop, rop, static_cast<unsigned long>(n), GMP_RNDN));
  }

  return *this;
}

mp_float_mpfr& mp_float_mpfr::negate(void)
{
  ::mpfr_neg(rop, rop, GMP_RNDN);
  return *this;
}

boost::int32_t mp_float_mpfr::cmp(const mp_float_mpfr& v) const
{
  // Handle all non-finite cases.
  if((!isfinite()) || (!v.isfinite()))
  {
    // NaN can never equal NaN. Return an implementation-dependent
    // signed result. Also note that comparison of NaN with NaN
    // using operators greater-than or less-than is undefined.
    if(isnan() || v.isnan()) { return (isnan() ? static_cast<boost::int32_t>(1) : static_cast<boost::int32_t>(-1)); }

    if(isinf() && v.isinf())
    {
      // Both *this and v are infinite. They are equal if they have the same sign.
      // Otherwise, *this is less than v if and only if *this is negative.
      return ((isneg() == v.isneg()) ? static_cast<boost::int32_t>(0) : (isneg() ? static_cast<boost::int32_t>(-1) : static_cast<boost::int32_t>(1)));
    }

    if(isinf())
    {
      // *this is infinite, but v is finite.
      // So negative infinite *this is less than any finite v.
      // Whereas positive infinite *this is greater than any finite v.
      return (isneg() ? static_cast<boost::int32_t>(-1) : static_cast<boost::int32_t>(1));
    }
    else
    {
      // *this is finite, and v is infinite.
      // So any finite *this is greater than negative infinite v.
      // Whereas any finite *this is less than positive infinite v.
      return (v.isneg() ? static_cast<boost::int32_t>(1) : static_cast<boost::int32_t>(-1));
    }
  }

  // And now handle all *finite* cases.
  if(iszero() && v.iszero())
  {
    return static_cast<boost::int32_t>(0);
  }
  else
  {
    return static_cast<boost::int32_t>(::mpfr_cmp(rop, v.rop));
  }
}

mp_float_mpfr& mp_float_mpfr::calculate_sqrt(void)
{
  static_cast<void>(::mpfr_sqrt(rop, rop, GMP_RNDN));
  return *this;
}

mp_float_mpfr& mp_float_mpfr::calculate_inv(void)
{
  static_cast<void>(::mpfr_div(rop, boost::multiprecision::one().rop, rop, GMP_RNDN));
  return *this;
}

bool mp_float_mpfr::isnan   (void) const { return  (::mpfr_nan_p    (rop)  != 0); }
bool mp_float_mpfr::isinf   (void) const { return  (::mpfr_inf_p    (rop)  != 0); }
bool mp_float_mpfr::isfinite(void) const { return  ((!isnan()) && (!isinf())); }
bool mp_float_mpfr::isone   (void) const { return ((::mpfr_integer_p(rop)  != 0) && (::mpfr_get_si(rop, GMP_RNDN) == static_cast<unsigned long>(1uL))); }
bool mp_float_mpfr::isint   (void) const { return  (::mpfr_integer_p(rop)  != 0); }
bool mp_float_mpfr::isneg   (void) const { return  (::mpfr_sgn      (rop)  <  0); }

bool mp_float_mpfr::iszero(void) const
{
  return (::mpfr_zero_p(rop) != 0);
}

mp_float_mpfr& mp_float_mpfr::operator++(void) { ::mpfr_add_ui(rop, rop, static_cast<unsigned long>(1uL), GMP_RNDN); return *this; }
mp_float_mpfr& mp_float_mpfr::operator--(void) { ::mpfr_sub_ui(rop, rop, static_cast<unsigned long>(1uL), GMP_RNDN); return *this; }

void mp_float_mpfr::extract_parts(double& mantissa, boost::int64_t& exponent) const
{
  const bool b_neg = isneg();

  long n2;
  const double d2    = ::mpfr_get_d_2exp(&n2, (boost::multiprecision::fabs(*this)).rop, GMP_RNDN);
  const double x_exp = static_cast<double>(static_cast<double>(n2) * ::d_log2());

  const double  x_exp_integer_part = static_cast<double>(static_cast<long>(x_exp));
  const double  x_exp_decimal_part = static_cast<double>(x_exp - x_exp_integer_part);

  double m = d2 * ::pow(10.0, x_exp_decimal_part);
  boost::int64_t  e = static_cast<boost::int64_t>(x_exp_integer_part);

  if(m < 1.0)
  {
    m *= 10.0;
    e -= static_cast<boost::int64_t>(1);
  }

  mantissa = ((!b_neg) ? m : -m);
  exponent = e;
}

double mp_float_mpfr::extract_double(void) const
{
  const bool b_neg = isneg();

  // Check for non-normal mp_float_mpfr.
  if(!isfinite())
  {
    if(isnan())
    {
      return std::numeric_limits<double>::quiet_NaN();
    }
    else
    {
      return ((!b_neg) ?  std::numeric_limits<double>::infinity()
                       : -std::numeric_limits<double>::infinity());
    }
  }

  const mp_float_mpfr xx(boost::multiprecision::fabs(*this));

  // Check for zero mp_float_mpfr.
  if(iszero() || (xx < boost::multiprecision::double_min()))
  {
    return 0.0;
  }

  // Check if mp_float_mpfr exceeds the maximum of double.
  if(xx > boost::multiprecision::double_max())
  {
    return ((!b_neg) ?  std::numeric_limits<double>::infinity()
                     : -std::numeric_limits<double>::infinity());
  }

  const double dx = ::mpfr_get_d(xx.rop, GMP_RNDN);

  return ((!b_neg) ? dx : -dx);
}

long double mp_float_mpfr::extract_long_double(void) const
{
  const bool b_neg = isneg();

  // Check for non-normal mp_float_mpfr.
  if(!isfinite())
  {
    if(isnan())
    {
      return std::numeric_limits<long double>::quiet_NaN();
    }
    else
    {
      return ((!b_neg) ?  std::numeric_limits<long double>::infinity()
                       : -std::numeric_limits<long double>::infinity());
    }
  }

  const mp_float_mpfr xx(boost::multiprecision::fabs(*this));

  // Check for zero mp_float_mpfr.
  if(iszero() || (xx < boost::multiprecision::long_double_min()))
  {
    return static_cast<long double>(0.0);
  }

  // Check if mp_float_mpfr exceeds the maximum of double.
  if(xx > boost::multiprecision::long_double_max())
  {
    return ((!b_neg) ?  std::numeric_limits<long double>::infinity()
                     : -std::numeric_limits<long double>::infinity());
  }

  const long double ldx = ::mpfr_get_ld(xx.rop, GMP_RNDN);

  return ((!b_neg) ? ldx : -ldx);
}

signed long long mp_float_mpfr::extract_signed_long_long(void) const
{
  const bool b_neg = isneg();

  const mp_float_mpfr nx = boost::multiprecision::fabs(*this);

  if(nx > boost::multiprecision::signed_long_long_max())
  {
    return ((!b_neg) ?  (std::numeric_limits<signed long long>::max)()
                     : -(std::numeric_limits<signed long long>::max)());
  }
  
  if(nx < boost::multiprecision::one())
  {
    return static_cast<signed long long>(0);
  }

  if(nx.isone())
  {
    return ((!b_neg) ? static_cast<signed long long>(1) : static_cast<signed long long>(-1));
  }

  boost::array<char, 64u> str = {{ static_cast<char>('0') }};

  mp_exp_t p10;

  static_cast<void>(::mpfr_get_str(str.data(), &p10, 10, str.size() - 1u, nx.rop, GMP_RNDN));

  std::string str_sll(static_cast<std::size_t>(p10), static_cast<char>('0'));

  std::copy(str.begin(), str.begin() + str_sll.size(), str_sll.begin());

  const signed long long n = boost::multiprecision::utility::numeric_cast<signed long long>(str_sll);

  return ((!b_neg) ? n : -n);
}

unsigned long long mp_float_mpfr::extract_unsigned_long_long(void) const
{
  if(isneg())
  {
    return static_cast<unsigned long long>(extract_signed_long_long());
  }

  if(*this > boost::multiprecision::unsigned_long_long_max())
  {
    return (std::numeric_limits<unsigned long long>::max)();
  }

  if(*this < boost::multiprecision::one())
  {
    return static_cast<unsigned long long>(0u);
  }

  if(isone())
  {
    return static_cast<unsigned long long>(1u);
  }

  boost::array<char, 64u> str = {{ static_cast<char>('0') }};

  mp_exp_t p10;

  static_cast<void>(::mpfr_get_str(str.data(), &p10, 10, str.size() - 1u, rop, GMP_RNDN));

  std::string str_ull(static_cast<std::size_t>(p10), static_cast<char>('0'));

  std::copy(str.begin(), str.begin() + str_ull.size(), str_ull.begin());

  const unsigned long long n = boost::multiprecision::utility::numeric_cast<unsigned long long>(str_ull);

  return n;
}

mp_float_mpfr mp_float_mpfr::extract_integer_part(void) const
{
  const bool b_neg = isneg();

  mp_float_mpfr nx;

  ::mpfr_floor(nx.rop, (boost::multiprecision::fabs(*this)).rop, GMP_RNDN);

  return ((!b_neg) ? nx : -nx);
}

mp_float_mpfr mp_float_mpfr::extract_decimal_part(void) const
{
  const bool b_neg = isneg();

  const mp_float_mpfr xx = boost::multiprecision::fabs(*this);

  const mp_float_mpfr dx = xx - xx.extract_integer_part();

  return ((!b_neg) ? dx : -dx);
}

boost::int64_t mp_float_mpfr::get_order_exact(void) const
{
  // Get the order-10 of the mp_float_mpfr. This is done using a partial
  // string extraction with 10 decimal digits.

  // Create a format string for 10-digits and scientific notation.
  std::string str_fmt = std::string("%.10RNe");

  // Get the ten digits.
  boost::array<char, 64u> buf = {{ static_cast<char>(0) }};

  ::mpfr_sprintf(buf.data(), str_fmt.c_str(), rop);

  const std::string str = std::string(buf.data());

  // Extract the base-10 exponent.
  const std::size_t pos_letter_e = str.rfind(static_cast<char>('e'));

  const boost::int64_t my_exp = ((pos_letter_e != std::string::npos) ? boost::multiprecision::utility::numeric_cast<boost::int64_t>(static_cast<const char* const>(str.c_str() + (pos_letter_e + 1u)))
                                                            : static_cast<boost::int64_t>(0));

  return my_exp;
}

boost::int64_t mp_float_mpfr::get_order_fast(void) const
{
  const mp_float_mpfr xx = boost::multiprecision::fabs(*this);

  if(xx.iszero() || xx.isone())
  {
    return static_cast<boost::int64_t>(0);
  }
  else
  {
    signed long int n2;
    const double d2    = ::mpfr_get_d_2exp(&n2, xx.rop, GMP_RNDN);
    const double lg10x = static_cast<double>(::log10(d2) + (static_cast<double>(n2) * ::d_log2()));

    return ((lg10x < 0.0) ? static_cast<boost::int64_t>(lg10x - 0.5)
                          : static_cast<boost::int64_t>(lg10x + 0.5));
  }
}

void mp_float_mpfr::get_output_string(std::string& str, boost::int64_t&, const std::size_t number_of_digits) const
{
  // Create a format string such as "%+.99RNe" in order to extract 100 digits
  // in scientific notation with the lowercase and noshowpos flags.
  const std::size_t the_number_of_digits_scientific = static_cast<std::size_t>((std::max)(number_of_digits, static_cast<std::size_t>(1u)) - static_cast<std::size_t>(1u));

  const std::string str_fmt = std::string("%.") + (boost::lexical_cast<std::string>(the_number_of_digits_scientific) + "RNe");

  // Get the string representation of the mp_float_mpfr in scientific notation (lowercase, noshowpos).
  boost::array<char, static_cast<std::size_t>(mp_float_mpfr::mp_float_max_digits10 + 32)> buf = {{ static_cast<char>(0) }};

  ::mpfr_sprintf(buf.data(), str_fmt.c_str(), rop);

  str = std::string(buf.data());

  // Obtain the raw digits from the scientific notation string.

  // TBD: Well, this is a bit silly. First get the string in
  // scientific notation, then reduce it to raw digits.
  // Perhaps this can be improved.
  // Get the raw digits from a string in scientific notation (lowercase, showpos).

  // Erase the negative sign, if present.
  if(str.at(0u) == static_cast<char>('-'))
  {
    str.erase(str.begin(), str.begin() + 1u);
  }

  // Erase the exponent.
  const std::size_t pos_letter_e = str.rfind(static_cast<char>('e'));

  if(pos_letter_e != std::string::npos)
  {
    str.erase(str.begin() + pos_letter_e, str.end());
  }

  // Erase the decimal point.
  const std::size_t pos_decimal_point = str.rfind(static_cast<char>('.'));

  if(pos_decimal_point != std::string::npos)
  {
    str.erase(str.begin() + pos_decimal_point, str.begin() + (pos_decimal_point + 1u));
  }
}

bool mp_float_mpfr::rd_string(const char* const s) { return (::mpfr_init_set_str(rop, s, 10, GMP_RNDN) == 1); }

mp_float_mpfr mp_float_mpfr::my_cbrt         (const mp_float_mpfr& x) { mp_float_mpfr res; static_cast<void>(::mpfr_cbrt (res.rop, x.rop, GMP_RNDN)); return res; }
mp_float_mpfr mp_float_mpfr::my_rootn        (const mp_float_mpfr& x, const boost::uint32_t p) { mp_float_mpfr res; static_cast<void>(::mpfr_root (res.rop, x.rop, static_cast<unsigned long int>(p), GMP_RNDN)); return res; }
mp_float_mpfr mp_float_mpfr::my_exp          (const mp_float_mpfr& x) { mp_float_mpfr res; static_cast<void>(::mpfr_exp  (res.rop, x.rop, GMP_RNDN)); return res; }
mp_float_mpfr mp_float_mpfr::my_log          (const mp_float_mpfr& x) { mp_float_mpfr res; static_cast<void>(::mpfr_log  (res.rop, x.rop, GMP_RNDN)); return res; }
mp_float_mpfr mp_float_mpfr::my_sin          (const mp_float_mpfr& x) { mp_float_mpfr res; static_cast<void>(::mpfr_sin  (res.rop, x.rop, GMP_RNDN)); return res; }
mp_float_mpfr mp_float_mpfr::my_cos          (const mp_float_mpfr& x) { mp_float_mpfr res; static_cast<void>(::mpfr_cos  (res.rop, x.rop, GMP_RNDN)); return res; }
mp_float_mpfr mp_float_mpfr::my_tan          (const mp_float_mpfr& x) { mp_float_mpfr res; static_cast<void>(::mpfr_tan  (res.rop, x.rop, GMP_RNDN)); return res; }
mp_float_mpfr mp_float_mpfr::my_asin         (const mp_float_mpfr& x) { mp_float_mpfr res; static_cast<void>(::mpfr_asin (res.rop, x.rop, GMP_RNDN)); return res; }
mp_float_mpfr mp_float_mpfr::my_acos         (const mp_float_mpfr& x) { mp_float_mpfr res; static_cast<void>(::mpfr_acos (res.rop, x.rop, GMP_RNDN)); return res; }
mp_float_mpfr mp_float_mpfr::my_atan         (const mp_float_mpfr& x) { mp_float_mpfr res; static_cast<void>(::mpfr_atan (res.rop, x.rop, GMP_RNDN)); return res; }
mp_float_mpfr mp_float_mpfr::my_sinh         (const mp_float_mpfr& x) { mp_float_mpfr res; static_cast<void>(::mpfr_sinh (res.rop, x.rop, GMP_RNDN)); return res; }
mp_float_mpfr mp_float_mpfr::my_cosh         (const mp_float_mpfr& x) { mp_float_mpfr res; static_cast<void>(::mpfr_cosh (res.rop, x.rop, GMP_RNDN)); return res; }
mp_float_mpfr mp_float_mpfr::my_tanh         (const mp_float_mpfr& x) { mp_float_mpfr res; static_cast<void>(::mpfr_tanh (res.rop, x.rop, GMP_RNDN)); return res; }
mp_float_mpfr mp_float_mpfr::my_asinh        (const mp_float_mpfr& x) { mp_float_mpfr res; static_cast<void>(::mpfr_asinh(res.rop, x.rop, GMP_RNDN)); return res; }
mp_float_mpfr mp_float_mpfr::my_acosh        (const mp_float_mpfr& x) { mp_float_mpfr res; static_cast<void>(::mpfr_acosh(res.rop, x.rop, GMP_RNDN)); return res; }
mp_float_mpfr mp_float_mpfr::my_atanh        (const mp_float_mpfr& x) { mp_float_mpfr res; static_cast<void>(::mpfr_atanh(res.rop, x.rop, GMP_RNDN)); return res; }
mp_float_mpfr mp_float_mpfr::my_gamma        (const mp_float_mpfr& x) { mp_float_mpfr res; static_cast<void>(::mpfr_gamma(res.rop, x.rop, GMP_RNDN)); return res; }
mp_float_mpfr mp_float_mpfr::my_riemann_zeta (const mp_float_mpfr& x) { mp_float_mpfr res; static_cast<void>(::mpfr_zeta (res.rop, x.rop, GMP_RNDN)); return res; }
mp_float_mpfr mp_float_mpfr::my_cyl_bessel_jn(const boost::int32_t n, const mp_float_mpfr& x) { mp_float_mpfr res; static_cast<void>(::mpfr_jn(res.rop, static_cast<long>(n), x.rop, GMP_RNDN)); return res; }
mp_float_mpfr mp_float_mpfr::my_cyl_bessel_yn(const boost::int32_t n, const mp_float_mpfr& x) { mp_float_mpfr res; static_cast<void>(::mpfr_yn(res.rop, static_cast<long>(n), x.rop, GMP_RNDN)); return res; }
