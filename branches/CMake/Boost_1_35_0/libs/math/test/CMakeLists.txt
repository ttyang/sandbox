boost_test_run(common_factor_test DEPENDS boost_unit_test_framework)
boost_test_run(octonion_test 
  ../octonion/octonion_test.cpp
  DEPENDS boost_unit_test_framework)
boost_test_run(quaternion_test 
  ../quaternion/quaternion_test.cpp
  DEPENDS boost_unit_test_framework)
boost_test_run(special_functions_test 
  ../special_functions/special_functions_test.cpp 
  DEPENDS boost_unit_test_framework)
boost_test_run(quaternion_multi_incl_test 
  ../quaternion/quaternion_mult_incl_test.cpp 
                 ../quaternion/quaternion_mi1.cpp
                 ../quaternion/quaternion_mi2.cpp
  DEPENDS boost_unit_test_framework)
boost_test_run(complex_test)
boost_test_run(hypot_test)
boost_test_run(log1p_expm1_test DEPENDS boost_regex)
