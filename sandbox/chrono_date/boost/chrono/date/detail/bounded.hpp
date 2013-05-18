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
    template <typename Tag, int first_, int last_, typename T=int>
    class bounded
    {
    public:
      /// the underlying type
      typedef T rep;
      BOOST_STATIC_CONSTEXPR T first = first_;
      BOOST_STATIC_CONSTEXPR T last = last_;
      /// the number of elements in the bounded type
      BOOST_STATIC_CONSTEXPR std::size_t size=last_-first_+1;

#if ! defined  BOOST_CHRONO_DATE_DOXYGEN_INVOKED
    private:
      static BOOST_CONSTEXPR BOOST_FORCEINLINE bool is_valid_(int v) BOOST_NOEXCEPT
      {
        return (first_ <= v && v <= last_);
      }
#ifndef  BOOST_NO_CXX11_CONSTEXPR
      static BOOST_CONSTEXPR BOOST_FORCEINLINE int check_invariants(int v)
      {
        return is_valid_(v)
            ? v
            : throw std::out_of_range("bounded " + chrono::to_string(int(v)) + " is out of range " +
                  chrono::to_string(first_) + ".." + chrono::to_string(last_)
                )
              ;
      }
#else
      static BOOST_CONSTEXPR BOOST_FORCEINLINE int check_invariants(int v) BOOST_NOEXCEPT
      {
        if (is_valid_(v))
            return v;
        else
            throw std::out_of_range("bounded " + boost::chrono::to_string(int(v)) + " is out of range");
      }
#endif
#endif
    public:

      /**
       * @c bounded is not @e DefaultConstructible
       */
#ifndef BOOST_NO_CXX11_DELETED_FUNCTIONS
      bounded() = delete;
#else
    private:
      bounded();
    public:
#endif
      /**
       * @Effects Constructs an object of class @c bounded by storing @e d.
       * @Postconditions <c>value() == d && is_valid()</c>.
       * @Throws if @c d is outside of the range [first, last], throws an exception of type @c std::out_of_range.
       */

      BOOST_FORCEINLINE BOOST_CONSTEXPR explicit bounded(int d, check_t)
      : value_(check_invariants(d))
      {}
      /**
       * @Effects Constructs an object of class @c bounded by storing @c d.
       * @Postconditions <c>value() == d</c>.
       * @Note This function doesn't check the parameters validity.
       * It is up to the user to provide a valid one.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR explicit bounded(int d, no_check_t) BOOST_NOEXCEPT
      : value_(d)
      {}
      BOOST_FORCEINLINE BOOST_CONSTEXPR explicit bounded(int d) BOOST_NOEXCEPT
      : value_(d)
      {}
      /**
       * @Return if the stored value is a valid one.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR bool is_valid() const BOOST_NOEXCEPT
      {
        return is_valid_(value_);
      }
      /**
       * @Returns the underlying value of that bounded.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR operator int() const BOOST_NOEXCEPT
      {
        return value_;
      }
      /**
       * @Returns the underlying value of that bounded.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR int value() const BOOST_NOEXCEPT
      {
        return value_;
      }
//      /**
//       * @Returns the min valid value for a bounded of a month.
//       */
//      static BOOST_FORCEINLINE BOOST_CONSTEXPR bounded min BOOST_PREVENT_MACRO_SUBSTITUTION () BOOST_NOEXCEPT
//      {
//          return bounded(first_, no_check);
//      }
//      /**
//       * @Returns the max valid value for a bounded of a month.
//       */
//      static BOOST_FORCEINLINE BOOST_CONSTEXPR bounded max BOOST_PREVENT_MACRO_SUBSTITUTION () BOOST_NOEXCEPT
//      {
//          return bounded(last_, no_check);
//      }
//      /**
//       * @Returns the first bounded.
//       */
//      static BOOST_FORCEINLINE BOOST_CONSTEXPR bounded first() BOOST_NOEXCEPT
//      {
//          return bounded(first_, no_check);
//      }
//      /**
//       * @Returns the first bounded.
//       */
//      static BOOST_FORCEINLINE BOOST_CONSTEXPR bounded last() BOOST_NOEXCEPT
//      {
//          return bounded(last_, no_check);
//      }
    private:
      rep value_;
    };

    namespace unchecked
    {
      /**
       * The class @c bounded is used to specify an opaque wrapper around integral type.
       */
      template <typename Tag, int first_, int last_, typename T=int>
      class bounded
      {
      public:
        /// the underlying type
        typedef T rep;
        BOOST_STATIC_CONSTEXPR T first = first_;
        BOOST_STATIC_CONSTEXPR T last = last_;
        /// the number of elements in the bounded type
        BOOST_STATIC_CONSTEXPR std::size_t size=last_-first_+1;

  #if ! defined  BOOST_CHRONO_DATE_DOXYGEN_INVOKED
      private:
        static BOOST_CONSTEXPR BOOST_FORCEINLINE bool is_valid_(int v) BOOST_NOEXCEPT
        {
          return (first_ <= v && v <= last_);
        }
  #ifndef  BOOST_NO_CXX11_CONSTEXPR
        static BOOST_CONSTEXPR BOOST_FORCEINLINE int check_invariants(int v)
        {
          return is_valid_(v)
              ? v
              : throw std::out_of_range("bounded " + chrono::to_string(int(v)) + " is out of range " +
                    chrono::to_string(first_) + ".." + chrono::to_string(last_)
                  )
                ;
        }
  #else
        static BOOST_CONSTEXPR BOOST_FORCEINLINE int check_invariants(int v) BOOST_NOEXCEPT
        {
          if (is_valid_(v))
              return v;
          else
              throw std::out_of_range("bounded " + boost::chrono::to_string(int(v)) + " is out of range");
        }
  #endif
  #endif
      public:

        /**
         * @c bounded is not @e DefaultConstructible
         */
  #ifndef BOOST_NO_CXX11_DELETED_FUNCTIONS
        bounded() = delete;
  #else
      private:
        bounded();
      public:
  #endif
        /**
         * @Effects Constructs an object of class @c bounded by storing @e d.
         * @Postconditions <c>value() == d && is_valid()</c>.
         * @Throws if @c d is outside of the range [first, last], throws an exception of type @c std::out_of_range.
         */

        BOOST_FORCEINLINE BOOST_CONSTEXPR explicit bounded(int d, check_t)
        : value_(check_invariants(d))
        {}
        /**
         * @Effects Constructs an object of class @c bounded by storing @c d.
         * @Postconditions <c>value() == d</c>.
         * @Note This function doesn't check the parameters validity.
         * It is up to the user to provide a valid one.
         */
        BOOST_FORCEINLINE BOOST_CONSTEXPR explicit bounded(int d, no_check_t) BOOST_NOEXCEPT
        : value_(d)
        {}
        BOOST_FORCEINLINE BOOST_CONSTEXPR explicit bounded(int d) BOOST_NOEXCEPT
        : value_(d)
        {}
        /**
         * @Return if the stored value is a valid one.
         */
        BOOST_FORCEINLINE BOOST_CONSTEXPR bool is_valid() const BOOST_NOEXCEPT
        {
          return is_valid_(value_);
        }
        /**
         * @Returns the underlying value of that bounded.
         */
        BOOST_FORCEINLINE BOOST_CONSTEXPR operator int() const BOOST_NOEXCEPT
        {
          return value_;
        }
        /**
         * @Returns the underlying value of that bounded.
         */
        BOOST_FORCEINLINE BOOST_CONSTEXPR int value() const BOOST_NOEXCEPT
        {
          return value_;
        }

      private:
        rep value_;
      };
    } //unchecked

  } // chrono

} // boost

#endif  // header
