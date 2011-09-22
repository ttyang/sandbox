
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/multiprecision/mp_float_functions.hpp>
#include "../test_case_real.h"

using boost::multiprecision::mp_float;

namespace test
{
  namespace real
  {
    class TestCaseOverflowUnderflowBase : public TestCaseReal
    {
    protected:
      static const boost::int32_t kmax = static_cast<boost::int32_t>(1000);

      mutable bool my_test_result;

      TestCaseOverflowUnderflowBase() : my_test_result(false) { }

    private:

      virtual const std::vector<mp_float>& control_data(void) const
      {
        static const std::vector<mp_float> dummy(1u, boost::multiprecision::one());
        return dummy;
      }

    public:

      virtual ~TestCaseOverflowUnderflowBase() { }

      virtual bool execute(const bool b_write_output) const
      {
        std::cout << name() << " : ";

        std::vector<mp_float> mp_float_data;

        // Calculate the mp_float test data.
        mp_float_test(mp_float_data);

        // Optionally write the mp_float test data to an output file.
        if(b_write_output)
        {
          if(!write_output_file(mp_float_data))
          {
            std::cout << "Can not write output: FAIL" << std::endl;
            return false;
          }
        }

        if(my_test_result)
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

    class TestCase_case_00001_overflow_mul_x : public TestCaseOverflowUnderflowBase
    {
    public:
      TestCase_case_00001_overflow_mul_x() { }
      virtual ~TestCase_case_00001_overflow_mul_x() { }
    private:
      virtual const std::string& name(void) const
      {
        static const std::string str("TestCase_case_00001_overflow_mul_x");
        return str;
      }
      virtual void mp_float_test(std::vector<mp_float>& data) const
      {
        data.clear();

        mp_float y = boost::multiprecision::googol() * boost::multiprecision::euler_gamma();

        data.push_back(y);

        boost::int32_t k;
        for(k = static_cast<boost::int32_t>(0); k < kmax; k++)
        {
          y = y * y;

          data.push_back(y);

          if(boost::multiprecision::isinf(y)) { break; }
        }

        my_test_result = (k > static_cast<boost::int32_t>(1)) && (k < kmax);
      }
    };

    class TestCase_case_00002_underflow_mul_x : public TestCaseOverflowUnderflowBase
    {
    public:
      TestCase_case_00002_underflow_mul_x() { }
      virtual ~TestCase_case_00002_underflow_mul_x() { }
    private:
      virtual const std::string& name(void) const
      {
        static const std::string str("TestCase_case_00002_underflow_mul_x");
        return str;
      }
      virtual void mp_float_test(std::vector<mp_float>& data) const
      {
        data.clear();

        mp_float y = boost::multiprecision::one() / (boost::multiprecision::googol() * boost::multiprecision::euler_gamma());

        data.push_back(y);

        boost::int32_t k;
        for(k = static_cast<boost::int32_t>(0); k < kmax; k++)
        {
          y = y * y;

          data.push_back(y);

          if(boost::multiprecision::iszero(y)) { break; }
        }

        my_test_result = (k > static_cast<boost::int32_t>(1)) && (k < static_cast<boost::int32_t>(1000));
      }
    };

    class TestCase_case_00003_overflow_x_mul_by_n : public TestCaseOverflowUnderflowBase
    {
    public:
      TestCase_case_00003_overflow_x_mul_by_n() { }
      virtual ~TestCase_case_00003_overflow_x_mul_by_n() { }
    private:
      virtual const std::string& name(void) const
      {
        static const std::string str("TestCase_case_00003_overflow_x_mul_by_n");
        return str;
      }
      virtual void mp_float_test(std::vector<mp_float>& data) const
      {
        data.clear();

        mp_float y = (std::numeric_limits<mp_float>::max)() / static_cast<boost::int32_t>(100);

        data.push_back(y);

        boost::int32_t k;

        for(k = static_cast<boost::int32_t>(0); k < kmax; k++)
        {
          y = y * static_cast<boost::int32_t>(3);

          data.push_back(y);

          if(boost::multiprecision::isinf(y)) { break; }
        }

        my_test_result = (k > static_cast<boost::int32_t>(1)) && (k < kmax);
      }
    };

    class TestCase_case_00004_underflow_x_div_by_n : public TestCaseOverflowUnderflowBase
    {
    public:
      TestCase_case_00004_underflow_x_div_by_n() { }
      virtual ~TestCase_case_00004_underflow_x_div_by_n() { }
    private:
      virtual const std::string& name(void) const
      {
        static const std::string str("TestCase_case_00004_underflow_x_div_by_n");
        return str;
      }
      virtual void mp_float_test(std::vector<mp_float>& data) const
      {
        data.clear();

        static const std::string str_tiny_exp = boost::lexical_cast<std::string>(std::numeric_limits<mp_float>::min_exponent10 + static_cast<boost::int64_t>(2));
        static const std::string str_tiny = "1e" + str_tiny_exp;

        mp_float y(str_tiny);

        data.push_back(y);

        boost::int32_t k;
        for(k = static_cast<boost::int32_t>(0); k < kmax; k++)
        {
          y = y / static_cast<boost::int32_t>(3);

          data.push_back(y);

          const bool is_zero_or_lt_min = (boost::multiprecision::iszero(y) || (y < (std::numeric_limits<mp_float>::min)()));

          if(is_zero_or_lt_min) { break; }
        }

        my_test_result = (k > static_cast<boost::int32_t>(1)) && (k < kmax);
      }
    };

    bool test_case_00001_overflow_mul_x (const bool b_write_output)
    {
      return TestCase_case_00001_overflow_mul_x().execute(b_write_output);
    }
    bool test_case_00002_underflow_mul_x(const bool b_write_output)
    {
      return TestCase_case_00002_underflow_mul_x().execute(b_write_output);
    }
    bool test_case_00003_overflow_x_mul_by_n(const bool b_write_output)
    {
      return TestCase_case_00003_overflow_x_mul_by_n().execute(b_write_output);
    }
    bool test_case_00004_underflow_x_div_by_n(const bool b_write_output)
    {
      return TestCase_case_00004_underflow_x_div_by_n().execute(b_write_output);
    }
  }
}
