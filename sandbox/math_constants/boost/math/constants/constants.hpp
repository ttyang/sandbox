//  Copyright John Maddock 2005-2006.
//  Copyright Paul A. Bristow 2006-2010.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_CONSTANTS_CONSTANTS_INCLUDED
#define BOOST_MATH_CONSTANTS_CONSTANTS_INCLUDED

#include <boost/math/tools/config.hpp>
#include <boost/math/policies/policy.hpp>
#include <boost/math/tools/precision.hpp>
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4127 4701)
#endif
#include <boost/lexical_cast.hpp>
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/int.hpp>
#include <boost/type_traits/is_convertible.hpp>
#ifdef BOOST_HAS_THREADS
#  include <boost/thread/once.hpp>
#endif

namespace boost{ namespace math
{
  namespace constants
  {
    // To permit other calculations at about 100 decimal digits with NTL::RR type,
    // it is obviously necessary to define constants to this accuracy.

    // However, some compilers do not accept decimal digits strings as long as this.
    // So the constant is split into two parts, with the 1st containing at least
    // long double precision, and the 2nd zero if not needed or known.
    // The 3rd part permits an exponent to be provided if necessary (use zero if none) -
    // the other two parameters may only contain decimal digits (and sign and decimal point),
    // and may NOT include an exponent like 1.234E99.
    // The second digit string is only used if T is a User-Defined Type,
    // when the constant is converted to a long string literal and lexical_casted to type T.
    // (This is necessary because you can't use a numeric constant
    // since even a long double might not have enough digits).

   enum construction_method
   {
      construct_from_float = 1,
      construct_from_double = 2,
      construct_from_long_double = 3,
      construct_from_string = 4
   };

   //
   // Max number of binary digits in the string representations
   // of our constants:
   //
   BOOST_STATIC_CONSTANT(int, max_string_digits = (101 * 1000L) / 301L);

   template <class Real, class Policy>
   struct construction_traits
   {
   private:
      typedef typename policies::precision<Real, Policy>::type t1;
      typedef typename policies::precision<float, Policy>::type t2;
      typedef typename policies::precision<double, Policy>::type t3;
      typedef typename policies::precision<long double, Policy>::type t4;
   public:
      typedef typename mpl::if_<
         mpl::and_<boost::is_convertible<float, Real>, mpl::bool_< t1::value <= t2::value>, mpl::bool_<0 != t1::value> >,
         mpl::int_<construct_from_float>,
         typename mpl::if_<
            mpl::and_<boost::is_convertible<double, Real>, mpl::bool_< t1::value <= t3::value>, mpl::bool_<0 != t1::value> >,
            mpl::int_<construct_from_double>,
            typename mpl::if_<
               mpl::and_<boost::is_convertible<long double, Real>, mpl::bool_< t1::value <= t4::value>, mpl::bool_<0 != t1::value> >,
               mpl::int_<construct_from_long_double>,
               typename mpl::if_<
                  mpl::and_<mpl::bool_< t1::value <= max_string_digits>, mpl::bool_<0 != t1::value> >,
                  mpl::int_<construct_from_string>,
                  mpl::int_<t1::value>
               >::type
            >::type
         >::type
      >::type type;
   };

#ifdef BOOST_HAS_THREADS
#define BOOST_MATH_CONSTANT_THREAD_HELPER(name, prefix) \
      boost::once_flag f = BOOST_ONCE_INIT;\
      boost::call_once(f, &BOOST_JOIN(BOOST_JOIN(string_, get_), name)<T>);
#else
#define BOOST_MATH_CONSTANT_THREAD_HELPER(name, prefix)
#endif

   #define BOOST_DEFINE_MATH_CONSTANT(name, x, y, exp)\
   namespace detail{\
   /* Forward declaration of the calculation method, just in case it's not been provided yet */ \
   template <class T, int N> T BOOST_JOIN(calculate_, name)(const mpl::int_<N>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T)); \
   \
   /* The default implementations come next: */ \
   template <class T> inline T BOOST_JOIN(string_get_, name)(BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T))\
   {\
      static const T result = ::boost::lexical_cast<T>(BOOST_STRINGIZE(BOOST_JOIN(BOOST_JOIN(x, y), BOOST_JOIN(e, exp))));\
      return result;\
   }\
   template <class T> inline T BOOST_JOIN(get_, name)(const mpl::int_<construct_from_string>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T))\
   {\
      BOOST_MATH_CONSTANT_THREAD_HELPER(name, string_)\
      return BOOST_JOIN(string_get_, name)<T>();\
   }\
   template <class T> inline BOOST_CONSTEXPR T BOOST_JOIN(get_, name)(const mpl::int_<construct_from_float>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))\
   { return BOOST_JOIN(BOOST_JOIN(x, BOOST_JOIN(e, exp)), F); }\
   template <class T> inline BOOST_CONSTEXPR T BOOST_JOIN(get_, name)(const mpl::int_<construct_from_double>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))\
   { return BOOST_JOIN(x, BOOST_JOIN(e, exp)); }\
   template <class T> inline BOOST_CONSTEXPR T BOOST_JOIN(get_, name)(const mpl::int_<construct_from_long_double>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))\
   { return BOOST_JOIN(BOOST_JOIN(x, BOOST_JOIN(e, exp)), L); }\
   /* This one is for very high precision that is none the less known at compile time: */ \
   template <class T, int N> inline T BOOST_JOIN(compute_get_, name)(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(mpl::int_<N>) BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))\
   { static const T result = BOOST_JOIN(calculate_, name)<T>(mpl::int_<N>()); return result; }\
   template <class T, int N> inline T BOOST_JOIN(get_, name)(const mpl::int_<N>& n BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))\
   {\
      BOOST_MATH_CONSTANT_THREAD_HELPER(name, compute_)\
      return BOOST_JOIN(compute_get_, name)<T, N>(); \
   }\
   /* This one is for true arbitary precision, which may well vary at runtime: */ \
   template <class T> inline T BOOST_JOIN(get_, name)(const mpl::int_<0>& n BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))\
   { return tools::digits<T>() > max_string_digits ? BOOST_JOIN(calculate_, name)<T>(n) : BOOST_JOIN(get_, name)<T>(mpl::int_<construct_from_string>()); }\
   } /* namespace detail */ \
   \
   \
   /* The actual forwarding function: */ \
   template <class T, class Policy> inline BOOST_CONSTEXPR T name(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(T) BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(Policy))\
   { return detail:: BOOST_JOIN(get_, name)<T>(typename construction_traits<T, Policy>::type()); }\
   template <class T> inline BOOST_CONSTEXPR T name(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(T))\
   { return name<T, boost::math::policies::policy<> >(); }\
   \
   \
   /* Now the namespace specific versions: */ \
   } namespace float_constants{ static const float name = BOOST_JOIN(BOOST_JOIN(x, BOOST_JOIN(e, exp)), F); }\
   namespace double_constants{ static const double name = BOOST_JOIN(x, BOOST_JOIN(e, exp)); } \
   namespace long_double_constants{ static const long double name = BOOST_JOIN(BOOST_JOIN(x, BOOST_JOIN(e, exp)), L); }\
   namespace constants{

   BOOST_DEFINE_MATH_CONSTANT(pi, 3.141592653589793238462643383279502884197169399375105820974944, 59230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196, 0)
   BOOST_DEFINE_MATH_CONSTANT(two_pi, 6.2831853071795864769252867665590057683943388015061, 0, 0)
   BOOST_DEFINE_MATH_CONSTANT(one_div_two_pi, 0.70710678118654752440084436210484903928483593756084, 0, 0)
   BOOST_DEFINE_MATH_CONSTANT(root_pi, 1.7724538509055160272981674833411451827975, 0, 0)
   BOOST_DEFINE_MATH_CONSTANT(root_half_pi, 1.253314137315500251207882642405522626503, 0, 0)
   BOOST_DEFINE_MATH_CONSTANT(root_two_pi, 2.506628274631000502415765284811045253007, 0, 0)
   BOOST_DEFINE_MATH_CONSTANT(root_ln_four, 1.1774100225154746910115693264596996377473856893858205385225257565000, 2658854698492680841813836877081, 0)
   BOOST_DEFINE_MATH_CONSTANT(e, 2.7182818284590452353602874713526624977572470936999595749669676, 27724076630353547594571382178525166427427466391932003059921817413596629043572900334295260595630738132328627943490763233829880753195251019011, 0)
   BOOST_DEFINE_MATH_CONSTANT(half, 0.5, 0, 0)
   BOOST_DEFINE_MATH_CONSTANT(euler,    0.577215664901532860606512090082402431042159335939923598805, 76723488486, 0)
   BOOST_DEFINE_MATH_CONSTANT(root_two, 1.414213562373095048801688724209698078569671875376948073, 17667973799073247846210703885038753432764157273501384623091229702492483605585073721264412149709993583141322266592750559275579995050115278206, 0)
   BOOST_DEFINE_MATH_CONSTANT(half_root_two, 0.70710678118654752440084436210484903928483593756084, 0, 0)
   BOOST_DEFINE_MATH_CONSTANT(ln_two,   0.693147180559945309417232121458176568075500134360255254, 120680009493393621969694715605863326996418687, 0)
   BOOST_DEFINE_MATH_CONSTANT(ln_ln_two,  -0.36651292058166432701243915823266946945426344783710526305367771367056, 16153193527385494558228566989083583025230453648347655663425171940646634, 0)
   BOOST_DEFINE_MATH_CONSTANT(third, 0.3333333333333333333333333333333333333333333333333333333333333333333333, 3333333333333333333333333333333333333333333333333333333333333333333333333, 0)
   BOOST_DEFINE_MATH_CONSTANT(twothirds, 0.66666666666666666666666666666666666666666666666666666666666666666666, 66666666666666666666666666666666666666666666666666666666666666666666667, 0)
   BOOST_DEFINE_MATH_CONSTANT(pi_minus_three, 0.141592653589793238462643383279502884197169399375105820974944, 59230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196, 0)
   BOOST_DEFINE_MATH_CONSTANT(four_minus_pi, 0.85840734641020676153735661672049711580283060062489417902505540769218359, 0, 0)
   BOOST_DEFINE_MATH_CONSTANT(pow23_four_minus_pi, 0.79531676737159754434839533505680658072763917332771320544530223438582161, 0, 0)
   BOOST_DEFINE_MATH_CONSTANT(exp_minus_half, 0.6065306597126334236037995349911804534419181354871869556828921587350565194137, 484239986476115079894560, 0)
   BOOST_DEFINE_MATH_CONSTANT(one_div_root_two, 0.70710678118654752440084436210484903928483593756084, 0, 0)
   BOOST_DEFINE_MATH_CONSTANT(one_div_root_two_pi, 0.39894228040143267793994605993438186847585863095671, 0, 0)


  } // namespace constants
} // namespace math
} // namespace boost

//
// We deliberately include this after all the declarations above,
// that way the calculation routines can call on other constants:
//
#include <boost/math/constants/calculate_constants.hpp>

#endif // BOOST_MATH_CONSTANTS_CONSTANTS_INCLUDED
