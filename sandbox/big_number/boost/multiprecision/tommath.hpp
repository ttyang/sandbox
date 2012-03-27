///////////////////////////////////////////////////////////////////////////////
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_MP_TOMMATH_BACKEND_HPP
#define BOOST_MATH_MP_TOMMATH_BACKEND_HPP

#include <boost/multiprecision/mp_number.hpp>
#include <boost/multiprecision/rational_adapter.hpp>
#include <boost/multiprecision/integer_ops.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/cstdint.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/scoped_array.hpp>
#include <tommath.h>
#include <cmath>
#include <limits>
#include <climits>

namespace boost{ namespace multiprecision{ namespace backends{

namespace detail{

inline void check_tommath_result(unsigned v)
{
   if(v != MP_OKAY)
   {
      BOOST_THROW_EXCEPTION(std::runtime_error(mp_error_to_string(v)));
   }
}

}

struct tommath_int
{
   typedef mpl::list<boost::int32_t, long long>             signed_types;
   typedef mpl::list<boost::uint32_t, unsigned long long>   unsigned_types;
   typedef mpl::list<long double>                           float_types;

   tommath_int()
   {
      detail::check_tommath_result(mp_init(&m_data));
   }
   tommath_int(const tommath_int& o)
   {
      detail::check_tommath_result(mp_init_copy(&m_data, const_cast< ::mp_int*>(&o.m_data)));
   }
   tommath_int& operator = (const tommath_int& o)
   {
      detail::check_tommath_result(mp_copy(const_cast< ::mp_int*>(&o.m_data), &m_data));
      return *this;
   }
   tommath_int& operator = (unsigned long long i)
   {
      unsigned long long mask = ((1uLL << std::numeric_limits<unsigned>::digits) - 1);
      unsigned shift = 0;
      ::mp_int t;
      detail::check_tommath_result(mp_init(&t));
      mp_zero(&m_data);
      while(i)
      {
         detail::check_tommath_result(mp_set_int(&t, static_cast<unsigned>(i & mask)));
         if(shift)
            detail::check_tommath_result(mp_mul_2d(&t, shift, &t));
         detail::check_tommath_result((mp_add(&m_data, &t, &m_data)));
         shift += std::numeric_limits<unsigned>::digits;
         i >>= std::numeric_limits<unsigned>::digits;
      }
      mp_clear(&t);
      return *this;
   }
   tommath_int& operator = (long long i)
   {
      BOOST_MP_USING_ABS
      bool neg = i < 0;
      *this = static_cast<unsigned long long>(abs(i));
      if(neg)
         detail::check_tommath_result(mp_neg(&m_data, &m_data));
      return *this;
   }
   //
   // Note that although mp_set_int takes an unsigned long as an argument
   // it only sets the first 32-bits to the result, and ignores the rest.
   // So use uint32_t as the largest type to pass to this function.
   //
   tommath_int& operator = (boost::uint32_t i)
   {
      detail::check_tommath_result((mp_set_int(&m_data, i)));
      return *this;
   }
   tommath_int& operator = (boost::int32_t i)
   {
      bool neg = i < 0;
      *this = static_cast<boost::uint32_t>(std::abs(i));
      if(neg)
         detail::check_tommath_result(mp_neg(&m_data, &m_data));
      return *this;
   }
   tommath_int& operator = (long double a)
   {
      using std::frexp;
      using std::ldexp;
      using std::floor;

      if (a == 0) {
         detail::check_tommath_result(mp_set_int(&m_data, 0));
         return *this;
      }

      if (a == 1) {
         detail::check_tommath_result(mp_set_int(&m_data, 1));
         return *this;
      }

      BOOST_ASSERT(!(boost::math::isinf)(a));
      BOOST_ASSERT(!(boost::math::isnan)(a));

      int e;
      long double f, term;
      detail::check_tommath_result(mp_set_int(&m_data, 0u));
      ::mp_int t;
      detail::check_tommath_result(mp_init(&t));

      f = frexp(a, &e);

      static const int shift = std::numeric_limits<int>::digits - 1;

      while(f)
      {
         // extract int sized bits from f:
         f = ldexp(f, shift);
         term = floor(f);
         e -= shift;
         detail::check_tommath_result(mp_mul_2d(&m_data, shift, &m_data));
         if(term > 0)
         {
            detail::check_tommath_result(mp_set_int(&t, static_cast<int>(term)));
            detail::check_tommath_result(mp_add(&m_data, &t, &m_data));
         }
         else
         {
            detail::check_tommath_result(mp_set_int(&t, static_cast<int>(-term)));
            detail::check_tommath_result(mp_sub(&m_data, &t, &m_data));
         }
         f -= term;
      }
      if(e > 0)
         detail::check_tommath_result(mp_mul_2d(&m_data, e, &m_data));
      else if(e < 0)
      {
         tommath_int t2;
         detail::check_tommath_result(mp_div_2d(&m_data, -e, &m_data, &t2.data()));
      }
      mp_clear(&t);
      return *this;
   }
   tommath_int& operator = (const char* s)
   {
      std::size_t n = s ? std::strlen(s) : 0;
      int radix = 10;
      if(n && (*s == '0'))
      {
         if((n > 1) && ((s[1] == 'x') || (s[1] == 'X')))
         {
            radix = 16;
            s +=2;
            n -= 2;
         }
         else
         {
            radix = 8;
            n -= 1;
            s += 1;
         }
      }
      if(n)
         detail::check_tommath_result(mp_read_radix(&m_data, s, radix));
      else
         detail::check_tommath_result(mp_set_int(&m_data, 0));
      return *this;
   }
   std::string str(std::streamsize /*digits*/, std::ios_base::fmtflags f)const
   {
      int base = 10;
      if((f & std::ios_base::oct) == std::ios_base::oct)
         base = 8;
      else if((f & std::ios_base::hex) == std::ios_base::hex)
         base = 16;
      //
      // sanity check, bases 8 and 16 are only available for positive numbers:
      //
      if((base != 10) && m_data.sign)
         BOOST_THROW_EXCEPTION(std::runtime_error("Formatted output in bases 8 or 16 is only available for positive numbers"));
      int s;
      detail::check_tommath_result(mp_radix_size(const_cast< ::mp_int*>(&m_data), base, &s));
      boost::scoped_array<char> a(new char[s+1]);
      detail::check_tommath_result(mp_toradix_n(const_cast< ::mp_int*>(&m_data), a.get(), base, s+1));
      std::string result = a.get();
      if((base != 10) && (f & std::ios_base::showbase))
      {
         int pos = result[0] == '-' ? 1 : 0;
         const char* pp = base == 8 ? "0" : "0x";
         result.insert(pos, pp);
      }
      if((f & std::ios_base::showpos) && (result[0] != '-'))
         result.insert(0, 1, '+');
      return result;
   }
   ~tommath_int()
   {
      mp_clear(&m_data);
   }
   void negate()
   {
      mp_neg(&m_data, &m_data);
   }
   int compare(const tommath_int& o)const
   {
      return mp_cmp(const_cast< ::mp_int*>(&m_data), const_cast< ::mp_int*>(&o.m_data));
   }
   template <class V>
   int compare(V v)const
   {
      tommath_int d;
      tommath_int t(*this);
      detail::check_tommath_result(mp_shrink(&t.data()));
      d = v;
      return t.compare(d);
   }
   ::mp_int& data() { return m_data; }
   const ::mp_int& data()const { return m_data; }
   void swap(tommath_int& o)
   {
      mp_exch(&m_data, &o.data());
   }
protected:
   ::mp_int m_data;
};

#define BOOST_MP_TOMMATH_BIT_OP_CHECK(x)\
   if(SIGN(&x.data()))\
      BOOST_THROW_EXCEPTION(std::runtime_error("Bitwise operations on libtommath negative valued integers are disabled as they produce unpredictable results"))

int eval_get_sign(const tommath_int& val);

inline void eval_add(tommath_int& t, const tommath_int& o)
{
   detail::check_tommath_result(mp_add(&t.data(), const_cast< ::mp_int*>(&o.data()), &t.data()));
}
inline void eval_subtract(tommath_int& t, const tommath_int& o)
{
   detail::check_tommath_result(mp_sub(&t.data(), const_cast< ::mp_int*>(&o.data()), &t.data()));
}
inline void eval_multiply(tommath_int& t, const tommath_int& o)
{
   detail::check_tommath_result(mp_mul(&t.data(), const_cast< ::mp_int*>(&o.data()), &t.data()));
}
inline void eval_divide(tommath_int& t, const tommath_int& o)
{
   tommath_int temp;
   detail::check_tommath_result(mp_div(&t.data(), const_cast< ::mp_int*>(&o.data()), &t.data(), &temp.data()));
}
inline void eval_modulus(tommath_int& t, const tommath_int& o)
{
   bool neg = eval_get_sign(t) < 0;
   bool neg2 = eval_get_sign(o) < 0;
   detail::check_tommath_result(mp_mod(&t.data(), const_cast< ::mp_int*>(&o.data()), &t.data()));
   if((neg != neg2) && (eval_get_sign(t) != 0))
   {
      t.negate();
      detail::check_tommath_result(mp_add(&t.data(), const_cast< ::mp_int*>(&o.data()), &t.data()));
      t.negate();
   }
   else if(neg && (t.compare(o) == 0))
   {
      mp_zero(&t.data());
   }
}
template <class UI>
inline void eval_left_shift(tommath_int& t, UI i)
{
   detail::check_tommath_result(mp_mul_2d(&t.data(), static_cast<unsigned>(i), &t.data()));
}
template <class UI>
inline void eval_right_shift(tommath_int& t, UI i)
{
   tommath_int d;
   detail::check_tommath_result(mp_div_2d(&t.data(), static_cast<unsigned>(i), &t.data(), &d.data()));
}
template <class UI>
inline void eval_left_shift(tommath_int& t, const tommath_int& v, UI i)
{
   detail::check_tommath_result(mp_mul_2d(const_cast< ::mp_int*>(&v.data()), static_cast<unsigned>(i), &t.data()));
}
template <class UI>
inline void eval_right_shift(tommath_int& t, const tommath_int& v, UI i)
{
   tommath_int d;
   detail::check_tommath_result(mp_div_2d(const_cast< ::mp_int*>(&v.data()), static_cast<unsigned long>(i), &t.data(), &d.data()));
}

inline void eval_bitwise_and(tommath_int& result, const tommath_int& v)
{
   BOOST_MP_TOMMATH_BIT_OP_CHECK(result);
   BOOST_MP_TOMMATH_BIT_OP_CHECK(v);
   detail::check_tommath_result(mp_and(&result.data(), const_cast< ::mp_int*>(&v.data()), &result.data()));
}

inline void eval_bitwise_or(tommath_int& result, const tommath_int& v)
{
   BOOST_MP_TOMMATH_BIT_OP_CHECK(result);
   BOOST_MP_TOMMATH_BIT_OP_CHECK(v);
   detail::check_tommath_result(mp_or(&result.data(), const_cast< ::mp_int*>(&v.data()), &result.data()));
}

inline void eval_bitwise_xor(tommath_int& result, const tommath_int& v)
{
   BOOST_MP_TOMMATH_BIT_OP_CHECK(result);
   BOOST_MP_TOMMATH_BIT_OP_CHECK(v);
   detail::check_tommath_result(mp_xor(&result.data(), const_cast< ::mp_int*>(&v.data()), &result.data()));
}

inline void eval_add(tommath_int& t, const tommath_int& p, const tommath_int& o)
{
   detail::check_tommath_result(mp_add(const_cast< ::mp_int*>(&p.data()), const_cast< ::mp_int*>(&o.data()), &t.data()));
}
inline void eval_subtract(tommath_int& t, const tommath_int& p, const tommath_int& o)
{
   detail::check_tommath_result(mp_sub(const_cast< ::mp_int*>(&p.data()), const_cast< ::mp_int*>(&o.data()), &t.data()));
}
inline void eval_multiply(tommath_int& t, const tommath_int& p, const tommath_int& o)
{
   detail::check_tommath_result(mp_mul(const_cast< ::mp_int*>(&p.data()), const_cast< ::mp_int*>(&o.data()), &t.data()));
}
inline void eval_divide(tommath_int& t, const tommath_int& p, const tommath_int& o)
{
   tommath_int d;
   detail::check_tommath_result(mp_div(const_cast< ::mp_int*>(&p.data()), const_cast< ::mp_int*>(&o.data()), &t.data(), &d.data()));
}
inline void eval_modulus(tommath_int& t, const tommath_int& p, const tommath_int& o)
{
   bool neg = eval_get_sign(p) < 0;
   bool neg2 = eval_get_sign(o) < 0;
   detail::check_tommath_result(mp_mod(const_cast< ::mp_int*>(&p.data()), const_cast< ::mp_int*>(&o.data()), &t.data()));
   if((neg != neg2) && (eval_get_sign(t) != 0))
   {
      t.negate();
      detail::check_tommath_result(mp_add(&t.data(), const_cast< ::mp_int*>(&o.data()), &t.data()));
      t.negate();
   }
   else if(neg  && (t.compare(o) == 0))
   {
      mp_zero(&t.data());
   }
}

inline void eval_bitwise_and(tommath_int& result, const tommath_int& u, const tommath_int& v)
{
   BOOST_MP_TOMMATH_BIT_OP_CHECK(u);
   BOOST_MP_TOMMATH_BIT_OP_CHECK(v);
   detail::check_tommath_result(mp_and(const_cast< ::mp_int*>(&u.data()), const_cast< ::mp_int*>(&v.data()), &result.data()));
}

inline void eval_bitwise_or(tommath_int& result, const tommath_int& u, const tommath_int& v)
{
   BOOST_MP_TOMMATH_BIT_OP_CHECK(u);
   BOOST_MP_TOMMATH_BIT_OP_CHECK(v);
   detail::check_tommath_result(mp_or(const_cast< ::mp_int*>(&u.data()), const_cast< ::mp_int*>(&v.data()), &result.data()));
}

inline void eval_bitwise_xor(tommath_int& result, const tommath_int& u, const tommath_int& v)
{
   BOOST_MP_TOMMATH_BIT_OP_CHECK(u);
   BOOST_MP_TOMMATH_BIT_OP_CHECK(v);
   detail::check_tommath_result(mp_xor(const_cast< ::mp_int*>(&u.data()), const_cast< ::mp_int*>(&v.data()), &result.data()));
}
/*
inline void eval_complement(tommath_int& result, const tommath_int& u)
{
   //
   // Although this code works, it doesn't really do what the user might expect....
   // and it's hard to see how it ever could.  Disabled for now:
   //
   result = u;
   for(int i = 0; i < result.data().used; ++i)
   {
      result.data().dp[i] = MP_MASK & ~(result.data().dp[i]);
   }
   //
   // We now need to pad out the left of the value with 1's to round up to a whole number of
   // CHAR_BIT * sizeof(mp_digit) units.  Otherwise we'll end up with a very strange number of
   // bits set!
   //
   unsigned shift = result.data().used * DIGIT_BIT;    // How many bits we're actually using
   // How many bits we actually need, reduced by one to account for a mythical sign bit:
   int padding = result.data().used * std::numeric_limits<mp_digit>::digits - shift - 1; 
   while(padding >= std::numeric_limits<mp_digit>::digits) 
      padding -= std::numeric_limits<mp_digit>::digits;

   // Create a mask providing the extra bits we need and add to result:
   tommath_int mask;
   mask = static_cast<long long>((1u << padding) - 1);
   eval_left_shift(mask, shift);
   add(result, mask);
}
*/
inline bool eval_is_zero(const tommath_int& val)
{
   return mp_iszero(&val.data());
}
inline int eval_get_sign(const tommath_int& val)
{
   return mp_iszero(&val.data()) ? 0 : SIGN(&val.data()) ? -1 : 1;
}
template <class A>
inline void eval_convert_to(A* result, const tommath_int& val)
{
   *result = boost::lexical_cast<A>(val.str(0, std::ios_base::fmtflags(0)));
}
inline void eval_convert_to(char* result, const tommath_int& val)
{
   *result = static_cast<char>(boost::lexical_cast<int>(val.str(0, std::ios_base::fmtflags(0))));
}
inline void eval_convert_to(unsigned char* result, const tommath_int& val)
{
   *result = static_cast<unsigned char>(boost::lexical_cast<unsigned>(val.str(0, std::ios_base::fmtflags(0))));
}
inline void eval_convert_to(signed char* result, const tommath_int& val)
{
   *result = static_cast<signed char>(boost::lexical_cast<int>(val.str(0, std::ios_base::fmtflags(0))));
}
inline void eval_abs(tommath_int& result, const tommath_int& val)
{
   detail::check_tommath_result(mp_abs(const_cast< ::mp_int*>(&val.data()), &result.data()));
}
inline void eval_gcd(tommath_int& result, const tommath_int& a, const tommath_int& b)
{
   detail::check_tommath_result(mp_gcd(const_cast< ::mp_int*>(&a.data()), const_cast< ::mp_int*>(&b.data()), const_cast< ::mp_int*>(&result.data())));
}
inline void eval_lcm(tommath_int& result, const tommath_int& a, const tommath_int& b)
{
   detail::check_tommath_result(mp_lcm(const_cast< ::mp_int*>(&a.data()), const_cast< ::mp_int*>(&b.data()), const_cast< ::mp_int*>(&result.data())));
}

inline void eval_qr(const tommath_int& x, const tommath_int& y, 
   tommath_int& q, tommath_int& r)
{
   detail::check_tommath_result(mp_div(const_cast< ::mp_int*>(&x.data()), const_cast< ::mp_int*>(&y.data()), &q.data(), &r.data()));
}

inline unsigned eval_lsb(const tommath_int& val)
{
   return mp_cnt_lsb(const_cast<::mp_int*>(&val.data()));
}

template <class Integer>
inline typename enable_if<is_unsigned<Integer>, Integer>::type eval_integer_modulus(const tommath_int& x, Integer val)
{
   static const mp_digit m = (static_cast<mp_digit>(1) << DIGIT_BIT) - 1;
   if(val <= m)
   {
      mp_digit d;
      detail::check_tommath_result(mp_mod_d(const_cast< ::mp_int*>(&x.data()), static_cast<mp_digit>(val), &d));
      return d;
   }
   else
   {
      return default_ops::eval_integer_modulus(x, val);
   }
}
template <class Integer>
inline typename enable_if<is_signed<Integer>, Integer>::type eval_integer_modulus(const tommath_int& x, Integer val)
{
   typedef typename make_unsigned<Integer>::type unsigned_type;
   return eval_integer_modulus(x, static_cast<unsigned_type>(std::abs(val)));
}

} // namespace backends

using boost::multiprecision::backends::tommath_int;

template<>
struct number_category<tommath_int> : public mpl::int_<number_kind_integer>{};

typedef mp_number<tommath_int >                     tom_int;
typedef rational_adapter<tommath_int>               tommath_rational;
typedef mp_number<tommath_rational>                 tom_rational;

}}  // namespaces

namespace std{

template<bool ExpressionTemplates> 
class numeric_limits<boost::multiprecision::mp_number<boost::multiprecision::tommath_int, ExpressionTemplates> >
{
   typedef boost::multiprecision::mp_number<boost::multiprecision::tommath_int, ExpressionTemplates> number_type;
public:
   BOOST_STATIC_CONSTEXPR bool is_specialized = true;
   //
   // Largest and smallest numbers are bounded only by available memory, set
   // to zero:
   //
   static number_type (min)() BOOST_MP_NOEXCEPT
   { 
      return number_type();
   }
   static number_type (max)() BOOST_MP_NOEXCEPT 
   { 
      return number_type();
   }
   static number_type lowest() BOOST_MP_NOEXCEPT { return (min)(); }
   BOOST_STATIC_CONSTEXPR int digits = INT_MAX;
   BOOST_STATIC_CONSTEXPR int digits10 = (INT_MAX / 1000) * 301L;
   BOOST_STATIC_CONSTEXPR int max_digits10 = digits10 + 2;
   BOOST_STATIC_CONSTEXPR bool is_signed = true;
   BOOST_STATIC_CONSTEXPR bool is_integer = true;
   BOOST_STATIC_CONSTEXPR bool is_exact = true;
   BOOST_STATIC_CONSTEXPR int radix = 2;
   static number_type epsilon() BOOST_MP_NOEXCEPT { return number_type(); }
   static number_type round_error() BOOST_MP_NOEXCEPT { return number_type(); }
   BOOST_STATIC_CONSTEXPR int min_exponent = 0;
   BOOST_STATIC_CONSTEXPR int min_exponent10 = 0;
   BOOST_STATIC_CONSTEXPR int max_exponent = 0;
   BOOST_STATIC_CONSTEXPR int max_exponent10 = 0;
   BOOST_STATIC_CONSTEXPR bool has_infinity = false;
   BOOST_STATIC_CONSTEXPR bool has_quiet_NaN = false;
   BOOST_STATIC_CONSTEXPR bool has_signaling_NaN = false;
   BOOST_STATIC_CONSTEXPR float_denorm_style has_denorm = denorm_absent;
   BOOST_STATIC_CONSTEXPR bool has_denorm_loss = false;
   static number_type infinity() BOOST_MP_NOEXCEPT { return number_type(); }
   static number_type quiet_NaN() BOOST_MP_NOEXCEPT { return number_type(); }
   static number_type signaling_NaN() BOOST_MP_NOEXCEPT { return number_type(); }
   static number_type denorm_min() BOOST_MP_NOEXCEPT { return number_type(); }
   BOOST_STATIC_CONSTEXPR bool is_iec559 = false;
   BOOST_STATIC_CONSTEXPR bool is_bounded = false;
   BOOST_STATIC_CONSTEXPR bool is_modulo = false;
   BOOST_STATIC_CONSTEXPR bool traps = false;
   BOOST_STATIC_CONSTEXPR bool tinyness_before = false;
   BOOST_STATIC_CONSTEXPR float_round_style round_style = round_toward_zero;
};

}

#endif
