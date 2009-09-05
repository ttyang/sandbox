/*-----------------------------------------------------------------------------+    
Interval Template Library
Author: Joachim Faulhaber
Copyright (c) 2007-2009: Joachim Faulhaber
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
/** Example overlap_counter.cpp \file overlap_counter.cpp

    The most basic application of an interval_map is a counter counting
    the number of overlaps of intervals inserted into it.

    On could call an interval_map an aggregate on overlap machine. A very basic
    aggregation is summation of an integer. A interval_map<int,int> maps
    intervals of int to ints. 

    If we insert a value pair (interval<int>(2,6), 1) into the interval_map, it
    increases the content of all value pairs in the map by 1, if their interval
    part overlaps with interval<int>(2,6).

    \include overlap_counter/overlap_counter.cpp
*/
//[example_overlap_counter
#include <stdio.h>
#include <iostream>
#include <boost/itl/split_interval_map.hpp>

using namespace std;
using namespace boost::itl;


/* The most simple example of an interval_map is an overlap counter.
   If intervals are added that are associated with the value 1,
   all overlaps of added intervals are counted as a result in the
   associated values. 
*/
typedef interval_map<int, int> OverlapCounterT;

void print_overlaps(const OverlapCounterT& counter)
{
    for(OverlapCounterT::const_iterator it = counter.begin(); it != counter.end(); it++)
    {
        interval<int> itv  = (*it).first;
        int overlaps_count = (*it).second;
        if(overlaps_count == 1)
            cout << "in interval " << itv << " intervals do not overlap" << endl;
        else
            cout << "in interval " << itv << ": "<< overlaps_count << " intervals overlap" << endl;
    }
}

void overlap_counter()
{
    OverlapCounterT overlap_counter;
    interval<int> itv;

    itv = interval<int>::rightopen(4,8);
    cout << "-- adding   " << itv.as_string() << " -----------------------------------------" << endl;
    overlap_counter += make_pair(interval<int>::rightopen(4,8), 1);
    print_overlaps(overlap_counter);
    cout << "-----------------------------------------------------------" << endl;

    itv = interval<int>::rightopen(6,9);
    cout << "-- adding   " << itv.as_string() << " -----------------------------------------" << endl;
    overlap_counter += make_pair(interval<int>::rightopen(6,9), 1);
    print_overlaps(overlap_counter);
    cout << "-----------------------------------------------------------" << endl;

    itv = interval<int>::rightopen(1,9);
    cout << "-- adding   " << itv.as_string() << " -----------------------------------------" << endl;
    overlap_counter += make_pair(interval<int>::rightopen(1,9), 1);
    print_overlaps(overlap_counter);
    cout << "-----------------------------------------------------------" << endl;
    
}

int main()
{
    cout << ">> Interval Template Library: Sample overlap_counter.cpp <<\n";
    cout << "-----------------------------------------------------------\n";
    overlap_counter();
    return 0;
}

// Program output:

// >> Interval Template Library: Sample overlap_counter.cpp <<
// -----------------------------------------------------------
// -- adding   [4,8) -----------------------------------------
// in interval [4,8) intervals do not overlap
// -----------------------------------------------------------
// -- adding   [6,9) -----------------------------------------
// in interval [4,6) intervals do not overlap
// in interval [6,8): 2 intervals overlap
// in interval [8,9) intervals do not overlap
// -----------------------------------------------------------
// -- adding   [1,9) -----------------------------------------
// in interval [1,4) intervals do not overlap
// in interval [4,6): 2 intervals overlap
// in interval [6,8): 3 intervals overlap
// in interval [8,9): 2 intervals overlap
// -----------------------------------------------------------
//]
