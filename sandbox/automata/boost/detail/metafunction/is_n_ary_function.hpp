// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_N_ARY_FUNCTION_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_N_ARY_FUNCTION_HPP_INCLUDED

#include <boost/tr1/type_traits.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace detail {

    template <typename T, typename N>
    struct is_n_ary_function
      : ::boost::mpl::if_<
            ::std::tr1::is_function<T>
          , ::boost::mpl::equal_to<
                ::boost::function_types::function_arity<T>
              , N
            >
          , ::std::tr1::false_type
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_n_ary_function,(T, N))
    };
}}  // namespace boost::detail

#endif  // BOOST_DETAIL_METAFUNCTION_IS_N_ARY_FUNCTION_HPP_INCLUDED

