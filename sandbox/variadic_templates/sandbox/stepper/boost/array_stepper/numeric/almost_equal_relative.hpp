#ifndef BOOST_ARRAY_STEPPER_NUMERIC_ALMOST_EQUAL_RELATIVE_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_NUMERIC_ALMOST_EQUAL_RELATIVE_HPP_INCLUDED
#include <limits>
#define TRACE_ALMOST_EQUAL_RELATIVE
#ifdef TRACE_ALMOST_EQUAL_RELATIVE
#include <iostream>
#endif
namespace boost
{
namespace array_stepper
{
namespace numeric
{
        template
        < typename Value
        >
        bool
      almost_equal_relative
        ( Value value_a
        , Value value_b
        , Value eps_factor=Value(30.0)
        )
       /**@brief
        *  Are value_a and value_b almost equal?
        */
        //Reference:
        //  http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
        //
        {
            Value const eps_val=eps_factor*std::numeric_limits<Value>::epsilon();
            Value const max_error=eps_factor*eps_val;
            Value const abs_diff=std::abs(value_a - value_b);
            bool const abs_lt_max=abs_diff < max_error;
            if (abs_lt_max)
                return true;
            Value abs_a=std::abs(value_a);
            Value abs_b=std::abs(value_b);
            Value abs_max=std::max(abs_a,abs_b);
            Value rel_error=abs_diff / abs_max;
            bool rel_lt_max=rel_error < max_error;
            if (rel_lt_max)
                return true;
          #ifdef TRACE_ALMOST_EQUAL_RELATIVE
            std::cout
              <<"almost_equal_relative:"
              <<"\n:value_a="<<value_a
              <<"\n:value_b="<<value_b
              <<"\n:eps_factor="<<eps_factor
              <<"\n:eps_val="<<eps_val
              <<"\n:max_error="<<max_error
              <<"\n:abs_diff="<<abs_diff
              <<"\n:rel_error="<<rel_error
              <<"\n";
          #endif
            return false;
        }
}//exit numeric namespace
}//exit array_stepper namespace
}//exit boost namespace
#endif
