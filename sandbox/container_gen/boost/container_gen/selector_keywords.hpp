//=============================================================================
// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=============================================================================

#ifndef BOOST_CONTAINER_GEN_SELECTOR_KEYWORDS_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_SELECTOR_KEYWORDS_HPP_INCLUDED

#include <boost/parameter/aux_/template_keyword.hpp>

namespace boost {

    struct compare_selector_tag;
    struct allocator_selector_tag;

    template <typename T>
    struct compare_selector
      : ::boost::parameter::template_keyword<compare_selector_tag,T>
    {
    };

    template <typename T>
    struct allocator_selector
      : ::boost::parameter::template_keyword<allocator_selector_tag,T>
    {
    };
}  // namespace boost

#endif  // BOOST_CONTAINER_GEN_SELECTOR_KEYWORDS_HPP_INCLUDED

