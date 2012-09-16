// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_KEYWORDS_INSCRIBED_RADIUS_HPP
#define BOOST_GRAPH_KEYWORDS_INSCRIBED_RADIUS_HPP

#include <boost/graph/named_function_params.hpp>
#include <boost/parameter/name.hpp>

namespace boost { namespace graph { namespace keywords {

    BOOST_PARAMETER_NAME(inscribed_radius);
}}}  // namespace boost::graph::keywords

namespace boost {

    struct inscribed_radius_t
    {
    };
}  // namespace boost

namespace boost { namespace detail {
	
    template <>
    struct convert_one_keyword<inscribed_radius_t>
    {
        typedef boost::graph::keywords::tag::inscribed_radius type;
    };
}}  // namespace boost::detail

#endif  // BOOST_GRAPH_KEYWORDS_INSCRIBED_RADIUS_HPP

