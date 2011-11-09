//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_NTH_HPP
#define BOOST_CHRONO_DATE_NTH_HPP

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
     * The class nth is used to specify a small integral value that indicates the nth day of the month (example: last, 1st).
     */
    class nth
    {
    public:
      typedef int_least8_t rep;
      static const rep not_applicable=7;
      //static const rep not_applicable=-32;
      static const rep last_=31;
      static const rep first_=-32;
      //static const rep last_=6;
      //static const rep first_=1;
      static const std::size_t size=last_-first_+1; // :3 bits

      nth(rep s) BOOST_NOEXCEPT
          : value_(s)
      {
        if (!is_valid())
        {
          throw bad_date("day " + boost::chrono::to_string(int(s)) + " is out of range");
        }
      }
      nth(rep s, no_check_t) BOOST_NOEXCEPT
          : value_(s)
      {
      }

      /**
       * @Return The nth stored component.
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
       * @Return if the stored value is a valid one.
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

    struct last_t {};
    const last_t last = {};
    struct _1st_t {};
    const _1st_t _1st = {};
    struct _2nd_t {};
    const _2nd_t _2nd = {};
    struct _3rd_t {};
    const _3rd_t _3rd = {};
    struct _4th_t {};
    const _4th_t _4th = {};
    struct _5th_t {};
    const _5th_t _5th = {};



  } // chrono

} // boost

#endif  // header
