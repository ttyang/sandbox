// Copyright Fabian Bösch 2013
//
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RANDOM_ACML_TEST_TEST_BOOST_DISTRIBUTIONS_HPP
#define BOOST_RANDOM_ACML_TEST_TEST_BOOST_DISTRIBUTIONS_HPP

#include <boost/random.hpp>
#include <boost/random/mkl/variate_generator_specialization_boost_distributions.hpp>
//#include <boost/random/acml/variate_generator_boost_distributions.hpp>
#include "test_statistics.hpp"


namespace boost {
namespace random {
namespace acml {
namespace test {


// discrete uniform distribution
template <class URNG, class URNG2>
void test_boost_uniform_int_distribution(std::size_t n, URNG& urng, URNG2& urng2)
{
	/*boost::random::uniform_int_distribution<int> dist1(0,10);
	test_statistic_properties(n, urng, urng2, dist1);	

	boost::random::uniform_int_distribution<int> dist2(0,1);
	test_statistic_properties(n, urng, urng2, dist2);	

	boost::random::uniform_int_distribution<int> dist3(std::numeric_limits<int>::min(),std::numeric_limits<int>::max());
	test_statistic_properties(n, urng, urng2, dist3);		*/
}

// continuous uniform distribution
template <class URNG, class URNG2>
void test_boost_uniform_real_distribution(std::size_t n, URNG& urng, URNG2& urng2)
{
	/*boost::random::uniform_real_distribution<double> dist1(0,9);
	test_statistic_properties_cont(n, urng, urng2, dist1);
	test_statistic_properties(n, urng, urng2, dist1);	

	boost::random::uniform_int_distribution<double> dist2(0,1);
	test_statistic_properties_cont(n, urng, urng2, dist1);	

	boost::random::uniform_int_distribution<double> dist3(std::numeric_limits<double>::min(),std::numeric_limits<double>::max());
	test_statistic_properties_cont(n, urng, urng2, dist1);	*/
}


}
}
}
}

#endif // BOOST_RANDOM_ACML_TEST_TEST_BOOST_DISTRIBUTIONS_HPP

