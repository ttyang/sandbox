//  date
//
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_DATE_DAY_OF_YEAR_HPP
#define BOOST_CHRONO_DATE_DATE_DAY_OF_YEAR_HPP


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
     * The class day_of_year is used to specify the day of the year when constructing a date.
     */
    class day_of_year
    {
    public:
      typedef int_least16_t rep;
      static const rep last_=366;
      static const rep first_=1;
      static const std::size_t size=last_-first_+1; // :9 bits

      /**
       * @Effects: Constructs an object of class @c day_of_year by storing @c d.
       * @Postconditions: <c>value() == d && is_valid()</c>.
       * @Throws: if @c d is outside of the range [1, 366], throws an exception of type @c bad_date.
       */
      explicit day_of_year(rep d)
          : value_(d)
          {
            if (!is_valid())
            {
              throw bad_date("day_of_year " + boost::chrono::to_string(d) + " is out of range");
            }
          }
      /**
       * @Effects: Constructs an object of class @c day_of_year by storing @c d.
       * @Postconditions: <c>value() == d</c>.
       * @Note This function doesn't check the parameters validity.
       * It is up to the user to provide a valid ones.
       */
      day_of_year(rep d,no_check_t) BOOST_NOEXCEPT
      : value_(d)
      {}
      /**
       * @Return if the stored value is a valid one, i.e. in the range [1,366].
       */
      bool is_valid() const BOOST_NOEXCEPT
      {
        return (first_ <= value_ && value_ <= last_);
      }
      /**
       * @Returns: the underlying value of that day of year.
       */
      operator rep() const BOOST_NOEXCEPT
      {
        return value_;
      }
      /**
       * @Returns: the underlying value of that day of year.
       */
      rep value() const BOOST_NOEXCEPT
      {
        return value_;
      }
      /**
       * @Returns: the min valid value for a day of a year.
       */
      static BOOST_CONSTEXPR day_of_year min BOOST_PREVENT_MACRO_SUBSTITUTION ()
      {
          return day_of_year(first_,no_check);
      }
      /**
       * @Returns: the first day of a month.
       */
      static BOOST_CONSTEXPR day_of_year first()
      {
          return day_of_year(first_,no_check);
      }
      /**
       * @Returns: the max valid value for a day of a year.
       */
      static BOOST_CONSTEXPR day_of_year max BOOST_PREVENT_MACRO_SUBSTITUTION ()
      {
        return day_of_year(last_,no_check);
      }
    private:
      rep value_;
    };

  } // chrono

} // boost

#endif  // header
