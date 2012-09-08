// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_PTR_CONTAINER_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_PTR_CONTAINER_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/detail/metafunction/has_auto_type.hpp>
#include <boost/detail/metafunction/is_container.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct is_ptr_container
      : ::boost::mpl::if_<
            typename has_auto_type<T>::type
          , is_container<T>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_ptr_container,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_PTR_CONTAINER_HPP_INCLUDED

