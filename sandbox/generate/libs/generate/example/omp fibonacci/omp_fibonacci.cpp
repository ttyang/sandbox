// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

//[ parallel_fibonacci
#include <boost/generate/generate.hpp>
#include <vector>
#include <cmath>
#include <omp.h>
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

struct omp_fibonacci_generator
{
	// typedefs
	typedef unsigned long result_type;                                                                         // generator's result type
	typedef double internal_type;                                                                              // type used internally for computation
	typedef boost::range_generate::unit_stride_range_generator_type_checked<result_type> is_range_generator;   // metafunction class
	
	// range function call
	template <class Iterator>
	void operator()(Iterator begin, Iterator end)
	{
		result_type* m = &(*begin);                                                                        // raw pointer to data
		const size_t n = end-begin;                                                                        // number of elements
		// some constants
		const internal_type sqrt5 = sqrt(static_cast<internal_type>(5));                        
		const internal_type f     = 1 / sqrt5;
		const internal_type phi   = (1 + sqrt5) / 2;
		const internal_type psi   = (1 - sqrt5) / 2;
		#pragma omp parallel for default(shared) schedule(static)                                          // omp parallelization
		for (size_t i=0; i<n; ++i) m[i] = f * ( pow(phi, i+1) - pow(psi, i+1) );                           // use Moivre-Binet's explicit formula
	}
};

int main()
{
	omp_set_num_threads(8);
	vector<typename omp_fibonacci_generator::result_type> fibonacci_numbers(80);                    
	boost::generate(fibonacci_numbers.begin(), fibonacci_numbers.end(), omp_fibonacci_generator());            // call boost::generate
	copy(fibonacci_numbers.begin(), fibonacci_numbers.end(), ostream_iterator<typename omp_fibonacci_generator::result_type>(cout, "\n")); // print generated values
}
//]

