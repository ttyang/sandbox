/*-----------------------------------------------------------------------------+    
A Law Based Test Automaton 'LaBatea'
Author: Joachim Faulhaber
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#include <iostream>
#include <stdio.h>

#include <boost/itl/ptime.hpp>

#include <boost/itl/set.hpp>
#include <boost/itl/map.hpp>
#include <boost/itl/interval_morphism.hpp>
#include <boost/validate/laws/induced_relation.hpp>
#include <boost/validate/laws/symmetric_difference.hpp>
#include <boost/validate/laws/pushouts.hpp>
#include <boost/validate/laws/set_laws.hpp>
//#include <boost/validate/laws/novial_tree.hpp>
#include <boost/validate/laws/inversion_laws.hpp>
#include <boost/validate/validater/law_validater.hpp>
#include <boost/validate/gentor/gentorprofile.hpp>
#include <boost/validate/gentor/rangegentor.hpp>
#include <boost/itl/interval_set.hpp>
#include <boost/itl/interval_map.hpp>
#include <boost/itl/functors.hpp>

using namespace std;
using namespace Loki;
using namespace boost;
using namespace boost::itl;
using namespace boost::posix_time;


void test_LawValidater()
{
    //typedef BinaryPushout<itl::split_interval_map<int,int,partial_enricher>, itl::map<int,int,partial_enricher>, Interval::Atomize, inplace_caret>
    //    TestLawT;
    //LawValidater<TestLawT, RandomGentor> test_law;

    //typedef BinaryPushout<itl::map<int,double>, itl::split_interval_map<int,double>, Interval::Cluster, inplace_et>
    //    Map_Cluster_Intersect_DiagramT;
    //LawValidater<Map_Cluster_Intersect_DiagramT, RandomGentor> map_cluster_star_pushout;
    //map_cluster_star_pushout.setTrialsCount(1000);
    //map_cluster_star_pushout.run();

    //typedef InplaceFlip
    //    <itl::interval_map<int, int, partial_enricher > >  TestLawT;
    //LawValidater<TestLawT, RandomGentor> test_law;

    //typedef InplaceAssociativity
    //    <itl::split_interval_map<int, int, partial_enricher> >  TestLawT;
    //LawValidater<TestLawT, RandomGentor> test_law;

    //typedef InducedRelation
    //    <itl::interval_map<int, int, partial_enricher>, 
    //    typename itl::interval_map<int, int, partial_enricher>::atomized_type, 
    //    Interval::Atomize, protonic_equal> TestLawT;
    //LawValidater<TestLawT, RandomGentor> test_law;

	//typedef Balance<itl::tree<int> >  TestLawT;
	//LawValidater<TestLawT, RandomGentor> test_law;

	typedef InplaceDeMorgan
	    <itl::interval_map<int, int> >  TestLawT;
	LawValidater<TestLawT, RandomGentor> test_law;

    //-----------------------------------------------------------------------------
    int test_count = 1000;
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
