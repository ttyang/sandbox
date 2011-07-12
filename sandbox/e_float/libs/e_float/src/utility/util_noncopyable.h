
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} © ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _UTIL_NONCOPYABLE_2009_03_30_H_
  #define _UTIL_NONCOPYABLE_2009_03_30_H_

  // Taken from boost.
  namespace Util
  {
    class noncopyable
    {
    protected:

      noncopyable() {}
      virtual ~noncopyable() {}

    private:  // emphasize the following members are private

      noncopyable(const noncopyable&);
      const noncopyable& operator=(const noncopyable&);
    };
  }

#endif // _UTIL_NONCOPYABLE_2009_03_30_H_
