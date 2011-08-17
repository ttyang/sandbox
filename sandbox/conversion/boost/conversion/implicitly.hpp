//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////


/*!
 @file
 @brief
 Defines the free function @c implicitly.
 */
#ifndef BOOST_CONVERSION_IMPLICITLY_HPP
#define BOOST_CONVERSION_IMPLICITLY_HPP

#include <boost/conversion/config.hpp>
#if defined(BOOST_CONVERSION_IMPLICITLY_ENABLED) || defined(BOOST_CONVERSION_DOXYGEN_INVOKED)

#include <boost/conversion/convertible_from.hpp>
#include <boost/conversion/implicit_convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/conversion/is_extrinsically_convertible.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/conversion/type_traits/is_copy_constructible.hpp>

namespace boost {
  namespace conversion {

    //! @brief makes a wrapper implicitly convertible to types extrinsicly implicit convertibles from @c Source.
    //!
    //! The result provides implicitly conversion to any type which is extrinsically implicit convertible from @c Source.
    //! @Returns convertible_from<Source>(s).
    //! @NoThrow.
    //! @Example
    //! @code
    //! template <typename T>
    //! struct test {
    //!   static void fct()
    //!   {
    //!     T v;
    //!     std::cout << f(implicitly(v)) << " called" << std::endl;
    //!   }
    //! };
    //! @endcode

    template <typename Source>
    typename enable_if_c<
      is_copy_constructible<Source>::value
    , convertible_from<Source>
    >::type
    implicitly(Source s)
    {
      return convertible_from<Source>(s);
    }
  }
}
#endif

#endif

