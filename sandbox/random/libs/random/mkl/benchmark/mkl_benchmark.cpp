// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/random/mkl/engine.hpp>
#include <boost/random/mkl/c++11/distributions.hpp>
#include <boost/random/mkl/boost/distributions.hpp>
#include "../../acml/benchmark/benchmark.hpp"

template<class Engine>
inline void raw_uniform_int_distribution(Engine& engine, std::size_t n, int* data)
{
	viRngUniform( VSL_RNG_METHOD_UNIFORM_STD, engine.get_stream(), n, data, 0, 10 );
}

template<class Engine>
inline void raw_uniform_real_distribution(Engine& engine, std::size_t n, double* data)
{
	vdRngUniform( VSL_RNG_METHOD_UNIFORM_STD, engine.get_stream(), n, data, 0, 10 );
}

template<class Engine>
inline void raw_normal_distribution(Engine& engine, std::size_t n, double* data)
{
	vdRngGaussian( VSL_RNG_METHOD_GAUSSIAN_BOXMULLER2, engine.get_stream(), n, data, 0, 1 );
}

template<class Engine>
inline void raw_exponential_distribution(Engine& engine, std::size_t n, double* data)
{
	vdRngExponential( VSL_RNG_METHOD_EXPONENTIAL_ICDF, engine.get_stream(), n, data, 0, 1 );
}

int main()
{
	benchmark bm{1000, 10000, 100000, 1000000, 10000000};
	
	typedef typename boost::random::mkl::mt19937 engine_t;		
	engine_t engine;
	std::mt19937 std_engine;
	boost::random::mt11213b boost_engine;

	{
		std::string title("Uniform int distribution with Mersenne Twister");
		std::uniform_int_distribution<int> std_distribution(0,10);
		boost::random::uniform_int_distribution<int> boost_distribution(0,10);
		bm.run(title, engine, std_engine, boost_engine, std_distribution, boost_distribution, &raw_uniform_int_distribution<engine_t>);
	}

	{
		std::string title("Uniform real distribution with Mersenne Twister");
		std::uniform_real_distribution<double> std_distribution(0,10);
		boost::random::uniform_real_distribution<double> boost_distribution(0,10);
		bm.run(title, engine, std_engine, boost_engine, std_distribution, boost_distribution, &raw_uniform_real_distribution<engine_t>);
	}
	
	{
		std::string title("Normal distribution with Mersenne Twister");
		std::normal_distribution<double> std_distribution(0,1);
		boost::random::normal_distribution<double> boost_distribution(0,1);
		bm.run(title, engine, std_engine, boost_engine, std_distribution, boost_distribution, &raw_normal_distribution<engine_t>);
	}

	{
		std::string title("Exponential distribution with Mersenne Twister");
		std::exponential_distribution<double> std_distribution(1);
		boost::random::exponential_distribution<double> boost_distribution(1);
		bm.run(title, engine, std_engine, boost_engine, std_distribution, boost_distribution, &raw_exponential_distribution<engine_t>);
	}
}

