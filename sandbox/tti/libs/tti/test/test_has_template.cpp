#include "test_has_template.hpp"
#include <boost/detail/lightweight_test.hpp>

int main()
  {
  
  BOOST_TEST(boost::tti::has_template_ATPMemberTemplate<AType>::value);
  BOOST_TEST(boost::tti::HaveCL<AType>::value);
  BOOST_TEST(!boost::tti::has_template_AMemberTemplate<AType>::value);
  BOOST_TEST(!boost::tti::HaveAnotherMT<AType>::value);
  BOOST_TEST(!boost::tti::has_template_SomeMemberTemplate<AnotherType>::value);
  BOOST_TEST(!boost::tti::ATemplateWithParms<AnotherType>::value);
  BOOST_TEST(boost::tti::has_template_SimpleTMP<AnotherType>::value);

  return boost::report_errors();
  
  }
