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
 Include this file when using conversions between @c std::pair<> of convertible types.
 */


//[PAIR_HPP
#ifndef BOOST_CONVERSION_STD_PAIR_HPP
#define BOOST_CONVERSION_STD_PAIR_HPP

#include <utility>
//#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>

namespace boost {
  namespace conversion {

    // std namespace can not be overloaded
    template < class T1, class T2, class S1, class S2>
    struct converter_cp< std::pair<T1,T2>, std::pair<S1,S2>
      BOOST_CONVERSION_REQUIRES((
          is_extrinsic_convertible<S1,T1>::value
       && is_extrinsic_convertible<S2,T2>::value
      ))
    > : true_type
    {
        std::pair<T1,T2> operator()(std::pair<S1,S2> const & from)
        {
            return std::pair<T1,T2>(boost::conversion::implicit_convert_to<T1>(from.first), boost::conversion::implicit_convert_to<T2>(from.second));
        }
    };
    template < class T1, class T2, class S1, class S2>
    struct assigner_cp< std::pair<T1,T2>, std::pair<S1,S2>
      BOOST_CONVERSION_REQUIRES((
           is_extrinsic_convertible<S1,T1>::value
        && is_extrinsic_convertible<S2,T2>::value
      ))
    > : true_type
    {
        std::pair<T1,T2>& operator()(std::pair<T1,T2>& to, const std::pair<S1,S2>& from)
        {
            to.first = boost::conversion::implicit_convert_to<T1>(from.first);
            to.second = boost::conversion::implicit_convert_to<T2>(from.second);
            return to;
        }
    };
  }
}

#endif

//]
