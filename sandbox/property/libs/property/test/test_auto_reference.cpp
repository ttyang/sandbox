#include <boost/test/unit_test.hpp>
#include <boost/property/property_auto_reference.hpp>

void test_auto_reference_function()
  {
  
  }

boost::unit_test::test_suite* init_unit_test_suite( int , char* [] )
{
    boost::unit_test::test_suite* test = BOOST_TEST_SUITE( "Property Test Auto Reference Suite" );

    test->add( BOOST_TEST_CASE( &test_auto_reference_function ) );

    return test;
}
