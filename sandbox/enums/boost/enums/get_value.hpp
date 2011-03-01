//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2011.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/enums for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_ENUMS_GET_VALUE_HPP
#define BOOST_ENUMS_GET_VALUE_HPP

#include <boost/config.hpp>
#include <boost/enums/enum_type.hpp>
#include <iostream>
namespace boost {
  namespace enums {

    template <typename EC>
    inline
    typename enum_type<EC>::type
    get_value(EC e)
    {
#ifdef BOOST_NO_SCOPED_ENUMS
          std::cout << __LINE__ << std::endl;
                return e.get();
#else
          std::cout << __LINE__ << std::endl;      return e;
#endif
    }
  }
}

#endif
