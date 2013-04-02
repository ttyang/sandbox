// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "benchmark.hpp"


template<class Engine>
inline void raw_acml_uniform_real_distribution(Engine& engine, std::size_t n, double* data)
{
	long info;
	dranduniform(static_cast<long>(n),0,10,&(engine.state()[0]),data,&info);
}

template<class Engine>
inline void raw_acml_normal_distribution(Engine& engine, std::size_t n, double* data)
{
	long info;
	drandgaussian(static_cast<long>(n),0,1,&(engine.state()[0]),data,&info);
}

template<class Engine>
inline void raw_acml_exponential_distribution(Engine& engine, std::size_t n, double* data)
{
	long info;
	drandexponential(static_cast<long>(n),1,&(engine.state()[0]),data,&info);
}

template<class Engine>
inline void raw_mkl_uniform_real_distribution(Engine& engine, std::size_t n, double* data)
{
	vdRngUniform( VSL_RNG_METHOD_UNIFORM_STD, engine.get_stream(), n, data, 0, 10 );
}

template<class Engine>
inline void raw_mkl_normal_distribution(Engine& engine, std::size_t n, double* data)
{
	vdRngGaussian( VSL_RNG_METHOD_GAUSSIAN_BOXMULLER2, engine.get_stream(), n, data, 0, 1 );
}

template<class Engine>
inline void raw_mkl_exponential_distribution(Engine& engine, std::size_t n, double* data)
{
	vdRngExponential( VSL_RNG_METHOD_EXPONENTIAL_ICDF, engine.get_stream(), n, data, 0, 1 );
}



int main()
{
	benchmark bm{1000, 10000, 100000};//, 1000000, 10000000};
	
	typedef typename boost::random::acml::mt19937 acml_engine_t;		
	typedef typename boost::random::mkl::mt19937 mkl_engine_t;		
	acml_engine_t acml_engine;
	mkl_engine_t mkl_engine;
	std::mt19937 std_engine;
	boost::random::mt19937 boost_engine;

	std::string acml_engine_str("boost::random::acml::mt19937");
	std::string mkl_engine_str("boost::random::mkl::mt19937");
	std::string boost_engine_str("boost::random::mt19937");
	std::string std_engine_str("std::mt19937");
	
	{
		std::string title("Uniform real distribution with Mersenne Twister 19937");
		std::string boost_distribution_str("boost::random::uniform_real_distribution<double>");
		std::string std_distribution_str("std::uniform_real_distribution<double>");
		std::uniform_real_distribution<double> std_distribution(0,10);
		boost::random::uniform_real_distribution<double> boost_distribution(0,10);
		bm.run(title, 
		       acml_engine, acml_engine_str,
		       mkl_engine, mkl_engine_str,
		       std_engine, std_engine_str,
		       boost_engine, boost_engine_str,
		       std_distribution, std_distribution_str,
		       boost_distribution, boost_distribution_str,
		       &raw_acml_uniform_real_distribution<acml_engine_t>, &raw_mkl_uniform_real_distribution<mkl_engine_t>);
	}

	{
		std::string title("Normal distribution with Mersenne Twister 19937");
		std::string boost_distribution_str("boost::random::normal_distribution<double>");
		std::string std_distribution_str("std::normal_distribution<double>");
		std::normal_distribution<double> std_distribution(0,1);
		boost::random::normal_distribution<double> boost_distribution(0,1);
		bm.run(title, 
		       acml_engine, acml_engine_str,
		       mkl_engine, mkl_engine_str,
		       std_engine, std_engine_str,
		       boost_engine, boost_engine_str,
		       std_distribution, std_distribution_str,
		       boost_distribution, boost_distribution_str, 
		       &raw_acml_normal_distribution<acml_engine_t>, &raw_mkl_normal_distribution<mkl_engine_t>);
	}

	{
		std::string title("Exponential distribution with Mersenne Twister 19937");
		std::string boost_distribution_str("boost::random::exponential_distribution<double>");
		std::string std_distribution_str("std::exponential_distribution<double>");
		std::exponential_distribution<double> std_distribution(1);
		boost::random::exponential_distribution<double> boost_distribution(1);
		bm.run(title, 
		       acml_engine, acml_engine_str,
		       mkl_engine, mkl_engine_str,
		       std_engine, std_engine_str,
		       boost_engine, boost_engine_str,
		       std_distribution, std_distribution_str,
		       boost_distribution, boost_distribution_str,
		       &raw_acml_exponential_distribution<acml_engine_t>, &raw_mkl_exponential_distribution<mkl_engine_t>);
	}

}

