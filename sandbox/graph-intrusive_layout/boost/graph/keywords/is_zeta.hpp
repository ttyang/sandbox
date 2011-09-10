// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_KEYWORDS_IS_ZETA_HPP
#define BOOST_GRAPH_KEYWORDS_IS_ZETA_HPP

#include <boost/graph/named_function_params.hpp>
#include <boost/parameter/name.hpp>

namespace boost {
  namespace graph { namespace keywords {

    BOOST_PARAMETER_NAME(is_zeta);
  }}  // namespace graph::keywords

    struct is_zeta_t
    {
    };

  namespace detail {

    template <>
    struct convert_one_keyword<is_zeta_t>
    {
        typedef boost::graph::keywords::tag::is_zeta type;
    };
  }  // namespace detail
}  // namespace boost

#endif  // BOOST_GRAPH_KEYWORDS_IS_ZETA_HPP

