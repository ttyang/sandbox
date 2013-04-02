// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RANDOM_ACML_BENCHMARK_HPP
#define BOOST_RANDOM_ACML_BENCHMARK_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <string>
#include <initializer_list>

#include <boost/random/acml/engine.hpp>
#include <boost/random/mkl/engine.hpp>
#include <boost/random/acml/boost/distributions.hpp>
#include <boost/random/acml/c++11/distributions.hpp>
#include <boost/random/mkl/boost/distributions.hpp>
#include <boost/random/mkl/c++11/distributions.hpp>
//#include <random>
//#include <boost/random.hpp>
#include <boost/generate/generate.hpp>



#define BOOST_RANDOM_ACML_BENCHMARK_N(eng, dist, vg, result_t, body)        \
std::cout << std::left << std::setw(w_1) << eng;                            \
std::cout << std::left << std::setw(w_2) << dist;                           \
std::cout << std::left << std::setw(w_3) << #vg;                            \
outfile << std::left << std::setw(w_1) << eng;                              \
outfile << std::left << std::setw(w_2) << dist;                             \
outfile << std::left << std::setw(w_3) << #vg;                              \
for (std::size_t i=0; i<n_vec.size(); ++i)                                  \
{	                                                                        \
	const std::size_t n = n_vec[i];                                         \
	std::vector<result_t> variates(n);	                                    \
	auto t0 = std::chrono::high_resolution_clock::now();	                \
	for (std::size_t r=0; r<rep; ++r)                                       \
	{                                                                       \
		body                                                                \
	}                                                                       \
	auto t1 = std::chrono::high_resolution_clock::now();                    \
	auto dt = std::chrono::duration_cast<milliseconds>(t1-t0).count();      \
	std::cout << std::right << std::setw(w) << dt/rep;                      \
	if (outfile.is_open()) outfile << std::right << std::setw(w) << dt/rep; \
}                                                                           \
std::cout << std::endl;                                                     \
if (outfile.is_open()) outfile << std::endl;


class benchmark
{

	public:

	benchmark(std::initializer_list<std::size_t> il, std::size_t _rep=500) : n_vec(il), rep(_rep) {}
	
	template<class ACMLEngine, class MKLEngine, class StdEngine, class BoostEngine, class StdDistribution, class BoostDistribution>
	void run(std::string title, 
	         ACMLEngine& acml_engine, std::string acml_engine_str,
	         MKLEngine& mkl_engine, std::string mkl_engine_str,
	         StdEngine& std_engine, std::string std_engine_str,
	         BoostEngine& boost_engine, std::string boost_engine_str,
             StdDistribution& std_distribution, std::string std_distribution_str,
	         BoostDistribution& boost_distribution, std::string boost_distribution_str,
	         void (*raw_acml_function)(ACMLEngine&, std::size_t, typename boost::variate_generator<ACMLEngine&,StdDistribution>::result_type*),
	         void (*raw_mkl_function)(MKLEngine&, std::size_t, typename boost::variate_generator<MKLEngine&,StdDistribution>::result_type*))
	{
		typedef typename boost::variate_generator<ACMLEngine&,StdDistribution> std_acml_vg_t;
		typedef typename boost::variate_generator<MKLEngine&,StdDistribution> std_mkl_vg_t;
		typedef typename std_acml_vg_t::result_type std_acml_vg_result_t;
		typedef typename std_mkl_vg_t::result_type std_mkl_vg_result_t;
		typedef typename boost::variate_generator<ACMLEngine&,BoostDistribution> boost_acml_vg_t;
		typedef typename boost::variate_generator<MKLEngine&,BoostDistribution> boost_mkl_vg_t;
		typedef typename boost_acml_vg_t::result_type boost_acml_vg_result_t;
		typedef typename boost_mkl_vg_t::result_type boost_mkl_vg_result_t;
		typedef typename StdDistribution::result_type std_dist_result_t;
		typedef typename BoostDistribution::result_type boost_dist_result_t;
		typedef std_acml_vg_result_t raw_acml_result_t;
		typedef std_mkl_vg_result_t raw_mkl_result_t;
		
		std_acml_vg_t std_acml_vg(acml_engine,std_distribution);
		std_mkl_vg_t std_mkl_vg(mkl_engine,std_distribution);
		boost_acml_vg_t boost_acml_vg(acml_engine,boost_distribution);
		boost_mkl_vg_t boost_mkl_vg(mkl_engine,boost_distribution);

		typedef std::chrono::duration<double, std::milli> milliseconds;

		std::size_t w_1 = 30;
		std::size_t w_2 = 50;
		std::size_t w_3 = 18;
		std::size_t w   = 15;

		std::ofstream outfile;
  		outfile.open(title.c_str());
		if (outfile.is_open())
		{
			outfile << std::left <<  std::setw(w_1) << "engine";
			outfile << std::left <<  std::setw(w_2) << "distribution";
			outfile << std::left <<  std::setw(w_3) << "variate_generator";
			for (std::size_t i=0; i<n_vec.size(); ++i)
				outfile << std::right << std::setw(w) << n_vec[i];
			outfile << std::endl;
		}
		//std::cout << std::setfill('*') << std::setw (title.size()) << "" << std::endl;
		std::cout << title << std::endl;
		std::cout << std::setfill('*') << std::setw (title.size()) << "" << std::endl;
		std::cout << std::setfill(' ');
		std::cout << std::left <<  std::setw(w_1) << "engine";
		std::cout << std::left <<  std::setw(w_2) << "distribution";
		std::cout << std::left <<  std::setw(w_3) << "variate_generator";
		for (std::size_t i=0; i<n_vec.size(); ++i)
			std::cout << std::right << std::setw(w) << n_vec[i];
		std::cout << std::endl;
		std::cout << std::setfill('-') << std::setw (w_1+w_2+w_3 + n_vec.size()*w) << "" << std::endl;
		std::cout << std::setfill(' ');

		// Boost engine and boost probability distribution
		BOOST_RANDOM_ACML_BENCHMARK_N(
			boost_engine_str, boost_distribution_str, no, 
			boost_dist_result_t,
			for (std::size_t j=0; j<n; ++j)
			{
				variates[j] = boost_distribution(boost_engine);
			}
		)

		// Standard engine and standard probability distribution
		BOOST_RANDOM_ACML_BENCHMARK_N(
			std_engine_str, std_distribution_str, no,
			std_dist_result_t,
			for (std::size_t j=0; j<n; ++j)
			{
				variates[j] = std_distribution(std_engine);
			}
		)

		// ACML engine with standard probability distribution without variate generator
		BOOST_RANDOM_ACML_BENCHMARK_N(
			acml_engine_str, std_distribution_str, no,
			std_dist_result_t,
			for (std::size_t j=0; j<n; ++j)
			{
				variates[j] = std_distribution(acml_engine);
			}
		)

		// ACML engine with boost probability distribution without variate generator
		BOOST_RANDOM_ACML_BENCHMARK_N(
			acml_engine_str, boost_distribution_str, no,
			boost_dist_result_t,
			for (std::size_t j=0; j<n; ++j)
			{
				variates[j] = boost_distribution(acml_engine);
			}
		)

		// ACML engine with standard probability distribution with variate generator
		BOOST_RANDOM_ACML_BENCHMARK_N(
			acml_engine_str, std_distribution_str, yes,
			std_acml_vg_result_t,
			boost::generate(variates.begin(), variates.end(), std_acml_vg);
		)

		// ACML engine with boost probability distribution with variate generator
		BOOST_RANDOM_ACML_BENCHMARK_N(
			acml_engine_str, boost_distribution_str, yes,
			boost_acml_vg_result_t,
			boost::generate(variates.begin(), variates.end(), boost_acml_vg);
		)

		// raw ACML c-functions
		BOOST_RANDOM_ACML_BENCHMARK_N(
			"raw ACML function", "raw ACML function", -,
			raw_acml_result_t,
			raw_acml_function(acml_engine, n, &variates[0]);
		)

		// MKL engine with standard probability distribution without variate generator
		BOOST_RANDOM_ACML_BENCHMARK_N(
			mkl_engine_str, std_distribution_str, no,
			std_dist_result_t,
			for (std::size_t j=0; j<n; ++j)
			{
				variates[j] = std_distribution(mkl_engine);
			}
		)

		// MKL engine with boost probability distribution without variate generator
		BOOST_RANDOM_ACML_BENCHMARK_N(
			mkl_engine_str, boost_distribution_str, no,
			boost_dist_result_t,
			for (std::size_t j=0; j<n; ++j)
			{
				variates[j] = boost_distribution(mkl_engine);
			}
		)

		// MKL engine with standard probability distribution with variate generator
		BOOST_RANDOM_ACML_BENCHMARK_N(
			mkl_engine_str, std_distribution_str, yes,
			std_mkl_vg_result_t,
			boost::generate(variates.begin(), variates.end(), std_mkl_vg);
		)

		// MKL engine with boost probability distribution with variate generator
		BOOST_RANDOM_ACML_BENCHMARK_N(
			mkl_engine_str, boost_distribution_str, yes,
			boost_acml_vg_result_t,
			boost::generate(variates.begin(), variates.end(), boost_mkl_vg);
		)

		// raw MKL c-functions
		BOOST_RANDOM_ACML_BENCHMARK_N(
			"raw MKL function", "raw MKL function", -, 
			raw_mkl_result_t,
			raw_mkl_function(mkl_engine, n, &variates[0]);
		)

		if (outfile.is_open()) outfile.close();
		std::cout << std::endl;

	}

	private:

	private:

	const std::vector<std::size_t> n_vec;
	const std::size_t rep;

};


#endif // BOOST_RANDOM_ACML_BENCHMARK_HPP

