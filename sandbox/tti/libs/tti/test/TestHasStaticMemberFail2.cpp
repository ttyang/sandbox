#include "TestHasStaticMember.hpp"
#include <boost/mpl/assert.hpp>

int main()
  {
  
  // Wrong enclosing type for DSMember
  
  BOOST_MPL_ASSERT((tti::has_static_member_DSMember<AnotherType,short>));
  
  return 0;

  }
