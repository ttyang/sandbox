///////////////////////////////////////////////////////////////////////////////
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BIG_NUM_BASE_HPP
#define BOOST_MATH_BIG_NUM_BASE_HPP

#include <limits>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/lexical_cast.hpp>

namespace boost{ namespace multiprecision{

template <class Backend, bool ExpressionTemplates = true>
class number;

template <class T>
struct is_mp_number : public mpl::false_ {};

template <class Backend, bool ExpressionTemplates>
struct is_mp_number<number<Backend, ExpressionTemplates> > : public mpl::true_ {};

namespace detail{

// Forward-declare an expression wrapper
template<class tag, class Arg1 = void, class Arg2 = void, class Arg3 = void, class Arg4 = void>
struct expression;

} // namespace detail

template <class T>
struct is_mp_number_expression : public mpl::false_ {};

template<class tag, class Arg1, class Arg2, class Arg3, class Arg4>
struct is_mp_number_expression<detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > : public mpl::true_ {};

template <class T, class Num>
struct is_compatible_arithmetic_type 
   : public mpl::bool_<
         is_convertible<T, Num>::value 
         && !is_mp_number<T>::value 
         && !is_mp_number_expression<T>::value> 
{};

namespace detail{
//
// Workaround for missing abs(long long) on some compilers:
//
template <class T>
typename boost::enable_if<is_arithmetic<T>, T>::type abs(const T& t) BOOST_NOEXCEPT
{
   return t < 0 ? -t : t;
}

#define BOOST_MP_USING_ABS using std::abs; using boost::multiprecision::detail::abs;

//
// Move support:
//
#ifndef BOOST_NO_RVALUE_REFERENCES
#  define BOOST_MP_MOVE(x) std::move(x)
#else
#  define BOOST_MP_MOVE(x) x
#endif

template <int b>
struct has_enough_bits
{
   template <class T>
   struct type : public mpl::bool_<std::numeric_limits<T>::digits >= b>{};
};

template <class Val, class Backend, class Tag>
struct canonical_imp
{
   typedef typename decay<Val>::type type;
};
template <class Val, class Backend>
struct canonical_imp<Val, Backend, mpl::int_<0> >
{
   typedef typename has_enough_bits<std::numeric_limits<Val>::digits>::template type<mpl::_> pred_type;
   typedef typename mpl::find_if<
      typename Backend::signed_types,
      pred_type
   >::type iter_type;
   typedef typename mpl::deref<iter_type>::type type;
};
template <class Val, class Backend>
struct canonical_imp<Val, Backend, mpl::int_<1> >
{
   typedef typename has_enough_bits<std::numeric_limits<Val>::digits>::template type<mpl::_> pred_type;
   typedef typename mpl::find_if<
      typename Backend::unsigned_types,
      pred_type
   >::type iter_type;
   typedef typename mpl::deref<iter_type>::type type;
};
template <class Val, class Backend>
struct canonical_imp<Val, Backend, mpl::int_<2> >
{
   typedef typename has_enough_bits<std::numeric_limits<Val>::digits>::template type<mpl::_> pred_type;
   typedef typename mpl::find_if<
      typename Backend::float_types,
      pred_type
   >::type iter_type;
   typedef typename mpl::deref<iter_type>::type type;
};
template <class Val, class Backend>
struct canonical_imp<Val, Backend, mpl::int_<3> >
{
   typedef const char* type;
};

template <class Val, class Backend>
struct canonical
{
   typedef typename mpl::if_<
      is_signed<Val>,
      mpl::int_<0>,
      typename mpl::if_<
         is_unsigned<Val>,
         mpl::int_<1>,
         typename mpl::if_<
            is_floating_point<Val>,
            mpl::int_<2>,
            typename mpl::if_<
               mpl::or_<
                  is_convertible<Val, const char*>,
                  is_same<Val, std::string>
               >,
               mpl::int_<3>,
               mpl::int_<4>
            >::type
         >::type
      >::type
   >::type tag_type;

   typedef typename canonical_imp<Val, Backend, tag_type>::type type;
};

struct terminal{};
struct negate{};
struct plus{};
struct minus{};
struct multiplies{};
struct divides{};
struct modulus{};
struct shift_left{};
struct shift_right{};
struct bitwise_and{};
struct bitwise_or{};
struct bitwise_xor{};
struct bitwise_complement{};
struct add_immediates{};
struct subtract_immediates{};
struct multiply_immediates{};
struct divide_immediates{};
struct modulus_immediates{};
struct bitwise_and_immediates{};
struct bitwise_or_immediates{};
struct bitwise_xor_immediates{};
struct complement_immediates{};
struct function{};

template <class T>
struct backend_type;

template <class T, bool ExpressionTemplates>
struct backend_type<number<T, ExpressionTemplates> >
{
   typedef T type;
};

template <class tag, class A1, class A2, class A3, class A4>
struct backend_type<expression<tag, A1, A2, A3, A4> >
{
   typedef typename backend_type<typename expression<tag, A1, A2, A3, A4>::result_type>::type type;
};


template <class T>
struct is_mp_number : public mpl::false_{};
template <class T, bool ExpressionTemplates>
struct is_mp_number<boost::multiprecision::number<T, ExpressionTemplates> > : public mpl::true_{};
template <class T>
struct is_mp_number_exp : public mpl::false_{};
template <class Tag, class Arg1, class Arg2, class Arg3, class Arg4>
struct is_mp_number_exp<boost::multiprecision::detail::expression<Tag, Arg1, Arg2, Arg3, Arg4> > : public mpl::true_{};

template <class T1, class T2>
struct combine_expression;

template <class T1, bool ExpressionTemplates, class T2>
struct combine_expression<number<T1, ExpressionTemplates>, T2>
{
   typedef number<T1, ExpressionTemplates> type;
};

template <class T1, class T2, bool ExpressionTemplates>
struct combine_expression<T1, number<T2, ExpressionTemplates> >
{
   typedef number<T2, ExpressionTemplates> type;
};

template <class T, bool ExpressionTemplates>
struct combine_expression<number<T, ExpressionTemplates>, number<T, ExpressionTemplates> >
{
   typedef number<T, ExpressionTemplates> type;
};

template <class T>
struct arg_type
{
   typedef expression<terminal, T> type;
};

template <class Tag, class Arg1, class Arg2, class Arg3, class Arg4>
struct arg_type<expression<Tag, Arg1, Arg2, Arg3, Arg4> >
{
   typedef expression<Tag, Arg1, Arg2, Arg3, Arg4> type;
};

template <class T>
struct unmentionable
{
   static void proc(){}
};

typedef void (*unmentionable_type)();

template <class T>
struct expression_storage
{
   typedef const T& type;
};

template <class T>
struct expression_storage<T*>
{
   typedef T* type;
};

template <class T>
struct expression_storage<const T*>
{
   typedef const T* type;
};

template <class tag, class A1, class A2, class A3, class A4>
struct expression_storage<expression<tag, A1, A2, A3, A4> >
{
   typedef expression<tag, A1, A2, A3, A4> type;
};

template<class tag, class Arg1>
struct expression<tag, Arg1, void, void, void>
{
   typedef mpl::int_<1> arity;
   typedef typename arg_type<Arg1>::type left_type;
   typedef typename left_type::result_type result_type;
   typedef tag tag_type;

   explicit expression(const Arg1& a) : arg(a) {}

   left_type left()const { return left_type(arg); }

   const Arg1& left_ref()const BOOST_NOEXCEPT { return arg; }

   static const unsigned depth = left_type::depth + 1;

   operator unmentionable_type()const
   {
      result_type r(*this);
      return r ? &unmentionable<void>::proc : 0;
   }

private:
   typename expression_storage<Arg1>::type arg;
   expression& operator=(const expression&);
};

template<class Arg1>
struct expression<terminal, Arg1, void, void, void>
{
   typedef mpl::int_<0> arity;
   typedef Arg1 result_type;
   typedef terminal tag_type;

   explicit expression(const Arg1& a) : arg(a) {}

   const Arg1& value()const BOOST_NOEXCEPT { return arg; }

   static const unsigned depth = 0;

   operator unmentionable_type()const
   {
      return arg ? &unmentionable<void>::proc : 0;
   }

private:
   typename expression_storage<Arg1>::type arg;
   expression& operator=(const expression&);
};

template <class tag, class Arg1, class Arg2>
struct expression<tag, Arg1, Arg2, void, void>
{
   typedef mpl::int_<2> arity;
   typedef typename arg_type<Arg1>::type left_type;
   typedef typename arg_type<Arg2>::type right_type;
   typedef typename left_type::result_type left_result_type;
   typedef typename right_type::result_type right_result_type;
   typedef typename combine_expression<left_result_type, right_result_type>::type result_type;
   typedef tag tag_type;

   expression(const Arg1& a1, const Arg2& a2) : arg1(a1), arg2(a2) {}

   left_type left()const { return left_type(arg1); }
   right_type right()const { return right_type(arg2); }
   const Arg1& left_ref()const BOOST_NOEXCEPT { return arg1; }
   const Arg2& right_ref()const BOOST_NOEXCEPT { return arg2; }

   operator unmentionable_type()const
   {
      result_type r(*this);
      return r ? &unmentionable<void>::proc : 0;
   }

   static const unsigned left_depth = left_type::depth + 1;
   static const unsigned right_depth = right_type::depth + 1;
   static const unsigned depth = left_depth > right_depth ? left_depth : right_depth;
private:
   typename expression_storage<Arg1>::type arg1;
   typename expression_storage<Arg2>::type arg2;
   expression& operator=(const expression&);
};

template <class tag, class Arg1, class Arg2, class Arg3>
struct expression<tag, Arg1, Arg2, Arg3, void>
{
   typedef mpl::int_<3> arity;
   typedef typename arg_type<Arg1>::type left_type;
   typedef typename arg_type<Arg2>::type middle_type;
   typedef typename arg_type<Arg3>::type right_type;
   typedef typename left_type::result_type left_result_type;
   typedef typename middle_type::result_type middle_result_type;
   typedef typename right_type::result_type right_result_type;
   typedef typename combine_expression<
      left_result_type, 
      typename combine_expression<right_result_type, middle_result_type>::type
   >::type result_type;
   typedef tag tag_type;

   expression(const Arg1& a1, const Arg2& a2, const Arg3& a3) : arg1(a1), arg2(a2), arg3(a3) {}

   left_type left()const { return left_type(arg1); }
   middle_type middle()const { return middle_type(arg2); }
   right_type right()const { return right_type(arg3); }
   const Arg1& left_ref()const BOOST_NOEXCEPT { return arg1; }
   const Arg2& middle_ref()const BOOST_NOEXCEPT { return arg2; }
   const Arg3& right_ref()const BOOST_NOEXCEPT { return arg3; }

   operator unmentionable_type()const
   {
      result_type r(*this);
      return r ? &unmentionable<void>::proc : 0;
   }

   static const unsigned left_depth = left_type::depth + 1;
   static const unsigned middle_depth = middle_type::depth + 1;
   static const unsigned right_depth = right_type::depth + 1;
   static const unsigned depth = left_depth > right_depth ? (left_depth > middle_depth ? left_depth : middle_depth) : (right_depth > middle_depth ? right_depth : middle_depth);
private:
   typename expression_storage<Arg1>::type arg1;
   typename expression_storage<Arg2>::type arg2;
   typename expression_storage<Arg3>::type arg3;
   expression& operator=(const expression&);
};

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
struct expression
{
   typedef mpl::int_<4> arity;
   typedef typename arg_type<Arg1>::type left_type;
   typedef typename arg_type<Arg2>::type left_middle_type;
   typedef typename arg_type<Arg3>::type right_middle_type;
   typedef typename arg_type<Arg4>::type right_type;
   typedef typename left_type::result_type left_result_type;
   typedef typename left_middle_type::result_type left_middle_result_type;
   typedef typename right_middle_type::result_type right_middle_result_type;
   typedef typename right_type::result_type right_result_type;
   typedef typename combine_expression<
      typename combine_expression<
         typename combine_expression<left_result_type, left_middle_result_type>::type,
         right_middle_result_type
      >::type,
      right_result_type
   >::type result_type;
   typedef tag tag_type;

   expression(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4) : arg1(a1), arg2(a2), arg3(a3), arg4(a4) {}

   left_type left()const { return left_type(arg1); }
   left_middle_type left_middle()const { return left_middle_type(arg2); }
   right_middle_type right_middle()const { return right_middle_type(arg3); }
   right_type right()const { return right_type(arg4); }
   const Arg1& left_ref()const BOOST_NOEXCEPT { return arg1; }
   const Arg2& left_middle_ref()const BOOST_NOEXCEPT { return arg2; }
   const Arg3& right_middle_ref()const BOOST_NOEXCEPT { return arg3; }
   const Arg4& right_ref()const BOOST_NOEXCEPT { return arg4; }

   operator unmentionable_type()const
   {
      result_type r(*this);
      return r ? &unmentionable<void>::proc : 0;
   }

   static const unsigned left_depth = left_type::depth + 1;
   static const unsigned left_middle_depth = left_middle_type::depth + 1;
   static const unsigned right_middle_depth = right_middle_type::depth + 1;
   static const unsigned right_depth = right_type::depth + 1;

   static const unsigned left_max_depth = left_depth > left_middle_depth ? left_depth : left_middle_depth;
   static const unsigned right_max_depth = right_depth > right_middle_depth ? right_depth : right_middle_depth;

   static const unsigned depth = left_max_depth > right_max_depth ? left_max_depth : right_max_depth;
private:
   typename expression_storage<Arg1>::type arg1;
   typename expression_storage<Arg2>::type arg2;
   typename expression_storage<Arg3>::type arg3;
   typename expression_storage<Arg4>::type arg4;
   expression& operator=(const expression&);
};

template <class T>
struct digits2
{
   BOOST_STATIC_ASSERT(std::numeric_limits<T>::is_specialized);
   BOOST_STATIC_ASSERT((std::numeric_limits<T>::radix == 2) || (std::numeric_limits<T>::radix == 10));
   // If we really have so many digits that this fails, then we're probably going to hit other problems anyway:
   BOOST_STATIC_ASSERT(LONG_MAX / 1000 > (std::numeric_limits<T>::digits + 1));
   static const long value = std::numeric_limits<T>::radix == 10 ?  (((std::numeric_limits<T>::digits + 1) * 1000L) / 301L) : std::numeric_limits<T>::digits;
};

#ifndef BOOST_MP_MIN_EXPONENT_DIGITS
#ifdef _MSC_VER
#  define BOOST_MP_MIN_EXPONENT_DIGITS 2
#else
#  define BOOST_MP_MIN_EXPONENT_DIGITS 2
#endif
#endif

template <class S>
void format_float_string(S& str, boost::intmax_t my_exp, boost::intmax_t digits, std::ios_base::fmtflags f, bool iszero)
{
   typedef typename S::size_type size_type;
   bool scientific = (f & std::ios_base::scientific) == std::ios_base::scientific;
   bool fixed      = (f & std::ios_base::fixed) == std::ios_base::fixed;
   bool showpoint  = (f & std::ios_base::showpoint) == std::ios_base::showpoint;
   bool showpos     = (f & std::ios_base::showpos) == std::ios_base::showpos;

   bool neg = str.size() && (str[0] == '-');

   if(neg)
      str.erase(0, 1);

   if(digits == 0)
   {
      digits = (std::max)(str.size(), size_type(16));
   }

   if(iszero || str.empty() || (str.find_first_not_of('0') == S::npos))
   {
      // We will be printing zero, even though the value might not
      // actually be zero (it just may have been rounded to zero).
      str = "0";
      if(scientific || fixed)
      {
         str.append(1, '.');
         str.append(size_type(digits), '0');
         if(scientific)
            str.append("e+00");
      }
      else
      {
         if(showpoint)
         {
            str.append(1, '.');
            if(digits > 1)
               str.append(size_type(digits - 1), '0');
         }
      }
      if(neg)
         str.insert(0, 1, '-');
      else if(showpos)
         str.insert(0, 1, '+');
      return;
   }

   if(!fixed && !scientific && !showpoint)
   {
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
   }
   else if(!fixed || (my_exp >= 0))
   {
      //
      // Pad out the end with zero's if we need to:
      //
      boost::intmax_t chars = str.size();
      chars = digits - chars;
      if(scientific)
         ++chars;
      if(chars > 0)
      {
         str.append(static_cast<std::string::size_type>(chars), '0');
      }
   }

   if(fixed || (!scientific && (my_exp >= -4) && (my_exp < digits)))
   {
      if(1 + my_exp > static_cast<boost::intmax_t>(str.size()))
      {
         // Just pad out the end with zeros:
         str.append(static_cast<std::string::size_type>(1 + my_exp - str.size()), '0');
         if(showpoint || fixed)
            str.append(".");
      }
      else if(my_exp + 1 < static_cast<boost::intmax_t>(str.size()))
      {
         if(my_exp < 0)
         {
            str.insert(0, static_cast<std::string::size_type>(-1 - my_exp), '0');
            str.insert(0, "0.");
         }
         else
         {
            // Insert the decimal point:
            str.insert(static_cast<std::string::size_type>(my_exp + 1), 1, '.');
         }
      }
      else if(showpoint || fixed) // we have exactly the digits we require to left of the point
         str += ".";

      if(fixed)
      {
         // We may need to add trailing zeros:
         boost::intmax_t l = str.find('.') + 1;
         l = digits - (str.size() - l);
         if(l > 0)
            str.append(size_type(l), '0');
      }
   }
   else
   {
      BOOST_MP_USING_ABS
      // Scientific format:
      if(showpoint || (str.size() > 1))
         str.insert(1, 1, '.');
      str.append(1, 'e');
      S e = boost::lexical_cast<S>(abs(my_exp));
      if(e.size() < BOOST_MP_MIN_EXPONENT_DIGITS)
         e.insert(0, BOOST_MP_MIN_EXPONENT_DIGITS-e.size(), '0');
      if(my_exp < 0)
         e.insert(0, 1, '-');
      else
         e.insert(0, 1, '+');
      str.append(e);
   }
   if(neg)
      str.insert(0, 1, '-');
   else if(showpos)
      str.insert(0, 1, '+');
}

} // namespace detail

//
// Non-member operators for number:
//
// Unary operators first:
//
template <class B, bool ExpressionTemplates>
inline const number<B, ExpressionTemplates>& operator + (const number<B, ExpressionTemplates>& v) { return v; }
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& operator + (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& v) { return v; }
template <class B>
inline detail::expression<detail::negate, number<B, true> > operator - (const number<B, true>& v) { return detail::expression<detail::negate, number<B, true> >(v); }
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline detail::expression<detail::negate, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > operator - (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& v) { return detail::expression<detail::negate, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(v); }
template <class B>
inline detail::expression<detail::complement_immediates, number<B, true> > operator ~ (const number<B, true>& v) { return detail::expression<detail::complement_immediates, number<B, true> >(v); }
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline detail::expression<detail::bitwise_complement, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > operator ~ (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& v) { return detail::expression<detail::bitwise_complement, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(v); }
//
// Then addition:
//
template <class B>
inline detail::expression<detail::add_immediates, number<B, true>, number<B, true> >
   operator + (const number<B, true>& a, const number<B, true>& b)
{
   return detail::expression<detail::add_immediates, number<B, true>, number<B, true> >(a, b);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::add_immediates, number<B, true>, V > >::type
   operator + (const number<B, true>& a, const V& b)
{
   return detail::expression<detail::add_immediates, number<B, true>, V >(a, b);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::add_immediates, V, number<B, true> > >::type
   operator + (const V& a, const number<B, true>& b)
{
   return detail::expression<detail::add_immediates, V, number<B, true> >(a, b);
}
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline detail::expression<detail::plus, number<B, true>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >
   operator + (const number<B, true>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::plus, number<B, true>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, true> >
   operator + (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, true>& b)
{
   return detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, true> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >
   operator + (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V > >::type
   operator + (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V >(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::plus, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
   operator + (const V& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::plus, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
//
// Repeat operator for negated arguments: propagate the negation to the top level to avoid temporaries:
//
template <class B, class Arg1, class Arg2, class Arg3, class Arg4>
inline detail::expression<detail::minus, number<B, true>, typename detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>::left_type >
   operator + (const number<B, true>& a, const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::minus, number<B, true>, typename detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>::left_type >(a, b.left_ref());
}
template <class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline detail::expression<detail::minus, number<B, true>, typename detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>::left_type >
   operator + (const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, const number<B, true>& b)
{
   return detail::expression<detail::minus, number<B, true>, typename detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>::left_type >(b, a.left_ref());
}
template <class B>
inline detail::expression<detail::subtract_immediates, number<B, true>, number<B, true> >
   operator + (const number<B, true>& a, const detail::expression<detail::negate, number<B, true> >& b)
{
   return detail::expression<detail::subtract_immediates, number<B, true>, number<B, true> >(a, b.left_ref());
}
template <class B>
inline detail::expression<detail::subtract_immediates, number<B, true>, number<B, true> >
   operator + (const detail::expression<detail::negate, number<B, true> >& a, const number<B, true>& b)
{
   return detail::expression<detail::subtract_immediates, number<B, true>, number<B, true> >(b, a.left_ref());
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::subtract_immediates, V, number<B, true> > >::type
   operator + (const detail::expression<detail::negate, number<B, true> >& a, const V& b)
{
   return detail::expression<detail::subtract_immediates, V, number<B, true> >(b, a.left_ref());
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::subtract_immediates, V, number<B, true> > >::type
   operator + (const V& a, const detail::expression<detail::negate, number<B, true> >& b)
{
   return detail::expression<detail::subtract_immediates, number<B, true>, number<B, true> >(a, b.left_ref());
}
template <class B>
inline detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, true>, number<B, true> > >
   operator + (const detail::expression<detail::negate, number<B, true> >& a, const detail::expression<detail::negate, number<B, true> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, true>, number<B, true> > >(detail::expression<detail::add_immediates, number<B, true>, number<B, true> >(a.left_ref(), b.left_ref()));
}
//
// Subtraction:
//
template <class B>
inline detail::expression<detail::subtract_immediates, number<B, true>, number<B, true> >
   operator - (const number<B, true>& a, const number<B, true>& b)
{
   return detail::expression<detail::subtract_immediates, number<B, true>, number<B, true> >(a, b);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::subtract_immediates, number<B, true>, V > >::type
   operator - (const number<B, true>& a, const V& b)
{
   return detail::expression<detail::subtract_immediates, number<B, true>, V >(a, b);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::subtract_immediates, V, number<B, true> > >::type
   operator - (const V& a, const number<B, true>& b)
{
   return detail::expression<detail::subtract_immediates, V, number<B, true> >(a, b);
}
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline detail::expression<detail::minus, number<B, true>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >
   operator - (const number<B, true>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::minus, number<B, true>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, true> >
   operator - (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, true>& b)
{
   return detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, true> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >
   operator - (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V > >::type
   operator - (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V >(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::minus, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
   operator - (const V& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::minus, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
//
// Repeat operator for negated arguments: propagate the negation to the top level to avoid temporaries:
//
template <class B, class Arg1, class Arg2, class Arg3, class Arg4>
inline detail::expression<detail::plus, number<B, true>, typename detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>::left_type >
   operator - (const number<B, true>& a, const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::plus, number<B, true>, typename detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>::left_type >(a, b.left_ref());
}
template <class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline detail::expression<detail::negate, detail::expression<detail::plus, number<B, true>, typename detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>::left_type > >
   operator - (const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, const number<B, true>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::plus, number<B, true>, typename detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>::left_type > >(
      detail::expression<detail::plus, number<B, true>, typename detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>::left_type >(b, a.left_ref()));
}
template <class B>
inline detail::expression<detail::add_immediates, number<B, true>, number<B, true> >
   operator - (const number<B, true>& a, const detail::expression<detail::negate, number<B, true> >& b)
{
   return detail::expression<detail::add_immediates, number<B, true>, number<B, true> >(a, b.left_ref());
}
template <class B>
inline detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, true>, number<B, true> > >
   operator - (const detail::expression<detail::negate, number<B, true> >& a, const number<B, true>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, true>, number<B, true> > >(
      detail::expression<detail::add_immediates, number<B, true>, number<B, true> >(b, a.left_ref()));
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, true>, V > > >::type
   operator - (const detail::expression<detail::negate, number<B, true> >& a, const V& b)
{
   return detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, true>, V > >(detail::expression<detail::add_immediates, number<B, true>, V >(a.left_ref(), b));
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::add_immediates, V, number<B, true> > >::type
   operator - (const V& a, const detail::expression<detail::negate, number<B, true> >& b)
{
   return detail::expression<detail::add_immediates, V, number<B, true> >(a, b.left_ref());
}
//
// Multiplication:
//
template <class B>
inline detail::expression<detail::multiply_immediates, number<B, true>, number<B, true> >
   operator * (const number<B, true>& a, const number<B, true>& b)
{
   return detail::expression<detail::multiply_immediates, number<B, true>, number<B, true> >(a, b);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::multiply_immediates, number<B, true>, V > >::type
   operator * (const number<B, true>& a, const V& b)
{
   return detail::expression<detail::multiply_immediates, number<B, true>, V >(a, b);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::multiply_immediates, V, number<B, true> > >::type
   operator * (const V& a, const number<B, true>& b)
{
   return detail::expression<detail::multiply_immediates, V, number<B, true> >(a, b);
}
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline detail::expression<detail::multiplies, number<B, true>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >
   operator * (const number<B, true>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::multiplies, number<B, true>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, true> >
   operator * (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, true>& b)
{
   return detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, true> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >
   operator * (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V > >::type
   operator * (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V >(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::multiplies, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
   operator * (const V& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::multiplies, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
//
// Repeat operator for negated arguments: propagate the negation to the top level to avoid temporaries:
//
template <class B, class Arg1, class Arg2, class Arg3, class Arg4>
inline detail::expression<detail::negate, detail::expression<detail::multiplies, number<B, true>, typename detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>::left_type > >
   operator * (const number<B, true>& a, const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiplies, number<B, true>, typename detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>::left_type > >(
      detail::expression<detail::multiplies, number<B, true>, typename detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>::left_type > (a, b.left_ref()));
}
template <class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline detail::expression<detail::negate, detail::expression<detail::multiplies, number<B, true>, typename detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>::left_type > >
   operator * (const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, const number<B, true>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiplies, number<B, true>, typename detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>::left_type > >(
      detail::expression<detail::multiplies, number<B, true>, typename detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>::left_type >(b, a.left_ref()));
}
template <class B>
inline detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, true>, number<B, true> > >
   operator * (const number<B, true>& a, const detail::expression<detail::negate, number<B, true> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, true>, number<B, true> > >(
      detail::expression<detail::multiply_immediates, number<B, true>, number<B, true> >(a, b.left_ref()));
}
template <class B>
inline detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, true>, number<B, true> > >
   operator * (const detail::expression<detail::negate, number<B, true> >& a, const number<B, true>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, true>, number<B, true> > >(
      detail::expression<detail::multiply_immediates, number<B, true>, number<B, true> >(b, a.left_ref()));
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, true>, V > > >::type
   operator * (const detail::expression<detail::negate, number<B, true> >& a, const V& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, true>, V > > (
      detail::expression<detail::multiply_immediates, number<B, true>, V >(a.left_ref(), b));
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, true>, V > > >::type
   operator * (const V& a, const detail::expression<detail::negate, number<B, true> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, true>, V > >(
      detail::expression<detail::multiply_immediates, number<B, true>, V >(b.left_ref(), a));
}
//
// Division:
//
template <class B>
inline detail::expression<detail::divide_immediates, number<B, true>, number<B, true> >
   operator / (const number<B, true>& a, const number<B, true>& b)
{
   return detail::expression<detail::divide_immediates, number<B, true>, number<B, true> >(a, b);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::divide_immediates, number<B, true>, V > >::type
   operator / (const number<B, true>& a, const V& b)
{
   return detail::expression<detail::divide_immediates, number<B, true>, V >(a, b);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::divide_immediates, V, number<B, true> > >::type
   operator / (const V& a, const number<B, true>& b)
{
   return detail::expression<detail::divide_immediates, V, number<B, true> >(a, b);
}
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline detail::expression<detail::divides, number<B, true>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >
   operator / (const number<B, true>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::divides, number<B, true>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, true> >
   operator / (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, true>& b)
{
   return detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, true> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >
   operator / (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V > >::type
   operator / (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V >(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::divides, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
   operator / (const V& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::divides, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
//
// Repeat operator for negated arguments: propagate the negation to the top level to avoid temporaries:
//
template <class B, class Arg1, class Arg2, class Arg3, class Arg4>
inline detail::expression<detail::negate, detail::expression<detail::divides, number<B, true>, typename detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>::left_type > >
   operator / (const number<B, true>& a, const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divides, number<B, true>, typename detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>::left_type > >(
      detail::expression<detail::divides, number<B, true>, typename detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>::left_type >(a, b.left_ref()));
}
template <class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline detail::expression<detail::negate, detail::expression<detail::divides, typename detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>::left_type, number<B, true> > >
   operator / (const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, const number<B, true>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divides, typename detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>::left_type, number<B, true> > >(
      detail::expression<detail::divides, typename detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>::left_type, number<B, true> >(a.left_ref(), b));
}
template <class B>
inline detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, true>, number<B, true> > >
   operator / (const number<B, true>& a, const detail::expression<detail::negate, number<B, true> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, true>, number<B, true> > >(
      detail::expression<detail::divide_immediates, number<B, true>, number<B, true> >(a, b.left_ref()));
}
template <class B>
inline detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, true>, number<B, true> > >
   operator / (const detail::expression<detail::negate, number<B, true> >& a, const number<B, true>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, true>, number<B, true> > >(
      detail::expression<detail::divide_immediates, number<B, true>, number<B, true> >(a.left_ref(), b));
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, true>, V > > >::type
   operator / (const detail::expression<detail::negate, number<B, true> >& a, const V& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, true>, V > >(
      detail::expression<detail::divide_immediates, number<B, true>, V>(a.left_ref(), b));
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::negate, detail::expression<detail::divide_immediates, V, number<B, true> > > >::type
   operator / (const V& a, const detail::expression<detail::negate, number<B, true> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, V, number<B, true> > >(
      detail::expression<detail::divide_immediates, V, number<B, true> >(a, b.left_ref()));
}
//
// Modulus:
//
template <class B>
inline detail::expression<detail::modulus_immediates, number<B, true>, number<B, true> >
   operator % (const number<B, true>& a, const number<B, true>& b)
{
   return detail::expression<detail::modulus_immediates, number<B, true>, number<B, true> >(a, b);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::modulus_immediates, number<B, true>, V > >::type
   operator % (const number<B, true>& a, const V& b)
{
   return detail::expression<detail::modulus_immediates, number<B, true>, V >(a, b);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::modulus_immediates, V, number<B, true> > >::type
   operator % (const V& a, const number<B, true>& b)
{
   return detail::expression<detail::modulus_immediates, V, number<B, true> >(a, b);
}
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline detail::expression<detail::modulus, number<B, true>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >
   operator % (const number<B, true>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::modulus, number<B, true>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, true> >
   operator % (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, true>& b)
{
   return detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, true> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >
   operator % (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V > >::type
   operator % (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V >(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::modulus, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
   operator % (const V& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::modulus, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
//
// Left shift:
//
template <class B, class I>
inline typename enable_if<is_integral<I>, detail::expression<detail::shift_left, number<B, true>, I > >::type
   operator << (const number<B, true>& a, const I& b)
{
   return detail::expression<detail::shift_left, number<B, true>, I>(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class I>
inline typename enable_if<is_integral<I>, detail::expression<detail::shift_left, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, I> >::type
   operator << (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const I& b)
{
   return detail::expression<detail::shift_left, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, I>(a, b);
}
//
// Right shift:
//
template <class B, class I>
inline typename enable_if<is_integral<I>, detail::expression<detail::shift_right, number<B, true>, I > >::type
   operator >> (const number<B, true>& a, const I& b)
{
   return detail::expression<detail::shift_right, number<B, true>, I>(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class I>
inline typename enable_if<is_integral<I>, detail::expression<detail::shift_right, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, I> >::type
   operator >> (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const I& b)
{
   return detail::expression<detail::shift_right, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, I>(a, b);
}
//
// Bitwise AND:
//
template <class B>
inline detail::expression<detail::bitwise_and_immediates, number<B, true>, number<B, true> >
   operator & (const number<B, true>& a, const number<B, true>& b)
{
   return detail::expression<detail::bitwise_and_immediates, number<B, true>, number<B, true> >(a, b);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::bitwise_and_immediates, number<B, true>, V > >::type
   operator & (const number<B, true>& a, const V& b)
{
   return detail::expression<detail::bitwise_and_immediates, number<B, true>, V >(a, b);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::bitwise_and_immediates, V, number<B, true> > >::type
   operator & (const V& a, const number<B, true>& b)
{
   return detail::expression<detail::bitwise_and_immediates, V, number<B, true> >(a, b);
}
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline detail::expression<detail::bitwise_and, number<B, true>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >
   operator & (const number<B, true>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_and, number<B, true>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, true> >
   operator & (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, true>& b)
{
   return detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, true> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >
   operator & (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V > >::type
   operator & (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V >(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::bitwise_and, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
   operator & (const V& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_and, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
//
// Bitwise OR:
//
template <class B>
inline detail::expression<detail::bitwise_or_immediates, number<B, true>, number<B, true> >
   operator| (const number<B, true>& a, const number<B, true>& b)
{
   return detail::expression<detail::bitwise_or_immediates, number<B, true>, number<B, true> >(a, b);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::bitwise_or_immediates, number<B, true>, V > >::type
   operator| (const number<B, true>& a, const V& b)
{
   return detail::expression<detail::bitwise_or_immediates, number<B, true>, V >(a, b);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::bitwise_or_immediates, V, number<B, true> > >::type
   operator| (const V& a, const number<B, true>& b)
{
   return detail::expression<detail::bitwise_or_immediates, V, number<B, true> >(a, b);
}
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline detail::expression<detail::bitwise_or, number<B, true>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >
   operator| (const number<B, true>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_or, number<B, true>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, true> >
   operator| (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, true>& b)
{
   return detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, true> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >
   operator| (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V > >::type
   operator| (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V >(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::bitwise_or, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
   operator| (const V& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_or, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
//
// Bitwise XOR:
//
template <class B>
inline detail::expression<detail::bitwise_xor_immediates, number<B, true>, number<B, true> >
   operator^ (const number<B, true>& a, const number<B, true>& b)
{
   return detail::expression<detail::bitwise_xor_immediates, number<B, true>, number<B, true> >(a, b);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::bitwise_xor_immediates, number<B, true>, V > >::type
   operator^ (const number<B, true>& a, const V& b)
{
   return detail::expression<detail::bitwise_xor_immediates, number<B, true>, V >(a, b);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, true> >, detail::expression<detail::bitwise_xor_immediates, V, number<B, true> > >::type
   operator^ (const V& a, const number<B, true>& b)
{
   return detail::expression<detail::bitwise_xor_immediates, V, number<B, true> >(a, b);
}
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline detail::expression<detail::bitwise_xor, number<B, true>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >
   operator^ (const number<B, true>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_xor, number<B, true>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, true> >
   operator^ (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, true>& b)
{
   return detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, true> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >
   operator^ (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V > >::type
   operator^ (const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V >(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::bitwise_xor, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
   operator^ (const V& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_xor, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}

//
// Traits class, lets us know what kind of number we have, defaults to a floating point type:
//
enum number_category_type
{
   number_kind_unknown = -1,
   number_kind_integer = 0,
   number_kind_floating_point = 1,
   number_kind_rational = 2,
   number_kind_fixed_point = 3
};

template <class Num>
struct number_category : public mpl::int_<std::numeric_limits<Num>::is_integer ? number_kind_integer : (std::numeric_limits<Num>::max_exponent ? number_kind_floating_point : number_kind_unknown)> {};
template <class Backend, bool ExpressionTemplates>
struct number_category<number<Backend, ExpressionTemplates> > : public number_category<Backend>{};
template <class tag, class A1, class A2, class A3, class A4>
struct number_category<detail::expression<tag, A1, A2, A3, A4> > : public number_category<typename detail::expression<tag, A1, A2, A3, A4>::result_type>{};

template <class T>
struct component_type;
template <class T, bool ExpressionTemplates>
struct component_type<number<T, ExpressionTemplates> > : public component_type<T>{};
template <class tag, class A1, class A2, class A3, class A4>
struct component_type<detail::expression<tag, A1, A2, A3, A4> > : public component_type<typename detail::expression<tag, A1, A2, A3, A4>::result_type>{};

}} // namespaces

namespace boost{ namespace math{ namespace tools{

template <class T>
struct promote_arg;

template <class tag, class A1, class A2, class A3, class A4>
struct promote_arg<boost::multiprecision::detail::expression<tag, A1, A2, A3, A4> >
{
   typedef typename boost::multiprecision::detail::expression<tag, A1, A2, A3, A4>::result_type type;
};

template <class R, class B, bool ET>
inline R real_cast(const boost::multiprecision::number<B, ET>& val)
{
   return val.template convert_to<R>();
}

template <class R, class tag, class A1, class A2, class A3, class A4>
inline R real_cast(const boost::multiprecision::detail::expression<tag, A1, A2, A3, A4>& val)
{
   typedef typename boost::multiprecision::detail::expression<tag, A1, A2, A3, A4>::result_type val_type;
   return val_type(val).template convert_to<R>();
}


}}}

#endif // BOOST_MATH_BIG_NUM_BASE_HPP


