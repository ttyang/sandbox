
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

#include <e_float/e_float.hpp>
#include <e_float/e_float_constants.hpp>

#include "e_float_mpfr_protos.h"
#include "../../utility/util_lexical_cast.h"

namespace
{
  const double& d_log2(void)
  {
    static const double value_log2 = 0.3010299956639811952137389;
    return value_log2;
  }
}

void mpfr::e_float::init(void)
{
  static bool precision_is_initialized = false;

  if(!precision_is_initialized)
  {
    precision_is_initialized = true;

    ::mpfr_set_default_prec(static_cast<mp_prec_t>(ef_digits2));
  }
}

mpfr::e_float::e_float()
{
  init();
  ::mpfr_init(rop);
}

mpfr::e_float::e_float(const char n)
{
  const bool b_neg = (std::numeric_limits<char>::is_signed && (n < static_cast<char>(0)));
  from_unsigned_long((!b_neg) ? static_cast<unsigned long>(n) : static_cast<unsigned long>(-n));
  if(b_neg) { ::mpfr_neg(rop, rop, GMP_RNDN); }
}

mpfr::e_float::e_float(const signed char n)
{
  const bool b_neg = (n < static_cast<signed char>(0));
  from_unsigned_long((!b_neg) ? static_cast<unsigned long>(n) : static_cast<unsigned long>(-n));
  if(b_neg) { ::mpfr_neg(rop, rop, GMP_RNDN); }
}

mpfr::e_float::e_float(const signed short n)
{
  const bool b_neg = (n < static_cast<signed short>(0));
  from_unsigned_long((!b_neg) ? static_cast<unsigned long>(n) : static_cast<unsigned long>(-n));
  if(b_neg) { ::mpfr_neg(rop, rop, GMP_RNDN); }
}

mpfr::e_float::e_float(const signed int n)
{
  const bool b_neg = (n < static_cast<signed int>(0));
  from_unsigned_long((!b_neg) ? static_cast<unsigned long>(n) : static_cast<unsigned long>(-n));
  if(b_neg) { ::mpfr_neg(rop, rop, GMP_RNDN); }
}

mpfr::e_float::e_float(const signed long n)
{
  const bool b_neg = (n < static_cast<signed long>(0));
  from_unsigned_long((!b_neg) ? static_cast<unsigned long>(n) : static_cast<unsigned long>(-n));
  if(b_neg) { ::mpfr_neg(rop, rop, GMP_RNDN); }
}

mpfr::e_float::e_float(const signed long long n)
{
  const bool b_neg = (n < static_cast<signed long long>(0));
  from_unsigned_long_long((!b_neg) ? static_cast<unsigned long long>(n) : static_cast<unsigned long long>(-n));
  if(b_neg) { ::mpfr_neg(rop, rop, GMP_RNDN); }
}

mpfr::e_float::e_float(const unsigned char n)      { from_unsigned_long(static_cast<unsigned long>(n)); }
mpfr::e_float::e_float(const wchar_t n)            { from_unsigned_long(static_cast<unsigned long>(n)); }
mpfr::e_float::e_float(const unsigned short n)     { from_unsigned_long(static_cast<unsigned long>(n)); }
mpfr::e_float::e_float(const unsigned int n)       { from_unsigned_long(static_cast<unsigned long>(n)); }
mpfr::e_float::e_float(const unsigned long n)      { from_unsigned_long(static_cast<unsigned long>(n)); }
mpfr::e_float::e_float(const unsigned long long n) { from_unsigned_long_long(static_cast<unsigned long long>(n)); }

mpfr::e_float::e_float(const float f)
{
  init();
  mpfr_init_set_d(rop, static_cast<double>(f), GMP_RNDN);
}

mpfr::e_float::e_float(const double d)
{
  init();
  mpfr_init_set_d(rop, d, GMP_RNDN);
}

mpfr::e_float::e_float(const long double ld)
{
  init();
  mpfr_init_set_ld(rop, ld, GMP_RNDN);
}

mpfr::e_float::e_float(const e_float& f)
{
  init();
  mpfr_init_set(rop, f.rop, GMP_RNDN);
}

mpfr::e_float::e_float(const char* s)
{
  static_cast<void>(rd_string(s));
}

mpfr::e_float::e_float(const std::string& str)
{
  static_cast<void>(rd_string(str.c_str()));
}

mpfr::e_float::e_float(const double mantissa, const INT64 exponent)
{
  init();

  const bool mantissa_is_iszero = (::fabs(mantissa) < ((std::numeric_limits<double>::min)() * 2.0));

  if(mantissa_is_iszero)
  {
    if(exponent == static_cast<INT64>(0))
    {
      mpfr_init_set(rop, (ef::one()).rop, GMP_RNDN);
    }
    else
    {
      mpfr_init_set(rop, (ef::zero()).rop, GMP_RNDN);
    }
  }
  else
  {
    mpfr_init_set(rop, (ef::zero()).rop, GMP_RNDN);
    operator=(e_float(mantissa));
    operator*=(e_float("1E" + Util::lexical_cast(exponent)));
  }
}

mpfr::e_float::~e_float()
{
  ::mpfr_clear(rop);
}

void mpfr::e_float::from_unsigned_long_long(const unsigned long long u)
{
  init();
  static_cast<void>(::mpfr_init_set_str(rop, Util::lexical_cast(u).c_str(), 10, GMP_RNDN));
}

void mpfr::e_float::from_unsigned_long(const unsigned long u)
{
  init();
  mpfr_init_set_ui(rop, u, GMP_RNDN);
}

const mpfr::e_float& mpfr::e_float::my_value_nan(void) const
{
  static const e_float val;
  return val;
}

const mpfr::e_float& mpfr::e_float::my_value_inf(void) const
{
  static const e_float inf = ef::one() / ef::zero();
  return inf;
}

const mpfr::e_float& mpfr::e_float::my_value_max(void) const
{
  static const INT64 exp10_max = std::numeric_limits<e_float>::max_exponent10;

  static const e_float val("1E" + Util::lexical_cast(exp10_max));

  return val;
}

const mpfr::e_float& mpfr::e_float::my_value_min(void) const
{
  static const INT64 exp10_min = std::numeric_limits<e_float>::min_exponent10;

  static const e_float val("1E" + Util::lexical_cast(exp10_min));

  return val;
}

mpfr::e_float& mpfr::e_float::operator=(const e_float& v)
{
  static_cast<void>(::mpfr_set(rop, v.rop, GMP_RNDN));
  return *this;
}

mpfr::e_float& mpfr::e_float::operator+=(const e_float& v)
{
  static_cast<void>(::mpfr_add(rop, rop, v.rop, GMP_RNDN));
  return *this;
}

mpfr::e_float& mpfr::e_float::operator-=(const e_float& v)
{
  static_cast<void>(::mpfr_sub(rop, rop, v.rop, GMP_RNDN));
  return *this;
}

mpfr::e_float& mpfr::e_float::operator*=(const e_float& v)
{
  static_cast<void>(::mpfr_mul(rop, rop, v.rop, GMP_RNDN));
  return *this;
}

mpfr::e_float& mpfr::e_float::operator/=(const e_float& v)
{
  static_cast<void>(::mpfr_div(rop, rop, v.rop, GMP_RNDN));
  return *this;
}

mpfr::e_float& mpfr::e_float::add_unsigned_long_long(const unsigned long long n)
{
  if(n > static_cast<unsigned long long>(std::numeric_limits<unsigned long>::max()))
  {
    operator+=(e_float(n));
  }
  else
  {
    static_cast<void>(::mpfr_add_ui(rop, rop, static_cast<unsigned long>(n), GMP_RNDN));
  }

  return *this;
}

mpfr::e_float& mpfr::e_float::sub_unsigned_long_long(const unsigned long long n)
{
  if(n > static_cast<unsigned long long>(std::numeric_limits<unsigned long>::max()))
  {
    operator-=(e_float(n));
  }
  else
  {
    static_cast<void>(::mpfr_sub_ui(rop, rop, static_cast<unsigned long>(n), GMP_RNDN));
  }

  return *this;
}

mpfr::e_float& mpfr::e_float::mul_unsigned_long_long(const unsigned long long n)
{
  if(n > static_cast<unsigned long long>(std::numeric_limits<unsigned long>::max()))
  {
    operator*=(e_float(n));
  }
  else
  {
    static_cast<void>(::mpfr_mul_ui(rop, rop, static_cast<unsigned long>(n), GMP_RNDN));
  }

  return *this;
}

mpfr::e_float& mpfr::e_float::div_unsigned_long_long(const unsigned long long n)
{
  if(n > static_cast<unsigned long long>(std::numeric_limits<unsigned long>::max()))
  {
    operator/=(e_float(n));
  }
  else
  {
    static_cast<void>(::mpfr_div_ui(rop, rop, static_cast<unsigned long>(n), GMP_RNDN));
  }

  return *this;
}

e_float& mpfr::e_float::negate(void)
{
  ::mpfr_neg(rop, rop, GMP_RNDN);
  return *this;
}

INT32 mpfr::e_float::cmp(const e_float& v) const
{
  return static_cast<INT32>(::mpfr_cmp(rop, v.rop));
}

mpfr::e_float& mpfr::e_float::calculate_sqrt(void)
{
  static_cast<void>(::mpfr_sqrt(rop, rop, GMP_RNDN));
  return *this;
}

mpfr::e_float& mpfr::e_float::calculate_inv(void)
{
  static_cast<void>(::mpfr_div(rop, ef::one().rop, rop, GMP_RNDN));
  return *this;
}

bool mpfr::e_float::isnan   (void) const { return  (::mpfr_nan_p    (rop)  != 0); }
bool mpfr::e_float::isinf   (void) const { return  (::mpfr_inf_p    (rop)  != 0); }
bool mpfr::e_float::isfinite(void) const { return  ((!isnan()) && (!isinf())); }
bool mpfr::e_float::iszero  (void) const { return  (::mpfr_zero_p   (rop)  != 0); }
bool mpfr::e_float::isone   (void) const { return ((::mpfr_integer_p(rop)  != 0) && (::mpfr_get_si(rop, GMP_RNDN) == static_cast<unsigned long>(1uL))); }
bool mpfr::e_float::isint   (void) const { return  (::mpfr_integer_p(rop)  != 0); }
bool mpfr::e_float::isneg   (void) const { return  (::mpfr_sgn      (rop)  <  0); }

mpfr::e_float& mpfr::e_float::operator++(void) { ::mpfr_add_ui(rop, rop, static_cast<unsigned long>(1uL), GMP_RNDN); return *this; }
mpfr::e_float& mpfr::e_float::operator--(void) { ::mpfr_sub_ui(rop, rop, static_cast<unsigned long>(1uL), GMP_RNDN); return *this; }

void mpfr::e_float::extract_parts(double& mantissa, INT64& exponent) const
{
  const bool b_neg = isneg();

  long n2;
  const double d2    = ::mpfr_get_d_2exp(&n2, (ef::fabs(*this)).rop, GMP_RNDN);
  const double x_exp = static_cast<double>(static_cast<double>(n2) * ::d_log2());

  const double  x_exp_integer_part = static_cast<double>(static_cast<long>(x_exp));
  const double  x_exp_decimal_part = static_cast<double>(x_exp - x_exp_integer_part);

  double m = d2 * ::pow(10.0, x_exp_decimal_part);
  INT64  e = static_cast<INT64>(x_exp_integer_part);

  if(m < 1.0)
  {
    m *= 10.0;
    e -= static_cast<INT64>(1);
  }

  mantissa = ((!b_neg) ? m : -m);
  exponent = e;
}

double mpfr::e_float::extract_double(void) const
{
  const bool b_neg = isneg();

  const e_float xx = ef::fabs(*this);

  static const e_float dbl_max((std::numeric_limits<double>::max)());
  static const e_float dbl_min((std::numeric_limits<double>::min)());

  if(xx > dbl_max)
  {
    return ((!b_neg) ?  (std::numeric_limits<double>::max)()
                     : -(std::numeric_limits<double>::max)());
  }
  else if(xx < dbl_min)
  {
    return ((!b_neg) ?  (std::numeric_limits<double>::min)()
                     : -(std::numeric_limits<double>::min)());
  }

  const double dx = ::mpfr_get_d(xx.rop, GMP_RNDN);

  return ((!b_neg) ? dx : -dx);
}

INT64 mpfr::e_float::extract_int64(void) const
{
  const bool b_neg = isneg();

  const e_float nx = ef::fabs(*this);

  static const e_float n64_max((std::numeric_limits<INT64>::max)());

  if(nx > n64_max)
  {
    return ((!b_neg) ?  (std::numeric_limits<INT64>::max)()
                     : -(std::numeric_limits<INT64>::max)());
  }
  
  if(nx < ef::one())
  {
    return static_cast<INT64>(0);
  }

  if(nx.isone())
  {
    return static_cast<INT64>(!b_neg ? static_cast<INT64>(1) : static_cast<INT64>(-1));
  }

  static const char c0 = static_cast<char>('\0');

  std::tr1::array<char, 32u> str = {{ c0 }};

  mp_exp_t p10;

  static_cast<void>(::mpfr_get_str(str.data(), &p10, 10, str.size() - 1u, nx.rop, GMP_RNDN));

  std::string str_n64(static_cast<std::size_t>(p10), static_cast<char>('0'));

  std::copy(str.begin(),
            str.begin() + str_n64.size(),
            str_n64.begin());

  std::stringstream ss;

  ss << str_n64;

  INT64 n;

  ss >> n;

  return ((!b_neg) ? n : -n);
}

mpfr::e_float mpfr::e_float::extract_integer_part(void) const
{
  const bool b_neg = isneg();

  e_float nx;

  ::mpfr_floor(nx.rop, (ef::fabs(*this)).rop, GMP_RNDN);

  return ((!b_neg) ? nx : -nx);
}

mpfr::e_float mpfr::e_float::extract_decimal_part(void) const
{
  const bool b_neg = isneg();

  const e_float xx = ef::fabs(*this);

  const e_float dx = xx - xx.extract_integer_part();

  return ((!b_neg) ? dx : -dx);
}

INT64 mpfr::e_float::order(void) const
{
  const e_float xx = ef::fabs(*this);

  if(xx.iszero() || xx.isone())
  {
    return static_cast<INT64>(0);
  }
  else
  {
    signed long int n2;
    const double d2    = ::mpfr_get_d_2exp(&n2, xx.rop, GMP_RNDN);
    const double lg10x = static_cast<double>(::log10(d2) + (static_cast<double>(n2) * ::d_log2()));

    return ((lg10x < 0.0) ? static_cast<INT64>(lg10x - 0.5)
                          : static_cast<INT64>(lg10x + 0.5));
  }
}

void mpfr::e_float::wr_string(std::string& str, std::ostream& os) const
{
  if(isnan())
  {
    str = "NaN";
    return;
  }

  if(isinf())
  {
    str = "INF";
    return;
  }

  static const std::streamsize p_min = static_cast<std::streamsize>(10);
  static const std::streamsize p_lim = static_cast<std::streamsize>(ef_digits10_tol);
         const std::streamsize p     = (std::max)(os.precision(), p_min);

  const std::streamsize my_precision = (std::min)(p, p_lim);

  const std::ios::fmtflags f = os.flags();

  const bool my_uppercase  = ((f & std::ios::uppercase)  != static_cast<std::ios::fmtflags>(0u));
  const bool my_showpos    = ((f & std::ios::showpos)    != static_cast<std::ios::fmtflags>(0u));
  const bool my_scientific = ((f & std::ios::scientific) != static_cast<std::ios::fmtflags>(0u));

  // Create a format string such as "%+.99RNe"
  const std::string str_sign(my_showpos ? "%+." : "%.");
  const std::string str_prec(Util::lexical_cast(my_precision - (my_scientific ? 1 : 0)));
  const std::string str_case(my_scientific ? (my_uppercase ? "RNE" : "RNe") : (my_uppercase ? "RNG" : "RNg"));

  const std::string str_fmt =  str_sign + (str_prec + str_case);

  std::tr1::array<char, static_cast<std::size_t>(e_float::ef_digits10_tol + 32)> buf = {{ static_cast<char>(0) }};

  ::mpfr_sprintf(buf.data(), str_fmt.c_str(), rop);

  str = std::string(buf.data());

  const std::size_t pos_E = (my_uppercase ? str.rfind('E') : str.rfind('e'));

  if(pos_E != std::string::npos)
  {
    // Pad the exponent number field with additional zeros such that the width
    // of the exponent number field is equal to the width of ef_max_exp10.
    const std::size_t pos_exp = static_cast<std::string::size_type>(pos_E + 2u);

    const std::string::size_type width_of_exp = str.length() - pos_exp;

    str.insert(pos_exp, std::string(width_of_exponent_field() - width_of_exp, static_cast<char>('0')));
  }
}

bool mpfr::e_float::rd_string(const char* const s)
{
  init();
  return (::mpfr_init_set_str(rop, s, 10, GMP_RNDN) == 1);
}

e_float mpfr::e_float::my_cbrt         (const e_float& x) { e_float res; static_cast<void>(::mpfr_cbrt (res.rop, x.rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_rootn        (const e_float& x, const UINT32 p) { e_float res; static_cast<void>(::mpfr_root (res.rop, x.rop, static_cast<unsigned long int>(p), GMP_RNDN)); return res; }
e_float mpfr::e_float::my_exp          (const e_float& x) { e_float res; static_cast<void>(::mpfr_exp  (res.rop, x.rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_log          (const e_float& x) { e_float res; static_cast<void>(::mpfr_log  (res.rop, x.rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_sin          (const e_float& x) { e_float res; static_cast<void>(::mpfr_sin  (res.rop, x.rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_cos          (const e_float& x) { e_float res; static_cast<void>(::mpfr_cos  (res.rop, x.rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_tan          (const e_float& x) { e_float res; static_cast<void>(::mpfr_tan  (res.rop, x.rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_asin         (const e_float& x) { e_float res; static_cast<void>(::mpfr_asin (res.rop, x.rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_acos         (const e_float& x) { e_float res; static_cast<void>(::mpfr_acos (res.rop, x.rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_atan         (const e_float& x) { e_float res; static_cast<void>(::mpfr_atan (res.rop, x.rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_sinh         (const e_float& x) { e_float res; static_cast<void>(::mpfr_sinh (res.rop, x.rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_cosh         (const e_float& x) { e_float res; static_cast<void>(::mpfr_cosh (res.rop, x.rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_tanh         (const e_float& x) { e_float res; static_cast<void>(::mpfr_tanh (res.rop, x.rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_asinh        (const e_float& x) { e_float res; static_cast<void>(::mpfr_asinh(res.rop, x.rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_acosh        (const e_float& x) { e_float res; static_cast<void>(::mpfr_acosh(res.rop, x.rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_atanh        (const e_float& x) { e_float res; static_cast<void>(::mpfr_atanh(res.rop, x.rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_gamma        (const e_float& x) { e_float res; static_cast<void>(::mpfr_gamma(res.rop, x.rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_riemann_zeta (const e_float& x) { e_float res; static_cast<void>(::mpfr_zeta (res.rop, x.rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_cyl_bessel_jn(const INT32 n, const e_float& x) { e_float res; static_cast<void>(::mpfr_jn(res.rop, static_cast<long>(n), x.rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_cyl_bessel_yn(const INT32 n, const e_float& x) { e_float res; static_cast<void>(::mpfr_yn(res.rop, static_cast<long>(n), x.rop, GMP_RNDN)); return res; }
