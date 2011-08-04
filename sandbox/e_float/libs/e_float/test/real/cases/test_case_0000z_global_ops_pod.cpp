
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <sstream>
#include <string>
#include <limits>
#include <iomanip>

#include <e_float/e_float.hpp>
#include <e_float/e_float_functions.hpp>
#include "../test_case_real.h"

namespace
{
  struct e_float_equate_to
  {
    static e_float the_value_min;
    static e_float the_value_max;

    template<typename STYPE>
    inline static bool check_stype(void)
    {
      the_value_min = std::numeric_limits<STYPE>::min();
      the_value_max = std::numeric_limits<STYPE>::max();

      std::stringstream ss;

      ss << static_cast<signed long long>(std::numeric_limits<STYPE>::min());
      std::string str_min = ss.str();

      ss.clear();
      ss.str("");

      ss << static_cast<signed long long>(std::numeric_limits<STYPE>::max());
      std::string str_max = ss.str();

      return ((the_value_min == e_float(str_min)) && (the_value_max == e_float(str_max)));
    }

    template<typename UTYPE>
    inline static bool check_utype(void)
    {
      the_value_max = std::numeric_limits<UTYPE>::max();

      std::stringstream ss;

      ss << static_cast<unsigned long long>(std::numeric_limits<UTYPE>::max());
      std::string str_max = ss.str();

      return (the_value_max == e_float(str_max));
    }
  };

  e_float e_float_equate_to::the_value_min;
  e_float e_float_equate_to::the_value_max;
}

namespace test
{
  namespace real
  {
    class TestCaseGlobalOpsPodBase : public TestCaseReal
    {
    protected:

      mutable bool my_test_result;

      TestCaseGlobalOpsPodBase() : my_test_result(false) { }

    private:

      virtual const std::vector<e_float>& control_data(void) const
      {
        static const std::vector<e_float> dummy(1u, ef::one());
        return dummy;
      }

    public:

      virtual ~TestCaseGlobalOpsPodBase() { }

      virtual bool execute(const bool b_write_output) const
      {
        std::cout << name() << " : ";

        std::vector<e_float> e_float_data;

        // Calculate the e_float test data.
        e_float_test(e_float_data);

        // Optionally write the e_float test data to an output file.
        if(b_write_output)
        {
          if(!write_output_file(e_float_data))
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

    class TestCase_case_00009_global_ops_pod_equate : public TestCaseGlobalOpsPodBase
    {
    public:
      TestCase_case_00009_global_ops_pod_equate() { }
      virtual ~TestCase_case_00009_global_ops_pod_equate() { }
    private:
      virtual const std::string& name(void) const
      {
        static const std::string str("TestCase_case_00009_global_ops_pod_equate");
        return str;
      }
      virtual void e_float_test(std::vector<e_float>& data) const
      {
        data.clear();

        my_test_result = true;

        my_test_result &= ::e_float_equate_to::check_utype<char>();
        my_test_result &= ::e_float_equate_to::check_stype<signed char>();
        my_test_result &= ::e_float_equate_to::check_utype<unsigned char>();
        my_test_result &= ::e_float_equate_to::check_utype<wchar_t>();
        my_test_result &= ::e_float_equate_to::check_stype<signed short>();
        my_test_result &= ::e_float_equate_to::check_utype<unsigned short>();
        my_test_result &= ::e_float_equate_to::check_stype<signed int>();
        my_test_result &= ::e_float_equate_to::check_utype<unsigned int>();
        my_test_result &= ::e_float_equate_to::check_stype<signed long>();
        my_test_result &= ::e_float_equate_to::check_utype<unsigned long>();
        my_test_result &= ::e_float_equate_to::check_stype<signed long long>();
        my_test_result &= ::e_float_equate_to::check_utype<unsigned long long>();

        e_float x(123u);

        x = static_cast<float>(4.0f);       my_test_result &= (x == e_float(4u));
        x = static_cast<double>(4.0);       my_test_result &= (x == e_float(4u));
        x = static_cast<long double>(4.0f); my_test_result &= (x == e_float(4u));
      }
    };

    class TestCase_case_00010_global_ops_pod_operations : public TestCaseGlobalOpsPodBase
    {
    public:
      TestCase_case_00010_global_ops_pod_operations() { }
      virtual ~TestCase_case_00010_global_ops_pod_operations() { }
    private:
      virtual const std::string& name(void) const
      {
        static const std::string str("TestCase_case_00010_global_ops_pod_operations");
        return str;
      }
      virtual void e_float_test(std::vector<e_float>& data) const
      {
        data.clear();

        my_test_result = true;

        my_test_result &= (ef::four() == static_cast<float>(4.0f));
        my_test_result &= (ef::four() == static_cast<double>(4.0));
        my_test_result &= (ef::four() == static_cast<long double>(4.0));

        my_test_result &= (ef::pi() > static_cast<float>(3.14f));
        my_test_result &= (ef::pi() > static_cast<double>(3.14));
        my_test_result &= (ef::pi() > static_cast<long double>(3.14));

        my_test_result &= (static_cast<float>      (0.5f) < ef::euler_gamma());
        my_test_result &= (static_cast<double>     (0.5)  < ef::euler_gamma());
        my_test_result &= (static_cast<long double>(0.5)  < ef::euler_gamma());

        my_test_result &= (e_float(static_cast<char>('1')) == static_cast<char>(0x31));
        my_test_result &= (e_float(static_cast<char>('2')) >  static_cast<char>('1'));
        my_test_result &= (e_float(static_cast<char>('1')) <  static_cast<char>('2'));
        my_test_result &= (e_float(static_cast<char>('2')) <= static_cast<char>('2'));
        my_test_result &= (e_float(static_cast<char>('2')) >= static_cast<char>('2'));

        my_test_result &= (e_float("1e1000") > std::numeric_limits<unsigned long long>::max());
        my_test_result &= (ef::zero() == 0);
        my_test_result &= (std::numeric_limits<e_float>::epsilon() > 0);

        my_test_result &= ((ef::one() * 4.0) == 4);
        my_test_result &= ((4.0 * ef::one()) == 4);
      }
    };

    bool test_case_00009_global_ops_pod_equate(const bool b_write_output)
    {
      return TestCase_case_00009_global_ops_pod_equate().execute(b_write_output);
    }
    bool test_case_00010_global_ops_pod_operations(const bool b_write_output)
    {
      return TestCase_case_00010_global_ops_pod_operations().execute(b_write_output);
    }
  }
}
