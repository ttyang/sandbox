// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_DETAIL_METAFUNCTION_IS_VERTEX_LIST_GRAPH_HPP
#define BOOST_GRAPH_DETAIL_METAFUNCTION_IS_VERTEX_LIST_GRAPH_HPP

#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/detail/metafunction/has_traversal_category.hpp>

namespace boost { namespace detail {

    template <typename T>
    struct is_vertex_list_graph_impl
      : ::boost::mpl::if_<
            ::std::tr1::is_convertible<
                typename graph_traits<T>::traversal_category
              , vertex_list_graph_tag
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >
    {
    };

    template <typename T>
    struct is_vertex_list_graph
      : ::boost::mpl::eval_if<
            ::boost::detail::metafunction::has_traversal_category<
                graph_traits<T>
            >
          , is_vertex_list_graph_impl<T>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_vertex_list_graph,(T))
    };
}}  // namespace boost::detail

#endif  // BOOST_GRAPH_DETAIL_METAFUNCTION_IS_VERTEX_LIST_GRAPH_HPP

