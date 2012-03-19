
#ifndef _TEST_TRAIT_BY_FUNCTOR_HPP_
#define _TEST_TRAIT_BY_FUNCTOR_HPP_


namespace test03 {

typedef boost::overload<sig0_t, sig1_t, sig2_t, sig3_t, sig4_t, 
                        sig5_t, sig6_1_t, sig6_2_t, sig7_1_t, sig7_2_t> 
        overload_type;

BOOST_STATIC_ASSERT(( ovdtl::functor_has_signature<f4_t, sig4_t>::value ));
BOOST_STATIC_ASSERT(( ovdtl::number_of_shared_signatures<f0_t, overload_type>::value == 1 ));
BOOST_STATIC_ASSERT(( ovdtl::number_of_shared_signatures<f1_t, overload_type>::value == 1 ));
BOOST_STATIC_ASSERT(( ovdtl::number_of_shared_signatures<f3_t, overload_type>::value == 1 ));
BOOST_STATIC_ASSERT(( ovdtl::number_of_shared_signatures<f4_t, overload_type>::value == 1 ));
BOOST_STATIC_ASSERT(( ovdtl::number_of_shared_signatures<f8_t, overload_type>::value == 0 ));
BOOST_STATIC_ASSERT(( ovdtl::number_of_shared_signatures<f10_t, overload_type>::value == 0 ));

// MSVC 7.1 doesn't succeed in managing the signature of a multi-signature
// function object
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1400)
BOOST_STATIC_ASSERT(( ovdtl::number_of_shared_signatures<f6_t, overload_type>::value == 2 ));
BOOST_STATIC_ASSERT(( ovdtl::number_of_shared_signatures<f7_t, overload_type>::value == 2 ));
BOOST_STATIC_ASSERT(( ovdtl::number_of_shared_signatures<f14_t, overload_type>::value == 1 ));
#endif

}


namespace test04 {

typedef boost::overload<sig0_t, sig1_t, sig2_t, sig3_t, sig4_t, sig5_t, sig6_1_t, sig6_2_t>
        overload_type;

BOOST_STATIC_ASSERT(( 
    is_same<ovdtl::base_by_functor<f0_t, overload_type>::type, 
            overload_type::base_type
    >::value
));
BOOST_STATIC_ASSERT(( 
    is_same<ovdtl::signature_by_functor<f5_t, ovdtl::base_by_functor<f0_t, overload_type>::type >::type, 
            sig5_t
    >::value 
));
BOOST_STATIC_ASSERT(( 
    is_same<ovdtl::function_by_functor<f1_t, overload_type>::type, 
            boost::function<sig1_t> 
    >::value 
));
BOOST_STATIC_ASSERT(( ovdtl::index_by_functor<f2_t, overload_type>::value == 2 ));
BOOST_STATIC_ASSERT(( ovdtl::have_any_shared_signature<f3_t, overload_type>::value ));
BOOST_STATIC_ASSERT(( ovdtl::have_any_shared_signature<f4_t, overload_type>::value ));
BOOST_STATIC_ASSERT(( !ovdtl::have_any_shared_signature<f7_t, overload_type>::value ));

}


#endif // _TEST_TRAIT_BY_FUNCTOR_HPP_

