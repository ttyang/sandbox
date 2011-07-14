//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////
/**
 * @file
 * @brief Defines the type trait @c is_constructible.
 */


#ifndef BOOST_CONVERSION_TT_IS_CONSTRUCTIBLE_HPP
#define BOOST_CONVERSION_TT_IS_CONSTRUCTIBLE_HPP

#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
namespace boost {

  /**
   * States if @c T is constructible from @c Args.
   *
   * Condition: @c true_type if and only if the following variable definition would be well-formed for
   * some invented variable t:
   *
   *   T t(decval<Args>()...);
   *
   * @Requires @c T and all types in the parameter pack @c Args must be complete types, (possibly cv-qualified) void, or arrays of unknown bound.
   */
  template < class T, class... Args>
  struct is_constructible
  {};

  //! Macro stating if the compiler doesn't support the features needed to define the @c is_constructible type trait.
  #define BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE
  //! Macro stating if the compiler doesn't support the features needed to define the @c is_default_constructible type trait.
  #define BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE
  //! Max number of arguments to is_constructible when using variadic templates emulation.
  #define BOOST_CONVERSION_TT_IS_CONSTRUCTIBLE_ARITY_MAX

}
#else

#if 1

#include <boost/config.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/utility/declval.hpp>
#include <cstddef>

#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/common_type.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_abstract.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/remove_all_extents.hpp>


#ifndef BOOST_CONVERSION_TT_IS_CONSTRUCTIBLE_ARITY_MAX
#define BOOST_CONVERSION_TT_IS_CONSTRUCTIBLE_ARITY_MAX 3
#endif

namespace boost
{

#if ! defined BOOST_NO_DECLTYPE
  #define BOOST_CONVERSION_IS_CONSTRUCTIBLE_USES_DECLTYPE
#elif ! defined BOOST_NO_SFINAE_EXPR
  #define BOOST_CONVERSION_IS_CONSTRUCTIBLE_USES_SIZEOF
  #if defined __clang__
  #elif defined __GNUC__
     #if __GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 7 )
       #define BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE
     #endif
  #endif
#else
  #define BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE
  #define BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE
#endif

#if defined BOOST_CONVERSION_IS_CONSTRUCTIBLE_USES_DECLTYPE

  namespace detail {

    namespace is_constructible {
      struct any {
        template <typename T>
        any(T);
      };
      template <class T>
      decltype((T(), true_type()))
      test0(T&);
      false_type
      test0(any);

      template <class T, class A1>
      decltype((T(declval<A1>()), true_type()))
      test1(T&, A1);
      template <class A1>
      false_type
      test1(any, A1);

      template <class T, class A1, class A2>
      decltype((T(declval<A1>(),declval<A2>()), true_type()))
      test2(T&, A1, A2);
      template <class A1, class A2>
      false_type
      test2(any, A1, A2);
      template <bool, class T>
      struct imp0 // false, T is not a scalar
          : public common_type
                   <
          decltype(test0(declval<T&>()))
                   >::type
      {};
      template <bool, class T, class A1>
      struct imp1 // false, T is not a scalar
          : public common_type
                   <
          decltype(test1(declval<T&>(), declval<A1>()))
                   >::type
      {};
      template <bool, class T, class A1, class A2>
      struct imp2 // false, T is not a scalar
          : public common_type
                   <
          decltype(test2(declval<T&>(), declval<A1>(), declval<A2>()))
                   >::type
      {};
      template <class T>
      struct imp0<true, T>
          : public is_scalar<T>
          {};

      template <class T, class A1>
      struct imp1<true, T, A1>
          : public is_convertible<A1, T>
          {};

      template <class T, class A1, class A2>
      struct imp2<true, T, A1, A2>
          : public false_type
          {};
      template <bool, class T>
      struct void_check0
          : public imp0<is_scalar<T>::value || is_reference<T>::value,
                                      T>
          {};

      template <bool, class T, class A1>
      struct void_check1
          : public imp1<is_scalar<T>::value || is_reference<T>::value,
                                      T, A1>
          {};

      template <bool, class T, class A1, class A2>
      struct void_check2
          : public imp2<is_scalar<T>::value || is_reference<T>::value,
                                      T, A1, A2>
          {};

      template <class T>
      struct void_check0<true, T>
          : public false_type
          {};

      template <class T, class A1>
      struct void_check1<true, T, A1>
          : public false_type
          {};

      template <class T, class A1, class A2>
      struct void_check2<true, T, A1, A2>
          : public false_type
          {};

      struct nat {};

      template <class A>
      struct imp0<false, A[]>
          : public false_type
          {};

      template <class A, class A1>
      struct imp1<false, A[], A1>
          : public false_type
          {};

      template <class A, class A1, class A2>
      struct imp2<false, A[], A1, A2>
          : public false_type
          {};

    }
  }

  template <class T, class A1 = detail::is_constructible::nat,
                     class A2 = detail::is_constructible::nat>
  struct is_constructible
      : public detail::is_constructible::void_check2<is_void<T>::value
                                            || is_abstract<T>::value
                                            || is_function<T>::value
                                            || is_void<A1>::value
                                            || is_void<A2>::value,
                                               T, A1, A2>
      {};

  template <class T>
  struct is_constructible<T, detail::is_constructible::nat, detail::is_constructible::nat>
      : public detail::is_constructible::void_check0<is_void<T>::value
                                            || is_abstract<T>::value
                                            || is_function<T>::value,
                                               T>
      {};

  template <class T, class A1>
  struct is_constructible<T, A1, detail::is_constructible::nat>
      : public detail::is_constructible::void_check1<is_void<T>::value
                                            || is_abstract<T>::value
                                            || is_function<T>::value
                                            || is_void<A1>::value,
                                               T, A1>
      {};

  namespace detail {
    namespace is_constructible {
      template <class A, std::size_t N>
      struct imp0<false, A[N]>
          : public boost::is_constructible<typename remove_all_extents<A>::type>
          {};

      template <class A, std::size_t N, class A1>
      struct imp1<false, A[N], A1>
          : public false_type
          {};

      template <class A, std::size_t N, class A1, class A2>
      struct imp2<false, A[N], A1, A2>
          : public false_type
          {};
    }
  }


#elif defined BOOST_CONVERSION_IS_CONSTRUCTIBLE_USES_SIZEOF

  template<class T, class A=void, BOOST_PP_ENUM_BINARY_PARAMS(BOOST_CONVERSION_TT_IS_CONSTRUCTIBLE_ARITY_MAX, class A, = void BOOST_PP_INTERCEPT)>
  struct is_constructible;
    namespace type_traits_detail
    {

        typedef char true_type;
        struct false_type { char a[2]; };

        template<std::size_t N>
        struct dummy;
    }

#define M1(z,n,t) declval<A##n>()

    #define M0(z,n,t)                                                                                   \
    template<class T, class A BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class A)>                             \
    struct is_constructible<T,A BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, A)>                          \
    {                                                                                                   \
        template<class X>                                                                               \
        static type_traits_detail::true_type                                                            \
        test(type_traits_detail::dummy<sizeof(X(declval<A>() BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM(n, M1, ~)))>*);   \
                                                                                                           \
        template<class X>                                                                               \
        static type_traits_detail::false_type                                                           \
        test(...);                                                                                      \
                                                                                                        \
        static const bool value = sizeof(test<T>(0)) == sizeof(type_traits_detail::true_type);          \
        typedef boost::integral_constant<bool,value> type;                                              \
    };

    BOOST_PP_REPEAT(BOOST_CONVERSION_TT_IS_CONSTRUCTIBLE_ARITY_MAX, M0, ~)
    #undef M0
    #undef M1

    #if ! defined BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE
    #define M1(z,n,t) void

    template<class T>                             \
    struct is_constructible<T,void, BOOST_PP_ENUM(BOOST_CONVERSION_TT_IS_CONSTRUCTIBLE_ARITY_MAX, M1, ~)>
    {
        template<class X>
        static type_traits_detail::true_type
        test(type_traits_detail::dummy<sizeof(X(),int())>*);

        template<class X>
        static type_traits_detail::false_type
        test(...);

        static const bool value = sizeof(test<T>(0)) == sizeof(type_traits_detail::true_type);
        typedef boost::integral_constant<bool,value> type;
    };

    template<>                             \
    struct is_constructible<void,void, BOOST_PP_ENUM(BOOST_CONVERSION_TT_IS_CONSTRUCTIBLE_ARITY_MAX, M1, ~)>
    : boost::false_type                                                                               \
    {                                                                                                   \
    };

    #undef M1

    #endif


    #define M0(z,n,t)                                                                                   \
    template<class A BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class A)>                             \
    struct is_constructible<void, A BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, A)>                          \
      : boost::false_type                                                                               \
    {                                                                                                   \
    };

    BOOST_PP_REPEAT(BOOST_CONVERSION_TT_IS_CONSTRUCTIBLE_ARITY_MAX, M0, ~)
    #undef M0


#else

    template<class T, class A=void, BOOST_PP_ENUM_BINARY_PARAMS(BOOST_CONVERSION_TT_IS_CONSTRUCTIBLE_ARITY_MAX, class A, = void BOOST_PP_INTERCEPT)>
    struct is_constructible;

    #define M0(z,n,t)                                                                                   \
    template<class T, class A BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class A)>                             \
    struct is_constructible<T, A BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, A)>                          \
      : boost::false_type                                                                               \
    {                                                                                                   \
    };

    BOOST_PP_REPEAT(BOOST_CONVERSION_TT_IS_CONSTRUCTIBLE_ARITY_MAX, M0, ~)
    #undef M0

#endif

#ifdef  BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE
    // default constructor
    template <> struct is_constructible< int  >  : true_type {};
#endif
#ifdef  BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE
    template <class T> struct is_constructible< T*, T* const &  >  : true_type {};
    template <> struct is_constructible< int, const int  >  : true_type {};
    template <> struct is_constructible< int, int const& >  : true_type {};
    template <> struct is_constructible< double, const double  >  : true_type {};
    template <> struct is_constructible< double, double const& >  : true_type {};
#endif


}




#endif
#endif
#endif

