// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_HAS_ALLOCATOR_TYPE_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_HAS_ALLOCATOR_TYPE_HPP_INCLUDED

#include <boost/mpl/has_xxx.hpp>

namespace boost { namespace detail { namespace metafunction {

    // The has_allocator_type metafunction will determine whether or not
    // the specified type has a nested 'allocator_type' type definition.
    BOOST_MPL_HAS_XXX_TRAIT_DEF(allocator_type)

    BOOST_MPL_HAS_XXX_TRAIT_DEF(propagate_on_container_copy_assignment)
    BOOST_MPL_HAS_XXX_TRAIT_DEF(propagate_on_container_move_assignment)
    BOOST_MPL_HAS_XXX_TRAIT_DEF(propagate_on_container_swap)
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_HAS_ALLOCATOR_TYPE_HPP_INCLUDED

