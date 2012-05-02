/* Copyright (C) 2012 Étienne Dupuis
* 
* Use, modification and distribution is subject to the 
* Boost Software License, Version 1.0. (See accompanying
* file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
*/

// Test of bug #5902 (https://svn.boost.org/trac/boost/ticket/5902)

#include <boost/pool/pool.hpp>

int main() 
{
	boost::pool<> p(0, 1, 1);
	
	p.malloc();
	p.ordered_malloc();
	p.ordered_malloc(48);

	return 0;
}
