#if !defined(TEST_DATA_VALUE_HPP)
#define TEST_DATA_VALUE_HPP

#include "test_enum.hpp"
#include "test_pod.hpp"
#include "test_global_data.hpp"
#include "test_data.hpp"
#include <boost/property/property_data_value.hpp>
#include <boost/property/property_notification_boost_function.hpp>

using namespace properties;

extern prop_data<char const,&p_data_class::p_char_2> p_gl_char_const;
extern prop_data<int,&p_data_int> p_gl_int;
extern prop_data<double const,&p_data_double> p_gl_double_const;
extern prop_data<bool,&p_data_class::p_bool,default_policy_tag,read_tag> p_gl_bool;
extern prop_data<int *,&p_data_pointer,notification_boost_function> p_gl_pointer_ntf;
extern prop_data<test_enum,&p_data_class::p_enum_2,notification_boost_function> p_gl_enum_ntf;
extern prop_data<test_pod,&p_data_class,notification_boost_function> p_gl_class_ntf;

class p_data_value_class
  {
  
  public:
  
  p_data_value_class();
  
  prop_data<char,&p_data_char> p_char;
  prop_data<int,&p_data_class::p_int_2> p_int;
  prop_data<double,&p_data_class::p_double,notification_boost_function> p_double_ntf;
  prop_data<bool,&p_data_class::p_bool_2> p_bool;
  prop_data<int *,&p_data_class::p_pointer> p_pointer;
  prop_data<test_enum,&p_data_class::p_enum,default_policy_tag,read_tag> p_enum_const;
  prop_data<test_pod,&p_data_class::p_class> p_class;
  
  static prop_data<char,&p_data_class::p_char> p_st_char;
  static prop_data<int,&p_data_class::p_int> p_st_int;
  static prop_data<double const,&p_data_class::p_double_2> p_st_double_const;
  static prop_data<bool,&p_data_bool> p_st_bool;
  static prop_data<int *,&p_data_class::p_pointer_2> p_st_pointer;
  static prop_data<test_enum,&p_data_enum> p_st_enum;
  static prop_data<test_pod const,&p_data_class::p_class_2> p_st_class_const;
  
  private:
  
  static int st_some_int;
  static int st_some_int_2;
  
  };
  
#endif