//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_NTH_WEEK_HPP
#define BOOST_CHRONO_DATE_NTH_WEEK_HPP


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
     * The class nth_week is used to specify a small integral value that indicates the nth week of the year (example: last_week, 1st_week).
     */
    class nth_week
    {
    public:
      typedef int_least8_t rep;
      static const rep not_applicable=7;
      static const rep last_=6;
      static const rep first_=1;
      static const std::size_t size=last_-first_+1; // :5 bits

      /**
       * @Effects: Constructs an object of class @c nth_week by storing @c s.
       * Throws: if @c s is outside of the range [1, 6], throws an exception of type bad_date.
       */
      nth_week(rep s) : value_(s)
      {
        if (!is_valid())
        {
          throw bad_date("day " + boost::chrono::to_string(int(s)) + " is out of range");
        }
      }
      /**
       * @Effects: Constructs an object of class @c nth_week by storing @c s.
       * @Note This function doesn't check the parameters validity.
       * It is up to the user to provide a valid ones.
       */
      nth_week(rep s, no_check_t) BOOST_NOEXCEPT
          : value_(s)
      {
      }
      /**
       * @Return The nth week stored component.
       */
      operator rep() const BOOST_NOEXCEPT
      {
        return value_;
      }
      /**
       * @Return The nth stored component.
       */
      rep value() const BOOST_NOEXCEPT
      {
        return value_;
      }

      /**
       * @Return if the stored value is a valid one, i.e. in the range [1,6].
       */
      bool is_valid() const BOOST_NOEXCEPT
      {
        return (first_ <= value_ && value_ <= last_);
      }
      bool is_not_applicable() const BOOST_NOEXCEPT
      {
        return value_==not_applicable;
      }
    private:
      rep value_; // 3 bits if only valid up to _5th
    };

//    extern const nth_week last_week;
//    extern const nth_week _1st_week;
//    extern const nth_week _2nd_week;
//    extern const nth_week _3rd_week;
//    extern const nth_week _4th_week;
//    extern const nth_week _5th_week;


  } // chrono

} // boost

#endif  // header
