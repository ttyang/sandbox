//
// Boost.Process
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

//
// This example program demonstrates the very basic usage of Boost.Process.
// It takes a list of CVS work directories as arguments and iterates over
// them bringing each one up to date.
//

// quickbook:begin(code)
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include <boost/process.hpp>

namespace bp = ::boost::process;

int
main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Please specify some directories." << std::endl;
        return EXIT_FAILURE;
    }

    //
    // Constructs a shell-based command line.
    //
    // This command line executes a CVS process passing it an update
    // command.  Note that it will be executed through the standard system
    // shell so that we do not have to know where the binary is located.
    //
    // In this case we have a command line that will work both on POSIX
    // systems and under Windows.
    //
    bp::command_line cl = bp::command_line::shell("cvs -z3 update -dP");

    for (int i = 1; i < argc; i++) {
        std::cout << "===> Updating directory " << argv[i] << std::endl;

        //
        // Constructs the launcher.
        //
        // This launcher will redirect us CVS' stdout and stderr data flows
        // through its stdout stream.  This will allow us to print the
        // output in a fancy way.
        //
        // The launcher also forces the CVS client to use the Secure Shell
        // to connect to servers and unsets the CVSROOT environment
        // variable to avoid side-effects.
        //
        bp::launcher l;
        l.set_stdout_behavior(bp::inherit_stream);
        l.set_merge_out_err(true);
        l.set_work_directory(argv[i]);
        l.set_environment("CVS_RSH", "ssh");
        l.unset_environment("CVSROOT");

        //
        // Spawns the CVS child process.
        //
        bp::child c = l.start(cl);

        //
        // Gets CVS' stdout stream.  As we asked for a merge of stdout and
        // stderr, this stream gets both outputs at once.
        //
        bp::pistream& is = c.get_stdout();

        //
        // Reads the child's output.
        //
        // As long as the child process (CVS) does not terminate, its
        // stdout will remain open and we will be able to retrieve data
        // from it.  Once it is closed, the 'is' stream will become invalid
        // and it will not return more data.
        //
        std::string line;
        while (std::getline(is, line))
            std::cout << "=> " << line << std::endl;

        //
        // Waits for the process to terminate and parses its exit status to
        // give the user feedback on the final results.
        //
        bp::status s = c.wait();
        if (s.exited() && s.exit_status() == EXIT_SUCCESS)
            std::cout << "     *** SUCCESSFUL UPDATE ***" << std::endl;
        else
            std::cout << "     *** FAILED UPDATE ***" << std::endl;
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}
// quickbook:end(code)
