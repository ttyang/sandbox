///////////////////////////////////////////////////////////////////////////////
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BIG_NUM_DEF_OPS
#define BOOST_MATH_BIG_NUM_DEF_OPS

#include <boost/math/policies/error_handling.hpp>
#include <boost/multiprecision/detail/mp_number_base.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/front.hpp>
#include <boost/cstdint.hpp>

#ifndef INSTRUMENT_BACKEND
#ifndef BOOST_MP_INSTRUMENT
#define INSTRUMENT_BACKEND(x)
#else
#define INSTRUMENT_BACKEND(x)\
   std::cout << BOOST_STRINGIZE(x) << " = " << x.str(0, std::ios_base::scientific) << std::endl;
#endif
#endif


namespace boost{ namespace multiprecision{ namespace default_ops{

//
// Default versions of mixed arithmetic, these just construct a temporary
// from the arithmetic value and then do the arithmetic on that:
//
template <class T, class V>
inline typename enable_if<mpl::or_<is_arithmetic<V>, is_convertible<V, const char*>, is_same<V, std::string> > >::type 
   eval_add(T& result, V const& v)
{
   T t;
   t = v;
   eval_add(result, t);
}
template <class T, class V>
inline typename enable_if<mpl::or_<is_arithmetic<V>, is_convertible<V, const char*>, is_same<V, std::string> > >::type
   eval_subtract(T& result, V const& v)
{
   T t;
   t = v;
   eval_subtract(result, t);
}
template <class T, class V>
inline typename enable_if<mpl::or_<is_arithmetic<V>, is_convertible<V, const char*>, is_same<V, std::string> > >::type
   eval_multiply(T& result, V const& v)
{
   T t;
   t = v;
   eval_multiply(result, t);
}
template <class T, class V>
inline typename enable_if<mpl::or_<is_arithmetic<V>, is_convertible<V, const char*>, is_same<V, std::string> > >::type
   eval_divide(T& result, V const& v)
{
   T t;
   t = v;
   eval_divide(result, t);
}
template <class T, class V>
inline typename enable_if<mpl::or_<is_arithmetic<V>, is_convertible<V, const char*>, is_same<V, std::string> > >::type
   eval_modulus(T& result, V const& v)
{
   T t;
   t = v;
   eval_modulus(result, t);
}
template <class T, class V>
inline typename enable_if<mpl::or_<is_arithmetic<V>, is_convertible<V, const char*>, is_same<V, std::string> > >::type
   eval_bitwise_and(T& result, V const& v)
{
   T t;
   t = v;
   eval_bitwise_and(result, t);
}
template <class T, class V>
inline typename enable_if<mpl::or_<is_arithmetic<V>, is_convertible<V, const char*>, is_same<V, std::string> > >::type
   eval_bitwise_or(T& result, V const& v)
{
   T t;
   t = v;
   eval_bitwise_or(result, t);
}
template <class T, class V>
inline typename enable_if<mpl::or_<is_arithmetic<V>, is_convertible<V, const char*>, is_same<V, std::string> > >::type
   eval_bitwise_xor(T& result, V const& v)
{
   T t;
   t = v;
   eval_bitwise_xor(result, t);
}

template <class T, class V>
inline typename enable_if<mpl::or_<is_arithmetic<V>, is_convertible<V, const char*>, is_same<V, std::string> > >::type
   eval_complement(T& result, V const& v)
{
   T t;
   t = v;
   eval_complement(result, t);
}

template <class T>
inline bool is_same_object(const T& u, const T&v)
{  return &u == &v;  }
template <class T, class U>
inline bool is_same_object(const T& u, const U&v)
{  return false;  }

//
// Default versions of 3-arg arithmetic functions, these just forward to the 2 arg versions:
//
template <class T, class U, class V>
inline void eval_add(T& t, const U& u, const V& v)
{
   if(is_same_object(t, v))
   {
      eval_add(t, u);
   }
   else if(is_same_object(t, u))
   {
      eval_add(t, v);
   }
   else
   {
      t = u;
      eval_add(t, v);
   }
}
template<class T, class U>
inline typename disable_if<is_same<T, U> >::type eval_add(T& t, const U& a, const T& b)
{
   return eval_add(t, b, a);
}

template <class T, class U, class V>
inline void eval_subtract(T& t, const U& u, const V& v)
{
   if(is_same_object(t, u))
      eval_subtract(t, v);
   else if(is_same_object(t, v))
   {
      eval_subtract(t, u);
      t.negate();
   }
   else
   {
      t = u;
      eval_subtract(t, v);
   }
}
template <class T, class U>
inline typename disable_if<is_same<T, U> >::type eval_subtract(T& t, const U& a, const T& b)
{
   eval_subtract(t, b, a);
   t.negate();
}

template <class T, class U, class V>
inline void eval_multiply(T& t, const U& u, const V& v)
{
   if(is_same_object(t, u))
      eval_multiply(t, v);
   else if(is_same_object(t, v))
      eval_multiply(t, u);
   else
   {
      t = u;
      eval_multiply(t, v);
   }
}
template <class T, class U>
inline typename disable_if<is_same<T, U> >::type eval_multiply(T& t, const U& a, const T& b)
{
   eval_multiply(t, b, a);
}
template <class T, class U, class V>
inline void eval_divide(T& t, const U& u, const V& v)
{
   if(is_same_object(t, u))
      eval_divide(t, v);
   else if(is_same_object(t, v))
   {
      T temp = t;
      eval_divide(temp, u, v);
      temp.swap(t);
   }
   else
   {
      t = u;
      eval_divide(t, v);
   }
}
template <class T, class U, class V>
inline void eval_modulus(T& t, const U& u, const V& v)
{
   if(is_same_object(t, u))
      eval_modulus(t, v);
   else if(is_same_object(t, v))
   {
      T temp;
      eval_modulus(temp, u, v);
      temp.swap(t);
   }
   else
   {
      t = u;
      eval_modulus(t, v);
   }
}
template <class T, class U, class V>
inline void eval_bitwise_and(T& t, const U& u, const V& v)
{
   if(is_same_object(t, u))
      eval_bitwise_and(t, v);
   else if(is_same_object(t, v))
      eval_bitwise_and(t, u);
   else
   {
      t = u;
      eval_bitwise_and(t, v);
   }
}
template <class T, class U>
inline typename disable_if<is_same<T, U> >::type eval_bitwise_and(T& t, const U& a, const T& b)
{
   eval_bitwise_and(t, b, a);
}

template <class T, class U, class V>
inline void eval_bitwise_or(T& t, const U& u, const V& v)
{
   if(is_same_object(t, u))
      eval_bitwise_or(t, v);
   else if(is_same_object(t, v))
      eval_bitwise_or(t, u);
   else
   {
      t = u;
      eval_bitwise_or(t, v);
   }
}
template <class T, class U>
inline typename disable_if<is_same<T, U> >::type eval_bitwise_or(T& t, const U& a, const T& b)
{
   eval_bitwise_or(t, b, a);
}

template <class T, class U, class V>
inline void eval_bitwise_xor(T& t, const U& u, const V& v)
{
   if(is_same_object(t, u))
      eval_bitwise_xor(t, v);
   else if(is_same_object(t, v))
      eval_bitwise_xor(t, u);
   else
   {
      t = u;
      eval_bitwise_xor(t, v);
   }
}
template <class T, class U>
inline typename disable_if<is_same<T, U> >::type eval_bitwise_xor(T& t, const U& a, const T& b)
{
   eval_bitwise_xor(t, b, a);
}

template <class T>
inline void eval_increment(T& val)
{
   typedef typename mpl::front<typename T::unsigned_types>::type ui_type;
   eval_add(val, static_cast<ui_type>(1u));
}

template <class T>
inline void eval_decrement(T& val)
{
   typedef typename mpl::front<typename T::unsigned_types>::type ui_type;
   eval_subtract(val, static_cast<ui_type>(1u));
}

template <class T, class V>
inline void eval_left_shift(T& result, const T& arg, const V val)
{
   result = arg;
   eval_left_shift(result, val);
}

template <class T, class V>
inline void eval_right_shift(T& result, const T& arg, const V val)
{
   result = arg;
   eval_right_shift(result, val);
}

template <class T>
inline bool eval_is_zero(const T& val)
{
   typedef typename mpl::front<typename T::unsigned_types>::type ui_type;
   return val.compare(static_cast<ui_type>(0)) == 0;
}
template <class T>
inline int eval_get_sign(const T& val)
{
   typedef typename mpl::front<typename T::unsigned_types>::type ui_type;
   return val.compare(static_cast<ui_type>(0));
}

template <class T, class V>
inline void assign_components_imp(T& result, const V& v1, const V& v2, const mpl::int_<number_kind_rational>&)
{
   result = v1;
   T t;
   t = v2;
   eval_divide(result, t);
}

template <class T, class V>
inline void assign_components(T& result, const V& v1, const V& v2)
{
   return assign_components_imp(result, v1, v2, typename number_category<T>::type());
}

template <class R, int b>
struct has_enough_bits
{
   template <class T>
   struct type : public mpl::and_<mpl::not_<is_same<R, T> >, mpl::bool_<std::numeric_limits<T>::digits >= b> >{};
};

template <class R>
struct terminal
{
   terminal(const R& v) : value(v){}
   terminal(){}
   terminal& operator = (R val) {  value = val;  }
   R value;
   operator R()const {  return value;  }
};

template<class R, class B>
struct calculate_next_larger_type
{
   typedef typename mpl::if_<
      is_signed<R>,
      typename B::signed_types,
      typename mpl::if_<
         is_unsigned<R>,
         typename B::unsigned_types,
         typename B::float_types
      >::type
   >::type list_type;
   typedef typename has_enough_bits<R, std::numeric_limits<R>::digits>::template type<mpl::_> pred_type;
   typedef typename mpl::find_if<
      list_type,
      pred_type
   >::type iter_type;
   typedef typename mpl::eval_if<
      is_same<typename mpl::end<list_type>::type, iter_type>,
      mpl::identity<terminal<R> >,
      mpl::deref<iter_type>
      >::type type;
};

template <class R, class B>
inline void eval_convert_to(R* result, const B& backend)
{
   typedef typename calculate_next_larger_type<R, B>::type next_type;
   next_type n;
   eval_convert_to(&n, backend);
   if(std::numeric_limits<R>::is_specialized && (n > (std::numeric_limits<R>::max)()))
   {
      *result = (std::numeric_limits<R>::max)();
   }
   else
      *result = static_cast<R>(n);
}

template <class R, class B>
inline void eval_convert_to(terminal<R>* result, const B& backend)
{
   //
   // We ran out of types to try for the convertion, try
   // a lexical_cast and hope for the best:
   //
   result->value = boost::lexical_cast<R>(backend.str(0, std::ios_base::fmtflags(0)));
}

//
// Functions:
//
template <class T>
void eval_abs(T& result, const T& arg)
{
   typedef typename T::signed_types type_list;
   typedef typename mpl::front<type_list>::type front;
   result = arg;
   if(arg.compare(front(0)) < 0)
      result.negate();
}
template <class T>
void eval_fabs(T& result, const T& arg)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The fabs function is only valid for floating point types.");
   typedef typename T::signed_types type_list;
   typedef typename mpl::front<type_list>::type front;
   result = arg;
   if(arg.compare(front(0)) < 0)
      result.negate();
}

template <class Backend>
inline int eval_fpclassify(const Backend& arg)
{
   BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_floating_point, "The fpclassify function is only valid for floating point types.");
   return eval_is_zero(arg) ? FP_ZERO : FP_NORMAL;
}

template <class T>
inline void eval_fmod(T& result, const T& a, const T& b)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The fmod function is only valid for floating point types.");
   if((&result == &a) || (&result == &b))
   {
      T temp;
      eval_fmod(temp, a, b);
      result = temp;
      return;
   }
   T n;
   eval_divide(result, a, b);
   if(eval_get_sign(a) < 0)
      eval_ceil(n, result);
   else
      eval_floor(n, result);
   eval_multiply(n, b);
   eval_subtract(result, a, n);
}
template <class T>
inline void eval_trunc(T& result, const T& a)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The trunc function is only valid for floating point types.");
   int c = eval_fpclassify(a);
   if(c == FP_NAN || c == FP_INFINITE)
   {
      result = boost::math::policies::raise_rounding_error("boost::multiprecision::trunc<%1%>(%1%)", 0, mp_number<T>(a), 0, boost::math::policies::policy<>()).backend();
      return;
   }
   if(eval_get_sign(a) < 0)
      eval_ceil(result, a);
   else
      eval_floor(result, a);
}

template <class T>
inline void eval_round(T& result, const T& a)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The round function is only valid for floating point types.");
   typedef typename boost::multiprecision::detail::canonical<float, T>::type fp_type;
   int c = eval_fpclassify(a);
   if(c == FP_NAN || c == FP_INFINITE)
   {
      result = boost::math::policies::raise_rounding_error("boost::multiprecision::round<%1%>(%1%)", 0, mp_number<T>(a), 0, boost::math::policies::policy<>()).backend();
      return;
   }
   if(eval_get_sign(a) < 0)
   {
      eval_subtract(result, a, fp_type(0.5f));
      eval_ceil(result, result);
   }
   else
   {
      eval_add(result, a, fp_type(0.5f));
      eval_floor(result, result);
   }
}

template <class T, class Arithmetic>
inline typename enable_if<is_integral<Arithmetic> >::type eval_gcd(T& result, const T& a, const Arithmetic& b)
{
   typedef typename boost::multiprecision::detail::canonical<Arithmetic, T>::type si_type;
   T t;
   t = static_cast<si_type>(b);
   eval_gcd(result, a, t);
}
template <class T, class Arithmetic>
inline typename enable_if<is_integral<Arithmetic> >::type eval_gcd(T& result, const Arithmetic& a, const T& b)
{
   eval_gcd(result, b, a);
}
template <class T, class Arithmetic>
inline typename enable_if<is_integral<Arithmetic> >::type eval_lcm(T& result, const T& a, const Arithmetic& b)
{
   typedef typename boost::multiprecision::detail::canonical<Arithmetic, T>::type si_type;
   T t;
   t = static_cast<si_type>(b);
   eval_lcm(result, a, t);
}
template <class T, class Arithmetic>
inline typename enable_if<is_integral<Arithmetic> >::type eval_lcm(T& result, const Arithmetic& a, const T& b)
{
   eval_lcm(result, b, a);
}

template <class T>
inline unsigned eval_lsb(const T& val)
{
   typedef typename boost::multiprecision::detail::canonical<unsigned, T>::type ui_type;
   unsigned result = 0;
   T mask, t;
   mask = ui_type(1);
   do
   {
      eval_bitwise_and(t, mask, val);
      ++result;
      eval_left_shift(mask, 1);
   }
   while(eval_is_zero(t));
   
   return --result;
}

template <class T>
inline bool eval_bit_test(const T& val, unsigned index)
{
   typedef typename boost::multiprecision::detail::canonical<unsigned, T>::type ui_type;
   unsigned result = 0;
   T mask, t;
   mask = ui_type(1);
   eval_left_shift(mask, index);
   eval_bitwise_and(t, mask, val);
   return !eval_is_zero(t);
}

template <class T>
inline void eval_bit_set(T& val, unsigned index)
{
   typedef typename boost::multiprecision::detail::canonical<unsigned, T>::type ui_type;
   unsigned result = 0;
   T mask;
   mask = ui_type(1);
   eval_left_shift(mask, index);
   eval_bitwise_or(val, mask);
}

template <class T>
inline void eval_bit_flip(T& val, unsigned index)
{
   typedef typename boost::multiprecision::detail::canonical<unsigned, T>::type ui_type;
   unsigned result = 0;
   T mask;
   mask = ui_type(1);
   eval_left_shift(mask, index);
   eval_bitwise_xor(val, mask);
}

template <class T>
inline void eval_bit_unset(T& val, unsigned index)
{
   typedef typename boost::multiprecision::detail::canonical<unsigned, T>::type ui_type;
   unsigned result = 0;
   T mask, t;
   mask = ui_type(1);
   eval_left_shift(mask, index);
   eval_bitwise_and(t, mask, val);
   if(!eval_is_zero(t))
      eval_bitwise_xor(val, mask);
}

//
// These have to implemented by the backend, declared here so that our macro generated code compiles OK.
//
template <class T>
typename enable_if_c<sizeof(T) == 0>::type eval_floor();
template <class T>
typename enable_if_c<sizeof(T) == 0>::type eval_ceil();
template <class T>
typename enable_if_c<sizeof(T) == 0>::type eval_trunc();
template <class T>
typename enable_if_c<sizeof(T) == 0>::type eval_sqrt();
template <class T>
typename enable_if_c<sizeof(T) == 0>::type eval_ldexp();
template <class T>
typename enable_if_c<sizeof(T) == 0>::type eval_frexp();
//
// These functions are implemented in separate files, but expanded inline here,
// DO NOT CHANGE THE ORDER OF THESE INCLUDES:
//
#include <boost/multiprecision/detail/functions/constants.hpp>
#include <boost/multiprecision/detail/functions/pow.hpp>
#include <boost/multiprecision/detail/functions/trig.hpp>

}

} // namespace multiprecision
namespace math{
//
// Default versions of floating point classification routines:
//
template <class Backend, bool ExpressionTemplates>
inline int fpclassify BOOST_PREVENT_MACRO_SUBSTITUTION(const multiprecision::mp_number<Backend, ExpressionTemplates>& arg)
{
   using multiprecision::default_ops::eval_fpclassify;
   return eval_fpclassify(arg.backend());
}
template <class tag, class A1, class A2, class A3>
inline int fpclassify BOOST_PREVENT_MACRO_SUBSTITUTION(const multiprecision::detail::mp_exp<tag, A1, A2, A3>& arg)
{
   typedef typename multiprecision::detail::mp_exp<tag, A1, A2, A3>::result_type value_type;
   return fpclassify(value_type(arg));
}
template <class Backend, bool ExpressionTemplates>
inline bool isfinite BOOST_PREVENT_MACRO_SUBSTITUTION(const multiprecision::mp_number<Backend, ExpressionTemplates>& arg)
{
   int v = fpclassify(arg);
   return (v != FP_INFINITE) && (v != FP_NAN);
}
template <class tag, class A1, class A2, class A3>
inline bool isfinite BOOST_PREVENT_MACRO_SUBSTITUTION(const multiprecision::detail::mp_exp<tag, A1, A2, A3>& arg)
{
   typedef typename multiprecision::detail::mp_exp<tag, A1, A2, A3>::result_type value_type;
   return isfinite(value_type(arg));
}
template <class Backend, bool ExpressionTemplates>
inline bool isnan BOOST_PREVENT_MACRO_SUBSTITUTION(const multiprecision::mp_number<Backend, ExpressionTemplates>& arg)
{
   return fpclassify(arg) == FP_NAN;
}
template <class tag, class A1, class A2, class A3>
inline bool isnan BOOST_PREVENT_MACRO_SUBSTITUTION(const multiprecision::detail::mp_exp<tag, A1, A2, A3>& arg)
{
   typedef typename multiprecision::detail::mp_exp<tag, A1, A2, A3>::result_type value_type;
   return isnan(value_type(arg));
}
template <class Backend, bool ExpressionTemplates>
inline bool isinf BOOST_PREVENT_MACRO_SUBSTITUTION(const multiprecision::mp_number<Backend, ExpressionTemplates>& arg)
{
   return fpclassify(arg) == FP_INFINITE;
}
template <class tag, class A1, class A2, class A3>
inline bool isinf BOOST_PREVENT_MACRO_SUBSTITUTION(const multiprecision::detail::mp_exp<tag, A1, A2, A3>& arg)
{
   typedef typename multiprecision::detail::mp_exp<tag, A1, A2, A3>::result_type value_type;
   return isinf(value_type(arg));
}
template <class Backend, bool ExpressionTemplates>
inline bool isnormal BOOST_PREVENT_MACRO_SUBSTITUTION(const multiprecision::mp_number<Backend, ExpressionTemplates>& arg)
{
   return fpclassify(arg) == FP_NORMAL;
}
template <class tag, class A1, class A2, class A3>
inline bool isnormal BOOST_PREVENT_MACRO_SUBSTITUTION(const multiprecision::detail::mp_exp<tag, A1, A2, A3>& arg)
{
   typedef typename multiprecision::detail::mp_exp<tag, A1, A2, A3>::result_type value_type;
   return isnormal(value_type(arg));
}

} // namespace math
namespace multiprecision{

template <class tag, class A1, class A2, class A3, class Policy>
inline typename detail::mp_exp<tag, A1, A2, A3>::result_type trunc(const detail::mp_exp<tag, A1, A2, A3>& v, const Policy& pol)
{
   typedef typename detail::mp_exp<tag, A1, A2, A3>::result_type number_type;
   return trunc(number_type(v), pol);
}

template <class Backend, bool ExpressionTemplates, class Policy>
inline mp_number<Backend, ExpressionTemplates> trunc(const mp_number<Backend, ExpressionTemplates>& v, const Policy& pol)
{
   using default_ops::eval_trunc;
   mp_number<Backend, ExpressionTemplates> result;
   eval_trunc(result.backend(), v.backend());
   return result;
}

template <class tag, class A1, class A2, class A3, class Policy>
inline int itrunc(const detail::mp_exp<tag, A1, A2, A3>& v, const Policy& pol)
{
   typedef typename detail::mp_exp<tag, A1, A2, A3>::result_type number_type;
   number_type r = trunc(v, pol);
   if((r > (std::numeric_limits<int>::max)()) || r < (std::numeric_limits<int>::min)() || !boost::math::isfinite(v))
      return boost::math::policies::raise_rounding_error("boost::multiprecision::itrunc<%1%>(%1%)", 0, number_type(v), 0, pol).template convert_to<int>();
   return r.template convert_to<int>();
}
template <class tag, class A1, class A2, class A3>
inline int itrunc(const detail::mp_exp<tag, A1, A2, A3>& v)
{
   return itrunc(v, boost::math::policies::policy<>());
}
template <class Backend, bool ExpressionTemplates, class Policy>
inline int itrunc(const mp_number<Backend, ExpressionTemplates>& v, const Policy& pol)
{
   mp_number<Backend, ExpressionTemplates> r = trunc(v, pol);
   if((r > (std::numeric_limits<int>::max)()) || r < (std::numeric_limits<int>::min)() || !boost::math::isfinite(v))
      return boost::math::policies::raise_rounding_error("boost::multiprecision::itrunc<%1%>(%1%)", 0, v, 0, pol).template convert_to<int>();
   return r.template convert_to<int>();
}
template <class Backend, bool ExpressionTemplates>
inline int itrunc(const mp_number<Backend, ExpressionTemplates>& v)
{
   return itrunc(v, boost::math::policies::policy<>());
}
template <class tag, class A1, class A2, class A3, class Policy>
inline long ltrunc(const detail::mp_exp<tag, A1, A2, A3>& v, const Policy& pol)
{
   typedef typename detail::mp_exp<tag, A1, A2, A3>::result_type number_type;
   number_type r = trunc(v, pol);
   if((r > (std::numeric_limits<long>::max)()) || r < (std::numeric_limits<long>::min)() || !boost::math::isfinite(v))
      return boost::math::policies::raise_rounding_error("boost::multiprecision::ltrunc<%1%>(%1%)", 0, number_type(v), 0L, pol).template convert_to<long>();
   return r.template convert_to<long>();
}
template <class tag, class A1, class A2, class A3>
inline long ltrunc(const detail::mp_exp<tag, A1, A2, A3>& v)
{
   return ltrunc(v, boost::math::policies::policy<>());
}
template <class T, bool ExpressionTemplates, class Policy>
inline long ltrunc(const mp_number<T, ExpressionTemplates>& v, const Policy& pol)
{
   mp_number<T, ExpressionTemplates> r = trunc(v, pol);
   if((r > (std::numeric_limits<long>::max)()) || r < (std::numeric_limits<long>::min)() || !boost::math::isfinite(v))
      return boost::math::policies::raise_rounding_error("boost::multiprecision::ltrunc<%1%>(%1%)", 0, v, 0L, pol).template convert_to<long>();
   return r.template convert_to<long>();
}
template <class T, bool ExpressionTemplates>
inline long ltrunc(const mp_number<T, ExpressionTemplates>& v)
{
   return ltrunc(v, boost::math::policies::policy<>());
}
#ifndef BOOST_NO_LONG_LONG
template <class tag, class A1, class A2, class A3, class Policy>
inline long long lltrunc(const detail::mp_exp<tag, A1, A2, A3>& v, const Policy& pol)
{
   typedef typename detail::mp_exp<tag, A1, A2, A3>::result_type number_type;
   number_type r = trunc(v, pol);
   if((r > (std::numeric_limits<long long>::max)()) || r < (std::numeric_limits<long long>::min)() || !boost::math::isfinite(v))
      return boost::math::policies::raise_rounding_error("boost::multiprecision::lltrunc<%1%>(%1%)", 0, number_type(v), 0LL, pol).template convert_to<long long>();
   return r.template convert_to<long long>();
}
template <class tag, class A1, class A2, class A3>
inline long long lltrunc(const detail::mp_exp<tag, A1, A2, A3>& v)
{
   return lltrunc(v, boost::math::policies::policy<>());
}
template <class T, bool ExpressionTemplates, class Policy>
inline long long lltrunc(const mp_number<T, ExpressionTemplates>& v, const Policy& pol)
{
   mp_number<T, ExpressionTemplates> r = trunc(v, pol);
   if((r > (std::numeric_limits<long long>::max)()) || r < (std::numeric_limits<long long>::min)() || !boost::math::isfinite(v))
      return boost::math::policies::raise_rounding_error("boost::multiprecision::lltrunc<%1%>(%1%)", 0, v, 0LL, pol).template convert_to<long long>();
   return r.template convert_to<long long>();
}
template <class T, bool ExpressionTemplates>
inline long long lltrunc(const mp_number<T, ExpressionTemplates>& v)
{
   return lltrunc(v, boost::math::policies::policy<>());
}
#endif
template <class tag, class A1, class A2, class A3, class Policy>
inline typename detail::mp_exp<tag, A1, A2, A3>::result_type round(const detail::mp_exp<tag, A1, A2, A3>& v, const Policy& pol)
{
   typedef typename detail::mp_exp<tag, A1, A2, A3>::result_type number_type;
   return round(static_cast<number_type>(v), pol);
}
template <class T, bool ExpressionTemplates, class Policy>
inline mp_number<T, ExpressionTemplates> round(const mp_number<T, ExpressionTemplates>& v, const Policy& pol)
{
   using default_ops::eval_round;
   mp_number<T, ExpressionTemplates> result;
   eval_round(result.backend(), v.backend());
   return result;
}

template <class tag, class A1, class A2, class A3, class Policy>
inline int iround(const detail::mp_exp<tag, A1, A2, A3>& v, const Policy& pol)
{
   typedef typename detail::mp_exp<tag, A1, A2, A3>::result_type number_type;
   number_type r = round(v, pol);
   if((r > (std::numeric_limits<int>::max)()) || r < (std::numeric_limits<int>::min)() || !boost::math::isfinite(v))
      return boost::math::policies::raise_rounding_error("boost::multiprecision::iround<%1%>(%1%)", 0, number_type(v), 0, pol).template convert_to<int>();
   return r.template convert_to<int>();
}
template <class tag, class A1, class A2, class A3>
inline int iround(const detail::mp_exp<tag, A1, A2, A3>& v)
{
   return iround(v, boost::math::policies::policy<>());
}
template <class T, bool ExpressionTemplates, class Policy>
inline int iround(const mp_number<T, ExpressionTemplates>& v, const Policy& pol)
{
   mp_number<T, ExpressionTemplates> r = round(v, pol);
   if((r > (std::numeric_limits<int>::max)()) || r < (std::numeric_limits<int>::min)() || !boost::math::isfinite(v))
      return boost::math::policies::raise_rounding_error("boost::multiprecision::iround<%1%>(%1%)", 0, v, 0, pol).template convert_to<int>();
   return r.template convert_to<int>();
}
template <class T, bool ExpressionTemplates>
inline int iround(const mp_number<T, ExpressionTemplates>& v)
{
   return iround(v, boost::math::policies::policy<>());
}
template <class tag, class A1, class A2, class A3, class Policy>
inline long lround(const detail::mp_exp<tag, A1, A2, A3>& v, const Policy& pol)
{
   typedef typename detail::mp_exp<tag, A1, A2, A3>::result_type number_type;
   number_type r = round(v, pol);
   if((r > (std::numeric_limits<long>::max)()) || r < (std::numeric_limits<long>::min)() || !boost::math::isfinite(v))
      return boost::math::policies::raise_rounding_error("boost::multiprecision::lround<%1%>(%1%)", 0, number_type(v), 0L, pol).template convert_to<long>();
   return r.template convert_to<long>();
}
template <class tag, class A1, class A2, class A3>
inline long lround(const detail::mp_exp<tag, A1, A2, A3>& v)
{
   return lround(v, boost::math::policies::policy<>());
}
template <class T, bool ExpressionTemplates, class Policy>
inline long lround(const mp_number<T, ExpressionTemplates>& v, const Policy& pol)
{
   mp_number<T, ExpressionTemplates> r = round(v, pol);
   if((r > (std::numeric_limits<long>::max)()) || r < (std::numeric_limits<long>::min)() || !boost::math::isfinite(v))
      return boost::math::policies::raise_rounding_error("boost::multiprecision::lround<%1%>(%1%)", 0, v, 0L, pol).template convert_to<long>();
   return r.template convert_to<long>();
}
template <class T, bool ExpressionTemplates>
inline long lround(const mp_number<T, ExpressionTemplates>& v)
{
   return lround(v, boost::math::policies::policy<>());
}
#ifndef BOOST_NO_LONG_LONG
template <class tag, class A1, class A2, class A3, class Policy>
inline long long llround(const detail::mp_exp<tag, A1, A2, A3>& v, const Policy& pol)
{
   typedef typename detail::mp_exp<tag, A1, A2, A3>::result_type number_type;
   number_type r = round(v, pol);
   if((r > (std::numeric_limits<long long>::max)()) || r < (std::numeric_limits<long long>::min)() || !boost::math::isfinite(v))
      return boost::math::policies::raise_rounding_error("boost::multiprecision::iround<%1%>(%1%)", 0, number_type(v), 0LL, pol).template convert_to<long long>();
   return r.template convert_to<long long>();
}
template <class tag, class A1, class A2, class A3>
inline long long llround(const detail::mp_exp<tag, A1, A2, A3>& v)
{
   return llround(v, boost::math::policies::policy<>());
}
template <class T, bool ExpressionTemplates, class Policy>
inline long long llround(const mp_number<T, ExpressionTemplates>& v, const Policy& pol)
{
   mp_number<T, ExpressionTemplates> r = round(v, pol);
   if((r > (std::numeric_limits<long long>::max)()) || r < (std::numeric_limits<long long>::min)() || !boost::math::isfinite(v))
      return boost::math::policies::raise_rounding_error("boost::multiprecision::iround<%1%>(%1%)", 0, v, 0LL, pol).template convert_to<long long>();
   return r.template convert_to<long long>();
}
template <class T, bool ExpressionTemplates>
inline long long llround(const mp_number<T, ExpressionTemplates>& v)
{
   return llround(v, boost::math::policies::policy<>());
}
#endif

#define UNARY_OP_FUNCTOR(func)\
namespace detail{\
template <class Backend> \
struct BOOST_JOIN(func, _funct)\
{\
   void operator()(Backend& result, const Backend& arg)const\
   {\
      using default_ops::BOOST_JOIN(eval_,func);\
      BOOST_JOIN(eval_,func)(result, arg);\
   }\
};\
\
}\
\
template <class tag, class A1, class A2, class A3> \
inline detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<typename detail::backend_type<detail::mp_exp<tag, A1, A2, A3> >::type> \
  , detail::mp_exp<tag, A1, A2, A3> \
> \
func(const detail::mp_exp<tag, A1, A2, A3>& arg)\
{\
    return detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<typename detail::backend_type<detail::mp_exp<tag, A1, A2, A3> >::type> \
  , detail::mp_exp<tag, A1, A2, A3> \
> (\
        detail::BOOST_JOIN(func, _funct)<typename detail::backend_type<detail::mp_exp<tag, A1, A2, A3> >::type>() \
      , arg   \
    );\
}\
template <class Backend> \
inline detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<Backend> \
  , mp_number<Backend> \
> \
func(const mp_number<Backend>& arg)\
{\
    return detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<Backend> \
  , mp_number<Backend> \
  >(\
        detail::BOOST_JOIN(func, _funct)<Backend>() \
      , arg   \
    );\
}\
template <class Backend> \
inline mp_number<Backend, false> \
func(const mp_number<Backend, false>& arg)\
{\
   mp_number<Backend, false> result;\
   using default_ops::BOOST_JOIN(eval_,func);\
   BOOST_JOIN(eval_,func)(result.backend(), arg.backend());\
   return result;\
}

#define BINARY_OP_FUNCTOR(func)\
namespace detail{\
template <class Backend> \
struct BOOST_JOIN(func, _funct)\
{\
   void operator()(Backend& result, const Backend& arg, const Backend& a)const\
   {\
      using default_ops:: BOOST_JOIN(eval_,func);\
      BOOST_JOIN(eval_,func)(result, arg, a);\
   }\
   template <class Arithmetic> \
   void operator()(Backend& result, const Backend& arg, const Arithmetic& a)const\
   {\
      using default_ops:: BOOST_JOIN(eval_,func);\
      BOOST_JOIN(eval_,func)(result, arg, a);\
   }\
   template <class Arithmetic> \
   void operator()(Backend& result, const Arithmetic& arg, const Backend& a)const\
   {\
      using default_ops:: BOOST_JOIN(eval_,func);\
      BOOST_JOIN(eval_,func)(result, arg, a);\
   }\
};\
\
}\
template <class Backend> \
inline detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<Backend> \
  , mp_number<Backend> \
  , mp_number<Backend> \
> \
func(const mp_number<Backend>& arg, const mp_number<Backend>& a)\
{\
    return detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<Backend> \
  , mp_number<Backend> \
  , mp_number<Backend> \
  >(\
        detail::BOOST_JOIN(func, _funct)<Backend>() \
      , arg,\
      a\
    );\
}\
template <class Backend, class tag, class A1, class A2, class A3> \
inline detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<Backend> \
  , mp_number<Backend> \
  , detail::mp_exp<tag, A1, A2, A3> \
> \
func(const mp_number<Backend>& arg, const detail::mp_exp<tag, A1, A2, A3>& a)\
{\
    return detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<Backend> \
  , mp_number<Backend> \
  , detail::mp_exp<tag, A1, A2, A3> \
  >(\
        detail::BOOST_JOIN(func, _funct)<Backend>() \
      , arg,\
      a\
    );\
}\
template <class tag, class A1, class A2, class A3, class Backend> \
inline detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<Backend> \
  , detail::mp_exp<tag, A1, A2, A3> \
  , mp_number<Backend> \
> \
func(const detail::mp_exp<tag, A1, A2, A3>& arg, const mp_number<Backend>& a)\
{\
    return detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<Backend> \
  , detail::mp_exp<tag, A1, A2, A3> \
  , mp_number<Backend> \
  >(\
        detail::BOOST_JOIN(func, _funct)<Backend>() \
      , arg,\
      a\
    );\
}\
template <class tag, class A1, class A2, class A3, class tagb, class A1b, class A2b, class A3b> \
inline detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<typename detail::backend_type<detail::mp_exp<tag, A1, A2, A3> >::type> \
  , detail::mp_exp<tag, A1, A2, A3> \
  , detail::mp_exp<tagb, A1b, A2b, A3b> \
> \
func(const detail::mp_exp<tag, A1, A2, A3>& arg, const detail::mp_exp<tagb, A1b, A2b, A3b>& a)\
{\
    return detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<typename detail::backend_type<detail::mp_exp<tag, A1, A2, A3> >::type> \
  , detail::mp_exp<tag, A1, A2, A3> \
  , detail::mp_exp<tagb, A1b, A2b, A3b> \
  >(\
        detail::BOOST_JOIN(func, _funct)<typename detail::backend_type<detail::mp_exp<tag, A1, A2, A3> >::type>() \
      , arg,\
      a\
    );\
}\
template <class Backend, class Arithmetic> \
inline typename enable_if<\
   is_arithmetic<Arithmetic>,\
   detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<Backend> \
  , mp_number<Backend> \
  , Arithmetic\
  > \
>::type \
func(const mp_number<Backend>& arg, const Arithmetic& a)\
{\
    return detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<Backend> \
  , mp_number<Backend> \
  , Arithmetic\
  >(\
        detail::BOOST_JOIN(func, _funct)<Backend>() \
      , arg,\
      a\
    );\
}\
template <class tag, class A1, class A2, class A3, class Arithmetic> \
inline typename enable_if<\
   is_arithmetic<Arithmetic>,\
   detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<typename detail::backend_type<detail::mp_exp<tag, A1, A2, A3> >::type> \
  , detail::mp_exp<tag, A1, A2, A3> \
  , Arithmetic\
  > \
>::type \
func(const detail::mp_exp<tag, A1, A2, A3>& arg, const Arithmetic& a)\
{\
    return detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<typename detail::backend_type<detail::mp_exp<tag, A1, A2, A3> >::type> \
  , detail::mp_exp<tag, A1, A2, A3> \
  , Arithmetic\
   >(\
        detail::BOOST_JOIN(func, _funct)<typename detail::backend_type<detail::mp_exp<tag, A1, A2, A3> >::type>() \
      , arg,\
      a\
    );\
}\
template <class Backend, class Arithmetic> \
inline typename enable_if<\
   is_arithmetic<Arithmetic>,\
   detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<Backend> \
  , Arithmetic \
  , mp_number<Backend> \
  > \
>::type \
func(const Arithmetic& arg, const mp_number<Backend>& a)\
{\
    return detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<Backend> \
  , Arithmetic \
  , mp_number<Backend> \
  >(\
        detail::BOOST_JOIN(func, _funct)<Backend>() \
      , arg,\
      a\
    );\
}\
template <class tag, class A1, class A2, class A3, class Arithmetic> \
inline typename enable_if<\
   is_arithmetic<Arithmetic>,\
   detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<typename detail::backend_type<detail::mp_exp<tag, A1, A2, A3> >::type> \
  , Arithmetic \
  , detail::mp_exp<tag, A1, A2, A3> \
  > \
>::type \
func(const Arithmetic& arg, const detail::mp_exp<tag, A1, A2, A3>& a)\
{\
    return detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<typename detail::backend_type<detail::mp_exp<tag, A1, A2, A3> >::type> \
  , Arithmetic \
  , detail::mp_exp<tag, A1, A2, A3> \
   >(\
        detail::BOOST_JOIN(func, _funct)<typename detail::backend_type<detail::mp_exp<tag, A1, A2, A3> >::type>() \
      , arg,\
      a\
    );\
}\
template <class Backend> \
inline mp_number<Backend, false> \
func(const mp_number<Backend, false>& arg, const mp_number<Backend, false>& a)\
{\
   mp_number<Backend, false> result;\
   using default_ops:: BOOST_JOIN(eval_,func);\
   BOOST_JOIN(eval_,func)(result.backend(), arg.backend(), a.backend());\
   return result;\
}\
template <class Backend, class Arithmetic> \
inline typename enable_if<\
   is_arithmetic<Arithmetic>,\
   mp_number<Backend, false> \
>::type \
func(const mp_number<Backend, false>& arg, const Arithmetic& a)\
{\
   typedef typename detail::canonical<Arithmetic, Backend>::type canonical_type;\
   mp_number<Backend, false> result;\
   using default_ops:: BOOST_JOIN(eval_,func);\
   BOOST_JOIN(eval_,func)(result.backend(), arg.backend(), static_cast<canonical_type>(a));\
   return result;\
}\
template <class Backend, class Arithmetic> \
inline typename enable_if<\
   is_arithmetic<Arithmetic>,\
   mp_number<Backend, false> \
>::type \
func(const Arithmetic& a, const mp_number<Backend, false>& arg)\
{\
   typedef typename detail::canonical<Arithmetic, Backend>::type canonical_type;\
   mp_number<Backend, false> result;\
   using default_ops:: BOOST_JOIN(eval_,func);\
   BOOST_JOIN(eval_,func)(result.backend(), static_cast<canonical_type>(a), arg.backend());\
   return result;\
}\


#define HETERO_BINARY_OP_FUNCTOR(func, Arg2)\
namespace detail{\
template <class Backend> \
struct BOOST_JOIN(func, _funct)\
{\
   void operator()(Backend& result, Backend const& arg, Arg2 a)const\
   {\
      using default_ops:: BOOST_JOIN(eval_,func);\
      BOOST_JOIN(eval_,func)(result, arg, a);\
   }\
};\
\
}\
\
template <class tag, class A1, class A2, class A3> \
inline detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<typename detail::backend_type<detail::mp_exp<tag, A1, A2, A3> >::type> \
  , detail::mp_exp<tag, A1, A2, A3> \
  , Arg2\
> \
func(const detail::mp_exp<tag, A1, A2, A3>& arg, Arg2 const& a)\
{\
    return detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<typename detail::backend_type<detail::mp_exp<tag, A1, A2, A3> >::type> \
  , detail::mp_exp<tag, A1, A2, A3> \
  , Arg2\
   >(\
        detail::BOOST_JOIN(func, _funct)<typename detail::backend_type<detail::mp_exp<tag, A1, A2, A3> >::type>() \
      , arg, a   \
    );\
}\
template <class Backend> \
inline detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<Backend> \
  , mp_number<Backend> \
  , Arg2\
> \
func(const mp_number<Backend>& arg, Arg2 const& a)\
{\
    return detail::mp_exp<\
    detail::function\
  , detail::BOOST_JOIN(func, _funct)<Backend> \
  , mp_number<Backend> \
  , Arg2\
  >(\
        detail::BOOST_JOIN(func, _funct)<Backend>() \
      , arg,\
      a\
    );\
}\
template <class Backend> \
inline mp_number<Backend, false> \
func(const mp_number<Backend, false>& arg, Arg2 const& a)\
{\
   mp_number<Backend, false> result;\
   using default_ops:: BOOST_JOIN(eval_,func);\
   BOOST_JOIN(eval_,func)(result.backend(), arg.backend(), a);\
   return result;\
}\

UNARY_OP_FUNCTOR(abs)
UNARY_OP_FUNCTOR(fabs)
UNARY_OP_FUNCTOR(sqrt)
UNARY_OP_FUNCTOR(floor)
UNARY_OP_FUNCTOR(ceil)
UNARY_OP_FUNCTOR(trunc)
UNARY_OP_FUNCTOR(round)
UNARY_OP_FUNCTOR(exp)
UNARY_OP_FUNCTOR(log)
UNARY_OP_FUNCTOR(log10)
UNARY_OP_FUNCTOR(cos)
UNARY_OP_FUNCTOR(sin)
UNARY_OP_FUNCTOR(tan)
UNARY_OP_FUNCTOR(asin)
UNARY_OP_FUNCTOR(acos)
UNARY_OP_FUNCTOR(atan)
UNARY_OP_FUNCTOR(cosh)
UNARY_OP_FUNCTOR(sinh)
UNARY_OP_FUNCTOR(tanh)

HETERO_BINARY_OP_FUNCTOR(ldexp, int)
HETERO_BINARY_OP_FUNCTOR(frexp, int*)
BINARY_OP_FUNCTOR(pow)
BINARY_OP_FUNCTOR(fmod)
BINARY_OP_FUNCTOR(atan2)

//
// Integer functions:
//
BINARY_OP_FUNCTOR(gcd)
BINARY_OP_FUNCTOR(lcm)


#undef BINARY_OP_FUNCTOR
#undef UNARY_OP_FUNCTOR

} //namespace multiprecision

namespace math{
//
// Overload of Boost.Math functions that find the wrong overload when used with mp_number:
//
namespace detail{
   template <class T> T sinc_pi_imp(T);
   template <class T> T sinhc_pi_imp(T);
}
template <class Backend, bool ExpressionTemplates>
inline multiprecision::mp_number<Backend, ExpressionTemplates> sinc_pi(const multiprecision::mp_number<Backend, ExpressionTemplates>& x)
{
   return detail::sinc_pi_imp(x);
}

template <class Backend, bool ExpressionTemplates, class Policy>
inline multiprecision::mp_number<Backend, ExpressionTemplates> sinc_pi(const multiprecision::mp_number<Backend, ExpressionTemplates>& x, const Policy&)
{
   return detail::sinc_pi_imp(x);
}

template <class Backend, bool ExpressionTemplates>
inline multiprecision::mp_number<Backend, ExpressionTemplates> sinhc_pi(const multiprecision::mp_number<Backend, ExpressionTemplates>& x)
{
   return detail::sinhc_pi_imp(x);
}

template <class Backend, bool ExpressionTemplates, class Policy>
inline multiprecision::mp_number<Backend, ExpressionTemplates> sinhc_pi(const multiprecision::mp_number<Backend, ExpressionTemplates>& x, const Policy&)
{
   return boost::math::sinhc_pi(x);
}

} // namespace math
} // namespace boost

//
// This has to come last of all:
//
#include <boost/multiprecision/detail/no_et_ops.hpp>

#endif

