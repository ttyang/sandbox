
#ifndef _TEST_CONTAINS_HPP_
#define _TEST_CONTAINS_HPP_

namespace contain_test {

// this part is recycled from the boost function test code

struct ReturnIntFE
{
  explicit ReturnIntFE(int value) : value(value) {}

  int operator()() const { return value; }

  int value;
};

}

#ifndef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP

namespace contain_test {
# ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
bool function_equal(const ReturnIntFE& x, const ReturnIntFE& y)
{ return x.value == y.value; }
# else
bool function_equal_impl(const ReturnIntFE& x, const ReturnIntFE& y, int)
{ return x.value == y.value; }
# endif // #ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
}
#else // BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
namespace boost {
# ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
bool
function_equal(const contain_test::ReturnIntFE& x,
               const contain_test::ReturnIntFE& y)
{ return x.value == y.value; }
# else
bool
function_equal_impl(const contain_test::ReturnIntFE& x,
                    const contain_test::ReturnIntFE& y, int)
{ return x.value == y.value; }
# endif
}
#endif


void contains_test()
{
    using namespace contain_test;
    boost::overload<sig0_t, sig1_t, int (), sig2_t> f;

    // f0_t function pointer
    // f1_t member function pointer
    // f2_t member function pointer (with const)

    ReturnIntFE this_return_ten(10);

    f.set( &foo0, &bar1::foo1, this_return_ten, &bar2::foo2 );

    BOOST_ASSERT( f.get<0>().target<f0_t>() );
    BOOST_ASSERT( *(f.get<0>().target<f0_t>()) == &foo0 );
    BOOST_ASSERT( f.get<1>().target<f1_t>() );
    BOOST_ASSERT( *(f.get<1>().target<f1_t>()) == &bar1::foo1 );
    BOOST_ASSERT( f.get<3>().target<f2_t>() );
    BOOST_ASSERT( *(f.get<3>().target<f2_t>()) == &bar2::foo2 );
    BOOST_ASSERT( f.get<2>().target<ReturnIntFE>() );
    BOOST_ASSERT( function_equal( *(f.get<2>().target<ReturnIntFE>()), this_return_ten ) );

    BOOST_ASSERT( f.get<0>().contains( &foo0 ) );
    BOOST_ASSERT( f.get<1>().contains( &bar1::foo1 ) );
    BOOST_ASSERT( f.get<2>().contains( this_return_ten ) );
    BOOST_ASSERT( f.get<3>().contains( &bar2::foo2 ) );

    BOOST_ASSERT( f.contains( &foo0 ) );
    BOOST_ASSERT( f.contains( &bar1::foo1 ) );
    BOOST_ASSERT( f.contains( this_return_ten ) );
    BOOST_ASSERT( f.contains( &bar2::foo2 ) );

}


#endif /* _TEST_CONTAINS_HPP_ */
