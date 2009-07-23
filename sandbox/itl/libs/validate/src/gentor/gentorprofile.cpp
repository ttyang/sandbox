/*-----------------------------------------------------------------------------+    
Interval Template Library
Author: Joachim Faulhaber
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#include <boost/validate/gentor/gentorprofile.hpp>

using namespace boost::itl;

GentorProfileSgl* GentorProfileSgl::s_instance = NULL;

GentorProfileSgl* GentorProfileSgl::it()
{
    if(s_instance==NULL) {
        s_instance = new GentorProfileSgl;
    }
    return s_instance;
}

GentorProfileSgl::GentorProfileSgl(){}


void GentorProfile::set_defaults()
{
#ifdef _DEBUG
	set_debug_defaults();
#else
	set_release_defaults();
#endif
}

void GentorProfile::set_debug_defaults()
{
	set_range_int(-5, 5);
	set_range_nat(0, 16);
	set_range_double(0.0, 1.0);
	set_range_ContainerSize(0,4);

	set_range_interval_int(-5, 5);
	set_range_interval_double(-5.0, 5.0);
	set_maxIntervalLength(5);

	set_range_element_ContainerSize(0,4);

	set_repeat_count(1);
	set_trials_count(20);
	set_laws_per_cycle(100);
}

void GentorProfile::set_release_defaults()
{
	set_range_int(-5, 5);
	set_range_nat(0, 16);
	set_range_double(0.0, 1.0);
	set_range_ContainerSize(0,20);

	set_range_interval_int(-20, 20);
	set_range_interval_double(-20.0, 20.0);
	set_maxIntervalLength(10);

	set_range_element_ContainerSize(0,20);

	set_repeat_count(1);
	set_trials_count(20);
	set_laws_per_cycle(100);
}




GentorProfile::GentorProfile()
{
	set_defaults();
    //---------------------------------
    //standard values
    //set_range_int(-10, 10);
    //set_range_nat(0, 20);
    //set_range_double(0.0, 1.0);
    //set_range_ContainerSize(0,10);

    //set_range_interval_int(-10, 10);
    //set_maxIntervalLength(8);

    //set_range_element_ContainerSize(0,5);

    //---------------------------------
    //small values
    //set_range_int(-5, 5);
    //set_range_nat(0, 16);
    //set_range_double(0.0, 1.0);
    //set_range_ContainerSize(0,4);

    //set_range_interval_int(-5, 5);
    //set_maxIntervalLength(5);
    //set_range_element_ContainerSize(0,4);

    //---------------------------------
    //current values
    set_range_int(-5, 5);
    set_range_nat(0, 16);
    set_range_double(0.0, 1.0);
    set_range_ContainerSize(0,20);

    set_range_interval_int(-20, 20);
    set_range_interval_double(-20.0, 20.0);
    set_maxIntervalLength(10);

    set_range_element_ContainerSize(0,20);
	set_repeat_count(1);
	set_trials_count(20);
	set_laws_per_cycle(100);

	//set_debug_defaults();

    //--------------------------------------------------------------------------
    // values for novial_tree test
    //set_range_int(-5, 5);
    //set_range_nat(0, 16);
    //set_range_double(0.0, 1.0);
    //set_range_ContainerSize(0,1000);

    //set_range_interval_int(0, 100000);
    //set_maxIntervalLength(1200);
    //set_range_element_ContainerSize(0,10);

    //set_range_int(-5, 5);
    //set_range_nat(0, 16);
    //set_range_double(0.0, 1.0);
    //set_range_ContainerSize(0,40);

    //set_range_interval_int(0, 1000);
    //set_maxIntervalLength(50);
    //set_range_element_ContainerSize(0,10);

}

// -------------------------------------
// (Algebra, Law, Type) -> (testsCount)
// (set, ipAddCommut, itl::set) -> 150

