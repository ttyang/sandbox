/*-----------------------------------------------------------------------------+    
A Law Based Test Automaton 'LaBatea'
Author: Joachim Faulhaber
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#include <boost/config/warning_disable.hpp>
#include <iostream>
#include <stdio.h>
#include <boost/validate/driver/map_copy_conformity_driver.hpp>

using namespace std;
using namespace boost;
using namespace boost::icl;

void test_Validater()
{
    map_copy_conformity_driver validater;
    cout << 
    ">> ------------------------------------------------------ <<\n"
    ">> -------- Law based test automaton 'LaBatea' ---------- <<\n"
    ">> Output will be generated in a few seconds\n"
    ">> terminate by typing <CTRL>C\n"
    ">> ------------------------------------------------------ <<\n";
    GentorProfileSgl::it()->set_std_profile(8,1);//JODO
    GentorProfileSgl::it()->report_profile();
    validater.validate();
};


int main()
{
    test_Validater();
    return 0;
}