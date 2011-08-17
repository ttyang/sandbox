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
 @brief Defines the free function @c lvalue.
 */
#ifndef BOOST_CONVERSION_LVALUE_HPP
#define BOOST_CONVERSION_LVALUE_HPP

#include <boost/conversion/assignable_to.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/conversion/is_extrinsically_convertible.hpp>
#include <boost/conversion/is_extrinsically_assignable.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
  namespace conversion {


    //! makes an assignable to @c Target which accepts assignment from any type that is extrinsic assignable to @c Target.

    //! The result is able to transform assignments by assign_to calls.
    //! @NoThrow.
    template <typename Target>
    assignable_to<Target> lvalue(Target& r)
    {
      return assignable_to<Target>(r);
    }
  }
}

#endif

