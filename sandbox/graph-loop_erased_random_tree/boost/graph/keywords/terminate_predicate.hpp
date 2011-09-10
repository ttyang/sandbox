// Copyright (C) 2004-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_KEYWORDS_TERMINATE_PREDICATE_HPP
#define BOOST_GRAPH_KEYWORDS_TERMINATE_PREDICATE_HPP

#include <boost/graph/named_function_params.hpp>
#include <boost/parameter/name.hpp>

namespace boost {
  namespace graph { namespace keywords {

    BOOST_PARAMETER_NAME(terminate_predicate);
  }}  // namespace graph::keywords

    struct terminate_predicate_t
    {
    };

  namespace detail {
	
    template <>
    struct convert_one_keyword<terminate_predicate_t>
    {
        typedef boost::graph::keywords::tag::terminate_predicate type;
    };
  }  // namespace detail
}  // namespace boost

#endif  // BOOST_GRAPH_KEYWORDS_TERMINATE_PREDICATE_HPP

