
#ifndef _TEST_SIGNATURE_DEDUCTION_HPP_
#define _TEST_SIGNATURE_DEDUCTION_HPP_


void signature_deduction_test() 
{
    typedef boost::overload<sig0_t, sig1_t, sig2_t, sig3_t, sig4_t, 
                            sig5_t, sig6_1_t, sig6_2_t, sig7_1_t, sig7_2_t> 
            overload_type;

    f0_t f0 = &foo0;                // function pointer
    f1_t f1 = &bar1::foo1;          // member function pointer
    f2_t f2 = &bar2::foo2;          // member function pointer (with const)
    f3_t f3 = &foo3;                // boost::function
    f4_t f4;                        // function object
    f5_t f5;                        // function object (with const)

    bar1 b1; bar2 b2;

    overload_type f(f4, f2);
    f.set(f0, f5, f1, f3);

    int out0    = f( "Hello",  ", ",  "world !" );
    int out1    = f(&b1, 'x');
    double out2 = f(&b2, 123, 'x');
    char out3   = f("hello");
    int out4    = f('x');
    double out5 = f(123, 'x');

    BOOST_ASSERT(out0 == 12);
    BOOST_ASSERT(out1 == 123);
    BOOST_ASSERT(out2 > 233.999 && out2 < 234.001);
    BOOST_ASSERT(out3 == 'Y');
    BOOST_ASSERT(out4 == 456);
    BOOST_ASSERT(out5 > 566.999 && out5 < 567.001);


    //////////////////////////////////////////////////////////////////////////
    // multi-signature function objects

    // MSVC 7.1 doesn't succeed in deducing the signature of a multi-signature 
    // function object
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1400)  
 
    f6_t f6;                        // overloaded function object
    f7_t f7;                        // template function object

    f.set_for_each_shared_signature(f6);
    f.set_for_each_shared_signature(f7);

    double out61    = f(2.5f);
    double out62    = f(3.0f, 4.0f);
    int out71       = f(1);
    double out72    = f(2.5);

    BOOST_ASSERT(out61 > 6780.999 && out61 < 6781.001);
    BOOST_ASSERT(out62 > 6781.999 && out62 < 6782.001);
    BOOST_ASSERT(out71 == (789 + sizeof(int)));
    BOOST_ASSERT(out72 > (788.999 + sizeof(double)) &&
                 out72 < (789.001 + sizeof(double)));



    boost::overload<int (int, int), int (int, std::string )> g;
    f14_t f14;
    g.set_for_each_shared_signature(f14);
    BOOST_ASSERT( g(1,1) == sizeof(int) );
    BOOST_ASSERT( g(1, std::string("hi")) == sizeof(std::string) );

#endif

}


#endif // _TEST_SIGNATURE_DEDUCTION_HPP_

