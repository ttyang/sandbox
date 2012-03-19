/*=============================================================
    Boost Overload
    Example 6 - Using the call signature based syntax
                with free and member polymorphic function
==============================================================*/

//[ signature_syntax_2_cpp
#include <boost/detail/lightweight_test.hpp>
#include <boost/overload.hpp>


template<typename T>
int foo(T  ) { return (3 + sizeof(T)); }

struct bar
{
    int mf(int ) { return 1; }
    int mf(double ) { return 2; }
};

int main()
{

    boost::overload<int (int ), int (double ),
                    int (bar*, int ), int (bar*, double )> f;

    // bar instance
    bar abar;

    // set bar::*mf as object target
    // for the int (bar*, int ) call signature only
    f.set<int (bar*, int )>(&bar::mf);
    // invokes int bar.mf(int )
    BOOST_ASSERT( f(&abar, 1) == abar.mf(1) );
    BOOST_ASSERT( f.empty<int (bar*, double )>() );

    // set bar::*mf as object target
    // for the int (bar*, double ) call signature too
    f.set<int (bar*, double )>(&bar::mf);
    BOOST_ASSERT( f(&abar, 1.0) == abar.mf(1.0) );
    BOOST_ASSERT( f(&abar, 1) == abar.mf(1) );

    // set *foo as object target
    // for the int (int ) call signature only
    f.set<int (int )>(&foo);
    BOOST_ASSERT( f(1) == foo(1) );
    BOOST_ASSERT( f.empty<int (double )>() );

    // set *foo as object target
    // for the int (double ) call signature too
    f.set<int (double )>(&foo);
    BOOST_ASSERT( f(1.0) == foo(1.0) );
    BOOST_ASSERT( f(1) == foo(1) );


    return boost::report_errors();
}
//]
