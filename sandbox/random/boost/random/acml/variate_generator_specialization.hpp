// Copyright Fabian Bösch 2012
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 *  @file 
 *  @brief This file contains macros used for specializing the template class variate_generator with ACML engines.
 */

#ifndef BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPECIALIZATION_HPP
#define BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPECIALIZATION_HPP

#include <boost/random/variate_generator.hpp>
#include <boost/generate/generate.hpp>
#include <boost/mpl/bool.hpp>
#include <limits>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#define BOOST_RANDOM_ACML_CONCAT(...) __VA_ARGS__

#define BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY(acml_engine_type, Distribution, acml_function, dist_params, value_params)           \
private:                                                                                                                                            \
                                                                                                                                                    \
typedef boost::random::detail::ptr_helper<acml_engine_type> helper_type;                                                                            \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
typedef typename helper_type::value_type engine_value_type;                                                                                         \
typedef acml_engine_type engine_type;                                                                                                               \
typedef Distribution distribution_type;                                                                                                             \
typedef typename Distribution::result_type result_type;                                                                                             \
typedef boost::range_generate::unit_stride_range_generator_type_checked<result_type> is_range_generator;                                            \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
variate_generator(acml_engine_type e, Distribution d)                                                                                               \
  : _eng(e), _dist(d) { }                                                                                                                           \
                                                                                                                                                    \
result_type operator()()                                                                                                                            \
{                                                                                                                                                   \
	long info(0);                                                                                                                                   \
	result_type result;                                                                                                                             \
    acml_function(1, dist_params, &(helper_type::ref(_eng).state()[0]), &result, &info);                                                            \
	boost::random::acml::check_errcode(info);                                                                                                       \
	return result;                                                                                                                                  \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class T>                                                                                                                                   \
result_type operator()(const T& value)                                                                                                              \
{                                                                                                                                                   \
	long info(0);                                                                                                                                   \
	result_type result;                                                                                                                             \
    acml_function(1, value_params, &(helper_type::ref(_eng).state()[0]), &result, &info);                                                           \
	boost::random::acml::check_errcode(info);                                                                                                       \
	return result;                                                                                                                                  \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class UnitStrideIterator>                                                                                                                  \
void operator()(UnitStrideIterator begin, UnitStrideIterator end)                                                                                   \
{                                                                                                                                                   \
	long info(0);                                                                                                                                   \
	acml_function(end-begin, dist_params, &(helper_type::ref(_eng).state()[0]), &(*begin), &info);                                                  \
	boost::random::acml::check_errcode(info);                                                                                                       \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class UnitStrideIterator, class T>                                                                                                         \
void operator()(UnitStrideIterator begin, UnitStrideIterator end, const T& value)                                                                   \
{                                                                                                                                                   \
	long info(0);                                                                                                                                   \
	acml_function(end-begin, value_params, &(helper_type::ref(_eng).state()[0]), &(*begin), &info);                                                 \
	boost::random::acml::check_errcode(info);                                                                                                       \
}                                                                                                                                                   \
                                                                                                                                                    \
distribution_type& distribution() { return _dist; }                                                                                                 \
                                                                                                                                                    \
const distribution_type& distribution() const { return _dist; }                                                                                     \
                                                                                                                                                    \
result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () const { return (distribution().min)(); }                                                        \
                                                                                                                                                    \
result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () const { return (distribution().max)(); }                                                        \
                                                                                                                                                    \
engine_value_type& engine() { return helper_type::ref(_eng); }                                                                                      \
                                                                                                                                                    \
const engine_value_type& engine() const { return helper_type::ref(_eng); }                                                                          \
                                                                                                                                                    \
private:                                                                                                                                            \
                                                                                                                                                    \
acml_engine_type _eng;                                                                                                                              \
distribution_type _dist;


#define BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION(Distribution, single, acml_function, dist_params, value_params)                          \
template<long genid, long subid>                                                                                                                    \
class variate_generator<boost::random::acml::engine<genid,single,subid>,Distribution>                                                               \
{                                                                                                                                                   \
    BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY(                                                                                        \
		BOOST_RANDOM_ACML_CONCAT(boost::random::acml::engine<genid,single,subid>),                                                                  \
		BOOST_RANDOM_ACML_CONCAT(Distribution),                                                                                                     \
		acml_function,                                                                                                                              \
		BOOST_RANDOM_ACML_CONCAT(dist_params),                                                                                                      \
		BOOST_RANDOM_ACML_CONCAT(value_params)                                                                                                      \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<long genid, long subid>                                                                                                                    \
class variate_generator<boost::random::acml::engine<genid,single,subid>&,Distribution>                                                              \
{                                                                                                                                                   \
    BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY(                                                                                        \
		BOOST_RANDOM_ACML_CONCAT(boost::random::acml::engine<genid,single,subid>&),                                                                 \
		BOOST_RANDOM_ACML_CONCAT(Distribution),                                                                                                     \
		acml_function,                                                                                                                              \
		BOOST_RANDOM_ACML_CONCAT(dist_params),                                                                                                      \
		BOOST_RANDOM_ACML_CONCAT(value_params)                                                                                                      \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<long genid, long subid>                                                                                                                    \
class variate_generator<boost::random::acml::engine<genid,single,subid>*,Distribution>                                                              \
{                                                                                                                                                   \
    BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY(                                                                                        \
		BOOST_RANDOM_ACML_CONCAT(boost::random::acml::engine<genid,single,subid>*),                                                                 \
		BOOST_RANDOM_ACML_CONCAT(Distribution),                                                                                                     \
		acml_function,                                                                                                                              \
		BOOST_RANDOM_ACML_CONCAT(dist_params),                                                                                                      \
		BOOST_RANDOM_ACML_CONCAT(value_params)                                                                                                      \
	)                                                                                                                                               \
};                                                                                                                                                  \
template <long genid, long subid> struct is_variate_generator_a_acml_range_generator<boost::random::acml::engine<genid,single,subid>, Distribution> : public boost::mpl::true_ {};\
template <long genid, long subid> struct is_variate_generator_a_acml_range_generator<boost::random::acml::engine<genid,single,subid>&,Distribution> : public boost::mpl::true_ {};\
template <long genid, long subid> struct is_variate_generator_a_acml_range_generator<boost::random::acml::engine<genid,single,subid>*,Distribution> : public boost::mpl::true_ {};


#define BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY_TR1(acml_engine_type, Distribution, acml_function, dist_params )                    \
private:                                                                                                                                            \
                                                                                                                                                    \
typedef boost::random::detail::ptr_helper<acml_engine_type> helper_type;                                                                            \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
typedef typename helper_type::value_type engine_value_type;                                                                                         \
typedef acml_engine_type engine_type;                                                                                                               \
typedef Distribution distribution_type;                                                                                                             \
typedef typename Distribution::result_type result_type;                                                                                             \
typedef boost::range_generate::unit_stride_range_generator_type_checked<result_type> is_range_generator;                                            \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
variate_generator(acml_engine_type e, Distribution d)                                                                                               \
  : _eng(e), _dist(d) { }                                                                                                                           \
                                                                                                                                                    \
result_type operator()()                                                                                                                            \
{                                                                                                                                                   \
	long info(0);                                                                                                                                   \
	result_type result;                                                                                                                             \
    acml_function(1, dist_params, &(helper_type::ref(_eng).state()[0]), &result, &info);                                                            \
	boost::random::acml::check_errcode(info);                                                                                                       \
	return result;                                                                                                                                  \
}                                                                                                                                                   \
                                                                                                                                                    \                                                                                                                                                    \
template<class UnitStrideIterator>                                                                                                                  \
void operator()(UnitStrideIterator begin, UnitStrideIterator end)                                                                                   \
{                                                                                                                                                   \
	long info(0);                                                                                                                                   \
	acml_function(end-begin, dist_params, &(helper_type::ref(_eng).state()[0]), &(*begin), &info);                                                  \
	boost::random::acml::check_errcode(info);                                                                                                       \
}                                                                                                                                                   \
                                                                                                                                                    \
distribution_type& distribution() { return _dist; }                                                                                                 \
                                                                                                                                                    \
const distribution_type& distribution() const { return _dist; }                                                                                     \
                                                                                                                                                    \
result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () const { return (distribution().min)(); }                                                        \
                                                                                                                                                    \
result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () const { return (distribution().max)(); }                                                        \
                                                                                                                                                    \
engine_value_type& engine() { return helper_type::ref(_eng); }                                                                                      \
                                                                                                                                                    \
const engine_value_type& engine() const { return helper_type::ref(_eng); }                                                                          \
                                                                                                                                                    \
private:                                                                                                                                            \
                                                                                                                                                    \
acml_engine_type _eng;                                                                                                                              \
distribution_type _dist;


#define BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_TR1(Distribution, single, acml_function, dist_params)                                    \
template<long genid, long subid>                                                                                                                    \
class variate_generator<boost::random::acml::engine<genid,single,subid>,Distribution>                                                               \
{                                                                                                                                                   \
    BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY_TR1(                                                                                    \
		BOOST_RANDOM_ACML_CONCAT(boost::random::acml::engine<genid,single,subid>),                                                                  \
		BOOST_RANDOM_ACML_CONCAT(Distribution),                                                                                                     \
		acml_function,                                                                                                                              \
		BOOST_RANDOM_ACML_CONCAT(dist_params)                                                                                                       \                                                                                                    \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<long genid, long subid>                                                                                                                    \
class variate_generator<boost::random::acml::engine<genid,single,subid>&,Distribution>                                                              \
{                                                                                                                                                   \
    BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY_TR1(                                                                                    \
		BOOST_RANDOM_ACML_CONCAT(boost::random::acml::engine<genid,single,subid>&),                                                                 \
		BOOST_RANDOM_ACML_CONCAT(Distribution),                                                                                                     \
		acml_function,                                                                                                                              \
		BOOST_RANDOM_ACML_CONCAT(dist_params)                                                                                                       \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<long genid, long subid>                                                                                                                    \
class variate_generator<boost::random::acml::engine<genid,single,subid>*,Distribution>                                                              \
{                                                                                                                                                   \
    BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY_TR1(                                                                                    \
		BOOST_RANDOM_ACML_CONCAT(boost::random::acml::engine<genid,single,subid>*),                                                                 \
		BOOST_RANDOM_ACML_CONCAT(Distribution),                                                                                                     \
		acml_function,                                                                                                                              \
		BOOST_RANDOM_ACML_CONCAT(dist_params)                                                                                                       \
	)                                                                                                                                               \
};                                                                                                                                                  \
template <long genid, long subid> struct is_variate_generator_a_acml_range_generator<boost::random::acml::engine<genid,single,subid>, Distribution> : public boost::mpl::true_ {};\
template <long genid, long subid> struct is_variate_generator_a_acml_range_generator<boost::random::acml::engine<genid,single,subid>&,Distribution> : public boost::mpl::true_ {};\
template <long genid, long subid> struct is_variate_generator_a_acml_range_generator<boost::random::acml::engine<genid,single,subid>*,Distribution> : public boost::mpl::true_ {};



#define BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY_DISC_UNIFORM(acml_engine_type, Distribution, acml_function, dist_params, value_params, dist_param_min, dist_param_max, value_param_min, value_param_max)  \
private:                                                                                                                                            \
                                                                                                                                                    \
typedef boost::random::detail::ptr_helper<acml_engine_type> helper_type;                                                                            \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
typedef typename helper_type::value_type engine_value_type;                                                                                         \
typedef acml_engine_type engine_type;                                                                                                               \
typedef Distribution distribution_type;                                                                                                             \
typedef typename Distribution::result_type result_type;                                                                                             \
typedef boost::range_generate::unit_stride_range_generator_type_checked<result_type> is_range_generator;                                            \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
variate_generator(acml_engine_type e, Distribution d)                                                                                               \
  : _eng(e), _dist(d) { }                                                                                                                           \
                                                                                                                                                    \
result_type operator()()                                                                                                                            \
{                                                                                                                                                   \
	if ( dist_param_min > std::numeric_limits<result_type>::max() - dist_param_max )                                                                \
	{                                                                                                                                               \
		return _dist(helper_type::ref(_eng));                                                                                                       \
	} else                                                                                                                                          \
	{                                                                                                                                               \
		long info(0);                                                                                                                               \
		result_type result;                                                                                                                         \
    	acml_function(1, dist_params, &(helper_type::ref(_eng).state()[0]), &result, &info);                                                        \
		boost::random::acml::check_errcode(info);                                                                                                   \
		return result;                                                                                                                              \
	}                                                                                                                                               \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class T>                                                                                                                                   \
result_type operator()(const T& value)                                                                                                              \
{                                                                                                                                                   \
	if ( value_param_min > std::numeric_limits<result_type>::max() - value_param_max )                                                              \
	{                                                                                                                                               \
		return _dist(helper_type::ref(_eng), value);                                                                                                \
	} else                                                                                                                                          \
	{                                                                                                                                               \
		long info(0);                                                                                                                               \
		result_type result;                                                                                                                         \
    	acml_function(1, value_params, &(helper_type::ref(_eng).state()[0]), &result, &info);                                                       \
		boost::random::acml::check_errcode(info);                                                                                                   \
		return result;                                                                                                                              \
	}                                                                                                                                               \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class UnitStrideIterator>                                                                                                                  \
void operator()(UnitStrideIterator begin, UnitStrideIterator end)                                                                                   \
{                                                                                                                                                   \
	if ( dist_param_min > std::numeric_limits<result_type>::max() - dist_param_max )                                                                \
	{                                                                                                                                               \
		while (begin != end)                                                                                                                        \
		{                                                                                                                                           \
			*begin++ = _dist(helper_type::ref(_eng));                                                                                               \
		}                                                                                                                                           \
	} else                                                                                                                                          \
	{                                                                                                                                               \
		long info(0);                                                                                                                               \
		acml_function(end-begin, dist_params, &(helper_type::ref(_eng).state()[0]), &(*begin), &info);                                              \
		boost::random::acml::check_errcode(info);                                                                                                   \
	}                                                                                                                                               \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class UnitStrideIterator, class T>                                                                                                         \
void operator()(UnitStrideIterator begin, UnitStrideIterator end, const T& value)                                                                   \
{                                                                                                                                                   \
	if ( value_param_min > std::numeric_limits<result_type>::max() - value_param_max )                                                              \
	{                                                                                                                                               \
		while (begin != end)                                                                                                                        \
		{                                                                                                                                           \
			*begin++ = _dist(helper_type::ref(_eng), value);                                                                                        \
		}                                                                                                                                           \
	} else                                                                                                                                          \
	{                                                                                                                                               \
		long info(0);                                                                                                                               \
		acml_function(end-begin, value_params, &(helper_type::ref(_eng).state()[0]), &(*begin), &info);                                             \
		boost::random::acml::check_errcode(info);                                                                                                   \
	}                                                                                                                                               \
}                                                                                                                                                   \
                                                                                                                                                    \
distribution_type& distribution() { return _dist; }                                                                                                 \
                                                                                                                                                    \
const distribution_type& distribution() const { return _dist; }                                                                                     \
                                                                                                                                                    \
result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () const { return (distribution().min)(); }                                                        \
                                                                                                                                                    \
result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () const { return (distribution().max)(); }                                                        \
                                                                                                                                                    \
engine_value_type& engine() { return helper_type::ref(_eng); }                                                                                      \
                                                                                                                                                    \
const engine_value_type& engine() const { return helper_type::ref(_eng); }                                                                          \
                                                                                                                                                    \
private:                                                                                                                                            \
                                                                                                                                                    \
acml_engine_type _eng;                                                                                                                              \
distribution_type _dist;


#define BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_DISC_UNIFORM(Distribution, single, acml_function, dist_params, value_params, dist_param_min, dist_param_max, value_param_min, value_param_max)\
template<long genid, long subid>                                                                                                                    \
class variate_generator<boost::random::acml::engine<genid,single,subid>,Distribution>                                                               \
{                                                                                                                                                   \
    BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY_DISC_UNIFORM(                                                                           \
		BOOST_RANDOM_ACML_CONCAT(boost::random::acml::engine<genid,single,subid>),                                                                  \
		BOOST_RANDOM_ACML_CONCAT(Distribution),                                                                                                     \
		acml_function,                                                                                                                              \
		BOOST_RANDOM_ACML_CONCAT(dist_params),                                                                                                      \
		BOOST_RANDOM_ACML_CONCAT(value_params),                                                                                                     \
		dist_param_min,                                                                                                                             \
		dist_param_max,                                                                                                                             \
		value_param_min,                                                                                                                            \
		value_param_max                                                                                                                             \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<long genid, long subid>                                                                                                                    \
class variate_generator<boost::random::acml::engine<genid,single,subid>&,Distribution>                                                              \
{                                                                                                                                                   \
    BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY_DISC_UNIFORM(                                                                           \
		BOOST_RANDOM_ACML_CONCAT(boost::random::acml::engine<genid,single,subid>&),                                                                 \
		BOOST_RANDOM_ACML_CONCAT(Distribution),                                                                                                     \
		acml_function,                                                                                                                              \
		BOOST_RANDOM_ACML_CONCAT(dist_params),                                                                                                      \
		BOOST_RANDOM_ACML_CONCAT(value_params),                                                                                                     \
		dist_param_min,                                                                                                                             \
		dist_param_max,                                                                                                                             \
		value_param_min,                                                                                                                            \
		value_param_max                                                                                                                             \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<long genid, long subid>                                                                                                                    \
class variate_generator<boost::random::acml::engine<genid,single,subid>*,Distribution>                                                              \
{                                                                                                                                                   \
    BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY_DISC_UNIFORM(                                                                           \
		BOOST_RANDOM_ACML_CONCAT(boost::random::acml::engine<genid,single,subid>*),                                                                 \
		BOOST_RANDOM_ACML_CONCAT(Distribution),                                                                                                     \
		acml_function,                                                                                                                              \
		BOOST_RANDOM_ACML_CONCAT(dist_params),                                                                                                      \
		BOOST_RANDOM_ACML_CONCAT(value_params),                                                                                                     \
		dist_param_min,                                                                                                                             \
		dist_param_max,                                                                                                                             \
		value_param_min,                                                                                                                            \
		value_param_max                                                                                                                             \
	)                                                                                                                                               \
};                                                                                                                                                  \
template <long genid, long subid> struct is_variate_generator_a_acml_range_generator<boost::random::acml::engine<genid,single,subid>, Distribution> : public boost::mpl::true_ {};\
template <long genid, long subid> struct is_variate_generator_a_acml_range_generator<boost::random::acml::engine<genid,single,subid>&,Distribution> : public boost::mpl::true_ {};\
template <long genid, long subid> struct is_variate_generator_a_acml_range_generator<boost::random::acml::engine<genid,single,subid>*,Distribution> : public boost::mpl::true_ {};



#define BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY_DISC_UNIFORM_TR1(acml_engine_type, Distribution, acml_function, dist_params, dist_param_min, dist_param_max)  \
private:                                                                                                                                            \
                                                                                                                                                    \
typedef boost::random::detail::ptr_helper<acml_engine_type> helper_type;                                                                            \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
typedef typename helper_type::value_type engine_value_type;                                                                                         \
typedef acml_engine_type engine_type;                                                                                                               \
typedef Distribution distribution_type;                                                                                                             \
typedef typename Distribution::result_type result_type;                                                                                             \
typedef boost::range_generate::unit_stride_range_generator_type_checked<result_type> is_range_generator;                                            \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
variate_generator(acml_engine_type e, Distribution d)                                                                                               \
  : _eng(e), _dist(d) { }                                                                                                                           \
                                                                                                                                                    \
result_type operator()()                                                                                                                            \
{                                                                                                                                                   \
	if ( dist_param_min > std::numeric_limits<result_type>::max() - dist_param_max )                                                                \
	{                                                                                                                                               \
		return _dist(helper_type::ref(_eng));                                                                                                       \
	} else                                                                                                                                          \
	{                                                                                                                                               \
		long info(0);                                                                                                                               \
		result_type result;                                                                                                                         \
    	acml_function(1, dist_params, &(helper_type::ref(_eng).state()[0]), &result, &info);                                                        \
		boost::random::acml::check_errcode(info);                                                                                                   \
		return result;                                                                                                                              \
	}                                                                                                                                               \
}                                                                                                                                                   \
                                                                                                                                                    \                                                                                                                                                    \
template<class UnitStrideIterator>                                                                                                                  \
void operator()(UnitStrideIterator begin, UnitStrideIterator end)                                                                                   \
{                                                                                                                                                   \
	if ( dist_param_min > std::numeric_limits<result_type>::max() - dist_param_max )                                                                \
	{                                                                                                                                               \
		while (begin != end)                                                                                                                        \
		{                                                                                                                                           \
			*begin++ = _dist(helper_type::ref(_eng));                                                                                               \
		}                                                                                                                                           \
	} else                                                                                                                                          \
	{                                                                                                                                               \
		long info(0);                                                                                                                               \
		acml_function(end-begin, dist_params, &(helper_type::ref(_eng).state()[0]), &(*begin), &info);                                              \
		boost::random::acml::check_errcode(info);                                                                                                   \
	}                                                                                                                                               \
}                                                                                                                                                   \
                                                                                                                                                    \                                                                                                                                                    \
distribution_type& distribution() { return _dist; }                                                                                                 \
                                                                                                                                                    \
const distribution_type& distribution() const { return _dist; }                                                                                     \
                                                                                                                                                    \
result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () const { return (distribution().min)(); }                                                        \
                                                                                                                                                    \
result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () const { return (distribution().max)(); }                                                        \
                                                                                                                                                    \
engine_value_type& engine() { return helper_type::ref(_eng); }                                                                                      \
                                                                                                                                                    \
const engine_value_type& engine() const { return helper_type::ref(_eng); }                                                                          \
                                                                                                                                                    \
private:                                                                                                                                            \
                                                                                                                                                    \
acml_engine_type _eng;                                                                                                                              \
distribution_type _dist;


#define BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_DISC_UNIFORM_TR1(Distribution, single, acml_function, dist_params, dist_param_min, dist_param_max)\
template<long genid, long subid>                                                                                                                    \
class variate_generator<boost::random::acml::engine<genid,single,subid>,Distribution>                                                               \
{                                                                                                                                                   \
    BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY_DISC_UNIFORM_TR1(                                                                       \
		BOOST_RANDOM_ACML_CONCAT(boost::random::acml::engine<genid,single,subid>),                                                                  \
		BOOST_RANDOM_ACML_CONCAT(Distribution),                                                                                                     \
		acml_function,                                                                                                                              \
		BOOST_RANDOM_ACML_CONCAT(dist_params),                                                                                                      \
		dist_param_min,                                                                                                                             \
		dist_param_max                                                                                                                              \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<long genid, long subid>                                                                                                                    \
class variate_generator<boost::random::acml::engine<genid,single,subid>&,Distribution>                                                              \
{                                                                                                                                                   \
    BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY_DISC_UNIFORM_TR1(                                                                       \
		BOOST_RANDOM_ACML_CONCAT(boost::random::acml::engine<genid,single,subid>&),                                                                 \
		BOOST_RANDOM_ACML_CONCAT(Distribution),                                                                                                     \
		acml_function,                                                                                                                              \
		BOOST_RANDOM_ACML_CONCAT(dist_params),                                                                                                      \
		dist_param_min,                                                                                                                             \
		dist_param_max                                                                                                                              \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<long genid, long subid>                                                                                                                    \
class variate_generator<boost::random::acml::engine<genid,single,subid>*,Distribution>                                                              \
{                                                                                                                                                   \
    BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY_DISC_UNIFORM_TR1(                                                                       \
		BOOST_RANDOM_ACML_CONCAT(boost::random::acml::engine<genid,single,subid>*),                                                                 \
		BOOST_RANDOM_ACML_CONCAT(Distribution),                                                                                                     \
		acml_function,                                                                                                                              \
		BOOST_RANDOM_ACML_CONCAT(dist_params),                                                                                                      \
		dist_param_min,                                                                                                                             \
		dist_param_max                                                                                                                              \
	)                                                                                                                                               \
};                                                                                                                                                  \
template <long genid, long subid> struct is_variate_generator_a_acml_range_generator<boost::random::acml::engine<genid,single,subid>, Distribution> : public boost::mpl::true_ {};\
template <long genid, long subid> struct is_variate_generator_a_acml_range_generator<boost::random::acml::engine<genid,single,subid>&,Distribution> : public boost::mpl::true_ {};\
template <long genid, long subid> struct is_variate_generator_a_acml_range_generator<boost::random::acml::engine<genid,single,subid>*,Distribution> : public boost::mpl::true_ {};










#define BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY_2(acml_engine_type, Distribution, acml_function, dist_params, value_params, ResultType) \
private:                                                                                                                                            \
                                                                                                                                                    \
typedef boost::random::detail::ptr_helper<acml_engine_type> helper_type;                                                                            \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
typedef typename helper_type::value_type engine_value_type;                                                                                         \
typedef acml_engine_type engine_type;                                                                                                               \
typedef Distribution distribution_type;                                                                                                             \
typedef ResultType result_type;                                                                                                                     \
typedef boost::range_generate::unit_stride_range_generator_type_checked<result_type> is_range_generator;                                            \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
variate_generator(acml_engine_type e, Distribution d)                                                                                               \
  : _eng(e), _dist(d) { }                                                                                                                           \
                                                                                                                                                    \
result_type operator()()                                                                                                                            \
{                                                                                                                                                   \
	long info(0);                                                                                                                                   \
	result_type result;                                                                                                                             \
    acml_function(1, dist_params, &(helper_type::ref(_eng).state()[0]), &result, &info);                                                            \
	boost::random::acml::check_errcode(info);                                                                                                       \
	return result;                                                                                                                                  \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class T>                                                                                                                                   \
result_type operator()(const T& value)                                                                                                              \
{                                                                                                                                                   \
	long info(0);                                                                                                                                   \
	result_type result;                                                                                                                             \
    acml_function(1, value_params, &(helper_type::ref(_eng).state()[0]), &result, &info);                                                           \
	boost::random::acml::check_errcode(info);                                                                                                       \
	return result;                                                                                                                                  \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class UnitStrideIterator>                                                                                                                  \
void operator()(UnitStrideIterator begin, UnitStrideIterator end)                                                                                   \
{                                                                                                                                                   \
	long info(0);                                                                                                                                   \
	acml_function(end-begin, dist_params, &(helper_type::ref(_eng).state()[0]), &(*begin), &info);                                                  \
	boost::random::acml::check_errcode(info);                                                                                                       \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class UnitStrideIterator, class T>                                                                                                         \
void operator()(UnitStrideIterator begin, UnitStrideIterator end, const T& value)                                                                   \
{                                                                                                                                                   \
	long info(0);                                                                                                                                   \
	acml_function(end-begin, value_params, &(helper_type::ref(_eng).state()[0]), &(*begin), &info);                                                 \
	boost::random::acml::check_errcode(info);                                                                                                       \
}                                                                                                                                                   \
                                                                                                                                                    \
distribution_type& distribution() { return _dist; }                                                                                                 \
                                                                                                                                                    \
const distribution_type& distribution() const { return _dist; }                                                                                     \
                                                                                                                                                    \
result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () const { return (distribution().min)(); }                                                        \
                                                                                                                                                    \
result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () const { return (distribution().max)(); }                                                        \
                                                                                                                                                    \
engine_value_type& engine() { return helper_type::ref(_eng); }                                                                                      \
                                                                                                                                                    \
const engine_value_type& engine() const { return helper_type::ref(_eng); }                                                                          \
                                                                                                                                                    \
private:                                                                                                                                            \
                                                                                                                                                    \
acml_engine_type _eng;                                                                                                                              \
distribution_type _dist;


#define BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_2(Distribution, single, acml_function, dist_params, value_params, result_type)           \
template<long genid, long subid>                                                                                                                    \
class variate_generator<boost::random::acml::engine<genid,single,subid>,Distribution>                                                               \
{                                                                                                                                                   \
    BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY_2(                                                                                      \
		BOOST_RANDOM_ACML_CONCAT(boost::random::acml::engine<genid,single,subid>),                                                                  \
		BOOST_RANDOM_ACML_CONCAT(Distribution),                                                                                                     \
		acml_function,                                                                                                                              \
		BOOST_RANDOM_ACML_CONCAT(dist_params),                                                                                                      \
		BOOST_RANDOM_ACML_CONCAT(value_params),                                                                                                     \
		result_type                                                                                                                                 \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<long genid, long subid>                                                                                                                    \
class variate_generator<boost::random::acml::engine<genid,single,subid>&,Distribution>                                                              \
{                                                                                                                                                   \
    BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY_2(                                                                                      \
		BOOST_RANDOM_ACML_CONCAT(boost::random::acml::engine<genid,single,subid>&),                                                                 \
		BOOST_RANDOM_ACML_CONCAT(Distribution),                                                                                                     \
		acml_function,                                                                                                                              \
		BOOST_RANDOM_ACML_CONCAT(dist_params),                                                                                                      \
		BOOST_RANDOM_ACML_CONCAT(value_params),                                                                                                     \
		result_type                                                                                                                                 \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<long genid, long subid>                                                                                                                    \
class variate_generator<boost::random::acml::engine<genid,single,subid>*,Distribution>                                                              \
{                                                                                                                                                   \
    BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY_2(                                                                                      \
		BOOST_RANDOM_ACML_CONCAT(boost::random::acml::engine<genid,single,subid>*),                                                                 \
		BOOST_RANDOM_ACML_CONCAT(Distribution),                                                                                                     \
		acml_function,                                                                                                                              \
		BOOST_RANDOM_ACML_CONCAT(dist_params),                                                                                                      \
		BOOST_RANDOM_ACML_CONCAT(value_params),                                                                                                     \
		result_type                                                                                                                                 \
	)                                                                                                                                               \
};                                                                                                                                                  \
template <long genid, long subid> struct is_variate_generator_a_acml_range_generator<boost::random::acml::engine<genid,single,subid>, Distribution> : public boost::mpl::true_ {};\
template <long genid, long subid> struct is_variate_generator_a_acml_range_generator<boost::random::acml::engine<genid,single,subid>&,Distribution> : public boost::mpl::true_ {};\
template <long genid, long subid> struct is_variate_generator_a_acml_range_generator<boost::random::acml::engine<genid,single,subid>*,Distribution> : public boost::mpl::true_ {};



/*#define BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY_MIN_MAX(acml_engine_type, Distribution, acml_function, dist_params, value_params, ResultType, minimum, maximum)\
private:                                                                                                                                            \
                                                                                                                                                    \
typedef boost::random::detail::ptr_helper<acml_engine_type> helper_type;                                                                            \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
typedef typename helper_type::value_type engine_value_type;                                                                                         \
typedef acml_engine_type engine_type;                                                                                                               \
typedef Distribution distribution_type;                                                                                                             \
typedef ResultType result_type;                                                                                                                     \
typedef boost::range_generate::unit_stride_range_generator_type_checked<result_type> is_range_generator;                                            \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
variate_generator(acml_engine_type e, Distribution d)                                                                                               \
  : _eng(e), _dist(d) { }                                                                                                                           \
                                                                                                                                                    \
result_type operator()()                                                                                                                            \
{                                                                                                                                                   \
	long info(0);                                                                                                                                   \
	result_type result;                                                                                                                             \
    acml_function(1, dist_params, &(helper_type::ref(_eng).state()[0]), &result, &info);                                                            \
	boost::random::acml::check_errcode(info);                                                                                                       \
	return result;                                                                                                                                  \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class T>                                                                                                                                   \
result_type operator()(const T& value)                                                                                                              \
{                                                                                                                                                   \
	long info(0);                                                                                                                                   \
	result_type result;                                                                                                                             \
    acml_function(1, value_params, &(helper_type::ref(_eng).state()[0]), &result, &info);                                                           \
	boost::random::acml::check_errcode(info);                                                                                                       \
	return result;                                                                                                                                  \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class UnitStrideIterator>                                                                                                                  \
void operator()(UnitStrideIterator begin, UnitStrideIterator end)                                                                                   \
{                                                                                                                                                   \
	long info(0);                                                                                                                                   \
	acml_function(end-begin, dist_params, &(helper_type::ref(_eng).state()[0]), &(*begin), &info);                                                  \
	boost::random::acml::check_errcode(info);                                                                                                       \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class UnitStrideIterator, class T>                                                                                                         \
void operator()(UnitStrideIterator begin, UnitStrideIterator end, const T& value)                                                                   \
{                                                                                                                                                   \
	long info(0);                                                                                                                                   \
	acml_function(end-begin, value_params, &(helper_type::ref(_eng).state()[0]), &(*begin), &info);                                                 \
	boost::random::acml::check_errcode(info);                                                                                                       \
}                                                                                                                                                   \
                                                                                                                                                    \
distribution_type& distribution() { return _dist; }                                                                                                 \
                                                                                                                                                    \
const distribution_type& distribution() const { return _dist; }                                                                                     \
                                                                                                                                                    \
result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () const { return maximum; }                                                                       \
                                                                                                                                                    \
result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () const { return minimum; }                                                                       \
                                                                                                                                                    \
engine_value_type& engine() { return helper_type::ref(_eng); }                                                                                      \
                                                                                                                                                    \
const engine_value_type& engine() const { return helper_type::ref(_eng); }                                                                          \
                                                                                                                                                    \
private:                                                                                                                                            \
                                                                                                                                                    \
acml_engine_type _eng;                                                                                                                              \
distribution_type _dist;

#define BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_MIN_MAX(Distribution, single, acml_function, dist_params, value_params, result_type, mimimum, maximum)\
template<long genid, long subid>                                                                                                                    \
class variate_generator<boost::random::acml::engine<genid,single,subid>,Distribution>                                                               \
{                                                                                                                                                   \
    BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY_MIN_MAX(                                                                                \
		BOOST_RANDOM_ACML_CONCAT(boost::random::acml::engine<genid,single,subid>),                                                                  \
		BOOST_RANDOM_ACML_CONCAT(Distribution),                                                                                                     \
		acml_function,                                                                                                                              \
		BOOST_RANDOM_ACML_CONCAT(dist_params),                                                                                                      \
		BOOST_RANDOM_ACML_CONCAT(value_params),                                                                                                     \
		result_type,                                                                                                                                \
		minimum,                                                                                                                                    \
		maximum                                                                                                                                     \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<long genid, long subid>                                                                                                                    \
class variate_generator<boost::random::acml::engine<genid,single,subid>&,Distribution>                                                              \
{                                                                                                                                                   \
    BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY_MIN_MAX(                                                                                \
		BOOST_RANDOM_ACML_CONCAT(boost::random::acml::engine<genid,single,subid>&),                                                                 \
		BOOST_RANDOM_ACML_CONCAT(Distribution),                                                                                                     \
		acml_function,                                                                                                                              \
		BOOST_RANDOM_ACML_CONCAT(dist_params),                                                                                                      \
		BOOST_RANDOM_ACML_CONCAT(value_params),                                                                                                     \
		result_type,                                                                                                                                \
		minimum,                                                                                                                                    \
		maximum                                                                                                                                     \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<long genid, long subid>                                                                                                                    \
class variate_generator<boost::random::acml::engine<genid,single,subid>*,Distribution>                                                              \
{                                                                                                                                                   \
    BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPEZIALIZATION_BODY_MIN_MAX(                                                                                \
		BOOST_RANDOM_ACML_CONCAT(boost::random::acml::engine<genid,single,subid>*),                                                                 \
		BOOST_RANDOM_ACML_CONCAT(Distribution),                                                                                                     \
		acml_function,                                                                                                                              \
		BOOST_RANDOM_ACML_CONCAT(dist_params),                                                                                                      \
		BOOST_RANDOM_ACML_CONCAT(value_params),                                                                                                     \
		result_type,                                                                                                                                \
		minimum,                                                                                                                                    \
		maximum                                                                                                                                     \
	)                                                                                                                                               \
};                                                                                                                                                  \
template <long genid, long subid> struct is_variate_generator_a_acml_range_generator<boost::random::acml::engine<genid,single,subid>, Distribution> : public boost::mpl::true_ {};\
template <long genid, long subid> struct is_variate_generator_a_acml_range_generator<boost::random::acml::engine<genid,single,subid>&,Distribution> : public boost::mpl::true_ {};\
template <long genid, long subid> struct is_variate_generator_a_acml_range_generator<boost::random::acml::engine<genid,single,subid>*,Distribution> : public boost::mpl::true_ {};
*/

#endif // DOXYGEN_SHOULD_SKIP_THIS

namespace boost {
namespace random {

template <class Engine, class Distribution>
struct is_variate_generator_a_acml_range_generator : public boost::mpl::false_ {};

} // random
} // boost

#endif // BOOST_RANDOM_ACML_VARIATE_GENERATOR_SPECIALIZATION_HPP

