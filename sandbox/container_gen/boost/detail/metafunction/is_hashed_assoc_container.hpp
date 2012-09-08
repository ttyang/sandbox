// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_HASHED_ASSOC_CONTAINER_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_HASHED_ASSOC_CONTAINER_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/detail/metafunction/has_hasher.hpp>
#include <boost/detail/metafunction/is_associative_container.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct is_hashed_associative_container_impl
      : ::boost::mpl::if_<
            ::std::tr1::is_void<typename T::hasher>
          , ::boost::mpl::false_
          , is_associative_container<T>
        >
    {
    };

    template <typename T>
    struct is_hashed_associative_container
      : ::boost::mpl::eval_if<
            typename has_hasher<T>::type
          , is_hashed_associative_container_impl<T>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_hashed_associative_container,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_HASHED_ASSOC_CONTAINER_HPP_INCLUDED

