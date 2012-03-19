/*=============================================================
    Boost Overload
    Example 7 - Using the call signature based syntax
                with two member functions that differ
                for the const qualifier only
==============================================================*/

//[ signature_syntax_3_cpp
#include <string>
#include <boost/detail/lightweight_test.hpp>
#include <boost/overload.hpp>


struct bar
{
    int mf(int ) { return 1; }
    int mf(int ) const { return 2; }
    int mf(double ) { return 3; }
};


int main()
{
    // overload object that supports the *non-const* qualified
    // explicit call signature int (bar*, int )
    boost::overload<int (bar*, int ), int (bar*, double )> f;

    // bar instance
    bar foo;

    // we set bar::*mf as object target
    // for the int (bar*, double ) call signature only
    f.set<int (bar*, double )>(&bar::mf);
    BOOST_ASSERT( f(&foo, 1.0) == 3 );
    BOOST_ASSERT( f.empty<int (bar*, int )>() );

    // if you try to compile the following line of code:
    // f.set<int (bar*, int )>(&bar::mf);
    // you get a compiler error, because the call signature
    // syntax is not able to disambiguate between two member
    // functions that differ for the const qualifier only


    // in order to set a pointer to the non-const qualified
    // version of bar::mf as object target
    // for the int (bar*, int ) call signature of the overload
    // object f, you can utilize a special variant of
    // the call signature syntax
    using boost::overloads::non_const;
    f.set<int (bar*, int ), non_const>(&bar::mf);
    // now foo.mf(int ) is invoked
    BOOST_ASSERT( f(&foo, 1) == 1 );

    // what if I want to set a pointer to
    // the const qualified version of boost::mf as object
    // target for the int (bar*, int ) call signature of
    // the overload object f ?

    // first off, you should notice that the set up of such
    // a target is semantically correct because the explicit
    // call signature of the const qualified bar::mf function
    // member is int (const bar*, int ) and we can always pass
    // a T* argument where a const T* is expected.

    // as above you can utilize the special variant of the call
    // signature syntax
    using boost::overloads::const_;
    f.set<int (bar*, int ), const_>(&bar::mf);
    // now foo.mf(int ) const is invoked
    BOOST_ASSERT( f(&foo, 1) == 2 );



    // you should notice that in case we have an overload
    // object that supports the *const* qualified explicit call
    // signature int (const bar*, int )
    boost::overload<int (const bar*, int ),
                    int (bar*, std::string )> g;
    // we can utilize the standard call signature based syntax
    // because selecting the const qualified version of the
    // bar::mf member function is the only semantically correct
    // choice

    // no compiler error here!
    g.set<int (const bar*, int )>(&bar::mf);
    // foo.mf(int ) const is invoked
    BOOST_ASSERT( g(&foo, 1) == 2 );

    // and if you try to compile the following line of code:
    // g.set<int (const bar*, int ), non_const>(&bar::mf);
    // you get a compiler error because you cannot pass a
    // const T* argument where a T* is expected

    return boost::report_errors();
}
//]
