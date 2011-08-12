
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _UTIL_NUMERIC_CAST_2009_11_24_H_
  #define _UTIL_NUMERIC_CAST_2009_11_24_H_

  #include <string>
  #include <sstream>

  namespace Util
  {
    template<typename T> inline T numeric_cast(const std::string& str)
    {
      std::stringstream ss;
      ss << str;
      T t;
      ss >> t;
      return t;
    }

    template<typename T> inline T numeric_cast(const char* const s)
    {
      std::stringstream ss;
      ss << s;
      T t;
      ss >> t;
      return t;
    }
  }

#endif // _UTIL_NUMERIC_CAST_2009_11_24_H_
