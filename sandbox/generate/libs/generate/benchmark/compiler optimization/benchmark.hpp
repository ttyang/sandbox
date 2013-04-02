// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GENERATE_BENCHMARK_COMPILER_OPTIMIZATION_BENCHMARK_HPP
#define BOOST_GENERATE_BENCHMARK_COMPILER_OPTIMIZATION_BENCHMARK_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <boost/generate/generate.hpp>
#include <vector>
#include <chrono>
#include <string>
#include <initializer_list>

template <class Generator>
struct has_state : public boost::mpl::false_ {};

//[while_generate
template <class ForwardIterator, class Generator>
void while_generate( ForwardIterator first, ForwardIterator last, Generator gen )
{
	while (first != last)  *first++ = gen();
}
//]
//[for_generate
template <class UnitStrideIterator, class Generator>
void for_generate( UnitStrideIterator first, UnitStrideIterator last, Generator gen )
{
	typedef typename std::iterator_traits<UnitStrideIterator>::difference_type difference_type;
	typedef typename std::iterator_traits<UnitStrideIterator>::pointer pointer;

	const difference_type n(last-first);
	pointer data(&*first);
	for ( difference_type i=0; i<n; ++i) data[i] = gen();
}
//]
//[for_generate2
template <class UnitStrideIterator, class Generator>
void for_generate2( UnitStrideIterator first, UnitStrideIterator last, Generator gen )
{
	typedef typename std::iterator_traits<UnitStrideIterator>::pointer pointer;

	pointer end(&*last);
	for ( pointer i=&*first; i!=end; ++i) *i = gen();
}
//]

#define BOOST_GENERATE_BENCHMARK_COMPILER_OPTIMIZATION_METHOD(method, ignore)         \
if (!ignore) std::cout << std::left << std::setw(column1_w) << #method;               \
if (!ignore && outfile.is_open()) outfile << std::left << std::setw(column1_w) << #method;       \
for (std::size_t i=0; i<n_vec.size(); ++i)                                            \
{                                                                                     \
	const std::size_t n = n_vec[i];                                                   \
	std::vector<result_t> v(n);                                                       \
	for (std::size_t r=0; r<10; ++r)                                                  \
	{                                                                                 \
		method(v.begin(), v.end(), generator);                                        \
	}                                                                                 \
	auto t0 = std::chrono::high_resolution_clock::now();                              \
	for (std::size_t r=0; r<rep; ++r)                                                 \
	{                                                                                 \
		method(v.begin(), v.end(), generator);                                        \
	}                                                                                 \
	auto t1 = std::chrono::high_resolution_clock::now();                              \
	auto dt = std::chrono::duration_cast<milliseconds>(t1-t0).count();                \
	if (!ignore) std::cout << std::right << std::setw(column_w) << dt/rep;            \
	if (!ignore && outfile.is_open()) outfile << std::right << std::setw(column_w) << dt/rep;    \
}                                                                                     \
if (!ignore) std::cout << std::endl;                                                  \
if (!ignore && outfile.is_open()) outfile << std::endl;


#define BOOST_GENERATE_BENCHMARK_COMPILER_OPTIMIZATION_METHOD_STATE(method, ignore)         \
if (!ignore) std::cout << std::left << std::setw(column1_w) << #method;               \
if (!ignore && outfile.is_open()) outfile << std::left << std::setw(column1_w) << #method;       \
for (std::size_t i=0; i<n_vec.size(); ++i)                                            \
{                                                                                     \
	const std::size_t n = n_vec[i];                                                   \
	std::vector<result_t> v(n);                                                       \
	generator.data = &v[0];                                                           \
	for (std::size_t r=0; r<10; ++r)                                                  \
	{                                                                                 \
		generator.c = 0;                                                              \
		method(v.begin(), v.end(), generator);                                        \
	}                                                                                 \
	auto t0 = std::chrono::high_resolution_clock::now();                              \
	for (std::size_t r=0; r<rep; ++r)                                                 \
	{                                                                                 \
		generator.c = 0;                                                              \
		method(v.begin(), v.end(), generator);                                        \
	}                                                                                 \
	auto t1 = std::chrono::high_resolution_clock::now();                              \
	auto dt = std::chrono::duration_cast<milliseconds>(t1-t0).count();                \
	if (!ignore) std::cout << std::right << std::setw(column_w) << dt/rep;            \
	if (!ignore && outfile.is_open()) outfile << std::right << std::setw(column_w) << dt/rep;    \
}                                                                                     \
if (!ignore) std::cout << std::endl;                                                  \
if (!ignore && outfile.is_open()) outfile << std::endl;


class benchmark
{
	public:

	benchmark(std::initializer_list<std::size_t> il, std::size_t _rep=2000) 
	: column1_w(30), column_w(20), n_vec(il), rep(_rep) {}

	benchmark(std::vector<std::size_t> v, std::size_t _rep=2000) 
	: column1_w(30), column_w(20), n_vec(v), rep(_rep) {}

	template <class Generator, class ResultType>
	void run(std::string title, Generator& generator, ResultType*, void*)
	{
		typedef std::chrono::duration<double, std::milli> milliseconds;
		typedef ResultType result_t;	
		
		print_header(title);	
		std::ofstream outfile;
  		outfile.open(title.c_str(), std::fstream::app);

		// while generate
		BOOST_GENERATE_BENCHMARK_COMPILER_OPTIMIZATION_METHOD(while_generate, true)
		
		// while generate
		BOOST_GENERATE_BENCHMARK_COMPILER_OPTIMIZATION_METHOD(while_generate, false)

		// for generate 1
		BOOST_GENERATE_BENCHMARK_COMPILER_OPTIMIZATION_METHOD(for_generate, false)

		// for generate 2
		BOOST_GENERATE_BENCHMARK_COMPILER_OPTIMIZATION_METHOD(for_generate2, false)

		// std::generate
		BOOST_GENERATE_BENCHMARK_COMPILER_OPTIMIZATION_METHOD(std::generate, false)

		// boost::generate
		BOOST_GENERATE_BENCHMARK_COMPILER_OPTIMIZATION_METHOD(boost::generate, false)

		std::cout << std::endl;
		if (outfile.is_open()) outfile.close();
	}

	template <class Generator, class ResultType>
	void run(std::string title, Generator& generator, ResultType*, bool)
	{
		typedef std::chrono::duration<double, std::milli> milliseconds;
		typedef ResultType result_t;	
		
		print_header(title);	
		std::ofstream outfile;
  		outfile.open(title.c_str(), std::fstream::app);
		
		// while generate
		BOOST_GENERATE_BENCHMARK_COMPILER_OPTIMIZATION_METHOD_STATE(while_generate, true)
		
		// while generate
		BOOST_GENERATE_BENCHMARK_COMPILER_OPTIMIZATION_METHOD_STATE(while_generate, false)

		// for generate 1
		BOOST_GENERATE_BENCHMARK_COMPILER_OPTIMIZATION_METHOD_STATE(for_generate, false)

		// for generate 2
		BOOST_GENERATE_BENCHMARK_COMPILER_OPTIMIZATION_METHOD_STATE(for_generate2, false)

		// std::generate
		BOOST_GENERATE_BENCHMARK_COMPILER_OPTIMIZATION_METHOD_STATE(std::generate, false)

		// boost::generate
		BOOST_GENERATE_BENCHMARK_COMPILER_OPTIMIZATION_METHOD_STATE(boost::generate, false)

		std::cout << std::endl;
		if (outfile.is_open()) outfile.close();
	}

	private:
	
	void print_header(const std::string& title)
	{
		//std::cout << std::setfill('*') << std::setw (title.size()) << "" << std::endl;
		std::cout << title << std::endl;
		std::cout << std::setfill('*') << std::setw (title.size()) << "" << std::endl;
		std::cout << std::setfill(' ');

		std::cout << std::left << std::setw(column1_w) << "Method";
		for (std::size_t i=0; i<n_vec.size(); ++i)
			std::cout << std::right << std::setw(column_w) << n_vec[i];
		std::cout << std::endl;
		std::cout << std::setfill('-') << std::setw (column1_w + n_vec.size()*column_w) << "" << std::endl;
		std::cout << std::setfill(' ');
		std::ofstream outfile;
  		outfile.open(title.c_str());
		if (outfile.is_open())
		{
			outfile << std::left << std::setfill(' ') << std::setw(column1_w) << "Method";
			for (std::size_t i=0; i<n_vec.size(); ++i)
				outfile << std::right << std::setw(column_w) << n_vec[i];
			outfile << std::endl;
			outfile.close();
		}
	}
	
	private:

	const std::size_t column1_w;
	const std::size_t column_w;
	const std::vector<std::size_t> n_vec;
	const std::size_t rep;	
};




#endif // BOOST_GENERATE_BENCHMARK_COMPILER_OPTIMIZATION_BENCHMARK_HPP

