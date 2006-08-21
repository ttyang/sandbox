//
// Boost.Process
// Regression tests for the win32_child class.
//
// Copyright (c) 2006 Julio M. Merino Vidal.
//
// This code may be used under either of the following two licences:
//
//      Permission is hereby granted, free of charge, to any person
//      obtaining a copy of this software and associated documentation
//      files (the "Software"), to deal in the Software without
//      restriction, including without limitation the rights to use,
//      copy, modify, merge, publish, distribute, sublicense, and/or
//      sell copies of the Software, and to permit persons to whom the
//      Software is furnished to do so, subject to the following
//      conditions:
//
//      The above copyright notice and this permission notice shall be
//      included in all copies or substantial portions of the Software.
//
//      THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//      EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//      OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//      NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//      HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//      WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//      FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//      OTHER DEALINGS IN THE SOFTWARE. OF SUCH DAMAGE.
//
// Or:
//
//      Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt or copy at
//      http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/process/config.hpp>

#if defined(BOOST_PROCESS_WIN32_API)
extern "C" {
#   include <windows.h>
}

#   include <boost/process/detail/factories.hpp>
#   include <boost/process/win32_child.hpp>

#   include "child_base_test.hpp"

namespace bp = ::boost::process;
namespace bpd = ::boost::process::detail;
#endif

#include <boost/test/unit_test.hpp>

namespace but = ::boost::unit_test;

// ------------------------------------------------------------------------

#if defined(BOOST_PROCESS_WIN32_API)
struct factory
{
    bp::win32_child
    operator()(bp::win32_child::handle_type h, bpd::file_handle fhstdin,
               bpd::file_handle fhstdout, bpd::file_handle fhstderr)
    {
        PROCESS_INFORMATION pi;
        pi.hProcess = h;
        return bpd::factories::create_win32_child(pi, fhstdin, fhstdout,
                                                  fhstderr);
    }
};
#endif

// ------------------------------------------------------------------------

#if defined(BOOST_PROCESS_WIN32_API)
static
void
test_getters(void)
{
    PROCESS_INFORMATION pi;
    pi.hProcess = (HANDLE)0x1234;
    pi.dwProcessId = 1111;
    pi.hThread = (HANDLE)0x5678;
    pi.dwThreadId = 2222;

    bpd::file_handle fh;

    bp::win32_child c = bpd::factories::create_win32_child(pi, fh, fh, fh);

    BOOST_CHECK_EQUAL(c.get_handle(), pi.hProcess);
    BOOST_CHECK_EQUAL(c.get_id(), pi.dwProcessId);
    BOOST_CHECK_EQUAL(c.get_primary_thread_handle(), pi.hThread);
    BOOST_CHECK_EQUAL(c.get_primary_thread_id(), pi.dwThreadId);
}
#endif

// ------------------------------------------------------------------------

#if !defined(BOOST_PROCESS_WIN32_API)
static
void
test_dummy(void)
{
}
#endif

// ------------------------------------------------------------------------

but::test_suite *
init_unit_test_suite(int argc, char* argv[])
{
    but::test_suite* test = BOOST_TEST_SUITE("win32_child test suite");

#if defined(BOOST_PROCESS_WIN32_API)
    add_tests_child_base< bp::win32_child, factory >(test);
    test->add(BOOST_TEST_CASE(&test_getters));
#else
    test->add(BOOST_TEST_CASE(&test_dummy));
#endif

    return test;
}
