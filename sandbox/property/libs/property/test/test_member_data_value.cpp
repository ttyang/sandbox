#include <boost/test/unit_test.hpp>
#include "test_member_data_value.hpp"
#include "test_global_data.hpp"

int p_member_data_value_class::p_st_iarray[9] = {757,9,5347,369,1174,53,3456,443,6};
int p_gl_iarray[] = {7,98,347,289,14,5763,230,7783,22675,59,12};

prop_member_data<char const,p_member_data_class,&p_member_data_class::p_data_char> p_gl_char_const(pmd_gl_char);
prop_member_data<int,p_member_data_class,&p_member_data_class::p_data_int> p_gl_int(pmd_gl_int);
prop_member_data<double const,p_member_data_class,&p_member_data_class::p_double_2> p_gl_double_const(pmd_gl_double);
prop_member_data<bool,p_member_data_class,&p_member_data_class::p_bool,default_policy_tag,read_tag> p_gl_bool(pmd_gl_bool);
prop_member_data<int *,p_member_data_class,&p_member_data_class::p_data_pointer,notification_boost_function> p_gl_pointer_ntf(pmd_gl_pointer);
prop_member_data<test_enum,p_member_data_class,&p_member_data_class::p_data_enum> p_gl_enum(pmd_gl_enum);
prop_member_data<test_pod,p_member_data_class,&p_member_data_class::p_data_pod,notification_boost_function> p_gl_pod_ntf(pmd_gl_pod);

p_member_data_value_class::p_member_data_value_class() :
  p_char(pmd_char),
  p_int(pmd_int),
  p_double_ntf(pmd_double,15),
  p_bool(pmd_bool,true),
  p_pointer(pmd_pointer,&p_iarray[3]),
  p_enum_ntf(pmd_enum,e_test_second),
  p_pod_const(pmd_pod)
  {
  p_iarray[0] = 56;
  p_iarray[1] = 13562;
  p_iarray[2] = 679;
  p_iarray[3] = 34;
  p_iarray[4] = 2491;
  p_iarray[5] = 856;
  p_iarray[6] = 37;
  p_iarray[7] = 932;
  p_iarray[8] = 8468;
  p_iarray[9] = 834;
  p_iarray[10] = 789;
  p_iarray[11] = 3452;
  p_iarray[12] = 741;
  p_iarray[13] = 3492;
  p_iarray[14] = 48;
  
  pmd_pod.p_pod_2 = test_pod('#',997,23.6744,false);
  
  }

prop_member_data<char,p_member_data_class,&p_member_data_class::p_char> p_member_data_value_class::p_st_char(pmd_st_char);
prop_member_data<int,p_member_data_class,&p_member_data_class::p_int> p_member_data_value_class::p_st_int(pmd_st_int);
prop_member_data<double const,p_member_data_class,&p_member_data_class::p_data_double> p_member_data_value_class::p_st_double_const(pmd_st_double);
prop_member_data<bool,p_member_data_class,&p_member_data_class::p_data_bool> p_member_data_value_class::p_st_bool(pmd_st_bool);
prop_member_data<int *,p_member_data_class,&p_member_data_class::p_pointer_2> p_member_data_value_class::p_st_pointer(pmd_st_pointer);
prop_member_data<test_enum,p_member_data_class,&p_member_data_class::p_enum,default_policy_tag,read_tag> p_member_data_value_class::p_st_enum_const(pmd_st_enum);
prop_member_data<test_pod,p_member_data_class,&p_member_data_class::p_pod> p_member_data_value_class::p_st_pod(pmd_st_pod);

bool TestCharacterNotificationWorked(false);

void TestCharacterNotification(const i_property_write<char> &,boost::optional<char>,char cnew)
  {
  BOOST_CHECK_EQUAL(cnew,'i');
  TestCharacterNotificationWorked = true;
  }

bool TestBoolNotificationWorked(false);

void TestBoolNotification(const i_property_write<bool> &,boost::optional<bool>,bool cnew)
  {
  BOOST_CHECK(cnew);
  TestBoolNotificationWorked = true;
  }

bool TestPointerNotificationWorked(false);

void TestPointerNotification(const i_property_write<int *> &,boost::optional<int *>,int *)
  {
  TestPointerNotificationWorked = true;
  }

bool TestEnumNotificationWorked(false);

void TestEnumNotification(const i_property_write<test_enum> &,boost::optional<test_enum>,test_enum cnew)
  {
  BOOST_CHECK_EQUAL(cnew,e_test_third);
  TestEnumNotificationWorked = true;
  }

bool TestPodNotificationWorked(false);

void TestPodNotification(const i_property_write<test_pod> &,boost::optional<test_pod>,test_pod cnew)
  {
  BOOST_CHECK_EQUAL(cnew.an_int,547);
  TestPodNotificationWorked = true;
  }

bool TestIntegerNotificationWorked(false);

void TestIntegerNotification(const i_property_write<int> &,boost::optional<int>,int cnew)
  {
  BOOST_CHECK_EQUAL(cnew,23611);
  TestIntegerNotificationWorked = true;
  }

bool TestDoubleNotificationWorked(false);

void TestDoubleNotification(const i_property_write<double> &,boost::optional<double>,double cnew)
  {
  BOOST_CHECK_CLOSE(cnew,566655.298,.0001);
  TestDoubleNotificationWorked = true;
  }

#include <string>

void TestCharacter(p_member_data_value_class & tcl) 
  {
  
  /*
  
  Although a character is considered an integral type, 
  doing integral arithmetic on it is really not normal.
  So we show functionality based on characters being part
  of C++ strings.
  
  */
  
  prop_member_data
    <
    char,
    p_member_data_class,
    &p_member_data_class::p_char_2,
    notification_boost_function
    > 
  p_loc_char_ntf(tcl.pmd_char,'J');
  
  std::string s1("Terry");
  
  s1[0] = p_loc_char_ntf;
  
  BOOST_CHECK_EQUAL(s1,"Jerry");
  
  pmd_gl_char.p_data_char = 'k';
  
  s1[3] = p_gl_char_const;
  
  BOOST_CHECK_EQUAL(s1,"Jerky");
  
  p_loc_char_ntf = s1[1];
  tcl.p_char = 's';
  p_member_data_value_class::p_st_char = 'o';
  
  s1[1] = p_member_data_value_class::p_st_char;
  s1[2] = p_gl_char_const;
  s1[3] = p_loc_char_ntf;
  s1[4] = tcl.p_char;
  
  BOOST_CHECK_EQUAL(s1,"Jokes");
  
  std::string s2(1,tcl.p_char);
  
  BOOST_CHECK_EQUAL(s2,"s");
  
  s2 += p_member_data_value_class::p_st_char;
  
  BOOST_CHECK_EQUAL(s2,"so");
  
  p_loc_char_ntf.fun = &TestCharacterNotification;
  p_loc_char_ntf = 'i';
  
  BOOST_CHECK(TestCharacterNotificationWorked);
  
  }
  
void TestInt(p_member_data_value_class & tcl) 
  {
  
  /*
  
  Integers can be tested with the full range of integer operations.
  
  */
  
  prop_member_data
    <
    int,
    p_member_data_class,
    &p_member_data_class::p_data_int,
    notification_boost_function
    > 
  p_loc_int(tcl.pmd_int,563);
  
  p_gl_int = 34662;
  
  BOOST_CHECK_EQUAL(p_gl_int,34662);
  
  p_member_data_value_class::p_st_int = 34;
  
  BOOST_CHECK_EQUAL(p_member_data_value_class::p_st_int,34);
  tcl.p_int = 44;
  tcl.p_int += 12;
  BOOST_CHECK_EQUAL(tcl.p_int,56);
  tcl.p_int -= 16;
  BOOST_CHECK_EQUAL(tcl.p_int,40);
  ++tcl.p_int;
  BOOST_CHECK_EQUAL(tcl.p_int,41);
  ++tcl.p_int;
  ++tcl.p_int;
  --tcl.p_int;
  BOOST_CHECK_EQUAL(tcl.p_int,42);
  tcl.p_int /= 3;
  BOOST_CHECK_EQUAL(tcl.p_int,14);
  tcl.p_int *= 5;
  BOOST_CHECK_EQUAL(tcl.p_int,70);
  
  int il1(p_loc_int++);
  BOOST_CHECK_EQUAL(il1,563);
  BOOST_CHECK_EQUAL(p_loc_int,564);
  p_loc_int >>= 2;
  BOOST_CHECK_EQUAL(p_loc_int,141);
  p_loc_int -= 81;
  p_loc_int <<= 3;
  BOOST_CHECK_EQUAL(p_loc_int,480);
  il1 = --p_loc_int;
  BOOST_CHECK_EQUAL(il1,479);
  p_loc_int -= 6;
  BOOST_CHECK_EQUAL(p_loc_int,473);
  p_loc_int |= 0x0da;
  BOOST_CHECK_EQUAL(p_loc_int,475);
  p_loc_int &= 0x076;
  BOOST_CHECK_EQUAL(p_loc_int,82);
  p_loc_int.fun = &TestIntegerNotification;
  p_loc_int = 23611;
  BOOST_CHECK(TestIntegerNotificationWorked);
  
  tcl.p_int ^= 57;
  
  }
  
void TestDouble(p_member_data_value_class & tcl) 
  {
  
  /*
  
  We can do the full range of arithmetic functionality with a double value
  
  */
  
  prop_member_data
    <
    double,
    p_member_data_class,
    &p_member_data_class::p_double_2
    > 
  p_loc_double(tcl.pmd_double,45.37);
    
  ++p_loc_double;
  BOOST_CHECK_CLOSE(p_loc_double.get(),46.37,.1);
  BOOST_CHECK_CLOSE(tcl.p_double_ntf.get(),15.0,.1);
  pmd_gl_double.p_double_2 = 2352.346;
  p_member_data_value_class::pmd_st_double.p_data_double = 452.98;
  BOOST_CHECK_CLOSE(p_gl_double_const.get(),2352.346,.01);
  BOOST_CHECK_CLOSE(p_member_data_value_class::p_st_double_const.get(),452.98,.1);
  double d1 = tcl.p_double_ntf++;
  BOOST_CHECK_CLOSE(d1,15.0,.1);
  BOOST_CHECK_CLOSE(tcl.p_double_ntf.get(),16.0,.1);
  p_loc_double *= 756.839;
  BOOST_CHECK_CLOSE(p_loc_double.get(),35094.624,.001);
  tcl.p_double_ntf.fun = &TestDoubleNotification;
  tcl.p_double_ntf += 566639.298;
  BOOST_CHECK(TestDoubleNotificationWorked);
  
  }
  
void TestBool(p_member_data_value_class & tcl) 
  {
  
  /*
  
  Bools are integral values, 
  either 0 (false) or 1 (true) in integer arithmetic,
  but are only tested here for true or false
  
  */
  
  prop_member_data
    <
    bool,
    p_member_data_class,
    &p_member_data_class::p_bool_2,
    notification_boost_function
    > 
  p_loc_bool_ntf(pmd_gl_bool,true);
  
  bool b1(tcl.p_bool);
  
  BOOST_CHECK(b1);
  
  bool b2(p_loc_bool_ntf);
  
  BOOST_CHECK(b2);
  
  b1 = p_gl_bool;
  
  BOOST_CHECK_EQUAL(b1,false);
  
  p_loc_bool_ntf.fun = &TestBoolNotification;
  p_loc_bool_ntf = b2;
  
  BOOST_CHECK(TestBoolNotificationWorked);
  
  p_member_data_value_class::p_st_bool = true;
  
  bool b3(p_member_data_value_class::p_st_bool);
  
  BOOST_CHECK(b3);
  
  }
  
void TestPointer(p_member_data_value_class & tcl) 
  {
  
  /*
  
  Pointers can be assigned, incremented, decremented,
  and take part in simple arithmetic.
  
  */
  
  prop_member_data
    <
    int *,
    p_member_data_class,
    &p_member_data_class::p_pointer,
    notification_boost_function
    > 
  p_loc_pointer(pmd_gl_pointer,&p_gl_iarray[7]);
  
  prop_member_data
    <
    int *,
    p_member_data_class,
    &p_member_data_class::p_pointer_2
    > 
  p_loc_pointer2(pmd_gl_pointer,&p_gl_iarray[4]);
  
  BOOST_CHECK_EQUAL(*p_loc_pointer,7783);
  
  p_loc_pointer = &p_gl_iarray[6];
  
  BOOST_CHECK_EQUAL(*p_loc_pointer,230);
  BOOST_CHECK_EQUAL(p_loc_pointer - p_loc_pointer2,2);
  
  p_loc_pointer += 4;
  BOOST_CHECK_EQUAL(*p_loc_pointer,12);
  p_loc_pointer.fun = &TestPointerNotification;
  p_loc_pointer -= 2;
  BOOST_CHECK_EQUAL(*p_loc_pointer,22675);
  BOOST_CHECK(TestPointerNotificationWorked);
  
  p_gl_pointer_ntf = &gld_int;
  
  *p_gl_pointer_ntf = 489;
  BOOST_CHECK_EQUAL(*p_gl_pointer_ntf,489);
  
  p_member_data_value_class::p_st_pointer = &p_member_data_value_class::p_st_iarray[5];
  
  BOOST_CHECK_EQUAL(*p_member_data_value_class::p_st_pointer,53);
  ++p_member_data_value_class::p_st_pointer;
  BOOST_CHECK_EQUAL(*p_member_data_value_class::p_st_pointer,3456);
  BOOST_CHECK_EQUAL(*tcl.p_pointer,34);
  tcl.p_pointer -= 2;
  BOOST_CHECK_EQUAL(*tcl.p_pointer,13562);
  --tcl.p_pointer;
  BOOST_CHECK_EQUAL(*tcl.p_pointer,56);
  tcl.p_pointer += 11;
  BOOST_CHECK_EQUAL(*(tcl.p_pointer--),3452);
  BOOST_CHECK_EQUAL(*tcl.p_pointer,789);
  p_member_data_value_class::p_st_pointer -= 4;
  BOOST_CHECK_EQUAL(*(p_member_data_value_class::p_st_pointer++),5347);
  BOOST_CHECK_EQUAL(*p_member_data_value_class::p_st_pointer,369);
  
  }
  
void TestEnum(p_member_data_value_class & tcl) 
  {
  
  /*
  
  Enums are individual values. They can participate in 
  arithmetic expressions but here I will just test basic 
  usage.
  
  */
  
  p_member_data_value_class::pmd_st_enum.p_enum = e_test_third;
  
  prop_member_data
    <
    test_enum,
    p_member_data_class,
    &p_member_data_class::p_enum_2
    > 
  p_loc_enum(p_member_data_value_class::pmd_st_enum,e_test_second);
  
  BOOST_CHECK_EQUAL(tcl.p_enum_ntf,e_test_second);
  BOOST_CHECK_EQUAL(p_loc_enum,e_test_second);
  p_loc_enum = e_test_third;
  BOOST_CHECK_EQUAL(p_loc_enum,e_test_third);
  BOOST_CHECK_EQUAL(p_member_data_value_class::p_st_enum_const,e_test_third);
  
  test_enum te1(p_loc_enum);
  
  BOOST_CHECK_EQUAL(te1,e_test_third);
  
  te1 = p_member_data_value_class::p_st_enum_const;
  BOOST_CHECK_EQUAL(te1,e_test_third);
  tcl.p_enum_ntf.fun = &TestEnumNotification;
  tcl.p_enum_ntf = e_test_third;
  BOOST_CHECK(TestEnumNotificationWorked);
  
  }
  
void TestPod(p_member_data_value_class & tcl) 
  {
  
  /*
  
  Our POD class will be tested by changing fields 
  and passing to and from the properties.
  
  */
  
  prop_member_data<test_pod,p_member_data_class,&p_member_data_class::p_pod> p_loc_pod(tcl.pmd_pod,test_pod('^',981,4.3,false));
  
  BOOST_CHECK_EQUAL(p_loc_pod.get().an_int,981);
  BOOST_CHECK_EQUAL(p_loc_pod.get().a_char,'^');
  
  p_member_data_value_class::p_st_pod = test_pod('y',45,32.6,true);
  
  test_pod p1(p_member_data_value_class::p_st_pod);
  
  BOOST_CHECK_EQUAL(p1.a_char,'y');
  BOOST_CHECK(p1.a_bool);
  BOOST_CHECK_EQUAL(p_member_data_value_class::p_st_pod.get().an_int,45);
  BOOST_CHECK_CLOSE(p_member_data_value_class::p_st_pod.get().a_double,32.6,.1);
  
  p1 = p_loc_pod;
  p1.an_int = 991;
  p_loc_pod = p1;
  BOOST_CHECK_EQUAL(p_loc_pod.get().an_int,991);
  
  BOOST_CHECK_EQUAL(tcl.p_pod_const.get().an_int,997);
  BOOST_CHECK_EQUAL(tcl.p_pod_const.get().a_char,'#');
  
  p_member_data_value_class::p_st_pod = test_pod();
  
  BOOST_CHECK_EQUAL(p_member_data_value_class::p_st_pod.get().a_double,0);
  
  p_gl_pod_ntf.fun = &TestPodNotification;
  p_gl_pod_ntf = test_pod('$',547,33.45,true);
  BOOST_CHECK(TestPodNotificationWorked);
  
  }
  
void test_member_data_value_function()
  {
  
  p_member_data_value_class tcl;
  
  TestCharacter(tcl);
  TestInt(tcl);
  TestDouble(tcl);
  TestBool(tcl);
  TestPointer(tcl);
  TestEnum(tcl);
  TestPod(tcl);
  
  }

boost::unit_test::test_suite* init_unit_test_suite( int , char* [] )
{
    boost::unit_test::test_suite* test = BOOST_TEST_SUITE( "Property Test Member Data Value Suite" );

    test->add( BOOST_TEST_CASE( &test_member_data_value_function ) );

    return test;
}

p_member_data_class pmd_gl_char;
p_member_data_class pmd_gl_int;
p_member_data_class pmd_gl_double;
p_member_data_class pmd_gl_bool;
p_member_data_class pmd_gl_pointer;
p_member_data_class pmd_gl_enum;
p_member_data_class pmd_gl_pod;

p_member_data_class p_member_data_value_class::pmd_st_char;
p_member_data_class p_member_data_value_class::pmd_st_int;
p_member_data_class p_member_data_value_class::pmd_st_double;
p_member_data_class p_member_data_value_class::pmd_st_bool;
p_member_data_class p_member_data_value_class::pmd_st_pointer;
p_member_data_class p_member_data_value_class::pmd_st_enum;
p_member_data_class p_member_data_value_class::pmd_st_pod;
  
#include "test_global_data.cpp"
#include "test_member_data_impl.cpp"
