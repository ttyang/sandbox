#include "test_has_type_check_typedef.hpp"
#include <boost/mpl/assert.hpp>

int main()
  {
  
  // NoOtherType does not exist at all
  
  BOOST_MPL_ASSERT((boost::tti::has_type_NoOtherType<AType,int>));
  
  return 0;

  }