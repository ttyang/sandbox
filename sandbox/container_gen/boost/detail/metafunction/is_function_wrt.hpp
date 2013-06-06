// Copyright (C) 2007-2011, 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_FUNCTION_WRT_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_FUNCTION_WRT_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/if.hpp>

#if !defined BOOST_NO_SFINAE && \
    !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/mpl/eval_if.hpp>
#include <boost/utility/result_of.hpp>
#endif

namespace boost { namespace detail { namespace metafunction {

#if defined BOOST_NO_SFINAE || \
    defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <typename T, typename R>
    struct is_function_with_result_type
      : ::boost::mpl::if_<
            ::std::tr1::is_same<typename T::result_type,R>
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
#else  // !defined BOOST_NO_SFINAE && \
//    !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <typename T, typename R>
    struct is_std_function_with_result_type
      : ::boost::mpl::if_<
            ::std::tr1::is_same<typename ::boost::result_of<T>::type,R>
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >
    {
    };

    template <typename T, typename R>
    struct is_functor_with_result_type
      : ::boost::mpl::if_<
            ::std::tr1::is_same<typename T::result_type,R>
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >
    {
    };

    template <typename T, typename R>
    struct is_functor_with_result_typedef
      : ::boost::mpl::eval_if<
            typename ::boost::detail::has_result_type<T>::type
          , is_functor_with_result_type<T,R>
          , ::boost::mpl::false_
        >
    {
    };

    template <typename T, typename R>
    struct is_function_with_result_type
      : ::boost::mpl::eval_if<
            ::std::tr1::is_function<T>
          , is_std_function_with_result_type<T,R>
          , is_functor_with_result_typedef<T,R>
        >::type
#endif  // BOOST_NO_SFINAE, BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_function_with_result_type,(T,R))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_FUNCTION_WRT_HPP_INCLUDED

