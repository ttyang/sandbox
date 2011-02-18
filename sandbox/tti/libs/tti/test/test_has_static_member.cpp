#include "test_has_static_member.hpp"
#include <boost/detail/lightweight_test.hpp>

int main()
  {
  
  BOOST_TEST((boost::tti::has_static_member_DSMember<AType,short>::value));
  BOOST_TEST((boost::tti::HaveTheSIntFunction<AType,int (long,double)>::value));
  BOOST_TEST((!boost::tti::TheTIntFunction<AType,AType (long,double)>::value));
  BOOST_TEST((boost::tti::TheTIntFunction<AnotherType,AType (long,double)>::value));
  BOOST_TEST((boost::tti::has_static_member_TSFunction<AnotherType,AType::AStructType (AType::AnIntType,double)>::value));
  BOOST_TEST((!boost::tti::has_static_member_SomeStaticData<AnotherType,float>::value));
  BOOST_TEST((!boost::tti::Pickedname<AnotherType,void ()>::value));
  
  return boost::report_errors();

  }