#include "TestMFHasTypeCheckTypedef.hpp"
#include <boost/mpl/assert.hpp>

int main()
  {
  
  // NoOtherType does not exist at all
  
  BOOST_MPL_ASSERT((tti::mf_has_type_check_typedef
                      <
                      tti::has_type_check_typedef_NoOtherType,
                      boost::mpl::identity<AnotherType>,
                      boost::mpl::identity<float>
                      >
                  ));
  
  return 0;

  }
