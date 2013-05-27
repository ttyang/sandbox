// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UTILITY_GET_REFERENCE_HPP_INCLUDED
#define BOOST_UTILITY_GET_REFERENCE_HPP_INCLUDED

#include <boost/typeof/boost/optional.hpp>

//[reference__get_reference
namespace boost {

    template <typename T>
    T& get_reference()
    {
        return ::boost::optional<T>().get();
    }
}  // namespace boost
//]

#endif  // BOOST_UTILITY_GET_REFERENCE_HPP_INCLUDED

