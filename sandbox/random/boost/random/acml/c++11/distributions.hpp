// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 *  @file 
 *  @brief This file contains specializations for the variate_generator class template for c++11 random distribution classes and ACML engines.
 */

#ifndef BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPECIALIZATION_0X_DISTRIBUTIONS_HPP
#define BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPECIALIZATION_0X_DISTRIBUTIONS_HPP

#include <boost/config.hpp>
#ifndef BOOST_NO_CXX11_HDR_RANDOM

#include "../variate_generator_specialization.hpp"
#include <random>

namespace boost {
namespace random {

// discrete distributions
// ----------------------

// discrete uniform distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_DISC_UNIFORM(
	std::uniform_int_distribution<long>,
	true,
	sranddiscreteuniform,
	BOOST_RANDOM_ACML_CONCAT( _dist.a(), _dist.b() ),
	BOOST_RANDOM_ACML_CONCAT( value.a(), value.b() ),
	_dist.a(), _dist.b(), value.a(), value.b()
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_DISC_UNIFORM(
	std::uniform_int_distribution<long>,
	false,
	dranddiscreteuniform,
	BOOST_RANDOM_ACML_CONCAT( _dist.a(), _dist.b() ),
	BOOST_RANDOM_ACML_CONCAT( value.a(), value.b() ),
	_dist.a(), _dist.b(), value.a(), value.b()
)

// binomial distribution
#if ((defined (__GLIBCXX__) && __GLIBCXX__ >= 20120906) || (! (defined (__GLIBCXX__)))  )
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::binomial_distribution<long>,
	true,
	srandbinomial,
	BOOST_RANDOM_ACML_CONCAT( _dist.t(), _dist.p() ),
	BOOST_RANDOM_ACML_CONCAT( value.t(), value.p() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::binomial_distribution<long>,
	false,
	drandbinomial,
	BOOST_RANDOM_ACML_CONCAT( _dist.t(), _dist.p() ),
	BOOST_RANDOM_ACML_CONCAT( value.t(), value.p() )
)
#endif

// geometric distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::geometric_distribution<long>,
	true,
	srandgeometric,
	_dist.p(),
	value.p()
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::geometric_distribution<long>,
	false,
	drandgeometric,
	_dist.p(),
	value.p()
)

// negative binomial distribution
#if ((defined (__GLIBCXX__) && __GLIBCXX__ >= 20120906) || (! (defined (__GLIBCXX__)))  )
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::negative_binomial_distribution<long>,
	true,
	srandnegativebinomial,
	BOOST_RANDOM_ACML_CONCAT( _dist.k(), _dist.p() ),
	BOOST_RANDOM_ACML_CONCAT( value.k(), value.p() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::negative_binomial_distribution<long>,
	false,
	drandnegativebinomial,
	BOOST_RANDOM_ACML_CONCAT( _dist.k(), _dist.p() ),
	BOOST_RANDOM_ACML_CONCAT( value.k(), value.p() )
)
#endif

// poisson distribution
#if ((defined (__GLIBCXX__) && __GLIBCXX__ >= 20120906) || (! (defined (__GLIBCXX__)))  )
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::poisson_distribution<long>,
	true,
	srandpoisson,
	BOOST_RANDOM_ACML_CONCAT( _dist.mean(), _dist.mean() ),
	BOOST_RANDOM_ACML_CONCAT( value.mean(), value.mean() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::poisson_distribution<long>,
	false,
	drandpoisson,
	BOOST_RANDOM_ACML_CONCAT( _dist.mean(), _dist.mean() ),
	BOOST_RANDOM_ACML_CONCAT( value.mean(), value.mean() )
)
#endif


// continuous distributions
// ----------------------

// cauchy distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::cauchy_distribution<float>,
	true,
	srandcauchy,
	BOOST_RANDOM_ACML_CONCAT( _dist.a(), _dist.b() ),
	BOOST_RANDOM_ACML_CONCAT( value.a(), value.b() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::cauchy_distribution<double>,
	false,
	drandcauchy,
	BOOST_RANDOM_ACML_CONCAT( _dist.a(), _dist.b() ),
	BOOST_RANDOM_ACML_CONCAT( value.a(), value.b() )
)

// chi-squared distribution
#if ((defined (__GLIBCXX__) && __GLIBCXX__ >= 20120906) || (! (defined (__GLIBCXX__)))  )
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::chi_squared_distribution<float>,
	true,
	srandchisquared,
	_dist.n(),
	value.n()
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::chi_squared_distribution<double>,
	false,
	drandchisquared,
	_dist.n(),
	value.n()
)
#endif

// exponential distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::exponential_distribution<float>,
	true,
	srandexponential,
	1.0f/_dist.lambda(),
	1.0f/value.lambda()
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::exponential_distribution<double>,
	false,
	drandexponential,
	1.0d/_dist.lambda(),
	1.0d/value.lambda()
)

// F distribution
#if ((defined (__GLIBCXX__) && __GLIBCXX__ >= 20120906) || (! (defined (__GLIBCXX__)))  )
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::fisher_f_distribution<float>,
	true,
	srandf,
	BOOST_RANDOM_ACML_CONCAT( _dist.m(), _dist.n() ),
	BOOST_RANDOM_ACML_CONCAT( value.m(), value.n() )
)
#endif
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::fisher_f_distribution<double>,
	false,
	drandf,
	BOOST_RANDOM_ACML_CONCAT( _dist.m(), _dist.n() ),
	BOOST_RANDOM_ACML_CONCAT( value.m(), value.n() )
)

// gamma distribution
#if ((defined (__GLIBCXX__) && __GLIBCXX__ >= 20120906) || (! (defined (__GLIBCXX__)))  )
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::gamma_distribution<float>,
	true,
	srandgamma,
	BOOST_RANDOM_ACML_CONCAT( _dist.alpha(), _dist.beta() ),
	BOOST_RANDOM_ACML_CONCAT( value.alpha(), value.beta() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::gamma_distribution<double>,
	false,
	drandgamma,
	BOOST_RANDOM_ACML_CONCAT( _dist.alpha(), _dist.beta() ),
	BOOST_RANDOM_ACML_CONCAT( value.alpha(), value.beta() )
)
#endif

// normal distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::normal_distribution<float>,
	true,
	srandgaussian,
	BOOST_RANDOM_ACML_CONCAT( _dist.mean(), _dist.stddev()*_dist.stddev() ),
	BOOST_RANDOM_ACML_CONCAT( value.mean(), value.stddev()*value.stddev() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::normal_distribution<double>,
	false,
	drandgaussian,
	BOOST_RANDOM_ACML_CONCAT( _dist.mean(), _dist.stddev()*_dist.stddev() ),
	BOOST_RANDOM_ACML_CONCAT( value.mean(), value.stddev()*value.stddev() )
)

// lognormal distribution
#if ((defined (__GLIBCXX__) && __GLIBCXX__ >= 20120906) || (! (defined (__GLIBCXX__)))  )
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::lognormal_distribution<float>,
	true,
	srandlognormal,
	BOOST_RANDOM_ACML_CONCAT( _dist.m(), _dist.s()*_dist.s() ),
	BOOST_RANDOM_ACML_CONCAT( value.m(), value.s()*value.s() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::lognormal_distribution<double>,
	false,
	drandlognormal,
	BOOST_RANDOM_ACML_CONCAT( _dist.m(), _dist.s()*_dist.s() ),
	BOOST_RANDOM_ACML_CONCAT( value.m(), value.s()*value.s() )
)
#endif

// sudent t distribution
#if ((defined (__GLIBCXX__) && __GLIBCXX__ >= 20120906) || (! (defined (__GLIBCXX__)))  )
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::student_t_distribution<float>,
	true,
	srandstudentst,
	_dist.n(),
	value.n()
)
#endif
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::student_t_distribution<double>,
	false,
	drandstudentst,
	_dist.n(),
	value.n()
)

// continuous uniform distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::uniform_real_distribution<float>,
	true,
	sranduniform,
	BOOST_RANDOM_ACML_CONCAT( _dist.a(), _dist.b() ),
	BOOST_RANDOM_ACML_CONCAT( value.a(), value.b() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::uniform_real_distribution<double>,
	false,
	dranduniform,
	BOOST_RANDOM_ACML_CONCAT( _dist.a(), _dist.b() ),
	BOOST_RANDOM_ACML_CONCAT( value.a(), value.b() )
)

// weibull distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::weibull_distribution<float>,
	true,
	srandweibull,
	BOOST_RANDOM_ACML_CONCAT( _dist.a(), _dist.b() ),
	BOOST_RANDOM_ACML_CONCAT( value.a(), value.b() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	std::weibull_distribution<double>,
	false,
	drandweibull,
	BOOST_RANDOM_ACML_CONCAT( _dist.a(), _dist.b() ),
	BOOST_RANDOM_ACML_CONCAT( value.a(), value.b() )
)

} // random
} // boost

#endif

#endif // BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPECIALIZATION_0X_DISTRIBUTIONS_HPP

