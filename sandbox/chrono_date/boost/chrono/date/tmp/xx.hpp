//
//  (C) Copyright Howard Hinnant
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//

#ifndef BOOST_CHRONO_IO_DURATION_GET_HPP
#define BOOST_CHRONO_IO_DURATION_GET_HPP

#include <boost/chrono/config.hpp>
#include <string>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/mpl/if.hpp>
#include <boost/math/common_factor_rt.hpp>
#include <boost/chrono/detail/scan_keyword.hpp>
#include <boost/assert.hpp>
#include <locale>
/**
 * Duration formatting facet for input.
 */
namespace boost
{
  namespace chrono
  {

    namespace detail
    {
      template <class Rep, bool = is_scalar<Rep>::value>
      struct duration_io_intermediate
      {
        typedef Rep type;
      };

      template <class Rep>
      struct duration_io_intermediate<Rep, true>
      {
        typedef typename mpl::if_c<is_floating_point<Rep>::value, long double, typename mpl::if_c<
            is_signed<Rep>::value, long long, unsigned long long>::type>::type type;
      };

      template <typename intermediate_type>
      typename enable_if<is_integral<intermediate_type>, bool>::type
      reduce(intermediate_type& r, unsigned long long& den, std::ios_base::iostate& err)
      {
        typedef typename common_type<intermediate_type, unsigned long long>::type common_type_t;

          // Reduce r * num / den
        common_type_t t = math::gcd<common_type_t>(common_type_t(r), common_type_t(den));
        r /= t;
        den /= t;
        if (den != 1)
        {
          // Conversion to Period is integral and not exact
          err |= std::ios_base::failbit;
          return false;
        }
        return true;
      }
      template <typename intermediate_type>
      typename disable_if<is_integral<intermediate_type>, bool>::type
      reduce(intermediate_type& , unsigned long long& , std::ios_base::iostate& )
      {
        return true;
      }

    }

    /**
     * @c duration_get is used to parse a character sequence, extracting
     * components of a duration into a class duration.
     * Each get member parses a format as produced by a corresponding format specifier to time_put<>::put.
     * If the sequence being parsed matches the correct format, the
     * corresponding member of the class duration argument are set to the
     * value used to produce the sequence;
     * otherwise either an error is reported or unspecified values are assigned.
     * In other words, user confirmation is required for reliable parsing of
     * user-entered durations, but machine-generated formats can be parsed
     * reliably. This allows parsers to be aggressive about interpreting user
     * variations on standard formats.
     *
     * If the end iterator is reached during parsing of the get() member
     * function, the member sets std::ios_base::eofbit in err.
     */
    template <class CharT, class InputIterator = std::istreambuf_iterator<CharT> >
    class duration_get: public std::locale::facet
    {
    public:
      /**
       * Type of character the facet is instantiated on.
       */
      typedef CharT char_type;
      typedef std::basic_string<CharT> string_type;
      /**
       * Type of iterator used to scan the character buffer.
       */
      typedef InputIterator iter_type;

      /**
       * Construct a @c duration_get facet.
       * @param refs
       * @Effects Construct a @c duration_get facet.
       * If the @c refs argument is @c 0 then destruction of the object is
       * delegated to the @c locale, or locales, containing it. This allows
       * the user to ignore lifetime management issues. On the other had,
       * if @c refs is @c 1 then the object must be explicitly deleted;
       * the @c locale will not do so. In this case, the object can be
       * maintained across the lifetime of multiple locales.
       */

      explicit duration_get(size_t refs = 0) :
        std::locale::facet(refs)
      {
      }

      /**
       * @param s start input stream iterator
       * @param end end input stream iterator
       * @param ios a reference to a ios_base
       * @param err the ios_base state
       * @param d the duration
       * @param pattern begin of the formatting pattern
       * @param pat_end end of the formatting pattern
       *
       * Requires: [pattern,pat_end) shall be a valid range.
       *
       * Effects: The function starts by evaluating err = std::ios_base::goodbit.
       * It then enters a loop, reading zero or more characters from s at
       * each iteration. Unless otherwise specified below, the loop
       * terminates when the first of the following conditions holds:
       * - The expression pattern == pat_end evaluates to true.
       * - The expression err == std::ios_base::goodbit evaluates to false.
       * - The expression s == end evaluates to true, in which case the
       * function evaluates err = std::ios_base::eofbit | std::ios_base::failbit.
       * - The next element of pattern is equal to ’%’, followed by a conversion
       * specifier character, format.
       * If the number of elements in the range [pattern,pat_end) is not
       * sufficient to unambiguously determine whether the conversion
       * specification is complete and valid, the function evaluates
       * err = std::ios_base::failbit. Otherwise, the function evaluates
       * s = do_get(s, end, ios, err, d). If err == std::ios_base::goodbit holds after
       * the evaluation of the expression, the function increments pattern to
       * point just past the end of the conversion specification and continues
       * looping.
       * - The expression isspace(*pattern, ios.getloc()) evaluates to true, in
       * which case the function first increments pattern until
       * pattern == pat_end || !isspace(*pattern, ios.getloc()) evaluates to true,
       * then advances s until s == end || !isspace(*s, ios.getloc()) is true,
       * and finally resumes looping.
       * - The next character read from s matches the element pointed to by
       * pattern in a case-insensitive comparison, in which case the function
       * evaluates ++pattern, ++s and continues looping. Otherwise, the function
       * evaluates err = std::ios_base::failbit.
       *
       * Returns: s
       */
      template <typename Rep, typename Period>
      iter_type get(iter_type s, iter_type end, std::ios_base& ios, std::ios_base::iostate& err,
          duration<Rep, Period> &d, const char_type *pattern, const char_type *pat_end) const
      {

        typedef typename detail::duration_io_intermediate<Rep>::type intermediate_type;
        intermediate_type r;
        detail::rt_ratio rt;
        bool value_found=false, unit_found=false, loc_found=false;

        const std::ctype<char_type>& ct = std::use_facet<std::ctype<char_type> >(ios.getloc());
        err = std::ios_base::goodbit;
        while (pattern != pat_end && err == std::ios_base::goodbit)
        {
            if (s == end)
            {
                err |= std::ios_base::eofbit;
                break;
            }
            if (ct.narrow(*pattern, 0) == '%')
            {
                if (++pattern == pat_end)
                {
                    err |= std::ios_base::failbit;
                    return s;
                }
                char cmd = ct.narrow(*pattern, 0);
                switch (cmd)
                {
                case 'v':
                {
                  if (value_found) {
                    err |= std::ios_base::failbit;
                    return s;
                  }
                  if (value_found) {
                    err |= std::ios_base::failbit;
                    return s;
                  }
                  value_found=true;
                  s=get_value(s, end, ios, err, r);
                  if ( err & (std::ios_base::badbit |std::ios_base::failbit) )
                  {
                    return s;
                  }
                  break;
                }
                case 'u':
                {
                  if (unit_found) {
                    err |= std::ios_base::failbit;
                    return s;
                  }
                  unit_found=true;
                  s = get_unit(s, end, ios, err, rt);
                  if ( err & (std::ios_base::badbit |std::ios_base::failbit) )
                  {
                    return s;
                  }
                  break;
                }
                case 'x':
                {
                  if (unit_found || value_found || loc_found) {
                    err |= std::ios_base::failbit;
                    return s;
                  }
                  loc_found=true;
                  string_type pat = duration_units<CharT>::imbue_if_has_not(ios).get_pattern();
                  if (pattern+1 != pat_end)
                  pat.append(pattern+1, pat_end);
                  pattern = pat.data();
                  pat_end = pattern + pat.size();
                  break;
                }
                default:
                  BOOST_ASSERT(false && "Boost::Chrono internal error.");
                  break;
                }

                ++pattern;
            }
            else if (ct.is(std::ctype_base::space, *pattern))
            {
                for (++pattern; pattern != pat_end && ct.is(std::ctype_base::space, *pattern); ++pattern)
                    ;
                for (        ;    s != end    && ct.is(std::ctype_base::space, *s);    ++s)
                    ;
            }
            else if (ct.toupper(*s) == ct.toupper(*pattern))
            {
                ++s;
                ++pattern;
            }
            else {
                err |= std::ios_base::failbit;
            }

        }

        unsigned long long num = rt.num;
        unsigned long long den = rt.den;

        // r should be multiplied by (num/den) / Period
        // Reduce (num/den) / Period to lowest terms
        unsigned long long gcd_n1_n2 = math::gcd<unsigned long long>(num, Period::num);
        unsigned long long gcd_d1_d2 = math::gcd<unsigned long long>(den, Period::den);
        num /= gcd_n1_n2;
        den /= gcd_d1_d2;
        unsigned long long n2 = Period::num / gcd_n1_n2;
        unsigned long long d2 = Period::den / gcd_d1_d2;
        if (num > (std::numeric_limits<unsigned long long>::max)() / d2 || den > (std::numeric_limits<
            unsigned long long>::max)() / n2)
        {
          // (num/den) / Period overflows
          err |= std::ios_base::failbit;
          return s;
        }
        num *= d2;
        den *= n2;

        typedef typename common_type<intermediate_type, unsigned long long>::type common_type_t;

        // num / den is now factor to multiply by r
        if (!detail::reduce(r, den, err))
          return s;

        if (r > ( (duration_values<common_type_t>::max)() / num))
        {
          // Conversion to Period overflowed
          err |= std::ios_base::failbit;
          return s;
        }
        common_type_t t = r * num;
        t /= den;
        if (t > 0)
        {
          Rep pt = t;
          if ( (duration_values<Rep>::max)() < pt)
          {
            // Conversion to Period overflowed
            err |= std::ios_base::failbit;
            return s;
          }
        }
        // Success!  Store it.
        r = Rep(t);
        d = duration<Rep, Period> (r);


        return s;
      }

      /**
       *
       * @param s an input stream iterator
       * @param ios a reference to a ios_base
       * @param d the duration
       * @Effects imbue in @c ios the @c duration_units_default facet if not already present.
       * Retrieves Stores the duration pattern from the @c duration_unit facet in let say @c str. Last as if
       * @code
       *   return get(s, end, ios, err, ios, d, str.data(), str.data() + str.size());
       * @codeend
       * @Returns An iterator pointing just beyond the last character that can be determined to be part of a valid name
       */
      template <typename Rep, typename Period>
      iter_type get(iter_type s, iter_type end, std::ios_base& ios, std::ios_base::iostate& err,
          duration<Rep, Period> & d) const
      {
        std::basic_string < CharT > str = duration_units<CharT>::imbue_if_has_not(ios).get_pattern();
        return get(s, end, ios, err, d, str.data(), str.data() + str.size());
      }

      /**
       *
       * @param s an input stream iterator
       * @param ios a reference to a ios_base
       * @param d the duration
       * @Returns An iterator pointing just beyond the last character that can be determined to be part of a valid name
       */
      template <typename Rep>
      iter_type get_value(iter_type s, iter_type end, std::ios_base& ios, std::ios_base::iostate& err, Rep& r) const
      {
        return std::use_facet<std::num_get<CharT, iter_type> >(ios.getloc()).get(s, end, ios, err, r);
      }

      /**
       *
       * @param s an output stream iterator
       * @param ios a reference to a ios_base
       * @param d the duration
       * @param pattern
       * @Effects Calls do_put_unit(s, ios, d).
       * @Returns An iterator pointing just beyond the last character that can be determined to be part of a valid name
       */
      virtual iter_type do_get_prefix_unit(iter_type i, iter_type e, std::ios_base& is, std::ios_base::iostate& err,
          detail::rt_ratio &rt) const
      {
        duration_units<CharT> const &facet = duration_units<CharT>::imbue_if_has_not(is);

        // parse SI name, short or long
        std::size_t pfs = facet.get_plural_forms()+1;

        // scoped_ptr ???
        string_type* units= new string_type[19*pfs]();
        string_type* it = units;
        it = facet.fill_units(it, atto());
        it = facet.fill_units(it, femto());
        it = facet.fill_units(it, pico());
        it = facet.fill_units(it, nano());
        it = facet.fill_units(it, micro());
        it = facet.fill_units(it, milli());
        it = facet.fill_units(it, centi());
        it = facet.fill_units(it, deci());
        it = facet.fill_units(it, deca());
        it = facet.fill_units(it, hecto());
        it = facet.fill_units(it, kilo());
        it = facet.fill_units(it, mega());
        it = facet.fill_units(it, giga());
        it = facet.fill_units(it, tera());
        it = facet.fill_units(it, peta());
        it = facet.fill_units(it, exa());
        it = facet.fill_units(it, ratio<1>());
        it = facet.fill_units(it, ratio<60>());
        it = facet.fill_units(it, ratio<3600>());

        string_type* units_end=  units +19*pfs;


        err = std::ios_base::goodbit;
        const string_type* k = chrono_detail::scan_keyword(i, e, units,
            units_end,
            //~ std::use_facet<std::ctype<CharT> >(loc),
            err);

        std::size_t index =  (k - units) / pfs;
        delete []units;
        switch ( index )
        {
        case 0:
          rt = detail::rt_ratio(atto());
          break;
        case 1:
          rt = detail::rt_ratio(femto());
          break;
        case 2:
          rt = detail::rt_ratio(pico());
          break;
        case 3:
          rt = detail::rt_ratio(nano());
          break;
        case 4:
          rt = detail::rt_ratio(micro());
          break;
        case 5:
          rt = detail::rt_ratio(milli());
          break;
        case 6:
          rt = detail::rt_ratio(centi());
          break;
        case 7:
          rt = detail::rt_ratio(deci());
          break;
        case 8:
          rt = detail::rt_ratio(deca());
          break;
        case 9:
          rt = detail::rt_ratio(hecto());
          break;
        case 10:
          rt = detail::rt_ratio(kilo());
          break;
        case 11:
          rt = detail::rt_ratio(mega());
          break;
        case 12:
          rt = detail::rt_ratio(giga());
          break;
        case 13:
          rt = detail::rt_ratio(tera());
          break;
        case 14:
          rt = detail::rt_ratio(peta());
          break;
        case 15:
          rt = detail::rt_ratio(exa());
          break;
        case 16:
          rt = detail::rt_ratio(ratio<1>());
          break;
        case 17:
          rt = detail::rt_ratio(ratio<60>());
          break;
        case 18:
          rt = detail::rt_ratio(ratio<3600>());
          break;
        default:
          err = std::ios_base::failbit;
          std::cout << __FILE__ << ":" << __LINE__ << std::endl;
          return i;
        }

      }
      //template <typename Rep>
      iter_type get_unit(iter_type i, iter_type e, std::ios_base& is, std::ios_base::iostate& err,
          detail::rt_ratio &rt) const
      {
        duration_units<CharT> const &facet = duration_units<CharT>::imbue_if_has_not(is);

        if (*i == '[')
        {
          // parse [N/D]s or [N/D]seconds format
          ++i;
          i=std::use_facet<std::num_get<CharT, iter_type> >(is.getloc()).get(i, e, is, err, rt.num);
          if ((err & std::ios_base::failbit) != 0)
          {
            return i;
          }

          if (i==e)
          {
            err |= std::ios_base::failbit;
            return i;
          }
          CharT x = *i++;
          if (x != '/')
          {
            err |= std::ios_base::failbit;
            return i;
          }
          i=std::use_facet<std::num_get<CharT, iter_type> >(is.getloc()).get(i, e, is, err, rt.den);
          if ((err & std::ios_base::failbit) != 0)
          {
            return i;
          }
          if (i==e)
          {
            err |= std::ios_base::failbit;
            return i;
          }
          if (*i != ']')
          {
            err |= std::ios_base::failbit;
            return i;
          }
          ++i;
          if (i==e)
          {
            err |= std::ios_base::failbit;
            return i;
          }
          const string_type units[] =
          {
              facet.template get_plural_form<ratio<1> >(duration_style::prefix, 1),
              facet.template get_plural_form<ratio<1> >(duration_style::prefix, 0),
              facet.template get_plural_form<ratio<1> >(duration_style::symbol, 0)
          };
          // FIXME is this necessary?????
          err = std::ios_base::goodbit;
          const string_type* k = chrono_detail::scan_keyword(i, e, units,
              units + sizeof (units) / sizeof (units[0]),
              //~ std::use_facet<std::ctype<CharT> >(loc),
              err);
          switch ( (k - units) / 3)
          {
          case 0:
            break;
          default:
            err |= std::ios_base::failbit;
            return i;
          }
        }
        else
        {
          return do_get_prefix_unit(i, e, is, err, rt);
        }
        // unit is num/den

        return i;
      }

      /**
       * Unique identifier for this type of facet.
       */
      static std::locale::id id;

      /**
       * @Effects Destroy the facet
       */
      ~duration_get()
      {
      }
    };

    /**
     * Unique identifier for this type of facet.
     */
    template <class CharT, class InputIterator>
    std::locale::id duration_get<CharT, InputIterator>::id;

  } // chrono
}
// boost

#endif  // BOOST_CHRONO_CHRONO_IO_HPP



////////////////////////////////
1-1-1
real  1m23.072s
user  1m10.769s
sys 0m10.921s

real  1m21.565s
user  1m9.964s
sys 0m10.792s

2-1-1
real  1m25.853s
user  1m10.232s
sys 0m10.905s

real  1m21.732s
user  1m10.101s
sys 0m10.744s

2-1-2
real  1m23.478s
user  1m10.949s
sys 0m10.972s


3-1-1
real  1m22.610s
user  1m10.893s
sys 0m10.971s


3-1-3
real  1m21.687s
user  1m10.086s
sys 0m10.824s


3-3-3
real  1m21.520s
user  1m9.906s
sys 0m10.823s

real  1m23.354s
user  1m9.983s
sys 0m10.753s


#ifdef CCCCCC
Howard Hinnant
====================================
   Autres options 23 août, 20:26
On Aug 23, 2011, at 2:15 PM, Nevin Liber wrote:

> On 23 August 2011 12:34, Howard Hinnant <howard.hinn...@gmail.com> wrote:

>>  If someone wants to go to the trouble to set up a real mailing list, knock yourself out! :-)

> I'm setting up kona-date-lib@googlegroups.com.  Invites going out shortly.
> --
>  Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

Thanks Nevin, I've joined.

Howard

====================================
====================================



Howard Hinnant
====================================
   Autres options 23 août, 21:56
On Aug 23, 2011, at 3:38 PM, j...@crystalclearsoftware.com wrote:

- Afficher le texte des messages précédents -

I'm probably not a good person to answer this question (too much bias).  There are attendees here who can answer much better.

I got the impression that few (maybe one) liked the library.  But I also got the impression that different people disliked or liked different parts.  For example I know that John L.  really disliked the storage of meta-data in the date class to influence the behavior of year and month arithmetic, while the same data did not influence the behavior of date comparison.  Others found the use of forward slash for date construction "too cute", and yet others didn't seem to mind it.  I recall one comment that the library should support the forth ordering supported by time_get:  ydm.  But I also got the impression that others believe we need only support ymd.

There was significant talk that the library conflated the ideas of a date with a calendar.  Or something like that.  I'm not currently qualified to address that issue.  Though I believe Alan has some ideas in this area.

Bottom line:  if you were to lock me away in solitary confinement for the next 5 months and ask me to rewrite that proposal based on the feedback from Bloomington, I seriously doubt I could improve it much.  Thus the purpose of this group.  I think as a collective we have a much better chance.  And I think we should start, at least at first, with pretty much a clean sheet, as opposed to build upon my proposal.

I encourage others to help me answer Jeff's question.

Howard

PS:  Hopefully we'll get the google group problems ironed out soon.  For now my plan is to double-post.

====================================
====================================



Ville Voutilainen
====================================
   Autres options 23 août, 22:24
On 23 August 2011 22:56, Howard Hinnant <howard.hinn...@gmail.com> wrote:

> I got the impression that few (maybe one) liked the library.  But I also got the impression that different people disliked or liked different parts.  For example I know that John L.  really disliked the storage of meta-data in the date class to influence the behavior of year and month arithmetic, while the same data did not influence the behavior of date comparison.  Others found the use of forward slash for date construction "too cute", and yet others didn't seem to mind it.  I recall one comment that the library should support the forth ordering supported by time_get:  ydm.  But I also got the impression that others believe we need only support ymd.

The construction gave me pause, and I do think it's

1) too cute
2) counterintuitive for my locale (we use dot, others use dash)
3) dangerous if I happen to pass such date types to unconstrained
generic code that uses operator/,
as such code may compile fine but do weird things.

I'd prefer sticking to yyyy followed by mm followed by dd, or
otherwise not forcing any order. I don't like
that it can recognize raw numbers as the third component magically if
two components are specified.

Providing just a gregorian calendar seems fine, as the proposal
indicates that adding other calendar types
on top of it should be easy.

I feel unease about add_month and such, and the fact that they throw
an exception if the result is invalid.
I don't have a clear idea of a better approach, though. I suppose many
users will like such functions.

Regarding what John W said, I'd prefer standardizing the bare
essentials and providing ranges and such
separately.

Just my 0.02.

====================================
====================================



Daniel Krügler
====================================
   Autres options 23 août, 22:32
2011/8/23 Ville Voutilainen <ville.voutilai...@gmail.com>:

> On 23 August 2011 22:56, Howard Hinnant <howard.hinn...@gmail.com> wrote:
>> I got the impression that few (maybe one) liked the library.  But I also got the impression that different people disliked or liked different parts.  For example I know that John L.  really disliked the storage of meta-data in the date class to influence the behavior of year and month arithmetic, while the same data did not influence the behavior of date comparison.  Others found the use of forward slash for date construction "too cute", and yet others didn't seem to mind it.  I recall one comment that the library should support the forth ordering supported by time_get:  ydm.  But I also got the impression that others believe we need only support ymd.

> The construction gave me pause, and I do think it's

> 1) too cute
> 2) counterintuitive for my locale (we use dot, others use dash)

Actually I found the approach rather natural, similar to the choice
of operator/ in the file system proposal, even though this is not
the correct separator for each system.

> 3) dangerous if I happen to pass such date types to unconstrained
> generic code that uses operator/,
> as such code may compile fine but do weird things.

The same argument would apply for the file system proposal
and I have never heard of problems of users among my
colleagues with this decision.

> I'd prefer sticking to yyyy followed by mm followed by dd, or
> otherwise not forcing any order. I don't like
> that it can recognize raw numbers as the third component magically if
> two components are specified.

I'm neutral on this one, but I found Howard's approach so type-safe,
that I didn't have problems with the possible diversity.

> Providing just a gregorian calendar seems fine, as the proposal
> indicates that adding other calendar types
> on top of it should be easy.

I agree.

> I feel unease about add_month and such, and the fact that they throw
> an exception if the result is invalid.
> I don't have a clear idea of a better approach, though. I suppose many
> users will like such functions.

Maybe we could use an approach that allows both choices via
system errors (See also file system library).

- Daniel

====================================
====================================



Jeff Garland
====================================
   Autres options 23 août, 23:02

 > Could you elaborate on the concerns expressed by the lwg to help us

> > understand what they liked and what they didn't?

> I'm probably not a good person to answer this question (too much bias).
>  There are attendees here who can answer much better.

> Sure, it's always subjective, but if there's some clear objection to a

particular element then that can be addressed directly.

> I got the impression that few (maybe one) liked the library.  But I also
> got the impression that different people disliked or liked different parts.
>  For example I know that John L.  really disliked the storage of meta-data
> in the date class to influence the behavior of year and month arithmetic,
> while the same data did not influence the behavior of date comparison.
>  Others found the use of forward slash for date construction "too cute", and
> yet others didn't seem to mind it.  I recall one comment that the library
> should support the forth ordering supported by time_get:  ydm.  But I also
> got the impression that others believe we need only support ymd.

Ok.

> There was significant talk that the library conflated the ideas of a date
> with a calendar.  Or something like that.  I'm not currently qualified to
> address that issue.  Though I believe Alan has some ideas in this area.

Sure.  There's date-time libraries that isolate the details of a calendar
representation explicitly into a single class while maintaining a 'universal
internal representation'.  If you read Calendrical Calculations or look at a
Java library like Joda you'll see this design.  In boost date time v1 it's
separate in the implementation with the intent that new calendar types could
be plugged in with minimal effort -- frankly I never got more than a handful
of requests for other calendars over a ten year period so there wasn't much
motivation.  The typical tradeoff here is a '2 object construction' -- where
you need a calendar to construct a date -- in sacrifices usability in my
view.

BTW, some people on the list may not be aware of the previous papers I've
presented to the committee -- the first N1900 is a scope outline and
discussion --

http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2005/n1900.pdf --
concepts and basic library outline
http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2058.html -- first
cut at  real wording -- after working the thread stuff I realize how
inadequate it is...

Honestly, I think there's much of the motivation / need documented in these.
Needless to say, these will be the starting point for my effort.  Note that
the "huge" problem I see in what's represented there is the complexity of
the proposal -- it's going to be hard for the lwg to swallow -- again, this
opinion coming from seeing how hard it was to get agreement on the chrono
api.  Still I'm inclined to shoot higher than Howard's date proposal....

> Bottom line:  if you were to lock me away in solitary confinement for the
> next 5 months and ask me to rewrite that proposal based on the feedback from
> Bloomington, I seriously doubt I could improve it much.  Thus the purpose of
> this group.  I think as a collective we have a much better chance.  And I
> think we should start, at least at first, with pretty much a clean sheet, as
> opposed to build upon my proposal.

> I encourage others to help me answer Jeff's question.

Please do.

> Howard

> PS:  Hopefully we'll get the google group problems ironed out soon.  For
> now my plan is to double-post.

Seems to be working for me now.

Jeff

====================================
====================================



Ville Voutilainen
====================================
   Autres options 23 août, 23:19
On 23 August 2011 23:32, Daniel Krügler <daniel.krueg...@googlemail.com> wrote:

> Actually I found the approach rather natural, similar to the choice
> of operator/ in the file system proposal, even though this is not
> the correct separator for each system.
> The same argument would apply for the file system proposal
> and I have never heard of problems of users among my
> colleagues with this decision.

I'll go shoot down the filesystem proposal separately, then. :) In
this discussion,
I'm planning to stick to the date proposal.

====================================
====================================



Daniel Krügler
====================================
   Autres options 24 août, 20:18
2011/8/24 JOHN LAKOS, BLOOMBERG/ 731 LEXIN <jla...@bloomberg.net>:

> Hi All,

> Based on what I have seen so far, I would like to state what I see are
> essential requirements for any standardized (reusable) date type.  Note that I have omitted 'constexpr' and 'noexcept'; they shall be added where appropriate.

> 1.  The date type is *value* *semantic*:
>      + its *salient* *attributes* are 'year', 'month', 'day' -- nothing else!

OK.

> 2.  An invariant of a date object is that it represents a valid date value.
>      + Note that Not-A-Date is better represented externally (e.g., boost
>        'optional', or our 'Nullable') so as not to force checking on each use.
>      + Also, nans in doubles are a problem when it comes to value semantics as
>        operator== is no longer a post condition of copy construction.  (I would
>        not want to use 'double' as a model for other types.)

I can accept this pov, even though NaD is often useful itself, but I'm not
strongly asking for it.

> 3.  There is a way to set a date's value without validating it.

Yes.

> 4.  There is a way to validate a date value, without creating a date object.

Fine.

> 5.  The date class is *not* a template class (it doesn't take an allocator).

I don't see need for an allocator, but I would not at this point in the design
phase exclude a template. Underlying representation can be one useful
choice. If we combine the duration library with the date library, this
might naturally follow (but I'm not trying to enforce this now. I was fine
with Howard's initial suggestion w/o this feature).

> 6.  The date class assumes a simple standard calendar (e.g., Proleptic
>    Gregorian, as in Howard's proposal).
>      + Conversions to/from dates in other calendars are higher-level utilities.
>      + (See 10. Below.)

Yes.

> 7.  There is no mention of 'epoch', only a valid range of supported dates.

OK.

> 8.  The class is maximally fast (otherwise it is not generally usable):
>      + Creating an invalid date is undefined behavior (not an exception).
>      + Exceeding the valid range is undefined behavior (not an exception).
>      + Note that the imp is "allowed" to check and throw, but not required to.
>      + (Will discuss more in the context of a new proposed assert facility).

It is very easy to make input error in dates. I would strongly object for not
having at least a chance for a portable, checked construction that
would through.
As an alternative suggestion to the above I would suggest the combination of

a) Exception per default

b) If you provide an error_code object as argument, no exception will be
thrown, but an error value will be set.

> 9.  There are essentially no non-primitive operations.
>      + Non-instance method: bool isValidYearMonthDay(int, int, int);

This looks like an error-prone approach, if you need to write

if (isValidYearMonthDay(1993, 09, 31))
  throw ...

date d(1993, 08, 31);
                   ^^

Strongly opposed.

>      + Default ctor, copy ctor & assign, trivial dtor.
>      + Value ctors that takes 'year', 'month', and 'day' (w/without tag types).

>      + Manipulator to set 'year', 'month', 'day' at once that returns 'void'.
>        * e.g., void setYearMonthDay(int year, int month, int day);
>        * The behavior is UNDEFINED if these do not represent a valid date.
>      + Manipulator to set 'year', 'month', 'day' at once that returns 'bool'.
>        * e.g., bool setYearMonthDayifValid(int year, int month, int day);
>        * The operation returns 'true' if valid, and 'false' (with no effect)
>          otherwise.

Concerning error handling see above. Why isn't month an enum, too?

>      + Accessors to get 'year', 'month', 'day' separately.
>      + An accessor to get 'year', 'month', 'day' all at once.
>      + An accessor to get the day-of-week (as an enum 0-6).

OK.

>      + The following operators:
>        // member
>        * date& operator+=(int days);               // add days to this date
>        * date& operator-=(int days);               // subtract days from date
>        // free
>        * ostream& operator<<(ostream&, const date&)// human-readable format
>        * istream& operator>>(istream&, date&);     // (optional, not necessary)

What about: We may want to separate IO into a different header?

- Afficher le texte des messages précédents -

I haven't thought about this hierarchy yet, but will do.

> I am sure that we will have lot's of interesting discussions about all this stuff.  Let's get going...

I agree.

- Daniel

====================================
====================================



Nevin Liber
====================================
   Autres options 24 août, 21:48
[Note:  we are down to one person who has not yet accepted the invite
to be on the mailing list]

On 24 August 2011 12:45, JOHN LAKOS, BLOOMBERG/ 731 LEXIN

<jla...@bloomberg.net> wrote:
> 2.  An invariant of a date object is that it represents a valid date value.

I agree.

>      + Note that Not-A-Date is better represented externally (e.g., boost
>        'optional', or our 'Nullable') so as not to force checking on each use.

I'm still on the fence on this one.

>      + Also, nans in doubles are a problem when it comes to value semantics as
>        operator== is no longer a post condition of copy construction.  (I would
>        not want to use 'double' as a model for other types.)

I agree for so many reasons.  Dates should have a SWO (doubles don't
because of nans so they can't be used as keys in ordered containers),
sortable, etc.

> 5.  The date class is *not* a template class (it doesn't take an allocator).

Is it because you want to rule out allocators (heap allocations which
imply exceptions) or just because it makes the class harder to use?  I
agree that there shouldn't be heap allocations (we want this class to
be fast), but on the fence on ruling out templates (not that I see a
use for them yet; we obviously shouldn't put them in just because we
can).

> 8.  The class is maximally fast (otherwise it is not generally usable):
>      + Creating an invalid date is undefined behavior (not an exception).
>      + Exceeding the valid range is undefined behavior (not an exception).
>      + Note that the imp is "allowed" to check and throw, but not required to.
>      + (Will discuss more in the context of a new proposed assert facility).

Not sure that I agree with the viewpoint that not meeting class
invariants should always result in undefined behavior instead of
exceptions being thrown.  That discussion is probably better when you
present your assert facility (I think that decision is mostly
orthogonal to defining the rest of the interface).

> 9.  There are essentially no non-primitive operations.
>      + Non-instance method: bool isValidYearMonthDay(int, int, int);

I don't want to see any interface taking multiple ints; way too error
prone.  Get things into the type system as quickly as possible.  I'd
like to see primitive types for Year, Month and Day.  I'd rather see:

bool isValidDate(Year, Month, Day)

Note:  I have no strong opinion on whether to support all permutations
(isValidDate(Month, Day, Year), isValidDate(Day, Month, Year), etc.)
or not, nor on whether the parameters should be passed in by value vs.
const reference.

(Similar comment for other interfaces.)

>      + The following operators:
>        // member
>        * date& operator+=(int days);               // add days to this date
>        * date& operator-=(int days);               // subtract days from date

Shouldn't take ints; should take a Days type which represents a
duration and is different from Day.

Still digesting the higher level utilities...
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



JOHN LAKOS, BLOOMBERG/ 731 LEXIN
====================================
   Autres options 24 août, 22:06
Hey Daniel,

I must say I am both pleased and a bit surprised with the amount of agreement, and/or lack of disagreement that you seemed to have with this initial cut
at date type requrements.  I will wait to hear what other think for most of this doc, but I do want to respond to your "strong opposition" to a small part of "point 9." now, so that perhaps I can clarify what I am getting at:

>> 9.  There are essentially no non-primitive operations.
>>      + Non-instance method: bool isValidYearMonthDay(int, int, int);

>This looks like an error-prone approach, if you need to write

>if (isValidYearMonthDay(1993, 09, 31))
>  throw ...

>date d(1993, 08, 31);
>                   ^^

>Strongly opposed.

Daniel, There are a number of important issues to address here.

First of all, you (or at least I) would never write code like this.  Note       that there was a manipulator in point 9...

       bool setYearMonthDateIfValid(int year, int month, int day).
            // Set this date to the indicated value and return 'true' if the
            // specified 'year', 'month', and 'day' represent a valid date
            // value; othrwise return 'false' with no effect.

that avoids your having repeate the literal date value:

       date d;
       if (!d.setYearMonthDayIfValid(1993, 09, 31)) throw 'logic_error';
       // ...

Except that I would not throw here either.  The problem is that some inputs
are known to be good, and some are not.  For those inputs that are known to
be good, the extra if to check to see if the date is valid is not viable in
many important practical contexts.  In finacial calculations in particular,
the cost of the 'if' could make or break the system.  That said, there are other
situations in which checking is exacatly the right answer!  But we can't have
it both ways!  Or can we?  As a matter of fact we can!

By specifying that constructing or setting a date to an invalid value is UNDEFINED BEHAVIOR, we allow for the possibility of a robust implemenation to detect the error in a CHECKED BUILD MODE.  This new, very general proposed approach to "defensive programming done right" (paper in Kona) will allow the applciation developer to:

 (1) specify with some granularity how much checking should be done at
     runtime: (a) none, (b) some, (c) lots, (d) go for it!, and

 (2) excatly what should happen if a pre-condition violation is detected:
     (a) abort, (b) throw, (c) spin, (d) <your desired behavior here>.

But if we don't know that the date coming into a system is valid, we will
not want to construct a date within a try block, because that is absurdly
inneficent and clunky.  Instead I would always address both the 'if' and 'else'
directly.

    void processRawDateValue(int year, int month, int day)
    {
        Date d;
        if (d.setYearMonthDay(year, month, day) {    // if valid value
            // ...
        }
        else {                                       // else invalid value
            // ...
        }
    }

But if we "know" the date is valid, we get two benefits:

(1) We don't have to check it ourselves (and we get the efficiency), and
(2) in the appropriate build mode, it will be checked automatically for us.

        Date d(1993, 9, 31);                        // caught in SAFE mode
        d.setYearMonthDay(1993, 9, 31);             // caught in SAFE mode

On the other hand, if we put checking directly into the contract then we check all the time -- whether we need to or not.  (I'm strongly opposed to that.)

If we were to make 'setYearMonthDay' return status like 'setYearMonthDayIfValid', then we would have a *wide* contract, and would not
be able to detect the bug in ANY build mode.

So to sumerize, some people want there pre-conditions checked (sometimes), and some don't.  This date facility is a general purpose library that will be used by all sorts of folks.  By not putting checking (let alone throwing) into the contract, we widen the applicability of this date type to accommodate EVERY CONCEVABLE APPLICATION.

Note that the notion of having a *narrow* contract that admits this kind of defensive programming is MUCH bigger than the date class, and was the basis
for our decision in Madrid NOT to decorate ANY narrow contracts with noexcept.

I would be very interested to know if this explaination makes you feel any differently about the non-instance 'isValid' method (which you need never use).

Cheers, John L.

- Afficher le texte des messages précédents -

...

plus de détails »

====================================
====================================



Daniel Krügler
====================================
   Autres options 24 août, 22:32
2011/8/24 JOHN LAKOS, BLOOMBERG/ 731 LEXIN <jla...@bloomberg.net>:

- Afficher le texte des messages précédents -

This would be a rather unique approach in the standard library
and of little robustness when used.

I would find the approach using an error_code object much more
appealing for your use case. First, the object in the call is immediately
alerting the user that this is a narrow contract function. Second, I
believe that the runtime cost of such a call with an error_code object
should be basically the same as your suggestion without. Third, the
information content in case of an error could drastically exceed
the bare correct-not correct reply of a boolean test.

> that avoids your having repeate the literal date value:

>       date d;
>       if (!d.setYearMonthDayIfValid(1993, 09, 31)) throw 'logic_error';
>       // ...

> Except that I would not throw here either.  The problem is that some inputs
> are known to be good, and some are not.  For those inputs that are known to
> be good, the extra if to check to see if the date is valid is not viable in
> many important practical contexts.  In finacial calculations in particular,
> the cost of the 'if' could make or break the system.

Why? If you have designed the function this way, there must already be
an implied if() branch *within* setYearMonthDayIfValid, otherwise the function
could not return the correct result. If the function would either just throw
instead of returning a "success/failure" result, the overhead should be the
same. If we add an overload with an error_code object, the user can ignore
the evaluation of that, or could put the evaluation within a maskable assert
to have the test conditionally active.

> That said, there are other
> situations in which checking is exacatly the right answer!  But we can't have
> it both ways!  Or can we?  As a matter of fact we can!

> By specifying that constructing or setting a date to an invalid value is UNDEFINED BEHAVIOR, we allow for the possibility of a robust implemenation to detect the error in a CHECKED BUILD MODE.  This new, very general proposed approach to "defensive programming done right" (paper in Kona) will allow the applciation developer to:

A date class looks like a wrong place for undefined behaviour to me,
especially because the construction or assignment will perform
the check internally anyway. Your suggestion simply prevents
the user to have robust code, because most people won't expect
the bool result and its meaning. This looks so much like non-C++
code to me, that I cannot accept it. I understand that user must
expect undefined behaviour in situations, where the test overhead
could much exceed the non-failure operation overhead (or is
impossible), but have not much sympathy for this strategy in case
of this date example.

>  (1) specify with some granularity how much checking should be done at
>     runtime: (a) none, (b) some, (c) lots, (d) go for it!, and

>  (2) excatly what should happen if a pre-condition violation is detected:
>     (a) abort, (b) throw, (c) spin, (d) <your desired behavior here>.

> But if we don't know that the date coming into a system is valid, we will
> not want to construct a date within a try block, because that is absurdly
> inneficent and clunky.

I have described an approach that would not require a try block.

- Afficher le texte des messages précédents -

Exactly, so use an error_code object and ignore it or don't.

This date facility is a general purpose library that will be used by
all sorts of folks.  By not putting checking (let alone throwing) into
the contract, we widen the applicability of this date type to
accommodate EVERY CONCEVABLE APPLICATION.

> Note that the notion of having a *narrow* contract that admits this kind of defensive programming is MUCH bigger than the date class, and was the basis
> for our decision in Madrid NOT to decorate ANY narrow contracts with noexcept.

> I would be very interested to know if this explaination makes you feel any differently about the non-instance 'isValid' method (which you need never use).

Unfortunately not, as I described above.

- Daniel

====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 25 août, 08:17

Il giorno 24/ago/2011, alle ore 22:06, JOHN LAKOS, BLOOMBERG/ 731 LEXIN ha scritto:

> By specifying that constructing or setting a date to an invalid value is UNDEFINED BEHAVIOR, we allow for the possibility of a robust implemenation to detect the error in a CHECKED BUILD MODE.  This new, very general proposed approach to "defensive programming done right" (paper in Kona) will allow the applciation developer to:

> (1) specify with some granularity how much checking should be done at
>     runtime: (a) none, (b) some, (c) lots, (d) go for it!, and

> (2) excatly what should happen if a pre-condition violation is detected:
>     (a) abort, (b) throw, (c) spin, (d) <your desired behavior here>.

I'm not convinced that going for undefined behaviour is good. It might occur that I need a specific behaviour in a piece of code and a different one in a separate TU of the same program. In large multi-developers projects you will eventually find two programmers that have different programming styles. I'd rather fully specify a few error policies to allow the user select them, for example like this:

----
struct no_check_t {};
struct validity_check_t {};
struct assert_if_invalid_t {};
struct throw_if_invalid_t {};

class date
{
  //...

  // notice: I have the same concerns as Nevin about the signature taking three ints,
  // but I keep it here for the time being for the sake of discussion

  bool setYearMonthDay(int, int, int, no_check_t); // always returns true
  bool setYearMonthDay(int, int, int, validity_check_t);
  bool setYearMonthDay(int, int, int, assert_if_invalid_t);
  bool setYearMonthDay(int, int, int, throw_if_invalid_t); // always returns true

  // any one of the above, in implementation-defined way (possibly according to a config macro)
  bool setYearMonthDay(int, int, int);

  // non-throwing, sets error code on error
  bool setYearMonthDay(int, int, int, std::error_code& ec);
};

----

Or even allow user-defined policies:

----
class date
{
  //...

  template <class Policy = DEFAULT_POLICY>
  bool setYearMonthDay(int, int, int, Policy = Policy{});

  template <> bool setYearMonthDay(int, int, int, no_check_t);
  template <> bool setYearMonthDay(int, int, int, validity_check_t);
  template <> bool setYearMonthDay(int, int, int, assert_if_invalid_t);
  template <> bool setYearMonthDay(int, int, int, throw_if_invalid_t);
  template <> bool setYearMonthDay(int, int, int, std::error_code& ec);
};

----

Just a thought. Not that I specifically endorse this approach.

Ganesh

====================================
====================================



Pablo Halpern
====================================
   Autres options 25 août, 16:25
On 8/24/2011 4:32 PM, Daniel Krügler wrote:

- Afficher le texte des messages précédents -

I think this makes sense.  Let me reprhase and see if I understand
correctly.  You are suggesting something
like:

       set year_month_day(int year, int month, int day);
       set year_month_day(int year, int month, int day, error_code& ec);

The second form is guaranteed error-checked.  The first is not.

If this is what you are saying, then you and John (and I) are
essentially in agreement.  The difference
is basically stylistic and if you think that the style above is more
consistent with the style of the
standard, then that's fine.

[...]

> A date class looks like a wrong place for undefined behaviour to me,
> especially because the construction or assignment will perform
> the check internally anyway. Your suggestion simply prevents
> the user to have robust code, because most people won't expect
> the bool result and its meaning. This looks so much like non-C++
> code to me, that I cannot accept it. I understand that user must
> expect undefined behaviour in situations, where the test overhead
> could much exceed the non-failure operation overhead (or is
> impossible), but have not much sympathy for this strategy in case
> of this date example.

Your argument is not convincing.  If an implementation chooses not to do
an inexpensive check, then that is a QOI issue.  The point is that, as a
general matter of principle, we should writing precondition checks into
the interface because:

1. The way to avoid undefined behavior is to SANITIZE YOUR INPUT.  That
goes for making sure that the date entered by a user is valid and that a
string entered by the user does not overflow your buffer.  The
validating constructor or is_valid call is there for exactly this
purpose.  Once a date is validated IT NEVER NEEDS TO BE VALIDATED
AGAIN.  Forced validation violates the "you pay for only what you use" rule.

2. A wide contract (one that includes precondition checks and a
guaranteed action in case the precondition fails) is difficult to change
in the future.  If, in the future, we want to ascribe a new meaning to a
specific invalid date (say, January 0, 0000), we would break the
contract, which says that we will THROW in this case.

3. The way to avoid undefined behavior is not to replace it with an
exception.   I have not seen in my career reasonable code that catches
exceptions as a generalized and robust way to handle bad input.  The
best I have seen is catching exceptions and shutting down gracefully.
For that to work well in general requires a general facility like the
kind that John will propose.

Even if precondition checks are cheap for date (because the conditionals
are already there), that is not sufficient reason to abandon the
principle.  As a matter of fact, however, you can write an unchecked
date constructor with NO CONDITIONALS AT ALL, as Bloomberg has demonstrated.

[...]

>> Note that the notion of having a *narrow* contract that admits this kind of defensive programming is MUCH bigger than the date class, and was the basis
>> for our decision in Madrid NOT to decorate ANY narrow contracts with noexcept.

>> I would be very interested to know if this explaination makes you feel any differently about the non-instance 'isValid' method (which you need never use).

> Unfortunately not, as I described above.

Actually, I think you two are converging.  The disagreement is on the
style of specifying the guaranteed-validating vs.
not-guaranteed-to-validate manipulator.  That is a disagreement on
style, not principle, and I'm sure that can be resolved.

-Pablo

====================================
====================================



Daniel Krügler
====================================
   Autres options 25 août, 16:32
2011/8/25 Pablo Halpern <phalp...@halpernwightsoftware.com>:

- Afficher le texte des messages précédents -

I'm not saying that. I'm suggesting that the first form would throw an
exception is case of input error, but the second form would not, instead
it would set the error code value. Whether you evaluate the error_code
or not, is your business.

>> A date class looks like a wrong place for undefined behaviour to me,
>> especially because the construction or assignment will perform
>> the check internally anyway. Your suggestion simply prevents
>> the user to have robust code, because most people won't expect
>> the bool result and its meaning. This looks so much like non-C++
>> code to me, that I cannot accept it. I understand that user must
>> expect undefined behaviour in situations, where the test overhead
>> could much exceed the non-failure operation overhead (or is
>> impossible), but have not much sympathy for this strategy in case
>> of this date example.

> Your argument is not convincing.  If an implementation chooses not to do an
> inexpensive check, then that is a QOI issue.  The point is that, as a
> general matter of principle, we should writing precondition checks into the
> interface because:

I don't get your concept of validation. If John's function has to
return true/false, this is also validation. I'm suggesting to provide
an overload with the error_code object. John could use this
and ignore the value of the error_code.

- Daniel

====================================
====================================



Pablo Halpern
====================================
   Autres options 25 août, 18:21
On 8/25/2011 10:32 AM, Daniel Krügler wrote:

- Afficher le texte des messages précédents -

But you then don't leave an option to not pay the cost of the check.
The precondition check
is in the interface in both cases.  That is an unacceptable cost for
checking for a condition
that a bug-free program will never see.
>>> A date class looks like a wrong place for undefined behaviour to me,
>>> especially because the construction or assignment will perform
>>> the check internally anyway. Your suggestion simply prevents
>>> the user to have robust code, because most people won't expect
>>> the bool result and its meaning. This looks so much like non-C++
>>> code to me, that I cannot accept it. I understand that user must
>>> expect undefined behaviour in situations, where the test overhead
>>> could much exceed the non-failure operation overhead (or is
>>> impossible), but have not much sympathy for this strategy in case
>>> of this date example.
>> Your argument is not convincing.  If an implementation chooses not to do an
>> inexpensive check, then that is a QOI issue.  The point is that, as a
>> general matter of principle, we should writing precondition checks into the

I meant we should *not* be writing precondition checks into the interface.
>> interface because:
> I don't get your concept of validation. If John's function has to
> return true/false, this is also validation. I'm suggesting to provide
> an overload with the error_code object. John could use this
> and ignore the value of the error_code.

Because John supplies both a checked and unchecked variant.  If you call
the unchecked variant, you don't pay the cost of the check.  I am happy
to have an overload with an error_code object, but only if it is the
*only* checked version.  The other version should not have precondition
checking in its interface.  It's just too expensive.  The C++ standard
is not about trying to do something "reasonable" in a buggy program.  If
you call the unchecked function, then you'd better be sure that the
preconditions hold.  Often, this is entirely possible, but when it's
not, you can use the checked version and look at the error code.

-Pablo

====================================
====================================



Howard Hinnant
====================================
   Autres options 25 août, 19:50
On Aug 25, 2011, at 12:21 PM, Pablo Halpern wrote:

> The precondition check
> is in the interface in both cases.  That is an unacceptable cost for checking for a condition
> that a bug-free program will never see.

Perhaps it is time to quantify this cost? 2%? 20%? 200%?

Howard

====================================
====================================



Ville Voutilainen
====================================
   Autres options 25 août, 20:26
On 25 August 2011 20:50, Howard Hinnant <howard.hinn...@gmail.com> wrote:

>> The precondition check
>> is in the interface in both cases.  That is an unacceptable cost for checking for a condition
>> that a bug-free program will never see.
> Perhaps it is time to quantify this cost? 2%? 20%? 200%?

It makes quite some sense to me to have a separate means of checking validity
and an interface that doesn't check, and the latter I can use without paying
a performance penalty. Reminds me of vector::at() vs. vector::operator[]().
I would very much prefer having that distinction, and go for undefined behavior
if you pass invalid data without checking. That combination seems to cater
for a wide variety of needs.

====================================
====================================



bs
====================================
   Autres options 25 août, 20:32
On 8/25/2011 2:26 PM, Ville Voutilainen wrote:

> On 25 August 2011 20:50, Howard Hinnant<howard.hinn...@gmail.com>  wrote:
>>> The precondition check
>>> is in the interface in both cases.  That is an unacceptable cost for checking for a condition
>>> that a bug-free program will never see.
>> Perhaps it is time to quantify this cost? 2%? 20%? 200%?
> It makes quite some sense to me to have a separate means of checking validity
> and an interface that doesn't check, and the latter I can use without paying
> a performance penalty. Reminds me of vector::at() vs. vector::operator[]().
> I would very much prefer having that distinction, and go for undefined behavior
> if you pass invalid data without checking. That combination seems to cater
> for a wide variety of needs.

*If* you provide a way of separating validation and construction, please
make sure that the checked interface is the notationally easier to use.
Having the checked interface (at()) uglier and less conventional than
the unchecked interface ([]) for vector was the result of for concerns
about generic programming and performance that I don't see  for dates.
For *most* lines of code a 10% overhead is unnoticeable and I suspect
that most uses of dates are in this category.

====================================
====================================



Ville Voutilainen
====================================
   Autres options 25 août, 20:36
On 25 August 2011 21:32, bs <b...@cs.tamu.edu> wrote:

> generic programming and performance that I don't see  for dates. For *most*
> lines of code a 10% overhead is unnoticeable and I suspect that most uses of
> dates are in this category.

I have had to do heavy processing of dates while interfacing with
databases. I can also
imagine the implementation of databases needing to do that in some cases. Having
a 10% overhead, if unavoidable, is downright shocking and frankly
unacceptable in
many cases.

====================================
====================================



bs
====================================
   Autres options 25 août, 20:38
On 8/25/2011 2:36 PM, Ville Voutilainen wrote:

> On 25 August 2011 21:32, bs<b...@cs.tamu.edu>  wrote:
>> generic programming and performance that I don't see  for dates. For *most*
>> lines of code a 10% overhead is unnoticeable and I suspect that most uses of
>> dates are in this category.
> I have had to do heavy processing of dates while interfacing with
> databases. I can also
> imagine the implementation of databases needing to do that in some cases. Having
> a 10% overhead, if unavoidable, is downright shocking and frankly
> unacceptable in
> many cases.

I don't doubt that and I know that "most" is always hard to quantify,
but it most certainly doesn't mean "all".

I picked that "10%" out of a hat. Howart's question is still unanswered.

====================================
====================================



Ville Voutilainen
====================================
   Autres options 25 août, 20:40
On 25 August 2011 21:38, bs <b...@cs.tamu.edu> wrote:

> I picked that "10%" out of a hat. Howart's question is still unanswered.

I'm not opposed to measuring it. I just wanted to point out why it's
desirable to
have the undefined behavior aka a non-checking interface, there are good reasons
to strive for such.

====================================
====================================



bs
====================================
   Autres options 25 août, 20:46
On 8/25/2011 2:40 PM, Ville Voutilainen wrote:

> On 25 August 2011 21:38, bs<b...@cs.tamu.edu>  wrote:
>> I picked that "10%" out of a hat. Howart's question is still unanswered.
> I'm not opposed to measuring it. I just wanted to point out why it's
> desirable to
> have the undefined behavior aka a non-checking interface, there are good reasons
> to strive for such.

If we have unchecked construction, we also need a (non-throwing)
validation function (is_date() is what I usually call it).

====================================
====================================



Nevin Liber
====================================
   Autres options 25 août, 20:48
[Still waiting for Nico to join the list...]

On 25 August 2011 13:26, Ville Voutilainen <ville.voutilai...@gmail.com> wrote:

> It makes quite some sense to me to have a separate means of checking validity
> and an interface that doesn't check, and the latter I can use without paying
> a performance penalty.

I agree with that.

> Reminds me of vector::at() vs. vector::operator[]().
> I would very much prefer having that distinction, and go for undefined behavior
> if you pass invalid data without checking. That combination seems to cater
> for a wide variety of needs.

Actually, I think the check in vector::at is almost useless, as most
indexing errors are due to programming bugs (so should be asserts),
and the few that aren't are quite easily to check for externally with
i < v.size().  We need a way to check for validity, although I'm not
sure if that should be an external function returning a bool or
another constructor that throws on failure (or both).
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



Nevin Liber
====================================
   Autres options 25 août, 21:14
On 25 August 2011 13:48, Nevin Liber <ne...@eviloverlord.com> wrote:
We need a way to check for validity, although I'm not

> sure if that should be an external function returning a bool or
> another constructor that throws on failure (or both).

Another alternative: a pair of free functions:

bool is_valid_date(year y, month m, day d); // returns true if and
only if y-m-d represents a valid date
date make_valid_date(year y, month m, day d); // throws if and only if
is_valid_date(y, m, d) would return false

For completeness (I'm not advocating this), we could also have two
date classes; one checked and one unchecked and conversions between
them.
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



JOHN LAKOS, BLOOMBERG/ 731 LEXIN
====================================
   Autres options 25 août, 21:15
Hi all,

I want to let you know that I met with my team today, and we will be
incorporating the "cost of checking" into the benchmarks we will be doing
on Howards and our date classes.  I do want to point out that making checking
part of the contract will absolutely imply additional cost and/or dictate
which implementation we choose.  For example, if the imp were just three fields

    unsigned short d_year;
    unsigned char  d_month;
    unsigned char  d_day;

then the cost of checking would *completely* *dominate* the set and get operations.

In response to various other comments so far...

I am completely opposed to *any* sort of test to see if a date holds a valid
value.  A date always holds a valid value (invariant of the class); this
invariant is guarded by preconditions (and not necessarily code).  Otherwise
we would be re-checking a date for validity before each use (BAD).   By keeping
our contracts narrow, a single date class can be used effectively by everyone,
which is important for interoperability.

C++ has as one of its central goals not to make people pay for something they
don't need/want.  Imposing checking on all users of date would violate this
principle.  Some languages favor safety over speed.  C++ does not.  The C++
language is full of undefined behaivors; attempting to write a "safe but slow" library is simply wrong minded for C++.

Adopting a more general solution (which allows for a checked build mode, and
what to do if a logic error is encountered -- TBD in Kona) will help us in forming the interfaces to the apparently large set of new value-semantic classes we are now about to consider.  And arguments like "most people won't care about the performance" are not compelling for most values of "most" :-@)

We need to make sure that this important vocabulary type is used ubiquitously to avoid compromising interoperability.  Again, this is why we were careful
*NEVER* to decorate narrow contracts with 'noexcept' in Madrid!

                                                            -John L.

- Afficher le texte des messages précédents -


====================================
====================================



JOHN LAKOS, BLOOMBERG/ 731 LEXIN
====================================
   Autres options 25 août, 21:31
Nevin,

Two date classes is simply out of the question!  We need a common vocabulary type here.  I realize you did not advocate it, but I hope you
appreciate the tremendous downside to having to convert between date types all over the place.  In fact, we at Bloomberg have gone out of our way to make sure to have just one date type, rather than both "year-month-day" and "serial-date" implementations, and we achieve the best of both using a 64k bidirectional static lookup table between the two representations.

Separately, I still don't understand this obsession with exceptions, when an optional return status get's the job done.

    class Date {
        // ...
      public:
        // ...
        void setYearMonthDay(int year, int month, int day);
            // Undefined if not a valid date value.

        bool setYearMonthDayIfValid(int year, int month, int day);
            // Returns 'true' on success, and 'false' with no effect otherwise.

        // Addid Just for Nevin...
        void setyearMonthDay(Year year, Month month, Day day);
            // Undefined if not a valid date value.

        bool setYearMonthDayIfValid(Year year, Month month, Day day);
            // Returns 'true' on success, and 'false' with no effect otherwise.
    };

BTW, we will be benchmarking a variety of approaches over the coming weeks...

                                            Cheers, John L.

- Masquer le texte des messages précédents -

----- Original Message -----
From: kona-date-lib@googlegroups.com
To: kona-date-lib@googlegroups.com, n...@josuttis.de

At:  8/25 15:15:14

On 25 August 2011 13:48, Nevin Liber <ne...@eviloverlord.com> wrote:
We need a way to check for validity, although I'm not
> sure if that should be an external function returning a bool or
> another constructor that throws on failure (or both).

Another alternative: a pair of free functions:

bool is_valid_date(year y, month m, day d); // returns true if and
only if y-m-d represents a valid date
date make_valid_date(year y, month m, day d); // throws if and only if
is_valid_date(y, m, d) would return false

For completeness (I'm not advocating this), we could also have two
date classes; one checked and one unchecked and conversions between
them.
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

--
You received this message because you are subscribed to the Google Groups "Kona-date-lib" group.
To post to this group, send email to kona-date-lib@googlegroups.com.
To unsubscribe from this group, send email to kona-date-lib+unsubscribe@googlegroups.com.
For more options, visit this group at http://groups.google.com/group/kona-date-lib?hl=en.


Nevin Liber
====================================
   Autres options 25 août, 21:40
On 25 August 2011 14:15, JOHN LAKOS, BLOOMBERG/ 731 LEXIN

<jla...@bloomberg.net> wrote:
> I am completely opposed to *any* sort of test to see if a date holds a valid
> value.

What we need is a way to validate the inputs to creating a date
*before* it gets constructed.  You are not opposed to that, correct?

> Adopting a more general solution (which allows for a checked build mode, and
> what to do if a logic error is encountered

It isn't about logic errors.  Dates come from a variety of sources
that are not under programmer control (users, networks, etc.) and we
need a way to know those inputs won't violate the class invariants.
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



Ville Voutilainen
====================================
   Autres options 25 août, 21:42
On 25 August 2011 22:40, Nevin Liber <ne...@eviloverlord.com> wrote:

> What we need is a way to validate the inputs to creating a date
> *before* it gets constructed.  You are not opposed to that, correct?

See the first mail/post by John.

+ Non-instance method: bool isValidYearMonthDay(int, int, int);

====================================
====================================



Nevin Liber
Afficher le profil
   Autres options 25 août, 21:47
On 25 August 2011 14:31, JOHN LAKOS, BLOOMBERG/ 731 LEXIN

<jla...@bloomberg.net> wrote:
>    class Date {
>        // ...
>      public:
>        // ...
>        void setYearMonthDay(int year, int month, int day);
>            // Undefined if not a valid date value.

Is there a default constructor?  If so, it must create a valid date,
or we are already off in undefined behavior land, and too late to call
member functions on it.

Of course, people are going to use that date as the epoch (which you
didn't want mentioned).

>        bool setYearMonthDayIfValid(Year year, Month month, Day day);
>            // Returns 'true' on success, and 'false' with no effect otherwise.

I want a way to validate before construction, not a more expensive
construct a dummy, validate and set.  I much prefer to use
construction and assignment instead of setters.
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



JOHN LAKOS, BLOOMBERG/ 731 LEXIN
====================================
   Autres options 25 août, 22:00
Nevin,

>On 25 August 2011 14:15, JOHN LAKOS, BLOOMBERG/ 731 LEXIN
><jla...@bloomberg.net> wrote:
>> I am completely opposed to *any* sort of test to see if a date holds a valid
>> value.

>What we need is a way to validate the inputs to creating a date
>*before* it gets constructed.  You are not opposed to that, correct?

I am absolutely fine with that; having a non-instance method

    static bool isValidYearMonthDay(int year, int month, int day);

is what we have.  If you want to avoid specifying the arguments
twice (and also doing the calculations twice) you set a pre-existing
date (which can be reused):

    Date d;
    if (d.setYearMonthDay(year, month, day)) {
        // good
    }
    else {
        // bad
    }

but if you know the date is good, just say

    d.setYearMonthDay(year, month, day);  // bad date value caught in checked
                                          // build, else undefined behavior.
or

    Date dd(year, month, day);    // bad date vallue caught in checked build, el
                                  // else undefined behavior.

>> Adopting a more general solution (which allows for a checked build mode, and
>> what to do if a logic error is encountered

>It isn't about logic errors.  Dates come from a variety of sources
>that are not under programmer control (users, networks, etc.) and we
>need a way to know those inputs won't violate the class invariants.

I completely agree that we need to validate raw data before creating objects with preconditions protecting invariants.  Once I know I have a valid date,
I don't (or sometimes may not) want to pay to check it each time.  This is
not what C++ is about; it truly is a language for people who want to squeeze
every drop of speed out of the platform.  But it's not just speed.  As Pablo
said, narrow contracts allow for new behaviors to be added if appropriate,
whereas wide ones do not.  IMO, a good design here is to allow narrow contracts
with preconditions that guard invariants checked in a "SAFE" build mode.
                                                               -John L.
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

- Afficher le texte des messages précédents -


====================================
====================================



Howard Hinnant
====================================
   Autres options 25 août, 22:22
On Aug 25, 2011, at 3:15 PM, JOHN LAKOS, BLOOMBERG/ 731 LEXIN wrote:

> I do want to point out that making checking
> part of the contract will absolutely imply additional cost and/or dictate
> which implementation we choose.  For example, if the imp were just three fields

>    unsigned short d_year;
>    unsigned char  d_month;
>    unsigned char  d_day;

> then the cost of checking would *completely* *dominate* the set and get operations.

I'm lacking John's 64Kb lookup table.  But I'm really anxious to get people hacking instead of yacking. :-)  Here's my engine, simplified down, with and without checking.  Everyone can run it by copy/pasting into their own environment (you might have to hack a substitute timer if you don't have a <chrono> yet).  My table is only 104 bytes, so this is probably 64000/104 times slower than John's. :-)  (actually the harder part is going from count back to ydm)

#include <cstdint>
#include <cassert>

class date
{
    std::uint32_t x_;
public:
    date(int year, int month, int day);

    std::uint32_t count() const {return x_;}

};

static
const int
db[2][13] = {{-1, 30, 58, 89, 119, 150, 180, 211, 242, 272, 303, 333, 364},
             {-1, 30, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365}};

static
inline
bool
is_leap(int y) noexcept
{
    return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);

}

date::date(int y, int m, int d)
{
    assert(-32768 <= y && y <= 32767);
    assert(1 <= m && m <= 12);
    const int* year_data = db[is_leap(y)];
    assert(1 <= d && d <= year_data[m] - year_data[m-1]);
    std::int32_t by = y + 32799;
    x_ = by*365 + by/4 - by/100 + by/400 + year_data[m-1] + d;

}

#include <chrono>
#include <iostream>

int main()
{
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::duration<double> sec;
    Clock::time_point t0 = Clock::now();
    std::uint64_t x = 0;
    std::uint64_t n = 0;
    std::error_code ec;
    for (int y = -8000; y <= 10000; ++y)
    {
        for (int m = 1; m <= 12; ++m)
        {
            for (int d = 1; d <= 28; ++d)
            {
                date dt(y, m, d);
                x += dt.count();
                ++n;
            }
        }
    }
    Clock::time_point t1 = Clock::now();
    std::cout << n/sec(t1-t0).count() << " date constructions / second\n";
    return x;

}

This simply constructs a date from ymd (int specified) and transforms that triplet into a 32 bit day counter.  I put a count() member function on the date only because the optimizer kept optimizing away what I was trying to measure!

The most bogus part of this test is that it is *only* timing construction (with and without testing depending on -DNDEBUG).  Imho a better test would include representative date manipulation.  It does little good just to construct a date if you aren't going to do anything with it.  But anyway, I throw this out in the hopes that someone might take it and turn it into a better test.  See http://home.roadrunner.com/~hinnant/bloomington/date.cpp if you want my code for turning count back into ymd.  Or maybe you can show your engine is faster! :-)

As it stands this outputs for me:

9.24503e+08 date constructions / second
(-DNDEBUG)

and

1.28118e+08 date constructions / second

Both are median of 3 and compiled using clang++ -O3.  These numbers indicate construction is a little over 7 times more expensive when checked.

These numbers will obviously vary with many decisions, including storage (as John said), and the ymd/count conversion algorithm.

I also note that sometimes date components will be known at compile time and thus can be checked at compile time (or be known to not need checking).  For example there is no need to range-check the month in date(2011, aug, 25).  And I am unclear if and how constexpr might help here.

But as it stands above, I find 7x sufficiently motivating for a non-checked interface (in addition to a checked interface).

Straw-man:

date unchecked(2011, aug, 25);
date checked = year(2011)/aug/25;

?

:-)

Howard

====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 26 août, 08:26

Il giorno 25/ago/2011, alle ore 21:31, JOHN LAKOS, BLOOMBERG/ 731 LEXIN ha scritto:

- Afficher le texte des messages précédents -

I still haven't received any feedback about my proposal of having custom validators, which would solve the above problem nicely, IMHO, providing even more flexibility without duplicating the signatures . Here's an updated version of it:

template <class T>
struct date_validator_traits;

struct no_check_t {} const no_check;
struct check_validity_t {} const check_validity;
struct throw_if_invalid_t {} const throw_if_invalid;

class date
{
public:
        template <class Validator = DEFAULT_VALIDATOR_TYPE>
        bool set_ymd(int year, int month, int day, Validator& v = DEFAULT_VALIDATOR)
        {
                if (date_validator_traits<Validator>::validate(year, month, day, v))
                {
                        // actually set ymd here
                        return true;
                }
                else
                {
                        return false;
                }
        }

};

by suitably specializing date_validator_traits we can have all behaviors we want as well as providing an extension point for the user. For example:

template <>
struct date_validator_traits<const no_check_t>
{
        static bool validate(int year, int month, int day, const no_check_t& v)
        {
                return true;
        }

};

template <>
struct date_validator_traits<const check_validity_t >
{
        static bool validate(int year, int month, int day, const check_validity_t& v)
        {
                return is_valid_ymd(year, month, day);
        }

};

template <>
struct date_validator_traits<const throw_if_invalid_t >
{
        static bool validate(int year, int month, int day, const throw_if_invalid_t& v)
        {
                if (!is_valid_ymd(year, month, day))
                        throw std::invalid_argument("not a date");
                return true;
        }

};

template <>
struct date_validator_traits<std::error_code>
{
        static bool validate(int year, int month, int day, std::error_code& ec)
        {
                if (!is_valid_ymd(year, month, day))
                {
                        // set error code in ec;
                        return false;
                }
                return true;
        }

};

int main()
{
        date dt;

        dt.set_ymd(2011, 8, 26); // uses default validator, whatever that is

        dt.set_ymd(2011, 8, 26, throw_if_invalid); // no need to check the result

        if (not dt.set_ymd(2011, 8, 26, check_validity))
        {
                // date is invalid
        }

        std::error_code ec;
        if (!dt.set_ymd(2011, 8, 26, ec))
        {
                // date is invalid and ec contains suitable error code
        }

}

---

This approach might seem to introduce a little overhead in the no_check case, but a reasonably optimizing compiler is able to remove all tests and inline all calls (Clang is able to do that, for example) making such overhead negligible if not even null.

Ganesh

====================================
====================================



Howard Hinnant
====================================
   Autres options 29 août, 01:28

On Aug 26, 2011, at 2:26 AM, Alberto Ganesh Barbati wrote:

- Afficher le texte des messages précédents -

I've been experimenting with a subset of Ganesh's proposal, but in a more-fine grained way than he intended.  The subset I'm experimenting with is just no_check.  I'm only playing with no_check because it is faster to play with just this subset.  It could easily be expanded to his other tags if this pans out.  The more-fine grained part is due to an observation that I'm often forming a new day from a ymd spec where I know only that one or two of year, month or day need not be checked.

For example if I know that my month is in range, but can't prove my year and day are in range I might:

    date d(year(y), month(m, no_check), day(d));

I've been going over the algorithms in my proposal and am finding this fine-grained no_check placement useful.  For example when I add a month to a date:

date&
date::operator+=(months mn)
{
    Int32_t y = y_;
    Int32_t m = m_;
    m += mn.x_;
    if (m < 1)
    {
        int dy = (12 - m) / 12;
        y -= dy;
        m += 12 * dy;
    }
    else if (m > 12)
    {
        int dy = (m - 1) / 12;
        y += dy;
        m -= 12 * dy;
    }
    *this = date(chrono::year(y), chrono::month(m, no_check),
                 chrono::day(d_, n_, dow_));
    return *this;

}

I can visually inspect the code and prove to myself that on the last line where I assign this date a new date that m will always be in the range [1, 12].  And so I tag the chrono::month constructor with no_check which bypasses (at compile time) all range checking for the month.  But I have no such assurances for the year (which may have wandered outside of [-32768, 32767]), or day, (which though it hasn't been changed, may now be invalid for the new month and year).

<aside>
My proposal still has things people really don't like, such as month addition as an operator+= of date.  Please ignore this for now.  I'm experimenting with what I have handy.  I'm not stubbornly pushing what a majority has made clear it doesn't like.  Imagine this is a namespace scope function instead of a member of date, and doesn't encode nth day-of-week into day.
</aside>

Year and month can be range checked in isolation.  Day can not.  So the day can not be range checked except in the date constructor.  Here is how I'm prototyping checking only the day, but not the year and month:

    date d(year(y), month(m), day(d), no_check);

And here is my current prototype for not checking anything:

    date d(year(y, no_check), month(m, no_check), day(d), no_check);

Quite verbose!  But again, this follows from the fact that when you say year(y), or month(m), you can check y and m at that point.  And then you never need to check copies of those objects again.  Including if you copy them out of another date:

   date d2(d.year(), d.month(), day(d.day()+1));  // year and month are not checked, only day is

This is not a fully thought out proposal!  This is an exploration of Ganesh's interesting suggestion - complete with prototyping which includes illustrative uses of no_check.  Perhaps it will inspire yet another evolution from someone else?

Howard

      date
25K Afficher Télécharger

      date.cpp
16K Afficher Télécharger


====================================
====================================



bs
====================================
   Autres options 29 août, 03:00

On 8/28/2011 6:28 PM, Howard Hinnant wrote:

I like the idea, provided
     (1) the default is "validated" (throwing) and
     (2) "validated" and "no checking" is specializations so that we
don't have overhead in those cases

What would be a user-provided case? (i.e., ar ewe overabstracting by
providing a general argument?)

- Afficher le texte des messages précédents -


====================================
====================================



Howard Hinnant
====================================
   Autres options 29 août, 03:39
On Aug 28, 2011, at 9:00 PM, bs wrote:

> On 8/28/2011 6:28 PM, Howard Hinnant wrote:

> I like the idea, provided
>     (1) the default is "validated" (throwing) and
>     (2) "validated" and "no checking" is specializations so that we don't have overhead in those cases

In my prototype I am throwing when not no_check and input is invalid.  If we generalized the tag, other options could be provided (e.g. assert).

As it turns out  "validated" and "no checking" are overloads.  For example:

class month
{
    UInt8_t m_;
public:
    explicit month(int m)
        : m_(m)
    {
        if (!(1 <= m && m <= 12))
            throw bad_date("month " + std::to_string(m) + " is out of range");
    }

    month(int m, no_check_t)
        : m_(m) {}
// ...

};

but the effect is the same:  no overhead when you ask for no_check.

> What would be a user-provided case? (i.e., ar ewe overabstracting by providing a general argument?)

I'm not understanding the question.  Could you elaborate?

Thanks,
Howard

====================================
====================================



bs
====================================
   Autres options 29 août, 04:13
On 8/28/2011 8:39 PM, Howard Hinnant wrote:

- Afficher le texte des messages précédents -

I can think of three cases:
     (1) validate and throw
     (2) validate and set invalid flag (for people who can't use exceptions)
     (3) don't validate
Can anyone think of a fourth case? (I can, of course, but I'm not sure
the alternatives are real)

====================================
====================================



Alisdair Meredith
====================================
   Autres options 29 août, 04:18
On 28Aug, 2011, at 10:13 PM, bs wrote:

> I can think of three cases:
>    (1) validate and throw
>    (2) validate and set invalid flag (for people who can't use exceptions)
>    (3) don't validate
> Can anyone think of a fourth case? (I can, of course, but I'm not sure the alternatives are real)

Do you picture asserting as a form of validation in this picture, assumed under the "no validation" heading, or is that a 4th?

AlisdairM

====================================
====================================



Howard Hinnant
====================================
   Autres options 29 août, 04:26
On Aug 28, 2011, at 10:13 PM, bs wrote:

- Afficher le texte des messages précédents -

If I'm understanding correctly, such choices could be provided by more overloads, e.g:

class month
{
    UInt8_t m_;
public:
    explicit month(int m)
        : m_(m)
    {
        if (!is_valid())
            throw bad_date("month " + std::to_string(m) + " is out of range");
    }

    month(int m, no_check_t)
        : m_(m) {}

    month(int m, assert_t)
        : m_(m)
    {
        assert(is_valid());
    }

    bool is_valid() const {return 1 <= m_ && m_ <= 12;}

    // ...

};

Howard

====================================
====================================



Daniel Krügler
====================================
   Autres options 29 août, 07:06
2011/8/29 bs <b...@cs.tamu.edu>:

> On 8/28/2011 8:39 PM, Howard Hinnant wrote:

>> On Aug 28, 2011, at 9:00 PM, bs wrote:

>>> On 8/28/2011 6:28 PM, Howard Hinnant wrote:

>>> I like the idea, provided
>>>     (1) the default is "validated" (throwing) and
>>>     (2) "validated" and "no checking" is specializations so that we don't
>>> have overhead in those cases

I agree, but I don't think that you need specializations to realize what
(2) intends to realize.

- Afficher le texte des messages précédents -

Yes, that makes sense to me.

>>> What would be a user-provided case? (i.e., ar ewe overabstracting by
>>> providing a general argument?)

>> I'm not understanding the question.  Could you elaborate?

> I can think of three cases:
>    (1) validate and throw
>    (2) validate and set invalid flag (for people who can't use exceptions)
>    (3) don't validate
> Can anyone think of a fourth case? (I can, of course, but I'm not sure the
> alternatives are real)

IMO the three choices are good enough, especially since we have already
a nice new error diagnostic parallel to exceptions.

- Daniel

====================================
====================================



JOHN LAKOS, BLOOMBERG/ 731 LEXIN
====================================
   Autres options 29 août, 08:33
Hi all,

There is something *much* bigger here than allowing each individual programmer to control what happens when he/she makes a coding error and calls a library function *out* *of* *contract*.  That is a logic error -- i.e., a coding bug.

The immediate client of a library facility should be empowered with suitable tools for the job at hand -- i.e., checking and non-checking forms of the
date setter methods, and also a non-instance method to pre-check the valididity
of a date value, before an object is created.  The checking versions are essential when the value is not "known" to be valid, e.g., because it is raw input.  (Note that an existing date can be used to prevent supplying the
date fields twice.)

BUT!!!!  When the value is "known" to be valid, the setter method of choice is
absolutly the one where *no* *checking* is performed as part of the contract, and the function returns void; in a "SAFE" build, however, it does WHATEVER the owner of main wants it to do if it turns out not to be valid.

Making this approach work is much, much bigger than just 'Date', and we are proposing to introduce a general assertion facility that allows for "defensive programming done right" in C++, including "course levels of runtime checking" and an "Oh Darn" handler that does whatever should be done (according to the applciation owner) if a logic error occurs anywhere within the program.

This facility is beyond the scope of individual contracts for components,
and becomes a library-wide understanding of how much checking is to be
done at runtime (without being specific in each component contract) and what should happen -- abort, throw, spin, or something else, if a pre-condition violation is detected.

In order for this approach to work, however, we need to allow some functions
to have less then fully specified (i.e., undefined) behavior -- also known
as a *narrow* contract.  As much as some will not like me for saying it, Undefined Behavior is the right choice for some conctracts: It keeps our options open now (depending on build mode), and in the future (when we know better).

Conclusion: We need exactly two kinds of setter method: (1) unchecked (returning void), which is checked in a "Safe" build, and does what the owner of main said to do on a logic error, and (2) a check method (with a name that makes it clear we are returning a status) that returns status and on failure has no effect.

Again, this fully baked "defensive programming" approach is part of a much bigger picture that would apply across the board, and that we plan to present in detail in Kona.

Note that it has the decided advantage of being all things to all people
in that the application owner configures (1) how much runtime to spend
checking for logic erros, and (2) exactly what to do if such a logic error
is encounered.  It just doesn't get better than that!

                                                   -John L.

p.s., I'm late and it's tired, so please forgive spelling, and other typo's ;-)

- Afficher le texte des messages précédents -


====================================
====================================



Nevin Liber
====================================
   Autres options 29 août, 09:32
On 29 August 2011 01:33, JOHN LAKOS, BLOOMBERG/ 731 LEXIN

<jla...@bloomberg.net> wrote:
> In order for this approach to work, however, we need to allow some functions
> to have less then fully specified (i.e., undefined) behavior -- also known
> as a *narrow* contract.  As much as some will not like me for saying it, Undefined Behavior is the right choice for some conctracts: It keeps our options open now (depending on build mode), and in the future (when we know better).

I agree with this.  To add perspective from a user point of view, UB
means "don't go there"; fully specifying behavior in many situations
leads to software that is much more difficult to reason about (since
we've granted a license for users to go there even though we really
don't want them to).

> Conclusion: We need exactly two kinds of setter method: (1) unchecked (returning void), which is checked in a "Safe" build, and does what the owner of main said to do on a logic error, and (2) a check method (with a name that makes it clear we are returning a status) that returns status and on failure has no effect.

While I really do agree with the general gist of this, I really don't
like the whole setter method paradigm (which I believe is orthogonal
to the idea behind wide and narrow contracts).  Construction and
assignment are the fundamental building blocks of C++ objects.  I find
it very clunky to create a dummy object and then set its value.  And
if I want to reset a value, assignment is a perfectly good way of
writing that.

I see three cases:

1.  Create an object quickly because I the programmer "know" the
parameters are valid
2.  Check the parameters before creation of the object
3.  Check the parameters during creation of the object

(and one more case not applicable to Date; namely, what to do if
object creation fails for an external reason, such as out of memory.)

I agree that I would use a non-instance function for (2), but there
are many different ways to write (3) depending on the circumstances
(different constructor, non-instance function returning a fully
constructed object, setter method, etc.).

> Again, this fully baked "defensive programming" approach is part of a much bigger picture that would apply across the board, and that we plan to present in detail in Kona.

But we are designing a date library here, not a date library that
meets the interface of some as yet unseen let alone unadopted
assertion facility.  The insights regarding narrow vs. wide contracts,
UB, etc., are appropriate (and very valuable) input to the design.  I
find these syntactic considerations far less so.
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 29 août, 09:33

Il giorno 29/ago/2011, alle ore 07:06, Daniel Krügler ha scritto:

> 2011/8/29 bs <b...@cs.tamu.edu>:
>> On 8/28/2011 8:39 PM, Howard Hinnant wrote:

>>> On Aug 28, 2011, at 9:00 PM, bs wrote:

>>>> On 8/28/2011 6:28 PM, Howard Hinnant wrote:

>>>> I like the idea, provided
>>>>     (1) the default is "validated" (throwing) and
>>>>     (2) "validated" and "no checking" is specializations so that we don't
>>>> have overhead in those cases

> I agree, but I don't think that you need specializations to realize what
> (2) intends to realize.

My experiments with Clang shows that you don't need to use specialization to avoid overhead. However, I am not opposed to specializations. Having specializations have the advantage that you can have the no_check_t version return void. (In my proposal all functions return a bool). However, having them all return a bool can useful in generic code:

template <class Validator>
void accept_date(Validator v)
{
        int y, m, d;
        read_from_user(y, m, d);
        date dt;
        if (dt.set_ymd(y, m, d, v))
        {
                // date is good or assumed to be good
        }
        else
        {
                // date is bad
        }

}

If set_ymd always returns a bool, this code work even if Validator is no_check_t (in that case, it is the programmer responsibility to ensure that read_from_user returns validated input). Whether we want to support this use-case or not is open to discussion.

>>>> What would be a user-provided case? (i.e., ar ewe overabstracting by
>>>> providing a general argument?)

>>> I'm not understanding the question.  Could you elaborate?

I believe Bjarne was referring to my statement about having user-defined validators. I was thinking about allowing the programmer to have validators such has "a valid date in the future" or "a valid date in a range". By packaging such validators in a function object you could use them in generic code as in the example above. However, I agree that this might be over-engineering: it's probably easier to convert ymd to a valid date first and then use the date facilities to implement more advanced checking.

Another user-validator scenario is to allow the user to include custom assertion code. This scenario might be covered as soon as we have a comprehensive assertion infrastructure as suggested by John.

>> I can think of three cases:
>>    (1) validate and throw
>>    (2) validate and set invalid flag (for people who can't use exceptions)
>>    (3) don't validate
>> Can anyone think of a fourth case? (I can, of course, but I'm not sure the
>> alternatives are real)

> IMO the three choices are good enough, especially since we have already
> a nice new error diagnostic parallel to exceptions.

I'd like to have a debug validator also that would perform an assert in debug builds and a no-check in release builds. Of course, this could also be made the default behaviour of the no-check validator.

Ganesh

====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 29 août, 09:57

Il giorno 29/ago/2011, alle ore 09:32, Nevin Liber ha scritto:

- Afficher le texte des messages précédents -

I definitely agree with Nevin. However, the main problem is that constructors can't return failure without either throwing or introducing a not-a-date valid. John (please correct me if I interpreted you wrongly) has expressed distaste for both these approaches. However, I believe implementing a not-a-date value has several advantages without introducing unwanted overhead. Consider this internal structure, suggested by Nevin:

union DateImpl
{
   struct
   {
       uint16_t year;
       uint8_t  month;
       uint8_t  day;
   };
   uint32_t fast_comparisons;

};

and have a constructor like:

date(int y, int m, int d, no_throw_validate_t)
{
    if (is_valid_ymd(y, m, d))
    {
       impl.year = y; imp.month = m; impl.day = d;
    }
    else
    {
       fast_comparison = 0;
    }

}

and a contextual conversion to bool:

explicit operator bool() const
{
        return fast_comparison;

}

then you could write:

if (date d = date(y, m, d, no_throw_validate))
{
    // date d is constructed and valid
}

else
{
   // date is invalid

}

The no-overhead guarantee can be achieved by stating that any other use of a not-a-date valid except the contextual conversion to bool and assignment-to are UB. We might even decide to have the default constructor leave the date uninitialized for performance reasons.

> I see three cases:

> 1.  Create an object quickly because I the programmer "know" the
> parameters are valid

Ok. This could be

  date d(y, m, d, no_check);

> 2.  Check the parameters before creation of the object
> 3.  Check the parameters during creation of the object

I wish we could avoid 2, as I believe we could have validated creation as cheap as validate params+creation. Once I have checked the parameters and found them to be valid, I will probably need to create a date object right away, but if checking the parameters in advance has no benefit we would make things simpler.

Ganesh

====================================
====================================



Ville Voutilainen
====================================
   Autres options 29 août, 10:06
On 29 August 2011 10:57, Alberto Ganesh Barbati <gan...@barbati.net> wrote:

> I definitely agree with Nevin. However, the main problem is that constructors can't return failure without either throwing or introducing a not-a-date valid.

Well, for constructors it would seem natural to me that you get either
UB or an exception. If you want to check whether a date
can be constructed from whatever bits (ints, Day/Month/Year), I'd
expect us to need a non-constructor for that. Trying to
get non-throwing/non-UB constructor doesn't seem worth the trouble.
And if we have non-constructor validation, we don't
need not-a-date. That also allows the implementation of Date to not
care about checking not-a-date everywhere, which
seems rather fundamental.

====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 29 août, 13:12
Il 8/29/2011 10:06 AM, Ville Voutilainen ha scritto:
> On 29 August 2011 10:57, Alberto Ganesh Barbati <gan...@barbati.net> wrote:
>> I definitely agree with Nevin. However, the main problem is that constructors can't return failure without either throwing or introducing a not-a-date valid.
> Well, for constructors it would seem natural to me that you get either
> UB or an exception. If you want to check whether a date
> can be constructed from whatever bits (ints, Day/Month/Year), I'd
> expect us to need a non-constructor for that. Trying to
> get non-throwing/non-UB constructor doesn't seem worth the trouble.

I don't see what "trouble" your are talking about. Could you please
elaborate?
> And if we have non-constructor validation, we don't
> need not-a-date.

How would you write such non-constructor? How would it return a failure?
> That also allows the implementation of Date to not
> care about checking not-a-date everywhere, which
> seems rather fundamental.

As I said, *no* member function except the contextual conversion to bool
needs to check a not-a-date value. Accessing a not-a-date is UB.

It is somehow incorrect to say that a non-throwing validating
constructor is non-UB. See it this way: UB is deferred to the first use
of the constructed object and you get the chance to detect invalidity
before UB is triggered.

Ganesh

====================================
====================================



Alisdair Meredith
====================================
   Autres options 29 août, 13:30

On 29 Aug 2011, at 07:12, Alberto Ganesh Barbati wrote:

> As I said, *no* member function except the contextual conversion to bool
> needs to check a not-a-date value. Accessing a not-a-date is UB.

> It is somehow incorrect to say that a non-throwing validating
> constructor is non-UB. See it this way: UB is deferred to the first use
> of the constructed object and you get the chance to detect invalidity
> before UB is triggered.

What can I do with your proposed "not a date" value, if it is undefined behavior to access it?

Is it defined behavior to copy a Not-a-Date value, e.g. if a function takes arguments by value?

My big concern is that by deferring the UB past the point of date-object construction, you are deferring it past the point where it is most easily checked.

We now have a 'valid' object running through our system, with pre-conditions on most of its members that it not hold the not-a-date value.  Many functions taking dates must document the requirement that they are not passed the 'not a date' value, or must widen their contracts to check for this, and then define some error handling policy (which must be tested for, increasing the state-space that calling functions must be aware of, increasing the complexity of the whole program).

Deferring UB past the point of construction is a bad way to introduce UB into library contracts - and still forces the potentially expensive checking onto the constructor as well.  This appears to be a "worst of both worlds" solution - we gain the cost of checking, and pay an additional price for pushing UB deeper into the system.

AlisdairM

====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 29 août, 13:51

Il giorno 29/ago/2011, alle ore 13:30, Alisdair Meredith ha scritto:

> On 29 Aug 2011, at 07:12, Alberto Ganesh Barbati wrote:

>> As I said, *no* member function except the contextual conversion to bool
>> needs to check a not-a-date value. Accessing a not-a-date is UB.

>> It is somehow incorrect to say that a non-throwing validating
>> constructor is non-UB. See it this way: UB is deferred to the first use
>> of the constructed object and you get the chance to detect invalidity
>> before UB is triggered.

> What can I do with your proposed "not a date" value, if it is undefined behavior to access it?

You can check the presence of a not-a-date using the contextual conversion to bool or possibly a member function.

> Is it defined behavior to copy a Not-a-Date value, e.g. if a function takes arguments by value?

Copying a NAD could be UB. Makes sense.

> My big concern is that by deferring the UB past the point of date-object construction, you are deferring it past the point where it is most easily checked.

> We now have a 'valid' object running through our system, with pre-conditions on most of its members that it not hold the not-a-date value.  Many functions taking dates must document the requirement that they are not passed the 'not a date' value, or must widen their contracts to check for this, and then define some error handling policy (which must be tested for, increasing the state-space that calling functions must be aware of, increasing the complexity of the whole program).

> Deferring UB past the point of construction is a bad way to introduce UB into library contracts - and still forces the potentially expensive checking onto the constructor as well.  This appears to be a "worst of both worlds" solution - we gain the cost of checking, and pay an additional price for pushing UB deeper into the system.

As I wrote in one of my previous posts, the idea is to allow the following idiom:

if (date d(y, m, d, nothrow_validate))
{
   // valid date
}

else
{
  // invalid date

}

which is less clumsy, IMHO, than:

date d;
if (d.set_ymd(y, m, d))
{
   // valid date
}

else
{
  // invalid date

}

This approach, by the way, doesn't specify what is the value of d before the call to set_ymd(). So even the validating-setter approach requires the construction of uninitialized values, accessing which is UB. What is the difference?

Ganesh

====================================
====================================



Daniel Krügler
====================================
   Autres options 29 août, 13:57
2011/8/29 Alberto Ganesh Barbati <gan...@barbati.net>:

> Il giorno 29/ago/2011, alle ore 13:30, Alisdair Meredith ha scritto:

>> What can I do with your proposed "not a date" value, if it is undefined behavior to access it?

> You can check the presence of a not-a-date using the contextual conversion to bool or possibly a member function.

>> Is it defined behavior to copy a Not-a-Date value, e.g. if a function takes arguments by value?

> Copying a NAD could be UB. Makes sense.

I like the idea, which is also very much similar to the valid flag of
future and shared_future.

- Afficher le texte des messages précédents -

I would prefer the "valid state" idiom. We have
comparable examples in the library for that as
well. I currently tend to not provide explicit
operator bool(), because that could be misinterpreted
as a null-like value, IMO quering valid is fine enough.

- Daniel

====================================
====================================



Ville Voutilainen
====================================
   Autres options 29 août, 14:07
On 29 August 2011 14:57, Daniel Krügler <daniel.krueg...@googlemail.com> wrote:

>> You can check the presence of a not-a-date using the contextual conversion to bool or possibly a member function.
>>> Is it defined behavior to copy a Not-a-Date value, e.g. if a function takes arguments by value?
>> Copying a NAD could be UB. Makes sense.
> I like the idea, which is also very much similar to the valid flag of
> future and shared_future.

I very much prefer invalid dates never existing. Then I can reason
about my systems, and don't
have to worry about operations past construction causing UB. My
assumption here is
that

1) a throwing constructor, if provided, obviously prevents an object's
lifetime starting
2) a non-throwing constructor causing UB causes reasonable-enough-UB
in debug builds
that I can correct my logic errors before shipping

Checking a Not-a-date with a member or with a conversion all over the
place doesn't sound like a good idea
at all, design-wise. If the date class can avoid such checks, I'll
have to do them myself, so "it just needs
to check in the bool-operator" doesn't help me at all.

====================================
====================================



JOHN LAKOS, BLOOMBERG/ 731 LEXIN
====================================
   Autres options 29 août, 14:48

Ganesh wrote:
>I definitely agree with Nevin. However, the main problem is that constructors >can't return failure without either throwing or introducing a not-a-date >valid. John (please correct me if I interpreted you wrongly) has expressed >distaste for both these approaches. However, I believe implementing a >not-a-date value has several advantages without introducing unwanted overhead. >Consider this internal structure, suggested by Nevin:

To clarify what I am advocating:

1. An invariant of the object is that it holds a valid date value.  Period.

2. Copy construction and assignment are always valid

3. (choose your name but) void setYearMonthDay(...) AND
   bool setYearMonthDayIfValid(...) are both supported in some form.

4. (could be free but) static bool isValid(...) is supported in some form.

5. The default constructed date is inititalized, valid, and *isn't* "today" for
   many reasons -- e.g., dependency, security, testing (by our clients).

6. It sounds to me like we may be allowing objective engineering to be
   influenced too greately by subjective aesthetics.  "Clunkey" or not, testing
   the date first OR setting the date with a validating setter of some form is
   what we *need* to do to in order to avoid fully defining the ctor behavior
   to throw (BAD IDEA) or allowing for not-a-date value (WORSE IDEA).

7. Note that the performance cost of seting the date to a default value is a
   single 'int' assignment.  As much as I love AS FAST AS POSSIBLE, default
   initializing the date to a valid value is a sound trade-off in ALL cases:       If we are talking about 1 date, then it cannot be a performance issue, and
   if we are talking about many dates, we can reuse the one dummy, and again
   it is not an issue.

                                                        Cheers, John Lakis

- Afficher le texte des messages précédents -


====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 29 août, 15:00

Il giorno 29/ago/2011, alle ore 14:07, Ville Voutilainen ha scritto:

- Afficher le texte des messages précédents -

Please consider that I suggest to have all three kind of constructors (throwing, non-throwing/non-validating, non-throwing/validating), with throwing being the default. If you don't want to be bother with NAD values, just do not call the non-throwing/validating constructor.

Ganesh


Alberto Ganesh Barbati
====================================
   Autres options 29 août, 15:11

Il giorno 29/ago/2011, alle ore 14:48, JOHN LAKOS, BLOOMBERG/ 731 LEXIN ha scritto:

> Ganesh wrote:
>> I definitely agree with Nevin. However, the main problem is that constructors >can't return failure without either throwing or introducing a not-a-date >valid. John (please correct me if I interpreted you wrongly) has expressed >distaste for both these approaches. However, I believe implementing a >not-a-date value has several advantages without introducing unwanted overhead. >Consider this internal structure, suggested by Nevin:

> To clarify what I am advocating:

> 1. An invariant of the object is that it holds a valid date value.  Period.

> <snip>
> 6. It sounds to me like we may be allowing objective engineering to be
>   influenced too greately by subjective aesthetics.  "Clunkey" or not, testing
>   the date first OR setting the date with a validating setter of some form is
>   what we *need* to do to in order to avoid fully defining the ctor behavior
>   to throw (BAD IDEA) or allowing for not-a-date value (WORSE IDEA).

I'm sorry, but I don't see how you could guarantee an invariant which doesn't include NAD values and yet require construction to be non-throwing. What would be the expected behaviour of:

  date d(0, 0, 0);

?

Or are you suggesting that we must always use two-phase construction?

Ganesh

====================================
====================================



Alisdair Meredith
====================================
   Autres options 29 août, 15:13
On 29 Aug 2011, at 09:00, Alberto Ganesh Barbati wrote:

- Afficher le texte des messages précédents -

Once the not-a-date semantic enters the library, I am not able to ignore it when writing my own libraries.  At a minimum I must add a precondition to each contract in my library taking dates that it is not passed a not-a-date value.

Trickier is specifying the contracts for my generic code.  I want to have the notion of a simple value-semantic type that I can use specifying generic interfaces.  Do I need to add the notion of 'not-a-value' to my idea of value-semantic, so my contracts can explicitly always exclude generic not-a-values from defined behavior?  Or can date simply not satisfy my type requirements due to the presence of this one additional state?

I would much rather that state not exist, as it has too much of a ripple effect through all the rest of my code.

I am quite happy to entertain something like a not-a-value in a higher level abstraction, such as boost::optional<date>, where an empty optional is equivalent to the not-a-value.  If you need both empty and not-a-value, then you can compose further with optional<optional<date>>.

AlisdairM

====================================
====================================



Ville Voutilainen
====================================
   Autres options 29 août, 15:21
On 29 August 2011 16:00, Alberto Ganesh Barbati <gan...@barbati.net> wrote:

> Please consider that I suggest to have all three kind of constructors (throwing, non-throwing/non-validating, non-throwing/validating), with throwing being the default.

That's almost ok. The assumption is that an UB-constructor will not
allow further code to continue executing.
But, I still don't think a NAD-constructed date is a good idea. Hence
I'd prefer having only two variants
of constructors, one throwing and one causing UB. Same goes for
setting values, two variants, one
causing UB and one validating+throwing, _and_ a separate validation
function that doesn't construct
or modify a date. I think I'm in 100% agreement with John there.

>If you don't want to be bother with NAD values, just do not call the non-throwing/validating constructor.

Practically the construction and use of such date objects can be so
far apart that this creates
a big problem, reasoning-wise and verification-wise. A never-invalid
date doesn't suffer from such
a problem.

====================================
====================================



Nevin Liber
====================================
   Autres options 29 août, 15:22
On 29 August 2011 06:57, Daniel Krügler <daniel.krueg...@googlemail.com> wrote:

> 2011/8/29 Alberto Ganesh Barbati <gan...@barbati.net>:
>> Copying a NAD could be UB. Makes sense.

> I like the idea, which is also very much similar to the valid flag of
> future and shared_future.

That means you can't use a date as a key in an ordered container.  I
would be against this.  Date needs to be copyable, assignable and have
a SWO.
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



Alisdair Meredith
====================================
   Autres options 29 août, 15:23

On 29 Aug 2011, at 09:11, Alberto Ganesh Barbati wrote:

- Afficher le texte des messages précédents -

You are not allowing for undefined behavior.  Such a constructor might assert, which in turn may throw depending on how the assertion library is configured - undefined behavior can do anything.  It also implies this this is a narrow contract that should not be marked 'noexcept' (at least in the library specification - implementers can 'noexcept' if they know their build mode cannot throw e.g. assertions are disabled).

(and yes, date(0,0,0) can make its best guess and come up with some other nonsense value as undefined behavior too.)

AlisdairM

====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 29 août, 15:24

Il giorno 29/ago/2011, alle ore 15:13, Alisdair Meredith ha scritto:

- Afficher le texte des messages précédents -

I'm still not convinced, but what about using a simple wrapper:

struct tentative_date
{
   date value;
   bool is_valid;

   tentative_date(int y, int m, int d)
    : is_valid(is_valid_ymd(y, m, d))
   {
     if (is_valid)
      value.set_ymd(y, m, d);
   }

   explicit operator bool() const
   {
     return value.is_valid();
   }

};

or even

struct tentative_date
{
   date value;

   tentative_date(int y, int m, int d)
        : value(y, m, d, no_check)
   {}

   explicit operator bool() const
   {
     return value._internal_is_valid_date();
   }

};

In this case date either contains a valid value or UB, but tentative_date might contain a NAD. Would that be address your concerns?

Ganesh

====================================
====================================



Robert Douglas
====================================
   Autres options 29 août, 15:25

On Mon, Aug 29, 2011 at 8:11 AM, Alberto Ganesh Barbati
<gan...@barbati.net>wrote:

> I'm sorry, but I don't see how you could guarantee an invariant which
> doesn't include NAD values and yet require construction to be non-throwing.
> What would be the expected behaviour of:

>  date d(0, 0, 0);

I would suggest, then, an interface in which all values passed are valid
ones:
date d = years(2011) + months(13) + days(32);
yields February 1st, 2012

Internal representation of day count gives no invalid bit patterns. Added
bonus, comparison, addition, and subtraction are all trivial to the class,
allowing for very simple use in ordered containers and databases.

The cost of converting back to year/month/day would be larger, but I cannot
think of many use cases where this wouldn't either precede or follow system
IO.

====================================
====================================



Daniel Krügler
====================================
   Autres options 29 août, 15:27
2011/8/29 Nevin Liber <ne...@eviloverlord.com>:

> On 29 August 2011 06:57, Daniel Krügler <daniel.krueg...@googlemail.com> wrote:
>> 2011/8/29 Alberto Ganesh Barbati <gan...@barbati.net>:
>>> Copying a NAD could be UB. Makes sense.

>> I like the idea, which is also very much similar to the valid flag of
>> future and shared_future.

> That means you can't use a date as a key in an ordered container.  I
> would be against this.  Date needs to be copyable, assignable and have
> a SWO.

I don't see the point. All operations of an invalid date except the destructor,
assignment, and valid call would invoke undefined behaviour,
I haven't seen any other proposal yet, unless you make Not-a-Date a fullfledged
value. But I understood that this was not part of John's design. This means
that you can perfectly define order and equality of dates without need
to consider Not-a-Date.

- Daniel

====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 29 août, 15:36

Il giorno 29/ago/2011, alle ore 15:24, Alberto Ganesh Barbati ha scritto:

- Afficher le texte des messages précédents -

Or even:

class unchecked_date
{
    // only non-throwing non-validating ctors
    // allows Not-a-date values
    // has validation members that "promote" to date

};

class date : public unchecked_date
{
   // only throwing validating ctors
   // date values are guaranteed to be valid

};

Ganesh

====================================
====================================



Ville Voutilainen
====================================
   Autres options 29 août, 15:44
On 29 August 2011 16:27, Daniel Krügler <daniel.krueg...@googlemail.com> wrote:

> I don't see the point. All operations of an invalid date except the destructor,
> assignment, and valid call would invoke undefined behaviour,
> I haven't seen any other proposal yet, unless you make Not-a-Date a fullfledged
> value. But I understood that this was not part of John's design. This means
> that you can perfectly define order and equality of dates without need
> to consider Not-a-Date.

I got the impression that in John's design the constructor and setter can
invoke UB. Nothing else can. Is that correct?

I very much see the point of using Date as a map key.

====================================
====================================



Nevin Liber
====================================
   Autres options 29 août, 15:47
On 29 August 2011 08:25, Robert Douglas <rwdou...@gmail.com> wrote:

>> I'm sorry, but I don't see how you could guarantee an invariant which
>> doesn't include NAD values and yet require construction to be non-throwing.
>> What would be the expected behaviour of:

>>  date d(0, 0, 0);

> I would suggest, then, an interface in which all values passed are valid
> ones:
> date d = years(2011) + months(13) + days(32);
> yields February 1st, 2012

Guaranteed?  I'm not sure you can, because at some point you hit the
range of the primitive types you use to create the objects, and that
is implementation-specified behavior (how many bytes in a short,
etc.).

Adding components together is a bad idea.  Dates are not durations,
and we start running into issues with commutativity and associativity
when defining the meaning behind:

date d1 = years(2012) + years(1);
date d2 = years(2012) + months(2) + days(28) + years(1);
date d3 = years(2012) + months(3) + days(1) + years(1);
date d4 = years(2012) + months(2) + days(28) + days(2) + years(1) - days(2);
date d5 = years(2012) + months(2) + days(29) + years(1) - years(1);

Maybe as a separate interface built on top of the primitives, but
construction of a date needs to come from a fixed year, month and day.
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



Daniel Krügler
====================================
   Autres options 29 août, 15:49
2011/8/29 Ville Voutilainen <ville.voutilai...@gmail.com>:

> On 29 August 2011 16:27, Daniel Krügler <daniel.krueg...@googlemail.com> wrote:
>> I don't see the point. All operations of an invalid date except the destructor,
>> assignment, and valid call would invoke undefined behaviour,
>> I haven't seen any other proposal yet, unless you make Not-a-Date a fullfledged
>> value. But I understood that this was not part of John's design. This means
>> that you can perfectly define order and equality of dates without need
>> to consider Not-a-Date.

> I got the impression that in John's design the constructor and setter can
> invoke UB. Nothing else can. Is that correct?

If you construct or set an invalid date value you are invoking UB.
But unless there are no further words what the properties
are of such a "constructed" invalid value are, any usage of
this value must also invoke UB. Anything else does not
make sense.

- Daniel

====================================
====================================



Ville Voutilainen
====================================
   Autres options 29 août, 15:56
On 29 August 2011 16:49, Daniel Krügler <daniel.krueg...@googlemail.com> wrote:

>> I got the impression that in John's design the constructor and setter can
>> invoke UB. Nothing else can. Is that correct?
> If you construct or set an invalid date value you are invoking UB.
> But unless there are no further words what the properties
> are of such a "constructed" invalid value are, any usage of
> this value must also invoke UB. Anything else does not
> make sense.

This seems to indicate that a not-a-date doesn't buy me anything at all.
If it's UB to access a not-a-date (beyond checking validity), and it's
similarly
UB to access a date which has been set with an invalid value, I'd rather live
without a not-a-date concept.

I can write a validating wrapper on top of a date class. A library can
provide such a
wrapper for me. But for that, the _fundamental vocabulary type_ must be FAST!
I'm more and more gravitating towards an approach where the
constructors/setters
should just be UB, fair and square. Provide a bare-bones date, and if
we can get a
_separate_ design right for a "safe" date, provide that as well.
Perhaps it's a bad idea to try and mix the two.

====================================
====================================



Nevin Liber
====================================
   Autres options 29 août, 15:57
On 29 August 2011 08:27, Daniel Krügler <daniel.krueg...@googlemail.com> wrote:

>> That means you can't use a date as a key in an ordered container.  I
>> would be against this.  Date needs to be copyable, assignable and have
>> a SWO.

> I don't see the point. All operations of an invalid date except the destructor,
> assignment, and valid call would invoke undefined behaviour,

If Date is not Copyable (which is a property of the type, not its
value), how can you store it in a container?  I suppose we could say
that Date is only Moveable, but that would be surprising to most
people.

> I haven't seen any other proposal yet, unless you make Not-a-Date a fullfledged
> value.

Or don't allow it.  Default construction (which I believe is necessary
to keep this as a useful class) could create a valid but unspecified
value.
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



JOHN LAKOS, BLOOMBERG/ 731 LEXIN
====================================
   Autres options 29 août, 15:58
Clarification:

I agree that the opertor< should be defined on date (and it is at Bloomberg).
Almost nothing else is UB unless you move a date off its valid range --
e.g., date += 10000000; // days

                                                       -John Lakos

- Afficher le texte des messages précédents -


====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 29 août, 16:10

Il giorno 29/ago/2011, alle ore 15:56, Ville Voutilainen ha scritto:

> On 29 August 2011 16:49, Daniel Krügler <daniel.krueg...@googlemail.com> wrote:
>>> I got the impression that in John's design the constructor and setter can
>>> invoke UB. Nothing else can. Is that correct?
>> If you construct or set an invalid date value you are invoking UB.
>> But unless there are no further words what the properties
>> are of such a "constructed" invalid value are, any usage of
>> this value must also invoke UB. Anything else does not
>> make sense.

> This seems to indicate that a not-a-date doesn't buy me anything at all.
> If it's UB to access a not-a-date (beyond checking validity), and it's
> similarly
> UB to access a date which has been set with an invalid value, I'd rather live
> without a not-a-date concept.

As you said, having a not-a-date allows you to check validity. This is not "anything at all". It's quite much, in fact.

> I can write a validating wrapper on top of a date class. A library can
> provide such a
> wrapper for me. But for that, the _fundamental vocabulary type_ must be FAST!
> I'm more and more gravitating towards an approach where the
> constructors/setters
> should just be UB, fair and square. Provide a bare-bones date, and if
> we can get a
> _separate_ design right for a "safe" date, provide that as well.
> Perhaps it's a bad idea to try and mix the two.

Sounds like the unchecked_date/date approach that I just posted, except that the focus is different: unchecked_date is bare-bone and allows not-a-dates, while date is fully validated and therefore guaranteed valid/copiable/hashable, etc. Users are expected to normally use date, while the use of unchecked_date should be limited and transitory, as a mean to construct a valid date. It seems to me that this approach is superior to a date/safe_date approach, precisely because we can have not-a-dates without having them spill all around.

Ganesh

====================================
====================================



Robert Douglas
====================================
   Autres options 29 août, 16:24

- Afficher le texte des messages précédents -

But my point is that for any resulting set of bits, the date object is
valid. You can force overflow for any numerical type.

Adding components together is a bad idea.  Dates are not durations,
> and we start running into issues with commutativity and associativity
> when defining the meaning behind:

I disagree. Dates represent a duration of time since some arguably arbitrary
beginning.
As for associativity and commutativity, it seems like an issue of operator
choice, not an issue as to the merits of initialization based the
combination of parts. Surely, we could do the same thing with a constructor
taking the 3 components, ymd, but that yields all the drawbacks seen above,
when the user believes that they are only adding in a number of months 1-12,
and a number of days based on the month and year number, but may actually be
passing in higher (or lower) values.

> date d1 = years(2012) + years(1);
> date d2 = years(2012) + months(2) + days(28) + years(1);
> date d3 = years(2012) + months(3) + days(1) + years(1);
> date d4 = years(2012) + months(2) + days(28) + days(2) + years(1) -
> days(2);
> date d5 = years(2012) + months(2) + days(29) + years(1) - years(1);

None of these are actually problems, when a forced left-to-right execution
is performed. Thus, perhaps a different operator? operator*? Addition seems
natural to me, but I can see that problems arise since the length of a month
is dependent on the year, and the length of a year is dependent on how many
precede it.

- Afficher le texte des messages précédents -


====================================
====================================



Nevin Liber
====================================
   Autres options 29 août, 16:32
On 29 August 2011 08:57, Nevin Liber <ne...@eviloverlord.com> wrote:

> If Date is not Copyable (which is a property of the type, not its
> value), how can you store it in a container?

To clarify, ithis precludes storing it in *any* container, even
something as simple as vector<Date>.

> Default construction (which I believe is necessary
> to keep this as a useful class) could create a valid but unspecified
> value.

And even other properties, such as:

date d1;
date d2;

assert(d1 == d2);

could be kept unspecified.
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



Ville Voutilainen
====================================
   Autres options 29 août, 16:46
On 29 August 2011 17:10, Alberto Ganesh Barbati <gan...@barbati.net> wrote:

>> This seems to indicate that a not-a-date doesn't buy me anything at all.
>> If it's UB to access a not-a-date (beyond checking validity), and it's
>> similarly
>> UB to access a date which has been set with an invalid value, I'd rather live
>> without a not-a-date concept.
> As you said, having a not-a-date allows you to check validity. This is not "anything at all". It's quite much, in fact.

I expect any debug-mode UB to allow me to quickly and easily notice misuses
of constructors and setters. I don't want non-debug-mode constructors and
setters waste time on validation. I expect debug-mode UB to bomb so hard
that I never cause further UB by accessing an object after an operation causing
UB. I don't want to worry about having to check for validity after
construction/setting/whatever when using the date type.

I also want to be able to store dates into containers and I want to be
able to use
them as associative container keys.

So far it seems to me that having a not-a-date hurts more than it
helps. Hence the
comment "doesn't seem to buy me anything". It' not "not anything" in
the very sense
of the words, but it doesn't buy me anything I want. :)

Regardless of how we solve all those problems, the "raw" setter
doesn't seem to fit
into the picture. It allows the invariants to break by setting a not-a-date or
an undefined date.

====================================
====================================



JOHN LAKOS, BLOOMBERG/ 731 LEXIN
====================================
   Autres options 29 août, 16:55
All,

We do not want a Date and a CheckedDate (derived from it).  The problem would
come from slicing the CheckedDate when passed into an interface.   The better
approach is to have a single date that has two types of methods: those
that check, and those that don't.  In a safe build, even the ones that
don't check do, and do what the app developer says (and not what the person who
violated the preconditions wants).  In our experience, having two build modes and two methods achieves our goals better than having two classes.

                                             -John Lakos

- Afficher le texte des messages précédents -


====================================
====================================



Ville Voutilainen
====================================
   Autres options 29 août, 16:59
On 29 August 2011 17:55, JOHN LAKOS, BLOOMBERG/ 731 LEXIN

<jla...@bloomberg.net> wrote:
> We do not want a Date and a CheckedDate (derived from it).  The problem would
> come from slicing the CheckedDate when passed into an interface.   The better

If we would end up having two dates, I wouldn't expect either to
publicly derive from the other.

====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 29 août, 17:02

Il giorno 29/ago/2011, alle ore 16:55, JOHN LAKOS, BLOOMBERG/ 731 LEXIN ha scritto:

> All,

> We do not want a Date and a CheckedDate (derived from it).

Neither do I. I suggested to have date derived from unchecked_date.

> The problem would
> come from slicing the CheckedDate when passed into an interface.

Slicing is no problem if unchecked_date is a base.

>   The better
> approach is to have a single date that has two types of methods: those
> that check, and those that don't.  In a safe build, even the ones that
> don't check do, and do what the app developer says (and not what the person who
> violated the preconditions wants).  In our experience, having two build modes and two methods achieves our goals better than having two classes.

I am pretty sure that your approach is good. Whether it's "better" is your opinion. I am evaluating alternative designs. As Howard put it in the opening email, it's ok if we come up with more than one design. We don't need to necessarily agree.

Ganesh

====================================
====================================



JOHN LAKOS, BLOOMBERG/ 731 LEXIN
====================================
   Autres options 29 août, 17:19
Ganesh,

First, I am -- of course -- just giving my opinion when I say one class is better than two, and you -- of course -- don't necessarily have to agree.
We are having an open discussion, and I feel that we are all contributing.

Second,

             date                      checked_date
              |             ==              |
              v                             v
         unchecked_date                   date

These two structures are the same, have the same methods, but have different
names for humans.  This is like a change of variables in math. :-)
The slicing problem is the same.  What am I missing?

                                                        -John L.

- Afficher le texte des messages précédents -


====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 29 août, 17:35

Il giorno 29/ago/2011, alle ore 17:19, JOHN LAKOS, BLOOMBERG/ 731 LEXIN ha scritto:

> Ganesh,

> First, I am -- of course -- just giving my opinion when I say one class is better than two, and you -- of course -- don't necessarily have to agree.
> We are having an open discussion, and I feel that we are all contributing.

> Second,

>             date                      checked_date
>              |             ==              |
>              v                             v
>         unchecked_date                   date

> These two structures are the same, have the same methods, but have different
> names for humans.  This is like a change of variables in math. :-)
> The slicing problem is the same.  What am I missing?

The focus changes. You are expected to generally use _date_ objects. By giving the "other" class a uglier name we implicitly say "use the ugly-named one only when needed". By having date/checked_date you are promoting the wrong usage pattern: that checking is to be done "only when needed", while it's the opposite view that I would like to promote.

What is the problem if a date (that has already been checked and validated) is sliced as an unchecked_date? Simply that information (about the validity of the date) is lost. So what? It's a performance issue, it doesn't introduce instability or incorrectness in the program. The ugly name should be enough deterrent to avoid people to write functions taking an unchecked_date& parameter and unchecked_date usage is to be restricted to those limited pieces of code that deal with date validation. I do not expect slicing to occur in the typical usage scenario.

Ganesh

====================================
====================================



JOHN LAKOS, BLOOMBERG/ 731 LEXIN
====================================
   Autres options 29 août, 18:07
Ganesh,

But the problem is that we cannot use an unchecked_date where a date is needed!

There will be a vocabulary problem.  I do not agree (in this specific case) that checking should be the default.  I think an unknown date value MUST ALWAYS be checked, and a known good one should not be checked (unless in a safe build mode).  The one true date allows for both cases as needed.

-John L.

- Masquer le texte des messages précédents -

----- Original Message -----
From: kona-date-lib@googlegroups.com
To: kona-date-lib@googlegroups.com

At:  8/29 11:35:22

Il giorno 29/ago/2011, alle ore 17:19, JOHN LAKOS, BLOOMBERG/ 731 LEXIN ha scritto:

> Ganesh,

> First, I am -- of course -- just giving my opinion when I say one class is better than two, and you -- of course -- don't necessarily have to agree.
> We are having an open discussion, and I feel that we are all contributing.

> Second,

>             date                      checked_date
>              |             ==              |
>              v                             v
>         unchecked_date                   date

> These two structures are the same, have the same methods, but have different
> names for humans.  This is like a change of variables in math. :-)
> The slicing problem is the same.  What am I missing?

The focus changes. You are expected to generally use _date_ objects. By giving the "other" class a uglier name we implicitly say "use the ugly-named one only when needed". By having date/checked_date you are promoting the wrong usage pattern: that checking is to be done "only when needed", while it's the opposite view that I would like to promote.

What is the problem if a date (that has already been checked and validated) is sliced as an unchecked_date? Simply that information (about the validity of the date) is lost. So what? It's a performance issue, it doesn't introduce instability or incorrectness in the program. The ugly name should be enough deterrent to avoid people to write functions taking an unchecked_date& parameter and unchecked_date usage is to be restricted to those limited pieces of code that deal with date validation. I do not expect slicing to occur in the typical usage scenario.

Ganesh

--
You received this message because you are subscribed to the Google Groups "Kona-date-lib" group.
To post to this group, send email to kona-date-lib@googlegroups.com.
To unsubscribe from this group, send email to kona-date-lib+unsubscribe@googlegroups.com.
For more options, visit this group at http://groups.google.com/group/kona-date-lib?hl=en.

Nevin Liber
====================================
   Autres options 29 août, 19:17
On 29 August 2011 10:02, Alberto Ganesh Barbati <gan...@barbati.net> wrote:

> Il giorno 29/ago/2011, alle ore 16:55, JOHN LAKOS, BLOOMBERG/ 731 LEXIN ha scritto:
>> We do not want a Date and a CheckedDate (derived from it).

> Neither do I. I suggested to have date derived from unchecked_date.

I'm not seeing any conceptual difference between these; only a
difference in the spelling of the types.

When discussing the concepts and relationships between the types,
could we use the names unchecked_date and checked_date, and break off
into a separate discussion which one of those (if any) we spell
"date"?
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



Nevin Liber
====================================
   Autres options 29 août, 19:54
On 29 August 2011 07:48, JOHN LAKOS, BLOOMBERG/ 731 LEXIN

<jla...@bloomberg.net> wrote:
> Ganesh wrote:
> 6. It sounds to me like we may be allowing objective engineering to be
>   influenced too greately by subjective aesthetics.  "Clunkey" or not, testing
>   the date first OR setting the date with a validating setter of some form is
>   what we *need* to do to in order to avoid fully defining the ctor behavior
>   to throw (BAD IDEA) or allowing for not-a-date value (WORSE IDEA).

Users need ways to:

1.  Create an object w/o validating its parameters.  This may invoke
undefined behavior.
2.  Create an object after validating its parameters.  Undefined
behavior must be avoidable, but object creation may fail.  (This may
be broken into multiple statements on the part of the user to make it
happen.)

Having thought about why it is clunky (and good for calling me on it),
it is because exceptions, not return codes, give me functions that are
composible (and function composition is an objective, not subjective
criterion).

Now, maybe a checking version has to be written as:

make_valid_date(make_valid_year(2012), make_valid_month(2), make_valid_day(32));

(in an implementation where (1) constructors create non-validated
objects and (2) make_valid_* are non-instance functions that throw on
invalid input and return a valid object otherwise) while the non
checked version is written

date(year(2012), month(2), day(32));

But that seems more error-prone to me, as some people are going to write:

make_valid_date(year(2012), month(2), day(32));

which subtly invokes undefined behavior.  (And no, I'm not giving up
on strong typing for the parameters to the date creation functions
just to get around this problem.)

As long as there is a creation method which doesn't throw (which I
agree we need), are you okay if there are other constructors that do
throw?
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



Daniel Krügler
====================================
   Autres options 29 août, 20:06
2011/8/29 Nevin Liber <ne...@eviloverlord.com>:

> On 29 August 2011 07:48, JOHN LAKOS, BLOOMBERG/ 731 LEXIN
> <jla...@bloomberg.net> wrote:
>> Ganesh wrote:
>> 6. It sounds to me like we may be allowing objective engineering to be
>>   influenced too greately by subjective aesthetics.  "Clunkey" or not, testing
>>   the date first OR setting the date with a validating setter of some form is
>>   what we *need* to do to in order to avoid fully defining the ctor behavior
>>   to throw (BAD IDEA) or allowing for not-a-date value (WORSE IDEA).

> Users need ways to:

> 1.  Create an object w/o validating its parameters.  This may invoke
> undefined behavior.

I'm fine with that.

> 2.  Create an object after validating its parameters.  Undefined
> behavior must be avoidable, but object creation may fail.  (This may
> be broken into multiple statements on the part of the user to make it
> happen.)

> Having thought about why it is clunky (and good for calling me on it),
> it is because exceptions, not return codes, give me functions that are
> composible (and function composition is an objective, not subjective
> criterion).

> Now, maybe a checking version has to be written as:

> make_valid_date(make_valid_year(2012), make_valid_month(2), make_valid_day(32));

First, I strongly object that using a checked creation
should require complicated code as shown above. IMO
the intuitive simple construction should be checked. If
you want an unchecked form, make that clear, e.g. by
requiring a tag like "unchecked".

Second, I'm not sure why there are such a lot of functions
involved. Having an individually checked year, an individually
checked month, and an individually checked day does not
help against the date 2011-02-29, for example.

And this is may main concern, why I prefer to have
a simple way for checked constructions/assignment,
because we have a multi-parameter interaction here, and
the probability increases with each parameter that the
combination could be invalid.

- Daniel

====================================
====================================



Nevin Liber
====================================
   Autres options 29 août, 20:42
On 29 August 2011 13:06, Daniel Krügler <daniel.krueg...@googlemail.com> wrote:

> Second, I'm not sure why there are such a lot of functions
> involved. Having an individually checked year, an individually
> checked month, and an individually checked day does not
> help against the date 2011-02-29, for example.

Strong type checking is a good thing.  People are going to get the
order of parameters wrong, and I strongly feel that be a compile time
error than either UB or deferred to run time (if detectable at all).

What is the "natural" order of parameters anyway?  C mostly (if not
all) has destination specified before source.  C++, which is supposed
to be a superset, inverted that for its own algorithms.  Worse, some
parameter orders require a C++ expert to understand, because the
"natural" order was discarded to avoid such issues as ambiguous
overloading. And then there are functions like memset, where almost no
one can remember the order of the last two parameters.

> And this is may main concern, why I prefer to have
> a simple way for checked constructions/assignment,
> because we have a multi-parameter interaction here, and
> the probability increases with each parameter that the
> combination could be invalid.

This is certainly a valid concern that I have also.  But there are so
many tensions between the tradeoffs that I am unsure this is the
biggest concern.
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 29 août, 21:15

Il giorno 29/ago/2011, alle ore 19:17, Nevin Liber ha scritto:

> On 29 August 2011 10:02, Alberto Ganesh Barbati <gan...@barbati.net> wrote:
>> Il giorno 29/ago/2011, alle ore 16:55, JOHN LAKOS, BLOOMBERG/ 731 LEXIN ha scritto:
>>> We do not want a Date and a CheckedDate (derived from it).

>> Neither do I. I suggested to have date derived from unchecked_date.

> I'm not seeing any conceptual difference between these; only a
> difference in the spelling of the types.

> When discussing the concepts and relationships between the types,
> could we use the names unchecked_date and checked_date, and break off
> into a separate discussion which one of those (if any) we spell
> "date"?

As I said in another post, there is a difference in focus which *is* relevant. Anyway, I whipped out some code and I am no longer sure the double date hierarchy achieves what I have in mind. The approach of having a single date class and a totally unrelated tentative_date class which acts as an optimized version of boost::optional<date> looks more promising.

Thus, there are three construction scenarios:

1) I have ymd values that represents a valid date (trust me!), I want maximal performance:

     date d(y, m, d, no_check);

if it happens that ymd do no represent a valid date, we have UB.

2) I have ymd values that may not represent a valid date, I want the library to validate them for me, getting an exception is fine:

    date d(y, m, d);

3) I have ymd values that may not represent a valid date, I want the library to validate them for me, I don't like exceptions:

    if (tentative_date td(y, m d))
    {
       date d = td.date(); // good date
    }
    else
    {
      // bad date
    }

calling td.date() if bool(td) == false is UB.

Obvious alternatives that don't require a separate tentative_date class and address this scenario are:

Alternative A:

   if (date::is_valid_ymd(y, m, d))
   {
       date dt(y, m, d, no_check);
       // good date
   }
   else
   {
      // bad date
   }

slightly more verbose, may require additional local variables if y, m, d are complex expressions to avoid re-evaluation of them. The user might forget the no_check and have the date validated twice.

Alternative B:

  date dt;
  if (dt.set_ymd_if_valid(y, m, d))
  {
     // good date
  }
  else
  {
     // bad date
  }

the main problem with this approach is that d is in scope after the if statement as well as in the false-branch. As there is some consensus that a default-initialized date is a *valid* albeit unspecified date, neither the compiler nor runtime assertion facilities will help spot an incorrect use of d if the set_ymd_if_valid() function fails.

Another added bonus of the tentative_date class is that it might have handy member functions to be used in the false-branch to provide extended information about _what_ did not validate (the year? the month? the day?).

Ganesh

====================================
====================================



Daniel Krügler
====================================
   Autres options 29 août, 21:28
2011/8/29 Alberto Ganesh Barbati <gan...@barbati.net>:

- Afficher le texte des messages précédents -

I like this construction.

> 2) I have ymd values that may not represent a valid date, I want the library to validate them for me, getting an exception is fine:

>    date d(y, m, d);

I like this as well.

> 3) I have ymd values that may not represent a valid date, I want the library to validate them for me, I don't like exceptions:

>    if (tentative_date td(y, m d))
>    {
>       date d = td.date(); // good date
>    }
>    else
>    {
>      // bad date
>    }

> calling td.date() if bool(td) == false is UB.

tentative_date doesn't convince me much: It seems to be quite complicated
and very special date-specific but has actually not much use expect for
validation. If we had optional, we could use this instead and it could be
reused for other types as well (I'm not suggesting to invent optional
just because of date, though).

I need a bit more time for the non-exceptional checked construction.

- Daniel

====================================
====================================



bs
====================================
   Autres options 29 août, 21:59
On 8/29/2011 12:54 PM, Nevin Liber wrote:

> On 29 August 2011 07:48, JOHN LAKOS, BLOO
> Now, maybe a checking version has to be written as:

> make_valid_date(make_valid_year(2012), make_valid_month(2), make_valid_day(32));

NO! That's too ugly for words. For the default, average, and novice user
the checked construction should look very much  like this

     date d{2012,month{12},30};

IMO, the unchecked version (which might lead to undefined behavior),
should look like this

     date d{2012,month{12},30,unchecked};

This is longer because it is the version for experts.

If you can't afford to have construction throw, you write something very
much like

     if (!date::valid(2012,month{12},30,unchecked) { /* deal with it */ }
     date d{2012,month{12},30,unchecked};

and hope you don't mess up. I could live with the alternative

     date d{2012,month{12},30,unchecked};
     if (!d::valid()) { /* deal with it */ }

My main concern is whether and how to get

     date d{2012,month{12},30,asserted};

which is the debug version on unchecked.

====================================
====================================



Nevin Liber
====================================
   Autres options 29 août, 22:13
On 29 August 2011 14:59, bs <b...@cs.tamu.edu> wrote:

> NO! That's too ugly for words. For the default, average, and novice user the
> checked construction should look very much  like this

>    date d{2012,month{12},30};

> IMO, the unchecked version (which might lead to undefined behavior), should
> look like this

>    date d{2012,month{12},30,unchecked};

To make this work, month must both not check its parameter AND you can
pass any value whatsoever to month's constructor w/o invoking
undefined behavior.  Is this as intended?
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



bs
====================================
   Autres options 29 août, 22:56
On 8/29/2011 3:13 PM, Nevin Liber wrote:

> On 29 August 2011 14:59, bs<b...@cs.tamu.edu>  wrote:
>> NO! That's too ugly for words. For the default, average, and novice user the
>> checked construction should look very much  like this

>>     date d{2012,month{12},30};

>> IMO, the unchecked version (which might lead to undefined behavior), should
>> look like this

>>     date d{2012,month{12},30,unchecked};
> To make this work, month must both not check its parameter AND you can
> pass any value whatsoever to month's constructor w/o invoking
> undefined behavior.  Is this as intended?

Yes. (at least that's what I do)

====================================
====================================



Nevin Liber
====================================
   Autres options 30 août, 00:54
On 29 August 2011 15:56, bs <b...@cs.tamu.edu> wrote:

>> To make this work, month must both not check its parameter AND you can
>> pass any value whatsoever to month's constructor w/o invoking
>> undefined behavior.  Is this as intended?

> Yes. (at least that's what I do)

Let me also suggest that we pick a signed type for the parameter to
the month constructor, as I'd rather we have undefined behavior if the
conversion to that type overflows or underflows instead of being able
to wrap back to a legitimate value by using an unsigned type.

(I'm only mentioning this in case someone is tempted to suggest using
a char as the parameter, since the range of possible months will
obviously fit in it.)

I'm actually liking this solution...
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



bs
====================================
   Autres options 30 août, 00:57
On 8/29/2011 5:54 PM, Nevin Liber wrote:

> On 29 August 2011 15:56, bs<b...@cs.tamu.edu>  wrote:
>>> To make this work, month must both not check its parameter AND you can
>>> pass any value whatsoever to month's constructor w/o invoking
>>> undefined behavior.  Is this as intended?
>> Yes. (at least that's what I do)
> Let me also suggest that we pick a signed type for the parameter to
> the month constructor, as I'd rather we have undefined behavior if the
> conversion to that type overflows or underflows instead of being able
> to wrap back to a legitimate value by using an unsigned type.

> (I'm only mentioning this in case someone is tempted to suggest using
> a char as the parameter, since the range of possible months will
> obviously fit in it.)

> I'm actually liking this solution...

I'm tempted to use an enum class.

====================================
====================================



JOHN LAKOS, BLOOMBERG/ 731 LEXIN
====================================
   Autres options 30 août, 09:57

Nevin wrote:
> As long as there is a creation method which doesn't throw (which I
> agree we need), are you okay if there are other constructors that do
> throw?

Honestly, when you talked about utility functions on top of (and separate from) the date Class (component) to do the extra checking and throw, you hit the nail on the head!  That way, we can build more complex functionality out of simpler functionality, without imposing it on everyone.  This is excatly how I think
we should structure our libraries (and how we do it at Bloomberg today).

I do think we need the "built-in" pair of member functions:

void set_year_month_day(y, m, d);            // choice of types for y, m, d
bool set_year_month_day_if_valid(y, m, d);   // is kept separate here

As for having an extra constructor that is checked... (like the 'at' in
vector)...  I would never use it, but it doesn't hurt me either, provided
it's NOT the default (like in vector).

I do understand why Bjarna does not agree with making the unchecked ctor
the default, and making it harder (more ugly, time consuming)  to do the "raw" (more dangerous) unchecked constructor.  I am used to narrow contracts for
value types, and clearly I may be in the minority.  The subtle cost of
having checking be the default for all value semantic types all the time
is a tax on performance ALL THE TIME, not just in development.  This is
my largest objection.  I would not say "over my dead body" though; it would
would be another choice I would have to teach professional programmers to
avoid in the standard (and in our implemenation, it would be checked anyway
in safe mode, AND THE APP DEVELOPER, AND NOT THE PROGRAMMER WHO MADE THE
MISTAKE BY CALLING DATE OUT OF CONTRACT) would have the say of both (1) roughly how much time to spend looking, and what to do if a logic error is detected..

Nevin Wrote:
> Let me also suggest that we pick a signed type for the parameter to
> the month constructor, as I'd rather we have undefined behavior if t
> conversion to that type overflows or underflows instead of being abl
> to wrap back to a legitimate value by using an unsigned type.

I totally agree with this.  In fact, unless there is a need for an unsinged
type that is tied specifically to the platform -- e.g., for memory allocation,
indexing into a vector -- in which case we must use std::size_t or std::ptr_diff_t, we should use int (or int_64), e.g., for things
like day, age, shoe-size.

> (I'm only mentioning this in case someone is tempted to suggest usin
> a char as the parameter, since the range of possible months will
> obviously fit in it.)

For reasons of a comon vocabulary, we should always pass int, not short or char, long, etc.. Also note that the char and short will be extened to int,
passed through, and then truncated back -- there is no advantage in performance (it may even be more expensive) and it's not intuitive.

Bjarne wrote:
> I'm tempted to use an enum class.

I wouldn't die if we had an overload that took an enum for literals; however, I would not want to have to cast an int to an enum as the only way to get a valid
date into my date class without checking.

                                                   -John Lakos

====================================
====================================



Nevin Liber
====================================
   Autres options 30 août, 18:34
On 29 August 2011 14:59, bs <b...@cs.tamu.edu> wrote:

>    date d{2012,month{12},30};

One minor (I hope!) point:  Based on the observation stated in
<http://home.roadrunner.com/~hinnant/bloomington/date.html> that the
only three orderings in use are:

YMD
MDY
DMY

I feel that month should go first (and still be typed), as in:

date d(month(12), 30, 2012);

as it is the only one that is unambiguous with respect to how dates
are actually written.  The other way to do this would be to create a
type for day instead of month (which has the advantage that you can
write all three constructors if we decide that is the way to go), and
that type would need the same properties (constructor takes a signed
primitive type, no undefined behavior and parameter is unchecked).
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



Daniel Krügler
====================================
   Autres options 30 août, 18:53
2011/8/30 Nevin Liber <ne...@eviloverlord.com>:

- Afficher le texte des messages précédents -

I consider this reasoning as a bit too weak as a base to decide for a
single canonical order. If we want to single canonical order (I'm fine
with that) please lets use an established standard order.

I would argue that ISO 8601 defines a reasonable order as YMD
and there are easy ways to deduce this order, should one have
forgotten about it.

- Daniel

====================================
====================================



JOHN LAKOS, BLOOMBERG/ 731 LEXIN
====================================
   Autres options 30 août, 19:09

Daniel wrote:
> I would argue that ISO 8601 defines a reasonable order as YMD
> and there are easy ways to deduce this order, should one have
> forgotten about it.

I'm affraid I have to agrree with Daniel: Having MDY as a universal standard is (and always has been), in my experience, a bad idea.

On a separate note, and being really practical here...

If were to have just one order...

How is

         date.set(Year(1959), Month(3), Day(8));

so much less dangerous and/or less readable than

         date.setYearMonthDay(1959, 3, 8);

I mean really.

And I can tell you that the first is a bunch harder for me to type ;-)

                                                             -John L.

- Afficher le texte des messages précédents -


====================================
====================================



Nevin Liber
====================================
   Autres options 30 août, 20:02
On 30 August 2011 12:09, JOHN LAKOS, BLOOMBERG/ 731 LEXIN

<jla...@bloomberg.net> wrote:
> How is

>         date.set(Year(1959), Month(3), Day(8));

> so much less dangerous and/or less readable than

>         date.setYearMonthDay(1959, 3, 8);

> I mean really.

> And I can tell you that the first is a bunch harder for me to type ;-)

You are advocating to use a mnemonic rather than the type system.  In
other words, C++ has a type system that is hard to use.

In my experience, there have been so many bugs that either would have
been caught at compile time, test time or been trivial to fix had
people created and used types instead of falling back on the
fundamental types.

Yes, it is tedious to define and use types, but I find that far less
painful than debugging.

Ease of use vs. reliability:  a classic tradeoff...
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



Ville Voutilainen
====================================
   Autres options 30 août, 20:20
On 30 August 2011 21:02, Nevin Liber <ne...@eviloverlord.com> wrote:

>> How is
>>         date.set(Year(1959), Month(3), Day(8));
>> so much less dangerous and/or less readable than
>>         date.setYearMonthDay(1959, 3, 8);

It isn't. What validators and human readers can work with is having day and
month on different sides of year (which differs from the two by having
more digits), then we can do

date.set(Day(6), 1959, 6); and we know which is which, or
date.set(Month(6), 1959, 6); and we know which is which.

date.setYMD(1959, 6, 6); is not particularly safe, but neither is
date.setYMD(Year(1959), Month(6), Day(6));

Note that it's still rather unsafe to say

date.setYMD(yearvar, monthvar, dayvar); or even
date.setYMD(yearvar, Month(monthvar), Day(dayvar);

it's impossible to make it truly idiot-safe for all possible cases.
We have probably all tried to use some sort of integral wrappers
or even enum classes to disambiguate raw-ish numbers, but
as long as the different types, if any, need to be ultimately
constructed from ints, we're not achieving much because it's
still possible to mess it up by messing up the order.

====================================
====================================



JOHN LAKOS, BLOOMBERG/ 731 LEXIN
====================================
   Autres options 30 août, 20:20

Nevin wrote:
> You are advocating to use a mnemonic rather than the type system.

I tend to agree with you about trading off ease of writing for ease of
reading/maintaining.  However, I think that getting the date set using
a function with a name like setYearMonthDay followed by 3 ordered integers
is just as "type safe" and just as mnemonic as 'set' followed by three name/type values.

Remember, I could write

    d.set(year(3), Month(8), Day(2011))

and this is not a going to produce any error unless each of the individual field types do bounds checking (which they cannot do fully) or the overall set method does the check -- either way at signficant runtime overhead (as Howard demonstrated).

I think it's really the same thing when you get down to it:

                   d.setYearMonthDay(1959, 3, 8);
or
                   d.set(Year(1959), Month(3), Day(8));
Obviously
                   d.set(1959, 3, 8)

is needlessly non-mnemonic ("non-typesafe"), but that would be a straw man.

                                                         -John L.

- Afficher le texte des messages précédents -


====================================
====================================



Howard Hinnant
====================================
   Autres options 30 août, 20:38
On Aug 30, 2011, at 2:20 PM, Ville Voutilainen wrote:

> date.set(Month(6), 1959, 6); and we know which is which.

I think it would be a good thing to support Jun as a synonym for Month(6).  Jun has the advantage that it doesn't need range checking and is type-safe (if we design the API right).  Month(m) has the advantage that m can be specified at run time.  It seems like both Jun and Month(6) are very useful.

Howard

====================================
====================================



Daniel Krügler
====================================
   Autres options 30 août, 20:39
2011/8/30 Howard Hinnant <howard.hinn...@gmail.com>:

> On Aug 30, 2011, at 2:20 PM, Ville Voutilainen wrote:

>> date.set(Month(6), 1959, 6); and we know which is which.

> I think it would be a good thing to support Jun as a synonym for Month(6).  Jun has the advantage that it doesn't need range checking and is type-safe (if we design the API right).  Month(m) has the advantage that m can be specified at run time.  It seems like both Jun and Month(6) are very useful.

I wholeheartedly agree with that suggestion.

- Daniel

====================================
====================================



Ville Voutilainen
====================================
   Autres options 30 août, 21:33
On 30 August 2011 21:39, Daniel Krügler <daniel.krueg...@googlemail.com> wrote:

> 2011/8/30 Howard Hinnant <howard.hinn...@gmail.com>:
>> I think it would be a good thing to support Jun as a synonym for Month(6).  Jun has the advantage that it doesn't need range checking and is type-safe (if we design the API right).  Month(m) has the advantage that m can be specified at run time.  It seems like both Jun and Month(6) are very useful.
> I wholeheartedly agree with that suggestion.

Yes, using such an enumeration value is useful in many cases. Even
that doesn't protect us from argument
ordering problems. We can take some precautions to make mistakes less
common, but ultimately
we can't escape them all, especially when generic code (and especially
variadic templates) enters the picture.

====================================
====================================



bs
====================================
   Autres options 30 août, 21:46
On 8/30/2011 2:33 PM, Ville Voutilainen wrote:

> On 30 August 2011 21:39, Daniel Kr gler<daniel.krueg...@googlemail.com>  wrote:
>> 2011/8/30 Howard Hinnant<howard.hinn...@gmail.com>:
>>> I think it would be a good thing to support Jun as a synonym for Month(6).  Jun has the advantage that it doesn't need range checking and is type-safe (if we design the API right).  Month(m) has the advantage that m can be specified at run time.  It seems like both Jun and Month(6) are very useful.
>> I wholeheartedly agree with that suggestion.
> Yes, using such an enumeration value is useful in many cases. Even
> that doesn't protect us from argument
> ordering problems.

It protects us from *some* argument ordering problems: Use an enum class.

- Afficher le texte des messages précédents -


====================================
====================================



Nevin Liber
====================================
   Autres options 30 août, 21:52
On 30 August 2011 13:38, Howard Hinnant <howard.hinn...@gmail.com> wrote:

> I think it would be a good thing to support Jun as a synonym for Month(6).  Jun has the advantage that it doesn't need range checking and is type-safe (if we design the API right).  Month(m) has the advantage that m can be specified at run time.  It seems like both Jun and Month(6) are very useful.

Are we going to (ultimately) follow the naming convention of using
lower case?  I'm just thinking about ADL and streams and oct and
dec...

Other than that, I like it.
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



Ville Voutilainen
====================================
   Autres options 30 août, 21:53
On 30 August 2011 22:46, bs <b...@cs.tamu.edu> wrote:

>> Yes, using such an enumeration value is useful in many cases. Even
>> that doesn't protect us from argument
>> ordering problems.
> It protects us from *some* argument ordering problems: Use an enum class.

Well, even an enum class won't protect us in cases where you explicitly convert
an int to a value of enum class type, aka construct your enum class from a value
that we got from ui/network/user-some-other-way. You can still have ordering
problems even with enum classes if you can construct both an enum class Day
and an enum class Month from values between 1-12.

But, that pointing-out aside, yes, it helps with some ordering cases. It doesn't
ultimately save us from all of them. And then there's things like
int I_accidentally_the_whole_month = get_day_from_where_ever();
int I_also_accidentally_the_whole_day = get_month_from_where_ever();
// now construct a date from these in the 'naming' order and voila

Stuff like that can't be protected against, reasonably, so what I'm trying to
say here is that we need to think how far we want to protect users who don't
make sure that they use the ints in the right order, because ultimately they
have to make sure that they do, or hell breaks loose.

====================================
====================================



Howard Hinnant
====================================
   Autres options 30 août, 21:58
On Aug 30, 2011, at 3:52 PM, Nevin Liber wrote:

> On 30 August 2011 13:38, Howard Hinnant <howard.hinn...@gmail.com> wrote:
>> I think it would be a good thing to support Jun as a synonym for Month(6).  Jun has the advantage that it doesn't need range checking and is type-safe (if we design the API right).  Month(m) has the advantage that m can be specified at run time.  It seems like both Jun and Month(6) are very useful.

> Are we going to (ultimately) follow the naming convention of using
> lower case?  I'm just thinking about ADL and streams and oct and
> dec...

> Other than that, I like it.

I'm not opposed to upper case, but had assumed to date lower case because of the existing std::lib convention.  I'm aware of the oct and dec conflicts and had imagined this library was destined for namespace std::chrono along with the other time-keeping components.

Howard

Howard Hinnant
====================================
   Autres options 30 août, 22:03
On Aug 30, 2011, at 3:53 PM, Ville Voutilainen wrote:

- Afficher le texte des messages précédents -

Making use of constexpr objects appears to get all of the benefits of [class] enums with none of the disadvantages:

class month
{
public:
    explicit month(int m) constexpr;
    // ...

};

constexpr month jun(6);

// ...

class date
{
public:
     date(year y, month d, day d);
     // overload this constructor to taste
     // ...

};

<Disclaimer>  I'm still learning constexpr and don't have a compiler to test this against.  But I've subbed in const with good success.

Howard

====================================
====================================



Ville Voutilainen
====================================
   Autres options 30 août, 22:06
On 30 August 2011 23:03, Howard Hinnant <howard.hinn...@gmail.com> wrote:

>> Well, even an enum class won't protect us in cases where you explicitly convert
>> an int to a value of enum class type, aka construct your enum class from a value
> Making use of constexpr objects appears to get all of the benefits of [class] enums with none of the disadvantages:

Well, it protects you when you do things at compile-time. When the int
comes in at runtime,
constexpr won't help you. ;)

====================================
====================================



Nevin Liber
====================================
   Autres options 30 août, 22:06
On 30 August 2011 14:58, Howard Hinnant <howard.hinn...@gmail.com> wrote:

> I'm aware of the oct and dec conflicts

We can always add an overload...

Just kidding,
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



Daniel Krügler
====================================
   Autres options 30 août, 22:11
2011/8/30 Ville Voutilainen <ville.voutilai...@gmail.com>:

> On 30 August 2011 23:03, Howard Hinnant <howard.hinn...@gmail.com> wrote:
>>> Well, even an enum class won't protect us in cases where you explicitly convert
>>> an int to a value of enum class type, aka construct your enum class from a value
>> Making use of constexpr objects appears to get all of the benefits of [class] enums with none of the disadvantages:

> Well, it protects you when you do things at compile-time. When the int
> comes in at runtime,
> constexpr won't help you. ;)

I don't understand the problem: During runtime you could rely
on the (runtime) checked form. It is possible to make the checked
form constexpr, so no further overloads are required, to have
both advantages in one place.

- Daniel

====================================
====================================



Ville Voutilainen
====================================
   Autres options 30 août, 22:36
On 30 August 2011 23:11, Daniel Krügler <daniel.krueg...@googlemail.com> wrote:

> I don't understand the problem: During runtime you could rely
> on the (runtime) checked form. It is possible to make the checked
> form constexpr, so no further overloads are required, to have
> both advantages in one place.

I don't understand how any kind of checking protects against logic errors.
Integral values between 1-12 can be either days or months, and we can't know
that no matter how much checking we add. We can add some sanity,
but as mentioned, there are cases where no amount of checking we
(try to) do in our date class protects against such problems.

I guess that's a problem with a "vocabulary type". It can't provide for
all possible vocabularies, nor can it provide for all kinds of domain-specific
designs. It can provide a very useful building block, and it can even provide
a bunch of very useful default facilities that can cover a wide swath of
vocabularies/domains/designs, however you want to call it, but there will
be limitations that need to be overcome by building things on top of it.

====================================
====================================



Ville Voutilainen
====================================
   Autres options 30 août, 22:39
On 30 August 2011 23:36, Ville Voutilainen <ville.voutilai...@gmail.com> wrote:

> I don't understand how any kind of checking protects against logic errors.
> Integral values between 1-12 can be either days or months, and we can't know

Not to mention that they can be years, too. :)

====================================
====================================



Robert Klarer
====================================
   Autres options 30 août, 22:44

Why just enumerate the months?

enum class DaysOfYear {

    Jan01 = 1,

    Jan02,

    Jan03,

    Jan04,

    /* ... */

    Dec29,

    Dec30,

    Dec31

};

class date

{

public:

    date(int year, DaysOfYear md);

    date(int year, int month, int day);

    /* ... */

};

On Tue, Aug 30, 2011 at 4:36 PM, Ville Voutilainen <

- Afficher le texte des messages précédents -


====================================
====================================



bs
====================================
   Autres options 30 août, 23:05

On 8/30/2011 3:44 PM, Robert Klarer wrote:

- Afficher le texte des messages précédents -

I'm not sure if I like it, but it is the first really new idea I have
seen in this thread :-)

- Afficher le texte des messages précédents -


====================================
====================================



Howard Hinnant
====================================
   Autres options 30 août, 23:14
On Aug 30, 2011, at 5:05 PM, bs wrote:

- Afficher le texte des messages précédents -

I'm having trouble prototyping it (or any use of class enums).  How do you convert Feb03 to the two ints 2 and 3 in the date constructor?  I know how to do it for enum DaysOfYear, but not for enum *class* DaysOfYear.  I'm having the same trouble with the use of enum class Month previously suggested.

Howard

====================================
====================================



bs
====================================
   Autres options 30 août, 23:16
On 8/30/2011 4:14 PM, Howard Hinnant wrote:

- Afficher le texte des messages précédents -

How do you handle Feb29?

====================================
====================================



Howard Hinnant
====================================
   Autres options 30 août, 23:23
On Aug 30, 2011, at 5:16 PM, bs wrote:

- Afficher le texte des messages précédents -

This is just prototype/throw-away code (and it doesn't compile, but I mean for it to):

enum DaysOfYear {
    Jan01 = 1, Jan02, Jan03, Jan04, Jan05, Jan06, Jan07,
    Jan08, Jan09, Jan10, Jan11, Jan12, Jan13, Jan14,
    Jan15, Jan16, Jan17, Jan18, Jan19, Jan20, Jan21,
    Jan22, Jan23, Jan24, Jan25, Jan26, Jan27, Jan28,
    Jan29, Jan30, Jan31,
    Feb01, Feb02, Feb03, Feb04, Feb05, Feb06, Feb07,
    Feb08, Feb09, Feb10, Feb11, Feb12, Feb13, Feb14,
    Feb15, Feb16, Feb17, Feb18, Feb19, Feb20, Feb21,
    Feb22, Feb23, Feb24, Feb25, Feb26, Feb27, Feb28,
    Feb29,
    Mar01, Mar02, Mar03, Mar04, Mar05, Mar06, Mar07,
    Mar08, Mar09, Mar10, Mar11, Mar12, Mar13, Mar14,
    Mar15, Mar16, Mar17, Mar18, Mar19, Mar20, Mar21,
    Mar22, Mar23, Mar24, Mar25, Mar26, Mar27, Mar28,
    Mar29, Mar30, Mar31,
    Apr01, Apr02, Apr03, Apr04, Apr05, Apr06, Apr07,
    Apr08, Apr09, Apr10, Apr11, Apr12, Apr13, Apr14,
    Apr15, Apr16, Apr17, Apr18, Apr19, Apr20, Apr21,
    Apr22, Apr23, Apr24, Apr25, Apr26, Apr27, Apr28,
    Apr29, Apr30, Apr31,
    // ...

};

static
const int
db[2][13] = {{-1, 30, 58, 89, 119, 150, 180, 211, 242, 272, 303, 333, 364},
             {-1, 30, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365}};

static
const unsigned char
mb[2][366] =
{
{
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,
12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12
},

{
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,
12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12

}
};

static
inline
bool
is_leap(int y) noexcept
{
    return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);

}

struct date
{
    int year_;
    int month_;
    int day_;

    date(int year, int month, int day)
        : year_(year), month_(month), day_(day) {}

    date(int year, DaysOfYear md)
        : year_(year)
        {
            bool leap = is_leap(year_);
            int doy(md);
            if (leap)
            {
                month_ = mb[1][doy];
                day_ = doy - db[1][month_-1];
            }
            else
            {
                if (doy == DaysOfYear::Feb29)
                    throw 1;
                if (doy > DaysOfYear::Feb29)
                    --doy;
                month_ = mb[0][doy];
                day_ = doy - db[0][month_-1];
            }
        }

};

int main()
{
    date(2011, DaysOfYear::Jan04);

}

Howard

====================================
====================================



Robert Klarer
====================================
   Autres options 31 août, 02:02

This compiles (using Apple LLVM):

    date(int year, DaysOfYear md)

    : year_(year)

    {

        bool leap = is_leap(year_);

        int doy = int(md); // explicit conversion

        if (leap)

        {

            month_ = mb[1][doy];

            day_ = doy - db[1][month_-1];

        }

        else

        {

            if (md == DaysOfYear::Feb29) // avoid spurious conversion

                throw 1;

            if (md > DaysOfYear::Feb29)  // avoid spurious conversion

                --doy;

            month_ = mb[0][doy];

            day_ = doy - db[0][month_-1];

        }

   }

On Tue, Aug 30, 2011 at 5:23 PM, Howard Hinnant <howard.hinn...@gmail.com>wrote:

- Afficher le texte des messages précédents -


====================================
====================================



Howard Hinnant
====================================
   Autres options 31 août, 02:28
On Aug 30, 2011, at 8:02 PM, Robert Klarer wrote:

- Afficher le texte des messages précédents -

Interesting.  Using :

enum class DaysOfYear {
    Jan01 = 1, Jan02, Jan03, Jan04, Jan05, Jan06, Jan07,
...

I'm getting:

test.cpp:141:17: error: cannot initialize a variable of type 'int' with an lvalue of type 'DaysOfYear'
            int doy(md);
                ^   ~~
1 error generated.

But if I use:

enum DaysOfYear {
    Jan01 = 1, Jan02, Jan03, Jan04, Jan05, Jan06, Jan07,
...

then it works.

Apple clang version 3.0 (tags/Apple/clang-211.10.1) (based on LLVM 3.0svn)
Target: x86_64-apple-darwin11.1.0
Thread model: posix

I'm not a class enum expert, so I'm not positive what the correct behavior is supposed to be.  [dcl.enum]/p9 says "no implicit conversion".  I can't find where it says there /is/ an explicit conversion.  Anyone here know for sure?

Howard

====================================
====================================



Robert Klarer
====================================
   Autres options 31 août, 02:29

Also, I think this version of the constructor is going to be cheaper than
the one I just posted.

    date(int year, DaysOfYear md)

    : year_(year)

    {

        bool leap = false;

        int doy = int(md);

        if (md == DaysOfYear::Feb29)

        {

            if ((leap = is_leap(year_)))

                {

                    throw 1;

                }

        }

        month_ = mb[leap ? 0 : 1][doy];

        day_ = doy - db[leap ? 0 : 1][month_-1];

    }

Verifying the date costs one integer equality comparison, but then you need
to decompose the  DaysOfYear value to a month and a day.

====================================
====================================



Alisdair Meredith
====================================
   Autres options 31 août, 02:52
Why are we doing all these tests for Feb29 as runtime tests?

If DayOfYear is a literal type, we can hoist that test to compile time (danger - silly template interfaces ahead)

enum Feb29Policy { BeforeFeb29, IsFeb29, AfterFeb29 };

template<Feb29Policy>
struct DayOfYear;

template<>
struct DayOfYear<BeforeFeb29> {
   constexpr explicit DayOfYear(int val) : m_day{val} {}

   constexpr auto dayOfYear(int year) -> int { return m_day; }

private:
   int m_day;

};

template<>
struct DayOfYear<IsFeb29> {
   constexpr explicit DayOfYear(int val) : m_day{val} {}

   constexpr auto dayOfYear(int year) -> int { return isLeapYear(year) ? throw bad_date{} : 60; }

};

template<>
struct DayOfYear<BeforeFeb29> {
   constexpr explicit DayOfYear(int val) : m_day{val} {}

   constexpr auto dayOfYear(int year) -> int { return isLeapYear ? m_day-1 : m_day; }

private:
   int m_day;

};

Now we simply create the 366 literal values:

constexpr DayOfYear<BeforeFeb29> Jan01{1};
constexpr DayOfYear<BeforeFeb29> Jan02{2};
...
constexpr DayOfYear<BeforeFeb29> Feb28{59};
constexpr DayOfYear<IsFeb29> Feb29{60};
constexpr DayOfYear<AfterFeb29> Mar01{61};
...
constexpr DayOfYear<AfterFeb29> Dec31{366};

Unfortunately, anything expecting to work with these literal values must be written as a function template on enum Feb29Policy, but we already have this issue with chrono times...

(No, I'm not being serious, but if we are trying to optimize this approach, why hold back!)

AlisdairM

On 30 Aug 2011, at 20:29, Robert Klarer wrote:

- Afficher le texte des messages précédents -


====================================
====================================



Daniel Krügler
====================================
   Autres options 31 août, 08:09
2011/8/31 Howard Hinnant <howard.hinn...@gmail.com>:
[..]

- Afficher le texte des messages précédents -

The compiler is right to reject the attempt to direct-initialize
an integral type with a scoped enum. The semantics of this
initialization is defined in the bulleted list of 8.5 p16. Since there
are no class types involved, we need to skip b6+7 and end in
the last bullet:

"Otherwise, the initial value of the object being initialized is the
(possibly converted) value of the initializer
expression. Standard conversions (Clause 4) will be used, if
necessary, to convert the initializer
expression to the cv-unqualified version of the destination type; no
user-defined conversions are considered.
If the conversion cannot be done, the initialization is ill-formed."

And we find that there is no standard conversion from a *scoped* enum
to int. So, direct-initialization is not sufficient here, you need an (explicit)
static_cast.

- Daniel

====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 31 août, 09:24

Il giorno 31/ago/2011, alle ore 08:09, Daniel Krügler ha scritto:

- Afficher le texte des messages précédents -

Correct. A static_cast is the correct way convert a scoped enum to an integral (see 5.2.9/9). This works as it should in Clang:

  int doy = static_cast<int>(md);

Ganesh

====================================
====================================



Howard Hinnant
====================================
   Autres options 1 sep, 02:55
On Aug 31, 2011, at 3:24 AM, Alberto Ganesh Barbati wrote:

> Correct. A static_cast is the correct way convert a scoped enum to an integral (see 5.2.9/9). This works as it should in Clang:

>  int doy = static_cast<int>(md);

Thanks Daniel, Ganesh.  Here's Robert's date constructor lightly tested:

    date(int year, DaysOfYear md)
        : year_(year)
        {
            int doy = static_cast<int>(md) - 1;
            if (md == DaysOfYear::Feb29)
            {
                if (!is_leap(year_))
                    throw 1;
            }
            month_ = mb[1][doy];
            day_ = doy - db[1][month_-1];
        }

Howard

====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 1 sep, 10:51

Il giorno 01/set/2011, alle ore 02:55, Howard Hinnant ha scritto:

- Afficher le texte des messages précédents -

That is very nice indeed. It might be favorite ctor for hard-coded date values. However, we still need a way to make a DaysOfYear value from separate month/day values, which is what is needed most often:

   int y, m, d;
   read_from_user(y, m, d);
   date dt(y, ???);

We could have a make_doy() function like this:

   date d(2011, make_doy(m, d));

but we are still facing the same issue regarding the order of parameters (too easy to write make_doy(d, m) incorrectly). We could have another enum class for months and have a make_month helper function, like this:

   date d(2011, make_doy(make_month(m), d));

which, alas, isn't any prettier than where we started from, that is:

   date d(year(2011), month(m), day(d));

in my humble opinion. Do we have alternatives to make_doy/make_month?

Ganesh

====================================
====================================



Ville Voutilainen
====================================
   Autres options 1 sep, 11:00
On 1 September 2011 11:51, Alberto Ganesh Barbati <gan...@barbati.net> wrote:

> but we are still facing the same issue regarding the order of parameters (too easy to write make_doy(d, m) incorrectly). We could have another enum class for months and have a make_month helper function, like this:
>   date d(2011, make_doy(make_month(m), d));

I suppose it's just equally easy to write date d(2011,
make_doy(make_month(d), m));

and oopsy-daisy we go. :) I seriously doubt the success chance of such
attempts at protective measures.
As long as the date components need to be constructible from ints
(which is just unavoidable), it's always
possible to mix them up.

====================================
====================================



Nevin Liber
====================================
   Autres options 1 sep, 15:46
On 1 September 2011 04:00, Ville Voutilainen
<ville.voutilai...@gmail.com> wrote:

I seriously doubt the success chance of such

> attempts at protective measures.
> As long as the date components need to be constructible from ints
> (which is just unavoidable), it's always
> possible to mix them up.

So, you are saying that because we cannot prevent *all* possible
errors, we should never try and prevent *any* possible errors.  I
disagree with that position.

The least error prone is to have the name right next to the value, at
the expense of being the most verbose.  We value terseness as well as
correctness, and hence are looking for the balance between the two.
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



Ville Voutilainen
====================================
   Autres options 1 sep, 17:27

> So, you are saying that because we cannot prevent *all* possible
> errors, we should never try and prevent *any* possible errors.   I
> disagree with that position.

I have no problems with the proposed enum
overloads. I expect to find them very useful
for cases where I know (some) of the values
before runtime. For runtime cases, I don't
see the benefit that the tedious syntax is
supposed to bring. For such cases I have
to get the order right anyway, so wrapping
won't help much, if at all. Having such
wrappers most likely brings a false sense
of security to users.

====================================
====================================



Robert Klarer
====================================
   Autres options 1 sep, 18:21

Has something like make_date (below) been discussed? There's still some
extra typing, and it doesn't eliminate the potential for error, but it
allows the programmer to record his or her intention, at least.

Examples:

auto today = make_date<ymd>(2011, 9, 1);

auto yesterday = make_date<mdy>(8, 31, 2011);

auto tomorrow = make_date<dmy>(2, 9, 2011);

//auto never = make_date<dym>(2, 10, 2011); // static assertion

Implementation:

struct date

{

    int year_;

    int month_;

    int day_;

    date(int year, int month, int day)

    : year_(year), month_(month), day_(day) {}

};

enum DateFormat {

    ymd,

    mdy,

    dmy,

    invalid_DateFormat,

    dym = invalid_DateFormat,

    myd = invalid_DateFormat,

    ydm = invalid_DateFormat

};

template <DateFormat fmt>

inline

date make_date(int, int, int)

{

    static_assert(fmt != invalid_DateFormat, "Invalid date format.");

    return date(0, 0, 0);

}

template <>

inline

    date make_date<ymd>(int m, int d, int y) {return date(y, m, d); }

template <>

inline

    date make_date<mdy>(int m, int d, int y) {return date(y, m, d); }

template <>

inline

    date make_date<dmy>(int d, int m, int y) {return date(y, m, d); }

====================================
====================================



Ville Voutilainen
====================================
   Autres options 1 sep, 18:26

> I have no problems with the proposed enum
> overloads. I expect to find them very useful
> for cases where I know (some) of the values
> before runtime. For runtime cases, I don't
> see the benefit that the tedious syntax is
> supposed to bring. For such cases I have

This actually means that I'd like to
have a bare-int version, at the very
least. If there are other overloads,
I don't think I mind. Let's just not
go overboard with it, ok? :)

====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 2 sep, 00:30

Il giorno 01/set/2011, alle ore 18:21, Robert Klarer ha scritto:

> Has something like make_date (below) been discussed? There's still some extra typing, and it doesn't eliminate the potential for error, but it allows the programmer to record his or her intention, at least.

> Examples:

> auto today = make_date<ymd>(2011, 9, 1);
> auto yesterday = make_date<mdy>(8, 31, 2011);
> auto tomorrow = make_date<dmy>(2, 9, 2011);
> //auto never = make_date<dym>(2, 10, 2011); // static assertion

I don't find it much better than the simpler:

auto today = make_date_ymd(2011, 9, 1);
auto yesterday = make_date_mdy(8, 31, 2011);
auto tomorrow = make_date_dmy(2, 9, 2011);

Anyway, I believe we are making a big mistake by using simple examples like this as arguments. Dates will rarely be constructed from hard-coded literals. They will usually be constructed from variables that may have been read or computed. I understand that in the typical scenario where the values are used immediately, as in:

   int y, m, d;
   read_user_input(y, m, d);
   // make date from y, m, d

there's very little difference between:

   date dt = make_date_ymd(y, m, d)

and

  date dt { year(y), month(m), day(d) };

There's basically the same chance that the user gets it wrong in both cases. (Consider that the order of the parameters in read_user_input may also be wrong!) I can hardly say which one is better in such a limited scenario, so everyone is just biased by their personal preference. But we have a more significant difference in the case where the y, m and d variables are obtained in a part of the code and the actual date is constructed elsewhere. Having separate types for year, month, day can be useful to avoid inadvertent exchanges, comparison between the wrong variables, etc. like any physical dimensional analysis library does. We should not underestimate that.

Just my opinion,

Ganesh

Robert Klarer
====================================
   Autres options 2 sep, 06:30

On Tue, Aug 30, 2011 at 8:52 PM, Alisdair Meredith <w...@alisdairm.net>wrote:

> Why are we doing all these tests for Feb29 as runtime tests?

Good question! I'm hoping that something like this will work, but I don't
have a compiler that does constexpr:

enum class DaysOfYear {

    Jan01 = 0x0101,

    Jan02, Jan03, Jan04, Jan05, Jan06, Jan07, Jan08, Jan09, Jan10, Jan11,

    Jan12, Jan13, Jan14, Jan15, Jan16, Jan17, Jan18, Jan19, Jan20, Jan21,

    Jan22, Jan23, Jan24, Jan25, Jan26, Jan27, Jan28, Jan29, Jan30, Jan31,

    Feb01 = 0x0201,

    Feb02, Feb03, Feb04, Feb05, Feb06, Feb07, Feb08, Feb09, Feb10, Feb11,

    Feb12, Feb13, Feb14, Feb15, Feb16, Feb17, Feb18, Feb19, Feb20, Feb21,

    Feb22, Feb23, Feb24, Feb25, Feb26, Feb27, Feb28, Feb29,

    Mar01 = 0x0301,

    Mar02, Mar03, Mar04, Mar05, Mar06, Mar07, Mar08, Mar09, Mar10, Mar11,

    Mar12, Mar13, Mar14, Mar15, Mar16, Mar17, Mar18, Mar19, Mar20, Mar21,

    Mar22, Mar23, Mar24, Mar25, Mar26, Mar27, Mar28, Mar29, Mar30, Mar31,

    Apr01 = 0x0401,

    Apr02, Apr03, Apr04, Apr05, Apr06, Apr07, Apr08, Apr09, Apr10, Apr11,

    Apr12, Apr13, Apr14, Apr15, Apr16, Apr17, Apr18, Apr19, Apr20, Apr21,

    Apr22, Apr23, Apr24, Apr25, Apr26, Apr27, Apr28, Apr29, Apr30,

    May01 = 0x0501,

    May02, May03, May04, May05, May06, May07, May08, May09, May10, May11,

    May12, May13, May14, May15, May16, May17, May18, May19, May20, May21,

    May22, May23, May24, May25, May26, May27, May28, May29, May30, May31,

    Jun01 = 0x0601,

    Jun02, Jun03, Jun04, Jun05, Jun06, Jun07, Jun08, Jun09, Jun10, Jun11,

    Jun12, Jun13, Jun14, Jun15, Jun16, Jun17, Jun18, Jun19, Jun20, Jun21,

    Jun22, Jun23, Jun24, Jun25, Jun26, Jun27, Jun28, Jun29, Jun30,

    Jul01 = 0x0701,

    Jul02, Jul03, Jul04, Jul05, Jul06, Jul07, Jul08, Jul09, Jul10, Jul11,

    Jul12, Jul13, Jul14, Jul15, Jul16, Jul17, Jul18, Jul19, Jul20, Jul21,

    Jul22, Jul23, Jul24, Jul25, Jul26, Jul27, Jul28, Jul29, Jul30, Jul31,

    Aug01 = 0x0801,

    Aug02, Aug03, Aug04, Aug05, Aug06, Aug07, Aug08, Aug09, Aug10, Aug11,

    Aug12, Aug13, Aug14, Aug15, Aug16, Aug17, Aug18, Aug19, Aug20, Aug21,

    Aug22, Aug23, Aug24, Aug25, Aug26, Aug27, Aug28, Aug29, Aug30, Aug31,

    Sep01 = 0x0901,

    Sep02, Sep03, Sep04, Sep05, Sep06, Sep07, Sep08, Sep09, Sep10, Sep11,

    Sep12, Sep13, Sep14, Sep15, Sep16, Sep17, Sep18, Sep19, Sep20, Sep21,

    Sep22, Sep23, Sep24, Sep25, Sep26, Sep27, Sep28, Sep29, Sep30,

    Oct01 = 0x0A01,

    Oct02, Oct03, Oct04, Oct05, Oct06, Oct07, Oct08, Oct09, Oct10, Oct11,

    Oct12, Oct13, Oct14, Oct15, Oct16, Oct17, Oct18, Oct19, Oct20, Oct21,

    Oct22, Oct23, Oct24, Oct25, Oct26, Oct27, Oct28, Oct29, Oct30, Oct31,

    Nov01 = 0x0B01,

    Nov02, Nov03, Nov04, Nov05, Nov06, Nov07, Nov08, Nov09, Nov10, Nov11,

    Nov12, Nov13, Nov14, Nov15, Nov16, Nov17, Nov18, Nov19, Nov20, Nov21,

    Nov22, Nov23, Nov24, Nov25, Nov26, Nov27, Nov28, Nov29, Nov30,

    Dec01 = 0x0C01,

    Dec02, Dec03, Dec04, Dec05, Dec06, Dec07, Dec08, Dec09, Dec10, Dec11,

    Dec12, Dec13, Dec14, Dec15, Dec16, Dec17, Dec18, Dec19, Dec20, Dec21,

    Dec22, Dec23, Dec24, Dec25, Dec26, Dec27, Dec28, Dec29, Dec30, Dec31

};

inline

constexpr bool is_leap(int y) { return y % 4 == 0 && (y % 100 != 0 || y %
400 == 0); }

inline

constexpr int extract_month(DaysOfYear md) { return static_cast<int>(md) >>
8; }

inline

constexpr int extract_day(DaysOfYear md) { return static_cast<int>(md) &
0xFF; }

struct date

{

    int year_;

    int month_;

    int day_;

    constexpr date(int year, int month, int day)

    : year_(year), month_(month), day_(day) {}

};

inline

constexpr date make_date(DaysOfYear md, int y)

{

    static_assert(md != DaysOfYear::Feb29 || is_leap(y), "Bad date.");

    return date(y, extract_month(md), extract_day(md));

}

Off-topic:

A problem that I've noticed is that static_assert doesn't seem to work well
with constexpr functions, even with the changes introduced through N3268 (
http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2011/n3268.htm).

The problem is that the arguments to make_date, above, may or may not be
constant expressions, so the static_assertion may or may not be ill-formed.
I don't think there's any way to say "check this assertion only if the
function is computed statically."

====================================
====================================



Robert Klarer
====================================
   Autres options 2 sep, 06:44

On Thu, Sep 1, 2011 at 6:30 PM, Alberto Ganesh Barbati
<gan...@barbati.net>wrote:

- Afficher le texte des messages précédents -

I see it this way: we need to be able to initialize a date with a triple of
ints. I'd like to see a simple, straight-forward constructor that allows the
date class to work as a literal type. We also need a better, safer, less
error-prone interface for initializing dates. For these more complicated
initializations, I'd like there to be a variety of make_date functions. Date
validation, unit types (days, months, years), and support for alternative
formats and argument orders (ymd, mdy, etc) belong in the make_date
functions, IMO, not in the constructor(s).

The people that really need to use the constructor directly can do so, but
most programmers should be encouraged to use the make_date functions as a
matter of good engineering.

====================================
====================================



Robert Klarer
====================================
   Autres options 2 sep, 16:38

Sorry for replying to my own post, but I wanted to point out that the
make_date approach has the added advantage of extensibility. For example, if
a programmer wants to enumerate month names other than the English ones, a
make_date-based interface would facilitate that.

On Fri, Sep 2, 2011 at 12:44 AM, Robert Klarer <robert.kla...@gmail.com>wrote:

- Afficher le texte des messages précédents -


====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 2 sep, 17:03

Il giorno 02/set/2011, alle ore 16:38, Robert Klarer ha scritto:

> Sorry for replying to my own post, but I wanted to point out that the make_date approach has the added advantage of extensibility. For example, if a programmer wants to enumerate month names other than the English ones, a make_date-based interface would facilitate that.

What do you mean by "enumerate month names other than the English ones". While I agree that having factory functions can be a good thing to have (in addition to constructors), I don't believe localization should be handled in factory functions. And non-gregorian calendars should be managed by a totally different class. In fact, here's my proposed approach for a possible multi-calendar date library:

namespace std
{
        namespace datelib
        {
                class days
                {
                        // simple wrapper over int: a date duration in days is common to all calendars
                };

                // a basic date_time facility, templated on a date class and a TimeDuration
                template <class DateType, class TimeDuration = std::chrono<int>>
                class date_time_base
                {
                        static_assert(TimeDuration::max() >= std::chrono<int>(60 * 60 * 24), "TimeDuration time must span at least one entire day");

                        DateType                date;
                        TimeDuration    time_of_day;

                        // ...
                };

                namespace gregorian
                {
                        // a year/month/day gregorian date class
                        class date
                        {
                                //...

                                // date conversion facilities
                                days days_since_1970() const;
                                static date date_after_1970(days d);
                        };

                        // aliases for gregorian date_time classes
                        template <class TimeDuration>
                        using basic_date_time<TimeDuration> = date_time_base<date, TimeDuration>

                        using date_time = date_time_base<date>;
                }

                namespace chinese
                {
                        // a chinese date class
                        class date
                        {
                                //...

                                // date conversion facilities
                                days days_since_1970() const;
                                static date date_after_1970(days d);
                        };

                        // aliases for chinese date_time classes
                        template <class TimeDuration>
                        using basic_date_time<TimeDuration> = date_time_base<date, TimeDuration>

                        using date_time = date_time_base<date>;
                }

                // cross-calendar conversion functions
                template <class FromDate, class ToDate>
                ToDate calendar_cast(const FromDate& from)
                {
                        return ToDate::date_after_1970(from.days_since_1970());
                }

                template <class FromDateTime, class ToDateTime>
                ToDateTime calendar_cast(const FromDateTime& from)
                {
                        return ToDateTime::date_after_1970(from.days_since_1970(), from.time_of_day());
                }
        }

}

Sample of usage:

int main()
{
        using namespace std::chrono;
        using namespace std::datelib;
        using namespace std::datelib::gregorian;

        date gdt(year(2010), september, day(2));

        // 1-second precision
        date_time gdti(gdt, hours(10)); // 10 o'clock (uses std::chrono::hours)

        // a more precise date_time class
        basic_date_time<microseconds> precise(gdti);

        // cross calendar conversions
        chinese::date cdt = calendar_cast<chinese::date>(gdt);
        chinese::date_time cdtm = calendar_cast<chinese::date>(gdti);

- Afficher le texte des messages précédents -


====================================
====================================



Robert Klarer
Afficher le profil
   Autres options 2 sep, 17:34

On Fri, Sep 2, 2011 at 11:03 AM, Alberto Ganesh Barbati
<gan...@barbati.net>wrote:

> Il giorno 02/set/2011, alle ore 16:38, Robert Klarer ha scritto:

> Sorry for replying to my own post, but I wanted to point out that the
> make_date approach has the added advantage of extensibility. For example, if
> a programmer wants to enumerate month names other than the English ones, a
> make_date-based interface would facilitate that.

> What do you mean by "enumerate month names other than the English ones".
> While I agree that having factory functions can be a good thing to have (in
> addition to constructors), I don't believe localization should be handled in
> factory functions. And non-gregorian calendars should be managed by a
> totally different class.

I don't mean localization. What I mean is that, if the standard date library
contains a scoped enum like this:

namespace chrono {
 class enum MonthName { January, February, March /* ... */ }
 date make_date(MonthName m, int d, int y);

}

then a programmer may wish to write something like this, for his or her own
convenience:

namespace User {
  class enum MonthName_fr { Janvier, Fevrier, Mars /* ...  */ }
  chrono::date make_date(MonthName_fr m, int d, int y);

}

I don't want to get hung up on the details of my offhand (and weak, I admit)
example. My main point is that make_date or some equivalent repertoire of
factory functions allows for some user customization of the library. This
point was being made in defence of the argument that chrono::date should
have a small number of very basic (and potentially unsafe) constructors, and
that the library should provide more sophisticated functionality at the
make_date level. Users should be implored to use make_date rather than the
constructor, unless they're sure they know what they're doing.

====================================
====================================



Daniel Krügler
====================================
   Autres options 2 sep, 19:08
2011/9/2 Robert Klarer <robert.kla...@gmail.com>:

- Afficher le texte des messages précédents -

Just for clarification, Robert: You are referring here to a similar
mechanism as we have for make_error_code and make_error_condition,
right?

- Daniel

====================================
====================================



Pablo Halpern
====================================
   Autres options 2 sep, 20:00

On 09/01/2011 06:30 PM, Alberto Ganesh Barbati wrote:

- Afficher le texte des messages précédents -

This is almost exactly what I was about to propose.  No need to
introduce three new identifiers (ymd, mdy, dmy) plus a template
function.  Just create three functions.  This mechanism is currently my
favorite.  The make_date_* functions could, alternatively, be written as
static members:

     class date
     {
       public:
         static date make_ymd(int, int, int);
         static date make_mdy(int, int, int);
         static date make_dmy(int, int, int);
     };

and there could be checked and unchecked variants of each.

- Afficher le texte des messages précédents -

Yes.  However, my bias against the latter form is two-fold.

     1. It introduces extra classes for month, day, and year for very
little gain and
     2. I am one of those people who prefers to use namespace-qualified
name and avoids "using" directives.  It's hard to imagine anything more
cumbersome than:

     std::chrono:date dt { std::chrono:year(y), std::chrono:month(m),
std::chrono:day(d) };

> But we have a more significant difference in the case where the y, m
> and d variables are obtained in a part of the code and the actual date
> is constructed elsewhere. Having separate types for year, month, day
> can be useful to avoid inadvertent exchanges, comparison between the
> wrong variables, etc. like any physical dimensional analysis library
> does. We should not underestimate that.

True.  If we care to make months, days, and years into first-class
concepts and not just a means to build a date, then I would be happy to
entertain that concept.  A millisecond, for example, is a useful type in
and of itself, not just as a way to test a timed mutex.  The fact that a
millisecond is type-safe and distinct from a microsecond is useful.  If
we want to have month, day, and year be real types independent of date,
then I would support having a date constructor or make_date() function
that is overloaded using these types -- but I still would like the
three-integer versions.

-Pablo

====================================
====================================



Ville Voutilainen
====================================
   Autres options 2 sep, 20:42
On 2 September 2011 21:00, Pablo Halpern

<phalp...@halpernwightsoftware.com> wrote:
>     2. I am one of those people who prefers to use namespace-qualified name
> and avoids "using" directives.  It's hard to imagine anything more
> cumbersome than:
>     std::chrono:date dt { std::chrono:year(y), std::chrono:month(m),
> std::chrono:day(d) };

Won't ADL find them?

====================================
====================================



Pablo Halpern
====================================
   Autres options 2 sep, 22:30
On 09/02/2011 02:42 PM, Ville Voutilainen wrote:
> On 2 September 2011 21:00, Pablo Halpern
> <phalp...@halpernwightsoftware.com>  wrote:
>>      2. I am one of those people who prefers to use namespace-qualified name
>> and avoids "using" directives.  It's hard to imagine anything more
>> cumbersome than:
>>      std::chrono:date dt { std::chrono:year(y), std::chrono:month(m),
>> std::chrono:day(d) };
> Won't ADL find them?

I don't see how.  If y is an int, now would ADL know to look in
std::crono for the year function or the year class?

-Pablo

====================================
====================================



Ville Voutilainen
====================================
   Autres options 2 sep, 22:47
On 2 September 2011 23:30, Pablo Halpern

<phalp...@halpernwightsoftware.com> wrote:
>> Won't ADL find them?
> I don't see how.  If y is an int, now would ADL know to look in std::crono
> for the year function or the year class?

Right you are, ADL doesn't help.

====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 3 sep, 09:09

Il giorno 02/set/2011, alle ore 20:00, Pablo Halpern ha scritto:

- Afficher le texte des messages précédents -

Scary. To think that I just proposed the namespace to be spelled std::whatever::gregorian... :-|

By the way, among the several proposed alternatives, we still haven't considered this:

   date dt { ymd, 2010, 9, 3 };

that is: just one mandatory tag followed by three ints. That is not much different from:

   date dt = make_date_ymd(2010, 9, 3);

except for programming style. The mandatory tag could be combined with the "check" tag:

   date dt { ymd_unchecked, 2010, 9, 3 };

if checked is to be the default, or

   date dt { ymd_checked, 2010, 9, 3 };

otherwise. Alternatively, we could not favor either, dropping the ymd and using only the checked/unchecked tags.

>> But we have a more significant difference in the case where the y, m and d variables are obtained in a part of the code and the actual date is constructed elsewhere. Having separate types for year, month, day can be useful to avoid inadvertent exchanges, comparison between the wrong variables, etc. like any physical dimensional analysis library does. We should not underestimate that.
> True.  If we care to make months, days, and years into first-class concepts and not just a means to build a date, then I would be happy to entertain that concept.  A millisecond, for example, is a useful type in and of itself, not just as a way to test a timed mutex.  The fact that a millisecond is type-safe and distinct from a microsecond is useful.  If we want to have month, day, and year be real types independent of date, then I would support having a date constructor or make_date() function that is overloaded using these types -- but     I still would like the three-integer versions.

There actually is an argument against type-tagging here... chrono::seconds, chrono::hours, etc. are really different unit of measures. They are not validated and you can write chrono::hours(10) + chrono::second(500), with a well defined meaning. However, if I write year(2010) or day(5) I really mean a *specific* year and a specific day (of the month). Writing day(1000) makes no sense and an implementation might be expected to assert. It doesn't make sense to write year(2010) + day(5). It's not a case that hours/seconds are plural while year/day are singular. On the other hand we will want to have a "date duration" type whose name could naturally be spelled "days" as in:

   date dt2 { ymd, 2010, 9, 2 };
   date dt3 { ymd, 2010, 9, 3 };
   days diff = dt3 - dt2;

and we might want to have date arithmetic like:

   date dt5 = dt2 + days(3);  //  2010-09-05

or even

   date dtx = dt2 + months(1);  //  2010-10-02

(of course, snapping becomes an issue here, but that's another story)

Having types named both "day" and "days" could definitely be a source of confusion.

Ganesh

====================================
====================================



Robert Klarer
====================================
   Autres options 3 sep, 16:19

On 2011-09-03, at 3:09 AM, Alberto Ganesh Barbati <gan...@barbati.net>

- Afficher le texte des messages précédents -

If the constructor needs to handle various ymd-style tags and perform validity checking, then it can't be a literal constructor. That's one of the reasons I've been advocating make_date. Let's keep the constructor simple and do the more complicated stuff at the make_date level.

====================================
====================================



Alisdair Meredith
====================================
   Autres options 3 sep, 16:26

On 3 Sep 2011, at 10:19, Robert Klarer wrote:

> If the constructor needs to handle various ymd-style tags and perform validity checking, then it can't be a literal constructor. That's one of the reasons I've been advocating make_date. Let's keep the constructor simple and do the more complicated stuff at the make_date level.

Why would the presence of tags cause a problem for making literal values?  I don't see that any of the validation we are expecting cannot be done in a constexpr function, and hence in a constexpr constructor (by calling a constexpr function from an initializer if necessary).

I am having problems reconciling 'assert'-style validation with constexpr constructors, but that seems to be a broad enough language-design issue that I would want to throw it back over to Evolution.

AlisdairM

====================================
====================================



Robert Klarer
====================================
   Autres options 3 sep, 17:37

On Sat, Sep 3, 2011 at 10:26 AM, Alisdair Meredith <w...@alisdairm.net>wrote:

> On 3 Sep 2011, at 10:19, Robert Klarer wrote:

> > If the constructor needs to handle various ymd-style tags and perform
> validity checking, then it can't be a literal constructor. That's one of the
> reasons I've been advocating make_date. Let's keep the constructor simple
> and do the more complicated stuff at the make_date level.

> Why would the presence of tags cause a problem for making literal values?
>  I don't see that any of the validation we are expecting cannot be done in a
> constexpr function, and hence in a constexpr constructor (by calling a
> constexpr function from an initializer if necessary).'

According to 7.1.5, constexpr constructors must have empty function bodies,
apart from:
- typedefs and aliases that don't define classes or enums
- static_assertions
- using declarations and using directives

This means that you can't switch on ymd/mdy/dmy anywhere inside the curly
braces, and you can't do any validity checking. It might be possible to
contrive to do these things in the ctor-initializer list, but that's
cheating, and it sets a bad example.

====================================
====================================



Alisdair Meredith
====================================
   Autres options 3 sep, 17:47

Assuming that 'ymd' etc. Are all the same enum type, and not literals of distinct tag types - which was how I read the this.

AlisdairM

Sent from my iPad

On 3 Sep 2011, at 11:37, Robert Klarer <robert.kla...@gmail.com> wrote:

- Afficher le texte des messages précédents -


====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 3 sep, 20:08

Alisdair is correct. ymd and ymd_checked are supposed to be (constexpr) values of distinct types.

Ganesh

Il giorno 03/set/2011, alle ore 17:47, Alisdair Meredith <w...@alisdairm.net> ha scritto:

- Afficher le texte des messages précédents -


====================================
====================================



Robert Klarer
====================================
   Autres options 3 sep, 20:42

I see. Thanks.
I still maintain that ymd_checked can't be implemented in a literal
constructor, because the code to do the checking cannot be written in the
ctor's function body.

On Sat, Sep 3, 2011 at 2:08 PM, Alberto Ganesh Barbati
<gan...@barbati.net>wrote:

- Afficher le texte des messages précédents -


====================================
====================================



Robert Klarer
====================================
   Autres options 3 sep, 22:25

I should respond to myself (again, sorry) to clarify that I understand that
your intention is that the "unchecked" variant would be a literal
constructor and the "checked" variant would not, but I fear the result will
be misleading:

struct unchecked_t {} unchecked;
struct checked_t {} checked;

stuct date {
int m_; int d_; int y_;
constexpr date(unchecked_t, int m, int d, int y)  : m_(m), d_(d), y_(y) {}
date(checked_t, int m, int d, int y) :  m_(m), d_(d), y_(y) { /* checking
code here */ }

};

date a(unchecked, 12, 31, 2011); // literal
date b(checked, 12, 31, 2011); // not literal

It's not clear from the definition of b that it won't be a literal. The tags
identify one important semantic difference between the two constructor
invocations (i.e., that one is checked and the other is not), and that
implies that there is no other semantic difference. Less misleading names
might be

date a(unchecked_and_potentially_literal, 12, 31, 2011); // literal
date b(checked, 12, 31, 2011); // not literal

Of course, that's absurd. An alternative is to introduce "literal" as a
synonym for "unchecked":

int m = 12; int d = 31; int y = 2011;

date a(literal, 12, 31, 2011);
date b(unchecked, m, d, y); // unchecked, but not a literal
date c(checked, 12, 31, 2011); // checked and not a literal

Unfortunately, the literal tag isn't enforced:
date d(literal, m, d, y); // unchecked, not a literal

I don't like tags.

On Sat, Sep 3, 2011 at 2:42 PM, Robert Klarer <robert.kla...@gmail.com>wrote:

- Afficher le texte des messages précédents -


====================================
====================================



Alisdair Meredith
====================================
   Autres options 3 sep, 22:40

On 3 Sep 2011, at 16:25, Robert Klarer wrote:

- Afficher le texte des messages précédents -

I still don't understand why the checked form can't be a literal constructor:

date::date(unchecked_tag, int year, int month, int day)
   : date{ !is_valid_ymd(year, month, day) ? throw bad_date{} : unchecked, year, month, day)
   {

}

constexpr bool is_valid_ymd(int year, int month, int day ) {
   return year >= MIN_SUPPORTED_YEAR
    && year <= MAX_SUPPORTED_YEAR
    && month > 0
    && month < 13
    && day > 0
    && day < days_in_month(year, month);
)

I'm leaving days_in_month(...) as an exercise for the reader as the point is simply to show that there is no fundamental reason that the checked constructor not be constexpr.

You might not like the style of the implementation, but that's a different matter.  Fundamentally, both checked and unchecked constructors may be defined as constexpr.

The tricky part is adding assertions to the 'unchecked' constructor in 'defensive' build modes.

AlisdairM

====================================
====================================



Robert Klarer
====================================
   Autres options 3 sep, 22:57

On Sat, Sep 3, 2011 at 4:40 PM, Alisdair Meredith <w...@alisdairm.net>wrote:

- Afficher le texte des messages précédents -

I agree that the standard allows what you've written, but I don't believe
that it will work in practice. Maybe my understanding of literal classes is
flawed, but I thought that the point of literals is that you can use them in
contexts where compile-time constant values are needed. A throw statement is
definitely not something that will be computed at compile time, so a
constructor with a throw in it is not a literal constructor, regardless of
the constexpr specifier.

If 7.1.5 prohibits you from writing something in the literal constructor's
function body, you should assume that you can't write it in the
ctor-initializer list, either, regardless of what the standard seems to
permit.

Maybe core already has an issue open for this. I will check...

====================================
====================================



Ville Voutilainen
====================================
   Autres options 3 sep, 23:01
On 3 September 2011 23:57, Robert Klarer <robert.kla...@gmail.com> wrote:

> If 7.1.5 prohibits you from writing something in the literal constructor's
> function body, you should assume that you can't write it in the
> ctor-initializer list, either, regardless of what the standard seems to
> permit.
> Maybe core already has an issue open for this. I will check...

If a ternary operator expression throws, it's not a constant expression. If it
doesn't throw, it can be, and in this case is.

====================================
====================================



Alisdair Meredith
====================================
   Autres options 3 sep, 23:05

On 3Sep, 2011, at 4:57 PM, Robert Klarer wrote:

- Afficher le texte des messages précédents -

constexpr functions are perfectly allowed to throw exceptions.  Remember a constexpr function is also a regular runtime function, and will have that runtime behavior if called with non-literal values.

On the other hand, if you call a constexpr constructor in a context where it absolutely must be evaluated as a literal, e.g.:

constexpr date bad{2011, 2, 30};

The attempt to throw an exception at compile time is a diagnosable error, and the compiler must report the error to you.

This interpretation was confirmed with experts from Core in Bloomington.

AlisdairM

====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 3 sep, 23:13
Il giorno 03/set/2011, alle ore 22:40, Alisdair Meredith <w...@alisdairm.net> ha scritto:

> The tricky part is adding assertions to the 'unchecked' constructor in 'defensive' build modes.

Yup. Please notice that the issue isn't related with constructors and tags. Even if you define a factory function like make_date_ymd you will encounter the same difficulty in having it both constexpr and asserting.

My point is that any make_date function can be made into a tagged constructor and vice-versa. In the standard, make_ functions are used when type deduction can help omitting some template argument. We do not have that need here, so I find it difficult to prefer them to constructors. Just my opinion.

Ganesh

====================================
====================================



Robert Klarer
====================================
   Autres options 3 sep, 23:21

On Sat, Sep 3, 2011 at 5:13 PM, Alberto Ganesh Barbati <gan...@barbati.net>

> My point is that any make_date function can be made into a tagged
> constructor and vice-versa. In the standard, make_ functions are used when
> type deduction can help omitting some template argument. We do not have that
> need here, so I find it difficult to prefer them to constructors. Just my
> opinion.

> Ganesh

Daniel has pointed out that make_error_code and make_error_condition do not
exist for type deduction reasons.

====================================
====================================



bs
====================================
   Autres options 3 sep, 23:22

On 9/3/2011 4:13 PM, Alberto Ganesh Barbati wrote:

> In the standard, make_ functions are used when type deduction can help omitting some template argument. We do not have that need here, so I find it difficult to prefer them to constructors. Just my opinion.

I agree. Where constructors can be used they should be.

Robert Klarer
====================================
   Autres options 3 sep, 23:36

On Sat, Sep 3, 2011 at 5:05 PM, Alisdair Meredith <w...@alisdairm.net>wrote:

On the other hand, if you call a constexpr constructor in a context where it

> absolutely must be evaluated as a literal, e.g.:

> constexpr date bad{2011, 2, 30};

> The attempt to throw an exception at compile time is a diagnosable error,
> and the compiler must report the error to you.

> This interpretation was confirmed with experts from Core in Bloomington.

Thanks. I didn't know that. I just figured the compiler would just crash in
such cases.

My insistence on make_date was based on the assumption that you couldn't do
checking in a literal constructor, so I wanted to separate out the checking
part into a different layer.

Sorry for wasting everyone's time on this list. If someone had volunteered
to sponsor my attendance at the meetings this all could have been avoided.
:-)

Off-topic:

Is someone working on a proposal to enhance static_assert so that it does
something benign if the conditional expression is not constant? I can't see
a safe way to use them in constexpr functions otherwise.

====================================
====================================



Howard Hinnant
====================================
   Autres options 3 sep, 23:52
On Sep 3, 2011, at 5:36 PM, Robert Klarer wrote:

> Sorry for wasting everyone's time on this list. If someone had volunteered to sponsor my attendance at the meetings this all could have been avoided. :-)

Wish I could. :-)  Nevertheless, I haven't detected any wasted time here.

Question, if I may:

Setting aside (only temporarily) all the wonderful ways we might construct a date, let's assume for a moment said date d is constructed.

Now what?  What do we want to be able to do with date d?

I ask now because I'm leery of designing the "perfect" constructor without ever considering any of the use cases for date.  I think it would be a good idea to not design /any/ aspect of date in complete isolation from all other aspects.   A little iteration among the several aspects of date would be a good thing.

Howard

====================================
====================================



Ville Voutilainen
====================================
   Autres options 4 sep, 00:52
On 4 September 2011 00:52, Howard Hinnant <howard.hinn...@gmail.com> wrote:

> Question, if I may:
> Setting aside (only temporarily) all the wonderful ways we might construct a date, let's assume for a moment said date d is constructed.
> Now what?  What do we want to be able to do with date d?
> I ask now because I'm leery of designing the "perfect" constructor without ever considering any of the use cases for date.  I think it would be a good idea to not design /any/ aspect of date in complete isolation from all other aspects.   A little iteration among the several aspects of date would be a good thing.

Well, I expect to be able to less-than (and/or equal) compare dates
and add (or subtract) days to (from) a date object.
I have stumbled upon two very important use cases where an easy-to-use
date facility would be useful:

1) is date(today) greater or equal than a date(launch_missiles)
2) is date(today) greater or equal than a date(base_date +
launch_missiles_offset)
(the offset is n days)

These use cases aren't theoretical, although you may replace
"launch_missiles" with "delete stuff
from database". And I've seen what the mistakes, or not having an easy
way to do those operations,
cost - they cost reports like "your data is now in a better place,
don't be sad". :)

I'm hesitant to talk about calendar-ish operations(*), I don't know
whether those are closely related to
date or whether they should be something kept separate or built on top
of a date. Any clues are
welcome.

(*) "From a starting date, give me every weekday for a timespan of 6
months", or "every sunday for
12 weeks" and such. There's a whole host of dvr-ish stuff that could
use such facilities for
scheduled recordings...

====================================
====================================



Howard Hinnant
====================================
   Autres options 4 sep, 01:49
On Sep 3, 2011, at 6:52 PM, Ville Voutilainen wrote:

- Afficher le texte des messages précédents -

My opinion:  We should target gregorian and only gregorian.  As soon as we add constructors in terms of gregorian year, month and day, we are putting ourselves firmly in the gregorian calendar territory.  That means we have to answer questions like what does it mean to add a month or year, and what is the day of the week.  And how many days are there in a month?  In a year?

Being able to easily specify, recognize and test against common holidays (including weekends) is important in many applications (many businesses don't function on holidays and must account for that).  Exception:  I'm happy to ignore the specification of Easter and other holidays that require extraordinary effort and/or special casing.

Where and how we answer those questions is a good debate.  But I don't think I could vote for a proposal that simply ignores these questions.

> (*) "From a starting date, give me every weekday for a timespan of 6
> months", or "every sunday for
> 12 weeks" and such. There's a whole host of dvr-ish stuff that could
> use such facilities for
> scheduled recordings...

So, starting to prototype:

namespace std { namespace chrono {  // Uncontroversial?

typedef duration<int_least32_t, ratio<86400>> days;  // Uncontroversial?

class date
{
    // unspecified data
    // ...
public:
    date() noexcept;  // as fast as possible?
    // other constructors
    // ...
    date(const date&)  noexcept = default;
    date& operator=(const date&)  noexcept = default;
    ~date() noexcept = default;

    // observers?

    // day oriented arithmetic
    date& operator+=(days d);
    date& operator-=(days d);
    friend date operator+(date x, days y);
    friend date operator+(days x, date y);
    friend date operator-(date x, days y);
    friend days operator-(date x, date y);

    // increment / decrement?
    date& operator++();   // or should this be named tomorrow?
    date  operator++(int);
    date& operator--();   // or should this be named yesterday?
    date  operator--(int);

    // comparisons
    friend bool operator==(const date& x, const date& y);
    friend bool operator!=(const date& x, const date& y);
    friend bool operator< (const date& x, const date& y);
    friend bool operator> (const date& x, const date& y);
    friend bool operator<=(const date& x, const date& y);
    friend bool operator>=(const date& x, const date& y);

};
}} // namespace end

I'm trying to hit the least controversial points here.  Where have I over-stepped?  And what can I add without controversy?  Observers?  I/O? Factory function for today?  Conversions to/from std::chrono::system_clock::time_point?

I've neglected to add constexpr, partly out of ignorance, mostly out of inability to test, and also wanting to be cautious about prematurely outlawing specific implementations without discussion.

Howard

====================================
====================================



Ville Voutilainen
====================================
   Autres options 4 sep, 02:57
On 4 September 2011 02:49, Howard Hinnant <howard.hinn...@gmail.com> wrote:

> I'm trying to hit the least controversial points here.  Where have I over-stepped?  And what can I add without controversy?  Observers?  I/O? Factory function for today?  Conversions to/from std::chrono::system_clock::time_point?

I expect observers to be, while not necessarily quite controversial,
something that will sparkle a lively discussion. :)

Perhaps discussing i/o will have to wait until there's some clarity on
observers? I do expect there to be some
observers, but what kind of observers exactly, I don't know yet. Off
the top of my hat I'd foolishly expect that
while we need to construct from raw ints, it's less necessary to be
able to observe raw int values.

I would think that making it easy to create a date for today is
fundamentally important.

====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 4 sep, 10:22
Il giorno 04/set/2011, alle ore 01:49, Howard Hinnant <howard.hinn...@gmail.com> ha scritto:

> My opinion:  We should target gregorian and only gregorian.  As soon as we add constructors in terms of gregorian year, month and day, we are putting ourselves firmly in the gregorian calendar territory.

In the design that I proposed in a previous post, the gregorian::date class is devoted to gregorian. However the design accommodates for other calendar classes in different namespaces (for example chinese::date). The post also showed how to realize a calendar_cast function to convert between calendars.

That said, I'm ok with focusing on gregorian as long as we describe a path for future extensions.

> Being able to easily specify, recognize and test against common holidays (including weekends) is important in many applications (many businesses don't function on holidays and must account for that).  Exception:  I'm happy to ignore the specification of Easter and other holidays that require extraordinary effort and/or special casing.

Special holidays enter the realm of localization. I believe the user might simply check against a suitably created std::map. We don't need to support that.

> So, starting to prototype:

> namespace std { namespace chrono {  // Uncontroversial?

That might be good for general utilities and cross-calendar facilities. Gregorian date-specific classes should go in a nested namespace, we could make it an inline namespace though.

> typedef duration<int_least32_t, ratio<86400>> days;  // Uncontroversial?

I have to think about that. What are the pros and cons against having a specific class which could have an implicit conversion to duration<>?

Ganesh

====================================
====================================



Howard Hinnant
====================================
   Autres options 4 sep, 18:14
On Sep 4, 2011, at 4:22 AM, Alberto Ganesh Barbati wrote:

> Il giorno 04/set/2011, alle ore 01:49, Howard Hinnant <howard.hinn...@gmail.com> ha scritto:

>> My opinion:  We should target gregorian and only gregorian.  As soon as we add constructors in terms of gregorian year, month and day, we are putting ourselves firmly in the gregorian calendar territory.

> In the design that I proposed in a previous post, the gregorian::date class is devoted to gregorian. However the design accommodates for other calendar classes in different namespaces (for example chinese::date). The post also showed how to realize a calendar_cast function to convert between calendars.

I already dislike the length of the namespace std::chrono.  But I was overridden on that one.  I'd really like to not further lengthen it.  As it is, *every* time I'm using chrono facilities I find myself writing typedefs just for the purpose of short cuts:

int main()
{
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::duration<double> sec;
    Clock::time_point t0 = Clock::now();
    // time stuff...
    Clock::time_point t1 = Clock::now();
    std::cout << sec(t1-t0).count() << " seconds\n";

}

> That said, I'm ok with focusing on gregorian as long as we describe a path for future extensions.

Have you considered the path described in http://home.roadrunner.com/~hinnant/bloomington/date.html "Interoperability with other calendar systems"?

>> Being able to easily specify, recognize and test against common holidays (including weekends) is important in many applications (many businesses don't function on holidays and must account for that).  Exception:  I'm happy to ignore the specification of Easter and other holidays that require extraordinary effort and/or special casing.

> Special holidays enter the realm of localization. I believe the user might simply check against a suitably created std::map. We don't need to support that.

I don't think I was clear on this one.  I don't propose that we enumerate holidays.  I propose that we provide the ability to easily compute them.  E.g. we have already shown that we want to be able to enter dates corresponding to a gregorian year, month and day.  This is sufficient to compute holidays such as New Years and Christmas.  I also propose that we provide facilities to specify (for example) the first Monday in September for year y so that one can easily compute Labor Day in the US.  I do not propose that we create a list of holidays that includes New Years, Christmas, or the US Labor day.

Being able to specify the 1st, 2nd, 3rd, 4th or last weekday of a month for a given year is sufficient to specify all official US holidays.  I'm not proposing anything more than that.  If someone else points out another relatively simple computation that would also be of general use (e.g. the Monday on or before Jan 4 is the start of the ISO week-based year), I'm open to that.  Computing nearest weekday from a date is generally useful.  But I do not think we should get into computing phases of the moon, an equinox or solstice.

>> So, starting to prototype:

>> namespace std { namespace chrono {  // Uncontroversial?

> That might be good for general utilities and cross-calendar facilities. Gregorian date-specific classes should go in a nested namespace, we could make it an inline namespace though.

>> typedef duration<int_least32_t, ratio<86400>> days;  // Uncontroversial?

> I have to think about that. What are the pros and cons against having a specific class which could have an implicit conversion to duration<>?

Pros:

days (as specified above) would be implicitly convertible to our other std::chrono::durations: hours, minutes, seconds, milliseconds, etc.  But the conversion in the opposite direction (to days) could only be done via duration_cast.  Such conversions might make multi-day countdowns to a specific event more convenient to code:  Only 100 hours and 40 minutes until Product X goes on sale!

The concept of days /is/ a duration.  day, abbreviated d, with a definition of 86400 SI seconds is a unit that is accepted for use with the International System of Units (http://www.bipm.org/en/si/si_brochure/chapter4/table6.html).

Cons:

Its use will bring leap-second enthusiasts out.  They will be quick to point out that we've made a mistake.  There's this new fangled thing we've obviously never heard of called leap seconds and thus a day can not possibly be defined as 86400 seconds.  My response:  If you care about leap seconds then std::chrono::date and std::chrono::days are only basic building blocks for the tools you're looking for.  You'll have to include (and update) your own table of leap second insertions.  No OS I'm aware of even acknowledges the existence of leap seconds for their std::chrono::system_clock (http://en.wikipedia.org/wiki/Unix_time) (http://support.microsoft.com/kb/909614).  These are not the droids you're looking for.  Move along.

Also note: http://en.wikipedia.org/wiki/Leap_second#Proposal_to_abolish_leap_sec...

Alternatives:

This operator has to return something:

   auto operator-(date x, date y) -> ?;

The choices I can imagine are:

1.  int_least32_t
2.  duration<int_least32_t, ratio<86400>>
3.  A class that has no interoperability with std::chrono::duration.

Now imagine you've written some duration utility such as round() or display_as_broken_down_time().  Here's round:

// round to nearest, to even on tie

template <class To, class Rep, class Period>
To
round(const std::chrono::duration<Rep, Period>& d)
{
    To t0 = std::chrono::duration_cast<To>(d);
    To t1 = t0;
    ++t1;
    auto diff0 = d - t0;
    auto diff1 = t1 - d;
    if (diff0 == diff1)
    {
        if (t0.count() & 1)
            return t1;
        return t0;
    }
    else if (diff0 < diff1)
        return t0;
    return t1;

}

One can easily imagine wanting to write code like:

    hours h = round<hours>(d2-d1);

and:

    d1 += round<days>(h);

If we choose 1, this would look more like:

    hours h = round<hours>(duration<int_least32_t, ratio<86400>>(d2-d1));

and:

    d1 += round<duration<int_least32_t, ratio<86400>>(h).count();

If we choose 3, this would look more like:

    hours h = round<hours>(duration<int_least32_t, ratio<86400>>((d2-d1).count()));

and:

    d1 += days(round<duration<int_least32_t, ratio<86400>>(h).count());

Or one could just write the conversion arithmetic between days and std::chrono::hours manually, not using your carefully written and debugged chrono utility functions such as round and display_as_broken_down_time.  Of course you'll probably need to convert to minutes, seconds, maybe milliseconds too.

Howard

====================================
====================================



Nevin Liber
====================================
   Autres options 4 sep, 18:37
On 4 September 2011 11:14, Howard Hinnant <howard.hinn...@gmail.com> wrote:

>  But I do not think we should get into computing phases of the moon, an equinox or solstice.

I agree.  Much of that can be calculated if you have a different
calendar, such as lunar.

> Pros:

> days (as specified above) would be implicitly convertible to our other std::chrono::durations: hours, minutes, seconds, milliseconds, etc.  But the conversion in the opposite direction (to days) could only be done via duration_cast.  Such conversions might make multi-day countdowns to a specific event more convenient to code:  Only 100 hours and 40 minutes until Product X goes on sale!

> The concept of days /is/ a duration.  day, abbreviated d, with a definition of 86400 SI seconds is a unit that is accepted for use with the International System of Units (http://www.bipm.org/en/si/si_brochure/chapter4/table6.html).

> Cons:

> Its use will bring leap-second enthusiasts out.

Also dayliight savings time.  Your "pro" breaks down in that case.
Similar issues with converting between time zones.

It's a bit weird to be designing a date class completely distinct from
a time class, since many of the things we want to do with dates depend
on the time of day as well as location.

Canonical example:  "I want to eat lunch at noon every weekday, so
I'll block it off on my calendar" vs. "I want to schedule a
teleconference every weekday at noon so I can catch up on what my
colleagues around the world are doing."  (Heck, neither is an
"absolute" date; the first one is relative to wherever I happen to be,
which the second is relative to my home location.)

I'm not saying we shouldn't define day as 86400 seconds; it's just
that there will be controversy no matter what we do.
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



Howard Hinnant
====================================
   Autres options 4 sep, 19:17
On Sep 4, 2011, at 12:37 PM, Nevin Liber wrote:

- Afficher le texte des messages précédents -

You make a good point.  Let's include std::chrono::system_clock::time_point in the conversation.  This is a time_point already in the standard that on every platform I know tracks UTC to at least millisecond precision.  This type is truly a date-time, but with an extremely limited interface.  One can, using completely std::components, I/O it in terms of the gregorian calendar:

#include <ctime>
#include <chrono>
#include <iostream>

int main()
{
   typedef std::chrono::system_clock Clock;
   auto tt = Clock::to_time_t(Clock::now());
   std::cout << std::ctime(&tt) << '\n';

}

Sun Sep  4 13:12:07 2011

Note that I had to make a conscious decision as to what time zone to perform the I/O.  The C/C++ standards give me two choices:  My local time zone, or UTC.

On date:  This object is nothing but a count of sunrises.  Subtracting dates is going to return an integral number of rotations of the earth, no matter how we package it.  I'm not currently seeing how any of:

1.  int_least32_t
2.  duration<int_least32_t, ratio<86400>>
3.  A class that has no interoperability with std::chrono::duration.

impacts differently issues with time zones, leap seconds, or setting events down to the minute on a calendar.

Howard

====================================
====================================



Howard Hinnant
====================================
   Autres options 4 sep, 23:01
On Sep 4, 2011, at 1:17 PM, Howard Hinnant wrote:

> On date:  This object is nothing but a count of sunrises.  Subtracting dates is going to return an integral number of rotations of the earth, no matter how we package it.  I'm not currently seeing how any of:

> 1.  int_least32_t
> 2.  duration<int_least32_t, ratio<86400>>
> 3.  A class that has no interoperability with std::chrono::duration.

> impacts differently issues with time zones, leap seconds, or setting events down to the minute on a calendar.

It occurred to me that some of you may not be familiar with std::chrono::duration.  So here is a very brief description:

In each of the 3 choices above, if one subtracts today from tomorrow, a 1 is stored as the return.  Nothing more.  sizeof(duration<int_least32_t, ratio<86400>>) == sizeof(int_least32_t).  The only real difference between int_least32_t(1) and duration<int_least32_t, ratio<86400>>(1) is that the latter comes with preprogrammed conversions to our other duration types.  Oh, and the latter is a distinct type with no implicit conversion to int_least32_t so that it can not be confused with other int_least32_t that do not represent a number of earth rotations.  It does have an explicit conversion though using a count() member function, which does nothing but return the internally stored int_least32_t:

int_least32_t                         d1(1);
duration<int_least32_t, ratio<86400>> d2(1);
assert(d1 == d2.count());

int_least32_t ms1 = 86400000 * d1;
milliseconds  ms2 = d2;
assert(ms1 == ms2.count());

static_assert( std::is_same<decltype(d1),
                            decltype(ms1)>::value,
               "d1 and ms1 should be the same type");
static_assert(!std::is_same<decltype(d2),
                            decltype(ms2)>::value,
               "d2 and ms2 should not be the same type");

So the questions are:

A.  Do we want a distinct (non-int) type for the return of date subtraction?
    Yes, choose 2 or 3.
    No, choose 1.

B.  If we want a distinct type, do we want to provide conversions to our existing duration types?
    Yes, choose 2.
    No, choose 3.

Howard

====================================
====================================



JOHN LAKOS, BLOOMBERG/ 731 LEXIN
====================================
   Autres options 4 sep, 23:05
All, I have the following questions/observations regarding Howard's proposed baseline 'date' class:

1. It is not clear to me why we need to build any sort of duration into
   the difference operator between two dates.  The difference between to
   date objects is integral: Unless we are using date objects in a different
   context -- e.g., one in which involves local time zones and DST (or leap
   seconds) -- for me, it's just the (signed) integer number of whole days
   between the two dates.  Bottom line: ++date is NOT necessarily 86,400
   seconds later, it IS one day later.

2. I would not have bothered to use 'int_least32_t' as the result type for a
   primitive date-difference operation because nothing we write at Bloomberg
   would work if 'int' were 16 bits.  I suspect this is true for most people
   who write C++, but I could live with 'int_least32_t' for the C++ standard
   if that's what makes people feel confortable, but then I'd want to see
   where else we use 'int' in the standard and clean that up too (if necessary).

3. The difference between two 'date_time' types is a 'date_time_interval', but
   not of any particular precision.  Building the precision into the difference
   type would be brittle and (IMO) a mistake.  (Type-safe programming can
   ensure that dimensions are correct at compile time.  Dimensions are
   distance, time, velocity, acceleration, etc., but not specific units like
   meters, seconds, meters-per-second, etc.).

4. With a 'date_time', there is again no notion of local timezone or leap
   seconds; hence, these concepts should be addressed at a higher level.

5. We (at Bloomberg) would need accessors of the 'date' type for the year,
   month, and day fields that (somehow) return 'int' year, 'int' month, and
   'int' day.

6. The prefixe ++ and -- operators on date are *no*t to be named 'tomorrow' or
   'yesterday', as they modify the object!  Even calling them 'makeTomorrow'
   (and 'makeYesterday') would be wrong, as the name would suggest that the
   operation is independent of the current value.  The prefix operators are
   unambiguous and correct, especially given the contiguous integral nature of
   date values.

7. By the same token, date += 3 modifies this date to be 3 days after its
   original value (unambiguous).  int days = d2 - d1; assert (d2 == d1 + days);

8. As a general matter, postfix operators should not be members.  The only
   use case for making the postfix operators members is to modify an unnamed
   temporary object, which is certainly a bug (and it is also inconstant with
   the behavior w.r.t. user-defined conversion for fundamental types).  I
   propose that we make the two postfix operators, free (but not friend)
   operators,  and implement them -- by definition ("as if") -- in terms of
   their corresponding member prefix operators.

                                                             -John Lakos

- Afficher le texte des messages précédents -


====================================
====================================



Howard Hinnant
====================================
   Autres options 5 sep, 02:33
On Sep 4, 2011, at 5:05 PM, JOHN LAKOS, BLOOMBERG/ 731 LEXIN wrote:

> All, I have the following questions/observations regarding Howard's proposed baseline 'date' class:

> 1. It is not clear to me why we need to build any sort of duration into
>   the difference operator between two dates.  The difference between to
>   date objects is integral: Unless we are using date objects in a different
>   context -- e.g., one in which involves local time zones and DST (or leap
>   seconds) -- for me, it's just the (signed) integer number of whole days
>   between the two dates.  Bottom line: ++date is NOT necessarily 86,400
>   seconds later, it IS one day later.

I can respect that view.  However I wanted to add: if we were to choose duration<int_least32_t, ratio<86400>>, or class days{}, there is zero overhead.  I can supply assembly examples demonstrating that if that would help (in case it makes a difference to anyone).

> 2. I would not have bothered to use 'int_least32_t' as the result type for a
>   primitive date-difference operation because nothing we write at Bloomberg
>   would work if 'int' were 16 bits.  I suspect this is true for most people
>   who write C++, but I could live with 'int_least32_t' for the C++ standard
>   if that's what makes people feel confortable, but then I'd want to see
>   where else we use 'int' in the standard and clean that up too (if necessary).

I did a quick survey, and actually we've done fairly well over the years with respect to this issue in the standard.  There may be a couple of places where int isn't quite the right type.  But I believe them to be relatively rare.  I believe we can not assume at this point that int is greater than 16 bits (our standard says otherwise).

> 3. The difference between two 'date_time' types is a 'date_time_interval', but
>   not of any particular precision.  Building the precision into the difference
>   type would be brittle and (IMO) a mistake.  (Type-safe programming can
>   ensure that dimensions are correct at compile time.  Dimensions are
>   distance, time, velocity, acceleration, etc., but not specific units like
>   meters, seconds, meters-per-second, etc.).

Informational:

The difference between two std::chrono::system_clock::time_point has type std::chrono::system_clock::duration.  The precision of this duration type is unspecified but inspectable at compile time (and thus self-documenting).  The implicit precision conversion logic among the duration types ensures that you can convert std::chrono::system_clock::duration to a known duration of your choosing, and either it will compile and there will be no truncation error, or it will fail to compile.

For example assume that std::chrono::system_clock::duration is a synonym for std::chrono::milliseconds and internally represented with a long long (as I suspect it is (or will be) in VC++).  Then the following code will compile, and the arithmetic will be exact:

using namespace std::chrono;
system_clock::time_point t0 = system_clock::now();
// do stuff
system_clock::time_point t1 = system_clock::now();
microseconds us = t1 - t0;  // exact & implicit conversion from milliseconds to microseconds represented with signed integral type
duration<double> dsec = t1 - t0;   // implicit conversion  from milliseconds to seconds represented with double
                                   // the above conversion is subject to round-off error, but not truncation error

However the following will not compile:

seconds isec = t1 - t0;  // compile time error.
                         // seconds is an integral duration and the conversion from milliseconds is subject to truncation error

The conversions among duration types have exactly the same efficiency as hand-coded conversions, even when the conversion is identity:

milliseconds ms = t1 -t0;  // nothing but a long long subtraction and assignment

Emphasis:  The above will generate the exact same assembly as:

  long long t0 = ...
  long long t1 = ...
  long long ms = t1 - t0;

and:

  microseconds us = t1 - t0;

generates the same assembly as:

  long long t0 = ...
  long long t1 = ...
  long long us = (t1 - t0) * 1000;

> 4. With a 'date_time', there is again no notion of local timezone or leap
>   seconds; hence, these concepts should be addressed at a higher level.

Agreed.  And I think this is consistent with std::chrono::system_clock::time_point.

> 5. We (at Bloomberg) would need accessors of the 'date' type for the year,
>   month, and day fields that (somehow) return 'int' year, 'int' month, and
>   'int' day.

and weekday?  [Sun - Sat] == [0 - 6]?

> 6. The prefixe ++ and -- operators on date are *no*t to be named 'tomorrow' or
>   'yesterday', as they modify the object!  Even calling them 'makeTomorrow'
>   (and 'makeYesterday') would be wrong, as the name would suggest that the
>   operation is independent of the current value.  The prefix operators are
>   unambiguous and correct, especially given the contiguous integral nature of
>   date values.

Thank you!  I'm glad somebody was awake! :-)

I envision "date day iteration" to be popular and coded similar to:

   date start_date = ...
   date end_date = ...
   for(; start_date <= end_date; ++start_date)
      // do stuff with start_date

For C++ programmers this is a lot more readable than something like:

   for(; start_date <= end_date; start_date.tomorrow())
      // do stuff with start_date

> 7. By the same token, date += 3 modifies this date to be 3 days after its
>   original value (unambiguous).  int days = d2 - d1; assert (d2 == d1 + days);

I agree in spirit, especially with the algebraic consistency.  I do worry about:

    int get_time_since();
    ...
    date += get_time_since();

One has to read the docs to find out what units get_time_since() is returning.  The compiler won't catch the error if the units aren't days.

> 8. As a general matter, postfix operators should not be members.  The only
>   use case for making the postfix operators members is to modify an unnamed
>   temporary object, which is certainly a bug (and it is also inconstant with
>   the behavior w.r.t. user-defined conversion for fundamental types).  I
>   propose that we make the two postfix operators, free (but not friend)
>   operators,  and implement them -- by definition ("as if") -- in terms of
>   their corresponding member prefix operators.

I like this suggestion!  Too bad the rest of the standard is patterned after this.  Use of "rvalue-this" would be another way to get the same effect:

struct A
{
    A operator++(int)&;

};

Howard

- Afficher le texte des messages précédents -

...

plus de détails »

====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 5 sep, 09:41

Il giorno 05/set/2011, alle ore 02:33, Howard Hinnant ha scritto:

> On Sep 4, 2011, at 5:05 PM, JOHN LAKOS, BLOOMBERG/ 731 LEXIN wrote:

>> All, I have the following questions/observations regarding Howard's proposed baseline 'date' class:

>> 1. It is not clear to me why we need to build any sort of duration into
>>  the difference operator between two dates.  The difference between to
>>  date objects is integral: Unless we are using date objects in a different
>>  context -- e.g., one in which involves local time zones and DST (or leap
>>  seconds) -- for me, it's just the (signed) integer number of whole days
>>  between the two dates.  Bottom line: ++date is NOT necessarily 86,400
>>  seconds later, it IS one day later.

> I can respect that view.  However I wanted to add: if we were to choose duration<int_least32_t, ratio<86400>>, or class days{}, there is zero overhead.  I can supply assembly examples demonstrating that if that would help (in case it makes a difference to anyone).

Howard's argument sounds convincing to me. The link Howard provided clearly shows that at least one international standard defines day as 86400 seconds. The *only* reason I see to not adopt duration<int_least32_t, ratio<86400>> for days is if we wanted to support leap seconds at the basic level. However, I see some agreement that we should consider leap seconds at that level.

>> 2. I would not have bothered to use 'int_least32_t' as the result type for a
>>  primitive date-difference operation because nothing we write at Bloomberg
>>  would work if 'int' were 16 bits.  I suspect this is true for most people
>>  who write C++, but I could live with 'int_least32_t' for the C++ standard
>>  if that's what makes people feel confortable, but then I'd want to see
>>  where else we use 'int' in the standard and clean that up too (if necessary).

> I did a quick survey, and actually we've done fairly well over the years with respect to this issue in the standard.  There may be a couple of places where int isn't quite the right type.  But I believe them to be relatively rare.  I believe we can not assume at this point that int is greater than 16 bits (our standard says otherwise).

I have no problems with int_least32_t. It's probably going to be defined to be int on most platforms, anyway.

The only place in the library where int is used and really shouldn't is in the specification of gbump/pbump. I believe there is already a DR about it.

>> 3. The difference between two 'date_time' types is a 'date_time_interval', but
>>  not of any particular precision.  Building the precision into the difference
>>  type would be brittle and (IMO) a mistake.  (Type-safe programming can
>>  ensure that dimensions are correct at compile time.  Dimensions are
>>  distance, time, velocity, acceleration, etc., but not specific units like
>>  meters, seconds, meters-per-second, etc.).

In my proposal, the date_time class is a templated wrapper over date and a duration. So you can have:

basic_date_time<date, milliseconds> d1; // time-of-day measured in milliseconds
basic_date_time<date, microseconds> d2; // time-of-day measured in microseconds
date_time d3; // an alias representing a reasonable default (seconds? milliseconds? we decide)

(the first argument of basic_date_date takes a date to accommodate for different calendars)

The time_duration arithmetic takes care of all the conversions as described by Howard.

>> 4. With a 'date_time', there is again no notion of local timezone or leap
>>  seconds; hence, these concepts should be addressed at a higher level.

> Agreed.  And I think this is consistent with std::chrono::system_clock::time_point.

Agreed.

>> 6. The prefixe ++ and -- operators on date are *no*t to be named 'tomorrow' or
>>  'yesterday', as they modify the object!  Even calling them 'makeTomorrow'
>>  (and 'makeYesterday') would be wrong, as the name would suggest that the
>>  operation is independent of the current value.  The prefix operators are
>>  unambiguous and correct, especially given the contiguous integral nature of
>>  date values.

> Thank you!  I'm glad somebody was awake! :-)

I don't like ++ and -- very much. I'd prefer if we forced the user to a more explicit:

  d += days(1);

> I envision "date day iteration" to be popular and coded similar to:

>   date start_date = ...
>   date end_date = ...
>   for(; start_date <= end_date; ++start_date)
>      // do stuff with start_date

> For C++ programmers this is a lot more readable than something like:

>   for(; start_date <= end_date; start_date.tomorrow())
>      // do stuff with start_date

I believe we should investigate the possibility of having syntaxes like:

  for (date d : date_range(start_date, end_date))
     // ...

or even

  for (date d : day_iteration(start_date, end_date))
     // ...

  for (date d : month_iteration(start_date, end_date))
     // ...

or something like that. We could create a whole sort of date range traversals algorithms without having to overload a single iterator class, while having them totally decoupled from the date class.  Such algorithms could also be used with regular algorithms, of course:

  week_iteration wi(start_date, end_date);
  for_each(wi.begin(), wi.end(), ...)

>> 7. By the same token, date += 3 modifies this date to be 3 days after its
>>  original value (unambiguous).  int days = d2 - d1; assert (d2 == d1 + days);

> I agree in spirit, especially with the algebraic consistency.  I do worry about:

>    int get_time_since();
>    ...
>    date += get_time_since();

> One has to read the docs to find out what units get_time_since() is returning.  The compiler won't catch the error if the units aren't days.

I totally agree with Howard. The difference between two dates should be typed and type "days" shouldn't be implicitly convertible to integers. Accordingly, you should also be disallowed to add integers to a date.

Ganesh

====================================
====================================



Alberto Ganesh Barbati
====================================
   Autres options 5 sep, 12:34

Il giorno 03/set/2011, alle ore 23:21, Robert Klarer <robert.kla...@gmail.com> ha scritto:

> On Sat, Sep 3, 2011 at 5:13 PM, Alberto Ganesh Barbati <gan...@barbati.net>

> My point is that any make_date function can be made into a tagged constructor and vice-versa. In the standard, make_ functions are used when type deduction can help omitting some template argument. We do not have that need here, so I find it difficult to prefer them to constructors. Just my opinion.

> Daniel has pointed out that make_error_code and make_error_condition do not exist for type deduction reasons.

make_error_code and make_error_condition are customizable extension points. They are not expected to be used directly by the user, although it would be no harm to do it. For example, I can write

  std::io_errc ioerr = ...;

  std::error_code ec(ioerr); // eventually calls make_error_code(ioerr);

I don't need (and I am not expected) to write:

 std::error_code ec = make_error_code(ioerr);

As you can see, the motivation and the design pattern (which includes the specialization of the is_error_code_enum trait class) is totally different what we would have with date.

Ganesh

====================================
====================================



Nevin Liber
====================================
   Autres options 5 sep, 20:34
On 5 September 2011 02:41, Alberto Ganesh Barbati <gan...@barbati.net> wrote:

> I totally agree with Howard. The difference between two dates should be typed and type "days" shouldn't be implicitly convertible to integers. Accordingly, you should also be disallowed to add integers to a date.

+1.  Durations may be integral, but they are certainly not scalars,
and the type system should reflect that.  Types are for more than just
enforcing invariants.

Heck, dates fundamentally are some number of integral days away from
some epoch, but we are arguing to make them a type instead of a just a
couple of conversion functions.
--
 Nevin ":-)" Liber  <mailto:ne...@eviloverlord.com>  (847) 691-1404

====================================
====================================



JOHN LAKOS, BLOOMBERG/ 731 LEXIN
====================================
   Autres options 5 sep, 20:17
JSL: Responding Ganesh Responding to Howard Responding to me -- My comments JSL: look like this...

- Masquer le texte des messages précédents -

----- Original Message -----
From: kona-date-lib@googlegroups.com
To: kona-date-lib@googlegroups.com

At:  9/05  3:41:13

Il giorno 05/set/2011, alle ore 02:33, Howard Hinnant ha scritto:

> On Sep 4, 2011, at 5:05 PM, JOHN LAKOS, BLOOMBERG/ 731 LEXIN wrote:

>> All, I have the following questions/observations regarding Howard's proposed baseline 'date' class:

>> 1. It is not clear to me why we need to build any sort of duration into
>>  the difference operator between two dates.  The difference between to
>>  date objects is integral: Unless we are using date objects in a different
>>  context -- e.g., one in which involves local time zones and DST (or leap
>>  seconds) -- for me, it's just the (signed) integer number of whole days
>>  between the two dates.  Bottom line: ++date is NOT necessarily 86,400
>>  seconds later, it IS one day later.

> I can respect that view.  However I wanted to add: if we were to choose duration<int_least32_t, ratio<86400>>, or class days{}, there is zero overhead.  I can supply assembly examples demonstrating that if that would help (in case it makes a difference to anyone).

Howard's argument sounds convincing to me. The link Howard provided clearly shows that at least one international standard defines day as 86400 seconds. The *only* reason I see to not adopt duration<int_least32_t, ratio<86400>> for days is if we wanted to support leap seconds at the basic level. However, I see some agreement that we should consider leap seconds at that level.

JSL: In this case, it is not an issue of overhead.  It is the semantics.
JSL: I agree with the difference between two date_time values being a
JSL: date_time_interval (of unspecified precision) because there is no one
JSL: base precision for time.  But there is for days.  So I don't see the
JSL: need to have anything to do with time in just the date type.  date_time
JSL: is different.  Separately, I do not think we should be dealing with
JSL: leap seconds in the basic time or date_time class (at the primitive level):
JSL: These are subtle issues that most people (including Bloomberg) don't care
JSL: about at all, and are handled differently by different people who do
JSL: care.  For example, some operating systems gradually adjust their clocks
JSL: over the entire year and side-step the issue entirely.

>> 2. I would not have bothered to use 'int_least32_t' as the result type for a
>>  primitive date-difference operation because nothing we write at Bloomberg
>>  would work if 'int' were 16 bits.  I suspect this is true for most people
>>  who write C++, but I could live with 'int_least32_t' for the C++ standard
>>  if that's what makes people feel confortable, but then I'd want to see
>>  where else we use 'int' in the standard and clean that up too (if necessary).

> I did a quick survey, and actually we've done fairly well over the years with respect to this issue in the standard.  There may be a couple of places where int isn't quite the right type.  But I believe them to be relatively rare.  I believe we can not assume at this point that int is greater than 16 bits (our standard says otherwise).

I have no problems with int_least32_t. It's probably going to be defined to be int on most platforms, anyway.

The only place in the library where int is used and really shouldn't is in the specification of gbump/pbump. I believe there is already a DR about it.

JSL: OK: As long as we're consistent about it in the standard.

>> 3. The difference between two 'date_time' types is a 'date_time_interval', but
>>  not of any particular precision.  Building the precision into the difference
>>  type would be brittle and (IMO) a mistake.  (Type-safe programming can
>>  ensure that dimensions are correct at compile time.  Dimensions are
>>  distance, time, velocity, acceleration, etc., but not specific units like
>>  meters, seconds, meters-per-second, etc.).

In my proposal, the date_time class is a templated wrapper over date and a duration. So you can have:

JSL: I will need more convincing that duration is the right answer for
JSL: date_time values.  duration may be what we use to implement them (which is,
JSL: in part, I voted for them) but they may not be the vocabulary type we need
JSL: for date, time, date_time, and date_time_interval (no compile-time units).
JSL: The goal is to be able to pass the value of the a date_time ubiquitously
JSL: without making the client a template; this property is critical for
JSL: Bloomberg (and IMO in general for large systems).

basic_date_time<date, milliseconds> d1; // time-of-day measured in milliseconds
basic_date_time<date, microseconds> d2; // time-of-day measured in microseconds
date_time d3; // an alias representing a reasonable default (seconds? milliseconds? we decide)

(the first argument of basic_date_date takes a date to accommodate for different calendars)

The time_duration arithmetic takes care of all the conversions as described by Howard.

>> 4. With a 'date_time', there is again no notion of local timezone or leap
>>  seconds; hence, these concepts should be addressed at a higher level.

> Agreed.  And I think this is consistent with std::chrono::system_clock::time_point.

Agreed.

JSL: Cool :-)

>> 6. The prefixe ++ and -- operators on date are *no*t to be named 'tomorrow' or
>>  'yesterday', as they modify the object!  Even calling them 'makeTomorrow'
>>  (and 'makeYesterday') would be wrong, as the name would suggest that the
>>  operation is independent of the current value.  The prefix operators are
>>  unambiguous and correct, especially given the contiguous integral nature of
>>  date values.

> Thank you!  I'm glad somebody was awake! :-)

I don't like ++ and -- very much. I'd prefer if we forced the user to a more explicit:

  d += days(1);

JSL: You can use += if you want, but let's not stop people from using terse, JSL: familiar, and intuitive notation that cannot reasonably be misunderstood.

> I envision "date day iteration" to be popular and coded similar to:

>   date start_date = ...
>   date end_date = ...
>   for(; start_date <= end_date; ++start_date)
>      // do stuff with start_date

> For C++ programmers this is a lot more readable than something like:

>   for(; start_date <= end_date; start_date.tomorrow())
>      // do stuff with start_date

I believe we should investigate the possibility of having syntaxes like:

  for (date d : date_range(start_date, end_date))
     // ...

or even

  for (date d : day_iteration(start_date, end_date))
     // ...

  for (date d : month_iteration(start_date, end_date))
     // ...

or something like that. We could create a whole sort of date range traversals algorithms without having to overload a single iterator class, while having them totally decoupled from the date class.  Such algorithms could also be used with regular algorithms, of course:

  week_iteration wi(start_date, end_date);
  for_each(wi.begin(), wi.end(), ...)

JSL: This is all more complicated than is needed.  I am not going to say
JSL: I am opposed, but pre and post fix operator ++ and -- belong here first.

>> 7. By the same token, date += 3 modifies this date to be 3 days after its
>>  original value (unambiguous).  int days = d2 - d1; assert (d2 == d1 + days);

> I agree in spirit, especially with the algebraic consistency.  I do worry about:

>    int get_time_since();
>    ...
>    date += get_time_since();

> One has to read the docs to find out what units get_time_since() is returning.  The compiler won't catch the error if the units aren't days.

JSL: We need to make the code easy and safe to write, but reading the docs
JSL: is not something we can eliminate (nor IMO should we try).  Notice
JSL: the function has "time" in it.  If it said get_whole_days_since ..., it
JSL: would satisfy my safety threshold -- that is, unless it returned whole
JSL: multiples of 86,400 as an int ;-)

I totally agree with Howard. The difference between two dates should be typed and type "days" shouldn't be implicitly convertible to integers. Accordingly, you should also be disallowed to add integers to a date.

JSL: I think we have *true* *disagreement* here:
JSL: IMO d1 - d2 is integral --> 'int' (or some kind of signed integer type)
JSL: We agree that assert(d2 == d1 + (d2 - d1)).
JSL: IMO int n = d2 - d1; should work fine.
JSL: as should date d2 = d1 + 2;
JSL: and then assert(2 == d2 - d1);
JSL: I don't necessarily mind if people don't want to use this, but
JSL: making people who fully qualify all types (i.e., don't use using) to type
JSL: d2 = d1 + std::chrono::days(2);
JSL: instead
JSL: d2 = d1 + 2;
JSL: will revolt.
JSL:
JSL: Again, dimensions are one thing, but integers are integers and this kind
JSL: excessive over typing gets in the way of interoperability.  You are, of
JSL: course, not going to stop people from getting the number of days out of a
JSL: std::chrono::days, which means that you constantly  make people who want
JSL: the 'int' to  say something like 'n.asInteger()' instead of just 'n'!
JSL: You may like this, but people who are used to writing terse code may well
JSL: think this is nuts, and refuse to use it.  Again, dates and date_times
JSL: are different, used differently, and have different properties.  I would
JSL: never suggest that the difference between two datetime values is integeral.
JSL: it is a date_time_interval (with unspecified precision) and you ask it
JSL: for the units you want, which is totally correct and fine by me.  But
JSL: dates are integral in nature, and ++ += + - etc. are all intuitive and
JSL: unambiguous (at least to the 1000s of programmers that have used our
JSL:

...

plus de détails »

====================================
====================================



Sujet remplacé par "Difference between two dates" par Pablo Halpern



Pablo Halpern
====================================
   Autres options 7 sep, 01:16

On 09/05/2011 02:17 PM, JOHN LAKOS, BLOOMBERG/ 731 LEXIN wrote:

- Afficher le texte des messages précédents -

I agree and would add an even more fundamental problem than precision.
The notion of a "date" is fundamentally different than the notion of a
timepoint.  If that were not true, then there would be no need to have
two separate types.  The meaning of a date is context-dependent and is
not necessarily 86400 seconds.  For example, a work day might be 8
hours.  A business day might be something else.  A birthday is the whole
day, not a specific time (midnight or noon).  If we impose the notion
that the difference between two dates is convertible implicitly to a
time duration, then we are inviting the programmer to make some very
common errors while giving them a false sense that the the compiler will
prevent these errors.

For example, a ski area may have lifts that open at 9 and close at 4.
If the user buys multi-day ski passes online and puts in firstday and
lastday, how many hours of skiing did the user buy?  Wrong answer:
(lastday - firstday + 1) * 24 hours.  If I have heated ski boots that
last 12-hours on a charge, how many days can I ski without recharging
the batteries?  Wrong answer: less than 1 day.  Here is a link to a joke
that hinges on exactly these kinds of errors:
http://www.funnyandjokes.com/so-you-want-a-day-off.html.
<http://www.funnyandjokes.com/so-you-want-a-day-off.html>

So, whatever gets returned from date subtraction, it should not be
something that is convertible to seconds.  So, of Howard's three
proposed return values, I'm against #2: duration<int_least32_t,
ratio<86400> >.
> Ganesh Wrote:
> I totally agree with Howard. The difference between two dates should be typed and type "days" shouldn't be implicitly convertible to integers. Accordingly, you should also be disallowed to add integers to a date.

> JSL: I think we have *true* *disagreement* here:
> JSL: IMO d1 - d2 is integral -->  'int' (or some kind of signed integer type)
> JSL: We agree that assert(d2 == d1 + (d2 - d1)).
> JSL: IMO int n = d2 - d1; should work fine.
> JSL: as should date d2 = d1 + 2;
> JSL: and then assert(2 == d2 - d1);
> JSL: I don't necessarily mind if people don't want to use this, but
> JSL: making people who fully qualify all types (i.e., don't use using) to type
> JSL: d2 = d1 + std::chrono::days(2);
> JSL: instead
> JSL: d2 = d1 + 2;
> JSL: will revolt.

I have mixed feelings about this issue, i.e., whether the difference
between dates should be a simple integer or a special type that is not a
duration.  I agree with John that most uses of integers with dates are
safe and intuitive and I appreciate the terseness.  However, I don't
have much experience programming with dimensional types so I don't have
a strong sense of the advantages. Dimensional types can have a nice
benefit for I/O, as Howard showed in his time I/O proposal.  I think it
would be cool to be able to say:

     std::cout << (a - b);

and if a and b are dates, then the result has the word "days" after it.
Would it be heresy to suggest a dimensional type like "days" that is
implicitly convertible to and from integers.  (Actually, calling
x.count() is not too onerous, but std::chrono::days(y) is icky, IMO.)

-Pablo

====================================
====================================



Sujet remplacé par "Increment and decrement operators" par Pablo Halpern



Pablo Halpern
====================================
   Autres options 7 sep, 01:20
On 09/05/2011 02:17 PM, JOHN LAKOS, BLOOMBERG/ 731 LEXIN wrote:
> JSL: Responding Ganesh Responding to Howard Responding to me -- My comments JSL: look like this...

>>> 6. The prefixe ++ and -- operators on date are *no*t to be named 'tomorrow' or
>>>   'yesterday', as they modify the object!  Even calling them 'makeTomorrow'
>>>   (and 'makeYesterday') would be wrong, as the name would suggest that the
>>>   operation is independent of the current value.  The prefix operators are
>>>   unambiguous and correct, especially given the contiguous integral nature of
>>>   date values.
>> Thank you!  I'm glad somebody was awake! :-)
> I don't like ++ and -- very much. I'd prefer if we forced the user to a more explicit:

>    d += days(1);

Ick!  Come on.  What possible meaning could ++d have than "increment d
to the next day!"  Especially if we decide that adding days to a date
would require constructing a days object (which I'm not completely
convinced of), then we need the terse ++ and -- operators for iterating
through days.
> JSL: You can use += if you want, but let's not stop people from using terse,
> JSL: familiar, and intuitive notation that cannot reasonably be misunderstood.

Agreed.

-Pablo
#endif
