
#ifndef _TEST_COMPATIBLE_SIGNATURES_
#define _TEST_COMPATIBLE_SIGNATURES_



int goo1(int )
{
    return 1;
}
typedef int s1_t (int );


int goo2(double )
{
    return 2;
}
typedef int s2_t (double );


double goo3(int )
{
    return 3.0;
}
typedef double s3_t (int );


int goo4(std::string )
{
    return 4;
}
typedef int s4_t (std::string );


struct goo5
{
    template< typename T >
    T operator()(T x)
    {
        return x;
    }
};


double goo6(double )
{
    return 6;
}




void compatible_signature_test()
{
    boost::overload<int (std::string ), double (int )> f1;

    f1.set<double (int )>( &goo1 );
    BOOST_ASSERT( !f1.empty<double (int )>() );
    BOOST_ASSERT( f1(10) == goo1(10) );

    f1.set<double (int )>( goo5() );
    BOOST_ASSERT( !f1.empty<double (int )>() );
    BOOST_ASSERT( f1(10) == goo5()(10) );

    f1.set<double (int )>( &goo2 );
    BOOST_ASSERT( !f1.empty<double (int )>() );
    BOOST_ASSERT( f1(10) == goo2(10.0) );


    f1.clear_all();
    BOOST_ASSERT( f1.empty_all() );

    f1.set<1>( &goo1 );
    BOOST_ASSERT( !f1.empty<1>() );
    BOOST_ASSERT( f1(10) == goo1(10) );

    f1.set<1>( goo5() );
    BOOST_ASSERT( !f1.empty<1>() );
    BOOST_ASSERT( f1(10) == goo5()(10) );

    f1.set<1>( &goo2 );
    BOOST_ASSERT( !f1.empty<1>() );
    BOOST_ASSERT( f1(10) == goo2(10.0) );


/*
    boost::overload<int (std::string ), int (double )> f2;

    // warning here: converting to 'int' from 'double'
    f2.set<int (double )>( &goo1 );
    BOOST_ASSERT( !f2.empty<int (double )>() );
    BOOST_ASSERT( f2(10.0) == goo1(10) );

    // warning here: converting to 'int' from 'double'
    f2.set<int (double )>( goo5() );
    BOOST_ASSERT( !f2.empty<int (double )>() );
    BOOST_ASSERT( f2(10.0) == goo5()(10.0) );

    // double warning here: converting to 'int' from 'double'
    f2.set<int (double )>( &goo3 );
    BOOST_ASSERT( !f2.empty<int (double )>() );
    BOOST_ASSERT( f2(10.0) == goo3(10) );
*/
    // error here:
    // invalid conversion from `int (*)(std::string)' to `int (*)(double)'
    // f2.set<int (double )>( &goo4 );

    // error here:
    // boost static assertion failure:
    // have_any_shared_signature<int (int), overload_type> evaluates to false
    // f1.set( &goo1 );


    boost::overload<double (double ), double (int )> f3;

    f3.set<double (int )>( &goo6 );
    BOOST_ASSERT( f3.empty<double (double )>() );
    BOOST_ASSERT( !f3.empty<double (int )>() );
    BOOST_ASSERT( f3(10) == goo6(10.0) );

    f3.set<double (double )>( &goo2 );
    BOOST_ASSERT( !f3.empty<double (double)>() );
    BOOST_ASSERT( f3(10.0) == goo2(10) );
    BOOST_ASSERT( f3(10) == goo6(10.0) );


    f3.clear_all();
    BOOST_ASSERT( f3.empty_all() );

    f3.set<1>( &goo6 );
    BOOST_ASSERT( f3.empty<0>() );
    BOOST_ASSERT( !f3.empty<1>() );
    BOOST_ASSERT( f3(10) == goo6(10.0) );

    f3.set<0>( &goo2 );
    BOOST_ASSERT( !f3.empty<0>() );
    BOOST_ASSERT( f3(10.0) == goo2(10) );
    BOOST_ASSERT( f3(10) == goo6(10.0) );

}


#endif // _TEST_COMPATIBLE_SIGNATURES_

