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
 Include this file when using conversions from/to @c std::string.
 */

#ifndef BOOST_CONVERSION_STD_STRING_HPP
#define BOOST_CONVERSION_STD_STRING_HPP

#include <string>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#if !defined(BOOST_CONVERSION_USE_CONVERT)
#include <boost/lexical_cast.hpp>
#else
#include <boost/convert/convert.hpp>
#endif
namespace boost {
  namespace conversion {

    // std namespace can not be overloaded
      
      template<typename T, typename CharT, typename Traits, typename Alloc>
      struct converter< std::basic_string<CharT,Traits,Alloc>, T > {
        std::basic_string<CharT,Traits,Alloc> operator()(T const & from)
        {
#if !defined(BOOST_CONVERSION_USE_CONVERT)
          return lexical_cast<std::basic_string<CharT,Traits,Alloc> >(from);
#else
          return convert<std::basic_string<CharT,Traits,Alloc> >::from(from);
#endif
        }
      };
      template<typename T, typename CharT, typename Traits, typename Alloc>
      struct converter< T, std::basic_string<CharT,Traits,Alloc> > {
        T operator()(std::basic_string<CharT,Traits,Alloc> const & from)
        {
#if !defined(BOOST_CONVERSION_USE_CONVERT)
          return lexical_cast<T>(from);
#else
          return convert<T>::from(from);
#endif
        }
      };

      template<typename T, typename CharT, typename Traits, typename Alloc>
      struct assigner< std::basic_string<CharT,Traits,Alloc>, T > {
        std::basic_string<CharT,Traits,Alloc>&
        operator()(std::basic_string<CharT,Traits,Alloc>& to, const T& from)
        {
          to = boost::conversion::convert_to<std::basic_string<CharT,Traits,Alloc> >(from);
          return to;
        }
      };
      template<typename T, typename CharT, typename Traits, typename Alloc>
      struct assigner< T, std::basic_string<CharT,Traits,Alloc> > {
        T& operator()(T& to, const std::basic_string<CharT,Traits,Alloc>& from)
        {
          to = boost::conversion::convert_to<T>(from);
          return to;
        }
      };

      
  }
}

#endif

