#include "test_has_template_cp.hpp"
#include <boost/mpl/assert.hpp>

int main()
  {
  
  // Wrong template parameters
  
  BOOST_MPL_ASSERT((boost::tti::WrongParametersForMP<AnotherType>));
  
  return 0;

  }