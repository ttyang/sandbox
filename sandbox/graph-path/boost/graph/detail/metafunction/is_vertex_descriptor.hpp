// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_DETAIL_METAFUNCTION_IS_VERTEX_DESCRIPTOR_HPP
#define BOOST_GRAPH_DETAIL_METAFUNCTION_IS_VERTEX_DESCRIPTOR_HPP

#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/detail/metafunction/has_vertex_descriptor.hpp>

namespace boost { namespace detail {

    template <typename V, typename G>
    struct is_vertex_descriptor_impl
      : ::boost::mpl::if_<
            ::std::tr1::is_convertible<
                V
              , typename graph_traits<G>::vertex_descriptor
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >
    {
    };

    template <typename V, typename G>
    struct is_vertex_descriptor
      : ::boost::mpl::eval_if<
            has_vertex_descriptor<graph_traits<G> >
          , is_vertex_descriptor_impl<V,G>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_vertex_descriptor,(V,G))
    };
}}  // namespace boost::detail

#endif  // BOOST_GRAPH_DETAIL_METAFUNCTION_IS_VERTEX_DESCRIPTOR_HPP

