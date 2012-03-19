/*=============================================================
    Boost Overload
    Example 10 - Using the set_for_each_shared_signature
                 method with a multi-signature function object
==============================================================*/

//[ set_for_each_shared_signature_cpp
#include <boost/detail/lightweight_test.hpp>
#include <boost/overload.hpp>

/* polymorphic function object */
struct bar
{
    int operator()(int ) { return -1; }

    template<typename T>
    int operator()(T ) { return sizeof(T); }
};

int main()
{

    boost::overload<int (int ), int (char ), int (int, int )> f;

    // function object
    bar foo;

    // we use the set_for_each_shared_signature method
    // for setting a copy of foo as object target for
    // both the shared int(int ) and int(char ) call signatures
    // *warning*: internally two separate boost::functions
    // are created
    f.set_for_each_shared_signature(foo);
    // invokes int foo(int ) template instantiation
    BOOST_ASSERT( f(1) == foo(1) );
    // invokes int foo(char ) template instantiation
    BOOST_ASSERT( f('x') == foo('x') );
    // through the empty<Signature>() method we check
    // that object target related to the not shared
    // int(int, int ) call signature is still empty
    BOOST_ASSERT( f.empty<int(int, int )>() );


    return boost::report_errors();
}
//]
