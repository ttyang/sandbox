// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_INDEX_PREDICATE_HPP_INCLUDED
#define BOOST_DETAIL_INDEX_PREDICATE_HPP_INCLUDED

namespace boost { namespace detail {

    template <bool ReturnValue>
    struct index_predicate
    {
        template <typename T>
        inline bool operator[](T const&) const
        {
            return ReturnValue;
        }
    };
}}  // namespace boost::detail

#endif  // BOOST_DETAIL_INDEX_PREDICATE_HPP_INCLUDED

