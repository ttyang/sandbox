// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_HAS_KEY_TYPE_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_HAS_KEY_TYPE_HPP_INCLUDED

#include <boost/mpl/has_xxx.hpp>

namespace boost { namespace detail {

    // The has_key_type metafunction will determine whether or not the specified
    // type has a nested 'key_type' type definition.
    BOOST_MPL_HAS_XXX_TRAIT_DEF(key_type)
}}  // namespace boost::detail

#endif  // BOOST_DETAIL_METAFUNCTION_HAS_KEY_TYPE_HPP_INCLUDED

