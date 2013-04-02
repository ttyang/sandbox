// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "benchmark.hpp"
#include <boost/random/mersenne_twister.hpp>
#include <functional>

//[ initializer_generator
template <class Value>
struct initializer_generator
{
	typedef Value result_type;
	initializer_generator(const result_type& init) : _init(init) {}
	inline result_type operator()() { return _init; }
	const result_type _init;
};
//]

//[counter_generator
template <class Value>
struct counter_generator
{
	typedef Value result_type;
	counter_generator(std::size_t init) : c(init) {}
	inline result_type operator()() { return c++
	std::size_t c;
	//<- this will be ignored by quickbook
	result_type* data;
	//->
};
//]

//[adder_generator
struct adder_generator
{
	typedef float result_type;
	inline result_type operator()() 
	{ 
		return 2.f + 6.f; 
	}
};
//]

//[incrementer_generator
struct adder_generator_state
{
	typedef float result_type;
	//<- this will be ignored by quickbook
	adder_generator_state() : data(0), c(0) {}
	//->
	adder_generator_state(result_type* p) : data(p), c(0) {}
	inline result_type operator()() 
	{ 
		return data[c] + 10.f;
		++c;
	}
	result_type* data;
	std::size_t c;
};
//]

#define TOKEN_TO_STRING(TOK) # TOK
#define STR_VALUE(TOK) TOKEN_TO_STRING(TOK)

int main()
{
	std::vector<std::size_t> n;
	//n.push_back(1000); n.push_back(5000); n.push_back(10000); n.push_back(50000); 
	n.push_back(1000000); //n.push_back(5000000);
	// n.push_back(10000000);
	//benchmark bm{ 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000, 10000000 };
	benchmark bm(n);
	std::string s (STR_VALUE(__OPTIMIZATIONS));	
	//std::cout << s << std::endl;

	initializer_generator<double> gen1(0);
	bm.run(std::string("initializer ")+s, gen1, (double*)0, (void*)0);

	counter_generator<double> gen2(0);
	bm.run(std::string("counter ")+s, gen2, (double*)0, true);

	boost::mt19937 gen3;
	bm.run(std::string("boost rng ")+s, gen3, (double*)0, (void*)0);

	adder_generator gen4;
	bm.run(std::string("adder ")+s, gen4, (float*)0, (void*)0);

	auto gen5 = std::bind(std::plus<float>(),2.f,6.f);
	float test = gen5();
	bm.run(std::string("adder functional ")+s, gen5, (float*)0, (void*)0);

	adder_generator_state gen6;
	bm.run(std::string("adder state ")+s, gen6, (float*)0, true);

	return 0;
}





