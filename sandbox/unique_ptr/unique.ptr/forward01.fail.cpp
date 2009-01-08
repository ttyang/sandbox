// Copyright 2009 Howard Hinnant.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation

// [unique.ptr]
// Test namespace scope move functions

// forward(lvalue int) should not work (must supply template arg)

#include "unique_ptr.hpp"

int main()
{
    int i = 1;
    int j = boost::forward(i);
}
