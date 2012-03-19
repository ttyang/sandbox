
#ifndef _TEST_TEST_TARGET_HPP_
#define _TEST_TEST_TARGET_HPP_


void test_target_test()
{
    boost::overload<sig0_t, sig1_t, sig2_t> f;
    BOOST_ASSERT( f.empty_all() );
    BOOST_ASSERT( f.empty_any() );

    f.set(&foo0);
    BOOST_ASSERT( !f.empty_all() );
    BOOST_ASSERT( f.empty_any() );

    f.set(&bar1::foo1);
    BOOST_ASSERT( !f.empty_all() );
    BOOST_ASSERT( f.empty_any() );

    f.set(&bar2::foo2);
    BOOST_ASSERT( !f.empty_all() );
    BOOST_ASSERT( f.empty_none() );
}


#endif /* _TEST_TEST_TARGET_HPP_ */
