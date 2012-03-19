/*=============================================================
    Boost Overload
    Example - Boost.ResultOf support
==============================================================*/


#include <boost/detail/lightweight_test.hpp>
//[ result_of_support_cpp
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/overload.hpp>

using boost::is_same;

struct A {};
struct B : public A {};


typedef boost::overload<int (int ), char (char ), double (double ), A (const A& )>
        overload_type;


BOOST_STATIC_ASSERT((
        is_same<
            boost::result_of< overload_type (int ) >::type,
            int
        >::value
));

BOOST_STATIC_ASSERT((
        is_same<
            boost::result_of< overload_type (char ) >::type,
            char
        >::value
));

BOOST_STATIC_ASSERT((
        is_same<
            boost::result_of< overload_type (double ) >::type,
            double
        >::value
));

BOOST_STATIC_ASSERT((
        is_same<
            boost::result_of< overload_type (short int ) >::type,
            int
        >::value
));

BOOST_STATIC_ASSERT((
        is_same<
            boost::result_of< overload_type (char& ) >::type,
            char
        >::value
));

BOOST_STATIC_ASSERT((
        is_same<
            boost::result_of< overload_type (const float& ) >::type,
            double
        >::value
));

BOOST_STATIC_ASSERT((
        is_same<
            boost::result_of< overload_type (B ) >::type,
            A
        >::value
));

BOOST_STATIC_ASSERT((
        is_same<
            boost::result_of< overload_type (B& ) >::type,
            A
        >::value
));
//]

int main()
{
    return boost::report_errors();
}


