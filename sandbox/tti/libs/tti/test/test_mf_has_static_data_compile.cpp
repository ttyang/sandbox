#include "test_mf_has_static_data.hpp"
#include <boost/mpl/assert.hpp>

int main()
  {
  
  using namespace boost::mpl::placeholders;
  
  // You can always instantiate without compiler errors
  
  boost::tti::mf_has_static_member_data
    <
    BOOST_TTI_HAS_STATIC_MEMBER_DATA_GEN(SomeStaticData)<_,_>,
    boost::mpl::identity<AnotherType>,
    boost::mpl::identity<double>
    > aVar;
  
  // Compile time asserts
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_static_member_data
                      <
                      BOOST_TTI_HAS_STATIC_MEMBER_DATA_GEN(DSMember)<_,_>,
                      boost::mpl::identity<AType>,
                      boost::mpl::identity<short>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_static_member_data
                      <
                      BOOST_TTI_MTFC_HAS_STATIC_MEMBER_DATA_GEN(DSMember),
                      boost::mpl::identity<AType>,
                      boost::mpl::identity<short>
                      >
                  ));
  
  return 0;

  }
