/*=============================================================
    Boost Overload
    Example 5 - Using the call signature based syntax
                with a multi-signature function object
==============================================================*/

//[ signature_syntax_1_cpp
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

    // we use the call signature syntax for setting a copy of
    // foo as object target for the call signature int (char )
    // only
    f.set<int (char )>(foo);
    // invokes int foo(char ) template instantiation
    BOOST_ASSERT( f('x') == foo('x') );
    // through the empty<Signature>() method we check
    // that no other object target has been set up
    BOOST_ASSERT( f.empty<int(int )>() );
    BOOST_ASSERT( f.empty<int(double )>() );

    // now we set a copy of foo as object target tied to
    // the call signature int( int )
    f.set<int (int )>(foo);
    BOOST_ASSERT( f('x') == foo('x') );
    BOOST_ASSERT( f(1) == foo(1) );
    BOOST_ASSERT( f.empty<int(double )>() );

    // and finally we set up also the object target
    // for the int(double ) call signature
    f.set<int (double )>(foo);
    BOOST_ASSERT( f('x') == foo('x') );
    BOOST_ASSERT( f(1) == foo(1) );
    BOOST_ASSERT( f(1.0) == foo(1.0) );


    return boost::report_errors();
}
//]
