//  boost/filesystem/operations.hpp  ---------------------------------------------------//

//  Copyright Beman Dawes 2002-2009
//  Copyright Jan Langer 2002
//  Copyright Dietmar Kuehl 2001                                        
//  Copyright Vladimir Prus 2002
   
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

//--------------------------------------------------------------------------------------//
/*
*                                TODO List
*
*  Review all operations.cpp code for race conditions similar to #2925. Fix or document.
*  Enable all BOOST_FILESYSTEM_NO_DEPRECATED code.
*  rename and remove really need to be renamed. If users says "using namespace boost::filesystem"
   and some header included stdio, there is just too much chance of silent error.
*  create_directories error handling.
*  Review any commented out code, both in operations.hpp and operations.cpp
*  Fold convenience.hpp into operations.hpp
*  Two argument recursive_directory_iterator ctor isn't recognizing throws().
   would it be better to fold into a single two argument ctor with default?
*  Add the push_directory class from tools/release/required_files.cpp

*/
//--------------------------------------------------------------------------------------// 

#ifndef BOOST_FILESYSTEM_OPERATIONS_HPP
#define BOOST_FILESYSTEM_OPERATIONS_HPP

#include <boost/filesystem/path.hpp>

#include <boost/detail/scoped_enum_emulation.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/iterator.hpp>
#include <boost/cstdint.hpp>
#include <boost/assert.hpp>

#include <string>
#include <utility> // for pair
#include <ctime>
#include <vector>
#include <stack>

#ifdef BOOST_WINDOWS_API
#  include <fstream>
#endif

#include <boost/config/abi_prefix.hpp> // must be the last #include

# ifdef BOOST_NO_STDC_NAMESPACE
    namespace std { using ::time_t; }
# endif

//--------------------------------------------------------------------------------------//

namespace boost
{
  namespace filesystem
  {

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                            support classes and enums                                 //
//                                                                                      //
//--------------------------------------------------------------------------------------//

  enum file_type
  { 
    status_error,
# ifndef BOOST_FILESYSTEM_NO_DEPRECATED
    status_unknown = status_error,
# endif
    file_not_found,
    regular_file,
    directory_file,
    // the following will never be reported by some operating or file systems
    symlink_file,
    block_file,
    character_file,
    fifo_file,
    socket_file,
    type_unknown // file does exist, but isn't one of the above types or
                 // we don't have strong enough permission to find its type
  };

  class BOOST_FILESYSTEM_DECL file_status
  {
  public:
    explicit file_status(file_type v = status_error) : m_value(v) {}

    void type(file_type v)    { m_value = v; }
    file_type type() const    { return m_value; }

    bool operator==(const file_status& rhs) const { return type() == rhs.type(); }
    bool operator!=(const file_status& rhs) const { return !(*this == rhs); }

  private:
    // the internal representation is unspecified so that additional state
    // information such as permissions can be added in the future; this
    // implementation just uses file_type as the internal representation

    file_type m_value;
  };

  inline bool status_known(file_status f) { return f.type() != status_error; }
  inline bool exists(file_status f)       { return f.type() != status_error
                                                && f.type() != file_not_found; }
  inline bool is_regular_file(file_status f){ return f.type() == regular_file; }
  inline bool is_directory(file_status f) { return f.type() == directory_file; }
  inline bool is_symlink(file_status f)   { return f.type() == symlink_file; }
  inline bool is_other(file_status f)     { return exists(f) && !is_regular_file(f)
                                                && !is_directory(f) && !is_symlink(f); }

# ifndef BOOST_FILESYSTEM_NO_DEPRECATED
  inline bool is_regular(file_status f)   { return f.type() == regular_file; }
# endif

  struct space_info
  {
    // all values are byte counts
    boost::uintmax_t capacity;
    boost::uintmax_t free;      // <= capacity
    boost::uintmax_t available; // <= free
  };

  BOOST_SCOPED_ENUM_START(copy_option)
    {fail_if_exists, overwrite_if_exists};
  BOOST_SCOPED_ENUM_END

//--------------------------------------------------------------------------------------//
//                             implementation details                                   //
//--------------------------------------------------------------------------------------//

  namespace detail
  {
    BOOST_FILESYSTEM_DECL
    file_status status(const path&p, system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    file_status symlink_status(const path& p, system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    path complete(const path& p, const path& base);
    BOOST_FILESYSTEM_DECL
    bool is_empty(const path& p, system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    path initial_path(system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    void copy(const path& from, const path& to, system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    void copy_directory(const path& from, const path& to, system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    void copy_file(const path& from, const path& to,
                    BOOST_SCOPED_ENUM(copy_option) option,  // See ticket #2925
                    system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    void copy_symlink(const path& from, const path& to, system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    bool create_directories(const path& p, system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    bool create_directory(const path& p, system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    void create_directory_symlink(const path& to, const path& from,
                                   system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    void create_hard_link(const path& to, const path& from, system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    void create_symlink(const path& to, const path& from, system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    path current_path(system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    void current_path(const path& p, system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    bool equivalent(const path& p1, const path& p2, system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    boost::uintmax_t file_size(const path& p, system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    boost::uintmax_t hard_link_count(const path& p, system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    std::time_t last_write_time(const path& p, system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    void last_write_time(const path& p, const std::time_t new_time,
                     system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    path read_symlink(const path& p, system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
      // For standardization, if the committee doesn't like "remove", consider "eliminate"
    bool remove(const path& p, system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    boost::uintmax_t remove_all(const path& p, system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    void rename(const path& old_p, const path& new_p, system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    void resize_file(const path& p, uintmax_t size, system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    space_info space(const path& p, system::error_code* ec=0); 
    BOOST_FILESYSTEM_DECL
    path system_complete(const path& p, system::error_code* ec=0);
    BOOST_FILESYSTEM_DECL
    path unique_path(const path& p, system::error_code* ec=0);
  }  // namespace detail

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                             status query functions                                   //
//                                                                                      //
//--------------------------------------------------------------------------------------//

  inline
  file_status status(const path& p)    {return detail::status(p);}
  inline 
  file_status status(const path& p, system::error_code& ec)
                                       {return detail::status(p, &ec);}
  inline 
  file_status symlink_status(const path& p) {return detail::symlink_status(p);}
  inline
  file_status symlink_status(const path& p, system::error_code& ec)
                                       {return detail::symlink_status(p, &ec);}
  inline 
  bool exists(const path& p)           {return exists(detail::status(p));}
  inline 
  bool exists(const path& p, system::error_code& ec)
                                       {return exists(detail::status(p, &ec));}
  inline 
  bool is_directory(const path& p)     {return is_directory(detail::status(p));}
  inline 
  bool is_directory(const path& p, system::error_code& ec)
                                       {return is_directory(detail::status(p, &ec));}
  inline 
  bool is_regular_file(const path& p)  {return is_regular_file(detail::status(p));}
  inline 
  bool is_regular_file(const path& p, system::error_code& ec)
                                       {return is_regular_file(detail::status(p, &ec));}
  inline 
  bool is_other(const path& p)         {return is_other(detail::status(p));}
  inline 
  bool is_other(const path& p, system::error_code& ec)
                                       {return is_other(detail::status(p, &ec));}
  inline
  bool is_symlink(const path& p)       {return is_symlink(detail::symlink_status(p));}
  inline 
  bool is_symlink(const path& p, system::error_code& ec)
                                       {return is_symlink(detail::symlink_status(p, &ec));}
# ifndef BOOST_FILESYSTEM_NO_DEPRECATED
  inline
  bool is_regular(const path& p)       {return is_regular(detail::status(p));}
  inline
  bool is_regular(const path& p, system::error_code& ec)
                                       {return is_regular(detail::status(p, &ec));}
# endif

  inline
  bool is_empty(const path& p)         {return detail::is_empty(p);}
  inline
  bool is_empty(const path& p, system::error_code& ec)
                                       {return detail::is_empty(p, &ec);}

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                             operational functions                                    //
//                  in alphabetical order, unless otherwise noted                       //
//                                                                                      //
//--------------------------------------------------------------------------------------//

  inline
  path complete(const path& p)
  {
    path base (detail::initial_path(0));
    return detail::complete(p, base);
  }

  inline
  path complete(const path& p, system::error_code& ec)
  {
    path base (detail::initial_path(&ec));
    if (ec) return path();
    return detail::complete(p, base);
  }

  inline
  path complete(const path& p, const path& base) {return detail::complete(p, base);}

  inline
  void copy(const path& from, const path& to) {detail::copy(from, to);}

  inline
  void copy(const path& from, const path& to, system::error_code& ec) 
                                       {detail::copy(from, to, &ec);}
  inline
  void copy_directory(const path& from, const path& to)
                                       {detail::copy_directory(from, to);}
  inline
  void copy_directory(const path& from, const path& to, system::error_code& ec)
                                       {detail::copy_directory(from, to, &ec);}
  inline
  void copy_file(const path& from, const path& to,   // See ticket #2925
                 BOOST_SCOPED_ENUM(copy_option) option)
                                       {detail::copy_file(from, to, option);}
  inline
  void copy_file(const path& from, const path& to)
                                       {detail::copy_file(from, to, copy_option::fail_if_exists);}
  inline
  void copy_file(const path& from, const path& to,   // See ticket #2925
                 BOOST_SCOPED_ENUM(copy_option) option, system::error_code& ec)
                                       {detail::copy_file(from, to, option, &ec);}
  inline
  void copy_file(const path& from, const path& to, system::error_code& ec)
                                       {detail::copy_file(from, to, copy_option::fail_if_exists, &ec);}
  inline
  void copy_symlink(const path& from, const path& to) {detail::copy_symlink(from, to);}

  inline
  void copy_symlink(const path& from, const path& to, system::error_code& ec)
                                       {detail::copy_symlink(from, to, &ec);}
  inline
  bool create_directories(const path& p) {return detail::create_directories(p);}

  inline
  bool create_directories(const path& p, system::error_code& ec)
                                       {return detail::create_directories(p, &ec);}
  inline
  bool create_directory(const path& p) {return detail::create_directory(p);}

  inline
  bool create_directory(const path& p, system::error_code& ec)
                                       {return detail::create_directory(p, &ec);}
  inline
  void create_directory_symlink(const path& to, const path& from)
                                       {detail::create_directory_symlink(to, from);}
  inline
  void create_directory_symlink(const path& to, const path& from, system::error_code& ec)
                                       {detail::create_directory_symlink(to, from, &ec);}
  inline
  void create_hard_link(const path& to, const path& from) {detail::create_hard_link(to, from);}

  inline
  void create_hard_link(const path& to, const path& from, system::error_code& ec)
                                       {detail::create_hard_link(to, from, &ec);}
  inline
  void create_symlink(const path& to, const path& from) {detail::create_symlink(to, from);}

  inline
  void create_symlink(const path& to, const path& from, system::error_code& ec)
                                       {detail::create_symlink(to, from, &ec);}
  inline
  path current_path()                  {return detail::current_path();}

  inline
  path current_path(system::error_code& ec) {return detail::current_path(&ec);}

  inline
  void current_path(const path& p)     {detail::current_path(p);}

  inline
  void current_path(const path& p, system::error_code& ec) {detail::current_path(p, &ec);}

  inline
  bool equivalent(const path& p1, const path& p2) {return detail::equivalent(p1, p2);}

  inline
  bool equivalent(const path& p1, const path& p2, system::error_code& ec)
                                       {return detail::equivalent(p1, p2, &ec);}
  inline
  boost::uintmax_t file_size(const path& p) {return detail::file_size(p);}

  inline
  boost::uintmax_t file_size(const path& p, system::error_code& ec)
                                       {return detail::file_size(p, &ec);}
  inline
  boost::uintmax_t hard_link_count(const path& p) {return detail::hard_link_count(p);}

  inline
  boost::uintmax_t hard_link_count(const path& p, system::error_code& ec)
                                       {return detail::hard_link_count(p, &ec);}
  inline
  path initial_path()                  {return detail::initial_path();}

  inline
  path initial_path(system::error_code& ec) {return detail::initial_path(&ec);}

# ifndef BOOST_FILESYSTEM_NO_DEPRECATED
  //  support legacy initial_path<...>()
  template <class Path>
  path initial_path() {return initial_path();}
  template <class Path>
  path initial_path(system::error_code& ec) {return detail::initial_path(&ec);}
# endif

  inline
  std::time_t last_write_time(const path& p) {return detail::last_write_time(p);}

  inline
  std::time_t last_write_time(const path& p, system::error_code& ec)
                                       {return detail::last_write_time(p, &ec);}
  inline
  void last_write_time(const path& p, const std::time_t new_time)
                                       {detail::last_write_time(p, new_time);}
  inline
  void last_write_time(const path& p, const std::time_t new_time, system::error_code& ec)
                                       {detail::last_write_time(p, new_time, &ec);}
  inline
  path read_symlink(const path& p)     {return detail::read_symlink(p);}

  inline
  path read_symlink(const path& p, system::error_code& ec)
                                       {return detail::read_symlink(p, &ec);}
  inline
    // For standardization, if the committee doesn't like "remove", consider "eliminate"
  bool remove(const path& p)           {return detail::remove(p);}

  inline
  bool remove(const path& p, system::error_code& ec) {return detail::remove(p, &ec);}

  inline
  boost::uintmax_t remove_all(const path& p) {return detail::remove_all(p);}
    
  inline
  boost::uintmax_t remove_all(const path& p, system::error_code& ec)
                                       {return detail::remove_all(p, &ec);}
  inline
  void rename(const path& old_p, const path& new_p) {detail::rename(old_p, new_p);}

  inline
  void rename(const path& old_p, const path& new_p, system::error_code& ec)
                                       {detail::rename(old_p, new_p, &ec);}
  inline  // name suggested by Scott McMurray
  void resize_file(const path& p, uintmax_t size) {detail::resize_file(p, size);}

  inline
  void resize_file(const path& p, uintmax_t size, system::error_code& ec)
                                       {detail::resize_file(p, size, &ec);}
  inline
  space_info space(const path& p)      {return detail::space(p);} 

  inline
  space_info space(const path& p, system::error_code& ec) {return detail::space(p, &ec);} 

# ifndef BOOST_FILESYSTEM_NO_DEPRECATED
    inline bool symbolic_link_exists(const path& p)
                                       { return is_symlink(symlink_status(p)); }
# endif

  inline
  path system_complete(const path& p)  {return detail::system_complete(p);}

  inline
  path system_complete(const path& p, system::error_code& ec)
                                       {return detail::system_complete(p, &ec);}
  inline
  path unique_path(const path& p="%%%%-%%%%-%%%%-%%%%")
                                       { return detail::unique_path(p); }
  inline
  path unique_path(const path& p, system::error_code& ec)
                                       { return detail::unique_path(p, &ec); }

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                 directory_entry                                      //
//                                                                                      //
//--------------------------------------------------------------------------------------//

//  GCC has a problem with a member function named path within a namespace or 
//  sub-namespace that also has a class named path. The workaround is to always
//  fully qualify the name path when it refers to the class name.

class BOOST_FILESYSTEM_DECL directory_entry
{
public:

  // compiler generated copy-ctor, copy assignment, and destructor apply

  directory_entry() {}
  explicit directory_entry(const boost::filesystem::path& p,
    file_status st = file_status(), file_status symlink_st=file_status())
    : m_path(p), m_status(st), m_symlink_status(symlink_st)
    {}

  void assign(const boost::filesystem::path& p,
    file_status st = file_status(), file_status symlink_st = file_status())
    { m_path = p; m_status = st; m_symlink_status = symlink_st; }

  void replace_filename(const boost::filesystem::path& p,
    file_status st = file_status(), file_status symlink_st = file_status())
  {
    m_path.remove_filename();
    m_path /= p;
    m_status = st;
    m_symlink_status = symlink_st;
  }

# ifndef BOOST_FILESYSTEM_NO_DEPRECATED
  void replace_leaf(const boost::filesystem::path& p,
    file_status st, file_status symlink_st)
      { replace_filename(p, st, symlink_st); }
# endif

  const boost::filesystem::path&  path() const               {return m_path;}
  file_status   status() const                               {return m_get_status();}
  file_status   status(system::error_code& ec) const         {return m_get_status(&ec);}
  file_status   symlink_status() const                       {return m_get_symlink_status();}
  file_status   symlink_status(system::error_code& ec) const {return m_get_symlink_status(&ec);}

  //// conversion simplifies the most common use of directory_entry
  // Removed; poor design and too likely to conflict with path v3 constructor templates
  //operator const boost::filesystem::path&() const { return m_path; }

//#   ifndef BOOST_FILESYSTEM_NO_DEPRECATED
//      // deprecated functions preserve common use cases in legacy code
//      typename Path::string_type filename() const
//      {
//        return path().filename();
//      }
//      typename Path::string_type leaf() const
//      {
//        return path().filename();
//      }
//      typename Path::string_type string() const
//      {
//        return path().string();
//      }
//#   endif

private:
  boost::filesystem::path   m_path;
  mutable file_status       m_status;           // stat()-like
  mutable file_status       m_symlink_status;   // lstat()-like

  file_status m_get_status(system::error_code* ec=0) const;
  file_status m_get_symlink_status(system::error_code* ec=0) const;
}; // directory_entry

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                            directory_iterator helpers                                //
//                                                                                      //
//--------------------------------------------------------------------------------------//

class directory_iterator;

namespace detail
{
  BOOST_FILESYSTEM_DECL
    system::error_code dir_itr_close(// never throws()
    void *& handle
#     if     defined(BOOST_POSIX_API)
        , void *& buffer
#     endif
  ); 

  struct dir_itr_imp
  {
    directory_entry  dir_entry;
    void*            handle;

#   ifdef BOOST_POSIX_API
      void*            buffer;  // see dir_itr_increment implementation
#   endif

    dir_itr_imp() : handle(0)
#     ifdef BOOST_POSIX_API
        , buffer(0)
#     endif
    {}

    ~dir_itr_imp() // never throws
    {
      dir_itr_close(handle
#       if defined(BOOST_POSIX_API)
         , buffer
#       endif
    );
    }
  };

  // see path::iterator: comment below
  BOOST_FILESYSTEM_DECL void directory_iterator_construct(directory_iterator& it,
    const path& p, system::error_code* ec);
  BOOST_FILESYSTEM_DECL void directory_iterator_increment(directory_iterator& it,
    system::error_code* ec);

}  // namespace detail

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                directory_iterator                                    //
//                                                                                      //
//--------------------------------------------------------------------------------------//

  class directory_iterator
    : public boost::iterator_facade< directory_iterator,
                                     directory_entry,
                                     boost::single_pass_traversal_tag >
  {
  public:

    directory_iterator(){}  // creates the "end" iterator

    // iterator_facade derived classes don't seem to like implementations in
    // separate translation unit dll's, so forward to detail functions
    explicit directory_iterator(const path& p)
        : m_imp(new detail::dir_itr_imp)
          { detail::directory_iterator_construct(*this, p, 0); }

    directory_iterator(const path& p, system::error_code& ec)
        : m_imp(new detail::dir_itr_imp)
          { detail::directory_iterator_construct(*this, p, &ec); }

   ~directory_iterator() {} // never throws

    directory_iterator& increment(system::error_code& ec)
    { 
      detail::directory_iterator_increment(*this, &ec);
      return *this;
    }

  private:
    friend struct detail::dir_itr_imp;
    friend void detail::directory_iterator_construct(directory_iterator& it,
      const path& p, system::error_code* ec);
    friend void detail::directory_iterator_increment(directory_iterator& it,
      system::error_code* ec);

    // shared_ptr provides shallow-copy semantics required for InputIterators.
    // m_imp.get()==0 indicates the end iterator.
    boost::shared_ptr< detail::dir_itr_imp >  m_imp;

    friend class boost::iterator_core_access;

    boost::iterator_facade<
      directory_iterator,
      directory_entry,
      boost::single_pass_traversal_tag >::reference dereference() const 
    {
      BOOST_ASSERT(m_imp.get() && "attempt to dereference end iterator");
      return m_imp->dir_entry;
    }

    void increment() { detail::directory_iterator_increment(*this, 0); }

    bool equal(const directory_iterator& rhs) const
      { return m_imp == rhs.m_imp; }
  };

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                      recursive_directory_iterator helpers                            //
//                                                                                      //
//--------------------------------------------------------------------------------------//

  namespace detail
  {
    struct recur_dir_itr_imp
    {
      typedef directory_iterator element_type;
      std::stack< element_type, std::vector< element_type > > m_stack;
      int  m_level;
      bool m_no_push_request;

      recur_dir_itr_imp() : m_level(0), m_no_push_request(false) {}

      void increment(system::error_code* ec);  // ec == 0 means throw on error

      void pop();

    };

    //  Implementation is inline to avoid dynamic linking difficulties with m_stack:
    //  Microsoft warning C4251, m_stack needs to have dll-interface to be used by
    //  clients of struct 'boost::filesystem::detail::recur_dir_itr_imp'

    inline
    void recur_dir_itr_imp::increment(system::error_code* ec)
    // ec == 0 means throw on error
    {
      if (m_no_push_request)
        { m_no_push_request = false; }
      else if (is_directory(m_stack.top()->status()))
      {
        if (ec == 0)
          m_stack.push(directory_iterator(m_stack.top()->path()));
        else
        {
          m_stack.push(directory_iterator(m_stack.top()->path(), *ec));
          if (*ec) return;
        }
        if (m_stack.top() != directory_iterator())
        {
          ++m_level;
          return;
        }
        m_stack.pop();
      }

      while (!m_stack.empty() && ++m_stack.top() == directory_iterator())
      {
        m_stack.pop();
        --m_level;
      }
    }

    inline
    void recur_dir_itr_imp::pop()
    {
      BOOST_ASSERT(m_level > 0 && "pop() on recursive_directory_iterator with level < 1");

      do
      {
        m_stack.pop();
        --m_level;
      }
      while (!m_stack.empty() && ++m_stack.top() == directory_iterator());
    }
  } // namespace detail

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                           recursive_directory_iterator                               //
//                                                                                      //
//--------------------------------------------------------------------------------------//

  class recursive_directory_iterator
    : public boost::iterator_facade<
        recursive_directory_iterator,
        directory_entry,
        boost::single_pass_traversal_tag >
  {
  public:

    recursive_directory_iterator(){}  // creates the "end" iterator

    explicit recursive_directory_iterator(const path& dir_path)
      : m_imp(new detail::recur_dir_itr_imp)
    {
      m_imp->m_stack.push(directory_iterator(dir_path));
      if (m_imp->m_stack.top() == directory_iterator())
        { m_imp.reset (); }
    }

    recursive_directory_iterator(const path& dir_path,
      system::error_code & ec)
    : m_imp(new detail::recur_dir_itr_imp)
    {
      m_imp->m_stack.push(directory_iterator(dir_path, ec));
      if (m_imp->m_stack.top() == directory_iterator())
        { m_imp.reset (); }
    }

    recursive_directory_iterator& increment(system::error_code* ec)
    {
      BOOST_ASSERT(m_imp.get() && "increment() on end recursive_directory_iterator");
      m_imp->increment(ec);
      return *this;
    }

    int level() const
    { 
      BOOST_ASSERT(m_imp.get() && "level() on end recursive_directory_iterator");
      return m_imp->m_level;
    }

    bool no_push_request() const
    {
      BOOST_ASSERT(m_imp.get() && "no_push_request() on end recursive_directory_iterator");
      return m_imp->m_no_push_request;
    }

    void pop()
    { 
      BOOST_ASSERT(m_imp.get() && "pop() on end recursive_directory_iterator");
      m_imp->pop();
      if (m_imp->m_stack.empty()) m_imp.reset(); // done, so make end iterator
    }

    void no_push()
    {
      BOOST_ASSERT(m_imp.get() && "no_push() on end recursive_directory_iterator");
      m_imp->m_no_push_request = true;
    }

    file_status status() const
    {
      BOOST_ASSERT(m_imp.get()
        && "status() on end recursive_directory_iterator");
      return m_imp->m_stack.top()->status();
    }

    file_status symlink_status() const
    {
      BOOST_ASSERT(m_imp.get()
        && "symlink_status() on end recursive_directory_iterator");
      return m_imp->m_stack.top()->symlink_status();
    }

  private:

    // shared_ptr provides shallow-copy semantics required for InputIterators.
    // m_imp.get()==0 indicates the end iterator.
    boost::shared_ptr< detail::recur_dir_itr_imp >  m_imp;

    friend class boost::iterator_core_access;

    boost::iterator_facade< 
      recursive_directory_iterator,
      directory_entry,
      boost::single_pass_traversal_tag >::reference
    dereference() const 
    {
      BOOST_ASSERT(m_imp.get() && "dereference of end recursive_directory_iterator");
      return *m_imp->m_stack.top();
    }

    void increment()
    { 
      BOOST_ASSERT(m_imp.get() && "increment of end recursive_directory_iterator");
      m_imp->increment(0);
      if (m_imp->m_stack.empty()) m_imp.reset(); // done, so make end iterator
    }

    bool equal(const recursive_directory_iterator& rhs) const
      { return m_imp == rhs.m_imp; }

  };

# if !defined(BOOST_FILESYSTEM_NO_DEPRECATED)
    typedef recursive_directory_iterator wrecursive_directory_iterator;
# endif

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                            class filesystem_error                                    //
//                                                                                      //
//--------------------------------------------------------------------------------------//
  
  class filesystem_error : public system::system_error
  {
  // see http://www.boost.org/more/error_handling.html for design rationale

  // all functions are inline to avoid issues with crossing dll boundaries

  public:
    // compiler generates copy constructor and copy assignment

    filesystem_error(
      const std::string & what_arg, system::error_code ec)
      : system::system_error(ec, what_arg)
    {
      try
      {
        m_imp_ptr.reset(new m_imp);
      }
      catch (...) { m_imp_ptr.reset(); }
    }

    filesystem_error(
      const std::string & what_arg, const path& path1_arg,
      system::error_code ec)
      : system::system_error(ec, what_arg)
    {
      try
      {
        m_imp_ptr.reset(new m_imp);
        m_imp_ptr->m_path1 = path1_arg;
      }
      catch (...) { m_imp_ptr.reset(); }
    }
    
    filesystem_error(
      const std::string & what_arg, const path& path1_arg,
      const path& path2_arg, system::error_code ec)
      : system::system_error(ec, what_arg)
    {
      try
      {
        m_imp_ptr.reset(new m_imp);
        m_imp_ptr->m_path1 = path1_arg;
        m_imp_ptr->m_path2 = path2_arg;
      }
      catch (...) { m_imp_ptr.reset(); }
    }

    ~filesystem_error() throw() {}

    const path& path1() const
    {
      static const path empty_path;
      return m_imp_ptr.get() ? m_imp_ptr->m_path1 : empty_path ;
    }
    const path& path2() const
    {
      static const path empty_path;
      return m_imp_ptr.get() ? m_imp_ptr->m_path2 : empty_path ;
    }

    const char* what() const throw()
    {
      if (!m_imp_ptr.get())
        return system::system_error::what();

      try
      {
        if (m_imp_ptr->m_what.empty())
        {
          m_imp_ptr->m_what = system::system_error::what();
          if (!m_imp_ptr->m_path1.empty())
          {
            m_imp_ptr->m_what += ": \"";
            m_imp_ptr->m_what += m_imp_ptr->m_path1.native_string();
            m_imp_ptr->m_what += "\"";
          }
          if (!m_imp_ptr->m_path2.empty())
          {
            m_imp_ptr->m_what += ", \"";
            m_imp_ptr->m_what += m_imp_ptr->m_path2.native_string();
            m_imp_ptr->m_what += "\"";
          }
        }
        return m_imp_ptr->m_what.c_str();
      }
      catch (...)
      {
        return system::system_error::what();
      }
    }

  private:
    struct m_imp
    {
      path         m_path1; // may be empty()
      path         m_path2; // may be empty()
      std::string  m_what;  // not built until needed
    };
    boost::shared_ptr<m_imp> m_imp_ptr;
  };

//  test helper  -----------------------------------------------------------------------//

//  Not part of the documented interface since false positives are possible;
//  there is no law that says that an OS that has large stat.st_size
//  actually supports large file sizes.

  namespace detail
  {
    BOOST_FILESYSTEM_DECL bool possible_large_file_size_support();
  }

  } // namespace filesystem
} // namespace boost


#include <boost/config/abi_suffix.hpp> // pops abi_prefix.hpp pragmas
#endif // BOOST_FILESYSTEM_OPERATIONS_HPP
