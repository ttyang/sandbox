
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

    template<typename TYPE, typename CAST_TYPE>
    inline static bool check_type(void)
    {
      the_value_min = (std::numeric_limits<TYPE>::min)();
      the_value_max = (std::numeric_limits<TYPE>::max)();

      std::stringstream ss;

      ss << static_cast<CAST_TYPE>((std::numeric_limits<TYPE>::min)());
      std::string str_min = ss.str();

      ss.clear();
      ss.str("");

      ss << static_cast<CAST_TYPE>((std::numeric_limits<TYPE>::max)());
      std::string str_max = ss.str();

      return ((the_value_min == e_float(str_min)) && (the_value_max == e_float(str_max)));
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

        my_test_result &= (std::numeric_limits<char>::is_signed ? ::e_float_equate_to::check_type<char, signed long long>()
                                                                : ::e_float_equate_to::check_type<char, unsigned long long>());
        my_test_result &= (std::numeric_limits<wchar_t>::is_signed ? ::e_float_equate_to::check_type<wchar_t, signed long long>()
                                                                   : ::e_float_equate_to::check_type<wchar_t, unsigned long long>());

        my_test_result &= ::e_float_equate_to::check_type<signed char, signed long long>();
        my_test_result &= ::e_float_equate_to::check_type<signed short, signed long long>();
        my_test_result &= ::e_float_equate_to::check_type<signed int, signed long long>();
        my_test_result &= ::e_float_equate_to::check_type<signed long, signed long long>();
        my_test_result &= ::e_float_equate_to::check_type<signed long long, signed long long>();

        my_test_result &= ::e_float_equate_to::check_type<unsigned char, unsigned long long>();
        my_test_result &= ::e_float_equate_to::check_type<unsigned short, unsigned long long>();
        my_test_result &= ::e_float_equate_to::check_type<unsigned int, unsigned long long>();
        my_test_result &= ::e_float_equate_to::check_type<unsigned long, unsigned long long>();
        my_test_result &= ::e_float_equate_to::check_type<unsigned long long, unsigned long long>();

        e_float x(123u); // Initialize x with something.

        // Reassign x to some floating-point POD values and check some equalities.
        x = static_cast<float>(4.0f);      my_test_result &= (x == e_float(4u));
        x = static_cast<double>(4.0);      my_test_result &= (x == e_float(4u));
        x = static_cast<long double>(4.0); my_test_result &= (x == e_float(4u));

        my_test_result &= (e_float(0.0f) == ef::zero());
        my_test_result &= (e_float(0.0)  == ef::zero());
        my_test_result &= (e_float(static_cast<long double>(0.0))  == ef::zero());
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

        my_test_result &= (+ef::four() == static_cast<float>(+4.0f));
        my_test_result &= (-ef::four() == static_cast<float>(-4.0f));
        my_test_result &= (+ef::four() == static_cast<double>(+4.0));
        my_test_result &= (-ef::four() == static_cast<double>(-4.0));
        my_test_result &= (+ef::four() == static_cast<long double>(+4.0));
        my_test_result &= (-ef::four() == static_cast<long double>(-4.0));

        my_test_result &= (e_float(11.1f) == e_float("11.1000003814697265625"));
        my_test_result &= (e_float(11.1) == e_float("11.0999999999999996447286321199499070644378662109375"));

        my_test_result &= (+ef::pi() > static_cast<float>(+3.14f));
        my_test_result &= (-ef::pi() < static_cast<float>(-3.14f));
        my_test_result &= (+ef::pi() > static_cast<double>(+3.14));
        my_test_result &= (-ef::pi() < static_cast<double>(-3.14));
        my_test_result &= (+ef::pi() > static_cast<long double>(+3.14));
        my_test_result &= (-ef::pi() < static_cast<long double>(-3.14));

        my_test_result &= (static_cast<float>      (0.5f) < ef::euler_gamma());
        my_test_result &= (static_cast<double>     (0.5)  < ef::euler_gamma());
        my_test_result &= (static_cast<long double>(0.5)  < ef::euler_gamma());

        my_test_result &= (e_float(static_cast<char>('1')) == static_cast<char>(0x31));
        my_test_result &= (e_float(static_cast<char>('2')) >  static_cast<char>('1'));
        my_test_result &= (e_float(static_cast<char>('1')) <  static_cast<char>('2'));
        my_test_result &= (e_float(static_cast<char>('2')) <= static_cast<char>('2'));
        my_test_result &= (e_float(static_cast<char>('2')) >= static_cast<char>('2'));
        my_test_result &= (3.14 != ef::pi());

        my_test_result &= (e_float("1e1000") > (std::numeric_limits<unsigned long long>::max)());
        my_test_result &= (ef::zero() == 0);
        my_test_result &= (std::numeric_limits<e_float>::epsilon() > 0);

        my_test_result &= ((ef::one() * 4.0) == 4);
        my_test_result &= ((4.0 * ef::one()) == 4);

        const e_float huge("1e12345678");
        const e_float tiny("1e-12345678");

        float f = huge;
        double d = huge;
        long double ld = huge;

        my_test_result &= (f == std::numeric_limits<float>::infinity());
        my_test_result &= (d == std::numeric_limits<double>::infinity());
        my_test_result &= (ld == std::numeric_limits<long double>::infinity());

        f = tiny;
        d = tiny;
        ld = tiny;

        my_test_result &= (f == 0.0f);
        my_test_result &= (d == 0.0);
        my_test_result &= (ld == static_cast<long double>(0.0));
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
