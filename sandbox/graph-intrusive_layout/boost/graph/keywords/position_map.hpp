// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_KEYWORDS_POSITION_MAP_HPP
#define BOOST_GRAPH_KEYWORDS_POSITION_MAP_HPP

#include <boost/graph/named_function_params.hpp>
#include <boost/parameter/name.hpp>

namespace boost { namespace graph { namespace keywords {

    BOOST_PARAMETER_NAME(position_map);
}}}  // namespace boost::graph::keywords

namespace boost {

    struct position_map_t
    {
    };
}  // namespace boost

namespace boost { namespace detail {

    template <>
    struct convert_one_keyword<position_map_t>
    {
        typedef boost::graph::keywords::tag::position_map type;
    };
}}  // namespace boost::detail

#endif  // BOOST_GRAPH_KEYWORDS_POSITION_MAP_HPP

