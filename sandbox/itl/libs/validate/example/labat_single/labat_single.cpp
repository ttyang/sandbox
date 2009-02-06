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
#include <boost/validate/lawvalidater.h>
#include <boost/validate/laws/monoid.h>
#include <boost/validate/laws/element_order.hpp>
#include <boost/validate/laws/subset_order.hpp>
#include <boost/validate/gentor/gentorprofile.h>
#include <boost/validate/gentor/rangegentor.h>

#include <boost/validate/single_law_validater.hpp>
#include <boost/itl/interval_set.hpp>
//#include <boost/itl_xt/numbergentor.hpp>
//#include <boost/itl_xt/setgentor.hpp>
#include <boost/itl/functors.hpp>

using namespace std;
using namespace Loki;
using namespace boost;
using namespace boost::itl;
using namespace boost::posix_time;


void test_LawValidater()
{
    //typedef BinaryPushout<itl::split_interval_map<int,double>, itl::map<int,double>, Interval::Atomize, inplace_plus>
    //    Map_Atomize_Union_DiagramT;
    //LawValidater<Map_Atomize_Union_DiagramT, RandomGentor> map_atomize_plus_pushout;
    //map_atomize_plus_pushout.setTrialsCount(1000);
    //map_atomize_plus_pushout.run();

    //typedef BinaryPushout<itl::map<int,double>, itl::split_interval_map<int,double>, Interval::Cluster, inplace_et>
    //    Map_Cluster_Intersect_DiagramT;
    //LawValidater<Map_Cluster_Intersect_DiagramT, RandomGentor> map_cluster_star_pushout;
    //map_cluster_star_pushout.setTrialsCount(1000);
    //map_cluster_star_pushout.run();

	typedef InplaceFlip
		<interval_map<int, int, total_enricher > >  TestLawT;
	LawValidater<TestLawT, RandomGentor> test_law;

	//-----------------------------------------------------------------------------
	int test_count = 10000;
	ptime start, stop;

	test_law.setTrialsCount(test_count);

	std::cout << "Start\n";
	start = ptime(microsec_clock::local_time());
	test_law.run();
	stop = ptime(microsec_clock::local_time());
	std::cout << "Stop. Time elapsed: " << stop - start << endl;
}



int main()
{
	test_LawValidater();
	return 0;
}
