#include "TestHasMemberData.hpp"
#include <boost/mpl/assert.hpp>

int main()
  {
  
  // You can always instantiate without compiler errors
  
  tti::has_member_data_aMember<AType,long> aVar;
  tti::has_member_data_someDataMember<AnotherType,double> aVar2;
  
  // Compile time asserts
  
  BOOST_MPL_ASSERT((tti::has_member_data_AnInt<AType,int>));
  BOOST_MPL_ASSERT((tti::has_member_data_AnInt<AnotherType,long>));
  BOOST_MPL_ASSERT((tti::has_member_data_aMember<AnotherType,bool>));
  BOOST_MPL_ASSERT((tti::CMember<AnotherType,bool>));
  BOOST_MPL_ASSERT((tti::has_member_data_IntBT<AType,AType::BType>));
  BOOST_MPL_ASSERT((tti::NestedData<AType,AType::BType::CType>));
  BOOST_MPL_ASSERT((tti::AOther<AnotherType,AType>));
  BOOST_MPL_ASSERT((tti::has_member_data_ONestStr<AnotherType,AType::AStructType>));
  
  return 0;

  }
