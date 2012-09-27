/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/is_recognized_arg.hpp>

#if !BOOST_GENERIC_DETAIL_IS_RECOGNIZED_ARG( ( try ( a + b ) ) )
#error Boost.Generic ad hoc concept "try" parameter is unrecognized.
#endif

#error Boost.Generic ad hoc concept "try" details tests unimplemented.
