// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_HAS_DIFFERENCE_TYPE_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_HAS_DIFFERENCE_TYPE_HPP_INCLUDED

#include <boost/mpl/has_xxx.hpp>

namespace boost { namespace detail { namespace metafunction {

    // The has_difference_type metafunction will determine whether or not the
    // specified type has a nested 'difference_type' type definition.
    BOOST_MPL_HAS_XXX_TRAIT_DEF(difference_type)
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_HAS_DIFFERENCE_TYPE_HPP_INCLUDED

