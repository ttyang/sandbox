// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_RANDOM_ACCESS_CONTAINER_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_RANDOM_ACCESS_CONTAINER_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/detail/metafunction/is_random_access_iterator.hpp>
#include <boost/detail/metafunction/is_container.hpp>
#include <boost/detail/metafunction/is_associative_container.hpp>

namespace boost { namespace detail { namespace metafunction {

    // Major assumption:
    // All Random Access Containers sport Random Access Iterators and
    // are not Associative Containers.
    template <typename T>
    struct is_random_access_container_impl
      : ::boost::mpl::and_<
            is_random_access_iterator<typename T::iterator>
          , ::boost::mpl::not_< is_associative_container<T> >
        >
    {
    };

    template <typename T>
    struct is_random_access_container
      : ::boost::mpl::if_<
            typename is_container<T>::type
          , is_random_access_container_impl<T>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_random_access_container,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_RANDOM_ACCESS_CONTAINER_HPP_INCLUDED

