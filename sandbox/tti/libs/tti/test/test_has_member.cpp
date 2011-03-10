#include "test_has_member.hpp"
#include <boost/detail/lightweight_test.hpp>

int main()
  {
  
  BOOST_TEST(BOOST_TTI_HAS_COMP_MEMBER_FUNCTION_GEN(VoidFunction)<void (AType::*)()>::value);
  BOOST_TEST(BOOST_TTI_TRAIT_GEN(FunctionReturningInt)<int (AType::*)()>::value);
  BOOST_TEST(BOOST_TTI_TRAIT_GEN(FunctionReturningInt)<double (AnotherType::*)(int)>::value);
  BOOST_TEST(BOOST_TTI_HAS_COMP_MEMBER_FUNCTION_GEN(aFunction)<AType (AnotherType::*)(int)>::value);
  BOOST_TEST(BOOST_TTI_TRAIT_GEN(AnotherIntFunction)<int (AnotherType::*)(AType)>::value);
  BOOST_TEST(BOOST_TTI_HAS_COMP_MEMBER_FUNCTION_GEN(sFunction)<AType::AnIntType (AnotherType::*)(int,long,double)>::value);
  BOOST_TEST(!BOOST_TTI_HAS_COMP_MEMBER_FUNCTION_GEN(someFunctionMember)<AType (AnotherType::*)(long,int)>::value);
  
  return boost::report_errors();

  }
