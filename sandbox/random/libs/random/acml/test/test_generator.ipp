// Copyright Fabian Bösch 2013
//
// Used this: boost/libs/random/test/test_generator.hpp Copyright Steven Watanabe 2011
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#include "concepts.hpp"
#include <boost/random/seed_seq.hpp>
#include <boost/generate/generate.hpp>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using boost::random::acml::test::PseudoRandomNumberEngine;
BOOST_CONCEPT_ASSERT((PseudoRandomNumberEngine< BOOST_RANDOM_ACML_URNG >));

typedef typename BOOST_RANDOM_ACML_URNG::result_type result_type;
typedef typename BOOST_RANDOM_ACML_URNG::seed_type seed_type;

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4244)
#endif

template<class Converted, class URNG, class T>
void test_seed_conversion(URNG & urng, const T & t)
{
    Converted c = static_cast<Converted>(t);
    if(static_cast<T>(c) == t) {
        URNG urng2(c);
        std::ostringstream msg;
        msg << "Testing seed: type " << typeid(Converted).name() << ", value " << c;
        BOOST_CHECK_MESSAGE(urng == urng2, msg.str());
        urng2.seed(c);
		msg << " check 2";
        BOOST_CHECK_MESSAGE(urng == urng2, msg.str());
    }
}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

void test_seed(seed_type value)
{
    BOOST_RANDOM_ACML_URNG urng(value);

    // integral types
    test_seed_conversion<char>(urng, value);
    test_seed_conversion<signed char>(urng, value);
    test_seed_conversion<unsigned char>(urng, value);
    test_seed_conversion<short>(urng, value);
    test_seed_conversion<unsigned short>(urng, value);
    test_seed_conversion<int>(urng, value);
    test_seed_conversion<unsigned int>(urng, value);
    test_seed_conversion<long>(urng, value);
    test_seed_conversion<unsigned long>(urng, value);
#if !defined(BOOST_NO_INT64_T)
    test_seed_conversion<boost::int64_t>(urng, value);
    test_seed_conversion<boost::uint64_t>(urng, value);
#endif

    // floating point types
    test_seed_conversion<float>(urng, value);
    test_seed_conversion<double>(urng, value);
    test_seed_conversion<long double>(urng, value);
}

BOOST_AUTO_TEST_CASE(test_default_seed)
{
	BOOST_RANDOM_ACML_URNG urng;
    BOOST_RANDOM_ACML_URNG urng2;
	urng2();
	BOOST_CHECK_NE(urng, urng2);
	urng2.seed();
	BOOST_CHECK_EQUAL(urng, urng2);

	/*urng.seed(1.f);
	urng2.seed(1);
	BOOST_CHECK_EQUAL(urng, urng2);*/
	//seed_type s(static_cast<seed_type>(1));	
	//BOOST_RANDOM_ACML_URNG urng3(s);	
	//char c = static_cast<char>(s);	
    //BOOST_RANDOM_ACML_URNG urng4(c);
	//BOOST_CHECK_EQUAL(urng3, urng4);*/
	
    //test_seed(1);

	/*
    BOOST_RANDOM_ACML_URNG urng;
    BOOST_RANDOM_ACML_URNG urng2;
	std::cout << "egnines the same? " << std::boolalpha << (urng == urng2) << std::endl;
	std::cout << "streams the same? " << std::boolalpha << (urng.get_stream() == urng2.get_stream()) << std::endl;    
	//urng2();
    //BOOST_CHECK_NE(urng, urng2);
	//urng();    
	urng2.seed(2);
	urng.seed(2);
	std::cout << "egnines the same? " << std::boolalpha << (urng == urng2) << std::endl;
	std::cout << "streams the same? " << std::boolalpha << (urng.get_stream() == urng2.get_stream()) << std::endl;
	BOOST_RANDOM_ACML_URNG urng3;//(urng);
	urng3();	
	urng3.seed(1);
	urng.seed(1);
	urng3();
	urng();
	std::cout << "egnines the same? " << std::boolalpha << (urng == urng3) << std::endl;
	std::cout << "streams the same? " << std::boolalpha << (urng.get_stream() == urng3.get_stream()) << std::endl;
	//urng2 = urng;
	//std::cout << "egnines the same? " << std::boolalpha << (urng == urng2) << std::endl;
	//std::cout << "streams the same? " << std::boolalpha << (urng.get_stream() == urng2.get_stream()) << std::endl;*/
    /*BOOST_CHECK_EQUAL(urng, urng2);*/
	/*
	std::cout << BOOST_RANDOM_ACML_URNG::default_seed  << std::endl;
	{
	BOOST_RANDOM_ACML_URNG urng_test;
	}
	BOOST_RANDOM_ACML_URNG urng0;
	//urng0.seed(1);
	BOOST_RANDOM_ACML_URNG urng;
    BOOST_RANDOM_ACML_URNG urng2;
	BOOST_RANDOM_ACML_URNG urng3;
	BOOST_RANDOM_ACML_URNG urng4;*/
	//std::cout << "egnine0 == engine1? " << std::boolalpha << (urng0 == urng1) << std::endl;
	//std::cout << std::endl;
	//std::cout << "egnine1 == engine2? " << std::boolalpha << (urng == urng2) << std::endl;
	//std::cout << "egnine1 == engine3? " << std::boolalpha << (urng == urng3) << std::endl;
	//std::cout << "egnine1 == engine4? " << std::boolalpha << (urng == urng4) << std::endl;
	//std::cout << "egnine2 == engine3? " << std::boolalpha << (urng2 == urng3) << std::endl;
	//std::cout << "egnine2 == engine4? " << std::boolalpha << (urng2 == urng4) << std::endl;
	//std::cout << "egnine3 == engine4? " << std::boolalpha << (urng3 == urng4) << std::endl;
	//std::cout << std::endl;	

	/*{
		BOOST_RANDOM_ACML_URNG* urng_test = new BOOST_RANDOM_ACML_URNG();
		urng_test->seed();
		std::cout << (*urng_test)() << std::endl;
		delete urng_test;
	}*/
	/*
	urng0.seed(1); // first seed call changes some internal state of the vsl library!!	
	urng.seed(1);
	urng2.seed(1);
	urng3.seed(1);
	urng4.seed(1);
	std::cout << "egnine0 == engine1? " << std::boolalpha << (urng0 == urng) << std::endl;
	std::cout << "egnine0 == engine2? " << std::boolalpha << (urng0 == urng2) << std::endl;
	std::cout << "egnine1 == engine2? " << std::boolalpha << (urng == urng2) << std::endl;
	std::cout << "egnine1 == engine3? " << std::boolalpha << (urng == urng3) << std::endl;
	std::cout << "egnine1 == engine4? " << std::boolalpha << (urng == urng4) << std::endl;
	std::cout << "egnine2 == engine3? " << std::boolalpha << (urng2 == urng3) << std::endl;
	std::cout << "egnine2 == engine4? " << std::boolalpha << (urng2 == urng4) << std::endl;
	std::cout << "egnine3 == engine4? " << std::boolalpha << (urng3 == urng4) << std::endl;	
	std::cout << std::endl;*/
}


BOOST_AUTO_TEST_CASE(test_arithmetic_seed)
{
    test_seed(static_cast<seed_type>(1));
    test_seed(static_cast<seed_type>(127));
    test_seed(static_cast<seed_type>(539157235));
    test_seed(static_cast<seed_type>(~0u));
}

BOOST_AUTO_TEST_CASE(test_iterator_seed)
{
    const std::vector<seed_type> v(std::size_t(9999u), 0x41);
    std::vector<seed_type>::const_iterator it = v.begin();
    std::vector<seed_type>::const_iterator it_end = v.end();
    BOOST_RANDOM_ACML_URNG urng(it, it_end);
    BOOST_RANDOM_ACML_URNG urng2;
    urng2.seed(it, it_end);
    BOOST_CHECK_EQUAL(urng, urng2);
}

BOOST_AUTO_TEST_CASE(test_seed_seq_seed)
{
    boost::random::seed_seq q;
    BOOST_RANDOM_ACML_URNG urng(q);
    BOOST_RANDOM_ACML_URNG urng2;
    BOOST_CHECK_NE(urng, urng2);
    urng2.seed(q);
    BOOST_CHECK_EQUAL(urng, urng2);
}

template<class CharT>
void do_test_streaming(const BOOST_RANDOM_ACML_URNG& urng)
{
    BOOST_RANDOM_ACML_URNG urng2;
    std::basic_ostringstream<CharT> output;
    output << urng;
    BOOST_CHECK_NE(urng, urng2);
    // restore old state
    std::basic_istringstream<CharT> input(output.str());
    input >> urng2;
    BOOST_CHECK_EQUAL(urng, urng2);
}

BOOST_AUTO_TEST_CASE(test_streaming)
{
    BOOST_RANDOM_ACML_URNG urng;
    urng.discard(9307);
    do_test_streaming<char>(urng); 
#if !defined(BOOST_NO_STD_WSTREAMBUF) && !defined(BOOST_NO_STD_WSTRING)
    do_test_streaming<wchar_t>(urng);
#endif
}

BOOST_AUTO_TEST_CASE(test_discard)
{
    BOOST_RANDOM_ACML_URNG urng;
    BOOST_RANDOM_ACML_URNG urng2;
    BOOST_CHECK_EQUAL(urng, urng2);
    for(int i = 0; i < 9307; ++i) urng();
    BOOST_CHECK_NE(urng, urng2);
    urng2.discard(9307);
    BOOST_CHECK_EQUAL(urng, urng2);
}

BOOST_AUTO_TEST_CASE(test_copy)
{
    BOOST_RANDOM_ACML_URNG urng;
    urng.discard(9307);
    {
        BOOST_RANDOM_ACML_URNG urng2 = urng;
        BOOST_CHECK_EQUAL(urng, urng2);
    }
    {
        BOOST_RANDOM_ACML_URNG urng2(urng);
        BOOST_CHECK_EQUAL(urng, urng2);
    }
    {
        BOOST_RANDOM_ACML_URNG urng2;
        urng2 = urng;
        BOOST_CHECK_EQUAL(urng, urng2);
    }
}

BOOST_AUTO_TEST_CASE(test_min_max)
{
    BOOST_RANDOM_ACML_URNG urng;
    for(int i = 0; i < 10000; ++i) {
        result_type value = urng();
        BOOST_CHECK_GE(value, (urng.min)());
        BOOST_CHECK_LE(value, (urng.max)());
    }
}

BOOST_AUTO_TEST_CASE(test_comparison)
{
    BOOST_RANDOM_ACML_URNG urng;
    BOOST_RANDOM_ACML_URNG urng2;
    BOOST_CHECK(urng == urng2);
    BOOST_CHECK(!(urng != urng2));
    urng();
    BOOST_CHECK(urng != urng2);
    BOOST_CHECK(!(urng == urng2));
}

BOOST_AUTO_TEST_CASE(test_generate)
{
    BOOST_RANDOM_ACML_URNG urng;
    BOOST_RANDOM_ACML_URNG urng2;
	BOOST_RANDOM_ACML_URNG urng3;
	static const std::size_t N = 9999;
	result_type arr[N];
	result_type arr2[N];
	result_type arr3[N];
	for (std::size_t i=0; i<N; ++i) arr[i] = urng();
	urng2(arr2, arr2+N);
	BOOST_CHECK_EQUAL_COLLECTIONS(arr, arr + N, arr2, arr2 + N);
	boost::generate(arr3,arr3+N,urng3);
	BOOST_CHECK_EQUAL_COLLECTIONS(arr, arr + N, arr3, arr3 + N);
}

template<class URNG, bool possible>
struct block_split_URNG {

	template <class Iterator>
	static void make(Iterator first, Iterator last, std::size_t n) {}

};

template<class URNG>
struct block_split_URNG<URNG,true>
{
	template <class Iterator>
	static void make(Iterator first, Iterator last, std::size_t n)
	{
		ENGINE_SCOPE::make_independent_engines_by_block_split<URNG>(first, last, n);
	}
};

BOOST_AUTO_TEST_CASE(block_split)
{
	static const std::size_t N = 100;
	const std::size_t n = 1000;
	if (ENGINE_SCOPE::has_block_split<BOOST_RANDOM_ACML_URNG>::value)
	{
		BOOST_RANDOM_ACML_URNG urng;
		std::vector<BOOST_RANDOM_ACML_URNG> urngs(N);
		block_split_URNG<BOOST_RANDOM_ACML_URNG, ENGINE_SCOPE::has_block_split<BOOST_RANDOM_ACML_URNG>::value>::make(urngs.begin(), urngs.end(), n);
		std::vector<result_type> variates(n*N);
		std::vector<result_type> variates2(n*N);
		boost::generate(variates.begin(),variates.end(),urng);
		for (std::size_t i=0; i<N; ++i)
		{
			boost::generate(&variates2[i*n],&variates2[(i+1)*n],urngs[i]);
		}
		BOOST_CHECK_EQUAL_COLLECTIONS(variates.begin(), variates.end(), variates2.begin(), variates2.end());
	}
}

template<class URNG, bool possible>
struct leap_frog_URNG {
	template <class Iterator>
	static void make(Iterator first, Iterator last) {}
};

template<class URNG>
struct leap_frog_URNG<URNG,true>
{
	template <class Iterator>
	static void make(Iterator first, Iterator last)
	{
		ENGINE_SCOPE::make_independent_engines_by_leap_frog<URNG>(first, last);
	}
};

BOOST_AUTO_TEST_CASE(leap_frog)
{
	static const std::size_t N = 100;
	const std::size_t n = 1000;
	if (ENGINE_SCOPE::has_leap_frog<BOOST_RANDOM_ACML_URNG>::value)
	{
		BOOST_RANDOM_ACML_URNG urng;
		std::vector<BOOST_RANDOM_ACML_URNG> urngs(N);
		leap_frog_URNG<BOOST_RANDOM_ACML_URNG, ENGINE_SCOPE::has_leap_frog<BOOST_RANDOM_ACML_URNG>::value>::make(urngs.begin(), urngs.end());
		std::vector<result_type> variates(n*N);
		std::vector<result_type> variates2(n*N);
		#ifndef BOOST_RANDOM_ACML_NO_DISCARD		
		urng.discard(N-1);
		#endif
		boost::generate(variates.begin(),variates.end(),urng);
		std::size_t c(0);
		for (std::size_t i=0; i<n; ++i)
		{
			for (std::size_t j=0; j<N; ++j)
			{
				variates2[c++] = urngs[j]();
			}
		}
		BOOST_CHECK_EQUAL_COLLECTIONS(variates.begin(), variates.end(), variates2.begin(), variates2.end());
	}
}


#include <boost/config.hpp>
#include <boost/random/acml/variate_generator_specialization.hpp>
#include <boost/random/mkl/variate_generator_specialization.hpp>
#include <boost/random.hpp>

/*#include "test_boost_distributions.hpp"
#include <boost/random/mersenne_twister.hpp>

BOOST_AUTO_TEST_CASE(statistics)
{
	typedef boost::random::mt19937 urng2_type;
	urng2_type urng2;
	BOOST_RANDOM_ACML_URNG urng;
	
	//boost::random::acml::test::test_boost_uniform_int_distribution(1000000, urng, urng2);
	//boost::random::acml::test::test_boost_uniform_real_distribution(1000000, urng, urng2);

}*/

//#include <boost/random/mkl/variate_generator_specialization_boost_distributions.hpp>
//#include <boost/random/acml/variate_generator_specialization_boost_distributions.hpp>

//#if (defined(__GXX_EXPERIMENTAL_CXX0X) || __cplusplus >= 201103L)

//#include <boost/random/mkl/variate_generator_specialization_0x_distributions.hpp>
//#include <boost/random/acml/variate_generator_specialization_0x_distributions.hpp>
//#endif

#ifdef BOOST_HAS_TR1_RANDOM
//#include <boost/random/mkl/variate_generator_specialization_tr1_distributions.hpp>
//#include <boost/random/acml/variate_generator_specialization_tr1_distributions.hpp>
#endif

template <class Distribution>
void instanciate()
{
	BOOST_RANDOM_ACML_URNG urng;
	Distribution dist;
	boost::variate_generator<BOOST_RANDOM_ACML_URNG,Distribution> vgen1(urng,dist);
	boost::variate_generator<BOOST_RANDOM_ACML_URNG&,Distribution> vgen2(urng,dist);
	boost::variate_generator<BOOST_RANDOM_ACML_URNG*,Distribution> vgen3(&urng,dist);

	if (boost::random::is_variate_generator_a_mkl_range_generator<BOOST_RANDOM_ACML_URNG, Distribution>::value)
	{
		std::cout << "variate generator is specialized for mkl engines for distribution: " << typeid(Distribution).name() << std::endl;
	}
	if (boost::random::is_variate_generator_a_acml_range_generator<BOOST_RANDOM_ACML_URNG, Distribution>::value)
	{
		std::cout << "variate generator is specialized for acml engines for distribution: " << typeid(Distribution).name() << std::endl;
	}
}

template <class IntType>
void int_distributions()
{
	// boost
	instanciate<typename boost::random::uniform_smallint<IntType> >();
	instanciate<typename boost::random::uniform_int_distribution<IntType> >();
	instanciate<typename boost::random::binomial_distribution<IntType, float> >();
	instanciate<typename boost::random::binomial_distribution<IntType, double> >();
	instanciate<typename boost::random::geometric_distribution<IntType, float> >();
	instanciate<typename boost::random::geometric_distribution<IntType, double> >();
	instanciate<typename boost::random::negative_binomial_distribution<IntType, float> >();
	instanciate<typename boost::random::negative_binomial_distribution<IntType, double> >();
	instanciate<typename boost::random::poisson_distribution<IntType, float> >();
	instanciate<typename boost::random::poisson_distribution<IntType, double> >();

	#ifdef BOOST_HAS_TR1_RANDOM
	// tr1
	instanciate<typename std::tr1::uniform_int<IntType> >();
	instanciate<typename std::tr1::binomial_distribution<IntType, float> >();
	instanciate<typename std::tr1::binomial_distribution<IntType, double> >();
	instanciate<typename std::tr1::geometric_distribution<IntType, float> >();
	instanciate<typename std::tr1::geometric_distribution<IntType, double> >();
	instanciate<typename std::tr1::poisson_distribution<IntType, float> >();
	instanciate<typename std::tr1::poisson_distribution<IntType, double> >();
	#endif
}

template <class IntType>
void int_distributions_std()
{
	//#if (defined(__GXX_EXPERIMENTAL_CXX0X) || __cplusplus >= 201103L)
	// std
	instanciate<typename std::uniform_int_distribution<IntType> >();
	instanciate<typename std::binomial_distribution<IntType> >();
	instanciate<typename std::geometric_distribution<IntType> >();
	instanciate<typename std::negative_binomial_distribution<IntType> >();
	instanciate<typename std::poisson_distribution<IntType> >();
	//#endif
}

template <class Real>
void int_distributions2()
{
	// boost
	instanciate<typename boost::random::bernoulli_distribution<Real> >();
}

void int_distributions3()
{
	//#if (defined(__GXX_EXPERIMENTAL_CXX0X) || __cplusplus >= 201103L)
	// std
	instanciate<typename std::bernoulli_distribution>();
	//#endif

	#ifdef BOOST_HAS_TR1_RANDOM
	// tr1
	instanciate<typename std::tr1::bernoulli_distribution>();
	#endif
}

template <class Real>
void real_distributions()
{
	// boost
	instanciate<typename boost::random::uniform_01<Real> >();
	instanciate<typename boost::random::uniform_real_distribution<Real> >();
	instanciate<typename boost::random::exponential_distribution<Real> >();
	instanciate<typename boost::random::gamma_distribution<Real> >();
	instanciate<typename boost::random::weibull_distribution<Real> >();
	instanciate<typename boost::random::extreme_value_distribution<Real> >();
	instanciate<typename boost::random::normal_distribution<Real> >();
	instanciate<typename boost::random::lognormal_distribution<Real> >();
	instanciate<typename boost::random::chi_squared_distribution<Real> >();
	instanciate<typename boost::random::cauchy_distribution<Real> >();
	instanciate<typename boost::random::fisher_f_distribution<Real> >();
	instanciate<typename boost::random::student_t_distribution<Real> >();

	//#if (defined(__GXX_EXPERIMENTAL_CXX0X) || __cplusplus >= 201103L)
	// std
	instanciate<typename std::uniform_real_distribution<Real> >();
	instanciate<typename std::exponential_distribution<Real> >();
	instanciate<typename std::weibull_distribution<Real> >();
	instanciate<typename std::extreme_value_distribution<Real> >();
	instanciate<typename std::normal_distribution<Real> >();
	instanciate<typename std::cauchy_distribution<Real> >();
	//#endif

	#ifdef BOOST_HAS_TR1_RANDOM
	// tr1
	instanciate<typename std::tr1::uniform_real<Real> >();
	instanciate<typename std::tr1::exponential_distribution<Real> >();
	instanciate<typename std::tr1::normal_distribution<Real> >();
	instanciate<typename std::tr1::gamma_distribution<Real> >();
	#endif
}

void real_distributions_std()
{
	//#if (defined(__GXX_EXPERIMENTAL_CXX0X) || __cplusplus >= 201103L)
	// std
	instanciate<typename std::lognormal_distribution<float> >();
	#if ((defined (__GLIBCXX__) && __GLIBCXX__ >= 20120906) || (! (defined (__GLIBCXX__)))  )
	instanciate<typename std::lognormal_distribution<double> >();
	instanciate<typename std::gamma_distribution<float> >();
	instanciate<typename std::chi_squared_distribution<float> >();
	instanciate<typename std::fisher_f_distribution<float> >();
	instanciate<typename std::student_t_distribution<float> >();
	#endif
	instanciate<typename std::gamma_distribution<double> >();
	instanciate<typename std::chi_squared_distribution<double> >();
	instanciate<typename std::fisher_f_distribution<double> >();
	instanciate<typename std::student_t_distribution<double> >();
	//#endif
}

BOOST_AUTO_TEST_CASE(variate_generator)
{
	int_distributions<char>();
	int_distributions<char>();
	int_distributions<unsigned char>();
	int_distributions<signed char>();
	int_distributions<short>();
	int_distributions<unsigned short>();
	int_distributions<signed short>();
	int_distributions<int>();
	int_distributions<signed int>();
	int_distributions<unsigned int>();
	int_distributions<long>();
	int_distributions<unsigned long>();
	int_distributions<signed long>();

	#if (defined (__GLIBCXX__) && __GLIBCXX__ < 20120906)
	#ifdef ACML_TEST
	int_distributions_std<long>();
	#else
	int_distributions_std<int>();
	#endif	
	#else	
	int_distributions_std<char>();
	int_distributions_std<char>();
	int_distributions_std<unsigned char>();
	int_distributions_std<signed char>();
	int_distributions_std<short>();
	int_distributions_std<unsigned short>();
	int_distributions_std<signed short>();
	int_distributions_std<int>();
	int_distributions_std<signed int>();
	int_distributions_std<unsigned int>();
	int_distributions_std<long>();
	int_distributions_std<unsigned long>();
	int_distributions_std<signed long>();
	#endif

	int_distributions2<float>();
	int_distributions2<double>();

	int_distributions3();

	real_distributions<float>();
	real_distributions<double>();

	real_distributions_std();

}


