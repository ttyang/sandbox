///////////////////////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_NO_ET_OPS_HPP
#define BOOST_MP_NO_ET_OPS_HPP

namespace boost{
namespace multiprecision{

//
// Operators for non-expression template enabled number.
// NOTE: this is not a complete header - really just a suffix to default_ops.hpp.
// NOTE: these operators have to be defined after the methods in default_ops.hpp.
//
template <class B>
inline number<B, false> operator - (const number<B, false>& v) 
{
   number<B, false> result(v);
   result.backend().negate();
   return BOOST_MP_MOVE(result); 
}
template <class B>
inline number<B, false> operator ~ (const number<B, false>& v) 
{
   number<B, false> result;
   eval_complement(result.backend(), v.backend());
   return BOOST_MP_MOVE(result); 
}
//
// Addition:
//
template <class B>
inline number<B, false> operator + (const number<B, false>& a, const number<B, false>& b)
{
   number<B, false> result;
   using default_ops::eval_add;
   eval_add(result.backend(), a.backend(), b.backend());
   return BOOST_MP_MOVE(result);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator + (const number<B, false>& a, const V& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   number<B, false> result;
   using default_ops::eval_add;
   eval_add(result.backend(), a.backend(), static_cast<canonical_type>(b));
   return BOOST_MP_MOVE(result);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator + (const V& a, const number<B, false>& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   number<B, false> result;
   using default_ops::eval_add;
   eval_add(result.backend(), b.backend(), static_cast<canonical_type>(a));
   return BOOST_MP_MOVE(result);
}
//
// Subtraction:
//
template <class B>
inline number<B, false> operator - (const number<B, false>& a, const number<B, false>& b)
{
   number<B, false> result;
   using default_ops::eval_subtract;
   eval_subtract(result.backend(), a.backend(), b.backend());
   return BOOST_MP_MOVE(result);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator - (const number<B, false>& a, const V& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   number<B, false> result;
   using default_ops::eval_subtract;
   eval_subtract(result.backend(), a.backend(), static_cast<canonical_type>(b));
   return BOOST_MP_MOVE(result);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator - (const V& a, const number<B, false>& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   number<B, false> result;
   using default_ops::eval_subtract;
   eval_subtract(result.backend(), static_cast<canonical_type>(a), b.backend());
   return BOOST_MP_MOVE(result);
}
//
// Multiply:
//
template <class B>
inline number<B, false> operator * (const number<B, false>& a, const number<B, false>& b)
{
   number<B, false> result;
   using default_ops::eval_multiply;
   eval_multiply(result.backend(), a.backend(), b.backend());
   return BOOST_MP_MOVE(result);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator * (const number<B, false>& a, const V& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   number<B, false> result;
   using default_ops::eval_multiply;
   eval_multiply(result.backend(), a.backend(), static_cast<canonical_type>(b));
   return BOOST_MP_MOVE(result);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator * (const V& a, const number<B, false>& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   number<B, false> result;
   using default_ops::eval_multiply;
   eval_multiply(result.backend(), b.backend(), static_cast<canonical_type>(a));
   return BOOST_MP_MOVE(result);
}
//
// divide:
//
template <class B>
inline number<B, false> operator / (const number<B, false>& a, const number<B, false>& b)
{
   number<B, false> result;
   using default_ops::eval_divide;
   eval_divide(result.backend(), a.backend(), b.backend());
   return BOOST_MP_MOVE(result);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator / (const number<B, false>& a, const V& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   number<B, false> result;
   using default_ops::eval_divide;
   eval_divide(result.backend(), a.backend(), static_cast<canonical_type>(b));
   return BOOST_MP_MOVE(result);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator / (const V& a, const number<B, false>& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   number<B, false> result;
   using default_ops::eval_divide;
   eval_divide(result.backend(), static_cast<canonical_type>(a), b.backend());
   return BOOST_MP_MOVE(result);
}
//
// modulus:
//
template <class B>
inline number<B, false> operator % (const number<B, false>& a, const number<B, false>& b)
{
   number<B, false> result;
   using default_ops::eval_modulus;
   eval_modulus(result.backend(), a.backend(), b.backend());
   return BOOST_MP_MOVE(result);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator % (const number<B, false>& a, const V& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   number<B, false> result;
   using default_ops::eval_modulus;
   eval_modulus(result.backend(), a.backend(), static_cast<canonical_type>(b));
   return BOOST_MP_MOVE(result);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator % (const V& a, const number<B, false>& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   number<B, false> result;
   using default_ops::eval_modulus;
   eval_modulus(result.backend(), static_cast<canonical_type>(a), b.backend());
   return BOOST_MP_MOVE(result);
}
//
// Bitwise or:
//
template <class B>
inline number<B, false> operator | (const number<B, false>& a, const number<B, false>& b)
{
   number<B, false> result;
   using default_ops::eval_bitwise_or;
   eval_bitwise_or(result.backend(), a.backend(), b.backend());
   return BOOST_MP_MOVE(result);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator | (const number<B, false>& a, const V& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   number<B, false> result;
   using default_ops::eval_bitwise_or;
   eval_bitwise_or(result.backend(), a.backend(), static_cast<canonical_type>(b));
   return BOOST_MP_MOVE(result);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator | (const V& a, const number<B, false>& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   number<B, false> result;
   using default_ops::eval_bitwise_or;
   eval_bitwise_or(result.backend(), b.backend(), static_cast<canonical_type>(a));
   return BOOST_MP_MOVE(result);
}
//
// Bitwise xor:
//
template <class B>
inline number<B, false> operator ^ (const number<B, false>& a, const number<B, false>& b)
{
   number<B, false> result;
   using default_ops::eval_bitwise_xor;
   eval_bitwise_xor(result.backend(), a.backend(), b.backend());
   return BOOST_MP_MOVE(result);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator ^ (const number<B, false>& a, const V& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   number<B, false> result;
   using default_ops::eval_bitwise_xor;
   eval_bitwise_xor(result.backend(), a.backend(), static_cast<canonical_type>(b));
   return BOOST_MP_MOVE(result);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator ^ (const V& a, const number<B, false>& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   number<B, false> result;
   using default_ops::eval_bitwise_xor;
   eval_bitwise_xor(result.backend(), b.backend(), static_cast<canonical_type>(a));
   return BOOST_MP_MOVE(result);
}
//
// Bitwise and:
//
template <class B>
inline number<B, false> operator & (const number<B, false>& a, const number<B, false>& b)
{
   number<B, false> result;
   using default_ops::eval_bitwise_and;
   eval_bitwise_and(result.backend(), a.backend(), b.backend());
   return BOOST_MP_MOVE(result);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator & (const number<B, false>& a, const V& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   number<B, false> result;
   using default_ops::eval_bitwise_and;
   eval_bitwise_and(result.backend(), a.backend(), static_cast<canonical_type>(b));
   return BOOST_MP_MOVE(result);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator & (const V& a, const number<B, false>& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   number<B, false> result;
   using default_ops::eval_bitwise_and;
   eval_bitwise_and(result.backend(), b.backend(), static_cast<canonical_type>(a));
   return BOOST_MP_MOVE(result);
}
//
// shifts:
//
template <class B, class I>
inline typename enable_if<is_integral<I>, number<B, false> >::type
   operator << (const number<B, false>& a, const I& b)
{
   number<B, false> result(a);
   using default_ops::eval_left_shift;
   detail::check_shift_range(b, mpl::bool_<(sizeof(I) > sizeof(std::size_t))>(), is_signed<I>());
   eval_left_shift(result.backend(), b);
   return BOOST_MP_MOVE(result);
}
template <class B, class I>
inline typename enable_if<is_integral<I>, number<B, false> >::type
   operator >> (const number<B, false>& a, const I& b)
{
   number<B, false> result(a);
   using default_ops::eval_right_shift;
   detail::check_shift_range(b, mpl::bool_<(sizeof(I) > sizeof(std::size_t))>(), is_signed<I>());
   eval_right_shift(result.backend(), b);
   return BOOST_MP_MOVE(result);
}

#ifndef BOOST_NO_RVALUE_REFERENCES
//
// If we have rvalue references go all over again with rvalue ref overloads and move semantics.
// Note that while it would be tempting to implement these so they return an rvalue reference
// (and indeed this would be optimally efficient), this is unsafe due to users propensity to
// write:
//
// const T& t = a * b;
//
// which would lead to a dangling reference if we didn't return by value.  Of course move
// semantics help a great deal in return by value, so performance is still pretty good...
//
template <class B>
inline number<B, false> operator - (number<B, false>&& v) 
{
   v.backend().negate();
   return static_cast<number<B, false>&&>(v); 
}
template <class B>
inline number<B, false> operator ~ (number<B, false>&& v) 
{
   eval_complement(v.backend(), v.backend());
   return static_cast<number<B, false>&&>(v); 
}
//
// Addition:
//
template <class B>
inline number<B, false> operator + (number<B, false>&& a, const number<B, false>& b)
{
   using default_ops::eval_add;
   eval_add(a.backend(), b.backend());
   return static_cast<number<B, false>&&>(a);
}
template <class B>
inline number<B, false> operator + (const number<B, false>& a, number<B, false>&& b)
{
   using default_ops::eval_add;
   eval_add(b.backend(), a.backend());
   return static_cast<number<B, false>&&>(b);
}
template <class B>
inline number<B, false> operator + (number<B, false>&& a, number<B, false>&& b)
{
   using default_ops::eval_add;
   eval_add(a.backend(), b.backend());
   return static_cast<number<B, false>&&>(a);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator + (number<B, false>&& a, const V& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   using default_ops::eval_add;
   eval_add(a.backend(), static_cast<canonical_type>(b));
   return static_cast<number<B, false>&&>(a);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator + (const V& a, number<B, false>&& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   using default_ops::eval_add;
   eval_add(b.backend(), static_cast<canonical_type>(a));
   return static_cast<number<B, false>&&>(b);
}
//
// Subtraction:
//
template <class B>
inline number<B, false> operator - (number<B, false>&& a, const number<B, false>& b)
{
   using default_ops::eval_subtract;
   eval_subtract(a.backend(), b.backend());
   return static_cast<number<B, false>&&>(a);
}
template <class B>
inline number<B, false> operator - (const number<B, false>& a, number<B, false>&& b)
{
   using default_ops::eval_subtract;
   eval_subtract(b.backend(), a.backend());
   b.backend().negate();
   return static_cast<number<B, false>&&>(b);
}
template <class B>
inline number<B, false> operator - (number<B, false>&& a, number<B, false>&& b)
{
   using default_ops::eval_subtract;
   eval_subtract(a.backend(), b.backend());
   return static_cast<number<B, false>&&>(a);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator - (number<B, false>&& a, const V& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   using default_ops::eval_subtract;
   eval_subtract(a.backend(), static_cast<canonical_type>(b));
   return static_cast<number<B, false>&&>(a);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator - (const V& a, number<B, false>&& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   using default_ops::eval_subtract;
   eval_subtract(b.backend(), static_cast<canonical_type>(a));
   b.backend().negate();
   return static_cast<number<B, false>&&>(b);
}
//
// Multiply:
//
template <class B>
inline number<B, false> operator * (number<B, false>&& a, const number<B, false>& b)
{
   using default_ops::eval_multiply;
   eval_multiply(a.backend(), b.backend());
   return static_cast<number<B, false>&&>(a);
}
template <class B>
inline number<B, false> operator * (const number<B, false>& a, number<B, false>&& b)
{
   using default_ops::eval_multiply;
   eval_multiply(b.backend(), a.backend());
   return static_cast<number<B, false>&&>(b);
}
template <class B>
inline number<B, false> operator * (number<B, false>&& a, number<B, false>&& b)
{
   using default_ops::eval_multiply;
   eval_multiply(a.backend(), b.backend());
   return static_cast<number<B, false>&&>(a);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator * (number<B, false>&& a, const V& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   using default_ops::eval_multiply;
   eval_multiply(a.backend(), static_cast<canonical_type>(b));
   return static_cast<number<B, false>&&>(a);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator * (const V& a, number<B, false>&& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   using default_ops::eval_multiply;
   eval_multiply(b.backend(), static_cast<canonical_type>(a));
   return static_cast<number<B, false>&&>(b);
}
//
// divide:
//
template <class B>
inline number<B, false> operator / (number<B, false>&& a, const number<B, false>& b)
{
   using default_ops::eval_divide;
   eval_divide(a.backend(), b.backend());
   return static_cast<number<B, false>&&>(a);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator / (number<B, false>&& a, const V& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   using default_ops::eval_divide;
   eval_divide(a.backend(), static_cast<canonical_type>(b));
   return static_cast<number<B, false>&&>(a);
}
//
// modulus:
//
template <class B>
inline number<B, false> operator % (number<B, false>&& a, const number<B, false>& b)
{
   using default_ops::eval_modulus;
   eval_modulus(a.backend(), b.backend());
   return static_cast<number<B, false>&&>(a);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator % (number<B, false>&& a, const V& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   using default_ops::eval_modulus;
   eval_modulus(a.backend(), static_cast<canonical_type>(b));
   return static_cast<number<B, false>&&>(a);
}
//
// Bitwise or:
//
template <class B>
inline number<B, false> operator | (number<B, false>&& a, const number<B, false>& b)
{
   using default_ops::eval_bitwise_or;
   eval_bitwise_or(a.backend(), b.backend());
   return static_cast<number<B, false>&&>(a);
}
template <class B>
inline number<B, false> operator | (const number<B, false>& a, number<B, false>&& b)
{
   using default_ops::eval_bitwise_or;
   eval_bitwise_or(b.backend(), a.backend());
   return static_cast<number<B, false>&&>(b);
}
template <class B>
inline number<B, false> operator | (number<B, false>&& a, number<B, false>&& b)
{
   using default_ops::eval_bitwise_or;
   eval_bitwise_or(a.backend(), b.backend());
   return static_cast<number<B, false>&&>(a);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator | (number<B, false>&& a, const V& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   using default_ops::eval_bitwise_or;
   eval_bitwise_or(a.backend(), static_cast<canonical_type>(b));
   return static_cast<number<B, false>&&>(a);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator | (const V& a, number<B, false>&& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   using default_ops::eval_bitwise_or;
   eval_bitwise_or(b.backend(), static_cast<canonical_type>(a));
   return static_cast<number<B, false>&&>(b);
}
//
// Bitwise xor:
//
template <class B>
inline number<B, false> operator ^ (number<B, false>&& a, const number<B, false>& b)
{
   using default_ops::eval_bitwise_xor;
   eval_bitwise_xor(a.backend(), b.backend());
   return static_cast<number<B, false>&&>(a);
}
template <class B>
inline number<B, false> operator ^ (const number<B, false>& a, number<B, false>&& b)
{
   using default_ops::eval_bitwise_xor;
   eval_bitwise_xor(b.backend(), a.backend());
   return static_cast<number<B, false>&&>(b);
}
template <class B>
inline number<B, false> operator ^ (number<B, false>&& a, number<B, false>&& b)
{
   using default_ops::eval_bitwise_xor;
   eval_bitwise_xor(a.backend(), b.backend());
   return static_cast<number<B, false>&&>(a);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator ^ (number<B, false>&& a, const V& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   using default_ops::eval_bitwise_xor;
   eval_bitwise_xor(a.backend(), static_cast<canonical_type>(b));
   return static_cast<number<B, false>&&>(a);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator ^ (const V& a, number<B, false>&& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   using default_ops::eval_bitwise_xor;
   eval_bitwise_xor(b.backend(), static_cast<canonical_type>(a));
   return static_cast<number<B, false>&&>(b);
}
//
// Bitwise and:
//
template <class B>
inline number<B, false> operator & (number<B, false>&& a, const number<B, false>& b)
{
   using default_ops::eval_bitwise_and;
   eval_bitwise_and(a.backend(), b.backend());
   return static_cast<number<B, false>&&>(a);
}
template <class B>
inline number<B, false> operator & (const number<B, false>& a, number<B, false>&& b)
{
   using default_ops::eval_bitwise_and;
   eval_bitwise_and(b.backend(), a.backend());
   return static_cast<number<B, false>&&>(b);
}
template <class B>
inline number<B, false> operator & (number<B, false>&& a, number<B, false>&& b)
{
   using default_ops::eval_bitwise_and;
   eval_bitwise_and(a.backend(), b.backend());
   return static_cast<number<B, false>&&>(a);
}
template <class B, class V>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator & (number<B, false>&& a, const V& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   using default_ops::eval_bitwise_and;
   eval_bitwise_and(a.backend(), static_cast<canonical_type>(b));
   return static_cast<number<B, false>&&>(a);
}
template <class V, class B>
inline typename enable_if<is_compatible_arithmetic_type<V, number<B, false> >, number<B, false> >::type
   operator & (const V& a, number<B, false>&& b)
{
   typedef typename detail::canonical<V, B>::type canonical_type;
   using default_ops::eval_bitwise_and;
   eval_bitwise_and(b.backend(), static_cast<canonical_type>(a));
   return static_cast<number<B, false>&&>(b);
}
//
// shifts:
//
template <class B, class I>
inline typename enable_if<is_integral<I>, number<B, false> >::type
   operator << (number<B, false>&& a, const I& b)
{
   using default_ops::eval_left_shift;
   eval_left_shift(a.backend(), b);
   return static_cast<number<B, false>&&>(a);
}
template <class B, class I>
inline typename enable_if<is_integral<I>, number<B, false> >::type
   operator >> (number<B, false>&& a, const I& b)
{
   using default_ops::eval_right_shift;
   eval_right_shift(a.backend(), b);
   return static_cast<number<B, false>&&>(a);
}

#endif

}} // namespaces

#endif // BOOST_MP_NO_ET_OPS_HPP
