// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_FUNCTION_GET_REFERENCE_HPP_INCLUDED
#define BOOST_DETAIL_FUNCTION_GET_REFERENCE_HPP_INCLUDED

#include <boost/typeof/boost/optional.hpp>

namespace boost { namespace detail {

    // Allows a BOOST_TYPEOF or BOOST_TYPEOF_TPL expression to obtain a
    // reference to T without requiring T to be DefaultConstructible.
    template <typename T>
    T& get_reference()
    {
        return ::boost::optional<T>().get();
    }
}}  // namespace boost::detail

#endif  // BOOST_DETAIL_FUNCTION_GET_REFERENCE_HPP_INCLUDED

