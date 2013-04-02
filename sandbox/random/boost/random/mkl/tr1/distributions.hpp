// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 *  @file 
 *  @brief This file contains specializations for the variate_generator class template for TR1 random distribution classes and MKL engines.
 */

#ifndef BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPECIALIZATION_TR1_DISTRIBUTIONS_HPP
#define BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPECIALIZATION_TR1_DISTRIBUTIONS_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_TR1_RANDOM

#include "../variate_generator_specialization.hpp"
#include <tr1/random.h>
#include <limits>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

namespace boost {
namespace random {

// discrete uniform distribution
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_DISC_UNIFORM_TR1(
	std::tr1::uniform_int<int>,
	viRngUniform,
	VSL_RNG_METHOD_UNIFORM_STD,
	BOOST_RANDOM_MKL_CONCAT( _dist.min(), _dist.max()), 
	_dist.max()
)

// continuous uniform distribution
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	std::tr1::uniform_real<float>,
	vsRngUniform,
	VSL_RNG_METHOD_UNIFORM_STD,
	BOOST_RANDOM_MKL_CONCAT( _dist.min(), _dist.max() )
)
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	std::tr1::uniform_real<double>,
	vdRngUniform,
	VSL_RNG_METHOD_UNIFORM_STD,
	BOOST_RANDOM_MKL_CONCAT( _dist.min(), _dist.max() )
)

// bernoulli distribution
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_TR1_2(
	std::tr1::bernoulli_distribution,
	viRngBernoulli,
	VSL_RNG_METHOD_BERNOULLI_ICDF,
	_dist.p(),
	int
)

// binomial distribution
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	BOOST_RANDOM_MKL_CONCAT(std::tr1::binomial_distribution<int, double>),
	viRngBinomial,
	VSL_RNG_METHOD_BINOMIAL_BTPE,
	BOOST_RANDOM_MKL_CONCAT( _dist.t(), _dist.p() )
)

// geometric distribution
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	BOOST_RANDOM_MKL_CONCAT(std::tr1::geometric_distribution<int, double>),
	viRngGeometric,
	VSL_RNG_METHOD_GEOMETRIC_ICDF,
	_dist.p() 
)

// poisson distribution
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	BOOST_RANDOM_MKL_CONCAT(std::tr1::poisson_distribution<int, double>),
	viRngPoisson,
	VSL_RNG_METHOD_POISSON_POISNORM,
	_dist.mean() 
)

// exponential distribution
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	std::tr1::exponential_distribution<float>,
	vsRngExponential,
	VSL_RNG_METHOD_EXPONENTIAL_ICDF,
	BOOST_RANDOM_MKL_CONCAT( 0, 1/_dist.lambda() )
)
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	std::tr1::exponential_distribution<double>,
	vdRngExponential,
	VSL_RNG_METHOD_EXPONENTIAL_ICDF,
	BOOST_RANDOM_MKL_CONCAT( 0, 1/_dist.lambda() )
)

// gamma distribution
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	std::tr1::gamma_distribution<float>,
	vsRngGamma,
	VSL_RNG_METHOD_GAMMA_GNORM,
	BOOST_RANDOM_MKL_CONCAT( _dist.alpha(), 0, 1 )
) 
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	std::tr1::gamma_distribution<double>,
	vdRngGamma,
	VSL_RNG_METHOD_GAMMA_GNORM,
	BOOST_RANDOM_MKL_CONCAT( _dist.alpha(), 0, 1 )
)

// normal distribution
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	std::tr1::normal_distribution<float>,
	vsRngGaussian,
	VSL_RNG_METHOD_GAUSSIAN_BOXMULLER2,
	BOOST_RANDOM_MKL_CONCAT( _dist.mean(), _dist.sigma() )
)
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_TR1(
	std::tr1::normal_distribution<double>,
	vdRngGaussian,
	VSL_RNG_METHOD_GAUSSIAN_BOXMULLER2,
	BOOST_RANDOM_MKL_CONCAT( _dist.mean(), _dist.sigma() ) 
)

} // random
} // boost

#endif // DOXYGEN_SHOULD_SKIP_THIS

#endif // BOOST_HAS_TR1_RANDOM

#endif // BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPECIALIZATION_TR1_DISTRIBUTIONS_HPP

