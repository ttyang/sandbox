//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_DATE_WEEKDAY_HPP
#define BOOST_CHRONO_DATE_DATE_WEEKDAY_HPP


#include <boost/cstdint.hpp>
#include <boost/chrono/config.hpp>
#include <boost/chrono/date/no_check.hpp>
#include <boost/chrono/date/exceptions.hpp>
#include <boost/chrono/date/detail/to_string.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * The class weekday is used to specify a day of the week.
     */
    class weekday
    {
    public:
      typedef int_least8_t rep;

      static const rep last_=6;
      static const rep first_=0;
      static const int_least8_t size=last_-first_+1; //:3 bits
      static const rep not_applicable=7;

      /**
       * @Effects Constructs an object of class weekday by storing v.
       * @Postconditions static_cast<rep>(*this) == v
       * @Throws if v is outside of the range [0, 6], throws an exception of type bad_date.
       */
      explicit weekday(rep v)
      : value_(v)
      {
        if (!is_valid())
        {
          throw bad_date("week day " + boost::chrono::to_string(v) + " is out of range");
        }
      }
      /**
       * @Effects Constructs an object of class weekday by storing v.
       * @Postconditions static_cast<rep>(*this) == v
       */
      explicit weekday(rep wd, no_check_t) BOOST_NOEXCEPT
      :value_(wd)
      {
      };

      /**
       * @Returns: the value of the stored int.
       */
      operator rep() const BOOST_NOEXCEPT
      {
        return value_;
      }
      /**
       * @Returns: the value of the stored int.
       */
      rep value() const BOOST_NOEXCEPT
      {
        return value_;
      }

      /**
       * @Return if the stored value is a valid one.
       */
      bool is_valid() const BOOST_NOEXCEPT
      {
        return (first_ <= value_ && value_ <= last_);
      }


      weekday next() const BOOST_NOEXCEPT
      {
        return weekday(((value_+1)%size),no_check);
      }
      weekday prev() BOOST_NOEXCEPT
      {
        return weekday((value_+size-1)%size,no_check);
      }

      /**
       * @Returns: the first day of the week.
       */
      static BOOST_CONSTEXPR weekday first()
      {
          return weekday(first_,no_check);
      }
      /**
       * @Returns: the last day of the week.
       */
      static BOOST_CONSTEXPR weekday last()
      {
          return weekday(last_,no_check);
      }
      static BOOST_CONSTEXPR weekday min BOOST_PREVENT_MACRO_SUBSTITUTION ()
      {
          return weekday(first_,no_check);
      }
      static BOOST_CONSTEXPR weekday max BOOST_PREVENT_MACRO_SUBSTITUTION ()
      {
          return weekday(last_,no_check);
      }
    private:
      rep value_;
    };

    /**
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
    extern const weekday sun;
    extern const weekday mon;
    extern const weekday tue;
    extern const weekday wed;
    extern const weekday thu;
    extern const weekday fri;
    extern const weekday sat;

    inline std::string to_string(weekday v) {
      switch (v) {
      case 0: return "Sun";
      case 1: return "Mon";
      case 2: return "Tue";
      case 3: return "Wed";
      case 4: return "Thu";
      case 5: return "Fri";
      case 6: return "Sat";
      default: throw bad_date("week day " + boost::chrono::to_string(v) + " is out of range");

      }
    }

  } // chrono

} // boost

#endif  // header
