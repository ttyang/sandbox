#include "TestHasMember.hpp"
#include <boost/mpl/assert.hpp>

int main()
  {
  
  // someDataMember does not exist at all
  
  BOOST_MPL_ASSERT(( tti::has_member_someDataMember<short AType::*> ));
  
  return 0;

  }