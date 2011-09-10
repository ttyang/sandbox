// Copyright (C) 2004-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_DETAIL_DEFAULT_COMPARE_PREDICATE_HPP
#define BOOST_GRAPH_DETAIL_DEFAULT_COMPARE_PREDICATE_HPP

#include <functional>
#include <boost/property_map/property_map.hpp>

namespace boost { namespace detail {

    template <typename EdgeWeightMap>
    inline ::std::less<typename property_traits<EdgeWeightMap>::value_type>
        make_default_compare_predicate(EdgeWeightMap const& map)
    {
        return ::std::less<
            typename property_traits<EdgeWeightMap>::value_type
        >();
    }
}}  // namespace boost::detail

#endif  // BOOST_GRAPH_DETAIL_DEFAULT_COMPARE_PREDICATE_HPP

