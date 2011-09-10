// Copyright (C) 2004-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_DETAIL_DEFAULT_TERMINATE_PREDICATE_HPP
#define BOOST_GRAPH_DETAIL_DEFAULT_TERMINATE_PREDICATE_HPP

#include <boost/graph/graph_traits.hpp>

namespace boost { namespace detail {

    template <typename InputGraph>
    struct default_terminate_predicate
    {
        typedef typename graph_traits<InputGraph>::vertex_descriptor
                first_argument_type;
        typedef InputGraph const&
                second_argument_type;
        typedef bool
                result_type;

        inline result_type
            operator()(first_argument_type v, second_argument_type g) const
        {
            return false;
        }
    };

    template <typename InputGraph>
    inline default_terminate_predicate<InputGraph>
        make_default_terminate_predicate(InputGraph const& g)
    {
        return default_terminate_predicate<InputGraph>();
    }
}}  // namespace boost::detail

#endif  // BOOST_GRAPH_DETAIL_DEFAULT_TERMINATE_PREDICATE_HPP

