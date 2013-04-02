// Copyright Fabian Bösch 2012
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <vector>
#include <algorithm>
#include <mkl.h>

//[ vsl_generator2
struct vsl_generator
{
	vsl_generator(VSLStreamStatePtr stream_) : stream(stream_) {}

	template <class Iterator>
	void operator()(Iterator begin, Iterator end)
	{
		viRngUniform(VSL_RNG_METHOD_UNIFORM_STD, stream, end-begin, &(*begin), 0, 10);
	}

	VSLStreamStatePtr stream; // random stream
};
//]

int main()
{
	

	VSLStreamStatePtr stream;                             // random stream
	int seed(42);                                         // seed value
	vslNewStream(&stream, VSL_BRNG_MT19937, seed);        // initialize random stream
	vsl_generator gen(stream);                            // create generator

	//[ std_generate
	// generate 10 uniformly distributed integers
	std::vector<int> variates(10,0);
	std::generate(variates.begin(), variates.end(), gen); 
	//]

	vslDeleteStream(&stream);                             // free resources
	
	return 0;
}

