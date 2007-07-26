//
// Boost.Process
// Checks that environment.hpp can be included without errors.
//
// Copyright (c) 2006 Julio M. Merino Vidal.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt.)
//

#include <boost/process/environment.hpp>

namespace bp = ::boost::process;

// ------------------------------------------------------------------------

void*
test_it(void)
{
    return new bp::environment();
}
