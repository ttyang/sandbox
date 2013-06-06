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

    struct constant_size_tag;
    struct is_tr1_not_boost_tag;
    struct is_boost_not_std_tag;
    struct hasher_selector_tag;
    struct compare_selector_tag;
    struct allocator_selector_tag;
    struct ptr_clone_allocator_tag;
    struct ptr_allocator_tag;
    struct sequence_selector_tag;

    template <typename T>
    struct constant_size_arg
      : ::boost::parameter::template_keyword<constant_size_tag,T>
    {
    };

    template <typename T>
    struct is_tr1_not_boost_arg
      : ::boost::parameter::template_keyword<is_tr1_not_boost_tag,T>
    {
    };

    template <typename T>
    struct is_boost_not_std_arg
      : ::boost::parameter::template_keyword<is_boost_not_std_tag,T>
    {
    };

    template <typename T>
    struct hasher_selector_arg
      : ::boost::parameter::template_keyword<hasher_selector_tag,T>
    {
    };

    template <typename T>
    struct compare_selector_arg
      : ::boost::parameter::template_keyword<compare_selector_tag,T>
    {
    };

    template <typename T>
    struct allocator_selector_arg
      : ::boost::parameter::template_keyword<allocator_selector_tag,T>
    {
    };

    template <typename T>
    struct ptr_clone_allocator_arg
      : ::boost::parameter::template_keyword<ptr_clone_allocator_tag,T>
    {
    };

    template <typename T>
    struct ptr_allocator_arg
      : ::boost::parameter::template_keyword<ptr_allocator_tag,T>
    {
    };

    template <typename T>
    struct sequence_selector_arg
      : ::boost::parameter::template_keyword<sequence_selector_tag,T>
    {
    };
}  // namespace boost

#endif  // BOOST_CONTAINER_GEN_SELECTOR_KEYWORDS_HPP_INCLUDED

