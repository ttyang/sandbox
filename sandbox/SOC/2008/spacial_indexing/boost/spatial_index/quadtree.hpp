// Copyright 2008 Federico J. Fernandez.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_SPATIAL_INDEX_QUADTREE_HPP
#define BOOST_SPATIAL_INDEX_QUADTREE_HPP

#include "quadtree_node.hpp"

// #include <boost/thread/xtime.hpp>

namespace boost {
namespace spatial_index {


template<typename Key, typename Value>
class quadtree : public spatial_index<Key, Value>
{
private:
	quadtree_node<Key,Value> root;
	unsigned int element_count;

	// number of points in each node
	unsigned int node_size_;

public:
	quadtree(double min_x, double min_y, double max_x, double max_y) 
		: root(min_x, min_y, max_x, max_y, 1), element_count(0), node_size_(1)  {}
	  
	virtual void insert(const Key &k, const Value &v)
	{
		element_count++;
		root.insert(k, v);
	}

	virtual void bulk_insert(Value &v_begin, Value &v_end, std::vector<Key> &v)
	{
// 		boost::xtime xt1, xt2;
// 		boost::xtime_get(&xt1, boost::TIME_UTC);

		//unsigned int counter = 0;

		typename std::vector<Key>::iterator it_point;
		it_point = v.begin();
		Value it_data = v_begin;
		while(it_data != v_end && it_point != v.end()) {
			insert(*it_point, it_data);
			      
			it_data++;
			it_point++;

			//counter++;
			//if(counter%10000 == 0) {
				//std::cerr << "counter: [" << counter << "]" << std::endl;
			//}
		}

// 		boost::xtime_get(&xt2, boost::TIME_UTC);
// 		std::cerr << "secs: " << xt2.sec - xt1.sec;
// 		std::cerr << " nsecs: " << xt2.nsec - xt1.nsec << std::endl;
	}

	virtual Value find(const Key &k)
	{
		return root.find(k);
	}

	virtual std::deque<Value> find(const double x1, const double x2, const double y1, const double y2)
	{
		std::deque<Value> r;
		root.find(r, x1, x2, y1, y2);
		return r;
	}


	virtual unsigned int elements(void) { return element_count; }
	
	virtual ~quadtree() {}
};


} // namespace spatial_index
} // namespace boost

#endif // BOOST_SPATIAL_INDEX_QUADTREE_HPP

