
#ifndef _TEST_SIGNATURE_WITH_PTR_AND_REF_HPP_
#define _TEST_SIGNATURE_WITH_PTR_AND_REF_HPP_


void signature_with_ptr_and_ref_test()
{
    boost::overload<sig8_t, sig9_1_t, sig9_2_t, sig10_t> f;

    bar9 b9;
    bar10 b10;

    f.set(&foo8);
    f.set(&bar9::foo9_1);
    f.set(&bar9::foo9_2);
    f.set(&bar10::foo10);

    double d = 5;
    double* p = &d;

    BOOST_ASSERT( f(d) == 8 );
    BOOST_ASSERT( f(&b9, &p) == 9 );
    BOOST_ASSERT( f(&b9 , p) == 10 );
    BOOST_ASSERT( f(&b10, &p) == 11 );

    f.clear_all();
    BOOST_ASSERT( f.empty_all() );

    f.set<sig8_t>(&foo8);
    f.set<sig9_1_t>(&bar9::foo9_1);
    f.set<sig9_2_t>(&bar9::foo9_2);
    f.set<sig10_t>(&bar10::foo10);

    BOOST_ASSERT( f(d) == 8 );
    BOOST_ASSERT( f(&b9, &p) == 9 );
    BOOST_ASSERT( f(&b9 , p) == 10 );
    BOOST_ASSERT( f(&b10, &p) == 11 );

    f.clear_all();
    BOOST_ASSERT( f.empty_all() );

    f.set<0>(&foo8);
    f.set<1>(&bar9::foo9_1);
    f.set<2>(&bar9::foo9_2);
    f.set<3>(&bar10::foo10);

    BOOST_ASSERT( f(d) == 8 );
    BOOST_ASSERT( f(&b9, &p) == 9 );
    BOOST_ASSERT( f(&b9 , p) == 10 );
    BOOST_ASSERT( f(&b10, &p) == 11 );

}



#endif // _TEST_SIGNATURE_WITH_PTR_AND_REF_HPP_

