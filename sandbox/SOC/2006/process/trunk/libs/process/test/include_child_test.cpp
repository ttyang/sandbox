//
// Boost.Process
// Checks that child.hpp can be included without errors.
//
// Copyright (c) 2006 Julio M. Merino Vidal.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt.)
//

#include <boost/process/child.hpp>

namespace bp = ::boost::process;
namespace bpd = ::boost::process::detail;

// ------------------------------------------------------------------------

void*
test_it(void)
{
    bp::child::id_type id = (bp::child::id_type)0;
    bpd::file_handle fh;
    return new bp::child(id, fh, fh, fh);
}