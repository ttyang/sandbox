//
// Boost.Process
//
// Copyright (c) 2006 Julio M. Merino Vidal.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0.  (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt.)
//

//!
//! \file boost/process/detail/command_line_ops.hpp
//!
//! Provides some convenience functions to convert command_line objects
//! to the representation used by the underlying operating system.
//!

#if !defined(BOOST_PROCESS_DETAIL_COMMAND_LINE_OPS_HPP)
/** \cond */
#define BOOST_PROCESS_DETAIL_COMMAND_LINE_OPS_HPP
/** \endcond */

#include <boost/process/config.hpp>

#if defined(BOOST_PROCESS_POSIX_API)
#   include <cerrno>
#   include <cstring>
#   include <utility>
#   include <boost/assert.hpp>
#elif defined(BOOST_PROCESS_WIN32_API)
#   include <tchar.h>
#   include <windows.h>
#   include <boost/shared_array.hpp>
#else
#   error "Unsupported platform."
#endif

#include <cstddef>

#include <boost/process/exceptions.hpp>
#include <boost/throw_exception.hpp>

namespace boost {
namespace process {
namespace detail {

// ------------------------------------------------------------------------

#if defined(BOOST_PROCESS_POSIX_API) || defined(BOOST_PROCESS_DOXYGEN)
//!
//! \brief Converts the command line to an array of C strings.
//!
//! Converts the command line's list of arguments to the format expected
//! by the \a argv parameter in the POSIX execve() system call.
//!
//! This operation is only available in POSIX systems.
//!
//! \return The first argument of the pair is an integer that indicates
//!         how many strings are stored in the second argument.  The
//!         second argument is a NULL-terminated, dynamically allocated
//!         vector of dynamically allocated strings holding the arguments
//!         to the executable.  The caller is responsible of freeing them.
//!
template< class Command_Line >
inline
std::pair< std::size_t, char** >
command_line_to_posix_argv(const Command_Line& cl)
{
    std::size_t nargs = cl.get_arguments().size();
    BOOST_ASSERT(nargs > 0);

    char** argv = new char*[nargs + 1];
    for (std::size_t i = 0; i < nargs; i++)
        argv[i] = ::strdup(cl.get_arguments()[i].c_str());
    argv[nargs] = NULL;

    return std::pair< std::size_t, char ** >(nargs, argv);
}
#endif

// ------------------------------------------------------------------------

#if defined(BOOST_PROCESS_WIN32_API) || defined(BOOST_PROCESS_DOXYGEN)
//!
//! \brief Converts the command line to a plain string.
//!
//! Converts the command line's list of arguments to the format
//! expected by the \a lpCommandLine parameter in the CreateProcess()
//! system call.
//!
//! This operation is only available in Win32 systems.
//!
//! \return A dynamically allocated string holding the command line
//!         to be passed to the executable.  It is returned in a
//!         shared_array object to ensure its release at some point.
//!
template< class Command_Line >
inline
boost::shared_array< TCHAR >
command_line_to_win32_cmdline(const Command_Line& cl)
{
    typedef std::vector< std::string > arguments_vector;
    arguments_vector args;

    std::size_t length = 0;
    for (Command_Line::arguments_vector::size_type i = 0;
         i < cl.get_arguments().size(); i++) {
        std::string arg = cl.get_arguments()[i];

        std::string::size_type pos = 0;
        while ((pos = arg.find('"', pos)) != std::string::npos) {
            arg.replace(pos, 1, "\\\"");
            pos += 2;
        }

        if (arg.find(' ') != std::string::npos)
            arg = '\"' + arg + '\"';

        if (i != cl.get_arguments().size() - 1)
            arg += ' ';

        args.push_back(arg);
        length += arg.size() + 1;
    }

    boost::shared_array< TCHAR > cmdline(new TCHAR[length]);
    ::_tcscpy_s(cmdline.get(), length, TEXT(""));
    for (arguments_vector::size_type i = 0; i < args.size(); i++)
        ::_tcscat_s(cmdline.get(), length, TEXT(args[i].c_str()));

    return cmdline;
}
#endif

// ------------------------------------------------------------------------

//!
//! \brief Locates a program in the path.
//!
//! Locates the executable program \a file in all the directory components
//! specified in \a path.  If \a path is empty, the value of the PATH
//! environment variable is used.
//!
//! The path variable is interpreted following the same conventions used
//! to parse the PATH environment variable in the underlying platform.
//!
inline
std::string
find_in_path(const std::string& file, std::string path = "")
{
#if defined(BOOST_PROCESS_POSIX_API)
    BOOST_ASSERT(file.find('/') == std::string::npos);
    const char delim = ':';
#elif defined(BOOST_PROCESS_WIN32_API)
    BOOST_ASSERT(file.find('\\') == std::string::npos);
    const char delim = ';';
#endif

    if (path.empty()) {
#if defined(BOOST_PROCESS_POSIX_API)
        const char* envpath = ::getenv("PATH");
        if (envpath == NULL)
            boost::throw_exception
                (system_error("boost::process::detail::find_in_path",
                              "getenv(2) of PATH failed", errno));
#elif defined(BOOST_PROCESS_WIN32_API)
        const char envpath[MAX_PATH];
        if (::GetEnvironmentVariable("PATH", envpath, MAX_PATH) == 0)
            boost::throw_exception
                (system_error("boost::process::detail::find_in_path",
                              "GetEnvironmentVariable of PATH failed",
                              ::GetLastError()));
#endif
        path = envpath;
    }
    BOOST_ASSERT(!path.empty());

    std::string result;

    std::string::size_type pos1 = 0, pos2;
    do {
        pos2 = path.find(delim, pos1);
        std::string dir = path.substr(pos1, pos2 - pos1);
        std::string f = dir + '/' + file;

#if defined(BOOST_PROCESS_POSIX_API)
        if (::access(f.c_str(), X_OK) == 0)
            result = f;
#elif defined(BOOST_PROCESS_WIN32_API)
#   error "Unimplemented."
#endif

        pos1 = pos2 + 1;
    } while (pos2 != std::string::npos && result.empty());

    if (result.empty())
        boost::throw_exception
            (system_error("boost::process::detail::find_in_path",
                          "cannot locate executable", ENOENT));

    return result;
}

// ------------------------------------------------------------------------

} // namespace detail
} // namespace process
} // namespace boost

#endif // !defined(BOOST_PROCESS_DETAIL_COMMAND_LINE_OPS_HPP)
