///////////////////////////////////////////////////////////////
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_

#ifdef _MSC_VER
#  define _SCL_SECURE_NO_WARNINGS
#endif

#ifdef TEST_VLD
#include <vld.h>
#endif

#include <boost/math/special_functions/pow.hpp>
#include <boost/math/common_factor_rt.hpp>
#include "test.hpp"

#if !defined(TEST_MPF_50) && !defined(TEST_MPF) && !defined(TEST_BACKEND) && !defined(TEST_MPZ) && \
   !defined(TEST_CPP_DEC_FLOAT) && !defined(TEST_MPFR) && !defined(TEST_MPFR_50) && !defined(TEST_MPQ) \
   && !defined(TEST_TOMMATH) && !defined(TEST_TOMMATH_BOOST_RATIONAL) && !defined(TEST_MPZ_BOOST_RATIONAL)\
   && !defined(TEST_CPP_INT) && !defined(TEST_CPP_INT_BR) && !defined(TEST_ARITHMETIC_BACKEND)
#  define TEST_MPF_50
#  define TEST_MPF
#  define TEST_BACKEND
#  define TEST_MPZ
#  define TEST_MPFR
#  define TEST_MPFR_50
#  define TEST_CPP_DEC_FLOAT
#  define TEST_MPQ
#  define TEST_TOMMATH
#  define TEST_CPP_INT
#  define TEST_CPP_INT_BR
#  define TEST_ARITHMETIC_BACKEND

#ifdef _MSC_VER
#pragma message("CAUTION!!: No backend type specified so testing everything.... this will take some time!!")
#endif
#ifdef __GNUC__
#pragma warning "CAUTION!!: No backend type specified so testing everything.... this will take some time!!"
#endif

#endif

#if defined(TEST_ARITHMETIC_BACKEND)
# include "../performance/arithmetic_backend.hpp"
#endif
#if defined(TEST_MPF_50) || defined(TEST_MPF) || defined(TEST_MPZ) || defined(TEST_MPQ) || defined(TEST_MPZ_BOOST_RATIONAL)
#include <boost/multiprecision/gmp.hpp>
#include <boost/multiprecision/rational_adapter.hpp>
#endif
#ifdef TEST_BACKEND
#include <boost/multiprecision/concepts/mp_number_archetypes.hpp>
#endif
#ifdef TEST_CPP_DEC_FLOAT
#include <boost/multiprecision/cpp_dec_float.hpp>
#endif
#if defined(TEST_MPFR) || defined(TEST_MPFR_50)
#include <boost/multiprecision/mpfr.hpp>
#endif
#if defined(TEST_TOMMATH) || defined(TEST_TOMMATH_BOOST_RATIONAL)
#include <boost/multiprecision/tommath.hpp>
#include <boost/multiprecision/rational_adapter.hpp>
#endif
#if defined(TEST_CPP_INT) || defined(TEST_CPP_INT_BR)
#include <boost/multiprecision/cpp_int.hpp>
#endif
#if defined(TEST_TOMMATH_BOOST_RATIONAL) || defined(TEST_MPZ_BOOST_RATIONAL)
#include <boost/rational.hpp>

#define NO_MIXED_OPS

template <class T>
bool is_boost_rational(const boost::rational<T>&)
{
   return true;
}

namespace boost{ namespace multiprecision{

#ifdef TEST_TOMMATH_BOOST_RATIONAL
template<>
struct number_category<rational<tom_int> > : public mpl::int_<number_kind_rational> {};
#endif
#ifdef TEST_MPZ_BOOST_RATIONAL
template<>
struct number_category<rational<mpz_int> > : public mpl::int_<number_kind_rational> {};
#endif

}}

#endif

#ifdef BOOST_MSVC
// warning C4127: conditional expression is constant
#pragma warning(disable:4127)
#endif

#define BOOST_TEST_THROW(x, EX)\
   try { x;  BOOST_ERROR("Expected exception not thrown"); } \
   catch(const EX&){}\
   catch(...){ BOOST_ERROR("Incorrect exception type thrown"); }

#undef BOOST_TEST
#define BOOST_TEST(x)\
   try {\
      if(x){}else{ BOOST_ERROR("Value was zero: "); }\
   }\
   catch(const std::exception& e){  \
      BOOST_ERROR("Unexpected exception: ");\
      BOOST_LIGHTWEIGHT_TEST_OSTREAM << e.what() << std::endl;\
   }

bool isfloat(float){ return true; }
bool isfloat(double){ return true; }
bool isfloat(long double){ return true; }
template <class T> bool isfloat(T){ return false; }

#define BOOST_TEST_CLOSE(x, y, tol)\
   if(x == 0){\
      BOOST_TEST(y == 0); }\
   else if(!isfloat(x)){\
      BOOST_TEST(x == y); }\
   else if((x != y) && (::fabsl(static_cast<long double>((x-y)/x)) > tol))\
   {\
       BOOST_ERROR("Expected tolerance was exceeded: ");\
       BOOST_LIGHTWEIGHT_TEST_OSTREAM << std::setprecision(34) << "(x-y)/x = " << ::fabsl(static_cast<long double>((x-y)/x)) \
       << " tolerance = " << tol << std::endl;\
   }

template <class T>
struct is_twos_complement_integer : public boost::mpl::true_ {};

#ifdef TEST_TOMMATH
template <>
struct is_twos_complement_integer<boost::multiprecision::tom_int> : public boost::mpl::false_ {};
#endif

#define BOOST_TEST_EQUAL(a, b) BOOST_TEST((a) == (b))

template <class Real, class Val>
void test_comparisons(Val a, Val b)
{
   Real r1(a);
   Real r2(b);
   Real z(1);

   BOOST_TEST_EQUAL(r1 == r2, a == b);
   BOOST_TEST_EQUAL(r1 != r2, a != b);
   BOOST_TEST_EQUAL(r1 <= r2, a <= b);
   BOOST_TEST_EQUAL(r1 < r2, a < b);
   BOOST_TEST_EQUAL(r1 >= r2, a >= b);
   BOOST_TEST_EQUAL(r1 > r2, a > b);

   BOOST_TEST_EQUAL(r1 == b, a == b);
   BOOST_TEST_EQUAL(r1 != b, a != b);
   BOOST_TEST_EQUAL(r1 <= b, a <= b);
   BOOST_TEST_EQUAL(r1 < b, a < b);
   BOOST_TEST_EQUAL(r1 >= b, a >= b);
   BOOST_TEST_EQUAL(r1 > b, a > b);

   BOOST_TEST_EQUAL(a == r2, a == b);
   BOOST_TEST_EQUAL(a != r2, a != b);
   BOOST_TEST_EQUAL(a <= r2, a <= b);
   BOOST_TEST_EQUAL(a < r2, a < b);
   BOOST_TEST_EQUAL(a >= r2, a >= b);
   BOOST_TEST_EQUAL(a > r2, a > b);

   BOOST_TEST_EQUAL(r1*z == r2, a == b);
   BOOST_TEST_EQUAL(r1*z != r2, a != b);
   BOOST_TEST_EQUAL(r1*z <= r2, a <= b);
   BOOST_TEST_EQUAL(r1*z < r2, a < b);
   BOOST_TEST_EQUAL(r1*z >= r2, a >= b);
   BOOST_TEST_EQUAL(r1*z > r2, a > b);

   BOOST_TEST_EQUAL(r1 == r2*z, a == b);
   BOOST_TEST_EQUAL(r1 != r2*z, a != b);
   BOOST_TEST_EQUAL(r1 <= r2*z, a <= b);
   BOOST_TEST_EQUAL(r1 < r2*z, a < b);
   BOOST_TEST_EQUAL(r1 >= r2*z, a >= b);
   BOOST_TEST_EQUAL(r1 > r2*z, a > b);

   BOOST_TEST_EQUAL(r1*z == r2*z, a == b);
   BOOST_TEST_EQUAL(r1*z != r2*z, a != b);
   BOOST_TEST_EQUAL(r1*z <= r2*z, a <= b);
   BOOST_TEST_EQUAL(r1*z < r2*z, a < b);
   BOOST_TEST_EQUAL(r1*z >= r2*z, a >= b);
   BOOST_TEST_EQUAL(r1*z > r2*z, a > b);

   BOOST_TEST_EQUAL(r1*z == b, a == b);
   BOOST_TEST_EQUAL(r1*z != b, a != b);
   BOOST_TEST_EQUAL(r1*z <= b, a <= b);
   BOOST_TEST_EQUAL(r1*z < b, a < b);
   BOOST_TEST_EQUAL(r1*z >= b, a >= b);
   BOOST_TEST_EQUAL(r1*z > b, a > b);

   BOOST_TEST_EQUAL(a == r2*z, a == b);
   BOOST_TEST_EQUAL(a != r2*z, a != b);
   BOOST_TEST_EQUAL(a <= r2*z, a <= b);
   BOOST_TEST_EQUAL(a < r2*z, a < b);
   BOOST_TEST_EQUAL(a >= r2*z, a >= b);
   BOOST_TEST_EQUAL(a > r2*z, a > b);
}

template <class Real>
void test_complement(Real a, Real b, Real c, const boost::mpl::true_&)
{
   int i = 1020304;
   int j = 56789123;
   int sign_mask = ~0;
   BOOST_TEST(~a == (~i & sign_mask));
   c = a & ~b;
   BOOST_TEST(c == (i & (~j & sign_mask)));
   c = ~(a | b);
   BOOST_TEST(c == (~(i | j) & sign_mask));
}

template <class Real>
void test_complement(Real, Real, Real, const boost::mpl::false_&)
{
}

template <class Real, class T>
void test_integer_ops(const T&){}

template <class T>
bool is_boost_rational(const T&)
{
   return false;
}

template <class Real>
void test_integer_ops(const boost::mpl::int_<boost::multiprecision::number_kind_rational>&)
{
   Real a(2);
   a /= 3;
   BOOST_TEST(numerator(a) == 2);
   BOOST_TEST(denominator(a) == 3);
   Real b(4);
   b /= 6;
   BOOST_TEST(a == b);

   //
   // Boost.Rational has a slightly different error handling stategy,
   // we only test our own:
   //
   if(!is_boost_rational(a))
   {
      BOOST_CHECK_THROW(Real(a / 0), std::runtime_error);
      BOOST_CHECK_THROW(Real("3.14"), std::runtime_error);
      b = "2/3";
      BOOST_CHECK_EQUAL(a, b);
   }
   //
   // Check IO code:
   //
   std::stringstream ss;
   ss << a;
   ss >> b;
   BOOST_CHECK_EQUAL(a, b);
}

template <class Real>
void test_integer_ops(const boost::mpl::int_<boost::multiprecision::number_kind_integer>&)
{
   Real a(20);
   Real b(7);
   Real c(5);
   BOOST_TEST(a % b == 20 % 7);
   BOOST_TEST(a % 7 == 20 % 7);
   BOOST_TEST(a % 7u == 20 % 7);
   BOOST_TEST(a % a == 0);
   BOOST_TEST(a % c == 0);
   BOOST_TEST(a % 5 == 0);
   if(std::numeric_limits<Real>::is_signed)
   {
      BOOST_TEST(-a % c == 0);
      BOOST_TEST(-a % b == -20 % 7);
      BOOST_TEST(-a % -b == -20 % -7);
      BOOST_TEST(a % -b == 20 % -7);
      BOOST_TEST(-a % 7 == -20 % 7);
      BOOST_TEST(-a % -7 == -20 % -7);
      BOOST_TEST(a % -7 == 20 % -7);
      BOOST_TEST(-a % 7u == -20 % 7);
      BOOST_TEST(-a % a == 0);
      BOOST_TEST(-a % 5 == 0);
      BOOST_TEST(-a % -5 == 0);
      BOOST_TEST(a % -5 == 0);

      b = -b;
      BOOST_TEST(a % b == 20 % -7);
      a = -a;
      BOOST_TEST(a % b == -20 % -7);
      BOOST_TEST(a % -7 == -20 % -7);
      b = 7;
      BOOST_TEST(a % b == -20 % 7);
      BOOST_TEST(a % 7 == -20 % 7);
      BOOST_TEST(a % 7u == -20 % 7);

      a = 20;
      a %= b;
      BOOST_TEST(a == 20 % 7);
      a = -20;
      a %= b;
      BOOST_TEST(a == -20 % 7);
      a = 20;
      a %= -b;
      BOOST_TEST(a == 20 % -7);
      a = -20;
      a %= -b;
      BOOST_TEST(a == -20 % -7);
   }

   a = 20;
   a %= 7;
   BOOST_TEST(a == 20 % 7);
   if(std::numeric_limits<Real>::is_signed)
   {
      a = -20;
      a %= 7;
      BOOST_TEST(a == -20 % 7);
      a = 20;
      a %= -7;
      BOOST_TEST(a == 20 % -7);
      a = -20;
      a %= -7;
      BOOST_TEST(a == -20 % -7);
   }
#ifndef BOOST_NO_LONG_LONG
   a = 20;
   a %= 7uLL;
   BOOST_TEST(a == 20 % 7);
   if(std::numeric_limits<Real>::is_signed)
   {
      a = -20;
      a %= 7uLL;
      BOOST_TEST(a == -20 % 7);
      a = 20;
      a %= -7LL;
      BOOST_TEST(a == 20 % -7);
      a = -20;
      a %= -7LL;
      BOOST_TEST(a == -20 % -7);
   }
#endif
   a = 20;
   BOOST_TEST(++a == 21);
   BOOST_TEST(--a == 20);
   BOOST_TEST(a++ == 20);
   BOOST_TEST(a == 21);
   BOOST_TEST(a-- == 21);
   BOOST_TEST(a == 20);
   a = 2000;
   a <<= 20;
   BOOST_TEST(a == 2000L << 20);
   a >>= 20;
   BOOST_TEST(a == 2000);
   a <<= 20u;
   BOOST_TEST(a == 2000L << 20);
   a >>= 20u;
   BOOST_TEST(a == 2000);
   BOOST_TEST_THROW(a <<= -20, std::out_of_range);
   BOOST_TEST_THROW(a >>= -20, std::out_of_range);
#ifndef BOOST_NO_LONG_LONG
   if(sizeof(long long) > sizeof(std::size_t))
   {
      // extreme values should trigger an exception:
      BOOST_TEST_THROW(a >>= (1uLL << (sizeof(long long) * CHAR_BIT - 2)), std::out_of_range);
      BOOST_TEST_THROW(a <<= (1uLL << (sizeof(long long) * CHAR_BIT - 2)), std::out_of_range);
   }
#endif
   a = 20;
   b = a << 20;
   BOOST_TEST(b == (20 << 20));
   b = a >> 2;
   BOOST_TEST(b == (20 >> 2));
   b = (a + 2) << 10;
   BOOST_TEST(b == (22 << 10));
   b = (a + 3) >> 3;
   BOOST_TEST(b == (23 >> 3));
   //
   // Bit fiddling:
   //
   int i = 1020304;
   int j = 56789123;
   int k = 4523187;
   a = i;
   b = j;
   c = a;
   c &= b;
   BOOST_TEST(c == (i & j));
   c = a;
   c &= j;
   BOOST_TEST(c == (i & j));
   c = a;
   c &= a + b;
   BOOST_TEST(c == (i & (i + j)));
   BOOST_TEST((a & b) == (i & j));
   c = k;
   a = a & (b + k);
   BOOST_TEST(a == (i & (j + k)));
   a = i;
   a = (b + k) & a;
   BOOST_TEST(a == (i & (j + k)));
   a = i;
   c = a & b & k;
   BOOST_TEST(c == (i&j&k));

   test_complement<Real>(a, b, c, typename is_twos_complement_integer<Real>::type());

   a = i;
   b = j;
   c = a;
   c |= b;
   BOOST_TEST(c == (i | j));
   c = a;
   c |= j;
   BOOST_TEST(c == (i | j));
   c = a;
   c |= a + b;
   BOOST_TEST(c == (i | (i + j)));
   BOOST_TEST((a | b) == (i | j));
   c = k;
   a = a | (b + k);
   BOOST_TEST(a == (i | (j + k)));
   a = i;
   a = (b + k) | a;
   BOOST_TEST(a == (i | (j + k)));
   a = i;
   c = a | b | k;
   BOOST_TEST(c == (i|j|k));

   a = i;
   b = j;
   c = a;
   c ^= b;
   BOOST_TEST(c == (i ^ j));
   c = a;
   c ^= j;
   BOOST_TEST(c == (i ^ j));
   c = a;
   c ^= a + b;
   BOOST_TEST(c == (i ^ (i + j)));
   BOOST_TEST((a ^ b) == (i ^ j));
   c = k;
   a = a ^ (b + k);
   BOOST_TEST(a == (i ^ (j + k)));
   a = i;
   a = (b + k) ^ a;
   BOOST_TEST(a == (i ^ (j + k)));
   a = i;
   c = a ^ b ^ k;
   BOOST_TEST(c == (i^j^k));
   a = i;
   b = j;
   c = k;
   //
   // Non-member functions:
   //
   a = 400;
   b = 45;
   BOOST_TEST(gcd(a, b) == boost::math::gcd(400, 45));
   BOOST_TEST(lcm(a, b) == boost::math::lcm(400, 45));
   BOOST_TEST(gcd(a, 45) == boost::math::gcd(400, 45));
   BOOST_TEST(lcm(a, 45) == boost::math::lcm(400, 45));
   BOOST_TEST(gcd(400, b) == boost::math::gcd(400, 45));
   BOOST_TEST(lcm(400, b) == boost::math::lcm(400, 45));
   Real r;
   divide_qr(a, b, c, r);
   BOOST_TEST(c == a / b);
   BOOST_TEST(r = a % b);
   divide_qr(a + 0, b, c, r);
   BOOST_TEST(c == a / b);
   BOOST_TEST(r = a % b);
   divide_qr(a, b+0, c, r);
   BOOST_TEST(c == a / b);
   BOOST_TEST(r = a % b);
   divide_qr(a+0, b+0, c, r);
   BOOST_TEST(c == a / b);
   BOOST_TEST(r = a % b);
   BOOST_TEST(integer_modulus(a, 57) == a % 57);
   if(std::numeric_limits<Real>::is_signed)
   {
      a = -20;
      BOOST_TEST(abs(a) == 20);
      BOOST_TEST(abs(-a) == 20);
      BOOST_TEST(abs(+a) == 20);
      a = 20;
      BOOST_TEST(abs(a) == 20);
      BOOST_TEST(abs(-a) == 20);
      BOOST_TEST(abs(+a) == 20);
      a = -400;
      b = 45;
      BOOST_TEST(gcd(a, b) == boost::math::gcd(-400, 45));
      BOOST_TEST(lcm(a, b) == boost::math::lcm(-400, 45));
      BOOST_TEST(gcd(a, 45) == boost::math::gcd(-400, 45));
      BOOST_TEST(lcm(a, 45) == boost::math::lcm(-400, 45));
      BOOST_TEST(gcd(-400, b) == boost::math::gcd(-400, 45));
      BOOST_TEST(lcm(-400, b) == boost::math::lcm(-400, 45));
      divide_qr(a, b, c, r);
      BOOST_TEST(c == a / b);
      BOOST_TEST(r = a % b);
      BOOST_TEST(integer_modulus(a, 57) == abs(a % 57));
      b = -57;
      divide_qr(a, b, c, r);
      BOOST_TEST(c == a / b);
      BOOST_TEST(r = a % b);
      BOOST_TEST(integer_modulus(a, -57) == abs(a % -57));
      a = 458;
      divide_qr(a, b, c, r);
      BOOST_TEST(c == a / b);
      BOOST_TEST(r = a % b);
      BOOST_TEST(integer_modulus(a, -57) == abs(a % -57));
   }
   for(unsigned i = 0; i < 20; ++i)
   {
      if(std::numeric_limits<Real>::is_specialized && (!std::numeric_limits<Real>::is_bounded || ((int)i * 17 < std::numeric_limits<Real>::digits)))
      {
         BOOST_TEST(lsb(Real(1) << (i * 17)) == i * 17);
         BOOST_TEST(bit_test(Real(1) << (i * 17), i * 17));
         BOOST_TEST(!bit_test(Real(1) << (i * 17), i * 17 + 1));
         BOOST_TEST(!bit_test(Real(1) << (i * 17), i * 17 - 1));
         Real zero(0);
         BOOST_TEST(bit_test(bit_set(zero, i * 17), i * 17));
         zero = 0;
         BOOST_TEST(bit_flip(zero, i*17) == Real(1) << i * 17);
         zero = Real(1) << i * 17;
         BOOST_TEST(bit_flip(zero, i * 17) == 0);
         zero = Real(1) << i * 17;
         BOOST_TEST(bit_unset(zero, i * 17) == 0);
      }
   }
   //
   // pow, powm:
   //
   BOOST_TEST(pow(Real(3), 4) == 81);
   BOOST_TEST(pow(Real(3) + Real(0), 4) == 81);
   BOOST_TEST(powm(Real(3), Real(4), Real(13)) == 81 % 13);
   BOOST_TEST(powm(Real(3), Real(4), 13) == 81 % 13);
   BOOST_TEST(powm(Real(3), Real(4), Real(13) + 0) == 81 % 13);
   BOOST_TEST(powm(Real(3), Real(4) + 0, Real(13)) == 81 % 13);
   BOOST_TEST(powm(Real(3), Real(4) + 0, 13) == 81 % 13);
   BOOST_TEST(powm(Real(3), Real(4) + 0, Real(13) + 0) == 81 % 13);
   BOOST_TEST(powm(Real(3), 4 + 0, Real(13)) == 81 % 13);
   BOOST_TEST(powm(Real(3), 4 + 0, 13) == 81 % 13);
   BOOST_TEST(powm(Real(3), 4 + 0, Real(13) + 0) == 81 % 13);
   BOOST_TEST(powm(Real(3) + 0, Real(4), Real(13)) == 81 % 13);
   BOOST_TEST(powm(Real(3) + 0, Real(4), 13) == 81 % 13);
   BOOST_TEST(powm(Real(3) + 0, Real(4), Real(13) + 0) == 81 % 13);
   BOOST_TEST(powm(Real(3) + 0, Real(4) + 0, Real(13)) == 81 % 13);
   BOOST_TEST(powm(Real(3) + 0, Real(4) + 0, 13) == 81 % 13);
   BOOST_TEST(powm(Real(3) + 0, Real(4) + 0, Real(13) + 0) == 81 % 13);
   BOOST_TEST(powm(Real(3) + 0, 4 + 0, Real(13)) == 81 % 13);
   BOOST_TEST(powm(Real(3) + 0, 4 + 0, 13) == 81 % 13);
   BOOST_TEST(powm(Real(3) + 0, 4 + 0, Real(13) + 0) == 81 % 13);
   //
   // Things that are expected errors:
   //
   BOOST_CHECK_THROW(Real("3.14"), std::runtime_error);
   BOOST_CHECK_THROW(Real("3L"), std::runtime_error);
   BOOST_CHECK_THROW(Real(Real(20) / 0u), std::runtime_error);
}

template <class Real, class T>
void test_float_ops(const T&){}

template <class Real>
void test_float_ops(const boost::mpl::int_<boost::multiprecision::number_kind_floating_point>&)
{
   BOOST_TEST(abs(Real(2)) == 2);
   BOOST_TEST(abs(Real(-2)) == 2);
   BOOST_TEST(fabs(Real(2)) == 2);
   BOOST_TEST(fabs(Real(-2)) == 2);
   BOOST_TEST(floor(Real(5) / 2) == 2);
   BOOST_TEST(ceil(Real(5) / 2) == 3);
   BOOST_TEST(floor(Real(-5) / 2) == -3);
   BOOST_TEST(ceil(Real(-5) / 2) == -2);
   BOOST_TEST(trunc(Real(5) / 2) == 2);
   BOOST_TEST(trunc(Real(-5) / 2) == -2);
   //
   // ldexp and frexp, these pretty much have to be implemented by each backend:
   //
   BOOST_TEST(ldexp(Real(2), 5) == 64);
   BOOST_TEST(ldexp(Real(2), -5) == Real(2) / 32);
   Real v(512);
   int exp;
   Real r = frexp(v, &exp);
   BOOST_TEST(r == 0.5);
   BOOST_TEST(exp == 10);
   BOOST_TEST(v == 512);
   v = 1 / v;
   r = frexp(v, &exp);
   BOOST_TEST(r == 0.5);
   BOOST_TEST(exp == -8);
   typedef typename Real::backend_type::exponent_type e_type;
   BOOST_TEST(ldexp(Real(2), e_type(5)) == 64);
   BOOST_TEST(ldexp(Real(2), e_type(-5)) == Real(2) / 32);
   v = 512;
   e_type exp2;
   r = frexp(v, &exp2);
   BOOST_TEST(r == 0.5);
   BOOST_TEST(exp2 == 10);
   BOOST_TEST(v == 512);
   v = 1 / v;
   r = frexp(v, &exp2);
   BOOST_TEST(r == 0.5);
   BOOST_TEST(exp2 == -8);
   //
   // pow and exp:
   //
   v = 3.25;
   r = pow(v, 0);
   BOOST_TEST(r == 1);
   r = pow(v, 1);
   BOOST_TEST(r == 3.25);
   r = pow(v, 2);
   BOOST_TEST(r == boost::math::pow<2>(3.25));
   r = pow(v, 3);
   BOOST_TEST(r == boost::math::pow<3>(3.25));
   r = pow(v, 4);
   BOOST_TEST(r == boost::math::pow<4>(3.25));
   r = pow(v, 5);
   BOOST_TEST(r == boost::math::pow<5>(3.25));
   r = pow(v, 6);
   BOOST_TEST(r == boost::math::pow<6>(3.25));
   r = pow(v, 25);
   BOOST_TEST(r == boost::math::pow<25>(Real(3.25)));
   //
   // Things that are expected errors:
   //
   BOOST_CHECK_THROW(Real("3.14L"), std::runtime_error);
   if(std::numeric_limits<Real>::is_specialized)
   {
      if(std::numeric_limits<Real>::has_infinity)
      {
         BOOST_CHECK(boost::math::isinf(Real(20) / 0u));
      }
      else
      {
         BOOST_CHECK_THROW(Real(Real(20) / 0u), std::runtime_error);
      }
   }
}

template <class T>
struct lexical_cast_target_type
{
   typedef typename boost::mpl::if_<
      boost::is_signed<T>,
      boost::intmax_t,
      typename boost::mpl::if_<
         boost::is_unsigned<T>,
         boost::uintmax_t,
         T
      >::type
   >::type type;
};

template <class Real, class Num>
void test_negative_mixed(boost::mpl::true_ const&)
{
   if(std::numeric_limits<Real>::is_specialized && !std::numeric_limits<Real>::is_signed)
      return;
   typedef typename lexical_cast_target_type<Num>::type target_type;
   std::cout << "Testing mixed arithmetic with type: " << typeid(Real).name()  << " and " << typeid(Num).name() << std::endl;
   Num n1 = -static_cast<Num>(1uLL << (std::numeric_limits<Num>::digits - 1));
   Num n2 = -1;
   Num n3 = 0;
   Num n4 = -20;
   Num n5 = -8;

   test_comparisons<Real>(n1, n2);
   test_comparisons<Real>(n1, n3);
   test_comparisons<Real>(n3, n1);
   test_comparisons<Real>(n2, n1);
   test_comparisons<Real>(n1, n1);
   test_comparisons<Real>(n3, n3);

   // Default construct:
   BOOST_TEST(Real(n1) == n1);
   BOOST_TEST(Real(n2) == n2);
   BOOST_TEST(Real(n3) == n3);
   BOOST_TEST(Real(n4) == n4);
   BOOST_TEST(n1 == Real(n1));
   BOOST_TEST(n2 == Real(n2));
   BOOST_TEST(n3 == Real(n3));
   BOOST_TEST(n4 == Real(n4));
   BOOST_TEST(Real(n1).template convert_to<Num>() == n1);
   BOOST_TEST(Real(n2).template convert_to<Num>() == n2);
   BOOST_TEST(Real(n3).template convert_to<Num>() == n3);
   BOOST_TEST(Real(n4).template convert_to<Num>() == n4);
#ifndef BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
   BOOST_TEST(static_cast<Num>(Real(n1)) == n1);
   BOOST_TEST(static_cast<Num>(Real(n2)) == n2);
   BOOST_TEST(static_cast<Num>(Real(n3)) == n3);
   BOOST_TEST(static_cast<Num>(Real(n4)) == n4);
#endif
#if defined(TEST_MPFR) || defined(TEST_MPFR_50)
   Num tol = 10 * std::numeric_limits<Num>::epsilon();
#else
   Num tol = 0;
#endif
   std::ios_base::fmtflags f = boost::is_floating_point<Num>::value ? std::ios_base::scientific : std::ios_base::fmtflags(0);
   if(std::numeric_limits<target_type>::digits <= std::numeric_limits<Real>::digits)
   {
      BOOST_TEST_CLOSE(n1, boost::lexical_cast<target_type>(Real(n1).str(0, f)), tol);
   }
   BOOST_TEST_CLOSE(n2, boost::lexical_cast<target_type>(Real(n2).str(0, f)), 0);
   BOOST_TEST_CLOSE(n3, boost::lexical_cast<target_type>(Real(n3).str(0, f)), 0);
   BOOST_TEST_CLOSE(n4, boost::lexical_cast<target_type>(Real(n4).str(0, f)), 0);
   // Assignment:
   Real r(0);
   BOOST_TEST(r != n1);
   r = n1;
   BOOST_TEST(r == n1);
   r = n2;
   BOOST_TEST(r == n2);
   r = n3;
   BOOST_TEST(r == n3);
   r = n4;
   BOOST_TEST(r == n4);
   // Addition:
   r = n2;
   BOOST_TEST(r + n4 == n2 + n4);
   BOOST_TEST(Real(r + n4) == n2 + n4);
   r += n4;
   BOOST_TEST(r == n2 + n4);
   // subtraction:
   r = n4;
   BOOST_TEST(r - n5 == n4 - n5);
   BOOST_TEST(Real(r - n5) == n4 - n5);
   r -= n5;
   BOOST_TEST(r == n4 - n5);
   // Multiplication:
   r = n2;
   BOOST_TEST(r * n4 == n2 * n4);
   BOOST_TEST(Real(r * n4) == n2 * n4);
   r *= n4;
   BOOST_TEST(r == n2 * n4);
   // Division:
   r = n1;
   BOOST_TEST(r / n5 == n1 / n5);
   BOOST_TEST(Real(r / n5) == n1 / n5);
   r /= n5;
   BOOST_TEST(r == n1 / n5);
   //
   // Extra cases for full coverage:
   //
   r = Real(n4) + n5;
   BOOST_TEST(r == n4 + n5);
   r = n4 + Real(n5);
   BOOST_TEST(r == n4 + n5);
   r = Real(n4) - n5;
   BOOST_TEST(r == n4 - n5);
   r = n4 - Real(n5);
   BOOST_TEST(r == n4 - n5);
   r = n4 * Real(n5);
   BOOST_TEST(r == n4 * n5);
   r = (4 * n4) / Real(4);
   BOOST_TEST(r == n4);
}

template <class Real, class Num>
void test_negative_mixed(boost::mpl::false_ const&)
{
}

template <class Real, class Num>
void test_mixed()
{
   typedef typename lexical_cast_target_type<Num>::type target_type;
   
   if(std::numeric_limits<Real>::digits < std::numeric_limits<Num>::digits)
      return;

   std::cout << "Testing mixed arithmetic with type: " << typeid(Real).name()  << " and " << typeid(Num).name() << std::endl;
   Num n1 = static_cast<Num>(1uLL << (std::numeric_limits<Num>::digits - 1));
   Num n2 = 1;
   Num n3 = 0;
   Num n4 = 20;
   Num n5 = 8;
   
   test_comparisons<Real>(n1, n2);
   test_comparisons<Real>(n1, n3);
   test_comparisons<Real>(n1, n1);
   test_comparisons<Real>(n3, n1);
   test_comparisons<Real>(n2, n1);
   test_comparisons<Real>(n3, n3);

   // Default construct:
   BOOST_TEST(Real(n1) == n1);
   BOOST_TEST(Real(n2) == n2);
   BOOST_TEST(Real(n3) == n3);
   BOOST_TEST(Real(n4) == n4);
   BOOST_TEST(Real(n1).template convert_to<Num>() == n1);
   BOOST_TEST(Real(n2).template convert_to<Num>() == n2);
   BOOST_TEST(Real(n3).template convert_to<Num>() == n3);
   BOOST_TEST(Real(n4).template convert_to<Num>() == n4);
#ifndef BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
   BOOST_TEST(static_cast<Num>(Real(n1)) == n1);
   BOOST_TEST(static_cast<Num>(Real(n2)) == n2);
   BOOST_TEST(static_cast<Num>(Real(n3)) == n3);
   BOOST_TEST(static_cast<Num>(Real(n4)) == n4);
#endif
   BOOST_TEST(n1 == Real(n1));
   BOOST_TEST(n2 == Real(n2));
   BOOST_TEST(n3 == Real(n3));
   BOOST_TEST(n4 == Real(n4));
#if defined(TEST_MPFR) || defined(TEST_MPFR_50)
   Num tol = 10 * std::numeric_limits<Num>::epsilon();
#else
   Num tol = 0;
#endif
   std::ios_base::fmtflags f = boost::is_floating_point<Num>::value ? std::ios_base::scientific : std::ios_base::fmtflags(0);
   if(std::numeric_limits<target_type>::digits <= std::numeric_limits<Real>::digits)
   {
      BOOST_TEST_CLOSE(n1, boost::lexical_cast<target_type>(Real(n1).str(0, f)), tol);
   }
   BOOST_TEST_CLOSE(n2, boost::lexical_cast<target_type>(Real(n2).str(0, f)), 0);
   BOOST_TEST_CLOSE(n3, boost::lexical_cast<target_type>(Real(n3).str(0, f)), 0);
   BOOST_TEST_CLOSE(n4, boost::lexical_cast<target_type>(Real(n4).str(0, f)), 0);
   // Assignment:
   Real r(0);
   BOOST_TEST(r != n1);
   r = n1;
   BOOST_TEST(r == n1);
   r = n2;
   BOOST_TEST(r == n2);
   r = n3;
   BOOST_TEST(r == n3);
   r = n4;
   BOOST_TEST(r == n4);
   // Addition:
   r = n2;
   BOOST_TEST(r + n4 == n2 + n4);
   BOOST_TEST(Real(r + n4) == n2 + n4);
   r += n4;
   BOOST_TEST(r == n2 + n4);
   // subtraction:
   r = n4;
   BOOST_TEST(r - n5 == n4 - n5);
   BOOST_TEST(Real(r - n5) == n4 - n5);
   r -= n5;
   BOOST_TEST(r == n4 - n5);
   // Multiplication:
   r = n2;
   BOOST_TEST(r * n4 == n2 * n4);
   BOOST_TEST(Real(r * n4) == n2 * n4);
   r *= n4;
   BOOST_TEST(r == n2 * n4);
   // Division:
   r = n1;
   BOOST_TEST(r / n5 == n1 / n5);
   BOOST_TEST(Real(r / n5) == n1 / n5);
   r /= n5;
   BOOST_TEST(r == n1 / n5);
   //
   // special cases for full coverage:
   //
   r = n5 + Real(n4);
   BOOST_TEST(r == n4 + n5);
   r = n4 - Real(n5);
   BOOST_TEST(r == n4 - n5);
   r = n4 * Real(n5);
   BOOST_TEST(r == n4 * n5);
   r = (4 * n4) / Real(4);
   BOOST_TEST(r == n4);
   test_negative_mixed<Real, Num>(boost::mpl::bool_<std::numeric_limits<Num>::is_signed>());
}

template <class Real>
void test()
{
#ifndef NO_MIXED_OPS
   test_mixed<Real, unsigned char>();
   test_mixed<Real, signed char>();
   test_mixed<Real, char>();
   test_mixed<Real, short>();
   test_mixed<Real, unsigned short>();
   test_mixed<Real, int>();
   test_mixed<Real, unsigned int>();
   test_mixed<Real, long>();
   test_mixed<Real, unsigned long>();
#ifdef BOOST_HAS_LONG_LONG
   test_mixed<Real, long long>();
   test_mixed<Real, unsigned long long>();
#endif
   test_mixed<Real, float>();
   test_mixed<Real, double>();
   test_mixed<Real, long double>();
#endif
   //
   // Integer only functions:
   //
   test_integer_ops<Real>(typename boost::multiprecision::number_category<Real>::type());
   //
   // Real number only functions:
   //
   test_float_ops<Real>(typename boost::multiprecision::number_category<Real>::type());
   //
   // Test basic arithmetic:
   //
   Real a(8);
   Real b(64);
   Real c(500);
   Real d(1024);
   BOOST_TEST(a + b == 72);
   a += b;
   BOOST_TEST(a == 72);
   BOOST_TEST(a - b == 8);
   a -= b;
   BOOST_TEST(a == 8);
   BOOST_TEST(a * b == 8*64L);
   a *= b;
   BOOST_TEST(a == 8*64L);
   BOOST_TEST(a / b == 8);
   a /= b;
   BOOST_TEST(a == 8);
   Real ac(a);
   BOOST_TEST(ac == a);
   if(std::numeric_limits<Real>::is_signed)
   {
      BOOST_TEST(-a == -8);
   }
   ac = a * c;
   BOOST_TEST(ac == 8*500L);
   ac = 8*500L;
   ac = ac + b + c;
   BOOST_TEST(ac == 8*500L+64+500);
   ac = a;
   ac = b + c + ac;
   BOOST_TEST(ac == 8+64+500);
   ac = ac - b + c;
   BOOST_TEST(ac == 8+64+500-64+500);
   ac = a;
   ac = b + c - ac;
   BOOST_TEST(ac == -8+64+500);
   ac = a;
   ac = ac * b;
   BOOST_TEST(ac == 8*64);
   ac = a;
   ac *= b * ac;
   BOOST_TEST(ac == 8*8*64);
   ac = b;
   ac = ac / a;
   BOOST_TEST(ac == 64/8);
   ac = b;
   ac /= ac / a;
   BOOST_TEST(ac == 64 / (64/8));
   ac = a;
   ac = b + ac * a;
   BOOST_TEST(ac == 64 * 2);
   ac = a;
   ac = b - ac * a;
   BOOST_TEST(ac == 0);
   ac = a;
   ac = b * (ac + a);
   BOOST_TEST(ac == 64 * (16));
   ac = a;
   ac = b / (ac * 1);
   BOOST_TEST(ac == 64 / 8);
   ac = a;
   ac = ac + b;
   BOOST_TEST(ac == 8 + 64);
   ac = a;
   ac = a + ac;
   BOOST_TEST(ac == 16);
   if(std::numeric_limits<Real>::is_signed)
   {
      ac = a;
      ac = ac - b;
      BOOST_TEST(ac == 8 - 64);
   }
   ac = a;
   ac = a - ac;
   BOOST_TEST(ac == 0);
   ac = a;
   ac += a + b;
   BOOST_TEST(ac == 80);
   ac = a;
   ac += b + a;
   BOOST_TEST(ac == 80);
   if(std::numeric_limits<Real>::is_signed)
   {
      ac = a;
      ac -= a + b;
      BOOST_TEST(ac == -64);
      ac = a;
      ac -= b - a;
      BOOST_TEST(ac == 16 - 64);
   }
   ac = +a;
   BOOST_TEST(ac == 8);
   if(std::numeric_limits<Real>::is_signed)
   {
      ac = -a;
      BOOST_TEST(ac == -8);
   }
   ac = 8;
   ac = a * ac;
   BOOST_TEST(ac == 8*8);
   ac = a;
   ac = a;
   ac += +a;
   BOOST_TEST(ac == 16);
   ac = a;
   ac += -a;
   BOOST_TEST(ac == 0);
   ac = a;
   ac += b - a;
   BOOST_TEST(ac == 8 + 64-8);
   ac = a;
   ac += b*c;
   BOOST_TEST(ac == 8 + 64 * 500);
   ac = a;
   ac = a;
   ac -= +a;
   BOOST_TEST(ac == 0);
   ac = a;
   if(std::numeric_limits<Real>::is_signed)
   {
      ac -= -a;
      BOOST_TEST(ac == 16);
   }
   ac = a;
   ac -= c - b;
   BOOST_TEST(ac == 8 - (500-64));
   ac = a;
   ac -= b*c;
   BOOST_TEST(ac == 8 - 500*64);
   ac = a;
   ac += ac * b;
   BOOST_TEST(ac == 8 + 8 * 64);
   ac = a;
   ac -= ac * b;
   BOOST_TEST(ac == 8 - 8 * 64);
   ac = a * 8;
   ac *= +a;
   BOOST_TEST(ac == 64 * 8);
   ac = a;
   ac *= -a;
   BOOST_TEST(ac == -64);
   ac = a;
   ac *= b * c;
   BOOST_TEST(ac == 8 * 64 * 500);
   ac = a;
   ac *= b / a;
   BOOST_TEST(ac == 8 * 64 / 8);
   ac = a;
   ac *= b + c;
   BOOST_TEST(ac == 8 * (64 + 500));
   ac = b;
   ac /= +a;
   BOOST_TEST(ac == 8);
   if(std::numeric_limits<Real>::is_signed)
   {
      ac = b;
      ac /= -a;
      BOOST_TEST(ac == -8);
   }
   ac = b;
   ac /= b / a;
   BOOST_TEST(ac == 64 / (64/8));
   ac = b;
   ac /= a + Real(0);
   BOOST_TEST(ac == 8);
   //
   // simple tests with immediate values, these calls can be optimised in many backends:
   //
   ac = a + b;
   BOOST_TEST(ac == 72);
   ac = a + +b;
   BOOST_TEST(ac == 72);
   ac = +a + b;
   BOOST_TEST(ac == 72);
   ac = +a + +b;
   BOOST_TEST(ac == 72);
   if(std::numeric_limits<Real>::is_signed)
   {
      ac = a + -b;
      BOOST_TEST(ac == 8 - 64);
      ac = -a + b;
      BOOST_TEST(ac == -8+64);
      ac = -a + -b;
      BOOST_TEST(ac == -72);
      ac = a + - + -b; // lots of unary operators!!
      BOOST_TEST(ac == 72);
   }
   ac = a;
   ac = b / ac;
   BOOST_TEST(ac == b / a);
   //
   // Comparisons:
   //
   BOOST_TEST((a == b) == false);
   BOOST_TEST((a != b) == true);
   BOOST_TEST((a <= b) == true);
   BOOST_TEST((a < b) == true);
   BOOST_TEST((a >= b) == false);
   BOOST_TEST((a > b) == false);

   BOOST_TEST((a+b == b) == false);
   BOOST_TEST((a+b != b) == true);
   BOOST_TEST((a+b >= b) == true);
   BOOST_TEST((a+b > b) == true);
   BOOST_TEST((a+b <= b) == false);
   BOOST_TEST((a+b < b) == false);

   BOOST_TEST((a == b+a) == false);
   BOOST_TEST((a != b+a) == true);
   BOOST_TEST((a <= b+a) == true);
   BOOST_TEST((a < b+a) == true);
   BOOST_TEST((a >= b+a) == false);
   BOOST_TEST((a > b+a) == false);

   BOOST_TEST((a+b == b+a) == true);
   BOOST_TEST((a+b != b+a) == false);
   BOOST_TEST((a+b <= b+a) == true);
   BOOST_TEST((a+b < b+a) == false);
   BOOST_TEST((a+b >= b+a) == true);
   BOOST_TEST((a+b > b+a) == false);

   BOOST_TEST((8 == b+a) == false);
   BOOST_TEST((8 != b+a) == true);
   BOOST_TEST((8 <= b+a) == true);
   BOOST_TEST((8 < b+a) == true);
   BOOST_TEST((8 >= b+a) == false);
   BOOST_TEST((8 > b+a) == false);
   BOOST_TEST((800 == b+a) == false);
   BOOST_TEST((800 != b+a) == true);
   BOOST_TEST((800 >= b+a) == true);
   BOOST_TEST((800 > b+a) == true);
   BOOST_TEST((800 <= b+a) == false);
   BOOST_TEST((800 < b+a) == false);
   BOOST_TEST((72 == b+a) == true);
   BOOST_TEST((72 != b+a) == false);
   BOOST_TEST((72 <= b+a) == true);
   BOOST_TEST((72 < b+a) == false);
   BOOST_TEST((72 >= b+a) == true);
   BOOST_TEST((72 > b+a) == false);
#ifndef NO_MIXED_OPS
   //
   // Test sign and zero functions, plus use in boolian context:
   //
   a = 20;
   BOOST_TEST(a.sign() > 0);
   BOOST_TEST(!a.is_zero());
   if(std::numeric_limits<Real>::is_signed)
   {
      a = -20;
      BOOST_TEST(a.sign() < 0);
      BOOST_TEST(!a.is_zero());
   }
   a = 0;
   BOOST_TEST(a.sign() == 0);
   BOOST_TEST(a.is_zero());
#endif
   a = 0;
   if(a)
   {
      BOOST_ERROR("Unexpected non-zero result");
   }
   if(!a){}
   else
   {
      BOOST_ERROR("Unexpected zero result");
   }
   b = 2;
   if(!b)
   {
      BOOST_ERROR("Unexpected zero result");
   }
   if(b){}
   else
   {
      BOOST_ERROR("Unexpected non-zero result");
   }
   if(a && b)
   {
      BOOST_ERROR("Unexpected zero result");
   }
   if(!(a || b))
   {
      BOOST_ERROR("Unexpected zero result");
   }
   if(a + b){}
   else
   {
      BOOST_ERROR("Unexpected zero result");
   }
   if(b - 2)
   {
      BOOST_ERROR("Unexpected non-zero result");
   }
   //
   // Test iostreams:
   //
   std::stringstream ss;
   a = 20;
   b = 2;
   ss << a;
   ss >> c;
   BOOST_TEST(a == c);
   ss.clear();
   ss << a + b;
   ss >> c;
   BOOST_TEST(c == 22);
   BOOST_TEST(c == a + b);
}


int main()
{
#ifdef TEST_ARITHMETIC_BACKEND
   test<boost::multiprecision::mp_number<boost::multiprecision::arithmetic_backend<double> > >();
   test<boost::multiprecision::mp_number<boost::multiprecision::arithmetic_backend<int> > >();
   test<boost::multiprecision::mp_number<boost::multiprecision::arithmetic_backend<unsigned int> > >();
#endif
#ifdef TEST_BACKEND
   test<boost::multiprecision::mp_number<boost::multiprecision::concepts::mp_number_backend_float_architype> >();
#endif
#ifdef TEST_MPF_50
   test<boost::multiprecision::mpf_float_50>();
#endif
#ifdef TEST_MPF
   boost::multiprecision::mpf_float::default_precision(1000);
   BOOST_TEST(boost::multiprecision::mpf_float::default_precision() == 1000);
   test<boost::multiprecision::mpf_float>();
#endif
#ifdef TEST_MPZ
   test<boost::multiprecision::mpz_int>();
   test<boost::multiprecision::mp_number<boost::multiprecision::rational_adapter<boost::multiprecision::gmp_int> > >();
#endif
#ifdef TEST_MPQ
   test<boost::multiprecision::mpq_rational>();
#endif
#ifdef TEST_CPP_DEC_FLOAT
   test<boost::multiprecision::cpp_dec_float_50>();
   test<boost::multiprecision::mp_number<boost::multiprecision::cpp_dec_float<100>, false> >();
#endif
#ifdef TEST_MPFR
   test<boost::multiprecision::mpfr_float>();
#endif
#ifdef TEST_MPFR_50
   test<boost::multiprecision::mpfr_float_50>();
#endif
#ifdef TEST_TOMMATH
   test<boost::multiprecision::tom_int>();
   test<boost::multiprecision::mp_number<boost::multiprecision::rational_adapter<boost::multiprecision::tommath_int> > >();
#endif
#ifdef TEST_TOMMATH_BOOST_RATIONAL
   test<boost::rational<boost::multiprecision::tom_int> >();
#endif
#ifdef TEST_MPZ_BOOST_RATIONAL
   test<boost::rational<boost::multiprecision::mpz_int> >();
#endif
#ifdef TEST_CPP_INT
   test<boost::multiprecision::cpp_int>();
   test<boost::multiprecision::mp_int256_t >();
   test<boost::multiprecision::mp_uint512_t >();
   test<boost::multiprecision::cpp_rational>();
   test<boost::multiprecision::mp_number<boost::multiprecision::cpp_int_backend<>, false> >();
   test<boost::multiprecision::mp_number<boost::multiprecision::cpp_int_backend<500, true, void> > >();

   // Again with "trivial" backends:
   test<boost::multiprecision::mp_number<boost::multiprecision::cpp_int_backend<64, true, void>, false > >();
   test<boost::multiprecision::mp_number<boost::multiprecision::cpp_int_backend<64, false, void>, false > >();
#endif
#ifdef TEST_CPP_INT_BR
   test<boost::multiprecision::cpp_rational>();
#endif
   return boost::report_errors();
}

