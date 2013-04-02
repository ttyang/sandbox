// Copyright Fabian Bösch 2013
//
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RANDOM_ACML_TEST_TEST_STATISTICS_HPP
#define BOOST_RANDOM_ACML_TEST_TEST_STATISTICS_HPP



#include <vector>
#include <boost/generate/generate.hpp>

#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>

namespace boost {
namespace random {
namespace acml {
namespace test {

template<class ResultType>
ResultType cdf(const std::vector<ResultType>& s, ResultType x)
{
	std::size_t r=0;
	for (std::size_t i = 0; i < s.size(); ++i)
	{
		if (s[i] >= x) ++r;
		else break;
	}
	return static_cast<ResultType>(r) / s.size();
} 

//Two-sample Kolmogorov–Smirnov test
template <class ResultType>
void k_s_test(const std::vector<ResultType>& s1, const std::vector<ResultType>& s2, bool compute_first = true)
{

	static std::size_t n1(s1.size());
	static std::vector<ResultType> sorted_s1(s1);
	
	if (compute_first)
	{
		n1 = s1.size();
		sorted_s1 = s1;
		std::sort(sorted_s1.begin(), sorted_s1.end());
	}

	const std::size_t n2(s2.size());
	std::vector<ResultType> sorted_s2(n2);
	std::sort(sorted_s2.begin(), sorted_s2.end());

	const ResultType a = std::max(sorted_s2[0],sorted_s1[0]);	
	const ResultType b = std::min(sorted_s2[n2-1],sorted_s1[n1-1]);
	
	const std::size_t N = 100;
	ResultType D = 0;
	for (std::size_t i=0; i<N; ++i)
	{
		const ResultType x = i*(b-a)/(N-1)+a;
		const ResultType d = std::abs(cdf(sorted_s1, x) - cdf(sorted_s2, x));
		if (d>D) D=d;
	}

	const ResultType K_5 = 1.35 * (n1+n2)/(n1*n2);
	
	BOOST_CHECK_LE(D, K_5);
}


template <class URNG, class URNG2, class Distribution>
void test_statistic_properties_cont(std::size_t n, URNG& urng, URNG2& urng2, Distribution& distribution)
{
	typedef typename Distribution::result_type result_type;
	typedef typename boost::random::variate_generator<URNG, Distribution > v_gen_type;
	typedef typename boost::random::variate_generator<URNG&, Distribution > v_gen_ref_type;
	typedef typename boost::random::variate_generator<URNG*, Distribution > v_gen_ptr_type;
	typedef typename boost::random::variate_generator<URNG2, Distribution > v_gen2_type;

	BOOST_CHECK((
		boost::random::is_variate_generator_a_mkl_range_generator<URNG, Distribution >::type::value /*||
		boost::random::is_variate_generator_a_acml_range_generator<v_gen_type, Distribution >::value*/
	));

	v_gen_type v_gen(urng, distribution);
	v_gen_ref_type v_gen_ref(urng, distribution);
	v_gen_ptr_type v_gen_ptr(&urng, distribution);
	v_gen2_type v_gen2(urng2, distribution);

	std::vector<result_type> variates1(n), variates2(n);

	for (std::size_t i=0; i<n; ++i) variates1[i] = v_gen2();
	for (std::size_t i=0; i<n; ++i) variates2[i] = distribution(urng2);

	k_s_test(variates1,variates2,true);

	/*check_statistical_properties(variates1.begin(), variates1.end(), variates2.begin(), variates2.end(), true);

	for (std::size_t i=0; i<n; ++i) variates2[i] = v_gen();
	check_statistical_properties(variates1.begin(), variates1.end(), variates2.begin(), variates2.end(), false);
	
	v_gen(variates2.begin(), variates2.end());
	check_statistical_properties(variates1.begin(), variates1.end(), variates2.begin(), variates2.end(), false);

	boost::generate(variates2.begin(), variates2.end(), v_gen);
	check_statistical_properties(variates1.begin(), variates1.end(), variates2.begin(), variates2.end(), false);

	for (std::size_t i=0; i<n; ++i) variates2[i] = distribution(urng);	
	check_statistical_properties(variates1.begin(), variates1.end(), variates2.begin(), variates2.end(), false);
	
	boost::generate(variates2.begin(), variates2.end(), v_gen_ref);
	check_statistical_properties(variates1.begin(), variates1.end(), variates2.begin(), variates2.end(), false);

	boost::generate(variates2.begin(), variates2.end(), v_gen_ptr);
	check_statistical_properties(variates1.begin(), variates1.end(), variates2.begin(), variates2.end(), false);*/
}


template <class Iterator>
void check_statistical_properties(Iterator first1, Iterator last1, Iterator first2, Iterator last2, bool compute_first = true)
{
	typedef boost::accumulators::accumulator_set< result_type, typename boost::accumulators::stats<
		typename boost::accumulators::tag::mean, 
		typename boost::accumulators::tag::moment<2>,
		typename boost::accumulators::tag::moment<3>,
		typename boost::accumulators::tag::moment<4>
	> > accumulator_type;

	static accumulator_type acc1;
	accumulator_type acc2;

	if (compute_first) 
	{
		acc1 = 	accumulator_type();
		std::for_each( first1, last1, boost::bind<void>( boost::ref(acc1), _1 ) );
	}
	std::for_each( first2, last2, boost::bind<void>( boost::ref(acc2), _1 ) );

	BOOST_CHECK_CLOSE(boost::accumulators::mean(acc1), boost::accumulators::mean(acc2), 0.1);
	BOOST_CHECK_CLOSE(boost::accumulators::moment<2>(acc1), boost::accumulators::moment<2>(acc2), 0.1);
	BOOST_CHECK_CLOSE(boost::accumulators::moment<3>(acc1), boost::accumulators::moment<3>(acc2), 0.1);
	BOOST_CHECK_CLOSE(boost::accumulators::moment<4>(acc1), boost::accumulators::moment<4>(acc2), 1.0);
}

template <class URNG, class URNG2, class Distribution>
void test_statistic_properties(std::size_t n, URNG& urng, URNG2& urng2, Distribution& distribution)
{
	typedef typename Distribution::result_type result_type;
	typedef typename boost::random::variate_generator<URNG, Distribution > v_gen_type;
	typedef typename boost::random::variate_generator<URNG&, Distribution > v_gen_ref_type;
	typedef typename boost::random::variate_generator<URNG*, Distribution > v_gen_ptr_type;
	typedef typename boost::random::variate_generator<URNG2, Distribution > v_gen2_type;

	BOOST_CHECK((
		boost::random::is_variate_generator_a_mkl_range_generator<URNG, Distribution >::type::value /*||
		boost::random::is_variate_generator_a_acml_range_generator<v_gen_type, Distribution >::value*/
	));

	v_gen_type v_gen(urng, distribution);
	v_gen_ref_type v_gen_ref(urng, distribution);
	v_gen_ptr_type v_gen_ptr(&urng, distribution);
	v_gen2_type v_gen2(urng2, distribution);

	std::vector<result_type> variates1(n), variates2(n);

	for (std::size_t i=0; i<n; ++i) variates1[i] = v_gen2();
	for (std::size_t i=0; i<n; ++i) variates2[i] = distribution(urng2);

	check_statistical_properties(variates1.begin(), variates1.end(), variates2.begin(), variates2.end(), true);

	for (std::size_t i=0; i<n; ++i) variates2[i] = v_gen();
	check_statistical_properties(variates1.begin(), variates1.end(), variates2.begin(), variates2.end(), false);
	
	v_gen(variates2.begin(), variates2.end());
	check_statistical_properties(variates1.begin(), variates1.end(), variates2.begin(), variates2.end(), false);

	boost::generate(variates2.begin(), variates2.end(), v_gen);
	check_statistical_properties(variates1.begin(), variates1.end(), variates2.begin(), variates2.end(), false);

	for (std::size_t i=0; i<n; ++i) variates2[i] = distribution(urng);	
	check_statistical_properties(variates1.begin(), variates1.end(), variates2.begin(), variates2.end(), false);
	
	boost::generate(variates2.begin(), variates2.end(), v_gen_ref);
	check_statistical_properties(variates1.begin(), variates1.end(), variates2.begin(), variates2.end(), false);

	boost::generate(variates2.begin(), variates2.end(), v_gen_ptr);
	check_statistical_properties(variates1.begin(), variates1.end(), variates2.begin(), variates2.end(), false);
}

}
}
}
}

#endif // BOOST_RANDOM_ACML_TEST_TEST_STATISTICS_HPP


