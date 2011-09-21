// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_UNARY_ARGUMENT_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_UNARY_ARGUMENT_HPP_INCLUDED

#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/detail/metafunction/adaptable_unary_argument.hpp>

namespace boost { namespace detail {

    template <typename T>
    struct unary_argument
    {
        typedef typename ::boost::mpl::eval_if<
                    ::std::tr1::is_function<T>
                  , ::boost::mpl::front<
                        ::boost::function_types::parameter_types<T>
                    >
                  , ::boost::detail::adaptable_unary_argument<T>
                >::type
                type;
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,unary_argument,(T))
    };
}}  // namespace boost::detail

#endif  // BOOST_DETAIL_METAFUNCTION_UNARY_ARGUMENT_HPP_INCLUDED

