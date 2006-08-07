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
//! \file boost/process/detail/win32_ops.hpp
//!
//! Provides some convenience functions to start processes under Win32
//! operating systems.
//!

#if !defined(BOOST_PROCESS_DETAIL_WIN32_OPS_HPP)
/** \cond */
#define BOOST_PROCESS_DETAIL_WIN32_OPS_HPP
/** \endcond */

#include <boost/process/config.hpp>

#if !defined(BOOST_PROCESS_WIN32_API)
#   error "Unsupported platform."
#endif

extern "C" {
#include <tchar.h>
#include <windows.h>
}

#include <boost/optional.hpp>
#include <boost/process/detail/command_line_ops.hpp>
#include <boost/process/detail/environment.hpp>
#include <boost/process/detail/file_handle.hpp>
#include <boost/process/detail/pipe.hpp>
#include <boost/process/detail/stream_info.hpp>
#include <boost/process/exceptions.hpp>
#include <boost/throw_exception.hpp>

namespace boost {
namespace process {
namespace detail {

// ------------------------------------------------------------------------

//!
//! \brief Helper class to configure a Win32 %child.
//!
//! This helper class is used to hold all the attributes that configure a
//! new Win32 %child process .
//!
//! All its fields are public for simplicity.  It is only intended for
//! internal use and it is heavily coupled with the Launcher
//! implementations.
//!
struct win32_setup
{
    //!
    //! \brief The work directory.
    //!
    //! This string specifies the directory in which the %child process
    //! starts execution.  It cannot be empty.
    //!
    std::string m_work_directory;

    //!
    //! \brief The process startup properties.
    //!
    //! This Win32-specific object holds a list of properties that describe
    //! how the new process should be started.  The STARTF_USESTDHANDLES
    //! flag should not be set in it because it is automatically configured
    //! by win32_start().
    //!
    STARTUPINFO* m_startupinfo;
};

// ------------------------------------------------------------------------

//!
//! \brief Starts a new child process in a Win32 operating system.
//!
//! This helper functions is provided to simplify the Launcher's task when
//! it comes to starting up a new process in a Win32 operating system.
//!
//! \param cl The command line used to execute the child process.
//! \param env The environment variables that the new child process
//!            receives.
//! \param infoin Information that describes stdin's behavior.
//! \param infoout Information that describes stdout's behavior.
//! \param infoerr Information that describes stderr's behavior.
//! \param setup A helper object holding extra child information.  The
//!              STARTUPINFO object in it is modified to set up the
//!              required redirections.
//! \return The new process' information as returned by the ::CreateProcess
//!         system call.  The caller is responsible of creating an
//!         appropriate Child representation for it.
//! \pre \a setup.m_startupinfo cannot have the \a STARTF_USESTDHANDLES set
//!      in the \a dwFlags field.
//!
template< class Command_Line >
inline
PROCESS_INFORMATION
win32_start(const Command_Line& cl,
            const environment& env,
            stream_info& infoin,
            stream_info& infoout,
            stream_info& infoerr,
            bool merge_out_err,
            win32_setup& setup)
{
    file_handle chin, chout, cherr;

    BOOST_ASSERT(!(setup.m_startupinfo->dwFlags & STARTF_USESTDHANDLES));
    setup.m_startupinfo->dwFlags = STARTF_USESTDHANDLES;

    if (infoin.m_type == stream_info::close) {
    } else if (infoin.m_type == stream_info::inherit) {
        chin = file_handle::win32_std(STD_INPUT_HANDLE, true);
    } else if (infoin.m_type == stream_info::usefile) {
        HANDLE h = ::CreateFile(TEXT(infoin.m_file.c_str()), GENERIC_READ,
                                0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
                                NULL);
        if (h == INVALID_HANDLE_VALUE)
            boost::throw_exception
                (system_error("boost::process::detail::win32_start",
                              "CreateFile failed", ::GetLastError()));
        chin = file_handle(h);
    } else if (infoin.m_type == stream_info::usehandle) {
        chin = infoin.m_handle;
    } else if (infoin.m_type == stream_info::usepipe) {
        infoin.m_pipe->rend().win32_set_inheritable(true);
        chin = infoin.m_pipe->rend();
    } else
        BOOST_ASSERT(false);
    setup.m_startupinfo->hStdInput =
        chin.is_valid() ? chin.get() : INVALID_HANDLE_VALUE;

    if (infoout.m_type == stream_info::close) {
    } else if (infoout.m_type == stream_info::inherit) {
        chout = file_handle::win32_std(STD_OUTPUT_HANDLE, true);
    } else if (infoout.m_type == stream_info::usefile) {
        HANDLE h = ::CreateFile(TEXT(infoout.m_file.c_str()), GENERIC_WRITE,
                                0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL,
                                NULL);
        if (h == INVALID_HANDLE_VALUE)
            boost::throw_exception
                (system_error("boost::process::detail::win32_start",
                              "CreateFile failed", ::GetLastError()));
        chout = file_handle(h);
    } else if (infoout.m_type == stream_info::usehandle) {
        chout = infoout.m_handle;
    } else if (infoout.m_type == stream_info::usepipe) {
        infoout.m_pipe->wend().win32_set_inheritable(true);
        chout = infoout.m_pipe->wend();
    } else
        BOOST_ASSERT(false);
    setup.m_startupinfo->hStdOutput =
        chout.is_valid() ? chout.get() : INVALID_HANDLE_VALUE;

    if (infoerr.m_type == stream_info::close) {
        if (merge_out_err) {
            BOOST_ASSERT(chout.is_valid());
            cherr = file_handle::win32_dup(chout.get(), true);
        }
    } else if (infoerr.m_type == stream_info::inherit) {
        cherr = file_handle::win32_std(STD_ERROR_HANDLE, true);
    } else if (infoerr.m_type == stream_info::usefile) {
        HANDLE h = ::CreateFile(TEXT(infoerr.m_file.c_str()), GENERIC_WRITE,
                                0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL,
                                NULL);
        if (h == INVALID_HANDLE_VALUE)
            boost::throw_exception
                (system_error("boost::process::detail::win32_start",
                              "CreateFile failed", ::GetLastError()));
        cherr = file_handle(h);
    } else if (infoerr.m_type == stream_info::usehandle) {
        cherr = infoerr.m_handle;
    } else if (infoerr.m_type == stream_info::usepipe) {
        infoerr.m_pipe->wend().win32_set_inheritable(true);
        cherr = infoerr.m_pipe->wend();
    } else
        BOOST_ASSERT(false);
    setup.m_startupinfo->hStdError =
        cherr.is_valid() ? cherr.get() : INVALID_HANDLE_VALUE;

    PROCESS_INFORMATION pi;
    ::ZeroMemory(&pi, sizeof(pi));

    boost::shared_array< TCHAR > cmdline =
        command_line_to_win32_cmdline(cl);
    boost::scoped_array< TCHAR > executable
        (::_tcsdup(TEXT(cl.get_executable().c_str())));
    boost::scoped_array< TCHAR > workdir
        (::_tcsdup(TEXT(setup.m_work_directory.c_str())));

    boost::shared_array< TCHAR > envstrs = env.win32_strings();
    if (!::CreateProcess(executable.get(), cmdline.get(), NULL, NULL, TRUE,
                         0, envstrs.get(), workdir.get(),
                         setup.m_startupinfo, &pi)) {
        boost::throw_exception
            (system_error("boost::process::detail::win32_start",
                          "CreateProcess failed", ::GetLastError()));
    }

    return pi;
}

// ------------------------------------------------------------------------

} // namespace detail
} // namespace process
} // namespace boost

#endif // !defined(BOOST_PROCESS_DETAIL_WIN32_OPS_HPP)
