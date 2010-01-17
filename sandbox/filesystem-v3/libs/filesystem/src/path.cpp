//  filesystem path.cpp  -------------------------------------------------------------  //

//  Copyright Beman Dawes 2008

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

// define BOOST_FILESYSTEM_SOURCE so that <boost/system/config.hpp> knows
// the library is being built (possibly exporting rather than importing code)
#define BOOST_FILESYSTEM_SOURCE 

#include <boost/filesystem/config.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/scoped_array.hpp>
#include <boost/system/error_code.hpp>
#include <boost/assert.hpp>
#include <cstddef>
#include <cstring>
#include <cassert>
#include "windows_file_codecvt.hpp"

#ifdef BOOST_FILESYSTEM_DEBUG
# include <iostream>
# include <iomanip>
#endif

#ifdef BOOST_WINDOWS_PATH
#  include <windows.h>
#endif

namespace fs = boost::filesystem;

using fs::path;

using std::string;
using std::wstring;

using boost::system::error_code;

#ifndef BOOST_FILESYSTEM_CODECVT_BUF_SIZE
# define BOOST_FILESYSTEM_CODECVT_BUF_SIZE 256
#endif

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                class path helpers                                    //
//                                                                                      //
//--------------------------------------------------------------------------------------//

namespace
{
  //------------------------------------------------------------------------------------//
  //                        miscellaneous class path helpers                            //
  //------------------------------------------------------------------------------------//

  typedef path::value_type        value_type;
  typedef path::string_type       string_type;
  typedef string_type::size_type  size_type;

  const std::size_t default_codecvt_buf_size = BOOST_FILESYSTEM_CODECVT_BUF_SIZE;

# ifdef BOOST_WINDOWS_PATH

  const wchar_t separator = L'/';
  const wchar_t preferred_separator = L'\\';
  const wchar_t* const separators = L"/\\";
  const wchar_t* separator_string = L"/";
  const wchar_t* preferred_separator_string = L"\\";
  const wchar_t colon = L':';
  const wchar_t dot = L'.';
  const fs::path dot_path(L".");
  const fs::path dot_dot_path(L"..");

# else

  const char separator = '/';
  const char preferred_separator = '/';
  const char* const separators = "/";
  const char* separator_string = "/";
  const char* preferred_separator_string = "/";
  const char colon = ':';
  const char dot = '.';
  const fs::path dot_path(".");
  const fs::path dot_dot_path("..");

# endif

  inline bool is_separator(fs::path::value_type c)
  {
    return c == separator
#     ifdef BOOST_WINDOWS_PATH
      || c == preferred_separator
#     endif
      ;
  }

  bool is_non_root_separator(const string_type& str, size_type pos);
    // pos is position of the separator

  size_type filename_pos(const string_type& str,
                          size_type end_pos); // end_pos is past-the-end position
  //  Returns: 0 if str itself is filename (or empty)

  size_type root_directory_start(const string_type& path, size_type size);
  //  Returns:  npos if no root_directory found

  void first_element(
      const string_type& src,
      size_type& element_pos,
      size_type& element_size,
#    if !BOOST_WORKAROUND(BOOST_MSVC, <= 1310) // VC++ 7.1
      size_type size = string_type::npos
#    else
      size_type size = -1
#    endif
    );

}  // unnamed namespace

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                            class path implementation                                 //
//                                                                                      //
//--------------------------------------------------------------------------------------//

namespace boost
{
namespace filesystem
{

  path & path::operator/=(const path & p)
  {
    if (p.empty())
      return *this;
    if (!is_separator(*p.m_pathname.begin()))
      m_append_separator_if_needed();
    m_pathname += p.m_pathname;
    return *this;
  }

# ifdef BOOST_WINDOWS_PATH

  const std::string  path::string() const
  { 
    std::string tmp;
    if (!m_pathname.empty())
      path_traits::convert(&*m_pathname.begin(), &*m_pathname.begin()+m_pathname.size(),
        tmp, codecvt());
    return tmp;
  }

  void path::m_portable()
  {
    for (string_type::iterator it = m_pathname.begin();
          it != m_pathname.end(); ++it)
    {
      if (*it == L'\\')
        *it = L'/';
    }
  }

  const std::string path::generic_string() const
  { 
    path tmp(*this);
    tmp.m_portable();
    return tmp.string();
  }

  const std::wstring path::generic_wstring() const
  { 
    path tmp(*this);
    tmp.m_portable();
    return tmp.wstring();
  }

  path & path::localize()
  {
    for (string_type::iterator it = m_pathname.begin();
          it != m_pathname.end(); ++it)
    {
      if (*it == L'/')
        *it = L'\\';
    }
    return *this;
  }

# endif  // BOOST_WINDOWS_PATH

  //  m_append_separator_if_needed  ----------------------------------------------------//

  path::string_type::size_type path::m_append_separator_if_needed()
  {
    if (!m_pathname.empty() &&
#   ifdef BOOST_WINDOWS_PATH
      *(m_pathname.end()-1) != colon && 
#   endif
      !is_separator(*(m_pathname.end()-1)))
    {
      string_type::size_type tmp(m_pathname.size());
      m_pathname += preferred_separator;
      return tmp;
    }
    return 0;
  }

  //  m_erase_redundant_separator  -----------------------------------------------------//

  void path::m_erase_redundant_separator(string_type::size_type sep_pos)
  {
    if (sep_pos                         // a separator was added
      && sep_pos < m_pathname.size()         // and something was appended
      && (m_pathname[sep_pos+1] == separator // and it was also separator
#   ifdef BOOST_WINDOWS_PATH
       || m_pathname[sep_pos+1] == preferred_separator  // or preferred_separator
#   endif
)) { m_pathname.erase(sep_pos, 1); } // erase the added separator
  }

  //  composition  ---------------------------------------------------------------------//

  path  path::absolute(const path& base) const
  {
    //  store expensive to compute values that are needed multiple times
    path this_root_name (root_name());
    path base_root_name (base.root_name());
#   ifdef BOOST_WINDOWS_PATH
    path this_root_directory (root_directory());
#   endif

#   ifndef BOOST_WINDOWS_PATH
    BOOST_ASSERT(!this_root_name.empty() || !base_root_name.empty());
#   endif

    BOOST_ASSERT(!this_root_directory.empty() || base.has_root_directory());
//
//    if (has_root_directory() // is_absolute
// #      ifdef BOOST_WINDOWS_PATH
//        && !this_root_name.empty()
// #      endif
//       ) return *this;
//
//    return (!this_root_name.empty() ? this_root_name : base_root_name)
//#     ifdef BOOST_POSIX_PATH
//      / separator
//#     else  // BOOST_WINDOWS_PATH
//      // use actual separator, which may be slash or backslash
//      / (!this_root_directory.empty() ? this_root_directory : base.root_directory())
//#     endif
//      / base.relative_path()
//      / relative_path();

    if (empty())
      return base;

    if (!this_root_name.empty()) // has_root_name
      return has_root_directory()
        ? m_pathname
        : this_root_name / base.root_directory() / base.relative_path() / relative_path();

    return has_root_directory()
      ? base.root_name() / m_pathname
      : base /  m_pathname;
  }

  //  decomposition  -------------------------------------------------------------------//

  path  path::root_path() const
  { 
    path temp(root_name());
    if (!root_directory().empty()) temp.m_pathname += root_directory().c_str();
    return temp;
  } 

  path path::root_name() const
  {
    iterator itr(begin());

    return (itr.m_pos != m_pathname.size()
      && (
          (itr.m_element.m_pathname.size() > 1
            && is_separator(itr.m_element.m_pathname[0])
            && is_separator(itr.m_element.m_pathname[1])
   )
#       ifdef BOOST_WINDOWS_PATH
        || itr.m_element.m_pathname[itr.m_element.m_pathname.size()-1] == colon
#       endif
  ))
      ? itr.m_element
      : path();
  }

  path path::root_directory() const
  {
    size_type pos(root_directory_start(m_pathname, m_pathname.size()));

    return pos == string_type::npos
      ? path()
      : path(m_pathname.c_str() + pos, m_pathname.c_str() + pos + 1);
  }

  path path::relative_path() const
  {
    iterator itr(begin());

    for (; itr.m_pos != m_pathname.size()
      && (is_separator(itr.m_element.m_pathname[0])
#       ifdef BOOST_WINDOWS_PATH
      || itr.m_element.m_pathname[itr.m_element.m_pathname.size()-1] == colon
#       endif
    ); ++itr) {}

    return path(m_pathname.c_str() + itr.m_pos);
  }

  string_type::size_type path::m_parent_path_end() const
  {
    size_type end_pos(filename_pos(m_pathname, m_pathname.size()));

    bool filename_was_separator(m_pathname.size()
      && is_separator(m_pathname[end_pos]));

    // skip separators unless root directory
    size_type root_dir_pos(root_directory_start(m_pathname, end_pos));
    for (; 
      end_pos > 0
      && (end_pos-1) != root_dir_pos
      && is_separator(m_pathname[end_pos-1])
      ;
      --end_pos) {}

   return (end_pos == 1 && root_dir_pos == 0 && filename_was_separator)
     ? string_type::npos
     : end_pos;
  }

  path path::parent_path() const
  {
   size_type end_pos(m_parent_path_end());
   return end_pos == string_type::npos
     ? path()
     : path(m_pathname.c_str(), m_pathname.c_str() + end_pos);
  }

  path& path::remove_filename()
  {
    m_pathname.erase(m_parent_path_end());
    return *this;
  }

  path path::filename() const
  {
    size_type pos(filename_pos(m_pathname, m_pathname.size()));
    return (m_pathname.size()
              && pos
              && is_separator(m_pathname[pos])
              && is_non_root_separator(m_pathname, pos))
      ? dot_path
      : path(m_pathname.c_str() + pos);
  }

  path path::stem() const
  {
    path name(filename());
    if (name == dot_path || name == dot_dot_path) return name;
    size_type pos(name.m_pathname.rfind(dot));
    return pos == string_type::npos
      ? name
      : path(name.m_pathname.c_str(), name.m_pathname.c_str() + pos);
  }

  path path::extension() const
  {
    path name(filename());
    if (name == dot_path || name == dot_dot_path) return path();
    size_type pos(name.m_pathname.rfind(dot));
    return pos == string_type::npos
      ? path()
      : path(name.m_pathname.c_str() + pos);
  }

  path & path::replace_extension(const path & source)
  {
    // erase existing extension if any
    size_type pos(m_pathname.rfind(dot));
    if (pos != string_type::npos)
      m_pathname.erase(pos);

    // append source extension if any
    pos = source.m_pathname.rfind(dot);
    if (pos != string_type::npos)
      m_pathname += source.c_str() + pos;

    return *this;
  }


  // m_normalize  ----------------------------------------------------------------------//

  path& path::m_normalize()
  {
    if (m_pathname.empty()) return *this;
      
    path temp;
    iterator start(begin());
    iterator last(end());
    iterator stop(last--);
    for (iterator itr(start); itr != stop; ++itr)
    {
      // ignore "." except at start and last
      if (itr->native().size() == 1
        && (itr->native())[0] == dot
        && itr != start
        && itr != last) continue;

      // ignore a name and following ".."
      if (!temp.empty()
        && itr->native().size() == 2
        && (itr->native())[0] == dot
        && (itr->native())[1] == dot) // dot dot
      {
        string_type lf(temp.filename().native());  
        if (lf.size() > 0  
          && (lf.size() != 1
            || (lf[0] != dot
              && lf[0] != separator))
          && (lf.size() != 2 
            || (lf[0] != dot
              && lf[1] != dot
#             ifdef BOOST_WINDOWS_PATH
              && lf[1] != colon
#             endif
               )
             )
          )
        {
          temp.remove_filename();
          // if not root directory, must also remove "/" if any
          if (temp.m_pathname.size() > 0
            && temp.m_pathname[temp.m_pathname.size()-1]
              == separator)
          {
            string_type::size_type rds(
              root_directory_start(temp.m_pathname, temp.m_pathname.size()));
            if (rds == string_type::npos
              || rds != temp.m_pathname.size()-1) 
              { temp.m_pathname.erase(temp.m_pathname.size()-1); }
          }

          iterator next(itr);
          if (temp.empty() && ++next != stop
            && next == last && *last == dot_path) temp /= dot_path;
          continue;
        }
      }

      temp /= *itr;
    };

    if (temp.empty()) temp /= dot_path;
    m_pathname = temp.m_pathname;
    return *this;
  }

}  // namespace filesystem
}  // namespace boost
  
//--------------------------------------------------------------------------------------//
//                                                                                      //
//                         class path helpers implementation                            //
//                                                                                      //
//--------------------------------------------------------------------------------------//

namespace
{

  //  is_non_root_separator  -------------------------------------------------//

  bool is_non_root_separator(const string_type & str, size_type pos)
    // pos is position of the separator
  {
    BOOST_ASSERT(!str.empty() && is_separator(str[pos])
      && "precondition violation");

    // subsequent logic expects pos to be for leftmost slash of a set
    while (pos > 0 && is_separator(str[pos-1]))
      --pos;

    return  pos != 0
      && (pos <= 2 || !is_separator(str[1])
        || str.find_first_of(separators, 2) != pos)
#   ifdef BOOST_WINDOWS_PATH
      && (pos !=2 || str[1] != colon)
#   endif
        ;
  }

  //  filename_pos  --------------------------------------------------------------------//

  size_type filename_pos(const string_type & str,
                          size_type end_pos) // end_pos is past-the-end position
    // return 0 if str itself is filename (or empty)
  {
    // case: "//"
    if (end_pos == 2 
      && is_separator(str[0])
      && is_separator(str[1])) return 0;

    // case: ends in "/"
    if (end_pos && is_separator(str[end_pos-1]))
      return end_pos-1;
    
    // set pos to start of last element
    size_type pos(str.find_last_of(separators, end_pos-1));

# ifdef BOOST_WINDOWS_PATH
    if (pos == string_type::npos)
      pos = str.find_last_of(colon, end_pos-2);
# endif

    return (pos == string_type::npos // path itself must be a filename (or empty)
      || (pos == 1 && is_separator(str[0]))) // or net
        ? 0 // so filename is entire string
        : pos + 1; // or starts after delimiter
  }

  //  root_directory_start  ------------------------------------------------------------//

  size_type root_directory_start(const string_type & path, size_type size)
  // return npos if no root_directory found
  {

#   ifdef BOOST_WINDOWS_PATH
    // case "c:/"
    if (size > 2
      && path[1] == colon
      && is_separator(path[2])) return 2;
#   endif

    // case "//"
    if (size == 2
      && is_separator(path[0])
      && is_separator(path[1])) return string_type::npos;

    // case "//net {/}"
    if (size > 3
      && is_separator(path[0])
      && is_separator(path[1])
      && !is_separator(path[2]))
    {
      string_type::size_type pos(path.find_first_of(separators, 2));
      return pos < size ? pos : string_type::npos;
    }
    
    // case "/"
    if (size > 0 && is_separator(path[0])) return 0;

    return string_type::npos;
  }

  //  first_element --------------------------------------------------------------------//
  //   sets pos and len of first element, excluding extra separators
  //   if src.empty(), sets pos,len, to 0,0.

  void first_element(
      const string_type & src,
      size_type & element_pos,
      size_type & element_size,
      size_type size
)
  {
    if (size == string_type::npos) size = src.size();
    element_pos = 0;
    element_size = 0;
    if (src.empty()) return;

    string_type::size_type cur(0);
    
    // deal with // [network]
    if (size >= 2 && is_separator(src[0])
      && is_separator(src[1])
      && (size == 2
        || !is_separator(src[2])))
    { 
      cur += 2;
      element_size += 2;
    }

    // leading (not non-network) separator
    else if (is_separator(src[0]))
    {
      ++element_size;
      // bypass extra leading separators
      while (cur+1 < size
        && is_separator(src[cur+1]))
      {
        ++cur;
        ++element_pos;
      }
      return;
    }

    // at this point, we have either a plain name, a network name,
    // or (on Windows only) a device name

    // find the end
    while (cur < size
#     ifdef BOOST_WINDOWS_PATH
      && src[cur] != colon
#     endif
      && !is_separator(src[cur]))
    {
      ++cur;
      ++element_size;
    }

#   ifdef BOOST_WINDOWS_PATH
    if (cur == size) return;
    // include device delimiter
    if (src[cur] == colon)
      { ++element_size; }
#   endif

    return;
  }

}  // unnammed namespace

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                        class path::iterator implementation                           //
//                                                                                      //
//--------------------------------------------------------------------------------------//

namespace boost
{
namespace filesystem
{

  path::iterator path::begin() const
  {
    iterator itr;
    itr.m_path_ptr = this;
    size_type element_size;
    first_element(m_pathname, itr.m_pos, element_size);
    itr.m_element = m_pathname.substr(itr.m_pos, element_size);
    if (itr.m_element.m_pathname == preferred_separator_string)
      itr.m_element.m_pathname = separator_string;  // needed for Windows, harmless on POSIX
    return itr;
  }

  path::iterator path::end() const
  {
    iterator itr;
    itr.m_path_ptr = this;
    itr.m_pos = m_pathname.size();
    return itr;
  }

  void path::m_path_iterator_increment(path::iterator & it)
  {
    BOOST_ASSERT(it.m_pos < it.m_path_ptr->m_pathname.size() && "path::basic_iterator increment past end()");

    // increment to position past current element
    it.m_pos += it.m_element.m_pathname.size();

    // if end reached, create end basic_iterator
    if (it.m_pos == it.m_path_ptr->m_pathname.size())
    {
      it.m_element.clear(); 
      return;
    }

    // both POSIX and Windows treat paths that begin with exactly two separators specially
    bool was_net(it.m_element.m_pathname.size() > 2
      && is_separator(it.m_element.m_pathname[0])
      && is_separator(it.m_element.m_pathname[1])
      && !is_separator(it.m_element.m_pathname[2]));

    // process separator (Windows drive spec is only case not a separator)
    if (is_separator(it.m_path_ptr->m_pathname[it.m_pos]))
    {
      // detect root directory
      if (was_net
#       ifdef BOOST_WINDOWS_PATH
        // case "c:/"
        || it.m_element.m_pathname[it.m_element.m_pathname.size()-1] == colon
#       endif
         )
      {
        it.m_element.m_pathname = separator;
        return;
      }

      // bypass separators
      while (it.m_pos != it.m_path_ptr->m_pathname.size()
        && is_separator(it.m_path_ptr->m_pathname[it.m_pos]))
        { ++it.m_pos; }

      // detect trailing separator, and treat it as ".", per POSIX spec
      if (it.m_pos == it.m_path_ptr->m_pathname.size()
        && is_non_root_separator(it.m_path_ptr->m_pathname, it.m_pos-1)) 
      {
        --it.m_pos;
        it.m_element = dot_path;
        return;
      }
    }

    // get next element
    size_type end_pos(it.m_path_ptr->m_pathname.find_first_of(separators, it.m_pos));
    if (end_pos == string_type::npos) end_pos = it.m_path_ptr->m_pathname.size();
    it.m_element = it.m_path_ptr->m_pathname.substr(it.m_pos, end_pos - it.m_pos);
  }

  void path::m_path_iterator_decrement(path::iterator & it)
  {
    BOOST_ASSERT(it.m_pos && "path::iterator decrement past begin()");

    size_type end_pos(it.m_pos);

    // if at end and there was a trailing non-root '/', return "."
    if (it.m_pos == it.m_path_ptr->m_pathname.size()
      && it.m_path_ptr->m_pathname.size() > 1
      && is_separator(it.m_path_ptr->m_pathname[it.m_pos-1])
      && is_non_root_separator(it.m_path_ptr->m_pathname, it.m_pos-1) 
       )
    {
      --it.m_pos;
      it.m_element = dot_path;
      return;
    }

    size_type root_dir_pos(root_directory_start(it.m_path_ptr->m_pathname, end_pos));

    // skip separators unless root directory
    for (
      ; 
      end_pos > 0
      && (end_pos-1) != root_dir_pos
      && is_separator(it.m_path_ptr->m_pathname[end_pos-1])
      ;
      --end_pos) {}

    it.m_pos = filename_pos(it.m_path_ptr->m_pathname, end_pos);
    it.m_element = it.m_path_ptr->m_pathname.substr(it.m_pos, end_pos - it.m_pos);
    if (it.m_element.m_pathname == preferred_separator_string)
      it.m_element.m_pathname = separator_string;  // needed for Windows, harmless on POSIX
  }

}  // namespace filesystem
}  // namespace boost

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                 detail helpers                                       //
//                                                                                      //
//--------------------------------------------------------------------------------------//

namespace
{

  //------------------------------------------------------------------------------------//
  //                              locale helpers                                        //
  //------------------------------------------------------------------------------------//

  // std::locale construction can throw (if LC_MESSAGES is wrong, for example),
  // so a static at function scope is used to ensure that exceptions can be
  // caught. (A previous version was at namespace scope, so initialization
  // occurred before main(), preventing exceptions from being caught.)

  std::locale default_locale()
  {
# ifdef BOOST_WINDOWS_API
    std::locale global_loc = std::locale();
    std::locale loc(global_loc, new windows_file_codecvt);
    return loc;
# else
    // ISO C calls this "the locale-specific native environment":
#   if !defined(macintosh) && !defined(__APPLE__) && !defined(__APPLE_CC__) 
      return std::locale("");
#   else
      return std::locale();  // std::locale("") throws on Mac OS
#   endif
# endif
  }

  std::locale & path_locale()
  {
    // ISO C calls this "the locale-specific native environment":
    static std::locale loc(default_locale());
    return loc;
  }

}  // unnamed namespace

//--------------------------------------------------------------------------------------//
//                           path::imbue implementation                                 //
//--------------------------------------------------------------------------------------//

namespace boost
{
namespace filesystem
{

  const path::codecvt_type *&
    path::wchar_t_codecvt_facet()
  {
   static const std::codecvt<wchar_t, char, std::mbstate_t> *
     facet(
       &std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t> >
        (path_locale()));
   return facet;
  }

  std::locale path::imbue(const std::locale & loc)
  {
    std::locale temp(path_locale());
    path_locale() = loc;
    wchar_t_codecvt_facet() = &std::use_facet
        <std::codecvt<wchar_t, char, std::mbstate_t> >(path_locale());
    return temp;
  }

}  // namespace filesystem
}  // namespace boost
