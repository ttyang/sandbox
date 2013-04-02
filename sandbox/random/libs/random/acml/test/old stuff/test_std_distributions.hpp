// Copyright Fabian Bösch 2013
//
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RANDOM_ACML_TEST_TEST_STD_DISTRIBUTIONS_HPP
#define BOOST_RANDOM_ACML_TEST_TEST_STD_DISTRIBUTIONS_HPP

#include <random>
#include <test_statistics.hpp>


namespace boost {
namespace random {
namespace acml {
namespace test {


// discrete uniform distribution
<class URNG, class URNG2>
void test_std_uniform_int_distribution(std::size_t n, URNG& urng, URNG2& urng2)
{
	std::uniform_int_distribution<int> dist1(0,10);
	test_statistic_properties(n, urng, urng2, dist1);	
}

}
}
}
}

#endif // BOOST_RANDOM_ACML_TEST_TEST_STD_DISTRIBUTIONS_HPP

