/*=============================================================
    Boost Overload
    Example 9 - Using the index based syntax
                with a multi-signature function object
==============================================================*/

//[ index_syntax_cpp
#include <boost/detail/lightweight_test.hpp>
#include <boost/overload.hpp>

/* polymorphic function object */
struct bar
{
    int operator()(int ) { return 1; }

    template<typename T>
    int operator()(T ) { return ( 2 + sizeof(T) ); }
};

int main()
{

    boost::overload<int (int ), int (char ), int (double )> f;

    // function object
    bar foo;

    // we use the index syntax for setting a copy of
    // foo as object target for the second call signature
    // int (char ) only
    f.set<1>(foo);
    // invokes int foo(char ) template instantiation
    BOOST_ASSERT( f('x') == foo('x') );
    // through the empty<N>() method we check
    // that no other object target has been set up
    BOOST_ASSERT( f.empty<0>() );
    BOOST_ASSERT( f.empty<2>() );

    // now we set a copy of foo as object target tied to
    // the first call signature int( int )
    f.set<0>(foo);
    BOOST_ASSERT( f('x') == foo('x') );
    BOOST_ASSERT( f(1) == foo(1) );
    BOOST_ASSERT( f.empty<2>() );

    // and finally we set up also the object target
    // for the last call signature int(double )
    f.set<2>(foo);
    BOOST_ASSERT( f('x') == foo('x') );
    BOOST_ASSERT( f(1) == foo(1) );
    BOOST_ASSERT( f(1.0) == foo(1.0) );


    return boost::report_errors();
}
//]
