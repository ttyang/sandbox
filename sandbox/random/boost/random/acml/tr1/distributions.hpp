// Copyright Fabian Bösch 2012
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 *  @file 
 *  @brief This file contains specializations for the variate_generator class template for TR1 random distribution classes and ACML engines.
 */

#ifndef BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPECIALIZATION_TR1_DISTRIBUTIONS_HPP
#define BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPECIALIZATION_TR1_DISTRIBUTIONS_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_TR1_RANDOM

#include "../variate_generator_specialization.hpp"
#include <tr1/random.hpp>

namespace boost {
namespace random {


// discrete distributions
// ----------------------

// discrete uniform distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_DISC_UNIFORM_TR1(
	std::tr1::uniform_int<long>,
	true,
	sranddiscreteuniform,
	BOOST_RANDOM_ACML_CONCAT( _dist.min(), _dist.max() ),
	_dist.a(), _dist.b()
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_DISC_UNIFORM_TR1(
	std::tr1::uniform_int<long>,
	false,
	dranddiscreteuniform,
	BOOST_RANDOM_ACML_CONCAT( _dist.min(), _dist.max() ),
	_dist.a(), _dist.b()
)

// binomial distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	BOOST_RANDOM_ACML_CONCAT(std::tr1::binomial_distribution<long, float>),
	true,
	srandbinomial,
	BOOST_RANDOM_ACML_CONCAT( _dist.t(), _dist.p() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	BOOST_RANDOM_ACML_CONCAT(std::tr1::binomial_distribution<long, double>),
	false,
	drandbinomial,
	BOOST_RANDOM_ACML_CONCAT( _dist.t(), _dist.p() )
)

// geometric distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	BOOST_RANDOM_ACML_CONCAT(std::tr1::geometric_distribution<long, float>),
	true,
	srandgeometric,
	_dist.p()
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	BOOST_RANDOM_ACML_CONCAT(std::tr1::geometric_distribution<long, double>),
	false,
	drandgeometric,
	_dist.p()
)

// poisson distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	BOOST_RANDOM_ACML_CONCAT(std::tr1::poisson_distribution<long, float>),
	true,
	srandpoisson,
	BOOST_RANDOM_ACML_CONCAT( _dist.mean(), _dist.mean() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	BOOST_RANDOM_ACML_CONCAT(std::tr1::poisson_distribution<long, double>),
	false,
	drandpoisson,
	BOOST_RANDOM_ACML_CONCAT( _dist.mean(), _dist.mean() )
)


// continuous distributions
// ----------------------

// exponential distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	std::tr1::exponential_distribution<float>,
	true,
	srandexponential,
	1.0f/_dist.lambda()
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	std::tr1::exponential_distribution<double>,
	false,
	drandexponential,
	1.0d/_dist.lambda()
)

// gamma distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	std::tr1::gamma_distribution<float>,
	true,
	srandgamma,
	BOOST_RANDOM_ACML_CONCAT( _dist.alpha(), 1.0f)
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	std::tr1::gamma_distribution<double>,
	false,
	drandgamma,
	BOOST_RANDOM_ACML_CONCAT( _dist.alpha(), 1.0d )
)

// normal distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	std::tr1::normal_distribution<float>,
	true,
	srandgaussian,
	BOOST_RANDOM_ACML_CONCAT( _dist.mean(), _dist.sigma()*_dist.sigma() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	std::tr1::normal_distribution<double>,
	false,
	drandgaussian,
	BOOST_RANDOM_ACML_CONCAT( _dist.mean(), _dist.sigma()*_dist.sigma() )
)

// continuous uniform distribution
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	std::tr1::uniform_real<float>,
	true,
	sranduniform,
	BOOST_RANDOM_ACML_CONCAT( _dist.min(), _dist.max() )
)
BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	std::tr1::uniform_real<double>,
	false,
	dranduniform,
	BOOST_RANDOM_ACML_CONCAT( _dist.min(), _dist.max() )
)

} // random
} // boost

#endif

#endif // BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPECIALIZATION_TR1_DISTRIBUTIONS_HPP

