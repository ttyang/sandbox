//  Copyright 2010 Brian Bartman.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)


#include <boost/integer/details/member.hpp>

using namespace boost;

// Fails because no storage is specified.

typedef bitfield_tuple< member<int,red,3> > bft;

int main() {
    return 0;
}
