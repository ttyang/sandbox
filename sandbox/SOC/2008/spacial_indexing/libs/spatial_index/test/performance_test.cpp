// Copyright 2008 Federico J. Fernandez.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/spatial_index.hpp>

#include <boost/test/included/test_exec_monitor.hpp>
#include <boost/shared_ptr.hpp>

#include <vector>
#include <string>


#include <sys/time.h>


std::vector<std::pair<double,double> > read_data(void)
{
	std::set<std::pair<double,double> > v;
	std::vector<std::pair<double,double> > r;

	std::ifstream data;
	data.open("gis-data.txt");

	double x, y;
	data >> x;
	data >> y;
	while(!data.eof()) {
		data >> x;
		data >> y;
		v.insert(std::make_pair(x,y));
	}
	copy(v.begin(), v.end(), std::back_inserter(r));
	return r;
}


double drandom(unsigned int upper_bound)
{
	double r;		/* random value in range [0,1) */
	long int M;	/* user supplied upper boundary */

	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);
	srand(tv.tv_usec);

	M = upper_bound;		/* Choose M. Upper bound */
	r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );

	return r * M;
}


int test_main(int, char* [])
{
	std::vector<unsigned int> ids;
 	std::vector<std::pair<double, double> > points = read_data();

// 	std::cerr << "Size: " << points.size() << std::endl;

	// plane
 	const double min_x = -130.0;
 	const double min_y = 10.0;
 	const double max_x = -60.0;
 	const double max_y = 80.0;

	// number of points to find on the search phase
	const unsigned int find_count = 1000;

 	for(unsigned int i = 0; i < points.size(); i++) {
 		ids.push_back(i);
	}

  	boost::shared_ptr< boost::spatial_index::spatial_index< std::pair<double, double> , std::vector<unsigned int>::iterator > > 
  		q(new boost::spatial_index::quadtree< std::pair<double, double> , 
		  std::vector<unsigned int>::iterator >(min_x, min_y, max_x, max_y));

 	// load data
   	std::cerr << " --> bulk insert" << std::endl;
   	std::vector<unsigned int>::iterator b, e;
   	b = ids.begin();
   	e = ids.end();
   	q->bulk_insert(b,e, points);

	// search
	std::vector<std::pair<double,double> > search_positions;
	std::vector<unsigned int> search_data;
	for(unsigned int j=0; j < find_count; j++) {
		unsigned int pos = (int) drandom(points.size());

		search_positions.push_back(points[pos]);
		search_data.push_back(pos);
	}

	for(unsigned int j=0; j < find_count; j++) {
		std::vector<unsigned int>::iterator it = q->find(search_positions[j]);
		std::cout << search_data[j] 
			  << " - found in (" << search_positions[j].first << "," << search_positions[j].second << ") --> " 
			  << *it << std::endl;

		BOOST_CHECK_EQUAL(*it, search_data[j]);
	}

	return 0;
}



