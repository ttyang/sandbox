//
// Boost.Process
// Regression tests for the launcher class.
//
// Copyright (c) 2006 Julio M. Merino Vidal.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt.)
//

#include <boost/filesystem/operations.hpp>
#include <boost/process/child.hpp>
#include <boost/process/context.hpp>
#include <boost/process/operations.hpp>
#include <boost/test/unit_test.hpp>

#include "launch_base_test.hpp"

namespace bfs = ::boost::filesystem;
namespace bp = ::boost::process;
namespace but = ::boost::unit_test;

// ------------------------------------------------------------------------

class launcher
{
public:
    bp::child
    operator()(const std::vector< std::string > args,
               const bp::context& ctx,
               bool usein = false)
        const
    {
        return bp::launch(get_helpers_path(), args, ctx);
    }
};

// ------------------------------------------------------------------------

but::test_suite *
init_unit_test_suite(int argc, char* argv[])
{
    bfs::initial_path();

    but::test_suite* test = BOOST_TEST_SUITE("launcher test suite");

    add_tests_launch_base< launcher, bp::context, bp::child >(test);

    return test;
}
