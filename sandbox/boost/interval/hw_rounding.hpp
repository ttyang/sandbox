#ifndef BOOST_INTERVAL_HW_ROUNDING_HPP
#define BOOST_INTERVAL_HW_ROUNDING_HPP

#include <boost/interval/rounding.hpp>
#include <boost/interval/rounded_arith.hpp>

// define appropriate specialization of rounding_control for built-in types
#if defined(__i386__) || defined(__BORLANDC__) || defined(BOOST_MSVC)
#  include <boost/interval/detail/x86_rounding_control.hpp>
#elif defined(powerpc) || defined(__powerpc__) || defined(__ppc__)
#  include <boost/interval/detail/ppc_rounding_control.hpp>
#elif defined(sparc) || defined(__sparc__)
#  include <boost/interval/detail/sparc_rounding_control.hpp>
#elif defined(__USE_ISOC99)
#  include <boost/interval/detail/c99_rounding_control.hpp>
#else
#  error Boost::interval: Please specify rounding control mechanism.
#endif

namespace boost {
  namespace interval_lib {

  /*
   * Three specializations of rounded_math<T>
   */

template<>
struct rounded_math<float>
  : save_state<rounded_arith_opp<float> >
{};

template<>
struct rounded_math<double>
  : save_state<rounded_arith_opp<double> >
{};

template<>
struct rounded_math<long double>
  : save_state<rounded_arith_opp<long double> >
{};

  } // namespace interval_lib
} // namespace boost

#endif // BOOST_INTERVAL_HW_ROUNDING_HPP
