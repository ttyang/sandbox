//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_DATE_MONTH_HPP
#define BOOST_CHRONO_DATE_DATE_MONTH_HPP

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
     * The class @c month is used to specify the month of the year when constructing a date.
     */
    class month
    {
    public:
      typedef int_least8_t rep;
      static const rep last_ = 12;
      static const rep first_ = 1;
      static const std::size_t size = last_ - first_ + 1; // 4 bits

      /**
       * @Effects: Constructs an object of class @c month by storing @c m.
       * @Postconditions: <c>value() == m && is_valid()</c>.
       * @Throws: if @c m is outside of the range [1, 12], throws an exception of type @c bad_date.
       */
      BOOST_CONSTEXPR explicit month(rep v) :
        value_(v)
      {
        if (!(is_valid()))
        {
          throw bad_date("month " + boost::chrono::to_string(int(v))
              + " is out of range");
        }
      }
      /**
       * @Effects: Constructs an object of class @c month by storing @c m.
       * @Postconditions: value() == m.
       * @Note This function doesn't check the parameters validity.
       * It is up to the user to provide a valid ones.
       */
      explicit month(rep m, no_check_t) :
        value_(m)
      {
      }

      /**
       * @Return if the stored value is a valid one, i.e. on the range [1, 12].
       */
      bool is_valid() const BOOST_NOEXCEPT
      {
        return (first_ <= value_ && value_ <= last_);
      }

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
      month next() const BOOST_NOEXCEPT
      {
        return month(((value_-first_+1)%size)+first_,no_check);
      }
      month prev()BOOST_NOEXCEPT
      {
        return month(((value_-first_+size-1)%size)+first_,no_check);
      }
      static BOOST_CONSTEXPR month first()
      {
        return month(first_,no_check);
      }
      static BOOST_CONSTEXPR month last()
      {
        return month(last_,no_check);
      }
      static BOOST_CONSTEXPR month min BOOST_PREVENT_MACRO_SUBSTITUTION ()
      {
        return month(first_,no_check);
      }
      static BOOST_CONSTEXPR month max BOOST_PREVENT_MACRO_SUBSTITUTION ()
      {
        return month(last_,no_check);
      }

      //      friend class date;
      //      friend class rel_date;
    private:
      rep value_;

    };

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
      default: throw bad_date("month " + boost::chrono::to_string(int(v)) + " is out of range");

      }
    }

  } // chrono

} // boost

#endif  // header
