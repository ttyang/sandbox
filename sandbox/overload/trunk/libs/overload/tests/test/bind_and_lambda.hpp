
#ifndef _TEST_BIND_AND_LAMBDA_HPP_
#define _TEST_BIND_AND_LAMBDA_HPP_


#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

void lambda_test()
{
    using namespace boost::lambda;

    boost::overload<int& (int& ), int (int, int )> f;
    f.set<int& (int& )>( _1 += 10 );
    f.set<int (int, int )>( _1 + _2 );
    int m = 3, n = 2;
    f(n);
    BOOST_ASSERT( n == 12 );
    BOOST_ASSERT( f(m, n) == 15 );

    f.clear_all();
    f.set<0>( _1 += 10 );
    f.set<1>( _1 + _2 );
    m = 3, n = 2;
    f(n);
    BOOST_ASSERT( n == 12 );
    BOOST_ASSERT( f(m, n) == 15 );


    boost::overload<int (char ), double (int, char )> ff;

    bar1 b1;
    bar2 b2;


    ff.set<int (char )>( bind( &bar1::foo1, &b1, _1 ) );
    ff.set<double (int, char )>( bind( &bar2::foo2, &b2, _1, _2 ) );

    int out1        = ff('x');
    double out2     = ff(123, 'x');

    BOOST_ASSERT(out1 == 123);
    BOOST_ASSERT(out2 > 233.999 && out2 < 234.001);

}

#include <boost/bind.hpp>

void bind_test()
{
    boost::overload<int (char ), double (int, char )> f;

    bar1 b1;
    bar2 b2;


    f.set<int (char )>( boost::bind( &bar1::foo1, &b1, _1 ) );
    f.set<double (int, char )>( boost::bind( &bar2::foo2, &b2, _1, _2 ) );

    int out1        = f('x');
    double out2     = f(123, 'x');

    BOOST_ASSERT(out1 == 123);
    BOOST_ASSERT(out2 > 233.999 && out2 < 234.001);

    f.clear_all();

    f.set<0>( boost::bind( &bar1::foo1, &b1, _1 ) );
    f.set<1>( boost::bind( &bar2::foo2, &b2, _1, _2 ) );

    out1     = f('x');
    out2     = f(123, 'x');

    BOOST_ASSERT(out1 == 123);
    BOOST_ASSERT(out2 > 233.999 && out2 < 234.001);


}


#endif // _TEST_BIND_AND_LAMBDA_HPP_

