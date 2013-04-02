// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 *  @file 
 *  @brief This file contains specializations for the variate_generator class template for c++11 random distribution classes and MKL engines.
 */

#ifndef BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPECIALIZATION_0X_DISTRIBUTIONS_HPP
#define BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPECIALIZATION_0X_DISTRIBUTIONS_HPP

#include <boost/config.hpp>
#ifndef BOOST_NO_CXX11_HDR_RANDOM

#include "../variate_generator_specialization.hpp"
#include <random>
#include <limits>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

namespace boost {
namespace random {

// discrete uniform distribution
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_DISC_UNIFORM(
	std::uniform_int_distribution<int>,
	viRngUniform,
	VSL_RNG_METHOD_UNIFORM_STD,
	BOOST_RANDOM_MKL_CONCAT( _dist.a(), _dist.b() /*(_dist.b()<std::numeric_limits<int>::max() ? _dist.b()+1 : _dist.b())*/ ), 
	BOOST_RANDOM_MKL_CONCAT( value.a(), value.b() /*(value.b()<std::numeric_limits<int>::max() ? value.b()+1 : value.b())*/ ),
	_dist.b(),
	value.b() 
)

// continuous uniform distribution
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION(
	std::uniform_real_distribution<float>,
	vsRngUniform,
	VSL_RNG_METHOD_UNIFORM_STD,
	BOOST_RANDOM_MKL_CONCAT( _dist.a(), _dist.b() ), 
	BOOST_RANDOM_MKL_CONCAT( value.a(), value.b() )
)
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION(
	std::uniform_real_distribution<double>,
	vdRngUniform,
	VSL_RNG_METHOD_UNIFORM_STD,
	BOOST_RANDOM_MKL_CONCAT( _dist.a(), _dist.b() ), 
	BOOST_RANDOM_MKL_CONCAT( value.a(), value.b() )
)

// bernoulli distribution
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_2(
	std::bernoulli_distribution,
	viRngBernoulli,
	VSL_RNG_METHOD_BERNOULLI_ICDF,
	_dist.p(), 
	value.p(),
	int
)

// binomial distribution
//#if (defined (__GLIBCXX__) && __GLIBCXX__ >= 20120906 || ! defined (__GLIBCXX__)  )
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION(
	std::binomial_distribution<int>,
	viRngBinomial,
	VSL_RNG_METHOD_BINOMIAL_BTPE,
	BOOST_RANDOM_MKL_CONCAT( _dist.t(), _dist.p() ), 
	BOOST_RANDOM_MKL_CONCAT( value.t(), value.p() )
)
//#endif 

// geometric distribution
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION(
	std::geometric_distribution<int>,
	viRngGeometric,
	VSL_RNG_METHOD_GEOMETRIC_ICDF,
	_dist.p(), 
	value.p() 
)

// negative binomial distribution
//#if (defined (__GLIBCXX__) && __GLIBCXX__ >= 20120906 || ! defined (__GLIBCXX__)  )
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION(
	std::negative_binomial_distribution<int>,
	viRngNegbinomial,
	VSL_RNG_METHOD_NEGBINOMIAL_NBAR,
	BOOST_RANDOM_MKL_CONCAT( _dist.k(), _dist.p() ), 
	BOOST_RANDOM_MKL_CONCAT( value.k(), value.p() )
)
//#endif

// poisson distribution
//#if ( (defined (__GLIBCXX__) && __GLIBCXX__ >= 20120906) || ! defined (__GLIBCXX__) )
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION(
	std::poisson_distribution<int>,
	viRngPoisson,
	VSL_RNG_METHOD_POISSON_POISNORM,
	_dist.mean(),
	value.mean() 
)
//#endif

// exponential distribution
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION(
	std::exponential_distribution<float>,
	vsRngExponential,
	VSL_RNG_METHOD_EXPONENTIAL_ICDF,
	BOOST_RANDOM_MKL_CONCAT( 0, 1/_dist.lambda() ),
	BOOST_RANDOM_MKL_CONCAT( 0,  1/value.lambda() )
)
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION(
	std::exponential_distribution<double>,
	vdRngExponential,
	VSL_RNG_METHOD_EXPONENTIAL_ICDF,
	BOOST_RANDOM_MKL_CONCAT( 0, 1/_dist.lambda() ),
	BOOST_RANDOM_MKL_CONCAT( 0,  1/value.lambda() )
)

// gamma distribution
#if ((defined (__GLIBCXX__) && __GLIBCXX__ >= 20120906) || (! (defined (__GLIBCXX__)))  )
// Does not work! Bug in the std library!!
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION(
	std::gamma_distribution<float>,
	vsRngGamma,
	VSL_RNG_METHOD_GAMMA_GNORM,
	BOOST_RANDOM_MKL_CONCAT( _dist.alpha(), 0, _dist.beta() ), 
	BOOST_RANDOM_MKL_CONCAT( value.alpha(), 0, value.beta() )
) 
#endif

BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION(
	std::gamma_distribution<double>,
	vdRngGamma,
	VSL_RNG_METHOD_GAMMA_GNORM,
	BOOST_RANDOM_MKL_CONCAT( _dist.alpha(), 0, _dist.beta() ), 
	BOOST_RANDOM_MKL_CONCAT( value.alpha(), 0, value.beta() )
)

// weibull distribution
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION(
	std::weibull_distribution<float>,
	vsRngWeibull,
	VSL_RNG_METHOD_WEIBULL_ICDF,
	BOOST_RANDOM_MKL_CONCAT( _dist.a(), 0, _dist.b() ),
	BOOST_RANDOM_MKL_CONCAT( value.a(), 0, value.b() )
)
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION(
	std::weibull_distribution<double>,
	vdRngWeibull,
	VSL_RNG_METHOD_WEIBULL_ICDF,
	BOOST_RANDOM_MKL_CONCAT( _dist.a(), 0, _dist.b() ),
	BOOST_RANDOM_MKL_CONCAT( value.a(), 0, value.b() )
)

// extreme value / gumbel distribution
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION(
	std::extreme_value_distribution<float>,
	vsRngGumbel,
	VSL_RNG_METHOD_GUMBEL_ICDF,
	BOOST_RANDOM_MKL_CONCAT( _dist.a(), _dist.b() ),
	BOOST_RANDOM_MKL_CONCAT( value.a(), value.b() )
)
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION(
	std::extreme_value_distribution<double>,
	vdRngGumbel,
	VSL_RNG_METHOD_GUMBEL_ICDF,
	BOOST_RANDOM_MKL_CONCAT( _dist.a(), _dist.b() ),
	BOOST_RANDOM_MKL_CONCAT( value.a(), value.b() )
)

// normal distribution
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION(
	std::normal_distribution<float>,
	vsRngGaussian,
	VSL_RNG_METHOD_GAUSSIAN_BOXMULLER2,
	BOOST_RANDOM_MKL_CONCAT( _dist.mean(), _dist.stddev() ), 
	BOOST_RANDOM_MKL_CONCAT( value.mean(), value.stddev() )
)
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION(
	std::normal_distribution<double>,
	vdRngGaussian,
	VSL_RNG_METHOD_GAUSSIAN_BOXMULLER2,
	BOOST_RANDOM_MKL_CONCAT( _dist.mean(), _dist.stddev() ),
	BOOST_RANDOM_MKL_CONCAT( value.mean(), value.stddev() ) 
)

// lognormal distribution
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION(
	std::lognormal_distribution<float>,
	vsRngLognormal,
	VSL_RNG_METHOD_LOGNORMAL_BOXMULLER2,
	BOOST_RANDOM_MKL_CONCAT( _dist.m(), _dist.s(), 0, 1 ), 
	BOOST_RANDOM_MKL_CONCAT( value.m(), value.s(), 0, 1 )
)
#if (defined (__GLIBCXX__) && __GLIBCXX__ >= 20120906 || ! defined (__GLIBCXX__)  )
// Does not work! Bug in the std library!!
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION(
	std::lognormal_distribution<double>,
	vdRngLognormal, 
	VSL_RNG_METHOD_LOGNORMAL_BOXMULLER2,
	BOOST_RANDOM_MKL_CONCAT( _dist.m(), _dist.s(), 0, 1 ), 
	BOOST_RANDOM_MKL_CONCAT( value.m(), value.s(), 0, 1 )
)
#endif

// cauchy distribution
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION(
	std::cauchy_distribution<float>,
	vsRngCauchy,
	VSL_RNG_METHOD_CAUCHY_ICDF,
	BOOST_RANDOM_MKL_CONCAT( _dist.a(), _dist.b() ),
	BOOST_RANDOM_MKL_CONCAT( value.a(), value.b() )
)
BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION(
	std::cauchy_distribution<double>,
	vdRngCauchy,
	VSL_RNG_METHOD_CAUCHY_ICDF,
	BOOST_RANDOM_MKL_CONCAT( _dist.a(), _dist.b() ), 
	BOOST_RANDOM_MKL_CONCAT( value.a(), value.b() )
)

} // random
} // boost

#endif // DOXYGEN_SHOULD_SKIP_THIS

#endif // BOOST_NO_CXX11_HDR_RANDOM

#endif // BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPECIALIZATION_0X_DISTRIBUTIONS_HPP

