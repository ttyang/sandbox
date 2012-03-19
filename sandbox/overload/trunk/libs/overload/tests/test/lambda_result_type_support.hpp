
#ifndef _TEST_LAMBDA_RESULT_TYPE_SUPPORT_HPP_
#define _TEST_LAMBDA_RESULT_TYPE_SUPPORT_HPP_

#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>


void lambda_support_test()
{
    using namespace boost::lambda;

    typedef boost::overload<sig0_t, sig1_t, sig2_t, sig3_t, sig4_t, sig5_t>
            overload_type;


    f0_t f0 = &foo0;                // function pointer
    f1_t f1 = &bar1::foo1;          // member function pointer
    f2_t f2 = &bar2::foo2;          // member function pointer (with const)
    f3_t f3 = &foo3;                // boost::function
    f3_t f3b = &foo3b;              // same signature (swap test)
    f4_t f4;                        // function object
    f5_t f5;                        // function object (with const)

    bar1 b1; bar2 b2;

    overload_type f( f0, f1, f2, f3, f4, f5 );

    // do not work with the following compilers
    // no Boost.Lambda support for the sig struct ?
#if !( BOOST_WORKAROUND(__INTEL_COMPILER, < 1210) || BOOST_WORKAROUND(BOOST_MSVC, < 1400) )

    std::string hello("hello");
    BOOST_ASSERT( boost::lambda::bind(f, hello, hello, _1)(hello) == f(hello, hello, hello) );
    BOOST_ASSERT( boost::lambda::bind(f, &b1, _1)('x') == f(&b1, 'x') );
    BOOST_ASSERT( boost::lambda::bind(f, static_cast<const bar2*>(&b2), _1, _2)(1, 'x') == f(&b2, 1, 'x') );
    BOOST_ASSERT( boost::lambda::bind(f, hello)() == f(hello) );
    BOOST_ASSERT( boost::lambda::bind(f, _1)(hello) == f(hello) );
    BOOST_ASSERT( boost::lambda::bind(f, _1)('x') == f('x') );
    BOOST_ASSERT( boost::lambda::bind(f, _1, 'x')(1) == f(1, 'x') );

#endif
    //boost::lambda::bind(f, &b1, _1)('x');

}



#endif // _TEST_LAMBDA_RESULT_TYPE_SUPPORT_HPP_
