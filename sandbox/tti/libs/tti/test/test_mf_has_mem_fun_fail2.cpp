#include "test_mf_has_mem_fun.hpp"
#include <boost/mpl/assert.hpp>

int main()
  {
  
  using namespace boost::mpl::placeholders;
  
  // Wrong function signature
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      BOOST_TTI_TRAIT_GEN(FunctionReturningInt)<_,_>,
                      boost::mpl::identity<AnotherType>,
                      boost::mpl::identity<short>
                      >
                  ));
  
  return 0;

  }