//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_WEEKDAY_HPP
#define BOOST_CHRONO_DATE_WEEKDAY_HPP


#include <boost/cstdint.hpp>
#include <boost/chrono/date/detail/bounded.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * weekday tag
     */
    struct weekday_tag {};
    /**
     * The class weekday is used to specify a day of the week.
     */
    class weekday: public bounded<weekday_tag, 0, 6, int_least8_t>
    {
      typedef bounded<weekday_tag, 0, 6, int_least8_t> base_type;

    public:
      BOOST_STATIC_CONSTEXPR rep not_applicable=7;

      /**
       * @Effects Constructs an object of class weekday by storing v.
       * @Postconditions static_cast<int>(*this) == v
       * @Throws if v is outside of the range [0, 6], throws an exception of type bad_date.
       */
      BOOST_CONSTEXPR weekday(int s, check_t) : base_type(s, check)
      {}
      /**
       * @Effects Constructs an object of class weekday by storing v.
       * @Postconditions static_cast<int>(*this) == v
       */
      BOOST_CONSTEXPR weekday(int s) BOOST_NOEXCEPT
          : base_type(s)
      {}

      BOOST_CONSTEXPR bool is_not_applicable() const BOOST_NOEXCEPT
      {
        return value()==not_applicable;
      }
    };

    /**
     * weekday pseudo-literals.
     *
     * These const weekday objects are constructed prior to first use with the following values:
     *
     * const weekday sun(0);
     * const weekday mon(1);
     * const weekday tue(2);
     * const weekday wed(3);
     * const weekday thu(4);
     * const weekday fri(5);
     * const weekday sat(6);
     *
     */
#ifndef  BOOST_NO_CXX11_CONSTEXPR
    BOOST_CONSTEXPR_OR_CONST weekday
      sun(0)
    , mon(1)
    , tue(2)
    , wed(3)
    , thu(4)
    , fri(5)
    , sat(6)
    ;
#else
    extern const weekday sun;
    extern const weekday mon;
    extern const weekday tue;
    extern const weekday wed;
    extern const weekday thu;
    extern const weekday fri;
    extern const weekday sat;
#endif
    /**
     * Overload for string vonversion.
     * @param v the weekday
     * @return the string representation.
     */
    inline std::string to_string(weekday v) {
      switch (v) {
      case 0: return "Sun";
      case 1: return "Mon";
      case 2: return "Tue";
      case 3: return "Wed";
      case 4: return "Thu";
      case 5: return "Fri";
      case 6: return "Sat";
      default: throw_exception( bad_date("week day " + boost::chrono::to_string(unsigned(v.value())) + " is out of range") );

      }
    }

  } // chrono

} // boost

#endif  // header
