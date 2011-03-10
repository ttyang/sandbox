#include "test_has_type_ct.hpp"
#include <boost/detail/lightweight_test.hpp>

int main()
  {
  
  BOOST_TEST((BOOST_TTI_HAS_TYPE_GEN(AnIntType)<AType,int>::value));
  BOOST_TEST((BOOST_TTI_TRAIT_GEN(NameStruct)<AType,AType::AStructType>::value));
  BOOST_TEST((BOOST_TTI_HAS_TYPE_GEN(AnIntTypeReference)<AType,int &>::value));
  BOOST_TEST((BOOST_TTI_HAS_TYPE_GEN(BType)<AType,AType::BType>::value));
  BOOST_TEST((BOOST_TTI_TRAIT_GEN(TheInteger)<AType::BType,int>::value));
  BOOST_TEST((BOOST_TTI_HAS_TYPE_GEN(CType)<AType::BType,AType::BType::CType>::value));
  BOOST_TEST((BOOST_TTI_HAS_TYPE_GEN(AnotherIntegerType)<AType::BType::CType,int>::value));
  BOOST_TEST((BOOST_TTI_TRAIT_GEN(SomethingElse)<AnotherType,AType::AnIntType>::value));
  BOOST_TEST((!BOOST_TTI_HAS_TYPE_GEN(NoOtherType)<AnotherType,double>::value));
  
  return boost::report_errors();

  }
