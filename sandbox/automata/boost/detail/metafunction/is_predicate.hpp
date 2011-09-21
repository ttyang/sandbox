// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_PREDICATE_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_PREDICATE_HPP_INCLUDED

#include <boost/tr1/type_traits.hpp>
#include <boost/tr1/functional.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace detail {

#ifdef BOOST_NO_RESULT_OF
    template <typename T>
    struct is_predicate
      : ::std::tr1::is_same<typename T::result_type,bool>
#else
    template <typename T>
    struct is_predicate_function
      : ::std::tr1::is_same<typename ::std::tr1::result_of<T>::type,bool>
    {
    };

    template <typename T>
    struct is_predicate_class
      : ::std::tr1::is_same<typename T::result_type,bool>
    {
    };

    template <typename T>
    struct is_predicate
      : ::boost::mpl::if_<
            ::std::tr1::is_function<T>
          , is_predicate_function<T>
          , is_predicate_class<T>
        >::type
#endif  // BOOST_NO_RESULT_OF
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_predicate,(T))
    };
}}  // namespace boost::detail

#endif  // BOOST_DETAIL_METAFUNCTION_IS_PREDICATE_HPP_INCLUDED

