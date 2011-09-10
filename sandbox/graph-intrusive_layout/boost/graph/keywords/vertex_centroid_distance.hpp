// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_KEYWORDS_VERTEX_CENTROID_DISTANCE_HPP
#define BOOST_GRAPH_KEYWORDS_VERTEX_CENTROID_DISTANCE_HPP

#include <boost/graph/named_function_params.hpp>
#include <boost/parameter/name.hpp>

namespace boost {
  namespace graph { namespace keywords {

    BOOST_PARAMETER_NAME(vertex_centroid_distance);
  }}  // namespace graph::keywords

    struct vertex_centroid_distance_t
    {
    };

  namespace detail {
	
    template <>
    struct convert_one_keyword<vertex_centroid_distance_t>
    {
        typedef boost::graph::keywords::tag::vertex_centroid_distance type;
    };
  }  // namespace detail
}  // namespace boost

#endif  // BOOST_GRAPH_KEYWORDS_VERTEX_CENTROID_DISTANCE_HPP

