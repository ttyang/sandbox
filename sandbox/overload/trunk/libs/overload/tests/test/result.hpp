
#ifndef _TEST_RESULT_HPP_
#define _TEST_RESULT_HPP_


#include <boost/utility/result_of.hpp>
#include "detail/change_result_type.hpp"

namespace result_test_ns {

typedef boost::overload<sig0_t, sig1_t, sig2_t, sig3_t, sig4_t, sig5_t>
        overload_type;

//////////////////////////////////////////////////////////////////////////////
// test change_result_type

BOOST_STATIC_ASSERT(( is_same<
        overload_type (std::string , std::string , std::string ),
        ovdtl::change_result_type<overload_type, sig0_t>::type
        >::value ));

BOOST_STATIC_ASSERT(( is_same<
        overload_type (bar1*, char ),
        ovdtl::change_result_type<overload_type, sig1_t>::type
        >::value ));

BOOST_STATIC_ASSERT(( is_same<
        overload_type (const bar2*, int, char ),
        ovdtl::change_result_type<overload_type, sig2_t>::type
        >::value ));

//////////////////////////////////////////////////////////////////////////////
// test result

BOOST_STATIC_ASSERT(( is_same<
        ovdtl::result< ovdtl::change_result_type<overload_type, sig0_t>::type >::type,
        int
        >::value ));

BOOST_STATIC_ASSERT(( is_same<
        ovdtl::result< ovdtl::change_result_type<overload_type, sig1_t>::type >::type,
        int
        >::value ));

BOOST_STATIC_ASSERT(( is_same<
        ovdtl::result< ovdtl::change_result_type<overload_type, sig2_t>::type >::type,
        double
        >::value ));

BOOST_STATIC_ASSERT(( is_same<
        ovdtl::result< ovdtl::change_result_type<overload_type, sig3_t>::type >::type,
        char
        >::value ));

BOOST_STATIC_ASSERT(( is_same<
        ovdtl::result< ovdtl::change_result_type<overload_type, sig4_t>::type >::type,
        int
        >::value ));

BOOST_STATIC_ASSERT(( is_same<
        ovdtl::result< ovdtl::change_result_type<overload_type, sig5_t>::type >::type,
        double
        >::value ));

//////////////////////////////////////////////////////////////////////////////
// test boost::result_of

BOOST_STATIC_ASSERT(( is_same<
        boost::result_of< ovdtl::change_result_type<overload_type, sig0_t>::type >::type,
        int
        >::value ));

BOOST_STATIC_ASSERT(( is_same<
        boost::result_of< ovdtl::change_result_type<overload_type, sig1_t>::type >::type,
        int
        >::value ));

BOOST_STATIC_ASSERT(( is_same<
        boost::result_of< ovdtl::change_result_type<overload_type, sig2_t>::type >::type,
        double
        >::value ));

BOOST_STATIC_ASSERT(( is_same<
        boost::result_of< ovdtl::change_result_type<overload_type, sig3_t>::type >::type,
        char
        >::value ));

BOOST_STATIC_ASSERT(( is_same<
        boost::result_of< ovdtl::change_result_type<overload_type, sig4_t>::type >::type,
        int
        >::value ));

BOOST_STATIC_ASSERT(( is_same<
        boost::result_of< ovdtl::change_result_type<overload_type, sig5_t>::type >::type,
        double
        >::value ));

//BOOST_STATIC_ASSERT(( is_same<
//        boost::result_of< ovdtl::change_result_type<overload_type, int(int* )>::type >::type,
//        int
//        >::value ));

}  // namespace result_test_ns


#endif /* _TEST_RESULT_HPP_ */
