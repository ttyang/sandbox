// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_ADAPTABLE_UNARY_FUNCTION_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_ADAPTABLE_UNARY_FUNCTION_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/detail/metafunction/has_argument_type.hpp>

namespace boost { namespace detail {

    template <typename T>
    struct is_adaptable_unary_function
      : has_argument_type<T>::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_adaptable_unary_function,(T))
    };
}}  // namespace boost::detail

#endif  // BOOST_DETAIL_METAFUNCTION_IS_ADAPTABLE_UNARY_FUNCTION_HPP_INCLUDED

