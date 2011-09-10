// Copyright (C) 2004-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_DETAIL_NULL_VERTEX_HPP
#define BOOST_GRAPH_DETAIL_NULL_VERTEX_HPP

#include <boost/graph/graph_traits.hpp>

namespace boost { namespace detail {

    template <typename InputGraph>
    inline typename graph_traits<InputGraph>::vertex_descriptor
        null_vertex(InputGraph const& g)
    {
        return graph_traits<InputGraph>::null_vertex();
    }
}}  // namespace boost::detail

#endif  // BOOST_GRAPH_DETAIL_NULL_VERTEX_HPP

