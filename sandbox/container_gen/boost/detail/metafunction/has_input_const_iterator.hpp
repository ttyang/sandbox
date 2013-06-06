// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_HAS_INPUT_CONST_ITERATOR_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_HAS_INPUT_CONST_ITERATOR_HPP_INCLUDED

#include <boost/detail/metafunction/is_input_iterator.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct has_input_const_iterator
      : is_input_iterator<typename T::const_iterator>::type
    {
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_HAS_INPUT_CONST_ITERATOR_HPP_INCLUDED

