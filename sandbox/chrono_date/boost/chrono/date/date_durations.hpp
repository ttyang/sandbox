//  date_durations.hpp
//
//  Copyright 2011-2013 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

/**
 * @file
 *
 * There are some chrono date duration types: days, weeks, months and years.
 * days and weeks are a chrono::duration.
 * The latter two types are modeled after chrono::duration except that there are
 * no conversions to and from the the different durations, not even amongst
 * themselves. These durations represent time durations, as opposed to
 * representing a date component (e.g. 7 months) and are used in date arithmetic.
 * These durations are based on a signed integral type that must be at
 * least 32 bits.
 */
#ifndef BOOST_CHRONO_DATE_DATE_DURATIONS_HPP
#define BOOST_CHRONO_DATE_DATE_DURATIONS_HPP

#include <boost/cstdint.hpp>
#include <boost/chrono/duration.hpp>
//#include <boost/chrono/io/duration_unit_string.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * A duration counting days.
     */
    typedef duration<boost::int_least64_t, boost::ratio<86400> > days;
    /**
     * A duration counting weeks.
     */
    typedef duration<boost::int_least32_t, ratio_multiply<days::period, ratio<7> > > weeks;
    /**
     * A duration counting eras = 400 years.
     */
    typedef duration<boost::int_least32_t, ratio_multiply<days::period, ratio<146097> > >
        eras;
    /**
     * A duration counting average years = eras / 400.
     */
    typedef duration<boost::int_least32_t, ratio_divide<eras::period, ratio<400> > >
        average_years;
    /**
     * A duration counting average months = average_years / 12.
     */
    typedef duration<boost::int_least32_t, ratio_divide<average_years::period, ratio<12> > >
        average_months;


//    /**
//     * partial duration_unit_strings specialization for days
//     */
//    template <class CharT>
//    struct duration_unit_strings<days::period, CharT >
//    {
//      static std::basic_string<CharT> plural()
//      {
//        static const CharT u[] =
//        { 'd', 'a', 'y', 's' };
//        static const std::basic_string<CharT> suffix(u, u + sizeof(u)
//            / sizeof(u[0]));
//        return suffix;
//      }
//      static std::basic_string<CharT> singular()
//      {
//        static const CharT u[] =
//        { 'd', 'a', 'y' };
//        static const std::basic_string<CharT> suffix(u, u + sizeof(u)
//            / sizeof(u[0]));
//        return suffix;
//      }
//      static std::basic_string<CharT> symbol()
//      {
//        //static const std::basic_string<CharT> str(1, 'd');
//        return plural();
//      }
//    };
//    /**
//     * partial duration_unit_strings specialization for weeks
//     */
//    template <class CharT>
//    struct duration_unit_strings<weeks::period, CharT >
//    {
//      static std::basic_string<CharT> plural()
//      {
//        static const CharT u[] =
//        { 'w', 'e', 'e', 'k', 's' };
//        static const std::basic_string<CharT> suffix(u, u + sizeof(u)
//            / sizeof(u[0]));
//        return suffix;
//      }
//      static std::basic_string<CharT> singular()
//      {
//        static const CharT u[] =
//        { 'w', 'e', 'e', 'k' };
//        static const std::basic_string<CharT> suffix(u, u + sizeof(u)
//            / sizeof(u[0]));
//        return suffix;
//      }
//      static std::basic_string<CharT> symbol()
//      {
//        //static const std::basic_string<CharT> str(1, 'W');
//        return plural();
//      }
//    };
//
//    template <class CharT>
//    struct duration_unit_strings<average_months::period, CharT >
//    {
//      static std::basic_string<CharT> plural()
//      {
//        static const CharT u[] =
//        { 'm', 'o', 'n', 't', 'h', 's' };
//        static const std::basic_string<CharT> suffix(u, u + sizeof(u)
//            / sizeof(u[0]));
//        return suffix;
//      }
//      static std::basic_string<CharT> singular()
//      {
//        static const CharT u[] =
//        { 'm', 'o', 'n', 't', 'h'};
//        static const std::basic_string<CharT> suffix(u, u + sizeof(u)
//            / sizeof(u[0]));
//        return suffix;
//      }
//      static std::basic_string<CharT> symbol()
//      {
//        //static const std::basic_string<CharT> str(1, 'M');
//        return plural();
//      }
//    };
//
//    template <class CharT>
//    struct duration_unit_strings<average_years::period, CharT >
//    {
//      static std::basic_string<CharT> plural()
//      {
//        static const CharT u[] =
//        { 'y', 'e', 'a', 'r', 's' };
//        static const std::basic_string<CharT> suffix(u, u + sizeof(u)
//            / sizeof(u[0]));
//        return suffix;
//      }
//      static std::basic_string<CharT> singular()
//      {
//        static const CharT u[] =
//        { 'y', 'e', 'a', 'r' };
//        static const std::basic_string<CharT> suffix(u, u + sizeof(u)
//            / sizeof(u[0]));
//        return suffix;
//      }
//      static std::basic_string<CharT> symbol()
//      {
//        //static const std::basic_string<CharT> str(1, 'M');
//        return plural();
//      }
//    };

    namespace detail
    {
      template <class T, int>
      class duration_type
      {
      public:
        typedef T rep;
      private:
        rep x_;
      public:
        explicit BOOST_FORCEINLINE BOOST_CONSTEXPR duration_type(rep x = rep()) BOOST_NOEXCEPT : x_(x)
        {
        }

        BOOST_FORCEINLINE BOOST_CONSTEXPR rep count() const BOOST_NOEXCEPT
        {
          return x_;
        }

        BOOST_FORCEINLINE BOOST_CONSTEXPR duration_type operator+() const BOOST_NOEXCEPT
        {
          return *this;
        }
        BOOST_FORCEINLINE BOOST_CONSTEXPR duration_type operator-() const BOOST_NOEXCEPT
        {
          return duration_type(-x_);
        }

        BOOST_FORCEINLINE duration_type& operator++() BOOST_NOEXCEPT
        {
          ++x_;
          return *this;
        }
        BOOST_FORCEINLINE duration_type operator++(int) BOOST_NOEXCEPT
        {
          return duration_type(x_++);
        }
        duration_type& operator--() BOOST_NOEXCEPT
        {
          --x_;
          return *this;
        }
        BOOST_FORCEINLINE duration_type operator--(int) BOOST_NOEXCEPT
        {
          return duration_type(x_--);
        }

        BOOST_FORCEINLINE duration_type& operator+=(const duration_type& rhs) BOOST_NOEXCEPT
        {
          x_ += rhs.x_;
          return *this;
        }
        BOOST_FORCEINLINE duration_type& operator-=(const duration_type& rhs) BOOST_NOEXCEPT
        {
          x_ -= rhs.x_;
          return *this;
        }

        friend BOOST_FORCEINLINE duration_type operator+(duration_type x, duration_type y) BOOST_NOEXCEPT
        {
          x += y;
          return x;
        }
        friend BOOST_FORCEINLINE duration_type operator-(duration_type x, duration_type y) BOOST_NOEXCEPT
        {
          x -= y;
          return x;
        }

        BOOST_FORCEINLINE duration_type& operator*=(const rep& rhs) BOOST_NOEXCEPT
        {
          x_ *= rhs;
          return *this;
        }
        BOOST_FORCEINLINE duration_type& operator/=(const rep& rhs) BOOST_NOEXCEPT
        {
          x_ /= rhs;
          return *this;
        }
        BOOST_FORCEINLINE duration_type& operator%=(const rep& rhs) BOOST_NOEXCEPT
        {
          x_ %= rhs;
          return *this;
        }
        BOOST_FORCEINLINE duration_type& operator%=(const duration_type& rhs) BOOST_NOEXCEPT
        {
          x_ %= rhs.x_;
          return *this;
        }

        friend BOOST_FORCEINLINE duration_type operator*(duration_type x, rep y) BOOST_NOEXCEPT
        {
          x *= y;
          return x;
        }
        friend BOOST_FORCEINLINE duration_type operator*(rep x, duration_type y) BOOST_NOEXCEPT
        {
          y *= x;
          return y;
        }
        friend BOOST_FORCEINLINE duration_type operator/(duration_type x, rep y) BOOST_NOEXCEPT
        {
          x /= y;
          return x;
        }
        friend BOOST_FORCEINLINE rep operator/(duration_type x, duration_type y) BOOST_NOEXCEPT
        {
          return x.x_ / y.x_;
        }
        friend BOOST_FORCEINLINE duration_type operator%(duration_type x, rep y) BOOST_NOEXCEPT
        {
          x %= y;
          return x;
        }
        friend BOOST_FORCEINLINE duration_type operator%(duration_type x, duration_type y) BOOST_NOEXCEPT
        {
          x %= y.x_;
          return x;
        }

        friend BOOST_FORCEINLINE BOOST_CONSTEXPR bool operator==(duration_type x, duration_type y) BOOST_NOEXCEPT
        {
          return x.x_ == y.x_;
        }
        friend BOOST_FORCEINLINE BOOST_CONSTEXPR bool operator!=(duration_type x, duration_type y) BOOST_NOEXCEPT
        {
          return !(x == y);
        }
        friend BOOST_FORCEINLINE BOOST_CONSTEXPR bool operator< (duration_type x, duration_type y) BOOST_NOEXCEPT
        {
          return x.x_ < y.x_;
        }
        friend BOOST_FORCEINLINE BOOST_CONSTEXPR bool operator> (duration_type x, duration_type y) BOOST_NOEXCEPT
        {
          return y < x;
        }
        friend BOOST_FORCEINLINE BOOST_CONSTEXPR bool operator<=(duration_type x, duration_type y) BOOST_NOEXCEPT
        {
          return !(y < x);
        }
        friend BOOST_FORCEINLINE BOOST_CONSTEXPR bool operator>=(duration_type x, duration_type y) BOOST_NOEXCEPT
        {
          return !(x < y);
        }

        //friend class date;
      };
    }

    /**
     * A independent duration counting of months.
     */
    typedef detail::duration_type<int32_t, 1> months;

    /**
     * A independent duration counting of years.
     */
    typedef detail::duration_type<int32_t, 2> years;

  } // chrono

} // boost

#endif  // header
