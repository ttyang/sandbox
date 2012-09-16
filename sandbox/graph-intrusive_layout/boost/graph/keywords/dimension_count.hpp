// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_KEYWORDS_DIMENSION_COUNT_HPP
#define BOOST_GRAPH_KEYWORDS_DIMENSION_COUNT_HPP

#include <boost/graph/named_function_params.hpp>
#include <boost/parameter/name.hpp>

namespace boost { namespace graph { namespace keywords {

    BOOST_PARAMETER_NAME(dimension_count);
}}}  // namespace graph::keywords

namespace boost {

    struct dimension_count_t
    {
    };
}  // namespace boost

namespace boost { namespace detail {
	
    template <>
    struct convert_one_keyword<dimension_count_t>
    {
        typedef boost::graph::keywords::tag::dimension_count type;
    };
}}  // namespace boost::detail

#endif  // BOOST_GRAPH_KEYWORDS_DIMENSION_COUNT_HPP

