//
// Boost.Process
// Regression tests for the status class.
//
// Copyright (c) 2006 Julio M. Merino Vidal.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0.  (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt.)
//

#include <cstring> // XXX For EXIT_* codes; should be hidden by the library.
#include <string>

#include <boost/process/child.hpp>
#include <boost/process/launcher.hpp>
#include <boost/process/status.hpp>
#include <boost/test/unit_test.hpp>

// XXX Extremely ugly way to determine helpers' path...
#if defined(__APPLE__)
#   define HELPERS_PATH "./bin/darwin/debug/helpers"
#else
#   define HELPERS_PATH "./bin/gcc/debug/helpers"
#endif

namespace bp = ::boost::process;
namespace but = ::boost::unit_test;

// ------------------------------------------------------------------------

bp::child
launch_helper(const std::string& name)
{
    bp::command_line cl(HELPERS_PATH);
    cl.argument(name);
    bp::attributes a(cl);
    return bp::launcher().start<bp::attributes>(a);
}

// ------------------------------------------------------------------------

void
test_exit_failure(void)
{
    bp::status s = launch_helper("exit-failure").wait();
    BOOST_REQUIRE(s.exited());
    BOOST_CHECK_EQUAL(s.exit_status(), EXIT_FAILURE);
}

// ------------------------------------------------------------------------

void
test_exit_success(void)
{
    bp::status s = launch_helper("exit-success").wait();
    BOOST_REQUIRE(s.exited());
    BOOST_CHECK_EQUAL(s.exit_status(), EXIT_SUCCESS);
}

// ------------------------------------------------------------------------

but::test_suite *
init_unit_test_suite(int argc, char* argv[])
{
    but::test_suite* test = BOOST_TEST_SUITE("status test suite");

    test->add(BOOST_TEST_CASE(&test_exit_success), 0, 10);
    test->add(BOOST_TEST_CASE(&test_exit_failure), 0, 10);

    return test;
}
