
#ifndef _TEST_ASSIGNMENT_HPP_
#define _TEST_ASSIGNMENT_HPP_


void assignment_test()
{

    typedef boost::overload<int (int, int), int (int, std::string )> overload_type;

    overload_type f;
    f14_t f14;
    f.set<0>(f14);
    f.set<1>(f14);

    overload_type g(f);
    BOOST_ASSERT( g(1,1) == f(1, 1) );
    BOOST_ASSERT( g(1, "hi") == f(1, "hi") );


    overload_type h;
    h = f;
    BOOST_ASSERT( h(1,1) == f(1, 1) );
    BOOST_ASSERT( h(1, "hi") == f(1, "hi") );

    overload_type f2;
    f2.set<int (int, int)>(&foo12);
    f2.set<int (int, std::string )>(&foo12);
    f.swap(f2);
    BOOST_ASSERT( f(1,1) == 12 );
    BOOST_ASSERT( f(1, "hello") == 122 );
    BOOST_ASSERT( f2(1,1) == sizeof(int) );
    BOOST_ASSERT( f2(1, "hello") == sizeof(std::string) );

    boost::swap( f, f2);
    BOOST_ASSERT( f2(1,1) == 12 );
    BOOST_ASSERT( f2(1, "hello") == 122 );
    BOOST_ASSERT( f(1,1) == sizeof(int) );
    BOOST_ASSERT( f(1, "hello") == sizeof(std::string) );
}

#endif /* _TEST_ASSIGNMENT_HPP_ */
