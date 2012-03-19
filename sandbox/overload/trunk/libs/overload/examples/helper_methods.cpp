/*=============================================================
    Boost Overload
    Example 6 - Using helper methods
==============================================================*/

//[ helper_methods_cpp
#include <boost/detail/lightweight_test.hpp>
#include <boost/overload.hpp>

int zoo(double ) { return 1; }

template<typename T>
int foo(T ) { return (2 + sizeof(T)); }

int zoo2(double ) { return -1; }

template<typename T>
int foo2(T ) { return -(int)(2 + sizeof(T)); }

typedef int sig1 (int );
typedef int sig2 (double );
typedef int sig3 (char );


int main()
{
    // test if a object target is valid
    boost::overload<sig1, sig2, sig3>f;
    // all object targets are empty
    BOOST_ASSERT( f.empty_all() );
    BOOST_ASSERT( f.empty_any() );
    BOOST_ASSERT( f.empty<sig1>() );
    BOOST_ASSERT( f.empty<sig2>() );
    BOOST_ASSERT( f.empty<sig3>() );

    f.set<sig1>(&foo);
    // only the first object target is set
    BOOST_ASSERT( !f.empty_all() );
    BOOST_ASSERT( f.empty_any() );
    BOOST_ASSERT( !f.empty<sig1>() );
    BOOST_ASSERT( f.empty<sig2>() );
    BOOST_ASSERT( f.empty<sig3>() );

    f.set<sig2>(&zoo);
    // only the last object target is not set
    BOOST_ASSERT( !f.empty_all() );
    BOOST_ASSERT( f.empty_any() );
    BOOST_ASSERT( !f.empty<sig1>() );
    BOOST_ASSERT( !f.empty<sig2>() );
    BOOST_ASSERT( f.empty<sig3>() );

    f.set<sig3>(&foo);
    // no object target is empty
    BOOST_ASSERT( !f.empty_all() );
    BOOST_ASSERT( f.empty_none() );
    BOOST_ASSERT( !f.empty<sig1>() );
    BOOST_ASSERT( !f.empty<sig2>() );
    BOOST_ASSERT( !f.empty<sig3>() );

    f.clear<sig2>();
    // all object targets set but the second one
    BOOST_ASSERT( !f.empty_all() );
    BOOST_ASSERT( f.empty_any() );
    BOOST_ASSERT( !f.empty<sig1>() );
    BOOST_ASSERT( f.empty<sig2>() );
    BOOST_ASSERT( !f.empty<sig3>() );

    f.clear_all();
    // all object targets are empty again
    BOOST_ASSERT( f.empty_all() );
    BOOST_ASSERT( f.empty_any() );
    BOOST_ASSERT( f.empty<sig1>() );
    BOOST_ASSERT( f.empty<sig2>() );
    BOOST_ASSERT( f.empty<sig3>() );


    // swapping
    f.set<sig1>(&foo).set<sig2>(&zoo).set<sig3>(&foo);
    boost::function<sig2> h = f.get<sig2>();
    BOOST_ASSERT( h(1.0) == zoo(1.0) );
    h = &zoo2;
    BOOST_ASSERT( h(1.0) == zoo2(1.0) );
    f.swap_function(h);
    BOOST_ASSERT( f(1.0) == zoo2(1.0) );
    BOOST_ASSERT( h(1.0) == zoo(1.0) );
    f.set<sig2>(h);
    BOOST_ASSERT( f(1.0) == zoo(1.0) );

    boost::overload<sig1, sig2, sig3> g;
    g.set<sig1>(&foo2).set<sig2>(&zoo2).set<sig3>(&foo2);
    f.swap(g);
    BOOST_ASSERT( f(1) == foo2(1) );
    BOOST_ASSERT( f(1.0) == zoo2(1.0) );
    BOOST_ASSERT( f('x') == foo2('x') );
    BOOST_ASSERT( g(1) == foo(1) );
    BOOST_ASSERT( g(1.0) == zoo(1.0) );
    BOOST_ASSERT( g('x') == foo('x') );

    return boost::report_errors();
}
//]
