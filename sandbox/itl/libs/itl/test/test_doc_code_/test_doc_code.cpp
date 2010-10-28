/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#define BOOST_TEST_MODULE icl::test_doc_code unit test

#include <limits>
#include <complex>


#include <string>
#include <vector>
#include <boost/mpl/list.hpp>
#include <boost/itl/iterator.hpp>
#include "../unit_test_unwarned.hpp"
#include <boost/test/test_case_template.hpp>

// interval instance types
#include "../test_type_lists.hpp"
#include "../test_value_maker.hpp"
#include "../test_laws.hpp"

#include <boost/type_traits/is_same.hpp>

#include <boost/itl/rational.hpp>

#include <boost/itl/detail/interval_morphism.hpp>
#include <boost/itl/interval_map.hpp>

using namespace std;
using namespace boost;
using namespace unit_test;
using namespace boost::icl;

BOOST_AUTO_TEST_CASE(intro_sample_telecast)
{
    // Switch on my favorite telecasts using an interval_set
    interval<int>::type news(2000, 2015);
    interval<int>::type talk_show(2245, 2330);
    interval_set<int> myTvProgram;
    myTvProgram.add(news).add(talk_show);

    // Iterating over elements (seconds) would be silly ...
    for(interval_set<int>::iterator telecast = myTvProgram.begin(); 
        telecast != myTvProgram.end(); ++telecast)
        //...so this iterates over intervals
        //TV.switch_on(*telecast);
        cout << *telecast;

    cout << endl;
}

BOOST_AUTO_TEST_CASE(interface_sample_identifiers)
{
    typedef interval_set<std::string, less, continuous_interval<std::string> > IdentifiersT;
    IdentifiersT identifiers, excluded;

    // special identifiers shall be excluded
    identifiers += continuous_interval<std::string>::right_open("a", "c");
    identifiers -= std::string("boost");
    cout << "identifiers: " << identifiers << endl;

    excluded = IdentifiersT(icl::hull(identifiers)) - identifiers;
    cout << "excluded   : " << excluded << endl;

    if(icl::contains(identifiers, std::string("boost")))
        cout << "error, identifiers.contains('boost')\n";
}

