// Boost.Bimap
//
// Copyright (c) 2006 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Boost.Bimap Example
//-----------------------------------------------------------------------------

#include <iostream>

#include <boost/bimap/bimap.hpp>

struct country  {};
struct place    {};

int main()
{
    using namespace bimap;

    // Soccer World cup. (The results are not real)

    typedef bimap
    <
        tagged< std::string, country >,
        tagged< int        , place   >

    > results_bimap;

    typedef results_bimap::relation position;

    results_bimap results;
    results.insert( position("Argentina"    ,1) );
    results.insert( position("Spain"        ,2) );
    results.insert( position("Germany"      ,3) );
    results.insert( position("France"       ,4) );

    std::cout << "Countries names ordered by their final position:"
                << std::endl;

    typedef iterator_type_by<place,results_bimap>::type iterator_by_place;
    for( iterator_by_place i    = map_by<place>(results).begin(),
                            iend = map_by<place>(results).end() ;
            i != iend; ++i )
    {
        std::cout << get<place>(*i) << ") " << get<country>(*i) << std::endl;
    }

    std::cout << std::endl
                << "Countries names ordered alfabetically along with"
                    "their final position:"
                << std::endl;

    typedef iterator_type_by<country,results_bimap>::type iterator_by_country;
    for(  iterator_by_country i    = map_by<country>(results).begin(),
                                iend = map_by<country>(results).end() ;
            i != iend; ++i )
    {
        std::cout << get<country>(*i) << " ends " << get<place>(*i) << "º" << std::endl;
    }

}