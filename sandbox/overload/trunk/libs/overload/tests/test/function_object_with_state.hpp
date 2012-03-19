
#ifndef _TEST_FUNCTION_OBJECT_WITH_STATE_
#define _TEST_FUNCTION_OBJECT_WITH_STATE_

namespace ns_func_object_with_state_test
{

struct bar
{
    bar() : calls(0) {}

    template< typename T >
    T operator()(T x)
    {
        ++calls;
        return x;
    }

    int calls;
};

void func_object_with_state_test()
{
    bar foo;

    foo( 1 );
    foo( "hello" );
    BOOST_ASSERT( foo.calls == 2 );

    boost::overload<std::string (std::string ), int (int )> f1;
#if BOOST_WORKAROUND(BOOST_MSVC, < 1400)
    f1.set<std::string (std::string )>( foo );
    f1.set<int (int )>( foo );
#else
    f1.set_for_each_shared_signature( foo );
#endif

    f1( 1 );
    f1( "hello" );

    BOOST_ASSERT( f1.get<std::string (std::string )>().target<bar>() );
    BOOST_ASSERT( f1.get<std::string (std::string )>().target<bar>()->calls == 3 );
    BOOST_ASSERT( f1.get<int (int )>().target<bar>() );
    BOOST_ASSERT( f1.get<int (int )>().target<bar>()->calls == 3 );
    BOOST_ASSERT( foo.calls == 2 );

    f1.clear_all();

#if BOOST_WORKAROUND(BOOST_MSVC, < 1400)
    f1.set<std::string (std::string )>( boost::ref(foo) );
    f1.set<int (int )>( boost::ref(foo) );
#else
    f1.set_for_each_shared_signature( boost::ref(foo) );
#endif

    f1( 1 );
    f1( "hello" );

// For intel compilers 9.1 and 10.0 the target method returns NULL pointers
#if !BOOST_WORKAROUND(__INTEL_COMPILER, < 1010) && ! __clang__
    BOOST_ASSERT( f1.get<std::string (std::string )>().target<bar>() );
    BOOST_ASSERT( f1.get<std::string (std::string )>().target<bar>()->calls == 4 );
    BOOST_ASSERT( f1.get<int (int )>().target<bar>() );
    BOOST_ASSERT( f1.get<int (int )>().target<bar>()->calls == 4 );
#endif
    BOOST_ASSERT( foo.calls == 4 );

}

} // end namespace ns_func_object_with_state_test

using ns_func_object_with_state_test::func_object_with_state_test;

#endif // TEST_FUNCTION_OBJECT_WITH_STATE_

