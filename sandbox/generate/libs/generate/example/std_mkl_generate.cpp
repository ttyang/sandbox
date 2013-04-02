// Copyright Fabian Bösch 2012
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <vector>
#include <algorithm>
#include <mkl.h>

//[ vsl_generator
struct vsl_generator
{
	vsl_generator(VSLStreamStatePtr stream_) : stream(stream_) {}

	int operator()()
	{
		int r; // result
		// call MKL function for discrete uniform distribution: viRngUniform( const int method, VSLStreamStatePtr stream, const int n, int* r, const int a, const int b );
		// generates random numbers uniformly distributed over the interval [a, b), where a, b are the left and right bounds of the interval respectively, 
		// n is the number of random values to be generated and r denotes the output vector of n random numbers.
		viRngUniform(VSL_RNG_METHOD_UNIFORM_STD, stream, 1,             &r, 0, 10);
		return r;
	}

	VSLStreamStatePtr stream; // random stream
};
//]

int main()
{
//[ main_code
	std::vector<int> variates(10,0);

	VSLStreamStatePtr stream;                             // random stream
	int seed(42);                                         // seed value
	vslNewStream(&stream, VSL_BRNG_MT19937, seed);        // initialize random stream
	vsl_generator gen(stream);                            // create generator

	std::generate(variates.begin(), variates.end(), gen); // generate 10 uniformly distributed integers in interval [0, 9]

	vslDeleteStream(&stream);                             // free resources
//]

	return 0;
}

