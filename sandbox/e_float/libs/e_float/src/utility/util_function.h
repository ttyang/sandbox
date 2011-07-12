
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} © ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _UTIL_FUNCTION_2009_10_27_H_
  #define _UTIL_FUNCTION_2009_10_27_H_

  namespace Util
  {
    template<typename T> class Function
    {
    private:

      const Function& operator=(const Function&);
      Function(const Function&);

    protected:

      Function() { }

    public:

      virtual ~Function() { }

    private:

      virtual T my_function(const T&) const = 0;

    public:

      T function(const T& x) const { return my_function(x); }
    };
  }

#endif // _UTIL_FUNCTION_2009_10_27_H_
