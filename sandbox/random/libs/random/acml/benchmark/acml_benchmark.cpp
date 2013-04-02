// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "benchmark.hpp"

template<class Engine>
inline void raw_uniform_int_distribution(Engine& engine, std::size_t n, long* data)
{
	long info;
	dranddiscreteuniform(static_cast<long>(n),0,10,&(engine.state()[0]),data,&info);
}


template<class Engine>
inline void raw_uniform_real_distribution(Engine& engine, std::size_t n, double* data)
{
	long info;
	dranduniform(static_cast<long>(n),0,10,&(engine.state()[0]),data,&info);
}

template<class Engine>
inline void raw_normal_distribution(Engine& engine, std::size_t n, double* data)
{
	long info;
	drandgaussian(static_cast<long>(n),0,1,&(engine.state()[0]),data,&info);
}

template<class Engine>
inline void raw_exponential_distribution(Engine& engine, std::size_t n, double* data)
{
	long info;
	drandexponential(static_cast<long>(n),1,&(engine.state()[0]),data,&info);

}

int main()
{
	benchmark bm{1000, 10000, 100000, 1000000, 10000000};
	
	typedef typename boost::random::acml::mt19937 engine_t;		
	engine_t engine;
	std::mt19937 std_engine;
	boost::random::mt11213b boost_engine;

	{
		std::string title("Uniform int distribution with Mersenne Twister");
		std::uniform_int_distribution<long> std_distribution(0,10);
		boost::random::uniform_int_distribution<long> boost_distribution(0,10);
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
