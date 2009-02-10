/*----------------------------------------------------------------------------+
A Law Based Test Automaton 'LaBatea'
Author: Joachim Faulhaber
Copyright (c) 2007-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#include <iostream>
#include <stdio.h>

#include <boost/itl/ptime.hpp> //CL (4 a quick test only)

#include <boost/validate/loki_xt/Tuple.h>
#include <boost/itl/set.hpp>
#include <boost/itl/map.hpp>
#include <boost/validate/validater/law_validater.hpp>
#include <boost/validate/laws/monoid.hpp>
#include <boost/validate/gentor/gentorprofile.h>
#include <boost/validate/gentor/rangegentor.h>

#include <boost/validate/itv_map_groupig_validater.hpp>
#include <boost/itl/interval_set.hpp>
#include <boost/itl_xt/numbergentor.hpp>
#include <boost/itl_xt/setgentor.hpp>
#include <boost/itl/functors.hpp>

using namespace std;
using namespace Loki;
using namespace boost;
using namespace boost::itl;
using namespace boost::posix_time;

void test_ItvMapGroupigValidater()
{
    ItvMapGroupigValidater validater;
    cout << 
    ">> ------------------------------------------------------ <<\n"
    ">> -------- Law based test automaton 'LaBatea' ---------- <<\n"
    ">> Output will be generated in a few seconds\n"
    ">> terminate by typing <CTRL>C\n"
    ">> ------------------------------------------------------ <<\n";
    validater.validate();
};


int main()
{
	test_ItvMapGroupigValidater();
    return 0;
}
