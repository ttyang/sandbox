#include <boost/test/unit_test.hpp>
#include <boost/lambda/lambda.hpp>
#include "test_auto_predicate.hpp"

using namespace boost::lambda;

prop_auto_predicate<char,notification_boost_function,predicate_failure_runtime_exception> p_gl_char_pred_ntf_err(_1 != 'e');
prop_auto_predicate<int,notification_boost_function> p_gl_int_pred_ntf(_1 < 100);
prop_auto_predicate<double,default_policy_tag,predicate_failure_runtime_exception> p_gl_double_pred_err(_1 >= 1.0 && _1 <= 2.0);
prop_auto_predicate<test_enum> p_gl_enum_pred(_1 != e_test_third);

p_auto_predicate_class::p_auto_predicate_class() :
  p_char_pred_ntf_err(_1 != 'f'),
  p_int_pred(_1 >= 10000),
  p_double_pred_ntf_err(_1 >= 100.0),
  p_enum_pred_err(_1 != e_test_second)
  {
  }

prop_auto_predicate<char> p_auto_predicate_class::p_st_char_pred(_1 != 'g');
prop_auto_predicate<int,notification_boost_function,predicate_failure_runtime_exception> p_auto_predicate_class::p_st_int_pred_ntf_err(_1 >= 20000);
prop_auto_predicate<double,default_policy_tag,predicate_failure_runtime_exception> p_auto_predicate_class::p_st_double_pred_err(_1 >= 1000.0);
prop_auto_predicate<test_enum,notification_boost_function> p_auto_predicate_class::p_st_enum_pred_ntf(_1 != e_test_first);

void TestCharacter(p_auto_predicate_class & ) 
  {
  }
  
void TestInt(p_auto_predicate_class & ) 
  {
  }
  
void TestDouble(p_auto_predicate_class & ) 
  {
  }
  
void TestEnum(p_auto_predicate_class & ) 
  {
  }

void test_auto_predicate_function()
  {
  
  p_auto_predicate_class tcl;
  
  TestCharacter(tcl);
  TestInt(tcl);
  TestDouble(tcl);
  TestEnum(tcl);
  
  }

boost::unit_test::test_suite* init_unit_test_suite( int , char* [] )
{
    boost::unit_test::test_suite* test = BOOST_TEST_SUITE( "Property Test Auto Predicate Suite" );

    test->add( BOOST_TEST_CASE( &test_auto_predicate_function ) );

    return test;
}

#include "test_global_data.cpp"