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

#include <cstring>
#include <string>
#include <iostream>

#include "./EnumClass.hpp"
#include "./f.hpp"
#include <boost/detail/lightweight_test.hpp>
#include <boost/enums/enum_subrange_traiter.hpp>
#ifndef BOOST_ENUMS_NOT_DEPENDS_ON_CONVERSION
#include <boost/conversion/is_extrinsically_explicitly_convertible.hpp>
#endif
#include <boost/static_assert.hpp>

#define RUN_TIME
#define COMPILE_TIME

int main() {

  using namespace boost;
  using namespace boost::conversion;
  using namespace boost::enums;

  std::cout << __LINE__ << std::endl;
#ifndef BOOST_ENUMS_NOT_DEPENDS_ON_CONVERSION
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicitly_convertible< const char*, EnumClass >::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicitly_convertible< std::string, EnumClass >::value));
  { // The wrapper can be constructed from a valid const char* representation
    std::string str="Enum2";
    EnumClass e = boost::conversion::explicit_convert_to<EnumClass>(str);
    BOOST_TEST(e==EnumClass::Enum2);
    EnumClass e2 = boost::conversion::explicit_convert_to<EnumClass>("Enum2");
    BOOST_TEST(e2==EnumClass::Enum2);
  }
#endif
#ifdef COMPILE_TIME2
  { // Construction of the wrapper from const char * compile fails
    const char* ptr = 0;
    EnumClass e0=ptr;
  }
#endif
#ifdef RUN_TIME2
  { // The wrapper can not be constructed from an invalid const char* representation
    EnumClass e = explicit_convert_to<EnumClass>("CHASSE");
    // ... fail
  }
#endif
#ifndef BOOST_ENUMS_NOT_DEPENDS_ON_CONVERSION
  { // The wrapper can be constructed from a valid std::string representation
    std::string str = "Enum2";
    EnumClass e = explicit_convert_to<EnumClass>(str);
    BOOST_TEST(e==EnumClass::Enum2);
    BOOST_TEST(strcmp(c_str(e),"Enum2")==0);
  }
#endif
  std::cout << __LINE__ << std::endl;
#ifdef COMPILE_TIME2
  { // Construction of the wrapper from const char * compile fails
    std::string str;
    EnumClass e0 = str;
  }
#endif
#ifdef RUN_TIME2
  { // The wrapper can not be constructed from an invalid std::string representation
    std::string str = "CHASSE";
    EnumClass e = explicit_convert_to<EnumClass>(str);
    // ... fail
    BOOST_TEST(e==EnumClass::Enum2);
    BOOST_TEST(strcmp(c_str(e), "CHASSE")==0);
  }
#endif
  { // Construction of the wrapper with an invalid ints results in run-time error (undefined behavior)
//    EnumClass e(explicit_convert_to<EnumClass>((unsigned char)(6)));
    BOOST_TEST((unsigned char)(enums::native_type<EnumClass>::type(6))==(unsigned char)(6));
//    BOOST_TEST(native_value(e)==(unsigned char)(6));
  }
    { // The wrapper can be used in switch through the function get only :(
    EnumClass e = EnumClass::Default;
    enums::native_type<EnumClass>::type c=native_value(e);
          std::cout << int(c) << std::endl;
    switch (native_value(e)) { // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      case EnumClass::Enum1:
      case EnumClass::Enum2:
      case EnumClass::Default:
          std::cout << e << std::endl;
        break;
      default:
        //std::cout << e << ":"<< native_value(e) << std::endl;
        ;
    }
  }
  return boost::report_errors();
}
