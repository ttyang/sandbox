#if !defined(TEST_HAS_TEMPLATE_CHECK_PARAMS_HPP)
#define TEST_HAS_TEMPLATE_CHECK_PARAMS_HPP

#include "test_structs.hpp"
#include <boost/tti/tti.hpp>

BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS(ATPMemberTemplate,(class))
BOOST_TTI_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(HaveCL,CLMemberTemplate,(class)(class))
BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS(AMemberTemplate,(int))
BOOST_TTI_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(HaveAnotherMT,AnotherMemberTemplate,(int)(int))
BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS(SomeMemberTemplate,(class)(class)(class)(class)(class)(class))
BOOST_TTI_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(ATemplateWithParms,ManyParameters,(class)(class)(int)(class)(template <class> class InnerTemplate)(class)(long))
BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS(SimpleTMP,(class)(class)(class)(class))
BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS(TemplateNotExist,(int)(class)(template <class> class ATemplate))
BOOST_TTI_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(WrongParametersForMP,ManyParameters,(class)(class)(int)(class)(template <class)(class> class InnerTemplate)(class)(long))
BOOST_TTI_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(WrongParameters2ForMP,ManyParameters,(class)(long)(int)(class)(template <class> class InnerTemplate)(class)(long))

#endif // TEST_HAS_TEMPLATE_CHECK_PARAMS_HPP
