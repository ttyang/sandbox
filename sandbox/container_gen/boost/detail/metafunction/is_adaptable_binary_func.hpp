// Copyright (C) 2011, 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_ADAPTABLE_BINARY_FUNC_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_ADAPTABLE_BINARY_FUNC_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/detail/metafunction/has_first_argument_type.hpp>
#include <boost/detail/metafunction/has_second_argument_type.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct is_adaptable_binary_function
      : boost::mpl::eval_if<
            typename has_first_argument_type<T>::type
          , has_second_argument_type<T>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_adaptable_binary_function,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_ADAPTABLE_BINARY_FUNC_HPP_INCLUDED

