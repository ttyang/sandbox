
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _UTIL_TIMER_2010_01_26_H_
  #define _UTIL_TIMER_2010_01_26_H_

  #include "util_noncopyable.h"

  namespace Util
  {
    struct timer : private noncopyable
    {
    public:
      timer(const double ofs = 0.0) : offset(ofs),
                                      start (get_sec()) { }

      ~timer() { }

      double elapsed(void) const;

    private:
      timer(const timer&);
      const timer& operator=(const timer&);

      const volatile double offset;
      const volatile double start;

      static double get_sec(void);
    };
  }

#endif // _UTIL_TIMER_2010_01_26_H_
