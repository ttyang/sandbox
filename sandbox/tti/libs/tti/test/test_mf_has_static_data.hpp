#if !defined(TEST_MF_HAS_STATIC_DATA_HPP)
#define TEST_MF_HAS_STATIC_DATA_HPP

#include "test_structs.hpp"
#include <boost/tti/static_member.hpp>

BOOST_TTI_HAS_STATIC_MEMBER(DSMember)
BOOST_TTI_HAS_STATIC_MEMBER(SomeStaticData)

BOOST_TTI_MTFC_HAS_STATIC_MEMBER(DSMember)
BOOST_TTI_MTFC_HAS_STATIC_MEMBER(SomeStaticData)

#endif // TEST_MF_HAS_STATIC_DATA_HPP
