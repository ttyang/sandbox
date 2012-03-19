
#ifndef _TEST_GET_SIGNATURE_HPP_
#define _TEST_GET_SIGNATURE_HPP_


#include<boost/overload/detail/get_signature.hpp>

namespace get_signature_test_ns {


// pointer to function
BOOST_STATIC_ASSERT(( is_same<
        ovdtl::get_signature<f0_t>::type,
        sig0_t
        >::value ));
// pointer to member function
BOOST_STATIC_ASSERT(( is_same<
        ovdtl::get_signature<f1_t>::type,
        sig1_t
        >::value ));
// pointer to const member function
BOOST_STATIC_ASSERT(( is_same<
        ovdtl::get_signature<f2_t>::type,
        sig2_t
        >::value ));
// boost::function
BOOST_STATIC_ASSERT(( is_same<
        ovdtl::get_signature<f3_t>::type,
        sig3_t
        >::value ));
// function object type
BOOST_STATIC_ASSERT(( is_same<
        ovdtl::get_signature<f4_t>::type,
        sig4_t
        >::value ));
// function object type (operator() const)
BOOST_STATIC_ASSERT(( is_same<
        ovdtl::get_signature<f5_t>::type,
        sig5_t
        >::value ));
// boost::reference_wrapper
BOOST_STATIC_ASSERT(( is_same<
        ovdtl::get_signature< boost::reference_wrapper<f4_t> >::type,
        sig4_t
        >::value ));
// boost::reference_wrapper (operator() const)
BOOST_STATIC_ASSERT(( is_same<
        ovdtl::get_signature< boost::reference_wrapper<f5_t> >::type,
        sig5_t
        >::value ));
// pointer to member function
BOOST_STATIC_ASSERT(( is_same<
        ovdtl::get_signature<f9_1_t>::type,
        sig9_1_t
        >::value ));
// pointer to const member function
BOOST_STATIC_ASSERT(( !is_same<
        ovdtl::get_signature<f9_2_t>::type,
        sig9_2_t
        >::value ));

} // namespace get_signature_test_ns


#endif /* _TEST_GET_SIGNATURE_HPP_ */
