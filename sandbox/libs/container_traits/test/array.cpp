#include <boost/container_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/test/unit_test.hpp>

using namespace boost;
using boost::unit_test_framework::test_suite;

void check_array()
{
    typedef int   array_t[9];
    int           my_array[9]  = { 1,2,3,4,5,6,7,8,9 };
    BOOST_STATIC_ASSERT(( sizeof( sizer( my_array ) ) == 9 ));
    BOOST_STATIC_ASSERT(( is_same< container_traits<array_t>::value_type, int >::value ));
    BOOST_STATIC_ASSERT(( is_same< container_traits<array_t>::iterator, int* >::value ));
    BOOST_STATIC_ASSERT(( is_same< container_traits<array_t>::const_iterator, const int* >::value ));
    BOOST_STATIC_ASSERT(( is_same< container_traits<array_t>::difference_type, std::ptrdiff_t >::value ));
    BOOST_STATIC_ASSERT(( is_same< container_traits<array_t>::size_type, std::size_t >::value ));
    BOOST_STATIC_ASSERT(( is_same< container_traits<array_t>::result_iterator, int* >::value ));
    BOOST_STATIC_ASSERT(( is_same< container_traits<const array_t>::result_iterator, const int* >::value ));
    
    BOOST_CHECK( begin( my_array ) == my_array );
    BOOST_CHECK( end( my_array )   == my_array + size( my_array ) );
    BOOST_CHECK( empty( my_array ) == false );
    BOOST_CHECK( size( my_array ) == sizeof( sizer( my_array ) ) );
}

test_suite* init_unit_test_suite( int, char* [] )
{
    test_suite* test = BOOST_TEST_SUITE( "container_traits<Array>" );
    test->add( BOOST_TEST_CASE( &check_array ), 0 );

    return test;
}

