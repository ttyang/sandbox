///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2002 - 2011.
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469
//

#ifndef BOOST_MP_EFX_BACKEND_HPP
#define BOOST_MP_EFX_BACKEND_HPP

#include <boost/cstdint.hpp>
#include <boost/array.hpp>
#include <boost/multiprecision/mp_number.hpp>

//
// Headers required for Boost.Math integration:
//
#include <boost/math/policies/policy.hpp>

namespace boost{
namespace multiprecision{

template <unsigned Digits10>
class mp_float
{
public:
   typedef mpl::list<long long>                    signed_types;
   typedef mpl::list<unsigned long long>           unsigned_types;
   typedef mpl::list<long double>                  real_types;
   typedef boost::int64_t                          exponent_type;


   static const boost::int32_t mp_radix        = 10;
   static const boost::int32_t mp_float_digits = Digits10;

   static const boost::int32_t mp_float_digits10_setting = Digits10;
   static const boost::int32_t mp_float_digits10_limit   = boost::integer_traits<boost::int32_t>::const_max;
   static const boost::int32_t mp_float_digits10         = ((mp_float_digits10_setting < static_cast<boost::int32_t>(30)) ? static_cast<boost::int32_t>(30) : ((mp_float_digits10_setting > mp_float_digits10_limit) ? mp_float_digits10_limit : mp_float_digits10_setting));
   static const boost::int32_t mp_float_digits10_extra   = static_cast<boost::int32_t>(((static_cast<boost::int64_t>(mp_float_digits10) * 15LL) + 50LL) / 100LL);
   static const boost::int32_t mp_float_max_digits10     = static_cast<boost::int32_t>(mp_float_digits10 + ((mp_float_digits10_extra < static_cast<boost::int32_t>(5)) ? static_cast<boost::int32_t>(5) : ((mp_float_digits10_extra > static_cast<boost::int32_t>(30)) ? static_cast<boost::int32_t>(30) : mp_float_digits10_extra)));
   static const boost::int64_t mp_float_max_exp   = static_cast<boost::int64_t>(+9223372036854775795LL);
   static const boost::int64_t mp_float_min_exp   = static_cast<boost::int64_t>(-9223372036854775795LL);
   static const boost::int64_t mp_float_max_exp10 = static_cast<boost::int64_t>(+3063937869882635616LL); // Approx. [mp_float_max_exp / log10(2)], also an even multiple of 8
   static const boost::int64_t mp_float_min_exp10 = static_cast<boost::int64_t>(-3063937869882635616LL);
   static const boost::int32_t mp_elem_digits10   = static_cast<boost::int32_t>(8);

private:
   static const boost::int32_t mp_float_digits10_num_base = static_cast<boost::int32_t>((mp_float_max_digits10 / mp_elem_digits10) + (((mp_float_max_digits10 % mp_elem_digits10) != 0) ? 1 : 0));
   static const boost::int32_t mp_elem_number       = static_cast<boost::int32_t>(mp_float_digits10_num_base + 2);
   static const boost::int32_t mp_elem_mask = static_cast<boost::int32_t>(100000000);

   typedef enum enum_fpclass
   {
      mp_finite,
      mp_inf,
      mp_NaN
   }
   t_fpclass;

   typedef boost::array<boost::uint32_t, mp_elem_number> array_type;

   array_type          data;
   boost::int64_t      exp;
   bool                neg;
   t_fpclass           fpclass;
   boost::int32_t      prec_elem;

   //
   // Special values constructor:
   //
   mp_float(t_fpclass c) : 
      data(),
      exp      (static_cast<boost::int64_t>(0)),
      neg      (false),
      fpclass  (c),
      prec_elem(mp_elem_number) { }

      //
      // Static data initializer:
      //
      struct initializer
      {
         initializer()
         {
            mp_float<Digits10>::nan();
            mp_float<Digits10>::inf();
            (mp_float<Digits10>::min)();
            (mp_float<Digits10>::max)();
            mp_float<Digits10>::zero();
            mp_float<Digits10>::one();
            mp_float<Digits10>::two();
            mp_float<Digits10>::half();
            mp_float<Digits10>::double_min();
            mp_float<Digits10>::double_max();
            mp_float<Digits10>::long_double_max();
            mp_float<Digits10>::long_double_min();
            mp_float<Digits10>::long_long_max();
            mp_float<Digits10>::long_long_min();
            mp_float<Digits10>::ulong_long_max();
            mp_float<Digits10>::eps();
            mp_float<Digits10>::pow2(0);
         }
         void do_nothing(){}
      };

      static initializer init;

public:
   // Constructors
   mp_float() : 
      data(),
      exp      (static_cast<boost::int64_t>(0)),
      neg      (false),
      fpclass  (mp_finite),
      prec_elem(mp_elem_number) { }

   mp_float(const char* s) : 
      data(),
      exp      (static_cast<boost::int64_t>(0)),
      neg      (false),
      fpclass  (mp_finite),
      prec_elem(mp_elem_number) 
      {
         *this = s;
      }

   template<class I>
   mp_float(I i, typename enable_if<is_unsigned<I> >::type* = 0) : 
      data(),
      exp      (static_cast<boost::int64_t>(0)),
      neg      (false),
      fpclass  (mp_finite),
      prec_elem(mp_elem_number) 
      {
         from_unsigned_long_long(i);
      }

   template <class I>
   mp_float(I i, typename enable_if<is_signed<I> >::type* = 0) : 
      data(),
      exp      (static_cast<boost::int64_t>(0)),
      neg      (false),
      fpclass  (mp_finite),
      prec_elem(mp_elem_number) 
      {
         if(i < 0)
         {
            from_unsigned_long_long(-i);
            negate();
         }
         else
            from_unsigned_long_long(i);
      }

   mp_float(const mp_float& f) : 
      data     (f.data),
      exp      (f.exp),
      neg      (f.neg),
      fpclass  (f.fpclass),
      prec_elem(f.prec_elem) { }

   template <class F>
   mp_float(const F val, typename enable_if<is_floating_point<F> >::type* = 0): 
      data(),
      exp      (static_cast<boost::int64_t>(0)),
      neg      (false),
      fpclass  (mp_finite),
      prec_elem(mp_elem_number) 
   {
      *this = val;
   }

   mp_float(const double val, long long exponent);

   // Specific special values.
   static const mp_float& nan()
   {
      static const mp_float val(mp_NaN);
      init.do_nothing();
      return val;
   }
   static const mp_float& inf()
   {
      static const mp_float val(mp_inf);
      init.do_nothing();
      return val;
   }
   static const mp_float& (max)()
   {
      init.do_nothing();
      static bool init = false;
      static const std::string str_max =   std::string("9." + std::string(static_cast<std::size_t>(mp_float_max_digits10), static_cast<char>('9')))
         + std::string("e+" + boost::lexical_cast<std::string>(mp_float_max_exp));
      static mp_float val_max;
      if(!init)
      {
         init = true;
         val_max = str_max.c_str();
      }
      return val_max;
   }

   static const mp_float& (min)()
   {
      init.do_nothing();
      static bool init = false;
      static mp_float val_min;
      if(!init)
      {
         init = true;
         val_min = std::string("1.0e" + boost::lexical_cast<std::string>(mp_float_min_exp)).c_str();
      }
      return val_min;
   }
   static const mp_float& zero()
   {
      init.do_nothing();
      static mp_float val(static_cast<unsigned long long>(0u));
      return val;
   }
   static const mp_float& one()
   {
      init.do_nothing();
      static mp_float val(static_cast<unsigned long long>(1u));
      return val;
   }
   static const mp_float& two()
   {
      init.do_nothing();
      static mp_float val(static_cast<unsigned long long>(2u));
      return val;
   }
   static const mp_float& half()
   {
      init.do_nothing();
      static mp_float val(0.5L);
      return val;
   }
   static const mp_float& double_min()
   {
      init.do_nothing();
      static mp_float val(static_cast<long double>((std::numeric_limits<double>::min)()));
      return val;
   }
   static const mp_float& double_max()
   {
      init.do_nothing();
      static mp_float val(static_cast<long double>((std::numeric_limits<double>::max)()));
      return val;
   }
   static const mp_float& long_double_min()
   {
      init.do_nothing();
      static mp_float val((std::numeric_limits<long double>::min)());
      return val;
   }
   static const mp_float& long_double_max()
   {
      init.do_nothing();
      static mp_float val((std::numeric_limits<long double>::max)());
      return val;
   }
   static const mp_float& long_long_max()
   {
      init.do_nothing();
      static mp_float val((std::numeric_limits<long long>::max)());
      return val;
   }
   static const mp_float& long_long_min()
   {
      init.do_nothing();
      static mp_float val((std::numeric_limits<long long>::min)());
      return val;
   }
   static const mp_float& ulong_long_max()
   {
      init.do_nothing();
      static mp_float val((std::numeric_limits<unsigned long long>::max)());
      return val;
   }
   static const mp_float& eps()
   {
      init.do_nothing();
      static mp_float val(1.0, 1 - Digits10);
      return val;
   }

   // Basic operations.
   mp_float& operator= (const mp_float& v)
   {
      data = v.data;
      exp = v.exp;
      neg = v.neg;
      fpclass = v.fpclass;
      prec_elem = v.prec_elem;
      return *this;
   }
   mp_float& operator= (long long v)
   {
      if(v < 0)
      {
         from_unsigned_long_long(-v);
         negate();
      }
      else
         from_unsigned_long_long(v);
      return *this;
   }
   mp_float& operator= (unsigned long long v)
   {
      from_unsigned_long_long(v);
      return *this;
   }
   mp_float& operator= (long double v);
   mp_float& operator= (const char* v)
   {
      rd_string(v);
      return *this;
   }

   mp_float& operator+=(const mp_float& v);
   mp_float& operator-=(const mp_float& v);
   mp_float& operator*=(const mp_float& v);
   mp_float& operator/=(const mp_float& v);
   
   mp_float& add_unsigned_long_long(const unsigned long long n)
   {
      mp_float t;
      t.from_unsigned_long_long(n);
      return *this += t;
   }
   mp_float& sub_unsigned_long_long(const unsigned long long n)
   {
      mp_float t;
      t.from_unsigned_long_long(n);
      return *this -= t;
   }
   mp_float& mul_unsigned_long_long(const unsigned long long n);
   mp_float& div_unsigned_long_long(const unsigned long long n);

   // Elementary primitives.
   mp_float& calculate_inv (void);
   mp_float& calculate_sqrt(void);
   void negate() 
   { 
      if(!iszero())
         neg = !neg;
   }

   // Comparison functions
   bool isnan   (void) const { return (fpclass == mp_NaN); }
   bool isinf   (void) const { return (fpclass == mp_inf); }
   bool isfinite(void) const { return (fpclass == mp_finite); }

   bool iszero (void) const
   {
      return ((fpclass == mp_finite) && (data[0u] == 0u));
   }
   bool isone  (void) const;
   bool isint  (void) const;
   bool isneg  (void) const { return neg; }

   // Operators pre-increment and pre-decrement
   mp_float& operator++(void)
   {
      return *this += one();
   }
   mp_float& operator--(void)
   {
      return *this -= one();
   }

   std::string str(unsigned digits, bool scientific)const;

   int compare(const mp_float& v)const;
   template <class V>
   int compare(const V& v)const
   {
      mp_float<Digits10> t;
      t = v;
      return compare(t);
   }

   void swap(mp_float& v)
   {
      data.swap(v.data);
      std::swap(exp, v.exp);
      std::swap(neg, v.neg);
      std::swap(fpclass, v.fpclass);
      std::swap(prec_elem, v.prec_elem);
   }

   double             extract_double            (void) const;
   long double        extract_long_double       (void) const;
   signed long long   extract_signed_long_long  (void) const;
   unsigned long long extract_unsigned_long_long(void) const;
   void               extract_parts             (double& mantissa, boost::int64_t& exponent) const;
   mp_float           extract_integer_part      (void) const;
   void precision(const boost::int32_t prec_digits)
   {
      if(prec_digits >= mp_float_digits10)
      {
         prec_elem = mp_elem_number;
      }
      else
      {
         const boost::int32_t elems = static_cast<boost::int32_t>(  static_cast<boost::int32_t>( (prec_digits + (mp_elem_digits10 / 2)) / mp_elem_digits10)
            + static_cast<boost::int32_t>(((prec_digits %  mp_elem_digits10) != 0) ? 1 : 0));

         prec_elem = (std::min)(mp_elem_number, (std::max)(elems, static_cast<boost::int32_t>(2)));
      }
   }
   static mp_float pow2(long long i);
   long long order()const
   {
      const bool bo_order_is_zero = ((!isfinite()) || (data[0] == static_cast<boost::uint32_t>(0u)));
      //
      // Binary search to find the order of the leading term:
      //
      boost::uint32_t prefix = 0;

      if(data[0] >= 100000UL)
      {
         if(data[0] >= 10000000UL)
         {
            if(data[0] >= 100000000UL)
            {
               if(data[0] >= 1000000000UL)
                  prefix = 9;
               else
                  prefix = 8;
            }
            else
               prefix = 7;
         }
         else
         {
            if(data[0] >= 1000000UL)
               prefix = 6;
            else
               prefix = 5;
         }
      }
      else
      {
         if(data[0] >= 1000UL)
         {
            if(data[0] >= 10000UL)
               prefix = 4;
            else
               prefix = 3;
         }
         else
         {
            if(data[0] >= 100)
               prefix = 2;
            else if(data[0] >= 10)
               prefix = 1;
         }
      }

      return (bo_order_is_zero ? static_cast<boost::int64_t>(0)
         : static_cast<boost::int64_t>(exp + prefix));
   }

private:
   static bool data_elem_is_non_zero_predicate(const boost::uint32_t& d) { return (d != static_cast<boost::uint32_t>(0u)); }
   static bool data_elem_is_non_nine_predicate(const boost::uint32_t& d) { return (d != static_cast<boost::uint32_t>(mp_float::mp_elem_mask - 1)); }
   static bool char_is_nonzero_predicate(const char& c) { return (c != static_cast<char>('0')); }

   void from_unsigned_long_long(const unsigned long long u);

   int cmp_data(const array_type& vd) const;

   static void mul_loop_uv(const boost::uint32_t* const u, const boost::uint32_t* const v, boost::uint32_t* const w, const boost::int32_t p);
   static boost::uint32_t mul_loop_n(boost::uint32_t* const u, boost::uint32_t n, const boost::int32_t p);
   static boost::uint32_t div_loop_n(boost::uint32_t* const u, boost::uint32_t n, const boost::int32_t p);

   bool rd_string(const char* const s);
};

template <unsigned Digits10>
typename mp_float<Digits10>::initializer mp_float<Digits10>::init;

template <unsigned Digits10>
const boost::int32_t mp_float<Digits10>::mp_radix;
template <unsigned Digits10>
const boost::int32_t mp_float<Digits10>::mp_float_digits;
template <unsigned Digits10>
const boost::int32_t mp_float<Digits10>::mp_float_digits10_setting;
template <unsigned Digits10>
const boost::int32_t mp_float<Digits10>::mp_float_digits10_limit;
template <unsigned Digits10>
const boost::int32_t mp_float<Digits10>::mp_float_digits10;
template <unsigned Digits10>
const boost::int32_t mp_float<Digits10>::mp_float_digits10_extra;
template <unsigned Digits10>
const boost::int32_t mp_float<Digits10>::mp_float_max_digits10;
template <unsigned Digits10>
const boost::int64_t mp_float<Digits10>::mp_float_max_exp;
template <unsigned Digits10>
const boost::int64_t mp_float<Digits10>::mp_float_min_exp;
template <unsigned Digits10>
const boost::int64_t mp_float<Digits10>::mp_float_max_exp10;
template <unsigned Digits10>
const boost::int64_t mp_float<Digits10>::mp_float_min_exp10;
template <unsigned Digits10>
const boost::int32_t mp_float<Digits10>::mp_elem_digits10;
template <unsigned Digits10>
const boost::int32_t mp_float<Digits10>::mp_float_digits10_num_base;
template <unsigned Digits10>
const boost::int32_t mp_float<Digits10>::mp_elem_number;
template <unsigned Digits10>
const boost::int32_t mp_float<Digits10>::mp_elem_mask;


template <unsigned Digits10>
mp_float<Digits10>& mp_float<Digits10>::operator+=(const mp_float<Digits10>& v)
{
   if(isnan())
   {
      return *this;
   }

   if(isinf())
   {
      if(v.isinf() && (isneg() != v.isneg()))
      {
         *this = nan();
      }
      return *this;
   }

   if(iszero())
   {
      return operator=(v);
   }

   // Get the offset for the add/sub operation.
   static const boost::int64_t max_delta_exp = static_cast<boost::int64_t>((mp_elem_number - 1) * mp_elem_digits10);

   const boost::int64_t ofs_exp = static_cast<boost::int64_t>(exp - v.exp);

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

   typename array_type::iterator       p_u    =   data.begin();
   typename array_type::const_iterator p_v    = v.data.begin();
   bool                       b_copy = false;
   const boost::int32_t       ofs    = static_cast<boost::int32_t>(static_cast<boost::int32_t>(ofs_exp) / mp_elem_digits10);
   array_type                 n_data;

   if(neg == v.neg)
   {
      // Add v to *this, where the data array of either *this or v
      // might have to be treated with a positive, negative or zero offset.
      // The result is stored in *this. The data are added one element
      // at a time, each element with carry.
      if(ofs >= static_cast<boost::int32_t>(0))
      {
         std::copy(v.data.begin(), v.data.end() - static_cast<size_t>(ofs), n_data.begin() + static_cast<size_t>(ofs));
         std::fill(n_data.begin(), n_data.begin() + static_cast<size_t>(ofs), static_cast<boost::uint32_t>(0u));
         p_v = n_data.begin();
      }
      else
      {
         std::copy(data.begin(), data.end() - static_cast<size_t>(-ofs), n_data.begin() + static_cast<size_t>(-ofs));
         std::fill(n_data.begin(), n_data.begin() + static_cast<size_t>(-ofs), static_cast<boost::uint32_t>(0u));
         p_u = n_data.begin();
         b_copy = true;
      }

      // Addition algorithm
      boost::uint32_t carry = static_cast<boost::uint32_t>(0u);

      for(boost::int32_t j = static_cast<boost::int32_t>(mp_elem_number - static_cast<boost::int32_t>(1)); j >= static_cast<boost::int32_t>(0); j--)
      {
         boost::uint32_t t = static_cast<boost::uint32_t>(static_cast<boost::uint32_t>(p_u[j] + p_v[j]) + carry);
         carry    = t / static_cast<boost::uint32_t>(mp_elem_mask);
         p_u[j]   = static_cast<boost::uint32_t>(t - static_cast<boost::uint32_t>(carry * static_cast<boost::uint32_t>(mp_elem_mask)));
      }

      if(b_copy)
      {
         data = n_data;
         exp  = v.exp;
      }

      // There needs to be a carry into the element -1 of the array data
      if(carry != static_cast<boost::uint32_t>(0u))
      {
         std::copy_backward(data.begin(), data.end() - static_cast<std::size_t>(1u), data.end());
         data[0] = carry;
         exp += static_cast<boost::int64_t>(mp_elem_digits10);
      }
   }
   else
   {
      // Subtract v from *this, where the data array of either *this or v
      // might have to be treated with a positive, negative or zero offset.
      if((ofs > static_cast<boost::int32_t>(0))
         || (   (ofs == static_cast<boost::int32_t>(0))
         && (cmp_data(v.data) > static_cast<boost::int32_t>(0)))
         )
      {
         // In this case, |u| > |v| and ofs is positive.
         // Copy the data of v, shifted down to a lower value
         // into the data array m_n. Set the operand pointer p_v
         // to point to the copied, shifted data m_n.
         std::copy(v.data.begin(), v.data.end() - static_cast<size_t>(ofs), n_data.begin() + static_cast<size_t>(ofs));
         std::fill(n_data.begin(), n_data.begin() + static_cast<size_t>(ofs), static_cast<boost::uint32_t>(0u));
         p_v = n_data.begin();
      }
      else
      {
         if(ofs != static_cast<boost::int32_t>(0))
         {
            // In this case, |u| < |v| and ofs is negative.
            // Shift the data of u down to a lower value.
            std::copy_backward(data.begin(), data.end() - static_cast<size_t>(-ofs), data.end());
            std::fill(data.begin(), data.begin() + static_cast<size_t>(-ofs), static_cast<boost::uint32_t>(0u));
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

      boost::int32_t j;

      // Subtraction algorithm
      boost::int32_t borrow = static_cast<boost::int32_t>(0);

      for(j = static_cast<boost::int32_t>(mp_elem_number - static_cast<boost::int32_t>(1)); j >= static_cast<boost::int32_t>(0); j--)
      {
         boost::int32_t t = static_cast<boost::int32_t>(static_cast<boost::int32_t>(  static_cast<boost::int32_t>(p_u[j])
            - static_cast<boost::int32_t>(p_v[j])) - borrow);

         // Underflow? Borrow?
         if(t < static_cast<boost::int32_t>(0))
         {
            // Yes, underflow and borrow
            t     += static_cast<boost::int32_t>(mp_elem_mask);
            borrow = static_cast<boost::int32_t>(1);
         }
         else
         {
            borrow = static_cast<boost::int32_t>(0);
         }

         p_u[j] = static_cast<boost::uint32_t>(static_cast<boost::uint32_t>(t) % static_cast<boost::uint32_t>(mp_elem_mask));
      }

      if(b_copy)
      {
         data = n_data;
         exp  = v.exp;
         neg  = v.neg;
      }

      // Is it necessary to justify the data?
      const typename array_type::const_iterator first_nonzero_elem = std::find_if(data.begin(), data.end(), data_elem_is_non_zero_predicate);

      if(first_nonzero_elem != data.begin())
      {
         if(first_nonzero_elem == data.end())
         {
            // This result of the subtraction is exactly zero.
            // Reset the sign and the exponent.
            neg = false;
            exp = static_cast<boost::int64_t>(0);
         }
         else
         {
            // Justify the data
            const std::size_t sj = static_cast<std::size_t>(std::distance<typename array_type::const_iterator>(data.begin(), first_nonzero_elem));

            std::copy(data.begin() + static_cast<std::size_t>(sj), data.end(), data.begin());
            std::fill(data.end() - sj, data.end(), static_cast<boost::uint32_t>(0u));

            exp -= static_cast<boost::int64_t>(sj * static_cast<std::size_t>(mp_elem_digits10));
         }
      }
   }

   // Check for underflow.
   if(iszero()) 
   { 
      return *this = zero();
   }

   bool overflow = exp >= mp_float_max_exp;
   if(exp == mp_float_max_exp)
   {
      // Check to see if we really truely have an overflow or not...
      if(isneg())
      {
         mp_float t(*this);
         t.negate();
         overflow = t.compare((max)()) > 0;
      }
      else
      {
         overflow = compare((max)()) > 0;
      }
   }

   // Check for overflow.
   if(overflow)
   {
      const bool b_result_is_neg = neg;

      *this = inf();
      if(b_result_is_neg)
         negate();
   }

   return *this;
}

template <unsigned Digits10>
mp_float<Digits10>& mp_float<Digits10>::operator-=(const mp_float<Digits10>& v)
{
   // Use *this - v = -(-*this + v).
   negate();
   *this += v;
   negate();
   return *this;
}

template <unsigned Digits10>
mp_float<Digits10>& mp_float<Digits10>::operator*=(const mp_float<Digits10>& v)
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
      *this = nan();
      return *this;
   }

   if(b_u_is_inf || b_v_is_inf)
   {
      *this = inf();
      if(b_result_is_neg)
         negate();
      return *this;
   }

   if(b_u_is_zero || b_v_is_zero)
   {
      return *this = zero();
   }

   // Check for overflow or underflow.
   const bool u_exp_is_neg =   (exp < static_cast<boost::int64_t>(0));
   const bool v_exp_is_neg = (v.exp < static_cast<boost::int64_t>(0));

   if(u_exp_is_neg == v_exp_is_neg)
   {
      // Get the unsigned base-10 exponents of *this and v and...
      const boost::int64_t u_exp = ((!u_exp_is_neg) ?   exp : static_cast<boost::int64_t>(  -exp));
      const boost::int64_t v_exp = ((!v_exp_is_neg) ? v.exp : static_cast<boost::int64_t>(-v.exp));

      // Check the range of the upcoming multiplication.
      const bool b_result_is_out_of_range = (v_exp >= static_cast<boost::int64_t>(mp_float_max_exp10 - u_exp));

      if(b_result_is_out_of_range)
      {
         if(u_exp_is_neg)
         {
            *this = zero();
         }
         else
         {
            *this = inf();
            if(b_result_is_neg)
               negate();
         }
         return *this;
      }
   }

   // Set the exponent of the result.
   exp += v.exp;

   boost::array<boost::uint32_t, static_cast<std::size_t>(mp_elem_number + static_cast<boost::int32_t>(1))> w = {{ 0u }};

   mul_loop_uv(data.data(), v.data.data(), w.data(), (std::min)(prec_elem, v.prec_elem));

   // Copy the multiplication data into the result.
   // Shift the result and adjust the exponent if necessary.
   if(w[static_cast<std::size_t>(0u)] != static_cast<boost::uint32_t>(0u))
   {
      exp += static_cast<boost::int64_t>(mp_elem_digits10);

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

template <unsigned Digits10>
mp_float<Digits10>& mp_float<Digits10>::operator/=(const mp_float<Digits10>& v)
{
   const bool u_and_v_are_finite_and_identical = (   isfinite()
      && (fpclass == v.fpclass)
      && (exp     == v.exp)
      && (cmp_data(v.data) == static_cast<boost::int32_t>(0)));

   if(u_and_v_are_finite_and_identical)
   {
      *this = one();
      if(neg != v.neg)
         negate();
      return *this;
   }
   else
   {
      mp_float t(v);
      t.calculate_inv();
      return operator*=(t);
   }
}

template <unsigned Digits10>
mp_float<Digits10>& mp_float<Digits10>::mul_unsigned_long_long(const unsigned long long n)
{
   // Multiply *this with a constant unsigned long long.

   // Evaluate the sign of the result.
   const bool b_neg = neg;

   // Artificially set the sign of the result to be positive.
   neg = false;

   // Handle special cases like zero, inf and NaN.
   const bool b_u_is_inf  = isinf();
   const bool b_n_is_zero = (n == static_cast<boost::int32_t>(0));

   if(isnan() || (b_u_is_inf && b_n_is_zero))
   {
      return (*this = nan());
   }

   if(b_u_is_inf)
   {
      *this = inf();
      if(b_neg)
         negate();
      return *this;
   }

   if(iszero() || b_n_is_zero)
   {
      // Multiplication by zero.
      return *this = zero();
   }

   if(n >= static_cast<unsigned long long>(mp_elem_mask))
   {
      neg = b_neg;
      mp_float t;
      t = n;
      return operator*=(t);
   }

   if(n == static_cast<unsigned long long>(1u))
   {
      neg = b_neg;
      return *this;
   }

   // Set up the multiplication loop.
   const boost::uint32_t nn = static_cast<boost::uint32_t>(n);
   const boost::uint32_t carry = mul_loop_n(data.data(), nn, prec_elem);

   // Handle the carry and adjust the exponent.
   if(carry != static_cast<boost::uint32_t>(0u))
   {
      exp += static_cast<boost::int64_t>(mp_elem_digits10);

      // Shift the result of the multiplication one element to the right.
      std::copy_backward(data.begin(),
         data.begin() + static_cast<std::size_t>(prec_elem - static_cast<boost::int32_t>(1)),
         data.begin() + static_cast<std::size_t>(prec_elem));

      data.front() = static_cast<boost::uint32_t>(carry);
   }

   bool overflow = exp >= mp_float_max_exp;
   if(exp == mp_float_max_exp)
   {
      // Check to see if we really truely have an overflow or not...
      if(isneg())
      {
         mp_float t(*this);
         t.negate();
         overflow = t.compare((max)()) > 0;
      }
      else
      {
         overflow = compare((max)()) > 0;
      }
   }

   if(overflow)
   {
      *this = inf();
      if(b_neg)
         negate();
      return *this;
   }

   // Set the sign.
   neg = b_neg;

   return *this;
}

template <unsigned Digits10>
mp_float<Digits10>& mp_float<Digits10>::div_unsigned_long_long(const unsigned long long n)
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
      *this = inf();
      if(b_neg)
         negate();
      return *this;
   }

   if(n == static_cast<unsigned long long>(0u))
   {
      // Divide by 0.
      if(iszero())
      {
         *this = nan();
         return *this;
      }
      else
      {
         *this = inf();
         if(isneg())
            negate();
         return *this;
      }
   }

   if(iszero())
   {
      return *this;
   }

   if(n >= static_cast<unsigned long long>(mp_elem_mask))
   {
      neg = b_neg;
      mp_float t;
      t = n;
      return operator/=(t);
   }

   const boost::uint32_t nn = static_cast<boost::uint32_t>(n);

   if(nn > static_cast<boost::uint32_t>(1u))
   {
      // Do the division loop.
      const boost::uint32_t prev = div_loop_n(data.data(), nn, prec_elem);

      // Determine if one leading zero is in the result data.
      if(data[0] == static_cast<boost::uint32_t>(0u))
      {
         // Adjust the exponent
         exp -= static_cast<boost::int64_t>(mp_elem_digits10);

         // Shift result of the division one element to the left.
         std::copy(data.begin() + static_cast<std::size_t>(1u),
            data.begin() + static_cast<std::size_t>(prec_elem - static_cast<boost::int32_t>(1)),
            data.begin());

         data[prec_elem - static_cast<boost::int32_t>(1)] = static_cast<boost::uint32_t>(static_cast<boost::uint64_t>(prev * static_cast<boost::uint64_t>(mp_elem_mask)) / nn);
      }
   }

   // Check for underflow.
   if(iszero()) 
   {
      return *this = zero();
   }

   // Set the sign of the result.
   neg = b_neg;

   return *this; 
}

template <unsigned Digits10>
mp_float<Digits10>& mp_float<Digits10>::calculate_inv()
{
   // Compute the inverse of *this.
   const bool b_neg = neg;

   neg = false;

   // Handle special cases like zero, inf and NaN.
   if(iszero())
   {
      *this = inf();
      if(b_neg)
         negate();
      return *this;
   }

   if(isnan())
   {
      return *this;
   }

   if(isinf())
   {
      return *this = zero();
   }

   if(isone())
   {
      if(b_neg)
         negate();
      return *this;
   }

   // Save the original *this.
   mp_float<Digits10> x(*this);

   // Generate the initial estimate using division.
   // Extract the mantissa and exponent for a "manual"
   // computation of the estimate.
   double dd;
   boost::int64_t  ne;
   x.extract_parts(dd, ne);

   // Do the inverse estimate using double precision estimates of mantissa and exponent.
   operator=(mp_float<Digits10>(1.0 / dd, -ne));

   // Compute the inverse of *this. Quadratically convergent Newton-Raphson iteration
   // is used. During the iterative steps, the precision of the calculation is limited
   // to the minimum required in order to minimize the run-time.

   static const boost::int32_t double_digits10_minus_one = static_cast<boost::int32_t>(static_cast<boost::int32_t>(Digits10) - static_cast<boost::int32_t>(1));

   for(boost::uint32_t digits = double_digits10_minus_one; digits <= Digits10; digits *= static_cast<boost::int32_t>(2))
   {
      // Adjust precision of the terms.
      precision(static_cast<boost::int32_t>(digits * static_cast<boost::int32_t>(2)));
      x.precision(static_cast<boost::int32_t>(digits * static_cast<boost::int32_t>(2)));

      // Next iteration.
      mp_float t(*this);
      t *= x;
      t -= two();
      t.negate();
      *this *= t;
   }

   neg = b_neg;

   prec_elem = mp_elem_number;

   return *this;
}

template <unsigned Digits10>
mp_float<Digits10>& mp_float<Digits10>::calculate_sqrt(void)
{
   // Compute the square root of *this.

   if(isneg() || (!isfinite()))
   {
      *this = nan();
      return *this;
   }

   if(iszero() || isone())
   {
      return *this;
   }

   // Save the original *this.
   mp_float<Digits10> x(*this);

   // Generate the initial estimate using division.
   // Extract the mantissa and exponent for a "manual"
   // computation of the estimate.
   double dd;
   boost::int64_t  ne;
   extract_parts(dd, ne);

   // Force the exponent to be an even multiple of two.
   if((ne % static_cast<boost::int64_t>(2)) != static_cast<boost::int64_t>(0))
   {
      ++ne;
      dd /= 10.0;
   }

   // Setup the iteration.
   // Estimate the square root using simple manipulations.
   const double sqd = std::sqrt(dd);

   *this = mp_float<Digits10>(sqd, static_cast<boost::int64_t>(ne / static_cast<boost::int64_t>(2)));

   // Estimate 1.0 / (2.0 * x0) using simple manipulations.
   mp_float<Digits10> vi(0.5 / sqd, static_cast<boost::int64_t>(-ne / static_cast<boost::int64_t>(2)));

   // Compute the square root of x. Coupled Newton iteration
   // as described in "Pi Unleashed" is used. During the
   // iterative steps, the precision of the calculation is
   // limited to the minimum required in order to minimize
   // the run-time.
   //
   // Book references:
   // http://www.jjj.de/pibook/pibook.html
   // http://www.amazon.com/exec/obidos/tg/detail/-/3540665722/qid=1035535482/sr=8-7/ref=sr_8_7/104-3357872-6059916?v=glance&n=507846

   static const boost::uint32_t double_digits10_minus_one = static_cast<boost::int32_t>(static_cast<boost::int32_t>(Digits10) - static_cast<boost::int32_t>(1));

   for(boost::uint32_t digits = double_digits10_minus_one; digits <= Digits10; digits *= 2u)
   {
      // Adjust precision of the terms.
      precision(digits * 2);
      vi.precision(digits * 2);

      // Next iteration of vi
      mp_float t(*this);
      t *= vi;
      t.negate();
      t.mul_unsigned_long_long(2u);
      t += one();
      t *= vi;
      vi += t;

      // Next iteration of *this
      t = *this;
      t *= *this;
      t.negate();
      t += x;
      t *= vi;
      *this += t;
   }

   prec_elem = mp_elem_number;

   return *this;
}

template <unsigned Digits10>
int mp_float<Digits10>::cmp_data(const array_type& vd) const
{
   // Compare the data of *this with those of v.
   //         Return +1 for *this > v
   //                 0 for *this = v
   //                -1 for *this < v

   const std::pair<typename array_type::const_iterator, typename array_type::const_iterator> mismatch_pair = std::mismatch(data.begin(), data.end(), vd.begin());

   const bool is_equal = ((mismatch_pair.first == data.end()) && (mismatch_pair.second == vd.end()));

   if(is_equal)
   {
      return 0;
   }
   else
   {
      return ((*mismatch_pair.first > *mismatch_pair.second) ? 1 : -1);
   }
}

template <unsigned Digits10>
int mp_float<Digits10>::compare(const mp_float& v) const
{
   // Compare v with *this.
   //         Return +1 for *this > v
   //                 0 for *this = v
   //                -1 for *this < v

   // Handle all non-finite cases.
   if((!isfinite()) || (!v.isfinite()))
   {
      // NaN can never equal NaN. Return an implementation-dependent
      // signed result. Also note that comparison of NaN with NaN
      // using operators greater-than or less-than is undefined.
      if(isnan() || v.isnan()) { return (isnan() ? 1 : -1); }

      if(isinf() && v.isinf())
      {
         // Both *this and v are infinite. They are equal if they have the same sign.
         // Otherwise, *this is less than v if and only if *this is negative.
         return ((neg == v.neg) ? 0 : (neg ? -1 : 1));
      }

      if(isinf())
      {
         // *this is infinite, but v is finite.
         // So negative infinite *this is less than any finite v.
         // Whereas positive infinite *this is greater than any finite v.
         return (isneg() ? -1 : 1);
      }
      else
      {
         // *this is finite, and v is infinite.
         // So any finite *this is greater than negative infinite v.
         // Whereas any finite *this is less than positive infinite v.
         return (v.neg ? 1 : -1);
      }
   }

   // And now handle all *finite* cases.
   if(iszero())
   {
      // The value of *this is zero and v is either zero or non-zero.
      return (v.iszero() ? 0
         : (v.neg ? 1 : -1));
   }
   else if(v.iszero())
   {
      // The value of v is zero and *this is non-zero.
      return (neg ? -1 : 1);
   }
   else
   {
      // Both *this and v are non-zero.

      if(neg != v.neg)
      {
         // The signs are different.
         return (neg ? -1 : 1);
      }
      else if(exp != v.exp)
      {
         // The signs are the same and the exponents are different.
         const int val_cmp_exp = ((exp < v.exp) ? 1 : -1);

         return (neg ? val_cmp_exp : -val_cmp_exp);
      }
      else
      {
         // The signs are the same and the exponents are the same.
         // Compare the data.
         const int val_cmp_data = cmp_data(v.data);

         return ((!neg) ? val_cmp_data : -val_cmp_data);
      }
   }
}

template <unsigned Digits10>
bool mp_float<Digits10>::isone() const
{
   // Check if the value of *this is identically 1 or very close to 1.

   const bool not_negative_and_is_finite = ((!neg) && isfinite());

   if(not_negative_and_is_finite)
   {
      if((data[0u] == static_cast<boost::uint32_t>(1u)) && (exp == static_cast<boost::int64_t>(0)))
      {
         const typename array_type::const_iterator it_non_zero = std::find_if(data.begin(), data.end(), data_elem_is_non_zero_predicate);
         return (it_non_zero == data.end());
      }
      else if((data[0u] == static_cast<boost::uint32_t>(mp_elem_mask - 1)) && (exp == static_cast<boost::int64_t>(-mp_elem_digits10)))
      {
         const typename array_type::const_iterator it_non_nine = std::find_if(data.begin(), data.end(), data_elem_is_non_nine_predicate);
         return (it_non_nine == data.end());
      }
   }

   return false;
}

template <unsigned Digits10>
bool mp_float<Digits10>::isint() const
{
   if(fpclass != mp_finite) { return false; }

   if(iszero()) { return true; }

   if(exp < static_cast<boost::int64_t>(0)) { return false; } // |*this| < 1.

   const typename array_type::size_type offset_decimal_part = static_cast<typename array_type::size_type>(exp / mp_elem_digits10) + 1u;

   if(offset_decimal_part >= static_cast<typename array_type::size_type>(mp_elem_number))
   {
      // The number is too large to resolve the integer part.
      // It considered to be a pure integer.
      return true;
   }

   typename array_type::const_iterator it_non_zero = std::find_if(data.begin() + offset_decimal_part, data.end(), data_elem_is_non_zero_predicate);

   return (it_non_zero == data.end());
}

template <unsigned Digits10>
void mp_float<Digits10>::extract_parts(double& mantissa, boost::int64_t& exponent) const
{
   // Extract the approximate parts mantissa and base-10 exponent from the input mp_float<Digits10> value x.

   // Extracts the mantissa and exponent.
   exponent = exp;

   boost::uint32_t p10  = static_cast<boost::uint32_t>(1u);
   boost::uint32_t test = data[0u];

   for(;;)
   {
      test /= static_cast<boost::uint32_t>(10u);

      if(test == static_cast<boost::uint32_t>(0u))
      {
         break;
      }

      p10 *= static_cast<boost::uint32_t>(10u);
      ++exponent;
   }

   mantissa =     static_cast<double>(data[0])
      +  (static_cast<double>(data[1]) / static_cast<double>(mp_elem_mask))
      + ((static_cast<double>(data[2]) / static_cast<double>(mp_elem_mask)) / static_cast<double>(mp_elem_mask));

   mantissa /= static_cast<double>(p10);

   if(neg) { mantissa = -mantissa; }
}

template <unsigned Digits10>
double mp_float<Digits10>::extract_double(void) const
{
   // Returns the double conversion of a mp_float<Digits10>.

   // Check for non-normal mp_float<Digits10>.
   if(!isfinite())
   {
      if(isnan())
      {
         return std::numeric_limits<double>::quiet_NaN();
      }
      else
      {
         return ((!neg) ?  std::numeric_limits<double>::infinity()
            : -std::numeric_limits<double>::infinity());
      }
   }

   mp_float<Digits10> xx(*this);
   if(xx.isneg())
      xx.negate();

   // Check for zero mp_float<Digits10>.
   if(iszero() || (xx.compare(double_min()) < 0))
   {
      return 0.0;
   }

   // Check if mp_float<Digits10> exceeds the maximum of double.
   if(xx.compare(double_max()) > 0)
   {
      return ((!neg) ?  std::numeric_limits<double>::infinity()
         : -std::numeric_limits<double>::infinity());
   }

   std::stringstream ss;

   ss << str(std::numeric_limits<double>::digits10 + (2 + 1), true);

   double d;
   ss >> d;

   return d;
}

template <unsigned Digits10>
long double mp_float<Digits10>::extract_long_double(void) const
{
   // Returns the long double conversion of a mp_float<Digits10>.

   // Check for non-normal mp_float<Digits10>.
   if(!isfinite())
   {
      if(isnan())
      {
         return std::numeric_limits<long double>::quiet_NaN();
      }
      else
      {
         return ((!neg) ?  std::numeric_limits<long double>::infinity()
            : -std::numeric_limits<long double>::infinity());
      }
   }

   mp_float<Digits10> xx(*this);
   if(xx.isneg())
      xx.negate();

   // Check for zero mp_float<Digits10>.
   if(iszero() || (xx.compare(long_double_min()) < 0))
   {
      return static_cast<long double>(0.0);
   }

   // Check if mp_float<Digits10> exceeds the maximum of double.
   if(xx.compare(long_double_max()) > 0)
   {
      return ((!neg) ?  std::numeric_limits<long double>::infinity()
         : -std::numeric_limits<long double>::infinity());
   }

   std::stringstream ss;

   ss << str(std::numeric_limits<long double>::digits10 + (2 + 1), true);

   long double ld;
   ss >> ld;

   return ld;
}

template <unsigned Digits10>
signed long long mp_float<Digits10>::extract_signed_long_long(void) const
{
   // Extracts a signed long long from *this.
   // If (x > maximum of signed long long) or (x < minimum of signed long long),
   // then the maximum or minimum of signed long long is returned accordingly.

   if(exp < static_cast<boost::int64_t>(0))
   {
      return static_cast<signed long long>(0);
   }

   const bool b_neg = isneg();

   unsigned long long val;

   if((!b_neg) && (compare(long_long_max()) > 0))
   {
      return (std::numeric_limits<signed long long>::max)();
   }
   else if(b_neg &&  (compare(long_long_min()) < 0))
   {
      return (std::numeric_limits<signed long long>::min)();
   }
   else
   {
      // Extract the data into an unsigned long long value.
      mp_float<Digits10> xn(extract_integer_part());
      if(xn.isneg())
         xn.negate();

      val = static_cast<unsigned long long>(xn.data[0]);

      const boost::int32_t imax = (std::min)(static_cast<boost::int32_t>(static_cast<boost::int32_t>(xn.exp) / mp_elem_digits10), static_cast<boost::int32_t>(mp_elem_number - static_cast<boost::int32_t>(1)));

      for(boost::int32_t i = static_cast<boost::int32_t>(1); i <= imax; i++)
      {
         val *= static_cast<unsigned long long>(mp_elem_mask);
         val += static_cast<unsigned long long>(xn.data[i]);
      }
   }

   return ((!b_neg) ? static_cast<signed long long>(val) : static_cast<signed long long>(-static_cast<signed long long>(val)));
}

template <unsigned Digits10>
unsigned long long mp_float<Digits10>::extract_unsigned_long_long(void) const
{
   // Extracts an unsigned long long from *this.
   // If x exceeds the maximum of unsigned long long,
   // then the maximum of unsigned long long is returned.
   // If x is negative, then the unsigned long long cast of
   // the signed long long extracted value is returned.

   if(isneg())
   {
      return static_cast<unsigned long long>(extract_signed_long_long());
   }

   if(exp < static_cast<boost::int64_t>(0))
   {
      return static_cast<unsigned long long>(0u);
   }

   const mp_float<Digits10> xn(extract_integer_part());

   unsigned long long val;

   if(xn.compare(ulong_long_max()) > 0)
   {
      return (std::numeric_limits<unsigned long long>::max)();
   }
   else
   {
      // Extract the data into an unsigned long long value.
      val = static_cast<unsigned long long>(xn.data[0]);

      const boost::int32_t imax = (std::min)(static_cast<boost::int32_t>(static_cast<boost::int32_t>(xn.exp) / mp_elem_digits10), static_cast<boost::int32_t>(mp_elem_number - static_cast<boost::int32_t>(1)));

      for(boost::int32_t i = static_cast<boost::int32_t>(1); i <= imax; i++)
      {
         val *= static_cast<unsigned long long>(mp_elem_mask);
         val += static_cast<unsigned long long>(xn.data[i]);
      }
   }

   return val;
}

template <unsigned Digits10>
mp_float<Digits10> mp_float<Digits10>::extract_integer_part(void) const
{
   // Compute the signed integer part of x.

   if(!isfinite())
   {
      return *this;
   }

   if(exp < static_cast<boost::int64_t>(0))
   {
      // The absolute value of the number is smaller than 1.
      // Thus the integer part is zero.
      return zero();
   }
   else if(exp >= Digits10 - 1)
   {
      // The number is too large to resolve the integer part.
      // Thus it is already a pure integer part.
      return *this;
   }

   // Make a local copy.
   mp_float<Digits10> x = *this;

   // Clear out the decimal portion
   const size_t first_clear = (static_cast<size_t>(x.exp) / static_cast<size_t>(mp_elem_digits10)) + 1u;
   const size_t last_clear  =  static_cast<size_t>(mp_elem_number);

   std::fill(x.data.begin() + first_clear, x.data.begin() + last_clear, static_cast<boost::uint32_t>(0u));

   return x;
}

template <unsigned Digits10>
std::string mp_float<Digits10>::str(std::size_t number_of_digits, bool scientific) const
{
   std::string str;
   boost::int64_t my_exp = order();
   if(number_of_digits == 0)
      number_of_digits = (std::numeric_limits<std::size_t>::max)();
   // Determine the number of elements needed to provide the requested digits from mp_float<Digits10>.
   const std::size_t number_of_elements = (std::min)(static_cast<std::size_t>((number_of_digits / static_cast<std::size_t>(mp_elem_digits10)) + 2u),
      static_cast<std::size_t>(mp_elem_number));

   // Extract the remaining digits from mp_float<Digits10> after the decimal point.
   str = boost::lexical_cast<std::string>(data[0]);

   // Extract all of the digits from mp_float<Digits10>, beginning with the first data element.
   for(std::size_t i = static_cast<std::size_t>(1u); i < number_of_elements; i++)
   {
      std::stringstream ss;

      ss << std::setw(static_cast<std::streamsize>(mp_elem_digits10))
         << std::setfill(static_cast<char>('0'))
         << data[i];

      str += ss.str();
   }

   // Cut the output to the size of the precision.
   if(str.length() > number_of_digits)
   {
      // Get the digit after the last needed digit for rounding
      const boost::uint32_t round = static_cast<boost::uint32_t>(static_cast<boost::uint32_t>(str.at(number_of_digits)) - static_cast<boost::uint32_t>('0'));

      // Truncate the string
      str = str.substr(static_cast<std::size_t>(0u), number_of_digits);

      if(round >= static_cast<boost::uint32_t>(5u))
      {
         std::size_t ix = static_cast<std::size_t>(str.length() - 1u);

         // Every trailing 9 must be rounded up
         while(ix && (static_cast<boost::int32_t>(str.at(ix)) - static_cast<boost::int32_t>('0') == static_cast<boost::int32_t>(9)))
         {
            str.at(ix) = static_cast<char>('0');
            --ix;
         }

         if(!ix)
         {
            // There were nothing but trailing nines.
            if(static_cast<boost::int32_t>(static_cast<boost::int32_t>(str.at(ix)) - static_cast<boost::int32_t>(0x30)) == static_cast<boost::int32_t>(9))
            {
               // Increment up to the next order and adjust exponent.
               str.at(ix) = static_cast<char>('1');
               ++my_exp;
            }
            else
            {
               // Round up this digit.
               ++str.at(ix);
            }
         }
         else
         {
            // Round up the last digit.
            ++str[ix];
         }
      }
   }
   //
   // Suppress trailing zeros:
   //
   std::string::iterator pos = str.end();
   while(pos != str.begin() && *--pos == '0'){}
   if(pos != str.end())
      ++pos;
   str.erase(pos, str.end());
   if(str.empty())
      str = '0';
   if(!scientific && (str.size() < 20) && (my_exp >= 0) && (my_exp < 20))
   {
      if(1 + my_exp > str.size())
      {
         // Just pad out the end with zeros:
         str.append(static_cast<std::string::size_type>(1 + my_exp - str.size()), '0');
      }
      else if(my_exp + 1 != str.size())
      {
         // Insert the decimal point:
         str.insert(static_cast<std::string::size_type>(my_exp + 1), 1, '.');
      }
   }
   else
   {
      // Scientific format:
      str.insert(1, 1, '.');
      if(str.size() == 2)
         str.append(1, '0');
      str.append(1, 'e');
      str.append(boost::lexical_cast<std::string>(my_exp));
   }
   if(isneg())
      str.insert(0, 1, '-');
   return str;
}

template <unsigned Digits10>
bool mp_float<Digits10>::rd_string(const char* const s)
{
   std::string str(s);

   // Get a possible exponent and remove it.
   exp = static_cast<boost::int64_t>(0);

   std::size_t pos;

   if(   ((pos = str.find('e')) != std::string::npos)
      || ((pos = str.find('E')) != std::string::npos)
      )
   {
      // Remove the exponent part from the string.
      exp = boost::lexical_cast<boost::int64_t>(static_cast<const char* const>(str.c_str() + (pos + 1u)));
      str = str.substr(static_cast<std::size_t>(0u), pos);
   }

   // Get a possible +/- sign and remove it.
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

   // Remove leading zeros for all input types.
   const std::string::iterator fwd_it_leading_zero = std::find_if(str.begin(), str.end(), char_is_nonzero_predicate);

   if(fwd_it_leading_zero != str.begin())
   {
      if(fwd_it_leading_zero == str.end())
      {
         // The string contains nothing but leading zeros.
         // This string represents zero.
         operator=(zero());
         return true;
      }
      else
      {
         str.erase(str.begin(), fwd_it_leading_zero);
      }
   }

   // Put the input string into the standard mp_float<Digits10> input form
   // aaa.bbbbE+/-n, where aa has 1...mp_elem_digits10, bbbb has an
   // even multiple of mp_elem_digits10 which are possibly zero padded
   // on the right-end, and n is a signed 32-bit integer which is an
   // even multiple of mp_elem_digits10.

   // Find a possible decimal point.
   pos = str.find(static_cast<char>('.'));

   if(pos != std::string::npos)
   {
      // Remove all trailing insignificant zeros.
      const std::string::const_reverse_iterator rit_non_zero = std::find_if(str.rbegin(), str.rend(), char_is_nonzero_predicate);

      if(rit_non_zero != str.rbegin())
      {
         const std::string::size_type ofs = str.length() - std::distance<std::string::const_reverse_iterator>(str.rbegin(), rit_non_zero);
         str.erase(str.begin() + ofs, str.end());
      }

      // Check if the input is identically zero.
      if(str == std::string("."))
      {
         operator=(zero());
         return true;
      }

      // Remove leading significant zeros just after the decimal point
      // and adjust the exponent accordingly.
      // Note that the while-loop operates only on strings of the form ".000abcd..."
      // and peels away the zeros just after the decimal point.
      if(str.at(static_cast<std::size_t>(0u)) == static_cast<char>('.'))
      {
         const std::string::iterator it_non_zero = std::find_if(str.begin() + 1u, str.end(), char_is_nonzero_predicate);

         std::size_t delta_exp = static_cast<std::size_t>(0u);

         if(str.at(static_cast<std::size_t>(1u)) == static_cast<char>('0'))
         {
            delta_exp = std::distance<std::string::const_iterator>(str.begin() + 1u, it_non_zero);
         }

         // Bring one single digit into the mantissa and adjust exponent accordingly.
         str.erase(str.begin(), it_non_zero);
         str.insert(static_cast<std::size_t>(1u), ".");
         exp -= static_cast<boost::int64_t>(delta_exp + 1u);
      }
   }
   else
   {
      // Input string has no decimal point: Append decimal point.
      str.append(".");
   }

   // Shift the decimal point such that the exponent is an even multiple of mp_elem_digits10.
   std::size_t n_shift   = static_cast<std::size_t>(0u);
   const std::size_t n_exp_rem = static_cast<std::size_t>(exp % static_cast<boost::int64_t>(mp_elem_digits10));

   if((exp % static_cast<boost::int64_t>(mp_elem_digits10)) != static_cast<boost::int64_t>(0))
   {
      n_shift = ((exp < static_cast<boost::int64_t>(0))
         ? static_cast<std::size_t>(n_exp_rem + static_cast<std::size_t>(mp_elem_digits10))
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

      exp -= static_cast<boost::int64_t>(n_shift);
   }

   // Cut the size of the mantissa to <= mp_elem_digits10.
   pos          = str.find(static_cast<char>('.'));
   pos_plus_one = static_cast<std::size_t>(pos + 1u);

   if(pos > static_cast<std::size_t>(mp_elem_digits10))
   {
      const boost::int32_t n_pos         = static_cast<boost::int32_t>(pos);
      const boost::int32_t n_rem_is_zero = ((static_cast<boost::int32_t>(n_pos % mp_elem_digits10) == static_cast<boost::int32_t>(0)) ? static_cast<boost::int32_t>(1) : static_cast<boost::int32_t>(0));
      const boost::int32_t n             = static_cast<boost::int32_t>(static_cast<boost::int32_t>(n_pos / mp_elem_digits10) - n_rem_is_zero);

      str.insert(static_cast<std::size_t>(static_cast<boost::int32_t>(n_pos - static_cast<boost::int32_t>(n * mp_elem_digits10))), ".");

      str.erase(pos_plus_one, static_cast<std::size_t>(1u));

      exp += static_cast<boost::int64_t>(static_cast<boost::int64_t>(n) * static_cast<boost::int64_t>(mp_elem_digits10));
   }

   // Pad the decimal part such that its value is an even
   // multiple of mp_elem_digits10.
   pos          = str.find(static_cast<char>('.'));
   pos_plus_one = static_cast<std::size_t>(pos + 1u);

   const boost::int32_t n_dec = static_cast<boost::int32_t>(static_cast<boost::int32_t>(str.length() - 1u) - static_cast<boost::int32_t>(pos));
   const boost::int32_t n_rem = static_cast<boost::int32_t>(n_dec % mp_elem_digits10);
   boost::int32_t n_cnt = ((n_rem != static_cast<boost::int32_t>(0)) ? static_cast<boost::int32_t>(mp_elem_digits10 - n_rem)
      : static_cast<boost::int32_t>(0));

   if(n_cnt != static_cast<boost::int32_t>(0))
   {
      str.append(static_cast<std::size_t>(n_cnt), static_cast<char>('0'));
   }

   // Truncate decimal part if it is too long.
   const std::size_t max_dec = static_cast<std::size_t>((mp_elem_number - 1) * mp_elem_digits10);

   if(static_cast<std::size_t>(str.length() - pos) > max_dec)
   {
      str = str.substr(static_cast<std::size_t>(0u),
         static_cast<std::size_t>(pos_plus_one + max_dec));
   }

   // Now the input string has the standard mp_float<Digits10> input form.
   // (See the comment above.)

   // Set all the data elements to 0.
   std::fill(data.begin(), data.end(), static_cast<boost::uint32_t>(0u));

   // Extract the data.

   // First get the digits to the left of the decimal point...
   data[0u] = boost::lexical_cast<boost::uint32_t>(str.substr(static_cast<std::size_t>(0u), pos));

   // ...then get the remaining digits to the right of the decimal point.
   const std::string::size_type i_end = ((str.length() - pos_plus_one) / static_cast<std::string::size_type>(mp_elem_digits10));

   for(std::string::size_type i = static_cast<std::string::size_type>(0u); i < i_end; i++)
   {
      const std::string::const_iterator it =   str.begin()
         + pos_plus_one
         + (i * static_cast<std::string::size_type>(mp_elem_digits10));

      data[i + 1u] = boost::lexical_cast<boost::uint32_t>(std::string(it, it + static_cast<std::string::size_type>(mp_elem_digits10)));
   }

   // Check for overflow...
   if(exp > mp_float_max_exp)
   {
      const bool b_result_is_neg = neg;

      *this = inf();
      if(b_result_is_neg)
         negate();
   }

   // ...and check for underflow.
   if(exp <= mp_float_min_exp)
   {
      if(exp == mp_float_min_exp)
      {
         // Check for identity with the minimum value.
         mp_float<Digits10> test = *this;

         test.exp = static_cast<boost::int64_t>(0);

         if(test.isone())
         {
            *this = zero();
         }
      }
      else
      {
         *this = zero();
      }
   }

   return true;
}

template <unsigned Digits10>
mp_float<Digits10>::mp_float(const double mantissa, const boost::int64_t exponent) 
 : data     (),
   exp      (static_cast<boost::int64_t>(0)),
   neg      (false),
   fpclass  (mp_finite),
   prec_elem(mp_elem_number)
{
   // Create an mp_float<Digits10> from mantissa and exponent.
   // This ctor does not maintain the full precision of double.

   const bool mantissa_is_iszero = (::fabs(mantissa) < ((std::numeric_limits<double>::min)() * (1.0 + std::numeric_limits<double>::epsilon())));

   if(mantissa_is_iszero)
   {
      std::fill(data.begin(), data.end(), static_cast<boost::uint32_t>(0u));
      return;
   }

   const bool b_neg = (mantissa < 0.0);

   double d = ((!b_neg) ? mantissa : -mantissa);
   boost::int64_t  e = exponent;

   while(d > 10.0) { d /= 10.0; ++e; }
   while(d <  1.0) { d *= 10.0; --e; }

   boost::int32_t shift = static_cast<boost::int32_t>(e % static_cast<boost::int32_t>(mp_elem_digits10));

   while(static_cast<boost::int32_t>(shift-- % mp_elem_digits10) != static_cast<boost::int32_t>(0))
   {
      d *= 10.0;
      --e;
   }

   exp = e;
   neg = b_neg;

   std::fill(data.begin(), data.end(), static_cast<boost::uint32_t>(0u));

   static const boost::int32_t digit_ratio = static_cast<boost::int32_t>(static_cast<boost::int32_t>(std::numeric_limits<double>::digits10) / static_cast<boost::int32_t>(mp_elem_digits10));
   static const boost::int32_t digit_loops = static_cast<boost::int32_t>(digit_ratio + static_cast<boost::int32_t>(2));

   for(boost::int32_t i = static_cast<boost::int32_t>(0); i < digit_loops; i++)
   {
      boost::uint32_t n = static_cast<boost::uint32_t>(static_cast<boost::uint64_t>(d));
      data[i]  = static_cast<boost::uint32_t>(n);
      d       -= static_cast<double>(n);
      d       *= static_cast<double>(mp_elem_mask);
   }
}

template <unsigned Digits10>
mp_float<Digits10>& mp_float<Digits10>::operator = (long double a)
{
   // Christopher Kormanyos's original code used a cast to long long here, but that fails
   // when long double has more digits than a long long.
   using std::frexp;
   using std::ldexp;
   using std::floor;

   if (a == 0) {
      return *this = zero();
   }

   if (a == 1) {
      return *this = one();
   }

   if((boost::math::isinf)(a))
   {
      return *this = inf();
   }
   if((boost::math::isnan)(a))
      return *this = nan();

   int e;
   long double f, term;
   *this = zero();

   f = frexp(a, &e);

   static const int shift = std::numeric_limits<int>::digits - 1;

   while(f)
   {
      // extract int sized bits from f:
      f = ldexp(f, shift);
      term = floor(f);
      e -= shift;
      *this *= pow2(shift);
      if(term > 0)
         add_unsigned_long_long(static_cast<unsigned>(term));
      else
         sub_unsigned_long_long(static_cast<unsigned>(-term));
      f -= term;
   }
   if(e != 0)
      *this *= pow2(e);
   return *this;
}

template <unsigned Digits10>
void mp_float<Digits10>::from_unsigned_long_long(const unsigned long long u)
{
   std::fill(data.begin(), data.end(), static_cast<boost::uint32_t>(0u));

   exp = static_cast<boost::int64_t>(0);
   neg = false;
   fpclass = mp_finite;
   prec_elem = mp_elem_number;

   std::size_t i =static_cast<std::size_t>(0u);

   unsigned long long uu = u;

   boost::uint32_t temp[(std::numeric_limits<unsigned long long>::digits10 / static_cast<int>(mp_elem_digits10)) + 3] = { static_cast<boost::uint32_t>(0u) };

   while(uu != static_cast<unsigned long long>(0u))
   {
      temp[i] = static_cast<boost::uint32_t>(uu % static_cast<unsigned long long>(mp_elem_mask));
      uu = static_cast<unsigned long long>(uu / static_cast<unsigned long long>(mp_elem_mask));
      ++i;
   }

   if(i > static_cast<std::size_t>(1u))
   {
      exp += static_cast<boost::int64_t>((i - 1u) * static_cast<std::size_t>(mp_elem_digits10));
   }

   std::reverse(temp, temp + i);
   std::copy(temp, temp + (std::min)(i, static_cast<std::size_t>(mp_elem_number)), data.begin());
}

template <unsigned Digits10>
void mp_float<Digits10>::mul_loop_uv(const boost::uint32_t* const u, const boost::uint32_t* const v, boost::uint32_t* const w, const boost::int32_t p)
{
   boost::uint64_t carry = static_cast<boost::uint64_t>(0u);

   for(boost::int32_t j = static_cast<boost::int32_t>(p - 1u); j >= static_cast<boost::int32_t>(0); j--)
   {
      boost::uint64_t sum = carry;

      for(boost::int32_t i = j; i >= static_cast<boost::int32_t>(0); i--)
      {
         sum += static_cast<boost::uint64_t>(u[i] * static_cast<boost::uint64_t>(v[j - i]));
      }

      w[j + 1] = static_cast<boost::uint32_t>(sum % static_cast<boost::uint32_t>(mp_elem_mask));
      carry    = static_cast<boost::uint64_t>(sum / static_cast<boost::uint32_t>(mp_elem_mask));
   }

   w[0u] = static_cast<boost::uint32_t>(carry);
}

template <unsigned Digits10>
boost::uint32_t mp_float<Digits10>::mul_loop_n(boost::uint32_t* const u, boost::uint32_t n, const boost::int32_t p)
{
   boost::uint64_t carry = static_cast<boost::uint64_t>(0u);

   // Multiplication loop.
   for(boost::int32_t j = p - 1; j >= static_cast<boost::int32_t>(0); j--)
   {
      const boost::uint64_t t = static_cast<boost::uint64_t>(carry + static_cast<boost::uint64_t>(u[j] * static_cast<boost::uint64_t>(n)));
      carry          = static_cast<boost::uint64_t>(t / static_cast<boost::uint32_t>(mp_elem_mask));
      u[j]           = static_cast<boost::uint32_t>(t - static_cast<boost::uint64_t>(static_cast<boost::uint32_t>(mp_elem_mask) * static_cast<boost::uint64_t>(carry)));
   }

   return static_cast<boost::uint32_t>(carry);
}

template <unsigned Digits10>
boost::uint32_t mp_float<Digits10>::div_loop_n(boost::uint32_t* const u, boost::uint32_t n, const boost::int32_t p)
{
   boost::uint64_t prev = static_cast<boost::uint64_t>(0u);

   for(boost::int32_t j = static_cast<boost::int32_t>(0); j < p; j++)
   {
      const boost::uint64_t t = static_cast<boost::uint64_t>(u[j] + static_cast<boost::uint64_t>(prev * static_cast<boost::uint32_t>(mp_elem_mask)));
      u[j]           = static_cast<boost::uint32_t>(t / n);
      prev           = static_cast<boost::uint64_t>(t - static_cast<boost::uint64_t>(n * static_cast<boost::uint64_t>(u[j])));
   }

   return static_cast<boost::uint32_t>(prev);
}

template <unsigned Digits10>
mp_float<Digits10> mp_float<Digits10>::pow2(const boost::int64_t p)
{
   // Create a static const table of p^2 for -128 < p < +128.
   // Note: The size of this table must be odd-numbered and
   // symmetric about 0.
   init.do_nothing();
   static const boost::array<mp_float<Digits10>, 255u> p2_data =
   {{
      mp_float("5.877471754111437539843682686111228389093327783860437607543758531392086297273635864257812500000000000e-39"),
         mp_float("1.175494350822287507968736537222245677818665556772087521508751706278417259454727172851562500000000000e-38"),
         mp_float("2.350988701644575015937473074444491355637331113544175043017503412556834518909454345703125000000000000e-38"),
         mp_float("4.701977403289150031874946148888982711274662227088350086035006825113669037818908691406250000000000000e-38"),
         mp_float("9.403954806578300063749892297777965422549324454176700172070013650227338075637817382812500000000000000e-38"),
         mp_float("1.880790961315660012749978459555593084509864890835340034414002730045467615127563476562500000000000000e-37"),
         mp_float("3.761581922631320025499956919111186169019729781670680068828005460090935230255126953125000000000000000e-37"),
         mp_float("7.523163845262640050999913838222372338039459563341360137656010920181870460510253906250000000000000000e-37"),
         mp_float("1.504632769052528010199982767644474467607891912668272027531202184036374092102050781250000000000000000e-36"),
         mp_float("3.009265538105056020399965535288948935215783825336544055062404368072748184204101562500000000000000000e-36"),
         mp_float("6.018531076210112040799931070577897870431567650673088110124808736145496368408203125000000000000000000e-36"),
         mp_float("1.203706215242022408159986214115579574086313530134617622024961747229099273681640625000000000000000000e-35"),
         mp_float("2.407412430484044816319972428231159148172627060269235244049923494458198547363281250000000000000000000e-35"),
         mp_float("4.814824860968089632639944856462318296345254120538470488099846988916397094726562500000000000000000000e-35"),
         mp_float("9.629649721936179265279889712924636592690508241076940976199693977832794189453125000000000000000000000e-35"),
         mp_float("1.925929944387235853055977942584927318538101648215388195239938795566558837890625000000000000000000000e-34"),
         mp_float("3.851859888774471706111955885169854637076203296430776390479877591133117675781250000000000000000000000e-34"),
         mp_float("7.703719777548943412223911770339709274152406592861552780959755182266235351562500000000000000000000000e-34"),
         mp_float("1.540743955509788682444782354067941854830481318572310556191951036453247070312500000000000000000000000e-33"),
         mp_float("3.081487911019577364889564708135883709660962637144621112383902072906494140625000000000000000000000000e-33"),
         mp_float("6.162975822039154729779129416271767419321925274289242224767804145812988281250000000000000000000000000e-33"),
         mp_float("1.232595164407830945955825883254353483864385054857848444953560829162597656250000000000000000000000000e-32"),
         mp_float("2.465190328815661891911651766508706967728770109715696889907121658325195312500000000000000000000000000e-32"),
         mp_float("4.930380657631323783823303533017413935457540219431393779814243316650390625000000000000000000000000000e-32"),
         mp_float("9.860761315262647567646607066034827870915080438862787559628486633300781250000000000000000000000000000e-32"),
         mp_float("1.972152263052529513529321413206965574183016087772557511925697326660156250000000000000000000000000000e-31"),
         mp_float("3.944304526105059027058642826413931148366032175545115023851394653320312500000000000000000000000000000e-31"),
         mp_float("7.888609052210118054117285652827862296732064351090230047702789306640625000000000000000000000000000000e-31"),
         mp_float("1.577721810442023610823457130565572459346412870218046009540557861328125000000000000000000000000000000e-30"),
         mp_float("3.155443620884047221646914261131144918692825740436092019081115722656250000000000000000000000000000000e-30"),
         mp_float("6.310887241768094443293828522262289837385651480872184038162231445312500000000000000000000000000000000e-30"),
         mp_float("1.262177448353618888658765704452457967477130296174436807632446289062500000000000000000000000000000000e-29"),
         mp_float("2.524354896707237777317531408904915934954260592348873615264892578125000000000000000000000000000000000e-29"),
         mp_float("5.048709793414475554635062817809831869908521184697747230529785156250000000000000000000000000000000000e-29"),
         mp_float("1.009741958682895110927012563561966373981704236939549446105957031250000000000000000000000000000000000e-28"),
         mp_float("2.019483917365790221854025127123932747963408473879098892211914062500000000000000000000000000000000000e-28"),
         mp_float("4.038967834731580443708050254247865495926816947758197784423828125000000000000000000000000000000000000e-28"),
         mp_float("8.077935669463160887416100508495730991853633895516395568847656250000000000000000000000000000000000000e-28"),
         mp_float("1.615587133892632177483220101699146198370726779103279113769531250000000000000000000000000000000000000e-27"),
         mp_float("3.231174267785264354966440203398292396741453558206558227539062500000000000000000000000000000000000000e-27"),
         mp_float("6.462348535570528709932880406796584793482907116413116455078125000000000000000000000000000000000000000e-27"),
         mp_float("1.292469707114105741986576081359316958696581423282623291015625000000000000000000000000000000000000000e-26"),
         mp_float("2.584939414228211483973152162718633917393162846565246582031250000000000000000000000000000000000000000e-26"),
         mp_float("5.169878828456422967946304325437267834786325693130493164062500000000000000000000000000000000000000000e-26"),
         mp_float("1.033975765691284593589260865087453566957265138626098632812500000000000000000000000000000000000000000e-25"),
         mp_float("2.067951531382569187178521730174907133914530277252197265625000000000000000000000000000000000000000000e-25"),
         mp_float("4.135903062765138374357043460349814267829060554504394531250000000000000000000000000000000000000000000e-25"),
         mp_float("8.271806125530276748714086920699628535658121109008789062500000000000000000000000000000000000000000000e-25"),
         mp_float("1.654361225106055349742817384139925707131624221801757812500000000000000000000000000000000000000000000e-24"),
         mp_float("3.308722450212110699485634768279851414263248443603515625000000000000000000000000000000000000000000000e-24"),
         mp_float("6.617444900424221398971269536559702828526496887207031250000000000000000000000000000000000000000000000e-24"),
         mp_float("1.323488980084844279794253907311940565705299377441406250000000000000000000000000000000000000000000000e-23"),
         mp_float("2.646977960169688559588507814623881131410598754882812500000000000000000000000000000000000000000000000e-23"),
         mp_float("5.293955920339377119177015629247762262821197509765625000000000000000000000000000000000000000000000000e-23"),
         mp_float("1.058791184067875423835403125849552452564239501953125000000000000000000000000000000000000000000000000e-22"),
         mp_float("2.117582368135750847670806251699104905128479003906250000000000000000000000000000000000000000000000000e-22"),
         mp_float("4.235164736271501695341612503398209810256958007812500000000000000000000000000000000000000000000000000e-22"),
         mp_float("8.470329472543003390683225006796419620513916015625000000000000000000000000000000000000000000000000000e-22"),
         mp_float("1.694065894508600678136645001359283924102783203125000000000000000000000000000000000000000000000000000e-21"),
         mp_float("3.388131789017201356273290002718567848205566406250000000000000000000000000000000000000000000000000000e-21"),
         mp_float("6.776263578034402712546580005437135696411132812500000000000000000000000000000000000000000000000000000e-21"),
         mp_float("1.355252715606880542509316001087427139282226562500000000000000000000000000000000000000000000000000000e-20"),
         mp_float("2.710505431213761085018632002174854278564453125000000000000000000000000000000000000000000000000000000e-20"),
         mp_float("5.421010862427522170037264004349708557128906250000000000000000000000000000000000000000000000000000000e-20"),
         mp_float("1.084202172485504434007452800869941711425781250000000000000000000000000000000000000000000000000000000e-19"),
         mp_float("2.168404344971008868014905601739883422851562500000000000000000000000000000000000000000000000000000000e-19"),
         mp_float("4.336808689942017736029811203479766845703125000000000000000000000000000000000000000000000000000000000e-19"),
         mp_float("8.673617379884035472059622406959533691406250000000000000000000000000000000000000000000000000000000000e-19"),
         mp_float("1.734723475976807094411924481391906738281250000000000000000000000000000000000000000000000000000000000e-18"),
         mp_float("3.469446951953614188823848962783813476562500000000000000000000000000000000000000000000000000000000000e-18"),
         mp_float("6.938893903907228377647697925567626953125000000000000000000000000000000000000000000000000000000000000e-18"),
         mp_float("1.387778780781445675529539585113525390625000000000000000000000000000000000000000000000000000000000000e-17"),
         mp_float("2.775557561562891351059079170227050781250000000000000000000000000000000000000000000000000000000000000e-17"),
         mp_float("5.551115123125782702118158340454101562500000000000000000000000000000000000000000000000000000000000000e-17"),
         mp_float("1.110223024625156540423631668090820312500000000000000000000000000000000000000000000000000000000000000e-16"),
         mp_float("2.220446049250313080847263336181640625000000000000000000000000000000000000000000000000000000000000000e-16"),
         mp_float("4.440892098500626161694526672363281250000000000000000000000000000000000000000000000000000000000000000e-16"),
         mp_float("8.881784197001252323389053344726562500000000000000000000000000000000000000000000000000000000000000000e-16"),
         mp_float("1.776356839400250464677810668945312500000000000000000000000000000000000000000000000000000000000000000e-15"),
         mp_float("3.552713678800500929355621337890625000000000000000000000000000000000000000000000000000000000000000000e-15"),
         mp_float("7.105427357601001858711242675781250000000000000000000000000000000000000000000000000000000000000000000e-15"),
         mp_float("1.421085471520200371742248535156250000000000000000000000000000000000000000000000000000000000000000000e-14"),
         mp_float("2.842170943040400743484497070312500000000000000000000000000000000000000000000000000000000000000000000e-14"),
         mp_float("5.684341886080801486968994140625000000000000000000000000000000000000000000000000000000000000000000000e-14"),
         mp_float("1.136868377216160297393798828125000000000000000000000000000000000000000000000000000000000000000000000e-13"),
         mp_float("2.273736754432320594787597656250000000000000000000000000000000000000000000000000000000000000000000000e-13"),
         mp_float("4.547473508864641189575195312500000000000000000000000000000000000000000000000000000000000000000000000e-13"),
         mp_float("9.094947017729282379150390625000000000000000000000000000000000000000000000000000000000000000000000000e-13"),
         mp_float("1.818989403545856475830078125000000000000000000000000000000000000000000000000000000000000000000000000e-12"),
         mp_float("3.637978807091712951660156250000000000000000000000000000000000000000000000000000000000000000000000000e-12"),
         mp_float("7.275957614183425903320312500000000000000000000000000000000000000000000000000000000000000000000000000e-12"),
         mp_float("1.455191522836685180664062500000000000000000000000000000000000000000000000000000000000000000000000000e-11"),
         mp_float("2.910383045673370361328125000000000000000000000000000000000000000000000000000000000000000000000000000e-11"),
         mp_float("5.820766091346740722656250000000000000000000000000000000000000000000000000000000000000000000000000000e-11"),
         mp_float("1.164153218269348144531250000000000000000000000000000000000000000000000000000000000000000000000000000e-10"),
         mp_float("2.328306436538696289062500000000000000000000000000000000000000000000000000000000000000000000000000000e-10"),
         mp_float("4.656612873077392578125000000000000000000000000000000000000000000000000000000000000000000000000000000e-10"),
         mp_float("9.313225746154785156250000000000000000000000000000000000000000000000000000000000000000000000000000000e-10"),
         mp_float("1.862645149230957031250000000000000000000000000000000000000000000000000000000000000000000000000000000e-9"),
         mp_float("3.725290298461914062500000000000000000000000000000000000000000000000000000000000000000000000000000000e-9"),
         mp_float("7.450580596923828125000000000000000000000000000000000000000000000000000000000000000000000000000000000e-9"),
         mp_float("1.490116119384765625000000000000000000000000000000000000000000000000000000000000000000000000000000000e-8"),
         mp_float("2.980232238769531250000000000000000000000000000000000000000000000000000000000000000000000000000000000e-8"),
         mp_float("5.960464477539062500000000000000000000000000000000000000000000000000000000000000000000000000000000000e-8"),
         mp_float("1.192092895507812500000000000000000000000000000000000000000000000000000000000000000000000000000000000e-7"),
         mp_float("2.384185791015625000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-7"),
         mp_float("4.768371582031250000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-7"),
         mp_float("9.536743164062500000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-7"),
         mp_float("1.907348632812500000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-6"),
         mp_float("3.814697265625000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-6"),
         mp_float("7.629394531250000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-6"),
         mp_float("0.000015258789062500000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
         mp_float("0.000030517578125000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
         mp_float("0.000061035156250000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
         mp_float("0.000122070312500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
         mp_float("0.000244140625000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
         mp_float("0.000488281250000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
         mp_float("0.000976562500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
         mp_float("0.001953125000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
         mp_float("0.003906250000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
         mp_float("0.007812500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
         mp_float("0.01562500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
         mp_float("0.03125000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
         mp_float("0.06250000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
         mp_float("0.125"),
         mp_float("0.25"),
         mp_float("0.5"),
         one(),
         two(),
         mp_float(static_cast<unsigned long long>(4)),
         mp_float(static_cast<unsigned long long>(8)),
         mp_float(static_cast<unsigned long long>(16)),
         mp_float(static_cast<unsigned long long>(32)),
         mp_float(static_cast<unsigned long long>(64)),
         mp_float(static_cast<unsigned long long>(128)),
         mp_float(static_cast<unsigned long long>(256)),
         mp_float(static_cast<unsigned long long>(512)),
         mp_float(static_cast<unsigned long long>(1024)),
         mp_float(static_cast<unsigned long long>(2048)),
         mp_float(static_cast<unsigned long long>(4096)),
         mp_float(static_cast<unsigned long long>(8192)),
         mp_float(static_cast<unsigned long long>(16384)),
         mp_float(static_cast<unsigned long long>(32768)),
         mp_float(static_cast<unsigned long long>(65536)),
         mp_float(static_cast<unsigned long long>(131072)),
         mp_float(static_cast<unsigned long long>(262144)),
         mp_float(static_cast<unsigned long long>(524288)),
         mp_float(static_cast<boost::uint64_t>(1uL << 20u)),
         mp_float(static_cast<boost::uint64_t>(1uL << 21u)),
         mp_float(static_cast<boost::uint64_t>(1uL << 22u)),
         mp_float(static_cast<boost::uint64_t>(1uL << 23u)),
         mp_float(static_cast<boost::uint64_t>(1uL << 24u)),
         mp_float(static_cast<boost::uint64_t>(1uL << 25u)),
         mp_float(static_cast<boost::uint64_t>(1uL << 26u)),
         mp_float(static_cast<boost::uint64_t>(1uL << 27u)),
         mp_float(static_cast<boost::uint64_t>(1uL << 28u)),
         mp_float(static_cast<boost::uint64_t>(1uL << 29u)),
         mp_float(static_cast<boost::uint64_t>(1uL << 30u)),
         mp_float(static_cast<boost::uint64_t>(1uL << 31u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 32u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 33u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 34u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 35u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 36u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 37u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 38u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 39u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 40u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 41u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 42u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 43u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 44u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 45u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 46u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 47u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 48u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 49u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 50u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 51u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 52u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 53u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 54u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 55u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 56u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 57u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 58u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 59u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 60u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 61u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 62u)),
         mp_float(static_cast<boost::uint64_t>(1uLL << 63u)),
         mp_float("1.844674407370955161600000000000000000000000000000000000000000000000000000000000000000000000000000000e19"),
         mp_float("3.689348814741910323200000000000000000000000000000000000000000000000000000000000000000000000000000000e19"),
         mp_float("7.378697629483820646400000000000000000000000000000000000000000000000000000000000000000000000000000000e19"),
         mp_float("1.475739525896764129280000000000000000000000000000000000000000000000000000000000000000000000000000000e20"),
         mp_float("2.951479051793528258560000000000000000000000000000000000000000000000000000000000000000000000000000000e20"),
         mp_float("5.902958103587056517120000000000000000000000000000000000000000000000000000000000000000000000000000000e20"),
         mp_float("1.180591620717411303424000000000000000000000000000000000000000000000000000000000000000000000000000000e21"),
         mp_float("2.361183241434822606848000000000000000000000000000000000000000000000000000000000000000000000000000000e21"),
         mp_float("4.722366482869645213696000000000000000000000000000000000000000000000000000000000000000000000000000000e21"),
         mp_float("9.444732965739290427392000000000000000000000000000000000000000000000000000000000000000000000000000000e21"),
         mp_float("1.888946593147858085478400000000000000000000000000000000000000000000000000000000000000000000000000000e22"),
         mp_float("3.777893186295716170956800000000000000000000000000000000000000000000000000000000000000000000000000000e22"),
         mp_float("7.555786372591432341913600000000000000000000000000000000000000000000000000000000000000000000000000000e22"),
         mp_float("1.511157274518286468382720000000000000000000000000000000000000000000000000000000000000000000000000000e23"),
         mp_float("3.022314549036572936765440000000000000000000000000000000000000000000000000000000000000000000000000000e23"),
         mp_float("6.044629098073145873530880000000000000000000000000000000000000000000000000000000000000000000000000000e23"),
         mp_float("1.208925819614629174706176000000000000000000000000000000000000000000000000000000000000000000000000000e24"),
         mp_float("2.417851639229258349412352000000000000000000000000000000000000000000000000000000000000000000000000000e24"),
         mp_float("4.835703278458516698824704000000000000000000000000000000000000000000000000000000000000000000000000000e24"),
         mp_float("9.671406556917033397649408000000000000000000000000000000000000000000000000000000000000000000000000000e24"),
         mp_float("1.934281311383406679529881600000000000000000000000000000000000000000000000000000000000000000000000000e25"),
         mp_float("3.868562622766813359059763200000000000000000000000000000000000000000000000000000000000000000000000000e25"),
         mp_float("7.737125245533626718119526400000000000000000000000000000000000000000000000000000000000000000000000000e25"),
         mp_float("1.547425049106725343623905280000000000000000000000000000000000000000000000000000000000000000000000000e26"),
         mp_float("3.094850098213450687247810560000000000000000000000000000000000000000000000000000000000000000000000000e26"),
         mp_float("6.189700196426901374495621120000000000000000000000000000000000000000000000000000000000000000000000000e26"),
         mp_float("1.237940039285380274899124224000000000000000000000000000000000000000000000000000000000000000000000000e27"),
         mp_float("2.475880078570760549798248448000000000000000000000000000000000000000000000000000000000000000000000000e27"),
         mp_float("4.951760157141521099596496896000000000000000000000000000000000000000000000000000000000000000000000000e27"),
         mp_float("9.903520314283042199192993792000000000000000000000000000000000000000000000000000000000000000000000000e27"),
         mp_float("1.980704062856608439838598758400000000000000000000000000000000000000000000000000000000000000000000000e28"),
         mp_float("3.961408125713216879677197516800000000000000000000000000000000000000000000000000000000000000000000000e28"),
         mp_float("7.922816251426433759354395033600000000000000000000000000000000000000000000000000000000000000000000000e28"),
         mp_float("1.584563250285286751870879006720000000000000000000000000000000000000000000000000000000000000000000000e29"),
         mp_float("3.169126500570573503741758013440000000000000000000000000000000000000000000000000000000000000000000000e29"),
         mp_float("6.338253001141147007483516026880000000000000000000000000000000000000000000000000000000000000000000000e29"),
         mp_float("1.267650600228229401496703205376000000000000000000000000000000000000000000000000000000000000000000000e30"),
         mp_float("2.535301200456458802993406410752000000000000000000000000000000000000000000000000000000000000000000000e30"),
         mp_float("5.070602400912917605986812821504000000000000000000000000000000000000000000000000000000000000000000000e30"),
         mp_float("1.014120480182583521197362564300800000000000000000000000000000000000000000000000000000000000000000000e31"),
         mp_float("2.028240960365167042394725128601600000000000000000000000000000000000000000000000000000000000000000000e31"),
         mp_float("4.056481920730334084789450257203200000000000000000000000000000000000000000000000000000000000000000000e31"),
         mp_float("8.112963841460668169578900514406400000000000000000000000000000000000000000000000000000000000000000000e31"),
         mp_float("1.622592768292133633915780102881280000000000000000000000000000000000000000000000000000000000000000000e32"),
         mp_float("3.245185536584267267831560205762560000000000000000000000000000000000000000000000000000000000000000000e32"),
         mp_float("6.490371073168534535663120411525120000000000000000000000000000000000000000000000000000000000000000000e32"),
         mp_float("1.298074214633706907132624082305024000000000000000000000000000000000000000000000000000000000000000000e33"),
         mp_float("2.596148429267413814265248164610048000000000000000000000000000000000000000000000000000000000000000000e33"),
         mp_float("5.192296858534827628530496329220096000000000000000000000000000000000000000000000000000000000000000000e33"),
         mp_float("1.038459371706965525706099265844019200000000000000000000000000000000000000000000000000000000000000000e34"),
         mp_float("2.076918743413931051412198531688038400000000000000000000000000000000000000000000000000000000000000000e34"),
         mp_float("4.153837486827862102824397063376076800000000000000000000000000000000000000000000000000000000000000000e34"),
         mp_float("8.307674973655724205648794126752153600000000000000000000000000000000000000000000000000000000000000000e34"),
         mp_float("1.661534994731144841129758825350430720000000000000000000000000000000000000000000000000000000000000000e35"),
         mp_float("3.323069989462289682259517650700861440000000000000000000000000000000000000000000000000000000000000000e35"),
         mp_float("6.646139978924579364519035301401722880000000000000000000000000000000000000000000000000000000000000000e35"),
         mp_float("1.329227995784915872903807060280344576000000000000000000000000000000000000000000000000000000000000000e36"),
         mp_float("2.658455991569831745807614120560689152000000000000000000000000000000000000000000000000000000000000000e36"),
         mp_float("5.316911983139663491615228241121378304000000000000000000000000000000000000000000000000000000000000000e36"),
         mp_float("1.063382396627932698323045648224275660800000000000000000000000000000000000000000000000000000000000000e37"),
         mp_float("2.126764793255865396646091296448551321600000000000000000000000000000000000000000000000000000000000000e37"),
         mp_float("4.253529586511730793292182592897102643200000000000000000000000000000000000000000000000000000000000000e37"),
         mp_float("8.507059173023461586584365185794205286400000000000000000000000000000000000000000000000000000000000000e37"),
         mp_float("1.701411834604692317316873037158841057280000000000000000000000000000000000000000000000000000000000000e38")
   }};

   if((p > static_cast<boost::int64_t>(-128)) && (p < static_cast<boost::int64_t>(+128)))
   {
      return p2_data[static_cast<std::size_t>(p + ((p2_data.size() - 1u) / 2u))];
   }

   // Compute and return 2^p.
   if(p < static_cast<boost::int64_t>(0))
   {
      return pow2(static_cast<boost::int64_t>(-p)).calculate_inv();
   }
   else if(p < static_cast<boost::int64_t>(std::numeric_limits<boost::uint64_t>::digits))
   {
      const boost::uint64_t p2 = static_cast<boost::uint64_t>(static_cast<boost::uint64_t>(1uLL) << p);
      return mp_float(p2);
   }
   else
   {
      mp_float<Digits10> t;
      default_ops::detail::pow_imp(t, two(), p, mpl::true_());
      return t;
   }
}


template <unsigned Digits10>
inline void add(mp_float<Digits10>& result, const mp_float<Digits10>& o)
{
   result += o;
}
template <unsigned Digits10>
inline void subtract(mp_float<Digits10>& result, const mp_float<Digits10>& o)
{
   result -= o;
}
template <unsigned Digits10>
inline void multiply(mp_float<Digits10>& result, const mp_float<Digits10>& o)
{
   result *= o;
}
template <unsigned Digits10>
inline void divide(mp_float<Digits10>& result, const mp_float<Digits10>& o)
{
   result /= o;
}

template <unsigned Digits10>
inline void add(mp_float<Digits10>& result, const unsigned long long& o)
{
   result.add_unsigned_long_long(o);
}
template <unsigned Digits10>
inline void subtract(mp_float<Digits10>& result, const unsigned long long& o)
{
   result.sub_unsigned_long_long(o);
}
template <unsigned Digits10>
inline void multiply(mp_float<Digits10>& result, const unsigned long long& o)
{
   result.mul_unsigned_long_long(o);
}
template <unsigned Digits10>
inline void divide(mp_float<Digits10>& result, const unsigned long long& o)
{
   result.div_unsigned_long_long(o);
}

template <unsigned Digits10>
inline void add(mp_float<Digits10>& result, long long o)
{
   if(o < 0)
      result.sub_unsigned_long_long(-o);
   else
      result.add_unsigned_long_long(o);
}
template <unsigned Digits10>
inline void subtract(mp_float<Digits10>& result, long long o)
{
   if(o < 0)
      result.add_unsigned_long_long(-o);
   else
      result.sub_unsigned_long_long(o);
}
template <unsigned Digits10>
inline void multiply(mp_float<Digits10>& result, long long o)
{
   if(o < 0)
   {
      result.mul_unsigned_long_long(-o);
      result.negate();
   }
   else
      result.mul_unsigned_long_long(o);
}
template <unsigned Digits10>
inline void divide(mp_float<Digits10>& result, long long o)
{
   if(o < 0)
   {
      result.div_unsigned_long_long(-o);
      result.negate();
   }
   else
      result.div_unsigned_long_long(o);
}

template <unsigned Digits10>
inline void convert_to(unsigned long long* result, const mp_float<Digits10>& val)
{
   *result = val.extract_unsigned_long_long();
}
template <unsigned Digits10>
inline void convert_to(long long* result, const mp_float<Digits10>& val)
{
   *result = val.extract_signed_long_long();
}
template <unsigned Digits10>
inline void convert_to(long double* result, mp_float<Digits10>& val)
{
   *result = val.extract_long_double();
}

//
// Non member function support:
//
template <unsigned Digits10>
inline int eval_fpclassify(const mp_float<Digits10>& x)
{
   if(x.isinf())
      return FP_INFINITE;
   if(x.isnan())
      return FP_NAN;
   if(x.iszero())
      return FP_ZERO;
   return FP_NORMAL;
}

template <unsigned Digits10>
inline void eval_abs(mp_float<Digits10>& result, const mp_float<Digits10>& x)
{
   result = x;
   if(x.isneg())
      result.negate();
}

template <unsigned Digits10>
inline void eval_fabs(mp_float<Digits10>& result, const mp_float<Digits10>& x)
{
   result = x;
   if(x.isneg())
      result.negate();
}

template <unsigned Digits10>
inline void eval_sqrt(mp_float<Digits10>& result, const mp_float<Digits10>& x)
{
   result = x;
   result.calculate_sqrt();
}

template <unsigned Digits10>
inline void eval_floor(mp_float<Digits10>& result, const mp_float<Digits10>& x)
{
   result = x;
   if(!x.isfinite() || x.isint()) 
   { 
      return; 
   }

   if(x.isneg())
      result -= mp_float<Digits10>::one();
   result = result.extract_integer_part();
}

template <unsigned Digits10>
inline void eval_ceil(mp_float<Digits10>& result, const mp_float<Digits10>& x)
{
   result = x;
   if(!x.isfinite() || x.isint()) 
   { 
      return; 
   }

   if(!x.isneg())
      result += mp_float<Digits10>::one();
   result = result.extract_integer_part();
}

template <unsigned Digits10>
inline void eval_trunc(mp_float<Digits10>& result, const mp_float<Digits10>& x)
{
   if(!x.isfinite()) 
   { 
      result = boost::math::policies::raise_rounding_error("boost::multiprecision::trunc<%1%>(%1%)", 0, mp_number<mp_float<Digits10> >(x), 0, boost::math::policies::policy<>()).backend();
      return;
   }
   else if(x.isint())
   {
      result = x;
      return;
   }
   result = x.extract_integer_part();
}

template <unsigned Digits10>
inline void eval_ldexp(mp_float<Digits10>& result, const mp_float<Digits10>& x, long long e)
{
   result = x;
   result *= mp_float<Digits10>::pow2(e);
}

template <unsigned Digits10>
inline void eval_frexp(mp_float<Digits10>& result, const mp_float<Digits10>& x, long long* e)
{
   result = x;
   if(result.isneg())
      result.negate();

   long long t = result.order();

   if(std::abs(t) > (std::numeric_limits<long long>::max)() / 3)
      throw std::runtime_error("Exponent is too large to be represented as a power of 2.");
   t *= 3;

   result *= mp_float<Digits10>::pow2(-t);

   while(result.compare(mp_float<Digits10>::one()) >= 0)
   {
      result /= mp_float<Digits10>::two();
      ++t;
   }
   while(result.compare(mp_float<Digits10>::half()) < 0)
   {
      result *= mp_float<Digits10>::two();
      --t;
   }
   *e = t;
   if(x.isneg())
      result.negate();
}

template <unsigned Digits10>
inline void eval_frexp(mp_float<Digits10>& result, const mp_float<Digits10>& x, int* e)
{
   long long t;
   eval_frexp(result, x, &t);
   if(t > (std::numeric_limits<int>::max)())
      throw std::runtime_error("Exponent is outside the range of an int");
   *e = static_cast<int>(t);
}

typedef mp_number<mp_float<50> > mp_float_50;
typedef mp_number<mp_float<100> > mp_float_100;

}}

namespace std
{
   template <unsigned Digits10> 
   class numeric_limits<boost::multiprecision::mp_number<boost::multiprecision::mp_float<Digits10> > >
   {
   public:
      static const bool                    is_specialized    = true;
      static const bool                    is_signed         = true;
      static const bool                    is_integer        = false;
      static const bool                    is_exact          = false;
      static const bool                    is_bounded        = true;
      static const bool                    is_modulo         = false;
      static const bool                    is_iec559         = false;
      static const int                     digits            = boost::multiprecision::mp_float<Digits10>::mp_float_digits;
      static const int                     digits10          = boost::multiprecision::mp_float<Digits10>::mp_float_digits10;
      static const int                     max_digits10      = boost::multiprecision::mp_float<Digits10>::mp_float_max_digits10;
      static const boost::int64_t          min_exponent      = boost::multiprecision::mp_float<Digits10>::mp_float_min_exp;      // Type differs from int.
      static const boost::int64_t          min_exponent10    = boost::multiprecision::mp_float<Digits10>::mp_float_min_exp10;    // Type differs from int.
      static const boost::int64_t          max_exponent      = boost::multiprecision::mp_float<Digits10>::mp_float_max_exp;      // Type differs from int.
      static const boost::int64_t          max_exponent10    = boost::multiprecision::mp_float<Digits10>::mp_float_max_exp10;    // Type differs from int.
      static const int                     radix             = boost::multiprecision::mp_float<Digits10>::mp_radix;
      static const std::float_round_style  round_style       = std::round_to_nearest;
      static const bool                    has_infinity      = true;
      static const bool                    has_quiet_NaN     = true;
      static const bool                    has_signaling_NaN = false;
      static const std::float_denorm_style has_denorm        = std::denorm_absent;
      static const bool                    has_denorm_loss   = false;
      static const bool                    traps             = false;
      static const bool                    tinyness_before   = false;

      static const boost::multiprecision::mp_number<boost::multiprecision::mp_float<Digits10> > (min)        (void) throw() { return (boost::multiprecision::mp_float<Digits10>::min)(); }
      static const boost::multiprecision::mp_number<boost::multiprecision::mp_float<Digits10> > (max)        (void) throw() { return (boost::multiprecision::mp_float<Digits10>::max)(); }
      static const boost::multiprecision::mp_number<boost::multiprecision::mp_float<Digits10> > lowest       (void) throw() { return boost::multiprecision::mp_float<Digits10>::zero(); }
      static const boost::multiprecision::mp_number<boost::multiprecision::mp_float<Digits10> > epsilon      (void) throw() { return boost::multiprecision::mp_float<Digits10>::eps(); }
      static const boost::multiprecision::mp_number<boost::multiprecision::mp_float<Digits10> > round_error  (void) throw() { return 0.5L; }
      static const boost::multiprecision::mp_number<boost::multiprecision::mp_float<Digits10> > infinity     (void) throw() { return boost::multiprecision::mp_float<Digits10>::inf(); }
      static const boost::multiprecision::mp_number<boost::multiprecision::mp_float<Digits10> > quiet_NaN    (void) throw() { return boost::multiprecision::mp_float<Digits10>::nan(); }
      static const boost::multiprecision::mp_number<boost::multiprecision::mp_float<Digits10> > signaling_NaN(void) throw() { return boost::multiprecision::mp_float<Digits10>::zero(); }
      static const boost::multiprecision::mp_number<boost::multiprecision::mp_float<Digits10> > denorm_min   (void) throw() { return boost::multiprecision::mp_float<Digits10>::zero(); }
   };
}

namespace boost{ namespace math{

namespace policies{

template <unsigned Digits10, class Policy>
struct precision< boost::multiprecision::mp_number<boost::multiprecision::mp_float<Digits10> >, Policy>
{
   typedef typename Policy::precision_type precision_type;
   typedef digits2<((Digits10 + 1) * 1000L) / 301L> digits_2;
   typedef typename mpl::if_c<
      ((digits_2::value <= precision_type::value) 
      || (Policy::precision_type::value <= 0)),
      // Default case, full precision for RealType:
      digits_2,
      // User customised precision:
      precision_type
   >::type type;
};

} // namespace policies

}} // namespaces boost::math


#endif

