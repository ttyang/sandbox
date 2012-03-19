/*=============================================================
    Boost Overload
    Example - Boost.Lambda result type support
==============================================================*/

//[ lambda_result_type_support_cpp
#include <boost/detail/lightweight_test.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

// You need to explicitly enable Boost.Lambda support
#define BOOST_OVERLOAD_ENABLE_LAMBDA_SUPPORT
#include <boost/overload.hpp>


int foo(int , std::string ) { return 1; }
int bar(int, int ) { return 2; }


int main()
{
    using namespace boost::lambda;

    boost::overload<int (int, std::string ), int (int, int )> f(&foo, &bar);

    std::string hello("hello");
    BOOST_ASSERT( boost::lambda::bind(f, 10, _1)(hello) == f(10, hello) );
    BOOST_ASSERT( boost::lambda::bind(f, 10, _1)(5) == f(10, 5) );
    BOOST_ASSERT( boost::lambda::bind(f, _1, hello)(10) == f(10, hello) );

    return boost::report_errors();
}
//]
