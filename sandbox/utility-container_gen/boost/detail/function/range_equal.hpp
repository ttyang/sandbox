// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_FUNCTION_RANGE_EQUAL_HPP_INCLUDED
#define BOOST_DETAIL_FUNCTION_RANGE_EQUAL_HPP_INCLUDED

#include <boost/range/algorithm/equal.hpp>

namespace boost { namespace detail {

    struct range_equal
    {
        template <typename R1, typename R2>
        inline bool operator()(R1 const& r1, R2 const& r2) const
        {
            return ::boost::range::equal(r1, r2);
        }
    };
}}  // namespace boost::detail

#endif  // BOOST_DETAIL_FUNCTION_RANGE_EQUAL_HPP_INCLUDED

