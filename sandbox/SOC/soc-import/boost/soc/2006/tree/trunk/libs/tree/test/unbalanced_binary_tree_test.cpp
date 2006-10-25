//  Copyright (c) 2006, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/binary_tree.hpp>

#include <boost/tree/searcher.hpp>
#include <boost/tree/algorithm.hpp>

#include <boost/test/minimal.hpp>

//TODO: Make this a test suite.

void test_unbalance_binary_tree()
{
	using boost::tree::binary_tree;
	using boost::tree::lower_bound;
	
	typedef binary_tree<int> tree_type;
	tree_type mytree;

	tree_type::cursor c, c1, c2, c3, c4;
	tree_type::iterator it;
	
	c = mytree.root();

	BOOST_CHECK(c.empty());
	//BOOST_CHECK(c.is_root());
	
	c1 = mytree.insert(c, 1);
	BOOST_CHECK(*c1 == 1);
	//BOOST_CHECK(!c1.is_root());
	
	BOOST_CHECK(!c.empty());
	//BOOST_CHECK(c.is_root());
	
	BOOST_CHECK(c1.parent() == c);
	
	c2 = mytree.insert(c1, 2);
	BOOST_CHECK(!c.empty());
	BOOST_CHECK(c2.empty());
	BOOST_CHECK(*c1 == 1);
	BOOST_CHECK(*c2 == 2);
	*c1 = 14;
	BOOST_CHECK(*c1 == 14);
	BOOST_CHECK(*c2 == 2);
	BOOST_CHECK(c2.parent() == c1);
	BOOST_CHECK(c1.parent() == c);
	
	c3 = c1.end();
	BOOST_CHECK(c3 == c1.end());
	--c3;
	BOOST_CHECK(c3.parity() == 0);
	BOOST_CHECK(c3.parent() != c3);
	BOOST_CHECK(c3.parent() == c1);
	BOOST_CHECK(c3 == c1.begin());
	
	*c3 = 3;
	*(c1.begin()) = 2;
	
	BOOST_CHECK(*c3 == 2);
	++c3;
	c4 = mytree.insert(c3, 4);
	BOOST_CHECK(*c4 == 4);
	c4 = c4.parent();
	--c4;
	BOOST_CHECK(*c4 == 2);
	BOOST_CHECK(c4.parent() == c1);
	c = boost::tree::lower_bound(mytree.root(), mytree.shoot(), 2, std::less<int>());
	BOOST_CHECK(*c == 2);
	BOOST_CHECK(c4.empty());

	BOOST_CHECK(*c1 == 14);
	
	BOOST_CHECK(c1.begin().empty() || c1.end().empty());
	
	//c1 = mytree.erase(c1);
	//BOOST_CHECK(*c1 == 2);

	mytree.clear();	
	BOOST_CHECK(mytree.empty());
	
}



int test_main(int, char* [])
{
	test_unbalance_binary_tree();
	return 0;
}
