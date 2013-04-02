// Copyright Fabian Bösch 2012
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 *  @file 
 *  @brief This file contains macros used for specializing the template class variate_generator with MKL engines.
 */


#ifndef BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPECIALIZATION_HPP
#define BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPECIALIZATION_HPP

#include <boost/random/variate_generator.hpp>
#include <boost/generate/generate.hpp>
#include <boost/mpl/bool.hpp>
#include <limits>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#define BOOST_RANDOM_MKL_CONCAT(...) __VA_ARGS__


#define BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY(mkl_engine_type, Distribution, vsl_function, vsl_method, dist_params, value_params)  \
private:                                                                                                                                            \
                                                                                                                                                    \
typedef boost::random::detail::ptr_helper<mkl_engine_type> helper_type;                                                                             \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
typedef typename helper_type::value_type engine_value_type;                                                                                         \
typedef mkl_engine_type engine_type;                                                                                                                \
typedef Distribution distribution_type;                                                                                                             \
typedef typename Distribution::result_type result_type;                                                                                             \
typedef boost::range_generate::unit_stride_range_generator_type_checked<result_type> is_range_generator;                                            \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
variate_generator(mkl_engine_type e, Distribution d)                                                                                                \
  : _eng(e), _dist(d) { }                                                                                                                           \
                                                                                                                                                    \
result_type operator()()                                                                                                                            \
{                                                                                                                                                   \
	result_type result;                                                                                                                             \
    boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), 1, &result, dist_params) );                   \
    return result;                                                                                                                                  \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class T>                                                                                                                                   \
result_type operator()(const T& value)                                                                                                              \
{                                                                                                                                                   \
	result_type result;                                                                                                                             \
    boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), 1, &result, value_params) );                  \
    return result;                                                                                                                                  \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class UnitStrideIterator>                                                                                                                  \
void operator()(UnitStrideIterator begin, UnitStrideIterator end)                                                                                   \
{                                                                                                                                                   \
    boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), end-begin, &(*begin), dist_params ) );        \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class UnitStrideIterator, class T>                                                                                                         \
void operator()(UnitStrideIterator begin, UnitStrideIterator end, const T& value)                                                                   \
{                                                                                                                                                   \
    boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), end-begin, &(*begin), value_params ) );       \
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
mkl_engine_type _eng;                                                                                                                               \
distribution_type _dist;


#define BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION(Distribution,  vsl_function, vsl_method, dist_params, value_params)                       \
template<int brng>                                                                                                                                  \
class variate_generator<boost::random::mkl::engine<brng>,Distribution>                                                                              \
{                                                                                                                                                   \
    BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY(                                                                                         \
		boost::random::mkl::engine<brng>,                                                                                                           \
		BOOST_RANDOM_MKL_CONCAT(Distribution),                                                                                                      \
		vsl_function,                                                                                                                               \
		vsl_method,                                                                                                                                 \
		BOOST_RANDOM_MKL_CONCAT(dist_params),                                                                                                       \
		BOOST_RANDOM_MKL_CONCAT(value_params)                                                                                                       \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<int brng>                                                                                                                                  \
class variate_generator<boost::random::mkl::engine<brng>&,Distribution>                                                                             \
{                                                                                                                                                   \
    BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY(                                                                                         \
		boost::random::mkl::engine<brng>&,                                                                                                          \
		BOOST_RANDOM_MKL_CONCAT(Distribution),                                                                                                      \
		vsl_function,                                                                                                                               \
		vsl_method,                                                                                                                                 \
		BOOST_RANDOM_MKL_CONCAT(dist_params),                                                                                                       \
		BOOST_RANDOM_MKL_CONCAT(value_params)                                                                                                       \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<int brng>                                                                                                                                  \
class variate_generator<boost::random::mkl::engine<brng>*,Distribution>                                                                             \
{                                                                                                                                                   \
    BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY(                                                                                         \
		boost::random::mkl::engine<brng>*,                                                                                                          \
		BOOST_RANDOM_MKL_CONCAT(Distribution),                                                                                                      \
		vsl_function,                                                                                                                               \
		vsl_method,                                                                                                                                 \
		BOOST_RANDOM_MKL_CONCAT(dist_params),                                                                                                       \
		BOOST_RANDOM_MKL_CONCAT(value_params)                                                                                                       \
	)                                                                                                                                               \
};                                                                                                                                                  \
template <int brng> struct is_variate_generator_a_mkl_range_generator<boost::random::mkl::engine<brng>, Distribution> : public boost::mpl::true_ {};\
template <int brng> struct is_variate_generator_a_mkl_range_generator<boost::random::mkl::engine<brng>&,Distribution> : public boost::mpl::true_ {};\
template <int brng> struct is_variate_generator_a_mkl_range_generator<boost::random::mkl::engine<brng>*,Distribution> : public boost::mpl::true_ {};


#define BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_TR1(mkl_engine_type, Distribution, vsl_function, vsl_method, dist_params)            \
private:                                                                                                                                            \
                                                                                                                                                    \
typedef boost::random::detail::ptr_helper<mkl_engine_type> helper_type;                                                                             \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
typedef typename helper_type::value_type engine_value_type;                                                                                         \
typedef mkl_engine_type engine_type;                                                                                                                \
typedef Distribution distribution_type;                                                                                                             \
typedef typename Distribution::result_type result_type;                                                                                             \
typedef boost::range_generate::unit_stride_range_generator_type_checked<result_type> is_range_generator;                                            \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
variate_generator(mkl_engine_type e, Distribution d)                                                                                                \
  : _eng(e), _dist(d) { }                                                                                                                           \
                                                                                                                                                    \
result_type operator()()                                                                                                                            \
{                                                                                                                                                   \
	result_type result;                                                                                                                             \
    boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), 1, &result, dist_params) );                   \
    return result;                                                                                                                                  \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class UnitStrideIterator>                                                                                                                  \
void operator()(UnitStrideIterator begin, UnitStrideIterator end)                                                                                   \
{                                                                                                                                                   \
    boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), end-begin, &(*begin), dist_params ) );        \
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
mkl_engine_type _eng;                                                                                                                               \
distribution_type _dist;


#define BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_TR1(Distribution,  vsl_function, vsl_method, dist_params)                                 \
template<int brng>                                                                                                                                  \
class variate_generator<boost::random::mkl::engine<brng>,Distribution>                                                                              \
{                                                                                                                                                   \
    BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_TR1(                                                                                     \
		boost::random::mkl::engine<brng>,                                                                                                           \
		BOOST_RANDOM_MKL_CONCAT(Distribution),                                                                                                      \
		vsl_function,                                                                                                                               \
		vsl_method,                                                                                                                                 \
		BOOST_RANDOM_MKL_CONCAT(dist_params)                                                                                                        \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<int brng>                                                                                                                                  \
class variate_generator<boost::random::mkl::engine<brng>&,Distribution>                                                                             \
{                                                                                                                                                   \
    BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_TR1(                                                                                     \
		boost::random::mkl::engine<brng>&,                                                                                                          \
		BOOST_RANDOM_MKL_CONCAT(Distribution),                                                                                                      \
		vsl_function,                                                                                                                               \
		vsl_method,                                                                                                                                 \
		BOOST_RANDOM_MKL_CONCAT(dist_params)                                                                                                        \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<int brng>                                                                                                                                  \
class variate_generator<boost::random::mkl::engine<brng>*,Distribution>                                                                             \
{                                                                                                                                                   \
    BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_TR1(                                                                                     \
		boost::random::mkl::engine<brng>*,                                                                                                          \
		BOOST_RANDOM_MKL_CONCAT(Distribution),                                                                                                      \
		vsl_function,                                                                                                                               \
		vsl_method,                                                                                                                                 \
		BOOST_RANDOM_MKL_CONCAT(dist_params)                                                                                                        \
	)                                                                                                                                               \
};                                                                                                                                                  \
template <int brng> struct is_variate_generator_a_mkl_range_generator<boost::random::mkl::engine<brng>, Distribution> : public boost::mpl::true_ {};\
template <int brng> struct is_variate_generator_a_mkl_range_generator<boost::random::mkl::engine<brng>&,Distribution> : public boost::mpl::true_ {};\
template <int brng> struct is_variate_generator_a_mkl_range_generator<boost::random::mkl::engine<brng>*,Distribution> : public boost::mpl::true_ {};



#define BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_DISC_UNIFORM(mkl_engine_type, Distribution, vsl_function, vsl_method, dist_params, value_params, dist_param_max, value_param_max)  \
private:                                                                                                                                            \
                                                                                                                                                    \
typedef boost::random::detail::ptr_helper<mkl_engine_type> helper_type;                                                                             \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
typedef typename helper_type::value_type engine_value_type;                                                                                         \
typedef mkl_engine_type engine_type;                                                                                                                \
typedef Distribution distribution_type;                                                                                                             \
typedef typename Distribution::result_type result_type;                                                                                             \
typedef boost::range_generate::unit_stride_range_generator_type_checked<result_type> is_range_generator;                                            \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
variate_generator(mkl_engine_type e, Distribution d)                                                                                                \
  : _eng(e), _dist(d) { }                                                                                                                           \
                                                                                                                                                    \
result_type operator()()                                                                                                                            \
{                                                                                                                                                   \
	if ( dist_param_max == std::numeric_limits<result_type>::max() )                                                                                \
	{                                                                                                                                               \
		return _dist(helper_type::ref(_eng));                                                                                                       \
	} else                                                                                                                                          \
	{                                                                                                                                               \
		result_type result;                                                                                                                         \
    	boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), 1, &result, dist_params + 1) );           \
    	return result;                                                                                                                              \
	}                                                                                                                                               \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class T>                                                                                                                                   \
result_type operator()(const T& value)                                                                                                              \
{                                                                                                                                                   \
	if ( value_param_max == std::numeric_limits<result_type>::max() )                                                                               \
	{                                                                                                                                               \
		return _dist(helper_type::ref(_eng), value);                                                                                                \
	} else                                                                                                                                          \
	{                                                                                                                                               \
		result_type result;                                                                                                                         \
    	boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), 1, &result, value_params + 1) );          \
    	return result;                                                                                                                              \
	}                                                                                                                                               \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class UnitStrideIterator>                                                                                                                  \
void operator()(UnitStrideIterator begin, UnitStrideIterator end)                                                                                   \
{                                                                                                                                                   \
	if ( dist_param_max == std::numeric_limits<result_type>::max() )                                                                                \
	{                                                                                                                                               \
		while (begin != end)                                                                                                                        \
		{                                                                                                                                           \
			*begin++ = _dist(helper_type::ref(_eng));                                                                                               \
		}                                                                                                                                           \
	} else                                                                                                                                          \
	{                                                                                                                                               \
    	boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), end-begin, &(*begin), dist_params + 1) ); \
	}                                                                                                                                               \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class UnitStrideIterator, class T>                                                                                                         \
void operator()(UnitStrideIterator begin, UnitStrideIterator end, const T& value)                                                                   \
{                                                                                                                                                   \
	if ( value_param_max == std::numeric_limits<result_type>::max() )                                                                               \
	{                                                                                                                                               \
		while (begin != end)                                                                                                                        \
		{                                                                                                                                           \
			*begin++ = _dist(helper_type::ref(_eng), value);                                                                                        \
		}                                                                                                                                           \
	} else                                                                                                                                          \
	{                                                                                                                                               \
		boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), end-begin, &(*begin), value_params + 1) );\
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
mkl_engine_type _eng;                                                                                                                               \
distribution_type _dist;


#define BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_DISC_UNIFORM(Distribution,  vsl_function, vsl_method, dist_params, value_params, dist_param_max, value_param_max)          \
template<int brng>                                                                                                                                  \
class variate_generator<boost::random::mkl::engine<brng>,Distribution>                                                                              \
{                                                                                                                                                   \
    BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_DISC_UNIFORM(                                                                            \
		boost::random::mkl::engine<brng>,                                                                                                           \
		BOOST_RANDOM_MKL_CONCAT(Distribution),                                                                                                      \
		vsl_function,                                                                                                                               \
		vsl_method,                                                                                                                                 \
		BOOST_RANDOM_MKL_CONCAT(dist_params),                                                                                                       \
		BOOST_RANDOM_MKL_CONCAT(value_params),                                                                                                      \
		dist_param_max,                                                                                                                             \
		value_param_max                                                                                                                             \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<int brng>                                                                                                                                  \
class variate_generator<boost::random::mkl::engine<brng>&,Distribution>                                                                             \
{                                                                                                                                                   \
    BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_DISC_UNIFORM(                                                                            \
		boost::random::mkl::engine<brng>&,                                                                                                          \
		BOOST_RANDOM_MKL_CONCAT(Distribution),                                                                                                      \
		vsl_function,                                                                                                                               \
		vsl_method,                                                                                                                                 \
		BOOST_RANDOM_MKL_CONCAT(dist_params),                                                                                                       \
		BOOST_RANDOM_MKL_CONCAT(value_params),                                                                                                      \
		dist_param_max,                                                                                                                             \
		value_param_max                                                                                                                             \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<int brng>                                                                                                                                  \
class variate_generator<boost::random::mkl::engine<brng>*,Distribution>                                                                             \
{                                                                                                                                                   \
    BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_DISC_UNIFORM(                                                                            \
		boost::random::mkl::engine<brng>*,                                                                                                          \
		BOOST_RANDOM_MKL_CONCAT(Distribution),                                                                                                      \
		vsl_function,                                                                                                                               \
		vsl_method,                                                                                                                                 \
		BOOST_RANDOM_MKL_CONCAT(dist_params),                                                                                                       \
		BOOST_RANDOM_MKL_CONCAT(value_params),                                                                                                      \
		dist_param_max,                                                                                                                             \
		value_param_max                                                                                                                             \
	)                                                                                                                                               \
};                                                                                                                                                  \
template <int brng> struct is_variate_generator_a_mkl_range_generator<boost::random::mkl::engine<brng>, Distribution> : public boost::mpl::true_ {};\
template <int brng> struct is_variate_generator_a_mkl_range_generator<boost::random::mkl::engine<brng>&,Distribution> : public boost::mpl::true_ {};\
template <int brng> struct is_variate_generator_a_mkl_range_generator<boost::random::mkl::engine<brng>*,Distribution> : public boost::mpl::true_ {};


#define BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_DISC_UNIFORM_TR1(mkl_engine_type, Distribution, vsl_function, vsl_method, dist_params, dist_param_max)  \
private:                                                                                                                                            \
                                                                                                                                                    \
typedef boost::random::detail::ptr_helper<mkl_engine_type> helper_type;                                                                             \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
typedef typename helper_type::value_type engine_value_type;                                                                                         \
typedef mkl_engine_type engine_type;                                                                                                                \
typedef Distribution distribution_type;                                                                                                             \
typedef typename Distribution::result_type result_type;                                                                                             \
typedef boost::range_generate::unit_stride_range_generator_type_checked<result_type> is_range_generator;                                            \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
variate_generator(mkl_engine_type e, Distribution d)                                                                                                \
  : _eng(e), _dist(d) { }                                                                                                                           \
                                                                                                                                                    \
result_type operator()()                                                                                                                            \
{                                                                                                                                                   \
	if ( dist_param_max == std::numeric_limits<result_type>::max() )                                                                                \
	{                                                                                                                                               \
		return _dist(helper_type::ref(_eng));                                                                                                       \
	} else                                                                                                                                          \
	{                                                                                                                                               \
		result_type result;                                                                                                                         \
    	boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), 1, &result, dist_params + 1) );           \
    	return result;                                                                                                                              \
	}                                                                                                                                               \
}                                                                                                                                                   \
                                                                                                                                                    \                                                                                                                                                    \
template<class UnitStrideIterator>                                                                                                                  \
void operator()(UnitStrideIterator begin, UnitStrideIterator end)                                                                                   \
{                                                                                                                                                   \
	if ( dist_param_max == std::numeric_limits<result_type>::max() )                                                                                \
	{                                                                                                                                               \
		while (begin != end)                                                                                                                        \
		{                                                                                                                                           \
			*begin++ = _dist(helper_type::ref(_eng));                                                                                               \
		}                                                                                                                                           \
	} else                                                                                                                                          \
	{                                                                                                                                               \
    	boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), end-begin, &(*begin), dist_params + 1) ); \
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
mkl_engine_type _eng;                                                                                                                               \
distribution_type _dist;


#define BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_DISC_UNIFORM_TR1(Distribution,  vsl_function, vsl_method, dist_params, dist_param_max)    \
template<int brng>                                                                                                                                  \
class variate_generator<boost::random::mkl::engine<brng>,Distribution>                                                                              \
{                                                                                                                                                   \
    BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_DISC_UNIFORM_TR1(                                                                        \
		boost::random::mkl::engine<brng>,                                                                                                           \
		BOOST_RANDOM_MKL_CONCAT(Distribution),                                                                                                      \
		vsl_function,                                                                                                                               \
		vsl_method,                                                                                                                                 \
		BOOST_RANDOM_MKL_CONCAT(dist_params),                                                                                                       \
		dist_param_max                                                                                                                              \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<int brng>                                                                                                                                  \
class variate_generator<boost::random::mkl::engine<brng>&,Distribution>                                                                             \
{                                                                                                                                                   \
    BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_DISC_UNIFORM_TR1(                                                                        \
		boost::random::mkl::engine<brng>&,                                                                                                          \
		BOOST_RANDOM_MKL_CONCAT(Distribution),                                                                                                      \
		vsl_function,                                                                                                                               \
		vsl_method,                                                                                                                                 \
		BOOST_RANDOM_MKL_CONCAT(dist_params),                                                                                                       \
		dist_param_max                                                                                                                              \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<int brng>                                                                                                                                  \
class variate_generator<boost::random::mkl::engine<brng>*,Distribution>                                                                             \
{                                                                                                                                                   \
    BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_DISC_UNIFORM_TR1(                                                                        \
		boost::random::mkl::engine<brng>*,                                                                                                          \
		BOOST_RANDOM_MKL_CONCAT(Distribution),                                                                                                      \
		vsl_function,                                                                                                                               \
		vsl_method,                                                                                                                                 \
		BOOST_RANDOM_MKL_CONCAT(dist_params),                                                                                                       \
		dist_param_max                                                                                                                              \
	)                                                                                                                                               \
};                                                                                                                                                  \
template <int brng> struct is_variate_generator_a_mkl_range_generator<boost::random::mkl::engine<brng>, Distribution> : public boost::mpl::true_ {};\
template <int brng> struct is_variate_generator_a_mkl_range_generator<boost::random::mkl::engine<brng>&,Distribution> : public boost::mpl::true_ {};\
template <int brng> struct is_variate_generator_a_mkl_range_generator<boost::random::mkl::engine<brng>*,Distribution> : public boost::mpl::true_ {};




/*
#define BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY(mkl_engine_type, Distribution, vsl_function, vsl_method, dist_params, value_params)  \
private:                                                                                                                                            \
                                                                                                                                                    \
typedef boost::random::detail::ptr_helper<mkl_engine_type> helper_type;                                                                             \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
typedef typename helper_type::value_type engine_value_type;                                                                                         \
typedef mkl_engine_type engine_type;                                                                                                                \
typedef Distribution distribution_type;                                                                                                             \
typedef typename Distribution::result_type result_type;                                                                                             \
typedef boost::range_generate::unit_stride_range_generator_type_checked<result_type> is_range_generator;                                            \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
variate_generator(mkl_engine_type e, Distribution d)                                                                                                \
  : _eng(e), _dist(d) { }                                                                                                                           \
                                                                                                                                                    \
result_type operator()()                                                                                                                            \
{                                                                                                                                                   \
	result_type result;                                                                                                                             \
    boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), 1, &result, dist_params) );                   \
    return result;                                                                                                                                  \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class T>                                                                                                                                   \
result_type operator()(const T& value)                                                                                                              \
{                                                                                                                                                   \
	result_type result;                                                                                                                             \
    boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), 1, &result, value_params) );                  \
    return result;                                                                                                                                  \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class UnitStrideIterator>                                                                                                                  \
void operator()(UnitStrideIterator begin, UnitStrideIterator end)                                                                                   \
{                                                                                                                                                   \
    boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), end-begin, &(*begin), dist_params ) );        \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class UnitStrideIterator, class T>                                                                                                         \
void operator()(UnitStrideIterator begin, UnitStrideIterator end, const T& value)                                                                   \
{                                                                                                                                                   \
    boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), end-begin, &(*begin), value_params ) );       \
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
mkl_engine_type _eng;                                                                                                                               \
distribution_type _dist;


#define BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_MIN_MAX(Distribution,  vsl_function, vsl_method, dist_params, value_params, minimum, maximum)\
template<int brng>                                                                                                                                  \
class variate_generator<boost::random::mkl::engine<brng>,Distribution>                                                                              \
{                                                                                                                                                   \
    BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_MIN_MAX(                                                                                 \
		boost::random::mkl::engine<brng>,                                                                                                           \
		BOOST_RANDOM_MKL_CONCAT(Distribution),                                                                                                      \
		vsl_function,                                                                                                                               \
		vsl_method,                                                                                                                                 \
		BOOST_RANDOM_MKL_CONCAT(dist_params),                                                                                                       \
		BOOST_RANDOM_MKL_CONCAT(value_params),                                                                                                      \
		minimum,                                                                                                                                    \
		maximum                                                                                                                                     \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<int brng>                                                                                                                                  \
class variate_generator<boost::random::mkl::engine<brng>&,Distribution>                                                                             \
{                                                                                                                                                   \
    BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_MIN_MAX(                                                                                 \
		boost::random::mkl::engine<brng>&,                                                                                                          \
		BOOST_RANDOM_MKL_CONCAT(Distribution),                                                                                                      \
		vsl_function,                                                                                                                               \
		vsl_method,                                                                                                                                 \
		BOOST_RANDOM_MKL_CONCAT(dist_params),                                                                                                       \
		BOOST_RANDOM_MKL_CONCAT(value_params)                                                                                                       \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<int brng>                                                                                                                                  \
class variate_generator<boost::random::mkl::engine<brng>*,Distribution>                                                                             \
{                                                                                                                                                   \
    BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_MIN_MAX(                                                                                 \
		boost::random::mkl::engine<brng>*,                                                                                                          \
		BOOST_RANDOM_MKL_CONCAT(Distribution),                                                                                                      \
		vsl_function,                                                                                                                               \
		vsl_method,                                                                                                                                 \
		BOOST_RANDOM_MKL_CONCAT(dist_params),                                                                                                       \
		BOOST_RANDOM_MKL_CONCAT(value_params)                                                                                                       \
	)                                                                                                                                               \
};                                                                                                                                                  \
template <int brng> struct is_variate_generator_a_mkl_range_generator<boost::random::mkl::engine<brng>, Distribution> : public boost::mpl::true_ {};\
template <int brng> struct is_variate_generator_a_mkl_range_generator<boost::random::mkl::engine<brng>&,Distribution> : public boost::mpl::true_ {};\
template <int brng> struct is_variate_generator_a_mkl_range_generator<boost::random::mkl::engine<brng>*,Distribution> : public boost::mpl::true_ {};
*/


#define BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_2(mkl_engine_type, Distribution, vsl_function, vsl_method, dist_params, value_params, ResultType) \
private:                                                                                                                                            \
                                                                                                                                                    \
typedef boost::random::detail::ptr_helper<mkl_engine_type> helper_type;                                                                             \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
typedef typename helper_type::value_type engine_value_type;                                                                                         \
typedef mkl_engine_type engine_type;                                                                                                                \
typedef Distribution distribution_type;                                                                                                             \
typedef ResultType result_type;                                                                                                                     \
typedef boost::range_generate::unit_stride_range_generator_type_checked<result_type> is_range_generator;                                            \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
variate_generator(mkl_engine_type e, Distribution d)                                                                                                \
  : _eng(e), _dist(d) { }                                                                                                                           \
                                                                                                                                                    \
result_type operator()()                                                                                                                            \
{                                                                                                                                                   \
	result_type result;                                                                                                                             \
    boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), 1, &result, dist_params) );                   \
    return result;                                                                                                                                  \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class T>                                                                                                                                   \
result_type operator()(const T& value)                                                                                                              \
{                                                                                                                                                   \
	result_type result;                                                                                                                             \
    boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), 1, &result, value_params) );                  \
    return result;                                                                                                                                  \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class UnitStrideIterator>                                                                                                                  \
void operator()(UnitStrideIterator begin, UnitStrideIterator end)                                                                                   \
{                                                                                                                                                   \
    boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), end-begin, &(*begin), dist_params ) );        \
}                                                                                                                                                   \
                                                                                                                                                    \
template<class UnitStrideIterator, class T>                                                                                                         \
void operator()(UnitStrideIterator begin, UnitStrideIterator end, const T& value)                                                                   \
{                                                                                                                                                   \
    boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), end-begin, &(*begin), value_params ) );       \
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
mkl_engine_type _eng;                                                                                                                               \
distribution_type _dist;


#define BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_2(Distribution,  vsl_function, vsl_method, dist_params, value_params, ResultType)         \
template<int brng>                                                                                                                                  \
class variate_generator<boost::random::mkl::engine<brng>,Distribution>                                                                              \
{                                                                                                                                                   \
    BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_2(                                                                                       \
		boost::random::mkl::engine<brng>,                                                                                                           \
		BOOST_RANDOM_MKL_CONCAT(Distribution),                                                                                                      \
		vsl_function,                                                                                                                               \
		vsl_method,                                                                                                                                 \
		BOOST_RANDOM_MKL_CONCAT(dist_params),                                                                                                       \
		BOOST_RANDOM_MKL_CONCAT(value_params),                                                                                                      \
		ResultType                                                                                                                                  \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<int brng>                                                                                                                                  \
class variate_generator<boost::random::mkl::engine<brng>&,Distribution>                                                                             \
{                                                                                                                                                   \
    BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_2(                                                                                       \
		boost::random::mkl::engine<brng>&,                                                                                                          \
		BOOST_RANDOM_MKL_CONCAT(Distribution),                                                                                                      \
		vsl_function,                                                                                                                               \
		vsl_method,                                                                                                                                 \
		BOOST_RANDOM_MKL_CONCAT(dist_params),                                                                                                       \
		BOOST_RANDOM_MKL_CONCAT(value_params),                                                                                                      \
		ResultType                                                                                                                                  \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<int brng>                                                                                                                                  \
class variate_generator<boost::random::mkl::engine<brng>*,Distribution>                                                                             \
{                                                                                                                                                   \
    BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_2(                                                                                       \
		boost::random::mkl::engine<brng>*,                                                                                                          \
		BOOST_RANDOM_MKL_CONCAT(Distribution),                                                                                                      \
		vsl_function,                                                                                                                               \
		vsl_method,                                                                                                                                 \
		BOOST_RANDOM_MKL_CONCAT(dist_params),                                                                                                       \
		BOOST_RANDOM_MKL_CONCAT(value_params),                                                                                                      \
		ResultType                                                                                                                                  \
	)                                                                                                                                               \
};                                                                                                                                                  \
template <int brng> struct is_variate_generator_a_mkl_range_generator<boost::random::mkl::engine<brng>, Distribution> : public boost::mpl::true_ {};\
template <int brng> struct is_variate_generator_a_mkl_range_generator<boost::random::mkl::engine<brng>&,Distribution> : public boost::mpl::true_ {};\
template <int brng> struct is_variate_generator_a_mkl_range_generator<boost::random::mkl::engine<brng>*,Distribution> : public boost::mpl::true_ {};


#define BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_TR1_2(mkl_engine_type, Distribution, vsl_function, vsl_method, dist_params, ResultType) \
private:                                                                                                                                            \
                                                                                                                                                    \
typedef boost::random::detail::ptr_helper<mkl_engine_type> helper_type;                                                                             \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
typedef typename helper_type::value_type engine_value_type;                                                                                         \
typedef mkl_engine_type engine_type;                                                                                                                \
typedef Distribution distribution_type;                                                                                                             \
typedef ResultType result_type;                                                                                                                     \
typedef boost::range_generate::unit_stride_range_generator_type_checked<result_type> is_range_generator;                                            \
                                                                                                                                                    \
public:                                                                                                                                             \
                                                                                                                                                    \
variate_generator(mkl_engine_type e, Distribution d)                                                                                                \
  : _eng(e), _dist(d) { }                                                                                                                           \
                                                                                                                                                    \
result_type operator()()                                                                                                                            \
{                                                                                                                                                   \
	result_type result;                                                                                                                             \
    boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), 1, &result, dist_params) );                   \
    return result;                                                                                                                                  \
}                                                                                                                                                   \
                                                                                                                                                    \                                                                                                                                                    \
template<class UnitStrideIterator>                                                                                                                  \
void operator()(UnitStrideIterator begin, UnitStrideIterator end)                                                                                   \
{                                                                                                                                                   \
    boost::random::mkl::check_errcode ( vsl_function(vsl_method, helper_type::ref(_eng).get_stream(), end-begin, &(*begin), dist_params ) );        \
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
mkl_engine_type _eng;                                                                                                                               \
distribution_type _dist;


#define BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_TR1_2(Distribution,  vsl_function, vsl_method, dist_params, ResultType)                   \
template<int brng>                                                                                                                                  \
class variate_generator<boost::random::mkl::engine<brng>,Distribution>                                                                              \
{                                                                                                                                                   \
    BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_TR1_2(                                                                                   \
		boost::random::mkl::engine<brng>,                                                                                                           \
		BOOST_RANDOM_MKL_CONCAT(Distribution),                                                                                                      \
		vsl_function,                                                                                                                               \
		vsl_method,                                                                                                                                 \
		BOOST_RANDOM_MKL_CONCAT(dist_params),                                                                                                       \
		ResultType                                                                                                                                  \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<int brng>                                                                                                                                  \
class variate_generator<boost::random::mkl::engine<brng>&,Distribution>                                                                             \
{                                                                                                                                                   \
    BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_TR1_2(                                                                                   \
		boost::random::mkl::engine<brng>&,                                                                                                          \
		BOOST_RANDOM_MKL_CONCAT(Distribution),                                                                                                      \
		vsl_function,                                                                                                                               \
		vsl_method,                                                                                                                                 \
		BOOST_RANDOM_MKL_CONCAT(dist_params),                                                                                                       \
		ResultType                                                                                                                                  \
	)                                                                                                                                               \
};                                                                                                                                                  \
template<int brng>                                                                                                                                  \
class variate_generator<boost::random::mkl::engine<brng>*,Distribution>                                                                             \
{                                                                                                                                                   \
    BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPEZIALIZATION_BODY_TR1_2(                                                                                   \
		boost::random::mkl::engine<brng>*,                                                                                                          \
		BOOST_RANDOM_MKL_CONCAT(Distribution),                                                                                                      \
		vsl_function,                                                                                                                               \
		vsl_method,                                                                                                                                 \
		BOOST_RANDOM_MKL_CONCAT(dist_params),                                                                                                       \
		ResultType                                                                                                                                  \
	)                                                                                                                                               \
};                                                                                                                                                  \
template <int brng> struct is_variate_generator_a_mkl_range_generator<boost::random::mkl::engine<brng>, Distribution> : public boost::mpl::true_ {};\
template <int brng> struct is_variate_generator_a_mkl_range_generator<boost::random::mkl::engine<brng>&,Distribution> : public boost::mpl::true_ {};\
template <int brng> struct is_variate_generator_a_mkl_range_generator<boost::random::mkl::engine<brng>*,Distribution> : public boost::mpl::true_ {};


#endif // DOXYGEN_SHOULD_SKIP_THIS

namespace boost {
namespace random {

template <class Engine, class Distribution>
struct is_variate_generator_a_mkl_range_generator : public boost::mpl::false_ {};

} // random
} // boost

#endif // BOOST_RANDOM_MKL_VARIATE_GENERATOR_SPECIALIZATION_HPP

