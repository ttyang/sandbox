// Copyright Fabian Bösch 2012
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/random/mkl/engine.hpp>
#include <boost/random/mkl/variate_generator_specialization_0x_distributions.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

int main()
{
	
	boost::random::mkl::mt19937 engine;

	std::uniform_int_distribution<int> dist;

	boost::random::variate_generator<boost::random::mkl::mt19937, std::uniform_int_distribution<int> > gen(engine, dist);

	std::vector<int> vec(100);

	std::vector<typename boost::random::mkl::mt19937::internal_type> vec2(100);
	
	engine(vec2.begin(), vec2.end());

	gen(vec.begin(), vec.end());
	boost::generate(vec.begin(), vec.end(), gen);

	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, "\n") );

	return 0;
}


