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

   namespace detail{

      template <class Real>
      Real convert_from_string(const char* p, const mpl::false_&)
      {
         return boost::lexical_cast<Real>(p);
      }
      template <class Real>
      const char* convert_from_string(const char* p, const mpl::true_&)
      {
         return p;
      }

      template <class T, T (*F)(BOOST_EXPLICIT_TEMPLATE_TYPE_SPEC(T))>
      struct constant_initializer
      {
         static void do_nothing()
         {
            init.do_nothing();
         }
      private:
         struct initializer
         {
            initializer()
            {
               F(
      #ifdef BOOST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS
                  0
      #endif
                  );
            }
            void do_nothing()const{}
         };
         static const initializer init;
      };

      template <class T, T (*F)(BOOST_EXPLICIT_TEMPLATE_TYPE_SPEC(T))>
      typename constant_initializer<T, F>::initializer const constant_initializer<T, F>::init;

      template <class T, int N, T (*F)(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(mpl::int_<N>) BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))>
      struct constant_initializer2
      {
         static void do_nothing()
         {
            init.do_nothing();
         }
      private:
         struct initializer
         {
            initializer()
            {
               F(
      #ifdef BOOST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS
                  mpl::int_<N>() , 0
      #endif
                  );
            }
            void do_nothing()const{}
         };
         static const initializer init;
      };

      template <class T, int N, T (*F)(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(mpl::int_<N>) BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))>
      typename constant_initializer2<T, N, F>::initializer const constant_initializer2<T, N, F>::init;

   }

   #define BOOST_DEFINE_MATH_CONSTANT(name, x, y, exp)\
   namespace detail{\
   /* Forward declaration of the calculation method, just in case it's not been provided yet */ \
   template <class T, int N> T BOOST_JOIN(calculate_, name)(const mpl::int_<N>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T)); \
   \
   /* The default implementations come next: */ \
   template <class T> inline T BOOST_JOIN(string_get_, name)(BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T))\
   {\
      static const T result = detail::convert_from_string<T>(BOOST_STRINGIZE(BOOST_JOIN(BOOST_JOIN(x, y), BOOST_JOIN(e, exp))), boost::is_convertible<const char*, T>());\
      return result;\
   }\
   template <class T> inline T BOOST_JOIN(get_, name)(const mpl::int_<construct_from_string>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T))\
   {\
      constant_initializer<T, & BOOST_JOIN(string_get_, name)<T> >::do_nothing();\
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
      constant_initializer2<T, N, & BOOST_JOIN(compute_get_, name)<T, N> >::do_nothing();\
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

BOOST_DEFINE_MATH_CONSTANT(pi, 3.141592653589793238462643383279502884, 1971693993751058209749445923078164062862089986280348253421170679821480865, 0);
BOOST_DEFINE_MATH_CONSTANT(two_pi, 6.283185307179586476925286766559005768, 394338798750211641949889184615632812572417997256069650684234135964296173, 0);
BOOST_DEFINE_MATH_CONSTANT(one_div_two_pi, 1.591549430918953357688837633725143620, 3445964574045644874766734405889679763422653509011380276625308595607284273, -1);
BOOST_DEFINE_MATH_CONSTANT(root_pi, 1.772453850905516027298167483341145182, 7975494561223871282138077898529112845910321813749506567385446654162268236, 0);
BOOST_DEFINE_MATH_CONSTANT(root_half_pi, 1.253314137315500251207882642405522626, 5034933703049691583149617881711468273039209874732979191890286330580049863, 0);
BOOST_DEFINE_MATH_CONSTANT(root_two_pi, 2.506628274631000502415765284811045253,0069867406099383166299235763422936546078419749465958383780572661160099727, 0);
BOOST_DEFINE_MATH_CONSTANT(root_ln_four, 1.177410022515474691011569326459699637, 7473856893858205385225257565000265885469849268084181383687708110674715786, 0);
BOOST_DEFINE_MATH_CONSTANT(e, 2.718281828459045235360287471352662497, 7572470936999595749669676277240766303535475945713821785251664274274663919, 0);
BOOST_DEFINE_MATH_CONSTANT(euler, 5.772156649015328606065120900824024310, 4215933593992359880576723488486772677766467093694706329174674951463144725, -1);
BOOST_DEFINE_MATH_CONSTANT(root_two, 1.414213562373095048801688724209698078, 5696718753769480731766797379907324784621070388503875343276415727350138462, 0);
BOOST_DEFINE_MATH_CONSTANT(half_root_two, 7.071067811865475244008443621048490392, 8483593768847403658833986899536623923105351942519376716382078636750692312, -1);
BOOST_DEFINE_MATH_CONSTANT(ln_two, 6.931471805599453094172321214581765680, 7550013436025525412068000949339362196969471560586332699641868754200148102, -1);
BOOST_DEFINE_MATH_CONSTANT(ln_ln_two, -3.665129205816643270124391582326694694, 5426344783710526305367771367056161531935273854945582285669890835830252305, -1);
BOOST_DEFINE_MATH_CONSTANT(third, 3.333333333333333333333333333333333333, 3333333333333333333333333333333333333333333333333333333333333333333333333, -1);
BOOST_DEFINE_MATH_CONSTANT(twothirds, 6.666666666666666666666666666666666666, 6666666666666666666666666666666666666666666666666666666666666666666666667, -1);
BOOST_DEFINE_MATH_CONSTANT(pi_minus_three, 1.415926535897932384626433832795028841, 9716939937510582097494459230781640628620899862803482534211706798214808651, -1);
BOOST_DEFINE_MATH_CONSTANT(four_minus_pi, 8.584073464102067615373566167204971158, 0283060062489417902505540769218359371379100137196517465788293201785191349, -1);
BOOST_DEFINE_MATH_CONSTANT(pow23_four_minus_pi, 7.953167673715975443483953350568065807, 2763917332771320544530223438885626826751818759075800688860082843683980018, -1);
BOOST_DEFINE_MATH_CONSTANT(exp_minus_half, 6.065306597126334236037995349911804534, 4191813548718695568289215873505651941374842399864761150798945602642378979, -1);
BOOST_DEFINE_MATH_CONSTANT(half, 5.000000000000000000, 0000, -1);

} // namespace constants
} // namespace math
} // namespace boost

//
// We deliberately include this after all the declarations above,
// that way the calculation routines can call on other constants:
//
#include <boost/math/constants/calculate_constants.hpp>

#endif // BOOST_MATH_CONSTANTS_CONSTANTS_INCLUDED
