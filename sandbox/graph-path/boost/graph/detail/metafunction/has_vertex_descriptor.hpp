// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_DETAIL_METAFUNCTION_HAS_VERTEX_DESCRIPTOR_HPP
#define BOOST_GRAPH_DETAIL_METAFUNCTION_HAS_VERTEX_DESCRIPTOR_HPP

#include <boost/mpl/has_xxx.hpp>

namespace boost { namespace detail {

    // The has_vertex_descriptor metafunction will determine whether or not the
    // specified type has a nested 'vertex_descriptor' type definition.
    BOOST_MPL_HAS_XXX_TRAIT_DEF(vertex_descriptor)
}}  // namespace boost::detail

#endif  // BOOST_GRAPH_DETAIL_METAFUNCTION_HAS_VERTEX_DESCRIPTOR_HPP

