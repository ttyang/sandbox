/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/assert_at_global_scope.hpp>

namespace foo {

BOOST_GENERIC_DETAIL_ASSERT_AT_GLOBAL_SCOPE
( "Global scope assert working correctly." )

}
