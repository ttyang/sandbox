
#ifndef _TEST_MAKE_OVERLOAD_HPP_
#define _TEST_MAKE_OVERLOAD_HPP_

#include <boost/overload/make_overload.hpp>

namespace make_overload_test_ns {
typedef boost::overload<sig0_t, sig1_t, sig2_t, sig3_t, sig4_t, sig5_t>
        overload_type;


BOOST_STATIC_ASSERT(( is_same<
        ovdtl::make_overload_type<f0_t, f1_t, f2_t, f3_t, f4_t, boost::reference_wrapper<f5_t> >::type,
        overload_type>::value
        ));

} // end namespace make_overload_test_ns


void make_overload_test()
{
    using make_overload_test_ns::overload_type;

    bar1 b1;
    bar2 b2;
    f3_t f3 = &foo3;                // boost::function
    f4_t f4;                        // function object
    f5_t f5;                        // function object (with const)


    overload_type f =
            boost::make_overload( &foo0, &bar1::foo1, &bar2::foo2,
                                  f3, f4, boost::ref(f5) );

    int out0    = f( "Hello",  ", ",  "world !" );
    int out1    = f(&b1, 'x');
    double out2 = f(&b2, 123, 'x');
    char out3   = f("hello");
    int out4    = f('x');
    double out5 = f(123, 'x');

    BOOST_ASSERT(out0 == 12);
    BOOST_ASSERT(out1 == 123);
    BOOST_ASSERT(out2 > 233.999 && out2 < 234.001);
    BOOST_ASSERT(out3 == 'Y');
    BOOST_ASSERT(out4 == 456);
    BOOST_ASSERT(out5 > 566.999 && out5 < 567.001);

}

#endif // _TEST_MAKE_OVERLOAD_HPP_
