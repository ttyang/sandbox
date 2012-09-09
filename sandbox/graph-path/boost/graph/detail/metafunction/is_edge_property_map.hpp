// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_DETAIL_METAFUNCTION_IS_EDGE_PROPERTY_MAP_HPP
#define BOOST_GRAPH_DETAIL_METAFUNCTION_IS_EDGE_PROPERTY_MAP_HPP

#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/detail/metafunction/is_property_map.hpp>

namespace boost { namespace detail {

    template <typename T, typename G>
    struct is_edge_property_map_impl
      : ::boost::mpl::if_<
            ::std::tr1::is_same<
                typename ::boost::property_traits<T>::key_type
              , typename graph_traits<G>::edge_descriptor
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >
    {
    };

    template <typename T, typename G>
    struct is_edge_property_map
      : ::boost::mpl::eval_if<
            ::boost::detail::metafunction::is_property_map<T>
          , is_edge_property_map_impl<T,G>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_edge_property_map,(T,G))
    };
}}  // namespace boost::detail

#endif  // BOOST_GRAPH_DETAIL_METAFUNCTION_IS_EDGE_PROPERTY_MAP_HPP

