#include "test_has_template_check_params.hpp"
#include <boost/mpl/assert.hpp>

int main()
  {
  
  // Wrong template parameters
  
  BOOST_MPL_ASSERT((boost::tti::WrongParameters2ForMP<AnotherType>));
  
  return 0;

  }