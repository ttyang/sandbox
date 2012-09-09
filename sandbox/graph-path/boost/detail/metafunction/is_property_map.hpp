// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_PROPERTY_MAP_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_PROPERTY_MAP_HPP_INCLUDED

#include <boost/mpl/and.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/detail/metafunction/has_key_type.hpp>
#include <boost/detail/metafunction/has_value_type.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct is_property_map
      : ::boost::mpl::and_<
            ::boost::detail::metafunction::has_key_type<
                ::boost::property_traits<T>
            >
          , ::boost::detail::metafunction::has_value_type<
                ::boost::property_traits<T>
            >
        >
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_property_map,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_PROPERTY_MAP_HPP_INCLUDED

