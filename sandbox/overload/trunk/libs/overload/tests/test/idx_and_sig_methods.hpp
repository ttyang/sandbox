
#ifndef TEST_IDX_AND_SIG_METHODS_HPP
#define TEST_IDX_AND_SIG_METHODS_HPP

void index_and_signature_methods_test()
{
    typedef boost::overload<sig0_t, sig1_t, sig2_t, sig3_t, sig4_t, 
                            sig5_t, sig6_1_t, sig6_2_t, sig7_1_t, sig7_2_t> 
            overload_type;

    f0_t f0 = &foo0;                // function pointer
    f1_t f1 = &bar1::foo1;          // member function pointer
    f2_t f2 = &bar2::foo2;          // member function pointer (with const)
    f3_t f3 = &foo3;                // boost::function
    f3_t f3b = &foo3b;              // same signature (swap test)
    f4_t f4;                        // function object
    f5_t f5;                        // function object (with const)
    f6_t f6;                        // overloaded function object
    f7_t f7;                        // polymorfic function object

    bar1 b1; bar2 b2;

    overload_type f;

    f.set<sig0_t>(f0);
    f.set<sig1_t>(f1);
    f.set<sig5_t>(f5).set<sig3_t>(f3).set<sig4_t>(f4).set<sig2_t>(f2);
    f.set<sig6_1_t>(f6).set<sig6_2_t>(f6);
    f.set<sig7_2_t>(f7).set<sig7_1_t>(f7);

    {
        int out0        = f( "Hi",  ", ",  "people !" );
        int out1        = f(&b1, 'x');
        double out2     = f(&b2, 123, 'x');
        char out3       = f("hello");
        int out4        = f('x');
        double out5     = f(123, 'x');
        double out61    = f(2.5f);
        double out62    = f(3.0f, 4.0f);
        int out71       = f(1);
        double out72    = f(2.5);

        BOOST_ASSERT(out0 == 12);
        BOOST_ASSERT(out1 == 123);
        BOOST_ASSERT(out2 > 233.999 && out2 < 234.001);
        BOOST_ASSERT(out3 == 'Y');
        BOOST_ASSERT(out4 == 456);
        BOOST_ASSERT(out5 > 566.999 && out5 < 567.001);
        BOOST_ASSERT(out61 > 6780.999 && out61 < 6781.001);
        BOOST_ASSERT(out62 > 6781.999 && out62 < 6782.001);
        BOOST_ASSERT(out71 == (789 + sizeof(int)));
        BOOST_ASSERT(out72 > (788.999 + sizeof(double)) &&
                     out72 < (789.001 + sizeof(double)));
    }

    f.clear_all();
    BOOST_ASSERT( f.empty_all() );

    f.set<0>(f0);
    f.set<1>(f1);
    f.set<5>(f5).set<3>(f3).set<4>(f4).set<2>(f2);
    f.set<6>(f6).set<7>(f6);
    f.set<8>(f7).set<9>(f7);

    {
        int out0        = f( "Hi",  ", ",  "people !" );
        int out1        = f(&b1, 'x');
        double out2     = f(&b2, 123, 'x');
        char out3       = f("hello");
        int out4        = f('x');
        double out5     = f(123, 'x');
        double out61    = f(2.5f);
        double out62    = f(3.0f, 4.0f);
        int out71       = f(1);
        double out72    = f(2.5);

        BOOST_ASSERT(out0 == 12);
        BOOST_ASSERT(out1 == 123);
        BOOST_ASSERT(out2 > 233.999 && out2 < 234.001);
        BOOST_ASSERT(out3 == 'Y');
        BOOST_ASSERT(out4 == 456);
        BOOST_ASSERT(out5 > 566.999 && out5 < 567.001);
        BOOST_ASSERT(out61 > 6780.999 && out61 < 6781.001);
        BOOST_ASSERT(out62 > 6781.999 && out62 < 6782.001);
        BOOST_ASSERT(out71 == (789 + sizeof(int)));
        BOOST_ASSERT(out72 > (788.999 + sizeof(double)) &&
                     out72 < (789.001 + sizeof(double)));
    }

    f.clear<sig0_t>();                      // same as f.clear<0>()
    BOOST_ASSERT( f.empty<sig0_t>() );      // same as f.empty<0>()

    boost::function<sig3_t> g(f3b);
    f.swap_function(g);
    BOOST_ASSERT(f("hello") == 'Z');
    BOOST_ASSERT(g("hello") == 'Y');

    g = f.get<sig3_t>();                    // same as f.get<3>()
    BOOST_ASSERT(g("hello") == 'Z');

}



#endif // TEST_IDX_AND_SIG_METHODS_HPP

