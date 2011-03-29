#include "test_has_template_cp.hpp"
#include <boost/detail/lightweight_test.hpp>

int main()
  {
  
  BOOST_TEST(BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS_GEN(ATPMemberTemplate)<AType>::value);
  BOOST_TEST(BOOST_TTI_TRAIT_GEN(HaveCL)<AType>::value);
  BOOST_TEST(BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS_GEN(AMemberTemplate)<AType>::value);
  BOOST_TEST(BOOST_TTI_TRAIT_GEN(HaveAnotherMT)<AType>::value);
  BOOST_TEST(BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS_GEN(SomeMemberTemplate)<AnotherType>::value);
  BOOST_TEST(BOOST_TTI_TRAIT_GEN(ATemplateWithParms)<AnotherType>::value);
  BOOST_TEST(BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS_GEN(SimpleTMP)<AnotherType>::value);
  BOOST_TEST(!BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS_GEN(TemplateNotExist)<AnotherType>::value);

  return boost::report_errors();

  }