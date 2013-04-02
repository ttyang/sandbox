// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

//[ acml
#include <boost/random/acml/engine.hpp>
#include <boost/random/acml/c++11/distributions.hpp>                             // specializations of the variate_generator class template for c++11 distribution classes
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
	typedef double result_type;
	typedef normal_distribution<result_type> distribution_t;                 // standard normal distribution
	typedef boost::random::acml::mt19937 engine_t;                           // random number engine wrapper for AMD ACML functions
	typedef boost::variate_generator<engine_t&,distribution_t> generator_t;  // variate generator internally uses AMD ACML functions

	std::vector<result_type> v(1000);
	distribution_t distribution;
	engine_t engine;
	boost::generate(v.begin(), v.end(), generator_t(engine,distribution));   // generate variates
	copy(v.begin(), v.end(), ostream_iterator<double>(cout, "\n"));          // print generated values
	return 0;
}
//]

