//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

/*!
 @file
 @brief
 Include this file when using conversions between @c boost::fusion::tuple<> of convertible types.
 */
#ifndef BOOST_CONVERSION_TUPLE_HPP
#define BOOST_CONVERSION_TUPLE_HPP

#include <boost/fusion/tuple.hpp>
#include <boost/conversion/explicit_convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/config.hpp>


namespace boost {
  namespace conversion {
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED2)
    /** @brief Added here only to favor generation of specializations with doxygen */
    template < class Target, class Source, class Enable=void>
    struct explicit_converter_cp{};
#endif

    template < class T1, class T2, class S1, class S2>
    struct explicit_converter_cp< fusion::tuple<T1,T2>, fusion::tuple<S1,S2>
      BOOST_CONVERSION_REQUIRES((
           is_extrinsic_convertible<S1,T1>::value
        && is_extrinsic_convertible<S2,T2>::value
      ))
    > : true_type
    {
      fusion::tuple<T1,T2> operator()(fusion::tuple<S1,S2> const & from)
      {
        return fusion::tuple<T1,T2>(
            boost::conversion::implicit_convert_to<T1>(fusion::get<0>(from))
            , boost::conversion::implicit_convert_to<T2>(fusion::get<1>(from))
        );
      }
    };
    template < class T1, class T2, class T3, class S1, class S2, class S3>
    struct explicit_converter_cp< fusion::tuple<T1,T2,T3>, fusion::tuple<S1,S2,S3>
    BOOST_CONVERSION_REQUIRES((
        is_extrinsic_convertible<S1,T1>::value
        && is_extrinsic_convertible<S2,T2>::value
        && is_extrinsic_convertible<S3,T3>::value
    ))
    > : true_type
    {
      fusion::tuple<T1,T2,T3> operator()(fusion::tuple<S1,S2,S3> const & from)
      {
        return fusion::tuple<T1,T2, T3>(
              boost::conversion::convert_to<T1>(fusion::get<0>(from))
            , boost::conversion::convert_to<T2>(fusion::get<1>(from))
            , boost::conversion::convert_to<T3>(fusion::get<2>(from))
        );
      }
    };

  }

#if defined(BOOST_CONVERSION_DOUBLE_CP)
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
  namespace fusion {
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    template < class... Target, class... Source>
    inline tuple<Target...>& assign_to(tuple<Target...>& to, tuple<Source...> const & from
    );
#else

    template < class T1, class T2, class S1, class S2>
    inline tuple<T1,T2>& assign_to(tuple<T1,T2>& to, tuple<S1,S2> const & from)
    {
      to = boost::conversion::convert_to<boost::fusion::tuple<T1,T2> >(from);
      return to;
    }

    template < class T1, class T2, class T3, class S1, class S2, class S3>
    inline tuple<T1,T2,T3> assign_to(tuple<T1,T2,T3>& to, boost::fusion::tuple<S1,S2,S3> const & from)
    {
      to = boost::conversion::convert_to<boost::fusion::tuple<T1,T2> >(from);
      return to;
    }
  }
#endif
#endif
#endif
}

#endif

