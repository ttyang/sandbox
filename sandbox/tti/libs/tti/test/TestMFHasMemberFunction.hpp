#if !defined(TEST_MF_HAS_MEMBER_FUNCTION_HPP)
#define TEST_MF_HAS_MEMBER_FUNCTION_HPP

#include "TestStructs.hpp"
#include <boost/tti/TTIntrospection.hpp>

TTI_HAS_MEMBER_FUNCTION(VoidFunction)
TTI_TRAIT_HAS_MEMBER_FUNCTION(FunctionReturningInt,IntFunction)
TTI_HAS_MEMBER_FUNCTION(aFunction)
TTI_TRAIT_HAS_MEMBER_FUNCTION(AnotherIntFunction,anotherFunction)
TTI_HAS_MEMBER_FUNCTION(sFunction)
TTI_HAS_MEMBER_FUNCTION(someFunctionMember)

TTI_MEMBER_TYPE(AnIntType)

#endif // TEST_MF_HAS_MEMBER_FUNCTION_HPP
