// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


//[ acml_distributions_example
#include <boost/random/acml/engine.hpp>
#include <boost/random/acml/boost/distributions.hpp>
#include <vector>
#include <boost/static_assert.hpp>
#include <boost/generate/generate.hpp>

int main()
{
	typedef typename boost::random::acml::mt19937 engine_t;
	typedef typename boost::random::uniform_real_distribution<double> distribution_t;
	typedef typename boost::variate_generator<engine_t&, distribution_t> variate_generator_t;
	engine_t engine;                                                                                                            // ACML engine
	distribution_t distribution(0,10);                                                                                          // Boost.Random continuous uniform distribution
	variate_generator_t vg(engine, distribution);                                                                               // Corresponding variate_generator

	std::vector<double> v(1000);
	
	BOOST_STATIC_ASSERT(( boost::random::is_variate_generator_a_acml_range_generator<engine_t&,distribution_t>::type::value ));    // make sure we use a fast version
	BOOST_STATIC_ASSERT(( variate_generator_t::is_range_generator::apply<typename std::vector<double>::iterator>::type::value ));  // make sure vectorization is possible for this iterator class

	boost::generate(v.begin(), v.end(), vg);                             // generating random numbers using Boost.Generate
	vg(v.begin(), v.end());                                              // directly generate through range function call (insecure if we are not sure whether our iterators are suitable for vectorization)
	for (std::size_t i=0; i<v.size(); ++i) v[i] = distribution(engine);  // caution: this is slow!!!

	return 0;
}
//]

