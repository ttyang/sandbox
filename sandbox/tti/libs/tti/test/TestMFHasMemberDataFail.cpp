#include "TestMFHasMemberData.hpp"
#include <boost/mpl/assert.hpp>
#include <boost/mpl/identity.hpp>

int main()
  {
  
  // someDataMember does not exist at all
  
  BOOST_MPL_ASSERT((tti::mf_has_member_data
                      <
                      tti::has_member_someDataMember,
                      boost::mpl::identity<AnotherType>,
                      boost::mpl::identity<short> 
                      >
                  ));
  
  return 0;

  }
