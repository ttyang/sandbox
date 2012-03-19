/*=============================================================
    Boost Overload
    Example 11 - Using the set_for_each_shared_signature method
                 with a statefull polymorphic function object
==============================================================*/

//[ statefull_polymorphic_function_object_cpp
#include <boost/detail/lightweight_test.hpp>
#include <boost/overload.hpp>

/* polymorphic function object */
struct bar
{
    bar() : total_calls(0) {}

    int operator()(int ) { ++total_calls; return -1; }

    template<typename T>
    int operator()(T ) { ++total_calls; return sizeof(T); }

    int total_calls;
};

int main()
{
    boost::overload<int (int ), int (char )> f;

    // function object
    bar foo;
    foo( 1 ); foo( 'x' );
    BOOST_ASSERT( foo.total_calls == 2 );

    f.set_for_each_shared_signature(foo);
    f(1); f('x');
    BOOST_ASSERT( foo.total_calls == 2 ); // not 4
    // f.get<int (int )>() and f.get<double (double )>() are
    // different boost::function instances that own two
    // different copy of the foo function object
    const bar* foo_copy_1 = f.get<int (int )>().target<bar>();
    BOOST_ASSERT( foo_copy_1->total_calls == 3 ); // not 4
    const bar* foo_copy_2 = f.get<int (char )>().target<bar>();
    BOOST_ASSERT( foo_copy_2->total_calls == 3 ); // not 4

    f.clear_all();
    BOOST_ASSERT( f.empty_all() );
    // foo.total_calls is still equal to 2

    //
    f.set_for_each_shared_signature( boost::ref(foo) );
    f(1); f('x');
    // f.get<int (int )>() and f.get<double (double )>()
    // are different boost::function instances
    // that own a reference to the same function object
    BOOST_ASSERT( foo.total_calls == 4 );
    const bar* foo_ref_1 = f.get<int (int )>().target<bar>();
    BOOST_ASSERT( foo_ref_1->total_calls == 4 );
    const bar* foo_ref_2 = f.get<int (char )>().target<bar>();
    BOOST_ASSERT( foo_ref_2->total_calls == 4 );


    return boost::report_errors();
}
//]
