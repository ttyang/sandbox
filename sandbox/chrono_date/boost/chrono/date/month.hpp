//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_MONTH_HPP
#define BOOST_CHRONO_DATE_MONTH_HPP

#include <boost/cstdint.hpp>
#include <boost/chrono/date/detail/bounded.hpp>


namespace boost
{
  namespace chrono
  {

    /**
     * month tag
     */
    struct month_tag {};
    /**
     * The class @c month is used to specify the month of the year when constructing a date.  Its range is [1,12].
     */
    typedef bounded<month_tag, 1, 12, int_least8_t> month;

    /**
     * month pseudo-literals.
     */
#ifndef  BOOST_NO_CXX11_CONSTEXPR
    BOOST_CONSTEXPR_OR_CONST month jan(1, no_check);
    BOOST_CONSTEXPR_OR_CONST month feb(2, no_check);
    BOOST_CONSTEXPR_OR_CONST month mar(3, no_check);
    BOOST_CONSTEXPR_OR_CONST month apr(4, no_check);
    BOOST_CONSTEXPR_OR_CONST month may(5, no_check);
    BOOST_CONSTEXPR_OR_CONST month jun(6, no_check);
    BOOST_CONSTEXPR_OR_CONST month jul(7, no_check);
    BOOST_CONSTEXPR_OR_CONST month aug(8, no_check);
    BOOST_CONSTEXPR_OR_CONST month sep(9, no_check);
    BOOST_CONSTEXPR_OR_CONST month oct(10, no_check);
    BOOST_CONSTEXPR_OR_CONST month nov(11, no_check);
    BOOST_CONSTEXPR_OR_CONST month dec(12, no_check);
#else
    extern const month jan;
    extern const month feb;
    extern const month mar;
    extern const month apr;
    extern const month may;
    extern const month jun;
    extern const month jul;
    extern const month aug;
    extern const month sep;
    extern const month oct;
    extern const month nov;
    extern const month dec;

#endif

    /**
     * Overload for month conversion to string.
     * @param v the @c month
     * @return the string representing the month.
     */
    inline std::string to_string(month v) {
      switch (v) {
      case 1: return "Jan";
      case 2: return "Feb";
      case 3: return "Mar";
      case 4: return "Apr";
      case 5: return "May";
      case 6: return "Jun";
      case 7: return "Jul";
      case 8: return "Aug";
      case 9: return "Sep";
      case 10: return "Oct";
      case 11: return "Nov";
      case 12: return "Dec";
      default: throw_exception( bad_date("month " + boost::chrono::to_string(unsigned(v.value())) + " is out of range") );

      }
    }

  } // chrono

} // boost

#endif  // header
