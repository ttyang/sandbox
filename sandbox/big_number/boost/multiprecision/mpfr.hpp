///////////////////////////////////////////////////////////////////////////////
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BN_MPFR_HPP
#define BOOST_MATH_BN_MPFR_HPP

#include <boost/multiprecision/mp_number.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/cstdint.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/math/bindings/detail/big_lanczos.hpp>
#include <mpfr.h>
#include <cmath>
#include <algorithm>

namespace boost{ namespace multiprecision{

template <unsigned digits10>
struct mpfr_real_backend;

namespace detail{

long get_default_precision() { return 50; }

template <unsigned digits10>
struct mpfr_real_imp
{
   typedef mpl::list<long, long long>                     signed_types;
   typedef mpl::list<unsigned long, unsigned long long>   unsigned_types;
   typedef mpl::list<double, long double>                 real_types;
   typedef long                                           exponent_type;

   mpfr_real_imp(){}

   mpfr_real_imp(const mpfr_real_imp& o)
   {
      mpfr_init2(m_data, (((digits10 ? digits10 : get_default_precision()) + 1) * 1000L) / 301L);
      mpfr_set(m_data, o.m_data, GMP_RNDN);
   }
#ifndef BOOST_NO_RVALUE_REFERENCES
   mpfr_real_imp(mpfr_real_imp&& o)
   {
      m_data[0] = o.m_data[0];
      o.m_data[0]._mpfr_d = 0;
   }
#endif
   mpfr_real_imp& operator = (const mpfr_real_imp& o)
   {
      mpfr_set(m_data, o.m_data, GMP_RNDN);
      return *this;
   }
#ifndef BOOST_NO_RVALUE_REFERENCES
   mpfr_real_imp& operator = (mpfr_real_imp&& o)
   {
      mpfr_swap(m_data, o.m_data);
      return *this;
   }
#endif
   mpfr_real_imp& operator = (boost::uintmax_t i)
   {
      boost::uintmax_t mask = ((1uLL << std::numeric_limits<unsigned>::digits) - 1);
      unsigned shift = 0;
      mpfr_t t;
      mpfr_init2(t, (std::max)(static_cast<unsigned>(std::numeric_limits<boost::uintmax_t>::digits), static_cast<unsigned>(((digits10 + 1) * 1000L) / 301L)));
      mpfr_set_ui(m_data, 0, GMP_RNDN);
      while(i)
      {
         mpfr_set_ui(t, static_cast<unsigned>(i & mask), GMP_RNDN);
         if(shift)
            mpfr_mul_2exp(t, t, shift, GMP_RNDN);
         mpfr_add(m_data, m_data, t, GMP_RNDN);
         shift += std::numeric_limits<unsigned>::digits;
         i >>= std::numeric_limits<unsigned>::digits;
      }
      mpfr_clear(t);
      return *this;
   }
   mpfr_real_imp& operator = (boost::intmax_t i)
   {
      bool neg = i < 0;
      *this = static_cast<boost::uintmax_t>(std::abs(i));
      if(neg)
         mpfr_neg(m_data, m_data, GMP_RNDN);
      return *this;
   }
   mpfr_real_imp& operator = (unsigned long i)
   {
      mpfr_set_ui(m_data, i, GMP_RNDN);
      return *this;
   }
   mpfr_real_imp& operator = (long i)
   {
      mpfr_set_si(m_data, i, GMP_RNDN);
      return *this;
   }
   mpfr_real_imp& operator = (double d)
   {
      mpfr_set_d(m_data, d, GMP_RNDN);
      return *this;
   }
   mpfr_real_imp& operator = (long double a)
   {
      using std::frexp;
      using std::ldexp;
      using std::floor;

      if (a == 0) {
         mpfr_set_si(m_data, 0, GMP_RNDN);
         return *this;
      }

      if (a == 1) {
         mpfr_set_si(m_data, 1, GMP_RNDN);
         return *this;
      }

      BOOST_ASSERT(!(boost::math::isinf)(a));
      BOOST_ASSERT(!(boost::math::isnan)(a));

      int e;
      long double f, term;
      mpfr_init_set_ui(m_data, 0u, GMP_RNDN);

      f = frexp(a, &e);

      static const int shift = std::numeric_limits<int>::digits - 1;

      while(f)
      {
         // extract int sized bits from f:
         f = ldexp(f, shift);
         term = floor(f);
         e -= shift;
         mpfr_mul_2exp(m_data, m_data, shift, GMP_RNDN);
         if(term > 0)
            mpfr_add_ui(m_data, m_data, static_cast<unsigned>(term), GMP_RNDN);
         else
            mpfr_sub_ui(m_data, m_data, static_cast<unsigned>(-term), GMP_RNDN);
         f -= term;
      }
      if(e > 0)
         mpfr_mul_2exp(m_data, m_data, e, GMP_RNDN);
      else if(e < 0)
         mpfr_div_2exp(m_data, m_data, -e, GMP_RNDN);
      return *this;
   }
   mpfr_real_imp& operator = (const char* s)
   {
      mpfr_set_str(m_data, s, 10, GMP_RNDN);
      return *this;
   }
   void swap(mpfr_real_imp& o)
   {
      mpfr_swap(m_data, o.m_data);
   }
   std::string str(unsigned digits, bool scientific)const
   {
      std::string result;
      mp_exp_t e;
      char* ps = mpfr_get_str (0, &e, 10, digits, m_data, GMP_RNDN);
      std::ptrdiff_t sl = std::strlen(ps);
      unsigned chars = sl;
      if(sl == 0)
         return "0";
      while(ps[chars-1] == '0')
         --chars;
      if(*ps == '-')
         --chars; // number of digits excluding sign.
      if(chars == 0)
         return "0";
      if(!scientific
         && (chars <= std::numeric_limits<boost::uintmax_t>::digits10 + 1)
         && (e >= (int)chars)
         && (chars <= std::numeric_limits<boost::uintmax_t>::digits10 + 1))
      {
         result.assign(ps, (*ps == '-' ? chars+1 : chars));
         result.append(e-chars, '0');
      }
      else
      {
         result = ps;
         if(ps[0] == '-')
            result.insert(2, 1, '.');
         else
            result.insert(1, 1, '.');
         --e;
         if(e)
            result += "e" + lexical_cast<std::string>(e);
      }
      mpfr_free_str(ps);
      return result;
   }
   ~mpfr_real_imp()
   {
      if(m_data[0]._mpfr_d)
         mpfr_clear(m_data);
   }
   void negate()
   {
      mpfr_neg(m_data, m_data, GMP_RNDN);
   }
   int compare(const mpfr_real_backend<digits10>& o)const
   {
      return mpfr_cmp(m_data, o.m_data);
   }
   int compare(long i)const
   {
      return mpfr_cmp_si(m_data, i);
   }
   int compare(unsigned long i)const
   {
      return mpfr_cmp_ui(m_data, i);
   }
   template <class V>
   int compare(V v)const
   {
      mpfr_real_backend<digits10> d;
      d = v;
      return compare(d);
   }
   mpfr_t& data() { return m_data; }
   const mpfr_t& data()const { return m_data; }
protected:
   mpfr_t m_data;
   static unsigned& get_default_precision()
   {
      static unsigned val = 50;
      return val;
   }
};

} // namespace detail

template <unsigned digits10>
struct mpfr_real_backend : public detail::mpfr_real_imp<digits10>
{
   mpfr_real_backend()
   {
      mpfr_init2(this->m_data, ((digits10 + 1) * 1000L) / 301L);
   }
   mpfr_real_backend(const mpfr_real_backend& o) : detail::mpfr_real_imp<digits10>(o) {}
#ifndef BOOST_NO_RVALUE_REFERENCES
   mpfr_real_backend(mpfr_real_backend&& o) : detail::mpfr_real_imp<digits10>(o) {}
#endif
   mpfr_real_backend& operator=(const mpfr_real_backend& o)
   {
      *static_cast<detail::mpfr_real_imp<digits10>*>(this) = static_cast<detail::mpfr_real_imp<digits10> const&>(o);
      return *this;
   }
#ifndef BOOST_NO_RVALUE_REFERENCES
   mpfr_real_backend& operator=(mpfr_real_backend&& o)
   {
      *static_cast<detail::mpfr_real_imp<digits10>*>(this) = static_cast<detail::mpfr_real_imp<digits10>&&>(o);
      return *this;
   }
#endif
   template <class V>
   mpfr_real_backend& operator=(const V& v)
   {
      *static_cast<detail::mpfr_real_imp<digits10>*>(this) = v;
      return *this;
   }
};

template <>
struct mpfr_real_backend<0> : public detail::mpfr_real_imp<0>
{
   mpfr_real_backend()
   {
      mpfr_init2(this->m_data, ((get_default_precision() + 1) * 1000L) / 301L);
   }
   mpfr_real_backend(unsigned digits10)
   {
      mpfr_init2(this->m_data, ((digits10 + 1) * 1000L) / 301L);
   }
   mpfr_real_backend(const mpfr_real_backend& o) : detail::mpfr_real_imp<0>(o) {}
#ifndef BOOST_NO_RVALUE_REFERENCES
   mpfr_real_backend(mpfr_real_backend&& o) : detail::mpfr_real_imp<0>(o) {}
#endif
   mpfr_real_backend(const mpfr_real_backend& o, unsigned digits10) 
   {
      mpfr_init2(this->m_data, ((digits10 + 1) * 1000L) / 301L);
      *this = o;
   }

   mpfr_real_backend& operator=(const mpfr_real_backend& o)
   {
      *static_cast<detail::mpfr_real_imp<0>*>(this) = static_cast<detail::mpfr_real_imp<0> const&>(o);
      return *this;
   }
#ifndef BOOST_NO_RVALUE_REFERENCES
   mpfr_real_backend& operator=(mpfr_real_backend&& o)
   {
      *static_cast<detail::mpfr_real_imp<0>*>(this) = static_cast<detail::mpfr_real_imp<0> &&>(o);
      return *this;
   }
#endif
   template <class V>
   mpfr_real_backend& operator=(const V& v)
   {
      *static_cast<detail::mpfr_real_imp<0>*>(this) = v;
      return *this;
   }
   static unsigned default_precision()
   {
      return get_default_precision();
   }
   static void default_precision(unsigned v)
   {
      get_default_precision() = v;
   }
   unsigned precision()const
   {
      return mpfr_get_prec(this->m_data) * 301L / 1000 - 1;
   }
   void precision(unsigned digits10)
   {
      mpfr_set_prec(this->m_data, (digits10 + 1) * 1000L / 301);
   }
};

template <unsigned digits10>
inline void add(mpfr_real_backend<digits10>& result, const mpfr_real_backend<digits10>& o)
{
   mpfr_add(result.data(), result.data(), o.data(), GMP_RNDN);
}
template <unsigned digits10>
inline void subtract(mpfr_real_backend<digits10>& result, const mpfr_real_backend<digits10>& o)
{
   mpfr_sub(result.data(), result.data(), o.data(), GMP_RNDN);
}
template <unsigned digits10>
inline void multiply(mpfr_real_backend<digits10>& result, const mpfr_real_backend<digits10>& o)
{
   mpfr_mul(result.data(), result.data(), o.data(), GMP_RNDN);
}
template <unsigned digits10>
inline void divide(mpfr_real_backend<digits10>& result, const mpfr_real_backend<digits10>& o)
{
   mpfr_div(result.data(), result.data(), o.data(), GMP_RNDN);
}
template <unsigned digits10>
inline void add(mpfr_real_backend<digits10>& result, unsigned long i)
{
   mpfr_add_ui(result.data(), result.data(), i, GMP_RNDN);
}
template <unsigned digits10>
inline void subtract(mpfr_real_backend<digits10>& result, unsigned long i)
{
   mpfr_sub_ui(result.data(), result.data(), i, GMP_RNDN);
}
template <unsigned digits10>
inline void multiply(mpfr_real_backend<digits10>& result, unsigned long i)
{
   mpfr_mul_ui(result.data(), result.data(), i, GMP_RNDN);
}
template <unsigned digits10>
inline void divide(mpfr_real_backend<digits10>& result, unsigned long i)
{
   mpfr_div_ui(result.data(), result.data(), i, GMP_RNDN);
}
template <unsigned digits10>
inline void add(mpfr_real_backend<digits10>& result, long i)
{
   if(i > 0)
      mpfr_add_ui(result.data(), result.data(), i, GMP_RNDN);
   else
      mpfr_sub_ui(result.data(), result.data(), std::abs(i), GMP_RNDN);
}
template <unsigned digits10>
inline void subtract(mpfr_real_backend<digits10>& result, long i)
{
   if(i > 0)
      mpfr_sub_ui(result.data(), result.data(), i, GMP_RNDN);
   else
      mpfr_add_ui(result.data(), result.data(), std::abs(i), GMP_RNDN);
}
template <unsigned digits10>
inline void multiply(mpfr_real_backend<digits10>& result, long i)
{
   mpfr_mul_ui(result.data(), result.data(), std::abs(i), GMP_RNDN);
   if(i < 0)
      mpfr_neg(result.data(), result.data(), GMP_RNDN);
}
template <unsigned digits10>
inline void divide(mpfr_real_backend<digits10>& result, long i)
{
   mpfr_div_ui(result.data(), result.data(), std::abs(i), GMP_RNDN);
   if(i < 0)
      mpfr_neg(result.data(), result.data(), GMP_RNDN);
}
//
// Specialised 3 arg versions of the basic operators:
//
template <unsigned digits10>
inline void add(mpfr_real_backend<digits10>& a, const mpfr_real_backend<digits10>& x, const mpfr_real_backend<digits10>& y)
{
   mpfr_add(a.data(), x.data(), y.data(), GMP_RNDN);
}
template <unsigned digits10>
inline void add(mpfr_real_backend<digits10>& a, const mpfr_real_backend<digits10>& x, unsigned long y)
{
   mpfr_add_ui(a.data(), x.data(), y, GMP_RNDN);
}
template <unsigned digits10>
inline void add(mpfr_real_backend<digits10>& a, const mpfr_real_backend<digits10>& x, long y)
{
   if(y < 0)
      mpfr_sub_ui(a.data(), x.data(), -y, GMP_RNDN);
   else
      mpfr_add_ui(a.data(), x.data(), y, GMP_RNDN);
}
template <unsigned digits10>
inline void add(mpfr_real_backend<digits10>& a, unsigned long x, const mpfr_real_backend<digits10>& y)
{
   mpfr_add_ui(a.data(), y.data(), x, GMP_RNDN);
}
template <unsigned digits10>
inline void add(mpfr_real_backend<digits10>& a, long x, const mpfr_real_backend<digits10>& y)
{
   if(x < 0)
   {
      mpfr_ui_sub(a.data(), -x, y.data(), GMP_RNDN);
      mpfr_neg(a.data(), a.data(), GMP_RNDN);
   }
   else
      mpfr_add_ui(a.data(), y.data(), x, GMP_RNDN);
}
template <unsigned digits10>
inline void subtract(mpfr_real_backend<digits10>& a, const mpfr_real_backend<digits10>& x, const mpfr_real_backend<digits10>& y)
{
   mpfr_sub(a.data(), x.data(), y.data(), GMP_RNDN);
}
template <unsigned digits10>
inline void subtract(mpfr_real_backend<digits10>& a, const mpfr_real_backend<digits10>& x, unsigned long y)
{
   mpfr_sub_ui(a.data(), x.data(), y, GMP_RNDN);
}
template <unsigned digits10>
inline void subtract(mpfr_real_backend<digits10>& a, const mpfr_real_backend<digits10>& x, long y)
{
   if(y < 0)
      mpfr_add_ui(a.data(), x.data(), -y, GMP_RNDN);
   else
      mpfr_sub_ui(a.data(), x.data(), y, GMP_RNDN);
}
template <unsigned digits10>
inline void subtract(mpfr_real_backend<digits10>& a, unsigned long x, const mpfr_real_backend<digits10>& y)
{
   mpfr_ui_sub(a.data(), x, y.data(), GMP_RNDN);
}
template <unsigned digits10>
inline void subtract(mpfr_real_backend<digits10>& a, long x, const mpfr_real_backend<digits10>& y)
{
   if(x < 0)
   {
      mpfr_add_ui(a.data(), y.data(), -x, GMP_RNDN);
      mpfr_neg(a.data(), a.data(), GMP_RNDN);
   }
   else
      mpfr_ui_sub(a.data(), x, y.data(), GMP_RNDN);
}

template <unsigned digits10>
inline void multiply(mpfr_real_backend<digits10>& a, const mpfr_real_backend<digits10>& x, const mpfr_real_backend<digits10>& y)
{
   mpfr_mul(a.data(), x.data(), y.data(), GMP_RNDN);
}
template <unsigned digits10>
inline void multiply(mpfr_real_backend<digits10>& a, const mpfr_real_backend<digits10>& x, unsigned long y)
{
   mpfr_mul_ui(a.data(), x.data(), y, GMP_RNDN);
}
template <unsigned digits10>
inline void multiply(mpfr_real_backend<digits10>& a, const mpfr_real_backend<digits10>& x, long y)
{
   if(y < 0)
   {
      mpfr_mul_ui(a.data(), x.data(), -y, GMP_RNDN);
      a.negate();
   }
   else
      mpfr_mul_ui(a.data(), x.data(), y, GMP_RNDN);
}
template <unsigned digits10>
inline void multiply(mpfr_real_backend<digits10>& a, unsigned long x, const mpfr_real_backend<digits10>& y)
{
   mpfr_mul_ui(a.data(), y.data(), x, GMP_RNDN);
}
template <unsigned digits10>
inline void multiply(mpfr_real_backend<digits10>& a, long x, const mpfr_real_backend<digits10>& y)
{
   if(x < 0)
   {
      mpfr_mul_ui(a.data(), y.data(), -x, GMP_RNDN);
      mpfr_neg(a.data(), a.data(), GMP_RNDN);
   }
   else
      mpfr_mul_ui(a.data(), y.data(), x, GMP_RNDN);
}

template <unsigned digits10>
inline void divide(mpfr_real_backend<digits10>& a, const mpfr_real_backend<digits10>& x, const mpfr_real_backend<digits10>& y)
{
   mpfr_div(a.data(), x.data(), y.data(), GMP_RNDN);
}
template <unsigned digits10>
inline void divide(mpfr_real_backend<digits10>& a, const mpfr_real_backend<digits10>& x, unsigned long y)
{
   mpfr_div_ui(a.data(), x.data(), y, GMP_RNDN);
}
template <unsigned digits10>
inline void divide(mpfr_real_backend<digits10>& a, const mpfr_real_backend<digits10>& x, long y)
{
   if(y < 0)
   {
      mpfr_div_ui(a.data(), x.data(), -y, GMP_RNDN);
      a.negate();
   }
   else
      mpfr_div_ui(a.data(), x.data(), y, GMP_RNDN);
}
template <unsigned digits10>
inline void divide(mpfr_real_backend<digits10>& a, unsigned long x, const mpfr_real_backend<digits10>& y)
{
   mpfr_ui_div(a.data(), x, y.data(), GMP_RNDN);
}
template <unsigned digits10>
inline void divide(mpfr_real_backend<digits10>& a, long x, const mpfr_real_backend<digits10>& y)
{
   if(x < 0)
   {
      mpfr_ui_div(a.data(), -x, y.data(), GMP_RNDN);
      mpfr_neg(a.data(), a.data(), GMP_RNDN);
   }
   else
      mpfr_ui_div(a.data(), x, y.data(), GMP_RNDN);
}

template <unsigned digits10>
inline bool is_zero(const mpfr_real_backend<digits10>& val)
{
   return 0 != mpfr_zero_p(val.data());
}
template <unsigned digits10>
inline int get_sign(const mpfr_real_backend<digits10>& val)
{
   return mpfr_sgn(val.data());
}

template <unsigned digits10>
inline void convert_to(unsigned long* result, const mpfr_real_backend<digits10>& val)
{
   *result = mpfr_get_ui(val.data(), GMP_RNDN);
}
template <unsigned digits10>
inline void convert_to(long* result, const mpfr_real_backend<digits10>& val)
{
   *result = mpfr_get_si(val.data(), GMP_RNDN);
}
#ifdef _MPFR_H_HAVE_INTMAX_T
template <unsigned digits10>
inline void convert_to(boost::uintmax_t* result, const mpfr_real_backend<digits10>& val)
{
   *result = mpfr_get_uj(val.data(), GMP_RNDN);
}
template <unsigned digits10>
inline void convert_to(boost::intmax_t* result, const mpfr_real_backend<digits10>& val)
{
   *result = mpfr_get_sj(val.data(), GMP_RNDN);
}
#endif
template <unsigned digits10>
inline void convert_to(double* result, const mpfr_real_backend<digits10>& val)
{
   *result = mpfr_get_d(val.data(), GMP_RNDN);
}
template <unsigned digits10>
inline void convert_to(long double* result, const mpfr_real_backend<digits10>& val)
{
   *result = mpfr_get_ld(val.data(), GMP_RNDN);
}

//
// Native non-member operations:
//
template <unsigned Digits10>
inline void eval_sqrt(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& val)
{
   mpfr_sqrt(result.data(), val.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_abs(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& val)
{
   mpfr_abs(result.data(), val.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_fabs(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& val)
{
   mpfr_abs(result.data(), val.data(), GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_ceil(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& val)
{
   mpfr_ceil(result.data(), val.data());
}
template <unsigned Digits10>
inline void eval_floor(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& val)
{
   mpfr_floor(result.data(), val.data());
}
template <unsigned Digits10>
inline void eval_trunc(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& val)
{
   mpfr_trunc(result.data(), val.data());
}
template <unsigned Digits10>
inline void eval_ldexp(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& val, long e)
{
   if(e > 0)
      mpfr_mul_2exp(result.data(), val.data(), e, GMP_RNDN);
   else if(e < 0)
      mpfr_div_2exp(result.data(), val.data(), -e, GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_frexp(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& val, int* e)
{
   long v;
   mpfr_get_d_2exp(&v, val.data(), GMP_RNDN);
   *e = v;
   eval_ldexp(result, val, -v);
}
template <unsigned Digits10>
inline void eval_frexp(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& val, long* e)
{
   mpfr_get_d_2exp(e, val.data(), GMP_RNDN);
   return eval_ldexp(result, val, -*e);
}

template <unsigned Digits10>
inline int eval_fpclassify(const mpfr_real_backend<Digits10>& val)
{
   return mpfr_inf_p(val.data()) ? FP_INFINITE : mpfr_nan_p(val.data()) ? FP_NAN : mpfr_zero_p(val.data()) ? FP_ZERO : FP_NORMAL;
}

template <unsigned Digits10>
inline void eval_pow(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& b, const mpfr_real_backend<Digits10>& e)
{
   mpfr_pow(result.data(), b.data(), e.data(), GMP_RNDN);
}

template <unsigned Digits10, class Integer>
inline typename enable_if<mpl::and_<is_signed<Integer>, mpl::bool_<sizeof(Integer) <= sizeof(long)> > >::type eval_pow(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& b, const Integer& e)
{
   mpfr_pow_si(result.data(), b.data(), e, GMP_RNDN);
}

template <unsigned Digits10, class Integer>
inline typename enable_if<mpl::and_<is_unsigned<Integer>, mpl::bool_<sizeof(Integer) <= sizeof(long)> > >::type eval_pow(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& b, const Integer& e)
{
   mpfr_pow_ui(result.data(), b.data(), e, GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_exp(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& arg)
{
   mpfr_exp(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_log(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& arg)
{
   mpfr_log(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_sin(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& arg)
{
   mpfr_sin(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_cos(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& arg)
{
   mpfr_cos(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_tan(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& arg)
{
   mpfr_tan(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_asin(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& arg)
{
   mpfr_asin(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_acos(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& arg)
{
   mpfr_acos(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_atan(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& arg)
{
   mpfr_atan(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_sinh(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& arg)
{
   mpfr_sinh(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_cosh(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& arg)
{
   mpfr_cosh(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_tanh(mpfr_real_backend<Digits10>& result, const mpfr_real_backend<Digits10>& arg)
{
   mpfr_tanh(result.data(), arg.data(), GMP_RNDN);
}

typedef mp_number<mpfr_real_backend<50> >    mpfr_real_50;
typedef mp_number<mpfr_real_backend<100> >   mpfr_real_100;
typedef mp_number<mpfr_real_backend<500> >   mpfr_real_500;
typedef mp_number<mpfr_real_backend<1000> >  mpfr_real_1000;
typedef mp_number<mpfr_real_backend<0> >     mpfr_real;

} // namespace boost

namespace math{

namespace lanczos{

template<unsigned Digits10, class Policy>
struct lanczos<multiprecision::mp_number<multiprecision::mpfr_real_backend<Digits10> >, Policy>
{
   typedef typename mpl::if_c<
      Digits10 <= 36,
      lanczos22UDT,
      typename mpl::if_c<
         Digits10 <= 50,
         lanczos31UDT,
         typename mpl::if_c<
            Digits10 <= 110,
            lanczos61UDT,
            undefined_lanczos
         >::type
      >::type
   >::type type;
};

} // namespace lanczos


}}  // namespaces

namespace std{

#ifdef BOOST_NO_NOEXCEPT
#  define noexcept
#endif

//
// numeric_limits [partial] specializations for the types declared in this header:
//
template<unsigned Digits10> 
class numeric_limits<boost::multiprecision::mp_number<boost::multiprecision::mpfr_real_backend<Digits10> > >
{
   typedef boost::multiprecision::mp_number<boost::multiprecision::mpfr_real_backend<Digits10> > number_type;
public:
   BOOST_STATIC_CONSTEXPR bool is_specialized = true;
   BOOST_STATIC_CONSTEXPR number_type (min)() noexcept
   { 
      initializer.do_nothing();
      static std::pair<bool, number_type> value;
      if(!value.first)
      {
         value.first = true;
         value.second = 0.5;
         mpfr_div_2exp(value.second.backend().data(), value.second.backend().data(), -mpfr_get_emin(), GMP_RNDN);
      }
      return value.second;
   }
   BOOST_STATIC_CONSTEXPR number_type (max)() noexcept
   { 
      initializer.do_nothing();
      static std::pair<bool, number_type> value;
      if(!value.first)
      {
         value.first = true;
         value.second = 0.5;
         mpfr_mul_2exp(value.second.backend().data(), value.second.backend().data(), mpfr_get_emax(), GMP_RNDN);
      }
      return value.second;
   }
   BOOST_STATIC_CONSTEXPR number_type lowest() noexcept
   {
      return -(max)();
   }
   BOOST_STATIC_CONSTEXPR int digits = static_cast<int>(((Digits10 + 1) * 1000L) / 301L);
   BOOST_STATIC_CONSTEXPR int digits10 = Digits10;
   // Is this really correct???
   BOOST_STATIC_CONSTEXPR int max_digits10 = Digits10 + 1;
   BOOST_STATIC_CONSTEXPR bool is_signed = true;
   BOOST_STATIC_CONSTEXPR bool is_integer = false;
   BOOST_STATIC_CONSTEXPR bool is_exact = false;
   BOOST_STATIC_CONSTEXPR int radix = 2;
   BOOST_STATIC_CONSTEXPR number_type epsilon() noexcept 
   { 
      initializer.do_nothing();
      static std::pair<bool, number_type> value;
      if(!value.first)
      {
         value.first = true;
         value.second = 1;
         mpfr_div_2exp(value.second.backend().data(), value.second.backend().data(), std::numeric_limits<number_type>::digits - 1, GMP_RNDN);
      }
      return value.second;
   }
   // What value should this be????
   BOOST_STATIC_CONSTEXPR number_type round_error() noexcept 
   { 
      // returns epsilon/2
      initializer.do_nothing();
      static std::pair<bool, number_type> value;
      if(!value.first)
      {
         value.first = true;
         value.second = 1;
         mpfr_div_2exp(value.second.backend().data(), value.second.backend().data(), digits, GMP_RNDN);
      }
      return value.second;
   }
   BOOST_STATIC_CONSTEXPR long min_exponent = MPFR_EMIN_DEFAULT;
   BOOST_STATIC_CONSTEXPR long min_exponent10 = (MPFR_EMIN_DEFAULT / 1000) * 301L;
   BOOST_STATIC_CONSTEXPR long max_exponent = MPFR_EMAX_DEFAULT;
   BOOST_STATIC_CONSTEXPR long max_exponent10 = (MPFR_EMAX_DEFAULT / 1000) * 301L;
   BOOST_STATIC_CONSTEXPR bool has_infinity = true;
   BOOST_STATIC_CONSTEXPR bool has_quiet_NaN = true;
   BOOST_STATIC_CONSTEXPR bool has_signaling_NaN = false;
   BOOST_STATIC_CONSTEXPR float_denorm_style has_denorm = denorm_absent;
   BOOST_STATIC_CONSTEXPR bool has_denorm_loss = false;
   BOOST_STATIC_CONSTEXPR number_type infinity() noexcept 
   { 
      // returns epsilon/2
      initializer.do_nothing();
      static std::pair<bool, number_type> value;
      if(!value.first)
      {
         value.first = true;
         value.second = 1;
         mpfr_set_inf(value.second.backend().data(), 1);
      }
      return value.second;
   }
   BOOST_STATIC_CONSTEXPR number_type quiet_NaN() noexcept 
   { 
      // returns epsilon/2
      initializer.do_nothing();
      static std::pair<bool, number_type> value;
      if(!value.first)
      {
         value.first = true;
         value.second = 1;
         mpfr_set_nan(value.second.backend().data());
      }
      return value.second;
   }
   BOOST_STATIC_CONSTEXPR number_type signaling_NaN() noexcept 
   { 
      return number_type(0); 
   }
   BOOST_STATIC_CONSTEXPR number_type denorm_min() noexcept { return number_type(0); }
   BOOST_STATIC_CONSTEXPR bool is_iec559 = false;
   BOOST_STATIC_CONSTEXPR bool is_bounded = true;
   BOOST_STATIC_CONSTEXPR bool is_modulo = false;
   BOOST_STATIC_CONSTEXPR bool traps = true;
   BOOST_STATIC_CONSTEXPR bool tinyness_before = false;
   BOOST_STATIC_CONSTEXPR float_round_style round_style = round_to_nearest;

private:
   struct data_initializer
   {
      data_initializer()
      {
         std::numeric_limits<boost::multiprecision::mp_number<boost::multiprecision::mpfr_real_backend<digits10> > >::epsilon();
         std::numeric_limits<boost::multiprecision::mp_number<boost::multiprecision::mpfr_real_backend<digits10> > >::round_error();
         (std::numeric_limits<boost::multiprecision::mp_number<boost::multiprecision::mpfr_real_backend<digits10> > >::min)();
         (std::numeric_limits<boost::multiprecision::mp_number<boost::multiprecision::mpfr_real_backend<digits10> > >::max)();
         std::numeric_limits<boost::multiprecision::mp_number<boost::multiprecision::mpfr_real_backend<digits10> > >::infinity();
         std::numeric_limits<boost::multiprecision::mp_number<boost::multiprecision::mpfr_real_backend<digits10> > >::quiet_NaN();
      }
      void do_nothing()const{}
   };
   static const data_initializer initializer;
};

template<unsigned Digits10> 
const typename numeric_limits<boost::multiprecision::mp_number<boost::multiprecision::mpfr_real_backend<Digits10> > >::data_initializer numeric_limits<boost::multiprecision::mp_number<boost::multiprecision::mpfr_real_backend<Digits10> > >::initializer;

template<> 
class numeric_limits<boost::multiprecision::mp_number<boost::multiprecision::mpfr_real_backend<0> > >
{
   typedef boost::multiprecision::mp_number<boost::multiprecision::mpfr_real_backend<0> > number_type;
public:
   BOOST_STATIC_CONSTEXPR bool is_specialized = false;
   BOOST_STATIC_CONSTEXPR number_type (min)() noexcept { return number_type(0); }
   BOOST_STATIC_CONSTEXPR number_type (max)() noexcept { return number_type(0); }
   BOOST_STATIC_CONSTEXPR number_type lowest() noexcept { return number_type(0); }
   BOOST_STATIC_CONSTEXPR int digits = 0;
   BOOST_STATIC_CONSTEXPR int digits10 = 0;
   BOOST_STATIC_CONSTEXPR int max_digits10 = 0;
   BOOST_STATIC_CONSTEXPR bool is_signed = false;
   BOOST_STATIC_CONSTEXPR bool is_integer = false;
   BOOST_STATIC_CONSTEXPR bool is_exact = false;
   BOOST_STATIC_CONSTEXPR int radix = 0;
   BOOST_STATIC_CONSTEXPR number_type epsilon() noexcept { return number_type(0); }
   BOOST_STATIC_CONSTEXPR number_type round_error() noexcept { return number_type(0); }
   BOOST_STATIC_CONSTEXPR int min_exponent = 0;
   BOOST_STATIC_CONSTEXPR int min_exponent10 = 0;
   BOOST_STATIC_CONSTEXPR int max_exponent = 0;
   BOOST_STATIC_CONSTEXPR int max_exponent10 = 0;
   BOOST_STATIC_CONSTEXPR bool has_infinity = false;
   BOOST_STATIC_CONSTEXPR bool has_quiet_NaN = false;
   BOOST_STATIC_CONSTEXPR bool has_signaling_NaN = false;
   BOOST_STATIC_CONSTEXPR float_denorm_style has_denorm = denorm_absent;
   BOOST_STATIC_CONSTEXPR bool has_denorm_loss = false;
   BOOST_STATIC_CONSTEXPR number_type infinity() noexcept { return number_type(0); }
   BOOST_STATIC_CONSTEXPR number_type quiet_NaN() noexcept { return number_type(0); }
   BOOST_STATIC_CONSTEXPR number_type signaling_NaN() noexcept { return number_type(0); }
   BOOST_STATIC_CONSTEXPR number_type denorm_min() noexcept { return number_type(0); }
   BOOST_STATIC_CONSTEXPR bool is_iec559 = false;
   BOOST_STATIC_CONSTEXPR bool is_bounded = false;
   BOOST_STATIC_CONSTEXPR bool is_modulo = false;
   BOOST_STATIC_CONSTEXPR bool traps = false;
   BOOST_STATIC_CONSTEXPR bool tinyness_before = false;
   BOOST_STATIC_CONSTEXPR float_round_style round_style = round_toward_zero;
};

#ifdef noexcept
#undef noexcept
#endif

} // namespace std
#endif
