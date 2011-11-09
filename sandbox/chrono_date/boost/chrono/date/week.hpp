//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_DATE_WEEK_HPP
#define BOOST_CHRONO_DATE_DATE_WEEK_HPP


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
     * The class week is used to specify the week of the year.
     */
    class week
    {
    public:
      typedef int_least8_t rep;
      static const rep last_=53;
      static const rep first_=1;
      static const std::size_t size=last_-first_+1; // :6 bits

      /**
       * @Effects Constructs an object of class week by storing v.
       * @Postconditions static_cast<rep>(*this) == v
       * @Throws if v is outside of the range [1, 53], throws an exception of type bad_date.
       */
      explicit week(rep v)
      : value_(v)
      {
        if (!is_valid())
        {
          throw bad_date("week day " + boost::chrono::to_string(v) + " is out of range");
        }
      }
      /**
       * @Effects Constructs an object of class week by storing v.
       * @Postconditions static_cast<rep>(*this) == v
       */
      week(rep v,no_check_t) BOOST_NOEXCEPT
      : value_(v)
      {}

      /**
       * @return true if the v stored value is in the range [1, 53],
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
      static BOOST_CONSTEXPR week min BOOST_PREVENT_MACRO_SUBSTITUTION ()
      {
          return week(first_,no_check);
      }
      static BOOST_CONSTEXPR week max BOOST_PREVENT_MACRO_SUBSTITUTION ()
      {
          return week(last_,no_check);
      }
    private:
      rep value_;
    };

    extern const week
         w_01, w_02, w_03, w_04, w_05, w_06, w_07, w_08, w_09,
         w_10, w_11, w_12, w_13, w_14, w_15, w_16, w_17, w_18, w_19,
         w_20, w_21, w_22, w_23, w_24, w_25, w_26, w_27, w_28, w_29,
         w_30, w_31, w_32, w_33, w_34, w_35, w_36, w_37, w_38, wv9,
         w_40, w_41, w_42, w_43, w_44, w_45, wv6, w_47, w_48, w_49,
         w_50, w_51, w_52, w_53;

  } // chrono

} // boost

#endif  // header
