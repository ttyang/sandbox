
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _TEST_CASE_BASE_2009_11_12_H_
  #define _TEST_CASE_BASE_2009_11_12_H_

  #include <string>
  #include <vector>
  #include <fstream>
  #include <iomanip>
  #include <algorithm>
  #include <iterator>


  #include <boost/e_float/e_float_complex.hpp>
  #include "../src/utility/util_noncopyable.h"

  namespace test
  {
    bool compare_value(std::string& str_result,
                       const e_float& my_value,
                       const e_float& control);

    bool compare_value(std::string& str_result,
                       const ef_complex& my_value,
                       const ef_complex& control);

    template<typename T> class TestCaseBase : private Util::noncopyable
    {
    protected:

      TestCaseBase() { }

    public:

      virtual ~TestCaseBase() { }

    protected:

      virtual const std::string& name(void) const = 0;

      virtual const std::vector<T>& control_data(void) const = 0;

      virtual void e_float_test(std::vector<T>&) const = 0;

      bool write_output_file(const std::vector<T>& data) const
      {
        std::ofstream out((name() + ".txt").c_str());

        if(out.is_open())
        {
          static const std::streamsize my_prec = static_cast<std::streamsize>(std::numeric_limits<e_float>::digits10);

          static_cast<void>(out.setf(std::ios::showpos | std::ios::scientific));
          static_cast<void>(out.precision(my_prec));

          std::copy(data.begin(), data.end(), std::ostream_iterator<T>(out, "\n"));

          out.close();

          return true;
        }
        else
        {
          return false;
        }
      }

    public:

      virtual bool execute(const bool b_write_output) const
      {
        std::cout << name() << " : ";

        std::vector<T> e_float_data;

        // Calculate the e_float test data.
        e_float_test(e_float_data);

        // Verify equal length of the data tables.
        if(e_float_data.size() != control_data().size())
        {
          std::cout << "Table size mismatch: FAIL" << std::endl;
          return false;
        }

        // Optionally write the e_float test data to an output file.
        if(b_write_output)
        {
          if(!write_output_file(e_float_data))
          {
            std::cout << "Can not write output: FAIL" << std::endl;
            return false;
          }
        }

        bool b_compare = true;

        for(typename std::vector<T>::size_type i = 0u; i < e_float_data.size(); i++)
        {
          std::string str_result;

          const bool b_result = compare_value(str_result, e_float_data[i], control_data()[i]);

          b_compare &= b_result;

          if(!b_result)
          {
            std::cout << str_result << ": Failed at index: " << i << std::endl;
          }
        }

        // Compare the e_float test data with the control data.
        if(b_compare)
        {
          std::cout << "Numerical compare OK: PASS"  << std::endl;
          return true;
        }
        else
        {
          std::cout << "Numerical compare not OK: FAIL"  << std::endl;
          return false;
        }
      }
    };
  }

#endif // _TEST_CASE_BASE_2009_11_12_H_
