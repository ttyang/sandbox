// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_FLAT_ASSOC_CONTAINER_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_FLAT_ASSOC_CONTAINER_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/detail/metafunction/is_random_access_iterator.hpp>
#include <boost/detail/metafunction/is_sorted_assoc_container.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct is_flat_associative_container_impl
      : is_random_access_iterator<typename T::iterator>
    {
    };

    template <typename T>
    struct is_flat_associative_container
      : ::boost::mpl::if_<
            is_sorted_associative_container<T>
          , is_flat_associative_container_impl<T>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_flat_associative_container,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_FLAT_ASSOC_CONTAINER_HPP_INCLUDED

