// 
// Boost.Process 
// ~~~~~~~~~~~~~ 
// 
// Copyright (c) 2006, 2007 Julio M. Merino Vidal 
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling 
// Copyright (c) 2009 Boris Schaeling 
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling 
// 
// Distributed under the Boost Software License, Version 1.0. (See accompanying 
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) 
// 

#include <boost/process/config.hpp> 

#if defined(BOOST_POSIX_API) 
#   include <stdlib.h> 
#   include <unistd.h> 
#   include <sys/wait.h> 
#elif defined(BOOST_WINDOWS_API) 
#   include <windows.h> 
#else 
#   error "Unsupported platform." 
#endif 

#define BOOST_TEST_MAIN 
#include "util/boost.hpp" 
#include "util/use_helpers.hpp" 
#include <string> 
#include <vector> 
#include <utility> 
#include <cstdlib> 

BOOST_AUTO_TEST_CASE(test_close_stdin) 
{ 
    check_helpers(); 

    std::vector<std::string> args; 
    args.push_back("is-closed-stdin"); 

    bp::context ctx; 
    ctx.stdin_behavior = bpb::close::def(); 

    bp::child c = bp::create_child(get_helpers_path(), args, ctx); 

    int s = c.wait(); 
#if defined(BOOST_POSIX_API) 
    BOOST_REQUIRE(WIFEXITED(s)); 
    BOOST_CHECK_EQUAL(WEXITSTATUS(s), EXIT_SUCCESS); 
#elif defined(BOOST_WINDOWS_API) 
    BOOST_CHECK_EQUAL(s, EXIT_SUCCESS); 
#endif 
} 

BOOST_AUTO_TEST_CASE(test_close_stdout) 
{ 
    check_helpers(); 

    std::vector<std::string> args; 
    args.push_back("is-closed-stdout"); 

    bp::context ctx1; 
    ctx1.stdout_behavior = bpb::close::def(); 

    bp::child c1 = bp::create_child(get_helpers_path(), args, ctx1); 

    int s1 = c1.wait(); 
#if defined(BOOST_POSIX_API) 
    BOOST_REQUIRE(WIFEXITED(s1)); 
    BOOST_CHECK_EQUAL(WEXITSTATUS(s1), EXIT_SUCCESS); 
#elif defined(BOOST_WINDOWS_API) 
    BOOST_CHECK_EQUAL(s1, EXIT_SUCCESS); 
#endif 

    bp::context ctx2; 
    ctx2.stdout_behavior = bpb::pipe::def(bpb::pipe::output_stream); 

    bp::child c2 = bp::create_child(get_helpers_path(), args, ctx2); 

    int s2 = c2.wait(); 
#if defined(BOOST_POSIX_API) 
    BOOST_REQUIRE(WIFEXITED(s2)); 
    BOOST_CHECK_EQUAL(WEXITSTATUS(s2), EXIT_FAILURE); 
#elif defined(BOOST_WINDOWS_API) 
    BOOST_CHECK_EQUAL(s2, EXIT_FAILURE); 
#endif 
} 

BOOST_AUTO_TEST_CASE(test_close_stderr) 
{ 
    check_helpers(); 

    std::vector<std::string> args; 
    args.push_back("is-closed-stderr"); 

    bp::context ctx1; 
    ctx1.stderr_behavior = bpb::close::def(); 

    bp::child c1 = bp::create_child(get_helpers_path(), args, ctx1); 

    int s1 = c1.wait(); 
#if defined(BOOST_POSIX_API) 
    BOOST_REQUIRE(WIFEXITED(s1)); 
    BOOST_CHECK_EQUAL(WEXITSTATUS(s1), EXIT_SUCCESS); 
#elif defined(BOOST_WINDOWS_API) 
    BOOST_CHECK_EQUAL(s1, EXIT_SUCCESS); 
#endif 

    bp::context ctx2; 
    ctx2.stderr_behavior = bpb::pipe::def(bpb::pipe::output_stream); 

    bp::child c2 = bp::create_child(get_helpers_path(), args, ctx2); 

    int s2 = c2.wait(); 
#if defined(BOOST_POSIX_API) 
    BOOST_REQUIRE(WIFEXITED(s2)); 
    BOOST_CHECK_EQUAL(WEXITSTATUS(s2), EXIT_FAILURE); 
#elif defined(BOOST_WINDOWS_API) 
    BOOST_CHECK_EQUAL(s2, EXIT_FAILURE); 
#endif 
} 

BOOST_AUTO_TEST_CASE(test_input) 
{ 
    check_helpers(); 

    std::vector<std::string> args; 
    args.push_back("stdin-to-stdout"); 

    bp::context ctx; 
    ctx.stdin_behavior = bpb::pipe::def(bpb::pipe::input_stream); 
    ctx.stdout_behavior = bpb::pipe::def(bpb::pipe::output_stream); 

    bp::child c = bp::create_child(get_helpers_path(), args, ctx); 

    bp::postream &os = c.get_stdin(); 
    bp::pistream &is = c.get_stdout(); 

    os << "message-to-process" << std::endl; 
    os.close(); 

    std::string word; 
    is >> word; 
    BOOST_CHECK_EQUAL(word, "message-to-process"); 

    int s = c.wait(); 
#if defined(BOOST_POSIX_API) 
    BOOST_REQUIRE(WIFEXITED(s)); 
    BOOST_CHECK_EQUAL(WEXITSTATUS(s), EXIT_SUCCESS); 
#elif defined(BOOST_WINDOWS_API) 
    BOOST_CHECK_EQUAL(s, EXIT_SUCCESS); 
#endif 
} 

BOOST_AUTO_TEST_CASE(test_output) 
{ 
    std::vector<std::string> args; 
    args.push_back("echo-stdout"); 
    args.push_back("message-stdout"); 

    bp::context ctx; 
    ctx.stdout_behavior = bpb::pipe::def(bpb::pipe::output_stream); 

    bp::child c = bp::create_child(get_helpers_path(), args, ctx); 

    std::string word; 
    bp::pistream &is = c.get_stdout(); 
    is >> word; 
    BOOST_CHECK_EQUAL(word, "message-stdout"); 

    int s = c.wait(); 
#if defined(BOOST_POSIX_API) 
    BOOST_REQUIRE(WIFEXITED(s)); 
    BOOST_CHECK_EQUAL(WEXITSTATUS(s), EXIT_SUCCESS); 
#elif defined(BOOST_WINDOWS_API) 
    BOOST_CHECK_EQUAL(s, EXIT_SUCCESS); 
#endif 
} 

BOOST_AUTO_TEST_CASE(test_output_error) 
{ 
    std::vector<std::string> args; 
    args.push_back("echo-stderr"); 
    args.push_back("message-stderr"); 

    bp::context ctx; 
    ctx.stderr_behavior = bpb::pipe::def(bpb::pipe::output_stream); 

    bp::child c = bp::create_child(get_helpers_path(), args, ctx); 

    std::string word; 
    bp::pistream &is = c.get_stderr(); 
    is >> word; 
    BOOST_CHECK_EQUAL(word, "message-stderr"); 

    int s = c.wait(); 
#if defined(BOOST_POSIX_API) 
    BOOST_REQUIRE(WIFEXITED(s)); 
    BOOST_CHECK_EQUAL(WEXITSTATUS(s), EXIT_SUCCESS); 
#elif defined(BOOST_WINDOWS_API) 
    BOOST_CHECK_EQUAL(s, EXIT_SUCCESS); 
#endif 
} 

class redirect_to : public bpb::stream 
{ 
public: 
    redirect_to(stream_end_type stream_end) 
    { 
#if defined(BOOST_POSIX_API) 
        child_end_ = dup(stream_end); 
        if (child_end_ == -1) 
            BOOST_PROCESS_THROW_LAST_SYSTEM_ERROR("dup(2) failed"); 
#elif defined(BOOST_WINDOWS_API) 
        if (!DuplicateHandle(GetCurrentProcess(), stream_end, 
            GetCurrentProcess(), &child_end_, 0, TRUE, DUPLICATE_SAME_ACCESS)) 
            BOOST_PROCESS_THROW_LAST_SYSTEM_ERROR("DuplicateHandle() failed"); 
#endif 
    } 

    static boost::shared_ptr<redirect_to> def(stream_end_type stream_end) 
    { 
        return boost::make_shared<redirect_to>(redirect_to(stream_end)); 
    } 

    stream_end_type get_child_end() 
    { 
        return child_end_; 
    } 

private: 
    stream_end_type child_end_; 
}; 

BOOST_AUTO_TEST_CASE(test_redirect_err_to_out) 
{ 
    std::vector<std::string> args; 
    args.push_back("echo-stdout-stderr"); 
    args.push_back("message-to-two-streams"); 

    bp::context ctx; 
    ctx.stdout_behavior = bpb::pipe::def(bpb::pipe::output_stream); 
    ctx.stderr_behavior = redirect_to::def( 
        ctx.stdout_behavior->get_child_end()); 

    bp::child c = bp::create_child(get_helpers_path(), args, ctx); 

    bp::pistream &is = c.get_stdout(); 
    std::string word; 
    is >> word; 
    BOOST_CHECK_EQUAL(word, "stdout"); 
    is >> word; 
    BOOST_CHECK_EQUAL(word, "message-to-two-streams"); 
    is >> word; 
    BOOST_CHECK_EQUAL(word, "stderr"); 
    is >> word; 
    BOOST_CHECK_EQUAL(word, "message-to-two-streams"); 

    int s = c.wait(); 
#if defined(BOOST_POSIX_API) 
    BOOST_REQUIRE(WIFEXITED(s)); 
    BOOST_CHECK_EQUAL(WEXITSTATUS(s), EXIT_SUCCESS); 
#elif defined(BOOST_WINDOWS_API) 
    BOOST_CHECK_EQUAL(s, EXIT_SUCCESS); 
#endif 
} 

BOOST_AUTO_TEST_CASE(check_work_directory) 
{ 
    std::vector<std::string> args; 
    args.push_back("pwd"); 

    bp::context ctx; 
    BOOST_CHECK(bfs::equivalent(ctx.work_dir, bfs::current_path().string())); 

    ctx.stdout_behavior = bpb::pipe::def(bpb::pipe::output_stream); 

    bp::child c = bp::create_child(get_helpers_path(), args, ctx); 

    bp::pistream &is = c.get_stdout(); 
    std::string dir; 
    std::getline(is, dir); 
    std::string::size_type pos = dir.rfind('\r'); 
    if (pos != std::string::npos) 
        dir.erase(pos); 

    int s = c.wait(); 
#if defined(BOOST_POSIX_API) 
    BOOST_REQUIRE(WIFEXITED(s)); 
    BOOST_CHECK_EQUAL(WEXITSTATUS(s), EXIT_SUCCESS); 
#elif defined(BOOST_WINDOWS_API) 
    BOOST_CHECK_EQUAL(s, EXIT_SUCCESS); 
#endif 

    BOOST_CHECK_EQUAL(bfs::path(dir), bfs::path(ctx.work_dir)); 
} 

BOOST_AUTO_TEST_CASE(check_work_directory2) 
{ 
    std::vector<std::string> args; 
    args.push_back("pwd"); 

    bfs::path wdir = bfs::current_path() / "test.dir"; 
    BOOST_REQUIRE_NO_THROW(bfs::create_directory(wdir)); 

    try 
    { 
        bp::context ctx; 
        ctx.work_dir = wdir.string(); 
        ctx.stdout_behavior = bpb::pipe::def(bpb::pipe::output_stream); 

        bp::child c = bp::create_child(get_helpers_path(), args, ctx); 

        bp::pistream &is = c.get_stdout(); 
        std::string dir; 
        std::getline(is, dir); 
        std::string::size_type pos = dir.rfind('\r'); 
        if (pos != std::string::npos) 
            dir.erase(pos); 

        int s = c.wait(); 
#if defined(BOOST_POSIX_API) 
        BOOST_REQUIRE(WIFEXITED(s)); 
        BOOST_CHECK_EQUAL(WEXITSTATUS(s), EXIT_SUCCESS); 
#elif defined(BOOST_WINDOWS_API) 
        BOOST_CHECK_EQUAL(s, EXIT_SUCCESS); 
#endif 

        BOOST_CHECK_EQUAL(bfs::path(dir), bfs::path(ctx.work_dir)); 
        BOOST_CHECK_NO_THROW(bfs::remove_all(wdir)); 
    } 
    catch (...) 
    { 
        BOOST_CHECK_NO_THROW(bfs::remove_all(wdir)); 
        throw; 
    } 
} 

std::pair<bool, std::string> get_var_value(bp::context &ctx, const std::string &var) 
{ 
    std::vector<std::string> args; 
    args.push_back("query-env"); 
    args.push_back(var); 

    ctx.stdout_behavior = bpb::pipe::def(bpb::pipe::output_stream); 

    bp::child c = bp::create_child(get_helpers_path(), args, ctx); 

    bp::pistream &is = c.get_stdout(); 
    std::string status; 
    is >> status; 
    std::string gotval; 
    if (status == "defined") 
        is >> gotval; 

    int s = c.wait(); 
#if defined(BOOST_POSIX_API) 
    BOOST_REQUIRE(WIFEXITED(s)); 
    BOOST_CHECK_EQUAL(WEXITSTATUS(s), EXIT_SUCCESS); 
#elif defined(BOOST_WINDOWS_API) 
    BOOST_CHECK_EQUAL(s, EXIT_SUCCESS); 
#endif 

    return std::pair<bool, std::string>(status == "defined", gotval); 
} 

BOOST_AUTO_TEST_CASE(test_clear_environment) 
{ 
    bp::context ctx; 
    ctx.environment.erase("TO_BE_QUERIED"); 

#if defined(BOOST_POSIX_API) 
    BOOST_REQUIRE(setenv("TO_BE_QUERIED", "test", 1) != -1); 
    BOOST_REQUIRE(getenv("TO_BE_QUERIED") != 0); 
#elif defined(BOOST_WINDOWS_API) 
    BOOST_REQUIRE(SetEnvironmentVariableA("TO_BE_QUERIED", "test") != 0); 
    char buf[5]; 
    BOOST_REQUIRE(GetEnvironmentVariableA("TO_BE_QUERIED", buf, 5) == 4); 
#endif 

    std::pair<bool, std::string> p = get_var_value(ctx, "TO_BE_QUERIED"); 
    BOOST_REQUIRE(!p.first); 
} 

BOOST_AUTO_TEST_CASE(test_unset_environment) 
{ 
    std::vector<std::string> args; 
    args.push_back("query-env"); 
    args.push_back("TO_BE_UNSET"); 

#if defined(BOOST_POSIX_API) 
    BOOST_REQUIRE(setenv("TO_BE_UNSET", "test", 1) != -1); 
    BOOST_REQUIRE(getenv("TO_BE_UNSET") != 0); 
#elif defined(BOOST_WINDOWS_API) 
    BOOST_REQUIRE(SetEnvironmentVariableA("TO_BE_UNSET", "test") != 0); 
    char buf[5]; 
    BOOST_REQUIRE(GetEnvironmentVariableA("TO_BE_UNSET", buf, 5) == 4); 
#endif 

    bp::context ctx; 
    ctx.environment.erase("TO_BE_UNSET"); 
    std::pair<bool, std::string> p = get_var_value(ctx, "TO_BE_UNSET"); 
    BOOST_CHECK(!p.first); 
} 

BOOST_AUTO_TEST_CASE(test_set_environment_var) 
{ 
    std::vector<std::string> args; 
    args.push_back("query-env"); 
    args.push_back("TO_BE_SET"); 

#if defined(BOOST_POSIX_API) 
    unsetenv("TO_BE_SET"); 
    BOOST_REQUIRE(getenv("TO_BE_SET") == 0); 
#elif defined(BOOST_WINDOWS_API) 
    char buf[5]; 
    BOOST_REQUIRE(GetEnvironmentVariableA("TO_BE_SET", buf, 5) == 0 || 
                    SetEnvironmentVariableA("TO_BE_SET", NULL) != 0); 
    BOOST_REQUIRE(GetEnvironmentVariableA("TO_BE_SET", buf, 5) == 0); 
#endif 

    bp::context ctx; 
    ctx.environment.insert(bp::environment_t::value_type("TO_BE_SET", 
        "some-value")); 
    std::pair<bool, std::string> p = get_var_value(ctx, "TO_BE_SET"); 
    BOOST_CHECK(p.first); 
    BOOST_CHECK_EQUAL(p.second, "'some-value'"); 

#if defined(BOOST_POSIX_API) 
    bp::context ctx2; 
    ctx2.environment.insert(bp::environment_t::value_type("TO_BE_SET", "")); 
    std::pair<bool, std::string> p2 = get_var_value(ctx2, "TO_BE_SET"); 
    BOOST_CHECK(p2.first); 
    BOOST_CHECK_EQUAL(p2.second, "''"); 
#endif 
} 
