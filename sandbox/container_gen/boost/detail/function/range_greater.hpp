// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_FUNCTION_RANGE_GREATER_HPP_INCLUDED
#define BOOST_DETAIL_FUNCTION_RANGE_GREATER_HPP_INCLUDED

#include <boost/range/algorithm/lexicographical_compare.hpp>

namespace boost { namespace detail {

    struct range_greater
    {
        typedef bool result_type;

        template <typename R1, typename R2>
        inline result_type operator()(R1 const& r1, R2 const& r2) const
        {
            return ::boost::range::lexicographical_compare(r2, r1);
        }
    };
}}  // namespace boost::detail

#endif  // BOOST_DETAIL_FUNCTION_RANGE_GREATER_HPP_INCLUDED

