// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_HAS_REFERENCE_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_HAS_REFERENCE_HPP_INCLUDED

#include <boost/mpl/has_xxx.hpp>

namespace boost { namespace detail {

    // The has_reference metafunction will determine whether or not the
    // specified type has a nested 'reference' type definition.
    BOOST_MPL_HAS_XXX_TRAIT_DEF(reference)
}}  // namespace boost::detail

#endif  // BOOST_DETAIL_METAFUNCTION_HAS_REFERENCE_HPP_INCLUDED

