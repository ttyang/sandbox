// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_KEYWORDS_WRAPAROUND_POLICY_HPP
#define BOOST_GRAPH_KEYWORDS_WRAPAROUND_POLICY_HPP

#include <boost/graph/named_function_params.hpp>
#include <boost/parameter/name.hpp>

namespace boost {
  namespace graph { namespace keywords {

    BOOST_PARAMETER_NAME(wraparound_policy);
  }}  // namespace graph::keywords

    struct wraparound_policy_t
    {
    };

  namespace detail {
	
    template <>
    struct convert_one_keyword<wraparound_policy_t>
    {
        typedef boost::graph::keywords::tag::wraparound_policy type;
    };
  }  // namespace detail
}  // namespace boost

#endif  // BOOST_GRAPH_KEYWORDS_WRAPAROUND_POLICY_HPP

