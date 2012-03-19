/*=============================================================
    Boost Overload
    Example 11 - Boost.Overload type traits
==============================================================*/

//[ type_traits_cpp

#include <boost/detail/lightweight_test.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/overload.hpp>

using namespace boost::overloads;
using boost::is_same;


int foo(long ) { return 1; }
typedef int (*foo_ptr)(long );

struct bar
{
    int operator()(double ) { return -1; }
};


typedef boost::overload<int (int ), int (char ), int (double )>
        overload_type;


BOOST_STATIC_ASSERT(( extent<overload_type>::value == 3 ));

BOOST_STATIC_ASSERT((
        is_same<
            signature<overload_type, 0>::type,
            int (int )
        >::value
));

BOOST_STATIC_ASSERT((
        is_same<
            function<overload_type, 1>::type,
            boost::function<int (char )>
        >::value
));

BOOST_STATIC_ASSERT(( boost::overloads::index_of_signature<overload_type, int (double )>::value == 2 ));

BOOST_STATIC_ASSERT(( boost::overloads::index_of_signature<overload_type, int (float )>::value == -1 ));

BOOST_STATIC_ASSERT(( has_signature<overload_type, int( char)>::value ));

BOOST_STATIC_ASSERT(( !has_signature<overload_type, int( long)>::value ));

BOOST_STATIC_ASSERT(( have_any_shared_signature<overload_type, bar>::value ));

BOOST_STATIC_ASSERT(( !have_any_shared_signature<overload_type, foo_ptr>::value ));



typedef boost::function<int(double)> function_type;


BOOST_STATIC_ASSERT(( extent<function_type>::value == 1 ));

BOOST_STATIC_ASSERT((
        is_same<
            signature<function_type>::type,
            int (double )
        >::value
));

BOOST_STATIC_ASSERT(( has_signature<function_type, int (double )>::value ));
BOOST_STATIC_ASSERT(( !has_signature<function_type, int (char )>::value ));

BOOST_STATIC_ASSERT(( have_any_shared_signature<function_type, bar>::value ));
BOOST_STATIC_ASSERT(( !have_any_shared_signature<function_type, foo_ptr>::value ));
//]


int main()
{
    return boost::report_errors();
}

