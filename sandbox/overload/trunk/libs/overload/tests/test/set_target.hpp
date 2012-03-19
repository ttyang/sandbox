
#ifndef _TEST_SET_TARGET_HPP_
#define _TEST_SET_TARGET_HPP_


void set_target_test()
{
    boost::overload<sig0_t, sig1_t, sig2_t, sig3_t, sig4_t, sig5_t, sig6_1_t, sig6_2_t, sig7_1_t, sig7_2_t> f;

    f0_t f0 = &foo0;                // function pointer
    f1_t f1 = &bar1::foo1;          // member function pointer
    f2_t f2 = &bar2::foo2;          // member function pointer (with const)
    f3_t f3 = &foo3;                // boost::function
    f4_t f4;                        // function object
    f5_t f5;                        // function object (with const)

    f.set( f0 );
    f.set( f1 );
    f.set( f2 );
    f.set( f3 );
    f.set( f4 );
    f.set( f5 );

    f.clear_all();

    f.set_for_each_shared_signature( f0 );
    f.set_for_each_shared_signature( f1 );
    f.set_for_each_shared_signature( f2 );
    f.set_for_each_shared_signature( f3 );
    f.set_for_each_shared_signature( f4 );
    f.set_for_each_shared_signature( f5 );


    // MSVC 7.1 doesn't succeed in deducing the signature of a multi-signature
    // function object
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1400)
    f6_t f6;                        // overloaded function object
    f7_t f7;                        // template function object

    //f.set( f6 );                  // more than one signature supported
    //f.set( f7 );                  // more than one signature supported

    f.set_for_each_shared_signature( f6 );
    f.set_for_each_shared_signature( f7 );
#endif


    //f8_t f8 = &foo8;                // function pointer
    //f9_1_t f9_1 = &bar9::foo9_1;    // member function pointer

    //f.set( f8 );                  // not supported signature
    //f.set( f9_1 );                // not supported signature

    //f.set_for_each_shared_signature( f8 );
    //f.set_for_each_shared_signature( f9_1 );

}




#endif // _TEST_SET_TARGET_HPP_

