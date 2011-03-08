#if !defined(TEST_HAS_STATIC_MEM_FUN_TEMPLATE_HPP)
#define TEST_HAS_STATIC_MEM_FUN_TEMPLATE_HPP

#include "test_structs.hpp"
#include <boost/tti/static_mem_fun_template.hpp>
#include <boost/tti/static_mem_fun_template_params.hpp>
#include <boost/tti/mem_type.hpp>

BOOST_TTI_HAS_STATIC_MEMBER_FUNCTION_TEMPLATE_PARAMS(StatFuncTemplate,(short)(long)(7854))
BOOST_TTI_TRAIT_HAS_STATIC_MEMBER_FUNCTION_TEMPLATE_PARAMS(TAnother,AnotherFuncTemplate,(int)(long)(long))
BOOST_TTI_HAS_STATIC_MEMBER_FUNCTION_TEMPLATE_PARAMS(YetAnotherFuncTemplate,(double)(float))

BOOST_TTI_TRAIT_HAS_STATIC_MEMBER_FUNCTION_TEMPLATE(AStatFT,StatFuncTemplate)
BOOST_TTI_HAS_STATIC_MEMBER_FUNCTION_TEMPLATE(AnotherFuncTemplate)
BOOST_TTI_TRAIT_HAS_STATIC_MEMBER_FUNCTION_TEMPLATE(YAFuncTemp,YetAnotherFuncTemplate)

BOOST_TTI_MEMBER_TYPE(AStructType)

#endif // TEST_HAS_STATIC_MEM_FUN_TEMPLATE_HPP
