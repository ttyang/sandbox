/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#define BOOST_TEST_MODULE icl::casual unit test

#define BOOST_ICL_TEST_CHRONO

#include <libs/icl/test/disable_test_warnings.hpp>

#include <string>
#include <vector>
#include <boost/mpl/list.hpp>
#include "../unit_test_unwarned.hpp"


// interval instance types
#include "../test_type_lists.hpp"
#include "../test_value_maker.hpp"

#include <boost/rational.hpp>

#include <boost/type_traits/is_same.hpp>

#include <boost/icl/gregorian.hpp>
#include <boost/icl/ptime.hpp>

#include <boost/icl/interval_map.hpp>
#include <boost/icl/interval_set.hpp>
#include <boost/icl/interval.hpp>

#include <boost/icl/concept/_interval_map.hpp>

using namespace std;
using namespace boost;
using namespace unit_test;
using namespace boost::icl;
using namespace boost::posix_time;
using namespace boost::gregorian;


BOOST_AUTO_TEST_CASE(casual)
{
    typedef int T;
    typedef int U;
    typedef interval_map<T,U, partial_absorber> IntervalMapT;
    typedef interval_set<T>                     IntervalSetT;
    typedef IntervalMapT::interval_type         IntervalT;
    typedef IntervalSetT::iterator              SetIterT;

    IntervalSetT is = IntervalSetT(I_I(1,1)) + IntervalSetT(I_I(3,3));
    cout << is << endl;

    std::map<int,int> m1;
    m1.insert(make_pair(0, 1));
    m1.insert(make_pair(6, 2));
    std::map<int,int> m2;
    m2.insert(make_pair(0, 1));
    m2.insert(make_pair(4, 3));

    std::map<int,int> m3 = new_add(m1, m2);

    new_show(m3);

    BOOST_CHECK_EQUAL(true, true);
}

BOOST_AUTO_TEST_CASE(interval_map_via_vector)
{
    typedef std::pair<int,int> PairT;
    typedef std::vector<PairT> IntervalMapT;

    IntervalMapT m1;
    m1.insert(m1.end(), make_pair(0, 1));
    m1.insert(m1.end(), make_pair(6, 2));
    IntervalMapT m2;
    m2.insert(m2.end(), make_pair(0, 1));
    m2.insert(m2.end(), make_pair(4, 3));

    IntervalMapT m3 = new_add(m1, m2);

    new_show(m3);
}

