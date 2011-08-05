
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

// *****************************************************************************
// Filename    : e_float_efx.cpp
// 
// Project     : Multiple precision mathematics
// 
// Date        : 28.02.2004
// 
// Description : Extended precision floating point data type, efx::e_float.
// 
// *****************************************************************************

#include <iomanip>
#include <algorithm>
#include <numeric>
#include <cmath>

#include <e_float/e_float.hpp>
#include <e_float/e_float_constants.hpp>
#include <e_float/e_float_elementary.hpp>

#include "../../utility/util_lexical_cast.h"
#include "../../utility/util_numeric_cast.h"
#include "../../utility/util_noncopyable.h"

namespace
{
  typedef enum enum_os_float_field_type
  {
    os_float_field_scientific,
    os_float_field_fixed,
    os_float_field_none
  }
  os_float_filed_type;

  // Emphasize: This template class can be used with native floating-point
  // types like float, double and 10-byte long double. Note: It would need
  // to be extended for 16-byte long double because the mantissa would
  // no longer fit in UINT64.
  template<typename native_float_type>
  class native_float_parts : private Util::noncopyable
  {
  public:
    native_float_parts(const native_float_type f) : u(0uLL), e(0) { make_parts(f); }

    const unsigned long long& get_mantissa(void) const { return u; }
    const int& get_exponent(void) const { return e; }

  private:
    unsigned long long u;
    int e;

    native_float_parts();

    void make_parts(const native_float_type f)
    {
      // Get the fraction and base-2 exponent.
      native_float_type man = ::frexp(f, &e);

      // Express the fractional part as a UINT64.
      UINT32 n2 = 0u;

      for(UINT32 i = static_cast<UINT32>(0u); i < static_cast<UINT32>(std::numeric_limits<native_float_type>::digits); i++)
      {
        // Extract the mantissa of the floating-point type in base-2
        // (yes, one bit at a time) and store it in a UINT64.
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
}

efx::e_float::e_float(const char n) : data     (),
                                      exp      (static_cast<INT64>(0)),
                                      neg      (std::numeric_limits<char>::is_signed ? (n < static_cast<char>(0)) : false),
                                      fpclass  (ef_finite),
                                      prec_elem(ef_elem_number)
{
  (std::numeric_limits<char>::is_signed ? from_unsigned_long((!neg) ? static_cast<unsigned long>(n) : static_cast<unsigned long>(-n))
                                        : from_unsigned_long(static_cast<unsigned long>(n)));
}

efx::e_float::e_float(const signed char n) : data     (),
                                             exp      (static_cast<INT64>(0)),
                                             neg      (n < static_cast<INT32>(0)),
                                             fpclass  (ef_finite),
                                             prec_elem(ef_elem_number)
{
  from_unsigned_long((!neg) ? static_cast<unsigned long>(n) : static_cast<unsigned long>(-n));
}

efx::e_float::e_float(const unsigned char n) : data     (),
                                               exp      (static_cast<INT64>(0)),
                                               neg      (false),
                                               fpclass  (ef_finite),
                                               prec_elem(ef_elem_number)
{
  from_unsigned_long(static_cast<unsigned long>(n));
}

efx::e_float::e_float(const wchar_t n) : data     (),
                                         exp      (static_cast<INT64>(0)),
                                         neg      (std::numeric_limits<wchar_t>::is_signed ? (n < static_cast<wchar_t>(0)) : false),
                                         fpclass  (ef_finite),
                                         prec_elem(ef_elem_number)
{
  (std::numeric_limits<wchar_t>::is_signed ? from_unsigned_long((!neg) ? static_cast<unsigned long>(n) : static_cast<unsigned long>(-n))
                                           : from_unsigned_long(static_cast<unsigned long>(n)));
}

efx::e_float::e_float(const signed short n) : data     (),
                                              exp      (static_cast<INT64>(0)),
                                              neg      (n < static_cast<INT32>(0)),
                                              fpclass  (ef_finite),
                                              prec_elem(ef_elem_number)
{
  from_unsigned_long((!neg) ? static_cast<unsigned long>(n) : static_cast<unsigned long>(-n));
}

efx::e_float::e_float(const unsigned short n) : data     (),
                                                exp      (static_cast<INT64>(0)),
                                                neg      (false),
                                                fpclass  (ef_finite),
                                                prec_elem(ef_elem_number)
{
  from_unsigned_long(static_cast<unsigned long>(n));
}

efx::e_float::e_float(const signed int n) : data     (),
                                            exp      (static_cast<INT64>(0)),
                                            neg      (n < 0),
                                            fpclass  (ef_finite),
                                            prec_elem(ef_elem_number)
{
  from_unsigned_long((!neg) ? static_cast<unsigned long>(n) : static_cast<unsigned long>(-n));
}

efx::e_float::e_float(const unsigned int n) : data     (),
                                              exp      (static_cast<INT64>(0)),
                                              neg      (false),
                                              fpclass  (ef_finite),
                                              prec_elem(ef_elem_number)
{
  from_unsigned_long(n);
}

efx::e_float::e_float(const signed long n) : data     (),
                                             exp      (static_cast<INT64>(0)),
                                             neg      (n < static_cast<signed long>(0)),
                                             fpclass  (ef_finite),
                                             prec_elem(ef_elem_number)
{
  from_unsigned_long((!neg) ? static_cast<unsigned long>(n) : static_cast<unsigned long>(-n));
}

efx::e_float::e_float(const unsigned long n) : data     (),
                                               exp      (static_cast<INT64>(0)),
                                               neg      (false),
                                               fpclass  (ef_finite),
                                               prec_elem(ef_elem_number)
{
  from_unsigned_long(n);
}

efx::e_float::e_float(const signed long long n) : data     (),
                                                  exp      (static_cast<INT64>(0)),
                                                  neg      (n < static_cast<signed long long>(0)),
                                                  fpclass  (ef_finite),
                                                  prec_elem(ef_elem_number)
{
  from_unsigned_long_long((!neg) ? static_cast<unsigned long long>(n) : static_cast<UINT64>(-n));
}

efx::e_float::e_float(const unsigned long long n) : data     (),
                                                    exp      (static_cast<INT64>(0)),
                                                    neg      (false),
                                                    fpclass  (ef_finite),
                                                    prec_elem(ef_elem_number)
{
  from_unsigned_long_long(n);
}

efx::e_float::e_float(const float f) : data     (),
                                       exp      (static_cast<INT64>(0)),
                                       neg      (false),
                                       fpclass  (ef_finite),
                                       prec_elem(ef_elem_number)
{
  bool b_neg;

  {
    const double d = static_cast<double>(f);

    b_neg = ef::isneg(d);

    if(!ef::isfinite(d))
    {
      operator=(ef::isnan(d) ? my_value_nan() : ((!ef::isneg(d)) ? my_value_inf() : -my_value_inf()));
      return;
    }
  }

  const native_float_parts<float> fb((!b_neg) ? f : -f);

  // Create an e_float from the fractional part of the
  // mantissa expressed as an unsigned long long.
  from_unsigned_long_long(fb.get_mantissa());

  // Scale the UINT64 representation to the fractional part of
  // the double and multiply with the base-2 exponent.
  const int p2 = fb.get_exponent() - (std::numeric_limits<float>::digits - 1);

  if(p2 == 0) { }
  else if((p2 > 0) && (p2 < 27))
  {
    mul_unsigned_long_long(static_cast<unsigned long long>(1uL << p2));
  }
  else if((p2 < 0) && (p2 > -27))
  {
    div_unsigned_long_long(static_cast<unsigned long long>(1uL << -p2));
  }
  else
  {
    operator*=(ef::pow2(static_cast<INT64>(p2)));
  }

  neg = b_neg;
}

efx::e_float::e_float(const double d) : data     (),
                                        exp      (static_cast<INT64>(0)),
                                        neg      (false),
                                        fpclass  (ef_finite),
                                        prec_elem(ef_elem_number)
{
  // Create an e_float from a double. Yes, this ctor does
  // maintain the full precision of double.

  if(!ef::isfinite(d))
  {
    operator=(ef::isnan(d) ? my_value_nan() : ((!ef::isneg(d)) ? my_value_inf() : -my_value_inf()));
  }
  else
  {
    const bool b_neg = ef::isneg(d);

    const native_float_parts<double> db((!b_neg) ? d : -d);

    // Create an e_float from the fractional part of the
    // mantissa expressed as an unsigned long long.
    from_unsigned_long_long(db.get_mantissa());

    // Scale the UINT64 representation to the fractional part of
    // the double and multiply with the base-2 exponent.
    const int p2 = db.get_exponent() - (std::numeric_limits<double>::digits - 1);

    if(p2 == 0) { }
    else if((p2 > 0) && (p2 < 27))
    {
      mul_unsigned_long_long(static_cast<unsigned long long>(1uL << p2));
    }
    else if((p2 < 0) && (p2 > -27))
    {
      div_unsigned_long_long(static_cast<unsigned long long>(1uL << -p2));
    }
    else
    {
      operator*=(ef::pow2(static_cast<INT64>(p2)));
    }

    neg = b_neg;
  }
}

efx::e_float::e_float(const long double ld) : data     (),
                                              exp      (static_cast<INT64>(0)),
                                              neg      (false),
                                              fpclass  (ef_finite),
                                              prec_elem(ef_elem_number)
{
  bool b_neg;

  {
    const double d = static_cast<double>(ld);

    b_neg = ef::isneg(d);

    if(!ef::isfinite(d))
    {
      operator=(ef::isnan(d) ? my_value_nan() : ((!ef::isneg(d)) ? my_value_inf() : -my_value_inf()));
      return;
    }
  }

  const native_float_parts<long double> ldb((!b_neg) ? ld : -ld);

  // Create an e_float from the fractional part of the
  // mantissa expressed as an unsigned long long.
  from_unsigned_long_long(ldb.get_mantissa());

  // Scale the UINT64 representation to the fractional part of
  // the double and multiply with the base-2 exponent.
  const int p2 = ldb.get_exponent() - (std::numeric_limits<long double>::digits - 1);

  if(p2 == 0) { }
  else if((p2 > 0) && (p2 < 27))
  {
    mul_unsigned_long_long(static_cast<unsigned long long>(1uL << p2));
  }
  else if((p2 < 0) && (p2 > -27))
  {
    div_unsigned_long_long(static_cast<unsigned long long>(1uL << -p2));
  }
  else
  {
    operator*=(ef::pow2(static_cast<INT64>(p2)));
  }

  neg = b_neg;
}

efx::e_float::e_float(const char* const s) : data     (),
                                             exp      (static_cast<INT64>(0)),
                                             neg      (false),
                                             fpclass  (ef_finite),
                                             prec_elem(ef_elem_number)
{
  if(!rd_string(s))
  {
    std::fill(data.begin(), data.end(), static_cast<UINT32>(0u));
    exp     = static_cast<INT64>(0);
    neg     = false;
    fpclass = ef_NaN;
  }
}

efx::e_float::e_float(const std::string& str) : data     (),
                                                exp      (static_cast<INT64>(0)),
                                                neg      (false),
                                                fpclass  (ef_finite),
                                                prec_elem(ef_elem_number)
{
  if(!rd_string(str.c_str()))
  {
    std::fill(data.begin(), data.end(), static_cast<UINT32>(0u));
    exp     = static_cast<INT64>(0);
    neg     = false;
    fpclass = ef_NaN;
  }
}

efx::e_float::e_float(const double mantissa,
                      const INT64 exponent) : data     (),
                                              exp      (static_cast<INT64>(0)),
                                              neg      (false),
                                              fpclass  (ef_finite),
                                              prec_elem(ef_elem_number)
{
  // Create an e_float from mantissa and exponent. No, this ctor
  // does not maintain the full precision of double.

  const bool mantissa_is_iszero = (::fabs(mantissa) < ((std::numeric_limits<double>::min)() * 2.0));

  if(mantissa_is_iszero)
  {
    if(exponent == static_cast<INT64>(0))
    {
      operator=(ef::one());
    }
    else
    {
      operator=(ef::zero());
    }
  }
  else
  {
    const bool b_neg = (mantissa < 0.0);

    neg = b_neg;

    double d = ((!b_neg) ? mantissa : -mantissa);
    INT64  e = exponent;

    while(d > 1.0)
    {
      d /= 10.0;
      ++e;
    }

    while(d < 1.0)
    {
      d *= 10.0;
      --e;
    }

    INT32 shift = static_cast<INT32>(e % static_cast<INT32>(ef_elem_digits10));

    while(static_cast<INT32>(shift-- % ef_elem_digits10) != static_cast<INT32>(0))
    {
      d *= 10.0;
      --e;
    }

    exp = e;
    neg = b_neg;

    std::fill(data.begin(), data.end(), static_cast<UINT32>(0u));

    static const INT32 digit_ratio = static_cast<INT32>(static_cast<INT32>(std::numeric_limits<double>::digits10) / static_cast<INT32>(ef_elem_digits10));
    static const INT32 digit_loops = static_cast<INT32>(digit_ratio + static_cast<INT32>(2));

    for(INT32 i = static_cast<INT32>(0); i < digit_loops; i++)
    {
      UINT32 n = static_cast<UINT32>(static_cast<UINT64>(d));
      data[i]  = static_cast<UINT32>(n);
      d       -= static_cast<double>(n);
      d       *= static_cast<double>(ef_elem_mask);
    }
  }
}

void efx::e_float::from_unsigned_long(const unsigned long u)
{
  std::fill(data.begin(), data.end(), static_cast<UINT32>(0u));

  exp = static_cast<INT64>(0);

  std::size_t i = 0u;

  unsigned long uu = u;

  UINT32 temp[(std::numeric_limits<unsigned long>::digits10 / static_cast<int>(ef_elem_digits10)) + 3] = { static_cast<UINT32>(0u) };

  while(uu != static_cast<unsigned long>(0u))
  {
    temp[i] = static_cast<UINT32>(uu % static_cast<unsigned long>(ef_elem_mask));
    uu = static_cast<unsigned long>(uu / static_cast<unsigned long>(ef_elem_mask));
    ++i;
  }

  if(i > static_cast<std::size_t>(1u))
  {
    exp += static_cast<INT64>((i - 1u) * static_cast<std::size_t>(ef_elem_digits10));
  }

  std::reverse(temp, temp + i);
  std::copy(temp, temp + (std::min)(i, static_cast<std::size_t>(ef_elem_number)), data.begin());
}

void efx::e_float::from_unsigned_long_long(const unsigned long long u)
{
  std::fill(data.begin(), data.end(), static_cast<UINT32>(0u));

  exp = static_cast<INT64>(0);

  std::size_t i = 0u;

  unsigned long long uu = u;

  UINT32 temp[(std::numeric_limits<unsigned long long>::digits10 / static_cast<int>(ef_elem_digits10)) + 3] = { static_cast<UINT32>(0u) };

  while(uu != static_cast<unsigned long long>(0u))
  {
    temp[i] = static_cast<UINT32>(uu % static_cast<unsigned long long>(ef_elem_mask));
    uu = static_cast<unsigned long long>(uu / static_cast<unsigned long long>(ef_elem_mask));
    ++i;
  }

  if(i > static_cast<std::size_t>(1u))
  {
    exp += static_cast<INT64>((i - 1u) * static_cast<std::size_t>(ef_elem_digits10));
  }

  std::reverse(temp, temp + i);
  std::copy(temp, temp + (std::min)(i, static_cast<std::size_t>(ef_elem_number)), data.begin());
}

void efx::e_float::mul_loop_uv(const UINT32* const u, const UINT32* const v, UINT32* const w, const INT32 p)
{
  UINT64 carry = static_cast<UINT64>(0u);

  for(INT32 j = static_cast<INT32>(p - 1u); j >= static_cast<INT32>(0); j--)
  {
    UINT64 sum = carry;

    for(INT32 i = j; i >= static_cast<INT32>(0); i--)
    {
      sum += static_cast<UINT64>(u[i] * static_cast<UINT64>(v[j - i]));
    }

    w[j + 1] = static_cast<UINT32>(sum % static_cast<UINT32>(ef_elem_mask));
    carry    = static_cast<UINT64>(sum / static_cast<UINT32>(ef_elem_mask));
  }

  w[0] = static_cast<UINT32>(carry);
}

UINT32 efx::e_float::mul_loop_n(UINT32* const u, UINT32 n, const INT32 p)
{
  UINT64 carry = static_cast<UINT64>(0u);

  // Multiplication loop.
  for(INT32 j = p - 1; j >= static_cast<INT32>(0); j--)
  {
    const UINT64 t = static_cast<UINT64>(carry + static_cast<UINT64>(u[j] * static_cast<UINT64>(n)));
    carry          = static_cast<UINT64>(t / static_cast<UINT32>(e_float::ef_elem_mask));
    u[j]           = static_cast<UINT32>(t - static_cast<UINT64>(static_cast<UINT32>(e_float::ef_elem_mask) * static_cast<UINT64>(carry)));
  }
  
  return static_cast<UINT32>(carry);
}

UINT32 efx::e_float::div_loop_n(UINT32* const u, UINT32 n, const INT32 p)
{
  UINT64 prev = static_cast<UINT64>(0u);

  for(INT32 j = static_cast<INT32>(0); j < p; j++)
  {
    const UINT64 t = static_cast<UINT64>(u[j] + static_cast<UINT64>(prev * static_cast<UINT32>(e_float::ef_elem_mask)));
    u[j]           = static_cast<UINT32>(t / n);
    prev           = static_cast<UINT64>(t - static_cast<UINT64>(n * static_cast<UINT64>(u[j])));
  }

  return static_cast<UINT32>(prev);
}

void efx::e_float::precision(const INT32 prec_digits)
{
  const INT32 elems_x = static_cast<INT32>(  static_cast<INT32>( (prec_digits + (ef_elem_digits10 / 2)) / ef_elem_digits10)
                                           + static_cast<INT32>(((prec_digits % ef_elem_digits10) != 0) ? 1 : 0));

  const INT32 elems = ((elems_x < static_cast<INT32>(2)) ? static_cast<INT32>(2) : elems_x);

  prec_elem = ((elems > ef_elem_number) ? ef_elem_number : elems);
}

efx::e_float& efx::e_float::operator=(const e_float& v)
{
  data      = v.data;
  exp       = v.exp;
  neg       = v.neg;
  fpclass   = v.fpclass;
  prec_elem = v.prec_elem;

  return *this;
}

efx::e_float& efx::e_float::operator+=(const e_float& v)
{
  if(isnan())
  {
    return *this;
  }

  if(isinf())
  {
    if(v.isinf() && (isneg() != v.isneg()))
    {
      *this = std::numeric_limits<e_float>::quiet_NaN();
    }

    return *this;
  }

  if(iszero())
  {
    return operator=(v);
  }

  // Get the offset for the add/sub operation.
  static const INT64 max_delta_exp = static_cast<INT64>((ef_elem_number - 1) * ef_elem_digits10);

  const INT64 ofs_exp = exp - v.exp;

  // Check if the operation is out of range, requiring special handling.
  if(v.iszero() || (ofs_exp > max_delta_exp))
  {
    // Result is *this unchanged since v is negligible compared to *this.
    return *this;
  }
  else if(ofs_exp < -max_delta_exp)
  {
    // Result is *this = v since *this is negligible compared to v.
    return operator=(v);
  }

  // Do the add/sub operation.

  array_type::iterator       p_u    =   data.begin();
  array_type::const_iterator p_v    = v.data.begin();
  bool                       b_copy = false;
  const INT32                ofs    = static_cast<INT32>(static_cast<INT32>(ofs_exp) / ef_elem_digits10);
  array_type                 n_data;

  if(neg == v.neg)
  {
    // Add v to *this, where the data array of either *this or v
    // might have to be treated with a positive, negative or zero offset.
    // The result is stored in *this. The data are added one element
    // at a time, each element with carry.
    if(ofs >= static_cast<INT32>(0))
    {
      std::copy(v.data.begin(),
                v.data.end()   - static_cast<size_t>(ofs),
                n_data.begin() + static_cast<size_t>(ofs));

      std::fill(n_data.begin(),
                n_data.begin() + static_cast<size_t>(ofs),
                static_cast<UINT32>(0u));

      p_v = n_data.begin();
    }
    else
    {
      std::copy(data.begin(),
                data.end()     - static_cast<size_t>(-ofs),
                n_data.begin() + static_cast<size_t>(-ofs));

      std::fill(n_data.begin(),
                n_data.begin() + static_cast<size_t>(-ofs),
                static_cast<UINT32>(0u));

      p_u = n_data.begin();

      b_copy = true;
    }

    // Addition algorithm
    UINT32 carry = static_cast<UINT32>(0u);

    for(INT32 j = static_cast<INT32>(ef_elem_number - static_cast<INT32>(1)); j >= static_cast<INT32>(0); j--)
    {
      UINT32 t = static_cast<UINT32>(static_cast<UINT32>(p_u[j] + p_v[j]) + carry);
      carry    = t / static_cast<UINT32>(ef_elem_mask);
      p_u[j]   = static_cast<UINT32>(t - static_cast<UINT32>(carry * static_cast<UINT32>(ef_elem_mask)));
    }

    if(b_copy)
    {
      data = n_data;
      exp  = v.exp;
    }
    
    // There needs to be a carry into the element -1 of the array data
    if(carry != static_cast<UINT32>(0u))
    {
      std::copy_backward(data.begin(),
                         data.end() - static_cast<std::size_t>(1u),
                         data.end());

      data[0] = carry;
      exp    += static_cast<INT64>(ef_elem_digits10);
    }
  }
  else
  {
    // Subtract v from *this, where the data array of either *this or v
    // might have to be treated with a positive, negative or zero offset.
    if((ofs > static_cast<INT32>(0))
       || (   (ofs == static_cast<INT32>(0))
           && (cmp_data(v.data) > static_cast<INT32>(0)))
      )
    {
      // In this case, |u| > |v| and ofs is positive.
      // Copy the data of v, shifted down to a lower value
      // into the data array m_n. Set the operand pointer p_v
      // to point to the copied, shifted data m_n.
      std::copy(v.data.begin(),
                v.data.end()   - static_cast<size_t>(ofs),
                n_data.begin() + static_cast<size_t>(ofs));

      std::fill(n_data.begin(),
                n_data.begin() + static_cast<size_t>(ofs),
                static_cast<UINT32>(0u));

      p_v = n_data.begin();
    }
    else
    {
      if(ofs != static_cast<INT32>(0))
      {
        // In this case, |u| < |v| and ofs is negative.
        // Shift the data of u down to a lower value.
        std::copy_backward(data.begin(),
                           data.end() - static_cast<size_t>(-ofs),
                           data.end());

        std::fill(data.begin(),
                  data.begin() + static_cast<size_t>(-ofs),
                  static_cast<UINT32>(0u));
      }

      // Copy the data of v into the data array n_data.
      // Set the u-pointer p_u to point to m_n and the
      // operand pointer p_v to point to the shifted
      // data m_data.
      n_data = v.data;
      p_u    = n_data.begin();
      p_v    = data.begin();
      b_copy = true;
    }

    INT32 j;

    // Subtraction algorithm
    INT32 borrow = static_cast<INT32>(0);

    for(j = static_cast<INT32>(ef_elem_number - static_cast<INT32>(1)); j >= static_cast<INT32>(0); j--)
    {
      INT32 t = static_cast<INT32>(static_cast<INT32>(  static_cast<INT32>(p_u[j])
                                                      - static_cast<INT32>(p_v[j])) - borrow);

      // Underflow? Borrow?
      if(t < static_cast<INT32>(0))
      {
        // Yes, underflow and borrow
        t     += static_cast<INT32>(ef_elem_mask);
        borrow = static_cast<INT32>(1);
      }
      else
      {
        borrow = static_cast<INT32>(0);
      }

      p_u[j] = static_cast<UINT32>(static_cast<UINT32>(t) % static_cast<UINT32>(ef_elem_mask));
    }

    if(b_copy)
    {
      data = n_data;
      exp  = v.exp;
      neg  = v.neg;
    }

    // Is it necessary to justify the data?
    const array_type::const_iterator first_nonzero_elem = std::find_if(data.begin(),
                                                                       data.end(),
                                                                       data_elem_is_nonzero_predicate);

    if(first_nonzero_elem != data.begin())
    {
      if(first_nonzero_elem == data.end())
      {
        // This result of the subtraction is exactly zero.
        // Reset the sign and the exponent.
        neg = false;
        exp = static_cast<INT64>(0);
      }
      else
      {
        // Justify the data
        const std::size_t sj = static_cast<std::size_t>(std::distance<array_type::const_iterator>(data.begin(), first_nonzero_elem));

        std::copy(data.begin() + static_cast<std::size_t>(sj),
                  data.end(),
                  data.begin());

        std::fill(data.end() - sj,
                  data.end(),
                  static_cast<UINT32>(0u));

        exp -= static_cast<INT64>(sj * static_cast<std::size_t>(ef_elem_digits10));
      }
    }
  }

  if(   (exp >= std::numeric_limits<e_float>::max_exponent10)
     && (ef::fabs(*this) > (std::numeric_limits<e_float>::max)())
    )
  {
    const bool b_result_is_neg = neg;

    *this = ((!b_result_is_neg) ?  std::numeric_limits<e_float>::infinity()
                                : -std::numeric_limits<e_float>::infinity());
  }

  return *this;
}

efx::e_float& efx::e_float::operator-=(const e_float& v)
{
  // Use *this - v = -(-*this + v).
  return (negate().operator+=(v)).negate();
}

efx::e_float& efx::e_float::operator*=(const e_float& v)
{
  // Evaluate the sign of the result.
  const bool b_result_is_neg = (neg != v.neg);

  // Artificially set the sign of the result to be positive.
  neg = false;

  // Handle special cases like zero, inf and NaN.
  const bool b_u_is_inf  =   isinf();
  const bool b_v_is_inf  = v.isinf();
  const bool b_u_is_zero =   iszero();
  const bool b_v_is_zero = v.iszero();

  if(   (isnan() || v.isnan())
     || (b_u_is_inf && b_v_is_zero)
     || (b_v_is_inf && b_u_is_zero)
    )
  {
    return (*this = std::numeric_limits<e_float>::quiet_NaN());
  }

  if(b_u_is_inf || b_v_is_inf)
  {
    *this = ((!b_result_is_neg) ?  std::numeric_limits<e_float>::infinity()
                                : -std::numeric_limits<e_float>::infinity());

    return *this;
  }

  if(b_u_is_zero || b_v_is_zero)
  {
    return (*this = ef::zero());
  }

  // Check for overflow or underflow.
  const bool u_exp_is_neg =   (exp < static_cast<INT64>(0));
  const bool v_exp_is_neg = (v.exp < static_cast<INT64>(0));

  if(u_exp_is_neg == v_exp_is_neg)
  {
    // Get the unsigned base-10 exponents of *this and v and...
    const INT64 u_exp = ((!u_exp_is_neg) ?   exp : static_cast<INT64>(  -exp));
    const INT64 v_exp = ((!v_exp_is_neg) ? v.exp : static_cast<INT64>(-v.exp));

    // Check the range of the upcoming multiplication.
    const bool b_result_is_out_of_range = (v_exp >= static_cast<INT64>(ef_max_exp10 - u_exp));

    if(b_result_is_out_of_range)
    {
      if(u_exp_is_neg)
      {
        *this = ef::zero();
      }
      else
      {
        *this = ((!b_result_is_neg) ?  std::numeric_limits<e_float>::infinity()
                                    : -std::numeric_limits<e_float>::infinity());
      }

      return *this;
    }
  }

  // Set the exponent of the result.
  exp += v.exp;

  const std::size_t prec_mul = (std::min)(prec_elem, v.prec_elem);

  std::tr1::array<UINT32, static_cast<std::size_t>(ef_elem_number + 1)> w = {{ 0u }};

  mul_loop_uv(data.data(), v.data.data(), w.data(), static_cast<INT32>(prec_mul));

  // Copy the multiplication data into the result.
  // Shift the result and adjust the exponent if necessary.
  if(w[static_cast<std::size_t>(0u)] != static_cast<UINT32>(0u))
  {
    exp += static_cast<INT64>(ef_elem_digits10);

    std::copy(w.begin(), w.end() - 1u, data.begin());
  }
  else
  {
    std::copy(w.begin() + 1u, w.end(), data.begin());
  }

  // Set the sign of the result.
  neg = b_result_is_neg;

  return *this;
}

efx::e_float& efx::e_float::operator/=(const e_float& v)
{
  const bool u_and_v_are_finite_and_identical = (   isfinite()
                                                 && (fpclass == v.fpclass)
                                                 && (exp     == v.exp)
                                                 && (cmp_data(v.data) == static_cast<INT32>(0)));

  if(u_and_v_are_finite_and_identical)
  {
    return (*this = ((neg == v.neg) ? ef::one() : ef::one_minus()));
  }
  else
  {
    return operator*=(e_float(v).calculate_inv());
  }
}

efx::e_float& efx::e_float::add_unsigned_long_long(const unsigned long long n) { return operator+=(e_float(n)); }
efx::e_float& efx::e_float::sub_unsigned_long_long(const unsigned long long n) { return operator-=(e_float(n)); }

efx::e_float& efx::e_float::mul_unsigned_long_long(const unsigned long long n)
{
  // Multiply *this with a constant unsigned long long.

  // Evaluate the sign of the result.
  const bool b_neg = neg;

  // Artificially set the sign of the result to be positive.
  neg = false;

  // Handle special cases like zero, inf and NaN.
  const bool b_u_is_inf  = isinf();
  const bool b_n_is_zero = (n == static_cast<INT32>(0));

  if(isnan() || (b_u_is_inf && b_n_is_zero))
  {
    return (*this = std::numeric_limits<e_float>::quiet_NaN());
  }

  if(b_u_is_inf)
  {
    *this = ((!b_neg) ?  std::numeric_limits<e_float>::infinity()
                      : -std::numeric_limits<e_float>::infinity());

    return *this;
  }

  if(iszero() || b_n_is_zero)
  {
    // Multiplication by zero.
    return (*this = ef::zero());
  }

  if(n >= static_cast<unsigned long long>(ef_elem_mask))
  {
    return operator*=(e_float(n));
  }

  if(n == static_cast<unsigned long long>(1u))
  {
    neg = b_neg;

    return *this;
  }

  // Set up the multiplication loop.
  const INT32 jmax = static_cast<INT32>(data.rend() - std::find_if(data.rbegin(),
                                                                   data.rend(),
                                                                   data_elem_is_nonzero_predicate));

  const INT32 jm1  = static_cast<INT32>(jmax + static_cast<INT32>(1));
  const INT32 prec = static_cast<INT32>(prec_elem);
  const INT32 jm   = (std::min)(jm1, prec);

  const UINT32 nn = static_cast<UINT32>(n);
  const UINT32 carry = mul_loop_n(data.data(), nn, jm);

  // Handle the carry and adjust the exponent.
  if(carry != static_cast<UINT32>(0u))
  {
    exp += static_cast<INT64>(ef_elem_digits10);

    // Shift result of the multiplication one element to the right.
    std::copy_backward(data.begin(),
                       data.begin() + static_cast<std::size_t>(jm - 1),
                       data.begin() + static_cast<std::size_t>(jm));

    data.front() = static_cast<UINT32>(carry);
  }

  if(   (exp >= std::numeric_limits<e_float>::max_exponent10)
     && (*this > (std::numeric_limits<e_float>::max)())
    )
  {
    *this = ((!b_neg) ?  std::numeric_limits<e_float>::infinity()
                      : -std::numeric_limits<e_float>::infinity());

    return *this;
  }

  // Set the sign.
  neg = b_neg;

  return *this;
}

efx::e_float& efx::e_float::div_unsigned_long_long(const unsigned long long n)
{
  // Divide *this by a constant unsigned long long.

  // Evaluate the sign of the result.
  const bool b_neg = neg;

  // Artificially set the sign of the result to be positive.
  neg = false;

  // Handle special cases like zero, inf and NaN.
  if(isnan())
  {
    return *this;
  }

  if(isinf())
  {
    *this = ((!b_neg) ?  std::numeric_limits<e_float>::infinity()
                      : -std::numeric_limits<e_float>::infinity());

    return *this;
  }

  if(n == static_cast<unsigned long long>(0u))
  {
    // Divide by 0.
    if(iszero())
    {
      return (*this = std::numeric_limits<e_float>::quiet_NaN());
    }
    else
    {
      *this = ((!isneg()) ?  std::numeric_limits<e_float>::infinity()
                          : -std::numeric_limits<e_float>::infinity());

      return *this;
    }
  }

  if(iszero())
  {
    return *this;
  }

  if(n >= static_cast<unsigned long long>(ef_elem_mask))
  {
    return operator/=(e_float(n));
  }
  
  if(n > static_cast<unsigned long long>(1u))
  {
    // Division loop.
    const INT32 jm  = static_cast<INT32>(prec_elem);

    const UINT32 nn = static_cast<UINT32>(n);
    const UINT32 prev = div_loop_n(data.data(), nn, jm);

    // Determine if one leading zero is in the result data.
    if(data[0] == static_cast<UINT32>(0u))
    {
      // Adjust the exponent
      exp -= static_cast<INT64>(ef_elem_digits10);

      // Shift result of the division one element to the left.
      std::copy(data.begin() + static_cast<std::size_t>(1u),
                data.begin() + static_cast<std::size_t>(jm),
                data.begin());

      data[static_cast<std::size_t>(jm - 1)] = static_cast<UINT32>(static_cast<UINT64>(prev * static_cast<UINT64>(ef_elem_mask)) / nn);
    }
  }

  // Check for underflow.
  if(   (exp <= std::numeric_limits<e_float>::min_exponent10)
     && (*this < (std::numeric_limits<e_float>::min)())
    )
  {
    return (*this = ef::zero());
  }

  // Set the sign of the result.
  neg = b_neg;

  return *this; 
}

efx::e_float& efx::e_float::calculate_inv(void)
{
  // Compute the inverse of *this.
  const bool b_neg = neg;

  neg = false;

  // Handle special cases like zero, inf and NaN.
  if(iszero())
  {
    *this = ((!b_neg) ?  std::numeric_limits<e_float>::infinity()
                      : -std::numeric_limits<e_float>::infinity());

    return *this;
  }

  if(isnan())
  {
    return *this;
  }

  if(isinf())
  {
    return (*this = ef::zero());
  }

  if(isone())
  {
    *this = ((!b_neg) ? ef::one() : -ef::one());

    return *this;
  }

  // Save the original *this.
  e_float x(*this);

  // Generate the initial estimate using division.
  // Extract the mantissa and exponent for a "manual"
  // computation of the estimate.
  double dd;
  INT64  ne;
  x.extract_parts(dd, ne);

  // Do the inverse estimate using double precision estimates of mantissa and exponent.
  operator=(e_float(1.0 / dd, -ne));

  // Compute the inverse of *this. Quadratically convergent Newton-Raphson iteration
  // is used. During the iterative steps, the precision of the calculation is limited
  // to the minimum required in order to minimize the run-time.

  static const INT32 double_digits10_minus_one = static_cast<INT32>(static_cast<INT32>(std::numeric_limits<double>::digits10) - static_cast<INT32>(1));

  for(INT32 digits = double_digits10_minus_one; digits <= static_cast<INT32>(ef::tol()); digits *= static_cast<INT32>(2))
  {
    // Adjust precision of the terms.
      precision(static_cast<INT32>(digits * static_cast<INT32>(2)));
    x.precision(static_cast<INT32>(digits * static_cast<INT32>(2)));

    // Next iteration.
    operator=(*this * (ef::two() - (*this * x)));
  }

  neg = b_neg;

  prec_elem = ef_elem_number;

  return *this;
}

efx::e_float& efx::e_float::calculate_sqrt(void)
{
  // Compute the square root of *this.

  if(isneg() || (!isfinite()))
  {
    return (*this = std::numeric_limits<e_float>::quiet_NaN());
  }

  if(iszero() || isone())
  {
    return *this;
  }

  // Save the original *this.
  e_float x(*this);

  // Generate the initial estimate using division.
  // Extract the mantissa and exponent for a "manual"
  // computation of the estimate.
  double dd;
  INT64  ne;
  extract_parts(dd, ne);

  // Force the exponent to be an even multiple of two.
  if((ne % static_cast<INT64>(2)) != static_cast<INT64>(0))
  {
    ++ne;
    dd /= 10.0;
  }

  // Setup the iteration.
  // Estimate the square root using simple manipulations.
  const double sqd = ::sqrt(dd);
  
  *this = e_float(sqd, static_cast<INT64>(ne / static_cast<INT64>(2)));
  
  // Estimate 1.0 / (2.0 * x0) using simple manipulations.
  e_float vi(0.5 / sqd, static_cast<INT64>(-ne / static_cast<INT64>(2)));

  // Compute the square root of x. Coupled Newton iteration
  // as described in "Pi Unleashed" is used. During the
  // iterative steps, the precision of the calculation is
  // limited to the minimum required in order to minimize
  // the run-time.
  //
  // Book references:
  // http://www.jjj.de/pibook/pibook.html
  // http://www.amazon.com/exec/obidos/tg/detail/-/3540665722/qid=1035535482/sr=8-7/ref=sr_8_7/104-3357872-6059916?v=glance&n=507846

  static const INT32 double_digits10_minus_one = static_cast<INT32>(static_cast<INT32>(std::numeric_limits<double>::digits10) - static_cast<INT32>(1));

  for(INT32 digits = double_digits10_minus_one; digits <= static_cast<INT32>(ef::tol()); digits *= static_cast<INT32>(2))
  {
    // Adjust precision of the terms.
       precision(static_cast<INT32>(digits * static_cast<INT32>(2)));
    vi.precision(static_cast<INT32>(digits * static_cast<INT32>(2)));

    // Next iteration of vi
    vi += vi * (-((*this * vi) * static_cast<INT32>(2)) + ef::one());

    // Next iteration of *this
    *this += vi * (-(*this * *this) + x);
  }
  
  prec_elem = ef_elem_number;

  return *this;
}

INT32 efx::e_float::cmp_data(const array_type& vd) const
{
  // Compare the data of *this (u) with those of v.
  //         Return +1 for u > v
  //                 0 for u = v
  //                -1 for u < v
  return ((data != vd) ? ((data > vd) ? static_cast<INT32>(1) : static_cast<INT32>(-1))
                       : static_cast<INT32>(0));
}

INT32 efx::e_float::cmp(const e_float& v) const
{
  // Compare v with *this.
  //         Return +1 for *this > v
  //                 0 for *this = v
  //                -1 for *this < v

  if(iszero())
  {
    // The value of *this is zero and v is either zero or non-zero.
    return (v.iszero() ? static_cast<INT32>(0)
                       : (v.isneg() ? static_cast<INT32>(1) : static_cast<INT32>(-1)));
  }
  else if(v.iszero())
  {
    // The value of v is zero and *this is non-zero.
    return (isneg() ? static_cast<INT32>(-1) : static_cast<INT32>(1));
  }
  else
  {
    // Both *this and v are non-zero.

    if(neg != v.neg)
    {
      // The signs are different.
      return (neg ? static_cast<INT32>(-1) : static_cast<INT32>(1));
    }
    else if(exp != v.exp)
    {
      // The signs are the same and the exponents are different.
      const INT32 val_cmp_exp = ((exp < v.exp) ? static_cast<INT32>(1) : static_cast<INT32>(-1));

      return (neg ? val_cmp_exp : static_cast<INT32>(-val_cmp_exp));
    }
    else
    {
      // The signs are the same and the exponents are the same.
      // Compare the data.
      const INT32 val_cmp_data = cmp_data(v.data);

      return (neg ? static_cast<INT32>(-val_cmp_data) : val_cmp_data);
    }
  }
}

bool efx::e_float::iszero(void) const
{
  return (   isfinite()
          && (   (data[0u] == static_cast<UINT32>(0u))
              || (exp < std::numeric_limits<e_float>::min_exponent10)));
}

bool efx::e_float::isone(void) const
{
  // Check if the value of *this is identically 1 or very close to 1.

  if(   (!neg)
     && isfinite()
     && (data[0u] == static_cast<UINT64>(1u))
     && (exp == static_cast<INT64>(0))
    )
  {
    const array_type::const_iterator pos_first_nonzero_elem =
      std::find_if(data.begin(),
                   data.end(),
                   data_elem_is_nonzero_predicate);

    return (pos_first_nonzero_elem == data.end());
  }
  else
  {
    return false;
  }
}

bool efx::e_float::isint(void) const
{
  // Check if the value of *this is pure integer.
  if(!isfinite())
  {
    return false;
  }

  if(iszero())
  {
    return true;
  }

  if(exp < static_cast<INT64>(0))
  {
    // The absolute value of the number is smaller than 1.
    // It can not be an integer.
    return false;
  }

  const array_type::size_type offset_decimal_part = static_cast<array_type::size_type>(exp / ef_elem_digits10) + 1u;

  if(offset_decimal_part >= data.size())
  {
    // The number is too large to resolve the integer part.
    // It considered to be a pure integer.
    return true;
  }

  array_type::const_iterator pos_first_nonzero_elem = std::find_if(data.begin() + offset_decimal_part,
                                                                   data.end(),
                                                                   data_elem_is_nonzero_predicate);

  return (pos_first_nonzero_elem == data.end());
}

efx::e_float& efx::e_float::operator++(void) { return *this += ef::one(); }
efx::e_float& efx::e_float::operator--(void) { return *this -= ef::one(); }

void efx::e_float::extract_parts(double& mantissa, INT64& exponent) const
{
  // Extract the approximate parts mantissa and base-10 exponent from the input e_float value x.

  // Extracts the mantissa and exponent.
  exponent = exp;

  UINT32 p10  = static_cast<UINT32>(1u);
  UINT32 test = data[0u];

  for(;;)
  {
    test /= static_cast<UINT32>(10u);

    if(test == static_cast<UINT32>(0u))
    {
      break;
    }

    p10 *= static_cast<UINT32>(10u);
    ++exponent;
  }

  static const double d_mask = static_cast<double>(ef_elem_mask);

  mantissa =    static_cast<double>(data[0])
             + (static_cast<double>(data[1]) /  d_mask
             +  static_cast<double>(data[2]) / (d_mask * d_mask));

  mantissa /= static_cast<double>(p10);

  if(neg)
  {
    mantissa = -mantissa;
  }
}

double efx::e_float::extract_double(void) const
{
  // Returns the double conversion of a e_float.

  // Check for zero or non-normal e_float.
  if(iszero())
  {
    return 0.0;
  }
  else if(!isfinite())
  {
    if(isnan())
    {
      return std::numeric_limits<double>::quiet_NaN();
    }
    else if(isinf())
    {
      return ((!neg) ?  std::numeric_limits<double>::infinity()
                     : -std::numeric_limits<double>::infinity());
    }
    else
    {
      return 0.0;
    }
  }
  
  // Check if e_float exceeds the  
  static const e_float dbl_max((std::numeric_limits<double>::max)());

  if(ef::fabs(*this) > dbl_max)
  {
    return ((!neg) ?  std::numeric_limits<double>::infinity()
                   : -std::numeric_limits<double>::infinity());
  }

  std::stringstream ss;

  ss << std::setprecision(static_cast<std::streamsize>(std::numeric_limits<double>::digits10 + (2 + 1)))
     << std::scientific
     << *this;

  double d;
  ss >> d;

  return d;
}

INT64 efx::e_float::extract_int64(void) const
{
  // Computes a 64-bit integer cast of the input e_float value x.
  // If |x| exceeds MAX_INT64, then this maximum value is returned.

  if(exp < static_cast<INT64>(0))
  {
    return static_cast<INT64>(0);
  }

  const bool b_neg = isneg();

  const e_float xn = ef::fabs(extract_integer_part());

  INT64 val;

  if(xn > ef::int64max())
  {
    val = (std::numeric_limits<INT64>::max)();
  }
  else
  {
    // Extract the data into the int64 value.
    val = static_cast<INT64>(xn.data[0]);

    for(INT32 i = static_cast<INT32>(1); i <= static_cast<INT32>(static_cast<INT32>(xn.exp) / ef_elem_digits10); i++)
    {
      val *= static_cast<INT64>(ef_elem_mask);
      val += static_cast<INT64>(xn.data[i]);
    }
  }

  return ((!b_neg) ? val : static_cast<INT64>(-val));
}

efx::e_float efx::e_float::extract_integer_part(void) const
{
  // Compute the signed integer part of x.

  if(!isfinite())
  {
    return *this;
  }

  if(exp < static_cast<INT64>(0))
  {
    // The absolute value of the number is smaller than 1.
    // Thus the integer part is zero.
    return ef::zero();
  }
  else if(exp >= static_cast<INT64>(std::numeric_limits<e_float>::digits10 - 1))
  {
    // The number is too large to resolve the integer part.
    // Thus it is already a pure integer part.
    return *this;
  }

  // Make a local copy.
  e_float x = *this;

  // Clear out the decimal portion
  const size_t first_clear = (static_cast<size_t>(x.exp) / static_cast<size_t>(ef_elem_digits10)) + 1u;
  const size_t last_clear  =  static_cast<size_t>(ef_elem_number);

  std::fill(x.data.begin() + first_clear,
            x.data.begin() + last_clear,
            static_cast<UINT32>(0u));

  return x;
}

efx::e_float efx::e_float::extract_decimal_part(void) const
{
  // Compute the signed decimal part of x.

  if(!isfinite())
  {
    return *this;
  }

  if(iszero())
  {
    return ef::zero();
  }

  if(exp < static_cast<INT64>(0))
  {
    // The absolute value of the number is smaller than 1.
    // Thus it is already a pure decimal part.
    return *this;
  }
  else if(exp >= static_cast<INT64>(std::numeric_limits<e_float>::digits10 - 1))
  {
    // The number is too large to have a decimal part.
    // Thus the decimal part is zero.
    return ef::zero();
  }

  e_float x = *this;

  const std::size_t first_copy = static_cast<size_t>((static_cast<size_t>(x.exp) / static_cast<size_t>(ef_elem_digits10)) + 1u);
  const std::size_t last_copy  = static_cast<size_t>(ef_elem_number);

  std::copy(x.data.begin() + first_copy,
            x.data.begin() + last_copy,
            x.data.begin());

  const size_t first_clear = static_cast<size_t>(ef_elem_number - first_copy);
  const size_t last_clear  = static_cast<size_t>(ef_elem_number);

  std::fill(x.data.begin() + first_clear,
            x.data.begin() + last_clear,
            static_cast<UINT32>(0u));

  // Is it necessary to justify the data?
  const array_type::const_iterator first_nonzero_elem = std::find_if(x.data.begin(),
                                                                     x.data.end(),
                                                                     data_elem_is_nonzero_predicate);

  std::size_t sj = static_cast<std::size_t>(0u);

  if(first_nonzero_elem != x.data.begin())
  {
    if(first_nonzero_elem == x.data.end())
    {
      // The decimal part is exactly zero.
      // Reset the sign and the exponent.
      x.neg = false;
      x.exp = static_cast<INT64>(0);
    }
    else
    {
      // Justify the data
      sj = static_cast<std::size_t>(std::distance<array_type::const_iterator>(x.data.begin(), first_nonzero_elem));

      std::copy(x.data.begin() + sj,
                x.data.end(),
                x.data.begin());

      std::fill(x.data.begin() + static_cast<std::size_t>(static_cast<std::size_t>(ef_elem_number) - sj),
                x.data.end(),
                static_cast<UINT32>(0u));
    }
  }

  x.exp -= static_cast<INT64>((first_copy + sj) * static_cast<size_t>(ef_elem_digits10));

  return x;
}

const efx::e_float& efx::e_float::my_value_nan(void) const
{
  static e_float val = ef::zero();

  val.fpclass = ef_NaN;

  static const e_float qnan(val);

  return qnan;
}

const efx::e_float& efx::e_float::my_value_inf(void) const
{
  static e_float val = ef::zero();

  val.fpclass = ef_inf;

  static const e_float inf(val);

  return inf;
}

const efx::e_float& efx::e_float::my_value_max(void) const
{
  static const INT64 exp10_max = std::numeric_limits<e_float>::max_exponent10;

  static const e_float val("1E" + Util::lexical_cast(exp10_max));

  return val;
}

const efx::e_float& efx::e_float::my_value_min(void) const
{
  static const INT64 exp10_min = std::numeric_limits<e_float>::min_exponent10;

  static const e_float val("1E" + Util::lexical_cast(exp10_min));

  return val;
}

void efx::e_float::wr_string(std::string& str, std::ostream& os) const
{
  // Handle INF and NaN.
  if(isnan()) { str = "NaN"; return; }
  if(isinf()) { str = "INF"; return; }

  // Extract all of the digits from e_float, beginning with the first data element.
  str = Util::lexical_cast(data[0]);

  // Readjust the exponent based on the width of the first data element.
  INT64 my_exp = ((!iszero()) ? static_cast<INT64>((exp + static_cast<INT64>(str.length())) - static_cast<INT64>(1))
                              : static_cast<INT64>(0));

  // Get the output stream's precision and limit it to max_digits10.
  // Erroneous negative precision will be set to the zero.
  const std::size_t os_precision  = ((os.precision() > std::streamsize(-1)) ? static_cast<std::size_t>(os.precision())
                                                                            : static_cast<std::size_t>(0u));

  // Assess the format flags.
  const std::ios::fmtflags my_flags = os.flags();

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

  // Determine the number of elements needed to provide the requested digits from e_float.
  const std::size_t number_of_elements = (std::min)(static_cast<std::size_t>((the_number_of_digits_i_want_from_e_float / static_cast<std::size_t>(ef_elem_digits10)) + 2u),
                                                    static_cast<std::size_t>(ef_elem_number));

  // Extract the remaining digits from e_float after the decimal point.
  for(std::size_t i = static_cast<std::size_t>(1u); i < number_of_elements; i++)
  {
    std::stringstream ss;

    ss << std::setw(static_cast<std::streamsize>(ef_elem_digits10))
       << std::setfill(static_cast<char>('0'))
       << data[i];

    str += ss.str();
  }

  // Trim (and round) the output string to the size of the precision.
  round_output_string(str, my_exp, the_number_of_digits_i_want_from_e_float);

  // Obtain additional format information.
  const bool my_uppercase  = ((my_flags & std::ios::uppercase)  != static_cast<std::ios::fmtflags>(0u));
  const bool my_showpos    = ((my_flags & std::ios::showpos)    != static_cast<std::ios::fmtflags>(0u));
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

void efx::e_float::round_output_string(std::string& str, INT64& my_exp, const std::size_t number_of_digits)
{
  // Cut the output to the size of the precision.
  if(str.length() > number_of_digits)
  {
    // Get the digit after the last needed digit for rounding
    const UINT32 round = static_cast<UINT32>(static_cast<UINT32>(str.at(number_of_digits)) - static_cast<UINT32>('0'));

    // Truncate the string
    str = str.substr(static_cast<std::size_t>(0u), number_of_digits);

    if(round >= static_cast<UINT32>(5u))
    {
      std::size_t ix = static_cast<std::size_t>(str.length() - 1u);

      // Every trailing 9 must be rounded up
      while(ix && (static_cast<INT32>(str.at(ix)) - static_cast<INT32>('0') == static_cast<INT32>(9)))
      {
        str.at(ix) = static_cast<char>('0');
        --ix;
      }

      if(!ix)
      {
        // There were nothing but trailing nines.
        if(static_cast<INT32>(static_cast<INT32>(str.at(ix)) - static_cast<INT32>(0x30)) == static_cast<INT32>(9))
        {
          // Increment up to the next order and adjust exponent.
          str.at(ix) = static_cast<char>('1');
          ++my_exp;
        }
        else
        {
          // Round up this digit
          ++str.at(ix);
        }
      }
      else
      {
        // Round up last digit.
        ++str[ix];
      }
    }
  }
}

void efx::e_float::wr_string_scientific(std::string& str,
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

void efx::e_float::wr_string_fixed(std::string& str,
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

bool efx::e_float::rd_string(const char* const s)
{
  std::string str(s);

  // Get possible exponent and remove it
  exp = static_cast<INT64>(0);

  std::size_t pos;

  if(   ((pos = str.find('e')) != std::string::npos)
     || ((pos = str.find('E')) != std::string::npos)
    )
  {
    exp = Util::numeric_cast<INT64>(std::string(str.c_str() + (pos + 1u)));

    str = str.substr(static_cast<std::size_t>(0u), pos);
  }

  // Get possible +/- sign and remove it
  neg = false;

  if((pos = str.find(static_cast<char>('-'))) != std::string::npos)
  {
    neg = true;
    str.erase(pos, static_cast<std::size_t>(1u));
  }

  if((pos = str.find(static_cast<char>('+'))) != std::string::npos)
  {
    str.erase(pos, static_cast<std::size_t>(1u));
  }

  // Remove leading zeros for all input types
  const std::string::iterator fwd_it_leading_zero = std::find_if(str.begin(), str.end(), char_is_nonzero_predicate);

  if(fwd_it_leading_zero != str.begin())
  {
    if(fwd_it_leading_zero == str.end())
    {
      // The string contains nothing but leading zeros. The string is zero.
      operator=(ef::zero());
      return true;
    }
    else
    {
      str.erase(str.begin(), fwd_it_leading_zero);
    }
  }

  // Put the input string into the standard e_float input
  // form aaa.bbbbE+/-n, where aa has 1...unit digits, bbbb
  // has an even multiple of unit digits which are possibly
  // zero padded on the right-end, and n is a signed 32-bit integer
  // which is an even multiple of unit.

  // Find possible decimal point
  pos = str.find(static_cast<char>('.'));

  if(pos != std::string::npos)
  {
    // Remove all trailing insignificant zeros.
    const std::string::const_reverse_iterator rev_it_non_zero_elem =
          std::find_if(str.rbegin(), str.rend(), char_is_nonzero_predicate);

    if(rev_it_non_zero_elem != str.rbegin())
    {
      const std::string::size_type ofs = str.length() - std::distance<std::string::const_reverse_iterator>(str.rbegin(), rev_it_non_zero_elem);
      str.erase(str.begin() + ofs, str.end());
    }

    // Check if input is identically zero
    if(str == std::string("."))
    {
      operator=(ef::zero());
      return true;
    }
  
    // Remove leading significant zeros just after the decimal point
    // and adjust the exponent accordingly.
    // Note that the while-loop operates only on strings of the form ".000abcd..."
    // and peels away the zeros just after the decimal point.
    if(str.at(static_cast<std::size_t>(0u)) == static_cast<char>('.'))
    {
      const std::string::iterator fwd_it_first_non_zero_decimal =
            std::find_if(str.begin() + 1u, str.end(), char_is_nonzero_predicate);

      std::string::size_type delta_exp = static_cast<std::size_t>(0u);

      if(str.at(static_cast<std::size_t>(1u)) == static_cast<char>('0'))
      {
        delta_exp = std::distance<std::string::const_iterator>(str.begin() + 1u,
                                                               fwd_it_first_non_zero_decimal);
      }

      // Bring one single digit into the mantissa and adjust exponent accordingly
      str.erase(str.begin(), fwd_it_first_non_zero_decimal);
      str.insert(static_cast<std::size_t>(1u), ".");
      exp -= static_cast<INT64>(delta_exp + 1u);
    }
  }
  else
  {
    // Input string has no decimal point: Append decimal point.
    str.append(".");
  }

  // Shift the decimal point such that the exponent is an even
  // multiple of std::numeric_limits<e_float>::elem_digits10
        std::size_t n_shift   = static_cast<std::size_t>(0u);
  const std::size_t n_exp_rem = static_cast<std::size_t>(exp % static_cast<INT64>(ef_elem_digits10));

  if((exp % static_cast<INT64>(ef_elem_digits10)) != static_cast<INT64>(0))
  {
    n_shift = ((exp < static_cast<INT64>(0))
                ? static_cast<std::size_t>(n_exp_rem + static_cast<std::size_t>(ef_elem_digits10))
                : static_cast<std::size_t>(n_exp_rem));
  }

  // Make sure that there are enough digits for the decimal point shift.
  pos = str.find(static_cast<char>('.'));

  std::size_t pos_plus_one = static_cast<std::size_t>(pos + 1u);

  if((str.length() - pos_plus_one) < n_shift)
  {
    const std::size_t sz = static_cast<std::size_t>(n_shift - (str.length() - pos_plus_one));

    str.append(std::string(sz, static_cast<char>('0')));
  }

  // Do the decimal point shift.
  if(n_shift != static_cast<std::size_t>(0u))
  {
    str.insert(static_cast<std::size_t>(pos_plus_one + n_shift), ".");

    str.erase(pos, static_cast<std::size_t>(1u));

    exp -= static_cast<INT64>(n_shift);
  }

  // Cut the size of the mantissa to <= ef_elem_digits10
  pos          = str.find(static_cast<char>('.'));
  pos_plus_one = static_cast<std::size_t>(pos + 1u);

  if(pos > static_cast<std::size_t>(ef_elem_digits10))
  {
    const INT32 n_pos         = static_cast<INT32>(pos);
    const INT32 n_rem_is_zero = ((static_cast<INT32>(n_pos % ef_elem_digits10) == static_cast<INT32>(0)) ? static_cast<INT32>(1) : static_cast<INT32>(0));
    const INT32 n             = static_cast<INT32>(static_cast<INT32>(n_pos / ef_elem_digits10) - n_rem_is_zero);
    
    str.insert(static_cast<std::size_t>(static_cast<INT32>(n_pos - static_cast<INT32>(n * ef_elem_digits10))), ".");

    str.erase(pos_plus_one, static_cast<std::size_t>(1u));

    exp += static_cast<INT64>(static_cast<INT64>(n) * static_cast<INT64>(ef_elem_digits10));
  }

  // Pad the decimal part such that its value
  // is an even multiple of ef_elem_digits10
  pos          = str.find(static_cast<char>('.'));
  pos_plus_one = static_cast<std::size_t>(pos + 1u);

  const INT32 n_dec = static_cast<INT32>(static_cast<INT32>(str.length() - 1u) - static_cast<INT32>(pos));
  const INT32 n_rem = static_cast<INT32>(n_dec % ef_elem_digits10);
        INT32 n_cnt = ((n_rem != static_cast<INT32>(0)) ? static_cast<INT32>(ef_elem_digits10 - n_rem)
                                                        : static_cast<INT32>(0));

  if(n_cnt != static_cast<INT32>(0))
  {
    str.append(static_cast<std::size_t>(n_cnt), static_cast<char>('0'));
  }

  // Truncate decimal part if it is too long
  const std::size_t max_dec = static_cast<std::size_t>((ef_elem_number - 1) * ef_elem_digits10);

  if(static_cast<std::size_t>(str.length() - pos) > max_dec)
  {
    str = str.substr(static_cast<std::size_t>(0u),
                     static_cast<std::size_t>(pos_plus_one + max_dec));
  }

  // Now the input string has the standard e_float input form (see comment above).

  // Set the data to 0.
  std::fill(data.begin(), data.end(), static_cast<UINT32>(0u));

  // Extract the data.

  // First get the digits to the left of the decimal point...
  data[0u] = Util::numeric_cast<UINT32>(str.substr(static_cast<std::size_t>(0u), pos));

  // ...then get the remaining digits to the right of the decimal point.
  const std::string::size_type i_end = ((str.length() - pos_plus_one) / static_cast<std::string::size_type>(ef_elem_digits10));

  for(std::string::size_type i = static_cast<std::string::size_type>(0u); i < i_end; i++)
  {
    const std::string::const_iterator it =   str.begin()
                                           + pos_plus_one
                                           + (i * static_cast<std::string::size_type>(ef_elem_digits10));

    data[i + 1u] = Util::numeric_cast<UINT32>(std::string(it, it + static_cast<std::string::size_type>(ef_elem_digits10)));
  }

  // Check for overflow...
  if(exp > std::numeric_limits<e_float>::max_exponent10)
  {
    const bool b_result_is_neg = neg;

    *this = ((!b_result_is_neg) ?  std::numeric_limits<e_float>::infinity()
                                : -std::numeric_limits<e_float>::infinity());
  }

  // ...and check for underflow.
  if(exp < std::numeric_limits<e_float>::min_exponent10)
  {
    *this = ef::zero();
  }

  return true;
}
