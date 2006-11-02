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

int main()
{
    using namespace bimap;

    // Soccer World cup. (The results are not real)

    typedef bimap<std::string,int> results_bimap;
    typedef results_bimap::relation position;

    results_bimap results;
    results.insert( position("Argentina"    ,1) );
    results.insert( position("Spain"        ,2) );
    results.insert( position("Germany"      ,3) );
    results.insert( position("France"       ,4) );

    std::cout << "Countries names ordered by their final position:"
                << std::endl;

    for( results_bimap::right_iterator i    = results.right.begin(),
                                        iend = results.right.end() ;
            i != iend; ++i )
    {
        std::cout << i->first << ") " << i->second << std::endl;
    }

    std::cout << std::endl
                << "Countries names ordered alfabetically along with"
                    "their final position:"
                << std::endl;

    for( results_bimap::left_iterator  i    = results.left.begin(),
                                        iend = results.left.end() ;
            i != iend; ++i )
    {
        std::cout << i->first << " ends " << i->second << "º" << std::endl;
    }

}