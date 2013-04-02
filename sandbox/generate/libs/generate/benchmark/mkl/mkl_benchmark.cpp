// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <mkl.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <random>
#include <algorithm>
#include <functional>
#include <chrono>
#include <boost/generate/generate.hpp>

//[ mkl_generator1
struct mkl_generator
{
	mkl_generator() { vslNewStream(&stream, VSL_BRNG_MT19937, 42); }
	mkl_generator(const mkl_generator& other) { vslCopyStream(&stream, other.stream); }
	~mkl_generator() { vslDeleteStream(&stream); }

	inline double operator()()
	{
		double result;
		vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER, stream, 1, &result, 0, 1);
		return result;
	}

	VSLStreamStatePtr stream;
};
//]

//[ mkl_generator2
struct mkl_generator_refined
{
	mkl_generator_refined() { vslNewStream(&stream, VSL_BRNG_MT19937, 42); }
	mkl_generator_refined(const mkl_generator_refined& other) { vslCopyStream(&stream, other.stream); }
	~mkl_generator_refined() { vslDeleteStream(&stream); }

	template <class Iterator>
	inline void operator()(Iterator first, Iterator last)
	{
		unsigned int n = static_cast<unsigned int>(last - first);
		vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER, stream, n, &(*first), 0, 1);
	}

	VSLStreamStatePtr stream;
};
//]

//[ mkl_range_generator
struct mkl_range_generator
{
	typedef boost::range_generate::unit_stride_range_generator_type_checked<double> is_range_generator;
	
	mkl_range_generator() { vslNewStream(&stream, VSL_BRNG_MT19937, 42); }
	mkl_range_generator(const mkl_range_generator& other) { vslCopyStream(&stream, other.stream); }
	~mkl_range_generator() { vslDeleteStream(&stream); }

	inline double operator()()
	{
		double result;
		vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER, stream, 1, &result, 0, 1);
		return result;
	}

	template <class UnitStrideIterator>
	inline void operator()(UnitStrideIterator first, UnitStrideIterator last)
	{
		unsigned int n = static_cast<unsigned int>(last - first);
		vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER, stream, n, &(*first), 0, 1);
	}

	VSLStreamStatePtr stream;
};
//]

int main()
{
	//[ std_normal_generate
	const std::size_t N = 1000000;
	std::vector<double> samples(N);

	// generate N standard normal distributed random samples
	// using the c++11 numerics (random) library
	std::normal_distribution<double> dist(0,1);                                        // probability distribution function
	std::mt19937 urng;                                                                 // uniform random number generator
	//<- this will be ignored by quickbook
	auto t0  = std::chrono::high_resolution_clock::now();                              // start timer
	//->
	std::generate(samples.begin(), samples.end(), std::bind( dist, std::ref(urng) ) ); // generate normal distributed variates
	//]
	auto t1  = std::chrono::high_resolution_clock::now();  // stop timer
	auto dt1 = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();   // measure time in milliseconds


	//[ plain_mkl_generate
	// generate N standard normal distributed random samples
	// using Intel Math Kernel Library's (MKL) Statistical Functions
	VSLStreamStatePtr stream;
	vslNewStream(&stream, VSL_BRNG_MT19937, 42);                                       // uniform random number generator stream
	//<- this will be ignored by quickbook
	t0  = std::chrono::high_resolution_clock::now();                                   // start timer
	//->
	vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER, stream, N, &samples[0], 0, 1);    // generate normal distributed variates
	vslDeleteStream(&stream);                                                          // delete stream
	//]
	t1  = std::chrono::high_resolution_clock::now();                                   // stop timer
	auto dt2 = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();   // measure time in milliseconds


	//[ mkl_generator1_generate	
	// generate N standard normal distributed random samples
	// using Intel Math Kernel Library's (MKL) Statistical Functions wrapped by a generator function object
	mkl_generator gen;                                                                 // create generator
	//<- this will be ignored by quickbook
	t0 = std::chrono::high_resolution_clock::now();                                    // start timer
	//->
	std::generate(samples.begin(), samples.end(), std::ref(gen));                      // generate normal distributed variates
	//]
	t1 = std::chrono::high_resolution_clock::now();                                    // stop timer
	auto dt3 = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();   // measure time in milliseconds

	
	//[ mkl_generator2_generate	
	// generate N standard normal distributed random samples
	// using Intel Math Kernel Library's (MKL) Statistical Functions wrapped by another generator function object
	mkl_generator_refined gen2;                                                       // create generator
	//<- this will be ignored by quickbook
	t0 = std::chrono::high_resolution_clock::now();                                   // start timer
	//->
	gen2(samples.begin(), samples.end());                                             // generate normal distributed variates
	//]
	t1 = std::chrono::high_resolution_clock::now();                                   // stop timer
	auto dt4 = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();  // measure time in milliseconds


	//[ mkl_range_generate	
	// generate N standard normal distributed random samples
	// using Intel Math Kernel Library's (MKL) Statistical Functions wrapped by a range generator function object
	mkl_range_generator gen3;                                                         // create generator
	//<- this will be ignored by quickbook
	t0 = std::chrono::high_resolution_clock::now();                                   // start timer
	//->
	boost::generate(samples.begin(), samples.end(), std::ref(gen3));                  // generate normal distributed variates	
	//]
	t1 = std::chrono::high_resolution_clock::now();                                   // stop timer
	auto dt5 = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();  // measure time in milliseconds


	//[ mkl_range_generate_list
	// generate N standard normal distributed random samples for a linked list
	// using Intel Math Kernel Library's (MKL) Statistical Functions wrapped by a range generator function object
	std::list<double> samples_list(N);
	//<- this will be ignored by quickbook
	t0 = std::chrono::high_resolution_clock::now();                                   // start timer
	//->
	boost::generate(samples_list.begin(), samples_list.end(), std::ref(gen3));        // generate normal distributed variates	
	//]
	t1 = std::chrono::high_resolution_clock::now();                                   // stop timer
	auto dt6 = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();  // measure time in milliseconds

	// output timings
	std::cout << std::left <<  std::setw(40) << "c++11 random" << std::right <<  std::setw(10) << dt1 << " milliseconds" << std::endl;	
	std::cout << std::left <<  std::setw(40) << "plain MKL-VSL" << std::right <<  std::setw(10) << dt2 << " milliseconds" << std::endl;	
	std::cout << std::left <<  std::setw(40) << "MKL function object" << std::right <<  std::setw(10) << dt3 << " milliseconds" << std::endl;	
	std::cout << std::left <<  std::setw(40) << "MKL function object refined" << std::right <<  std::setw(10) << dt4 << " milliseconds" << std::endl;	
	std::cout << std::left <<  std::setw(40) << "MKL range function object" << std::right <<  std::setw(10) << dt5 << " milliseconds" << std::endl;	
	std::cout << std::left <<  std::setw(40) << "MKL range function object with list" << std::right <<  std::setw(10) << dt6 << " milliseconds" << std::endl;	

	return 0;
}

