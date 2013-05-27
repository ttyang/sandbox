// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_SORTED_ASSOC_CONTAINER_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_SORTED_ASSOC_CONTAINER_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/detail/metafunction/has_key_compare.hpp>
#include <boost/detail/metafunction/has_value_compare.hpp>
#include <boost/detail/metafunction/is_associative_container.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct is_sorted_associative_container
      : ::boost::mpl::if_<
            ::boost::mpl::and_<
                typename has_key_compare<T>::type
              , typename has_value_compare<T>::type
            >
          , is_associative_container<T>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_sorted_associative_container,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_SORTED_ASSOC_CONTAINER_HPP_INCLUDED

