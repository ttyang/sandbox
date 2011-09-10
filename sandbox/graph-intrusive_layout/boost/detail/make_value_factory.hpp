// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_MAKE_VALUE_FACTORY_HPP
#define BOOST_DETAIL_MAKE_VALUE_FACTORY_HPP

#include <boost/functional/value_factory.hpp>

namespace boost { namespace detail {

    template <typename T>
    inline value_factory<T> make_value_factory(T const&)
    {
        return value_factory<T>();
    }
}}  // namespace boost::detail

#endif  // BOOST_DETAIL_MAKE_VALUE_FACTORY_HPP

