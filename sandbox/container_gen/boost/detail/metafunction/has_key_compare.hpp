// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_HAS_KEY_COMPARE_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_HAS_KEY_COMPARE_HPP_INCLUDED

#include <boost/mpl/has_xxx.hpp>

namespace boost { namespace detail { namespace metafunction {

    // The has_key_compare metafunction will determine whether or not the
    // specified type has a nested 'key_compare' type definition.
    BOOST_MPL_HAS_XXX_TRAIT_DEF(key_compare)
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_HAS_KEY_COMPARE_HPP_INCLUDED

