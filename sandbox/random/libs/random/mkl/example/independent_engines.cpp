// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/random/mkl/engine.hpp>
#include <vector>

int main()
{

	{
	//[ mkl_independent_engines_example_block_split
	typedef typename boost::random::mkl::mcg31 engine_t;           
	std::vector<engine_t> engines(100);                                                                             // 100 MKL engines
	boost::random::mkl::make_independent_engines_by_block_split<engine_t>(engines.begin(), engines.end(), 10000);   // make engines independent (max 10000 variates per engine)
	//]
	}

	{
	//[ mkl_independent_engines_example_leap_frog
	typedef typename boost::random::mkl::mcg31 engine_t;
	std::vector<engine_t> engines(100);                                                                             // 100 MKL engines
	boost::random::mkl::make_independent_engines_by_leap_frog<engine_t>(engines.begin(), engines.end());            // make engines independent
	//]
	}
	return 0;
}

