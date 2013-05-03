//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2013 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_BOUNDED_HPP
#define BOOST_CHRONO_DATE_BOUNDED_HPP

#include <boost/chrono/config.hpp>
#include <boost/chrono/date/no_check.hpp>
#include <boost/chrono/date/exceptions.hpp>
#include <boost/chrono/date/detail/to_string.hpp>
#include <boost/throw_exception.hpp>
#include <exception>


namespace boost
{
  namespace chrono
  {

    /**
     * The class @c bounded is used to specify an opaque wrapper around integral type.
     */
    template <typename Tag, int first_, int last_, typename T=int, typename IT=int>
    class bounded
    {
    public:
      typedef T rep;
      typedef IT irep;
      BOOST_STATIC_CONSTEXPR std::size_t size=last_-first_+1; // :5 bits

    private:
      static BOOST_CONSTEXPR bool is_valid_(irep v) BOOST_NOEXCEPT
      {
        return (first_ <= v && v <= last_);
      }
    public:

      /**
       * @Effects: Constructs an object of class @c bounded by storing @c d.
       * @Postconditions: <c>value() == d && is_valid()</c>.
       * @Throws: if @c d is outside of the range [first, last], throws an exception of type @c std::logic_error.
       */

#ifndef  BOOST_NO_CXX11_CONSTEXPR
      BOOST_CONSTEXPR explicit bounded(irep d)
      : value_(
          is_valid_(d)
          ? d
          : throw std::logic_error("bounded " + boost::chrono::to_string(int(d)) + " is out of range")
        )
      {}
#else
      BOOST_CONSTEXPR explicit bounded(irep d)
      : value_(d)
      {
        if (!is_valid_(d))
          throw std::logic_error("bounded " + boost::chrono::to_string(int(d)) + " is out of range");
      }
#endif
      /**
       * @Effects: Constructs an object of class @c bounded by storing @c d.
       * @Postconditions: <c>value() == d</c>.
       * @Note This function doesn't check the parameters validity.
       * It is up to the user to provide a valid ones.
       */
      BOOST_CONSTEXPR bounded(irep d,no_check_t) BOOST_NOEXCEPT
      : value_(d)
      {}
      /**
       * @Return if the stored value is a valid one.
       */
      BOOST_CONSTEXPR bool is_valid() const BOOST_NOEXCEPT
      {
        return is_valid_(value_);
      }
      /**
       * @Requires @c is_valid()
       * @Returns the underlying value of that bounded.
       */
      BOOST_CONSTEXPR operator irep() const BOOST_NOEXCEPT
      {
        return value_;
      }
      /**
       * @Requires @c is_valid()
       * @Returns: the underlying value of that bounded.
       */
      BOOST_CONSTEXPR irep value() const BOOST_NOEXCEPT
      {
        return value_;
      }
      /**
       * @Returns: the min valid value for a bounded of a month.
       */
      static BOOST_CONSTEXPR bounded min BOOST_PREVENT_MACRO_SUBSTITUTION () BOOST_NOEXCEPT
      {
          return bounded(first_,no_check);
      }
      /**
       * @Returns: the max valid value for a bounded of a month.
       */
      static BOOST_CONSTEXPR bounded max BOOST_PREVENT_MACRO_SUBSTITUTION () BOOST_NOEXCEPT
      {
          return bounded(last_,no_check);
      }
      /**
       * @Returns: the first bounded.
       */
      static BOOST_CONSTEXPR bounded first() BOOST_NOEXCEPT
      {
          return bounded(first_,no_check);
      }
      /**
       * @Returns: the first bounded.
       */
      static BOOST_CONSTEXPR bounded last() BOOST_NOEXCEPT
      {
          return bounded(last_,no_check);
      }
    private:
      rep value_;
    };


  } // chrono

} // boost

#endif  // header
