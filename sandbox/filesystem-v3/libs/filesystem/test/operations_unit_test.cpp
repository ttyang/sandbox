//  operations_unit_test.cpp  ----------------------------------------------------------//

//  Copyright Beman Dawes 2008

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

#include <iostream>
#include <boost/filesystem/operations.hpp>
#include <boost/system/error_code.hpp>
#include <boost/detail/lightweight_test.hpp>

using namespace boost::filesystem;
using namespace boost::system;
using std::cout;
using std::string;

#define CHECK(x) check(x, __FILE__, __LINE__)

namespace
{

  std::string this_file;
  
  void check(bool ok, const char* file, int line)
  {
    if (ok) return;

    ++::boost::detail::test_errors();

    std::cout << file << '(' << line << "): test failed\n";
  }

  //  query_test  ----------------------------------------------------------------------//

  void query_test()
  {
    std::cout << "query test..." << std::endl;

    error_code ec;

    CHECK(file_size("no-such-file", ec) == 0);
    CHECK(ec == errc::no_such_file_or_directory);

    CHECK(status("no-such-file") == file_status(file_not_found));

    CHECK(exists("/"));
    CHECK(!exists("no-such-file"));

    CHECK(is_directory("/"));
    CHECK(!is_directory(this_file));

    CHECK(is_regular_file(this_file));
    CHECK(!boost::filesystem::is_empty(this_file));
    CHECK(!is_other(this_file));
  }

  //  directory_iterator_test  -----------------------------------------------//

  void directory_iterator_test()
  {
    std::cout << "directory_iterator_test..." << std::endl;

    directory_iterator end;

    directory_iterator it(".");

    CHECK(!it->path().empty());

    if (is_regular_file(it->status()))
    {
      CHECK(is_regular_file(it->symlink_status()));
      CHECK(!is_directory(it->status()));
      CHECK(!is_symlink(it->status()));
      CHECK(!is_directory(it->symlink_status()));
      CHECK(!is_symlink(it->symlink_status()));
    }
    else
    {
      CHECK(is_directory(it->status()));
      CHECK(is_directory(it->symlink_status()));
      CHECK(!is_regular_file(it->status()));
      CHECK(!is_regular_file(it->symlink_status()));
      CHECK(!is_symlink(it->status()));
      CHECK(!is_symlink(it->symlink_status()));
    }

    for (; it != end; ++it)
    {
//      cout << "  " << it->path().string() << "\n";
    }

    std::cout << "directory_iterator_test complete" << std::endl;
  }

  //  operations_test  -------------------------------------------------------//

  void operations_test()
  {
    std::cout << "operations test..." << std::endl;

    error_code ec;

    CHECK(complete("foo", "c:/") == "c:/foo");

    CHECK(!create_directory("/", ec));

    CHECK(!boost::filesystem::remove("no-such-file-or-directory"));
    CHECK(!remove_all("no-such-file-or-directory"));

    space_info info = space("/");

    CHECK(info.available <= info.capacity);

    CHECK(equivalent("/", "/"));
    CHECK(!equivalent("/", "."));

    std::time_t ft = last_write_time(".");
    ft = -1;
    last_write_time(".", ft, ec);
  }

  //  directory_entry_overload_test  ---------------------------------------------------//

  void directory_entry_overload_test()
  {
    std::cout << "directory_entry overload test..." << std::endl;

    directory_iterator it(".");
    path p(*it);
  }

}  // unnamed namespace

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                    main                                              //
//                                                                                      //
//--------------------------------------------------------------------------------------//

int main(int, char* argv[])
{
  this_file = argv[0];

  cout << current_path().string() << std::endl;

  //  error handling tests

  bool threw(false);
  try
  { 
    file_size("no-such-file");
  }
  catch (const boost::filesystem::filesystem_error & ex)
  {
    threw = true;
    cout << "\nas expected, attempt to get size of non-existent file threw a filesystem_error\n"
      "what() returns " << ex.what() << "\n";
  }
  catch (...)
  {
    cout << "\nunexpected exception type caught" << std::endl;
  }

  CHECK(threw);

  error_code ec;
  CHECK(!create_directory("/", ec));

  query_test();
  directory_iterator_test();
  operations_test();
  directory_entry_overload_test();
  
  return ::boost::report_errors();
}
