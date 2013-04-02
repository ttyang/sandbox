// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 *  @file 
 *  @brief This file contains specializations for the variate_generator class template for Boost random distribution classes and ACML engines.
 */

#ifndef BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPECIALIZATION_BOOST_DISTRIBUTIONS_HPP
#define BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPECIALIZATION_BOOST_DISTRIBUTIONS_HPP

#include "../variate_generator_specialization.hpp"
#include <boost/random.hpp>

namespace boost {
namespace random {


// discrete distributions
// ----------------------

// discrete uniform distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_DISC_UNIFORM(
	boost::random::uniform_int_distribution<long>,
	true,
	sranddiscreteuniform,
	BOOST_RANDOM_ACML_CONCAT( _dist.a(), _dist.b() ),
	BOOST_RANDOM_ACML_CONCAT( value.a(), value.b() ),
	_dist.a(), _dist.b(), value.a(), value.b()
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_DISC_UNIFORM(
	boost::random::uniform_int_distribution<long>,
	false,
	dranddiscreteuniform,
	BOOST_RANDOM_ACML_CONCAT( _dist.a(), _dist.b() ),
	BOOST_RANDOM_ACML_CONCAT( value.a(), value.b() ),
	_dist.a(), _dist.b(), value.a(), value.b()
)

// binomial distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	BOOST_RANDOM_ACML_CONCAT(boost::random::binomial_distribution<long, float>),
	true,
	srandbinomial,
	BOOST_RANDOM_ACML_CONCAT( _dist.t(), _dist.p() ),
	BOOST_RANDOM_ACML_CONCAT( value.t(), value.p() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	BOOST_RANDOM_ACML_CONCAT(boost::random::binomial_distribution<long, double>),
	false,
	drandbinomial,
	BOOST_RANDOM_ACML_CONCAT( _dist.t(), _dist.p() ),
	BOOST_RANDOM_ACML_CONCAT( value.t(), value.p() )
)

// geometric distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	BOOST_RANDOM_ACML_CONCAT(boost::random::geometric_distribution<long, float>),
	true,
	srandgeometric,
	_dist.p(),
	value.p()
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	BOOST_RANDOM_ACML_CONCAT(boost::random::geometric_distribution<long, double>),
	false,
	drandgeometric,
	_dist.p(),
	value.p()
)

// negative binomial distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	BOOST_RANDOM_ACML_CONCAT(boost::random::negative_binomial_distribution<long, float>),
	true,
	srandnegativebinomial,
	BOOST_RANDOM_ACML_CONCAT( _dist.k(), _dist.p() ),
	BOOST_RANDOM_ACML_CONCAT( value.k(), value.p() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	BOOST_RANDOM_ACML_CONCAT(boost::random::negative_binomial_distribution<long, double>),
	false,
	drandnegativebinomial,
	BOOST_RANDOM_ACML_CONCAT( _dist.k(), _dist.p() ),
	BOOST_RANDOM_ACML_CONCAT( value.k(), value.p() )
)

// poisson distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	BOOST_RANDOM_ACML_CONCAT(boost::random::poisson_distribution<long, float>),
	true,
	srandpoisson,
	BOOST_RANDOM_ACML_CONCAT( _dist.mean(), _dist.mean() ),
	BOOST_RANDOM_ACML_CONCAT( value.mean(), value.mean() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	BOOST_RANDOM_ACML_CONCAT(boost::random::poisson_distribution<long, double>),
	false,
	drandpoisson,
	BOOST_RANDOM_ACML_CONCAT( _dist.mean(), _dist.mean() ),
	BOOST_RANDOM_ACML_CONCAT( value.mean(), value.mean() )
)


// continuous distributions
// ----------------------

// cauchy distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	boost::random::cauchy_distribution<float>,
	true,
	srandcauchy,
	BOOST_RANDOM_ACML_CONCAT( _dist.a(), _dist.b() ),
	BOOST_RANDOM_ACML_CONCAT( value.a(), value.b() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	boost::random::cauchy_distribution<double>,
	false,
	drandcauchy,
	BOOST_RANDOM_ACML_CONCAT( _dist.a(), _dist.b() ),
	BOOST_RANDOM_ACML_CONCAT( value.a(), value.b() )
)

// chi-squared distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	boost::random::chi_squared_distribution<float>,
	true,
	srandchisquared,
	_dist.n(),
	value.n()
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	boost::random::chi_squared_distribution<double>,
	false,
	drandchisquared,
	_dist.n(),
	value.n()
)

// exponential distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	boost::random::exponential_distribution<float>,
	true,
	srandexponential,
	1.0f/_dist.lambda(),
	1.0f/value.lambda()
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	boost::random::exponential_distribution<double>,
	false,
	drandexponential,
	1.0d/_dist.lambda(),
	1.0d/value.lambda()
)

// F distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	boost::random::fisher_f_distribution<float>,
	true,
	srandf,
	BOOST_RANDOM_ACML_CONCAT( _dist.m(), _dist.n() ),
	BOOST_RANDOM_ACML_CONCAT( value.m(), value.n() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	boost::random::fisher_f_distribution<double>,
	false,
	drandf,
	BOOST_RANDOM_ACML_CONCAT( _dist.m(), _dist.n() ),
	BOOST_RANDOM_ACML_CONCAT( value.m(), value.n() )
)

// gamma distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	boost::random::gamma_distribution<float>,
	true,
	srandgamma,
	BOOST_RANDOM_ACML_CONCAT( _dist.alpha(), _dist.beta() ),
	BOOST_RANDOM_ACML_CONCAT( value.alpha(), value.beta() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	boost::random::gamma_distribution<double>,
	false,
	drandgamma,
	BOOST_RANDOM_ACML_CONCAT( _dist.alpha(), _dist.beta() ),
	BOOST_RANDOM_ACML_CONCAT( value.alpha(), value.beta() )
)

// normal distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	boost::random::normal_distribution<float>,
	true,
	srandgaussian,
	BOOST_RANDOM_ACML_CONCAT( _dist.mean(), _dist.sigma()*_dist.sigma() ),
	BOOST_RANDOM_ACML_CONCAT( value.mean(), value.sigma()*value.sigma() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	boost::random::normal_distribution<double>,
	false,
	drandgaussian,
	BOOST_RANDOM_ACML_CONCAT( _dist.mean(), _dist.sigma()*_dist.sigma() ),
	BOOST_RANDOM_ACML_CONCAT( value.mean(), value.sigma()*value.sigma() )
)

// lognormal distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	boost::random::lognormal_distribution<float>,
	true,
	srandlognormal,
	BOOST_RANDOM_ACML_CONCAT( _dist.m(), _dist.s()*_dist.s() ),
	BOOST_RANDOM_ACML_CONCAT( value.m(), value.s()*value.s() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	boost::random::lognormal_distribution<double>,
	false,
	drandlognormal,
	BOOST_RANDOM_ACML_CONCAT( _dist.m(), _dist.s()*_dist.s() ),
	BOOST_RANDOM_ACML_CONCAT( value.m(), value.s()*value.s() )
)

// sudent t distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	boost::random::student_t_distribution<float>,
	true,
	srandstudentst,
	_dist.n(),
	value.n()
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	boost::random::student_t_distribution<double>,
	false,
	drandstudentst,
	_dist.n(),
	value.n()
)

// continuous uniform distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	boost::random::uniform_real_distribution<float>,
	true,
	sranduniform,
	BOOST_RANDOM_ACML_CONCAT( _dist.a(), _dist.b() ),
	BOOST_RANDOM_ACML_CONCAT( value.a(), value.b() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	boost::random::uniform_real_distribution<double>,
	false,
	dranduniform,
	BOOST_RANDOM_ACML_CONCAT( _dist.a(), _dist.b() ),
	BOOST_RANDOM_ACML_CONCAT( value.a(), value.b() )
)

// weibull distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	boost::random::weibull_distribution<float>,
	true,
	srandweibull,
	BOOST_RANDOM_ACML_CONCAT( _dist.a(), _dist.b() ),
	BOOST_RANDOM_ACML_CONCAT( value.a(), value.b() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(
	boost::random::weibull_distribution<double>,
	false,
	drandweibull,
	BOOST_RANDOM_ACML_CONCAT( _dist.a(), _dist.b() ),
	BOOST_RANDOM_ACML_CONCAT( value.a(), value.b() )
)

} // random
} // boost

#endif // BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPECIALIZATION_BOOST_DISTRIBUTIONS_HPP

