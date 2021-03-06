
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _TEST_CASE_IMAG_2009_10_24_H_
  #define _TEST_CASE_IMAG_2009_10_24_H_

  #include "../test_case_base.h"

  namespace test
  {
    namespace imag
    {
      class TestCaseImag : public TestCaseBase<ef_complex>
      {
      private:

        TestCaseImag(const TestCaseImag&);
        const TestCaseImag& operator=(const TestCaseImag&);

      protected:

        TestCaseImag() { }

      public:

        virtual ~TestCaseImag() { }
      };
    }
  }

#endif // _TEST_CASE_IMAG_2009_10_24_H_
