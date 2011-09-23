
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

#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/multiprecision/mp_float.hpp>
#include <boost/multiprecision/mp_float_functions.hpp>
#include "../test_case_real.h"

using boost::multiprecision::mp_float;

namespace
{
  struct mp_float_equate_to
  {
    static mp_float the_value_min;
    static mp_float the_value_max;

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

      return ((the_value_min == mp_float(str_min)) && (the_value_max == mp_float(str_max)));
    }
  };

  mp_float mp_float_equate_to::the_value_min;
  mp_float mp_float_equate_to::the_value_max;
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
      virtual const std::vector<mp_float>& control_data(void) const
      {
        static const std::vector<mp_float> dummy(1u, boost::multiprecision::one());
        return dummy;
      }

    public:
      virtual ~TestCaseGlobalOpsPodBase() { }

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
      virtual void mp_float_test(std::vector<mp_float>& data) const
      {
        data.clear();

        my_test_result = true;

        my_test_result &= (std::numeric_limits<char>::is_signed ? ::mp_float_equate_to::check_type<char, signed long long>()
                                                                : ::mp_float_equate_to::check_type<char, unsigned long long>());
        my_test_result &= (std::numeric_limits<wchar_t>::is_signed ? ::mp_float_equate_to::check_type<wchar_t, signed long long>()
                                                                   : ::mp_float_equate_to::check_type<wchar_t, unsigned long long>());

        my_test_result &= ::mp_float_equate_to::check_type<signed char, signed long long>();
        my_test_result &= ::mp_float_equate_to::check_type<signed short, signed long long>();
        my_test_result &= ::mp_float_equate_to::check_type<int, signed long long>();
        my_test_result &= ::mp_float_equate_to::check_type<signed long, signed long long>();
        my_test_result &= ::mp_float_equate_to::check_type<signed long long, signed long long>();

        my_test_result &= ::mp_float_equate_to::check_type<unsigned char, unsigned long long>();
        my_test_result &= ::mp_float_equate_to::check_type<unsigned short, unsigned long long>();
        my_test_result &= ::mp_float_equate_to::check_type<unsigned int, unsigned long long>();
        my_test_result &= ::mp_float_equate_to::check_type<unsigned long, unsigned long long>();
        my_test_result &= ::mp_float_equate_to::check_type<unsigned long long, unsigned long long>();

        mp_float x(123u); // Initialize x with something.

        // Reassign x to some floating-point POD values and check some equalities.
        x = static_cast<float>(4.0f);      my_test_result &= (x == mp_float(4u));
        x = static_cast<double>(4.0);      my_test_result &= (x == mp_float(4u));
        x = static_cast<long double>(4.0); my_test_result &= (x == mp_float(4u));

        my_test_result &= (mp_float(0.0f) == boost::multiprecision::zero());
        my_test_result &= (mp_float(0.0)  == boost::multiprecision::zero());
        my_test_result &= (mp_float(static_cast<long double>(0.0))  == boost::multiprecision::zero());
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
      virtual void mp_float_test(std::vector<mp_float>& data) const
      {
        data.clear();

        my_test_result = true;

        my_test_result &= (+boost::multiprecision::four() == static_cast<float>(+4.0f));
        my_test_result &= (-boost::multiprecision::four() == static_cast<float>(-4.0f));
        my_test_result &= (+boost::multiprecision::four() == static_cast<double>(+4.0));
        my_test_result &= (-boost::multiprecision::four() == static_cast<double>(-4.0));
        my_test_result &= (+boost::multiprecision::four() == static_cast<long double>(+4.0));
        my_test_result &= (-boost::multiprecision::four() == static_cast<long double>(-4.0));

        my_test_result &= (mp_float(11.1f) == mp_float("11.1000003814697265625"));
        my_test_result &= (mp_float(11.1) == mp_float("11.0999999999999996447286321199499070644378662109375"));

        my_test_result &= (+boost::multiprecision::pi() > static_cast<float>(+3.14f));
        my_test_result &= (-boost::multiprecision::pi() < static_cast<float>(-3.14f));
        my_test_result &= (+boost::multiprecision::pi() > static_cast<double>(+3.14));
        my_test_result &= (-boost::multiprecision::pi() < static_cast<double>(-3.14));
        my_test_result &= (+boost::multiprecision::pi() > static_cast<long double>(+3.14));
        my_test_result &= (-boost::multiprecision::pi() < static_cast<long double>(-3.14));

        my_test_result &= (static_cast<float>      (0.5f) < boost::multiprecision::euler_gamma());
        my_test_result &= (static_cast<double>     (0.5)  < boost::multiprecision::euler_gamma());
        my_test_result &= (static_cast<long double>(0.5)  < boost::multiprecision::euler_gamma());

        my_test_result &= (mp_float(static_cast<char>('1')) == static_cast<char>(0x31));
        my_test_result &= (mp_float(static_cast<char>('2')) >  static_cast<char>('1'));
        my_test_result &= (mp_float(static_cast<char>('1')) <  static_cast<char>('2'));
        my_test_result &= (mp_float(static_cast<char>('2')) <= static_cast<char>('2'));
        my_test_result &= (mp_float(static_cast<char>('2')) >= static_cast<char>('2'));
        my_test_result &= (3.14 != boost::multiprecision::pi());

        my_test_result &= (mp_float("1e1000") > (std::numeric_limits<unsigned long long>::max)());
        my_test_result &= (boost::multiprecision::zero() == 0);
        my_test_result &= (std::numeric_limits<mp_float>::epsilon() > 0);

        my_test_result &= ((boost::multiprecision::one() * 4.0) == 4);
        my_test_result &= ((4.0 * boost::multiprecision::one()) == 4);

        my_test_result &= (std::numeric_limits<mp_float>::quiet_NaN() != 0);
        my_test_result &= (std::numeric_limits<mp_float>::quiet_NaN() != boost::multiprecision::one());
        my_test_result &= (std::numeric_limits<mp_float>::quiet_NaN() != std::numeric_limits<mp_float>::quiet_NaN());

        static const mp_float huge("1e12345678");
        static const mp_float tiny("1e-12345678");

        my_test_result &= (huge < +std::numeric_limits<mp_float>::infinity());
        my_test_result &= (tiny > -std::numeric_limits<mp_float>::infinity());
        my_test_result &= (+std::numeric_limits<mp_float>::infinity() == (+1 / boost::multiprecision::zero()));
        my_test_result &= (-std::numeric_limits<mp_float>::infinity() == (-1 / boost::multiprecision::zero()));
        my_test_result &= (-std::numeric_limits<mp_float>::infinity() != +std::numeric_limits<mp_float>::infinity());
        my_test_result &= (+std::numeric_limits<mp_float>::infinity() >  -std::numeric_limits<mp_float>::infinity());
        my_test_result &= (-std::numeric_limits<mp_float>::infinity() <  +std::numeric_limits<mp_float>::infinity());

        float f = huge;
        double d = huge;
        long double ld = huge;

        my_test_result &= (f == std::numeric_limits<float>::infinity());
        my_test_result &= (d == std::numeric_limits<double>::infinity());
//        TBD: Why does this not work for GCC on cygwin with unusual 10-byte long double?
//        my_test_result &= (ld == std::numeric_limits<long double>::infinity());

        f = tiny;
        d = tiny;
        ld = tiny;

        my_test_result &= (f == 0.0f);
        my_test_result &= (d == 0.0);
        my_test_result &= (ld == static_cast<long double>(0.0));

        static const mp_float min_value("1e" + boost::lexical_cast<std::string>(std::numeric_limits<mp_float>::min_exponent10));

        my_test_result &= ((std::numeric_limits<mp_float>::min)() == min_value);
        my_test_result &= ((std::numeric_limits<mp_float>::min)() != 0);
        my_test_result &= ((std::numeric_limits<mp_float>::min)() != boost::multiprecision::zero());
        my_test_result &= (0 != (std::numeric_limits<mp_float>::min)());
        my_test_result &= (boost::multiprecision::zero() != (std::numeric_limits<mp_float>::min)());
        my_test_result &= (0 < +(std::numeric_limits<mp_float>::min)());
        my_test_result &= (0 > -(std::numeric_limits<mp_float>::min)());

        static const mp_float a_little_more_than_min_value("1e" + boost::lexical_cast<std::string>(std::numeric_limits<mp_float>::min_exponent10 + static_cast<boost::int64_t>(1)));

        my_test_result &= (a_little_more_than_min_value != 0);
        my_test_result &= (a_little_more_than_min_value > (std::numeric_limits<mp_float>::min)());
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
