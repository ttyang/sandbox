//  Copyright John Maddock 2010.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_CALCULATE_CONSTANTS_CONSTANTS_INCLUDED
#define BOOST_MATH_CALCULATE_CONSTANTS_CONSTANTS_INCLUDED

namespace boost{ namespace math{ namespace constants{ namespace detail{

template <class T, int N> 
inline T calculate_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING

   return ldexp(acos(T(0)), 1);

   /*
   // Although this code works well, it's usually more accurate to just call acos
   // and access the numner types own representation of PI which is usually calculated
   // at slightly higher precision...

   T result;
   T a = 1;
   T b;
   T A(a);
   T B = 0.5f;
   T D = 0.25f;

   T lim;
   lim = boost::math::tools::epsilon<T>();

   unsigned k = 1;

   do
   {
      result = A + B;
      result = ldexp(result, -2);
      b = sqrt(B);
      a += b;
      a = ldexp(a, -1);
      A = a * a;
      B = A - result;
      B = ldexp(B, 1);
      result = A - B;
      bool neg = boost::math::sign(result) < 0;
      if(neg)
         result = -result;
      if(result <= lim)
         break;
      if(neg)
         result = -result;
      result = ldexp(result, k - 1);
      D -= result;
      ++k;
      lim = ldexp(lim, 1);
   }
   while(true);

   result = B / D;
   return result;
   */
}

template <class T, int N> 
inline T calculate_two_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   return 2 * pi<T, policies::policy<policies::digits2<N> > >();
}

template <class T, int N> 
inline T calculate_one_div_two_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   return 1 / two_pi<T, policies::policy<policies::digits2<N> > >();
}

template <class T, int N> 
inline T calculate_root_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return sqrt(pi<T, policies::policy<policies::digits2<N> > >());
}

template <class T, int N> 
inline T calculate_root_half_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return sqrt(pi<T, policies::policy<policies::digits2<N> > >() / 2);
}

template <class T, int N> 
inline T calculate_root_two_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return sqrt(two_pi<T, policies::policy<policies::digits2<N> > >());
}

template <class T, int N> 
inline T calculate_root_ln_four(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return sqrt(log(static_cast<T>(4)));
}

template <class T, int N> 
inline T calculate_e(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   //
   // Although we can clearly calculate this from first principles, this hooks into
   // T's own notion of e, which hopefully will more accurate than one calculated to
   // a few epsilon:
   //
   BOOST_MATH_STD_USING
   return exp(static_cast<T>(1));
}

template <class T, int N> 
inline T calculate_half(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   return static_cast<T>(1) / static_cast<T>(2);
}

template <class T, int N> 
inline T calculate_euler(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   //
   // This is the method described in:
   // "Some New Algorithms for High-Precision Computation of Euler's Constant"
   // Richard P Brent and Edwin M McMillan.
   // Mathematics of Comnputation, Volume 34, Number 149, Jan 1980, pages 305-312.
   // See equation 17 with p = 2.
   //
   T n = 3 + boost::math::tools::digits<T>() / 4;
   T lnn = log(n);
   T term = 1;
   T N = -lnn;
   T D = 1;
   T Hk = 0;
   T one = 1;

   for(unsigned k = 1;; ++k)
   {
      term *= n * n;
      term /= k * k;
      Hk += one / k;
      N += term * (Hk - lnn);
      D += term;

      if(term < D * boost::math::tools::epsilon<T>())
         break;
   }
   return N / D;
}

template <class T, int N> 
inline T calculate_root_two(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return sqrt(static_cast<T>(2));
}

template <class T, int N> 
inline T calculate_half_root_two(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return sqrt(static_cast<T>(2)) / 2;
}

template <class T, int N> 
inline T calculate_ln_two(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   //
   // Although there are good ways to calculate this from scratch, this hooks into
   // T's own notion of log(2) which will hopefully be accurate to the full precision
   // of T:
   //
   BOOST_MATH_STD_USING
   return log(static_cast<T>(2));
}

template <class T, int N> 
inline T calculate_ln_ln_two(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return log(log(static_cast<T>(2)));
}

template <class T, int N> 
inline T calculate_third(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return static_cast<T>(1) / static_cast<T>(3);
}

template <class T, int N> 
inline T calculate_twothirds(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return static_cast<T>(2) / static_cast<T>(3);
}

template <class T, int N> 
inline T calculate_pi_minus_three(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   return pi<T, policies::policy<policies::digits2<N> > >() - static_cast<T>(3);
}

template <class T, int N> 
inline T calculate_four_minus_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   return static_cast<T>(4) - pi<T, policies::policy<policies::digits2<N> > >();
}

template <class T, int N> 
inline T calculate_pow23_four_minus_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return pow(four_minus_pi<T, policies::policy<policies::digits2<N> > >(), static_cast<T>(1.5));
}

template <class T, int N> 
inline T calculate_exp_minus_half(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return exp(static_cast<T>(-0.5));
}

template <class T, int N> 
inline T calculate_one_div_root_two(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   return static_cast<T>(1) / root_two<T, policies::policy<policies::digits2<N> > >();
}

template <class T, int N> 
inline T calculate_one_div_root_two_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   return static_cast<T>(1) / root_two_pi<T, policies::policy<policies::digits2<N> > >();
}

}}}} // namespaces

#endif // BOOST_MATH_CALCULATE_CONSTANTS_CONSTANTS_INCLUDED
