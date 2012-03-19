/*=============================================================
    Boost Overload
    Example 8 - Using the call signature based syntax
                for setting as target a functor whose call
                signature is only compatible
==============================================================*/

//[ compatible_signature_cpp
#include <string>
#include <boost/detail/lightweight_test.hpp>
#include <boost/overload.hpp>

int foo(double ) { return 1; }


int main()
{
    boost::overload<int (std::string ), int (int )> f1;

    // the call signature of the foo free function does not
    // match exactly any call signature of f1, anyway it is
    // compatible with the call signature int (int )
    // because an int type convert implicitly to a double
    // for this reason the set<Signature> method let you
    // pass as argument a functor whose call signature is only
    // compatible with the call signature Signature
    f1.set<int (int )>( &foo );
    // ok the target object tied to the int (int )
    // call signature is set
    BOOST_ASSERT( !f1.empty<int (int )>() );
    // foo is invoked
    BOOST_ASSERT( f1(1) == foo(1) );

    // all that work even if the overload object owns a call
    // signature that matches exactly the call signature of the
    // functor
    boost::overload<int (double ), int (int )> f2;

    // all work exactly as before
    f2.set<int (int )>( &foo );
    BOOST_ASSERT( !f2.empty<int (int )>() );
    BOOST_ASSERT( f2(1) == foo(1) );
    // no object target has been set up for
    // the int (double ) call signature
    BOOST_ASSERT( f2.empty<int (double )>() );


    return boost::report_errors();
}
//]
