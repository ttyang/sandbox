// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_ADAPTABLE_BINARY_FUNCTION_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_ADAPTABLE_BINARY_FUNCTION_HPP_INCLUDED

#include <boost/mpl/and.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/detail/metafunction/has_first_argument_type.hpp>
#include <boost/detail/metafunction/has_second_argument_type.hpp>

namespace boost { namespace detail {

    template <typename T>
    struct is_adaptable_binary_function
      : boost::mpl::and_<
            typename has_first_argument_type<T>::type
          , typename has_second_argument_type<T>::type
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_adaptable_binary_function,(T))
    };
}}  // namespace boost::detail

#endif  // BOOST_DETAIL_METAFUNCTION_IS_ADAPTABLE_BINARY_FUNCTION_HPP_INCLUDED

