// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/random/acml/engine.hpp>
#include <vector>

int main()
{

	{
	//[ acml_independent_engines_example_block_split
	typedef typename boost::random::acml::nag engine_t;           
	std::vector<engine_t> engines(100);                                                                             // 100 ACML engines
	boost::random::acml::make_independent_engines_by_block_split<engine_t>(engines.begin(), engines.end(), 10000);  // make engines independent (max 10000 variates per engine)
	//]
	}

	{
	//[ acml_independent_engines_example_leap_frog
	typedef typename boost::random::acml::wh engine_t;
	std::vector<engine_t> engines(100);                                                                             // 100 ACML engines
	boost::random::acml::make_independent_engines_by_leap_frog<engine_t>(engines.begin(), engines.end());           // make engines independent
	//]
	}
	return 0;
}

