// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_HAS_CONST_REFERENCE_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_HAS_CONST_REFERENCE_HPP_INCLUDED

#include <boost/mpl/has_xxx.hpp>

namespace boost { namespace detail {

    // The has_const_reference metafunction will determine whether or not the
    // specified type has a nested 'const_reference' type definition.
    BOOST_MPL_HAS_XXX_TRAIT_DEF(const_reference)
}}  // namespace boost::detail

#endif  // BOOST_DETAIL_METAFUNCTION_HAS_CONST_REFERENCE_HPP_INCLUDED

