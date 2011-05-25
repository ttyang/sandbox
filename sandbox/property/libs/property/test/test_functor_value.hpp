#if !defined(TEST_FUNCTOR_VALUE_HPP)
#define TEST_FUNCTOR_VALUE_HPP

#include "test_enum.hpp"
#include "test_pod.hpp"
#include "test_functor_impl.hpp"
#include <boost/property/property_functor_value.hpp>

using namespace properties;

extern prop_functor<char,p_functor_class_char> p_gl_char;
extern prop_functor<int,p_functor_class_int> p_gl_int;
extern prop_functor<double,p_functor_class_double> p_gl_double;
extern prop_functor<bool,p_functor_class_bool,write_tag> p_gl_bool_write;
extern prop_functor<int *,p_functor_class_pointer> p_gl_pointer;
extern prop_functor<test_enum,p_functor_class_enum,read_tag> p_gl_enum_const;
extern prop_functor<test_pod const,p_functor_class_pod> p_gl_pod_const;

extern p_functor_class_char pf_gl_char;
extern p_functor_class_int pf_gl_int;
extern p_functor_class_double pf_gl_double;
extern p_functor_class_bool pf_gl_bool;
extern p_functor_class_pointer pf_gl_pointer;
extern p_functor_class_enum pf_gl_enum;
extern p_functor_class_pod pf_gl_pod;
  
class p_functor_value_class
  {
  
  public:
  
  p_functor_value_class();
  
  prop_functor<char,p_functor_class_char> p_char;
  prop_functor<int,p_functor_class_int> p_int;
  prop_functor<double const,p_functor_class_double> p_double_const;
  prop_functor<bool const,p_functor_class_bool> p_bool_const;
  prop_functor<int *,p_functor_class_pointer,read_tag> p_pointer_const;
  prop_functor<test_enum,p_functor_class_enum> p_enum;
  prop_functor<test_pod,p_functor_class_pod,read_tag> p_pod_const;

  static prop_functor<char,p_functor_class_char> p_st_char;
  static prop_functor<int,p_functor_class_int,read_tag> p_st_int_const;
  static prop_functor<double,p_functor_class_double> p_st_double;
  static prop_functor<bool,p_functor_class_bool> p_st_bool;
  static prop_functor<int *,p_functor_class_pointer> p_st_pointer;
  static prop_functor<test_enum,p_functor_class_enum,read_tag> p_st_enum_const;
  static prop_functor<test_pod,p_functor_class_pod,write_tag> p_st_pod_write;
  
  private:
  
  p_functor_class_char pf_char;
  p_functor_class_int pf_int;
  p_functor_class_double pf_double;
  p_functor_class_bool pf_bool;
  p_functor_class_pointer pf_pointer;
  p_functor_class_enum pf_enum;
  p_functor_class_pod pf_pod;
  
  static p_functor_class_char pf_st_char;
  static p_functor_class_int pf_st_int;
  static p_functor_class_double pf_st_double;
  static p_functor_class_bool pf_st_bool;
  static p_functor_class_pointer pf_st_pointer;
  static p_functor_class_enum pf_st_enum;
  static p_functor_class_pod pf_st_pod;
  
  static int pvalue;
  
  };
  
#endif