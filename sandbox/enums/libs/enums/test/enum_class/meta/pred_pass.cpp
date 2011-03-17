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

#include "./EnumClass.hpp"
#include <boost/static_assert.hpp>
#include <boost/enums/ordinal/pred.hpp>
#include <boost/enums/mpl/enum_c.hpp>
#include <boost/enums/mpl/equal_to.hpp>

void pass() {
  using namespace boost;
  using namespace boost::enums;

  {
    BOOST_STATIC_ASSERT((mpl::equal_to<
      mpl::enum_c<EnumClass, meta::pred<EnumClass,EnumClass::Enum1>::value>,
      mpl::enum_c<EnumClass, EnumClass::Default>
    >::value));

    BOOST_STATIC_ASSERT((mpl::equal_to<
      mpl::enum_c<EnumClass, meta::pred<EnumClass,EnumClass::Enum2>::value>,
      mpl::enum_c<EnumClass, EnumClass::Enum1>
    >::value));
  }

}
