// Copyright Fabian Bösch 2012
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 *  @file 
 *  @brief This file contains a random number engine which wraps functions from the AMD ACML library.
 */

#ifndef BOOST_RANDOM_ACML_ENGINE_HPP
#define BOOST_RANDOM_ACML_ENGINE_HPP

#include <istream>
#include <ostream>
#include <vector>
#include <limits>
#include <acml.h>
#include "acml_exception.hpp"
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/static_assert.hpp>
#include <boost/generate/generate.hpp>
#include <boost/random/detail/seed.hpp>
#include <boost/random/detail/seed_impl.hpp>
#include <cassert>

namespace boost {
namespace random {
namespace acml {
namespace detail {

inline void randinitalize(long genid, long subid, long* seed, long* lseed, long* state, long* lstate, double*)
{
    long info(0);
    drandinitialize(genid, subid, seed, lseed, state, lstate, &info);
    check_errcode(info);
}

inline void randinitalize(long genid, long subid, long* seed, long* lseed, long* state, long* lstate, float*)
{
    long info(0);
    srandinitialize(genid, subid, seed, lseed, state, lstate, &info);
    check_errcode(info);
}

inline void randdiscreteuniform(long n, long a, long b, long *state, long *x, double*)
{
    long info(0);
    dranddiscreteuniform(n, a, b, state, x, &info);
    check_errcode(info);
}

inline void randdiscreteuniform(long n, long a, long b, long *state, long *x, float*)
{
    long info(0);
    sranddiscreteuniform(n, a, b, state, x, &info);
    check_errcode(info);
}

template<class T>
inline long randdiscreteuniform(long a, long b, long *state, T* ptr)
{
    long x;
    randdiscreteuniform(1, a, b, state, &x, ptr);
    return x;
}

inline void randskipahead(long n, long *state, double*)
{
    long info(0);
    drandskipahead(n, state, &info);
    check_errcode(info);
}

inline void randskipahead(long n, long *state, float*)
{
    long info(0);
    srandskipahead(n, state, &info);
    check_errcode(info);
}

inline void randleapfrog(long n, long k, long *state, double*)
{
    long info(0);
    drandleapfrog(n,k,state,&info);
    check_errcode(info);
}

inline void randleapfrog(long n, long k, long *state, float*)
{
    long info(0);
    srandleapfrog(n,k,state,&info);
    check_errcode(info);
}

template<class T>
inline long state_size(long genid, long subid, T* ptr)
{
    long seed = 0; long lseed = 1; long state = 0; long lstate = -1;
    randinitalize(genid, subid, &seed, &lseed, &state, &lstate, ptr);
    return lstate;
}

template<class T>
inline std::size_t seed_sequence_size(long genid, long subid, T* ptr)
{
    long seed = 0; long lseed = -1; long state = 0; long lstate = -1;
    randinitalize(genid, subid, &seed, &lseed, &state, &lstate, ptr);
    return static_cast<std::size_t>(lseed);
}

template<class T>
inline std::vector<long> randinitalize(long genid, long subid, long seed, T* ptr)
{
    std::vector<long> state(state_size(genid,subid,ptr));
    long d_seed(seed); long dl_seed(1); long ds(state.size());
    randinitalize(genid, subid, &d_seed, &dl_seed, &state[0], &ds, ptr);
    return state;
}

template<class T>
inline std::vector<long> randinitalize(long genid, long subid, std::vector<long>& seeds, T* ptr)
{
    std::vector<long> state(state_size(genid,subid,ptr));
    long dl_seed(seeds.size()); long ds(state.size());
    randinitalize(genid, subid, &seeds[0], &dl_seed, &state[0], &ds, ptr);
    return state;
}

template <long genid>
struct has_block_split_impl : public
    boost::mpl::eval_if_c<(genid==1) || (genid==2) || (genid==4),
        boost::mpl::true_,
        boost::mpl::false_
    >::type
{};

template <long genid>
struct has_leap_frog_impl : public
boost::mpl::eval_if_c<(genid==1) || (genid==2) /*|| (genid==4)*/,
        boost::mpl::true_,
        boost::mpl::false_
    >::type
{};

} // detail

/** @brief Class wrapping the AMD ACML base random number generators.
 *
 *  Implements the boost uniform random number generator concept.
 *  @tparam brng Generator ID.
 *  @tparam single Use single precision?
 *  @tparam subid Generator sub ID.
 */
template <long genid_=1, bool single=false, long subid_=1>
class engine
{
    
	BOOST_STATIC_ASSERT( (genid_ > 0) && (genid_ < 5) && ( ((genid_==2) && (subid_ > 0) && (subid_ < 274)) || (genid_!=2) ) );


    public: // typedefs

    /** @typedef internal_type
      * Single or double precision.
      */
    typedef typename boost::mpl::if_c<single,float,double>::type internal_type;

    /** @typedef result_type
      * Type of the resulting random value.
      */
    typedef long result_type;

	/** @typedef seed_type
      * Type of the seed values.
      */
	typedef long seed_type;

	/** @typedef is_range_generator
      * Required for the engine to model a Range Generator.
      */
	typedef boost::range_generate::unit_stride_range_generator_type_checked<result_type> is_range_generator;

    /** @typedef state_type
      * Type of the internal state.
      */
    typedef std::vector<long> state_type;


	public: // static members
	
    /// AMD ACML GENID index.
	static const long genid;

    /// AMD ACML SUBID index
    static const long subid;

	/// Default seed parameter
	static const long default_seed;


    public: // ctors

    /// Construct an instance with default parameters.
    engine() { seed(); }

    /** @brief Construct with user defined seed value.
     *  @param value Seed value.
     */
	BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(engine, long, value) { seed(value); }

	/** @brief Construct with seed sequence.
     *  @param seq Seed sequence.
     */
	BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(engine, SeedSeq, seq) { seed(seq); }

	/** @brief Construct from seed values.
     *  @tparam It Input iterator type.
	 *  @param  first Iterator pointing to the first seed value.
	 *  @param  last  Iterator pointing past-the-end of seed value sequence.
     */
	template<class It> 
	engine(It& first, It& last) { seed(first,last); }

	/** @brief Copy construct
	 *	@param e Other engine
	 */
    engine(const engine& e) : state_(e.state_) {}

	
	public: // seed
	
    /// @brief Set default seed value.
	void seed() { seed(default_seed); }

    /** @brief Set seed value.
     *  @param s Seed value.
     */
	BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(engine, long, s)
    //void seed(const long& s)
    {
        state_type s2(detail::randinitalize(genid_, subid_, s, (internal_type*)0));
        std::swap(state_,s2);
    }

    /** @brief Set state by seed sequence.
     *  @tparam Sseq Seed sequence type.
     *  @param q Seed sequence.
     */
	BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(engine, Sseq, q)
    //template <class Sseq>
    //void seed(Sseq& q)
    {
		// generate as many seeds as needed
		const std::size_t n_seed = detail::seed_sequence_size(genid_, subid_, (internal_type*)0);	
		std::vector<typename Sseq::result_type> seed0(n_seed);
		std::vector<long> seed_(n_seed);
		q.generate(seed0.begin(),seed0.end());
		std::copy(seed0.begin(),seed0.end(),seed_.begin());
		state_type s2(detail::randinitalize(genid_, subid_, seed_, (internal_type*)0));
        std::swap(state_,s2);
    }

	/** @brief Set state by sequence of seed values.
     *  @tparam It Input iterator type.
     *  @param first Iterator pointing to the first seed value.
	 *  @param  last  Iterator pointing past-the-end of seed value sequence.
     */
	template<class It>
    void seed(It first, It last)
	{
		std::vector<long> seed_;
		while(first!=last)
		{
			seed_.push_back(*first++);
		}
		state_type s2(detail::randinitalize(genid_, subid_, seed_, (internal_type*)0));
        std::swap(state_,s2);
	}


    public: // assignment

    /** @brief Assignment operator.
     *  @param rhs Instance to copy from.
     *  @return Reference to this instance.
     */
    engine& operator=(engine rhs)
    {
        std::swap(rhs.state_,state_);
        return *this;
    }


	public: // Advance state

	/** @brief Discard values.
	 *  @param z Number of values to be discarded.
	 */
	void discard(std::size_t z)
    {
        for(std::size_t j = 0; j < z; ++j) (*this)();
    }


    public: // main methods

    /** @brief Range function call.
     *
     *  Assign random values to a range.
     *  @pre    @c UnitStrideIterator must meet the requirements of a Unit Stride Iterator and it's value_type must be equal to the engine's result type.
     *  @tparam UnitStrideIterator Iterator type which implements the Unit Stride Iterator concept.
     *  @param  first Start iterator.
     *  @param  last  Past-the-end iterator.
     */
    template <class UnitStrideIterator>
    inline void operator()(UnitStrideIterator first, UnitStrideIterator last)
    {
		assert((boost::is_unit_stride_iterator<UnitStrideIterator>::type::value && boost::is_same<typename std::iterator_traits<UnitStrideIterator>::value_type, result_type>::type::value));
        const unsigned int n(last - first);
        detail::randdiscreteuniform(n, min(), max(), &state_[0], &(*first), (internal_type*)0);
    }

    /** @brief Element function call.
     *  @return  A single random value.
     */
    inline result_type operator()()
    { 
        return detail::randdiscreteuniform(min(), max(), &state_[0], (internal_type*)0);
    }


    public: // info

	/** @brief Minimum value that the engine can return.
	 *  @return Minimum value
	 */
	inline result_type min() const { return (std::numeric_limits<result_type>::min)() / 2 + 1; }
	
	/** @brief Maximum value that the engine can return.
	 *  @return Maximum value
	 */
	inline result_type max() const { return (std::numeric_limits<result_type>::max)() / 2; }


    public: // equality check

    /** @brief Equality operator.
     *  @param a Left hand side instance.
     *  @param b Right hand side instance.
     *  @return Returns true if a and b are in the same state.
     */
    friend bool operator==(const engine& a, const engine& b) { return a.state_ == b.state_; }

	/** @brief Inequality operator.
     *  @param a Left hand side instance.
     *  @param b Right hand side instance.
     *  @return Returns true if a and b are not in the same state.
     */
	friend bool operator!=(const engine& a, const engine& b) { return a.state_ != b.state_; }

    public: // io

    /** @brief Writes state to output stream.
     *  @param os Output stream instance.
     *  @param e Instance of engine.
     *  @return Reference to output stream.
     */
    /*friend std::ostream& operator<<(std::ostream& os, const engine& e)
    {
        const std::size_t n(e.state_.size()*sizeof(long) / sizeof(const char));
        const std::size_t nl(sizeof(std::size_t)/sizeof(const char));
        const char* l(reinterpret_cast<const char*>(&n));
        for (std::size_t i=0; i<nl; ++i) os << l[i];
        const char* data(reinterpret_cast<const char*>(&e.state_[0]));
        for (std::size_t i=0; i<n; ++i) os << data[i];
        return os;
    }*/
	template<class CharT, class Traits>
    friend std::basic_ostream<CharT,Traits>& operator<<(std::basic_ostream<CharT,Traits>& os, const engine& e)
    {
		const std::size_t n(e.state_.size());
		os.write(reinterpret_cast<const CharT*>(&n), sizeof(std::size_t)/sizeof(CharT));
		os.write(reinterpret_cast<const CharT*>(&e.state_[0]), sizeof(long)/sizeof(CharT)*n);
		return os;
	}

    /** @brief Reads state from input stream.
     *  @param is Input stream instance.
     *  @param e Instance of engine.
     *  @return Reference to input stream.
     */
	template<class CharT, class Traits>
    friend std::basic_istream<CharT,Traits>& operator>>(std::basic_istream<CharT,Traits>& is, engine& e)
    {
		std::size_t n(0);
		is.read(reinterpret_cast<CharT*>(&n), sizeof(std::size_t)/sizeof(CharT));
		state_type s2(n);
		is.read(reinterpret_cast<CharT*>(&s2[0]), sizeof(long)/sizeof(CharT)*n);
		std::swap(s2,e.state_);
        return is;
	}


    public: // access

    /** @brief Get access to internal state object.
     *  @return State.
     */
    inline state_type& state()
    {
        return state_;
    }

    /** @brief Get read access to internal state object.
     *  @return State.
     */
    inline const state_type& state() const
    {
        return state_;
    }


    private: // members

    /// Internal state.
    state_type state_;

};


//  A definition is required even for integral static constants
template <long genid_, bool single, long subid_>
const long engine<genid_, single, subid_>::genid = genid_;
template <long genid_, bool single, long subid_>
const long engine<genid_, single, subid_>::subid = subid_;
template <long genid_, bool single, long subid_>
const long engine<genid_, single, subid_>::default_seed = 42;



// TODO?
/*
template <bool single, long subid_>
class engine<5l,single, subid_>
{

};*/



/** @brief Traits class to inquire whether engine can be used with block-splitting.
 *  @tparam Engine ACML engine.
 */
template <class Engine>
struct has_block_split : public detail::has_block_split_impl<Engine::genid>::type {};


/** @brief Makes engines independent by block-splitting.
 *  @tparam Engine   ACML engine.
 *  @tparam Iterator Iterator class. 
 *  @param begin     Points to the first engine.
 *  @param end       Points past-the-end of the last engine.
 *  @param size      Maximum number of variates needed from a single engine.
 *  @return          Independent engines (by block-splitting).
 */
template <class Engine, class Iterator>
void make_independent_engines_by_block_split(Iterator begin, Iterator end, const std::size_t& size)
{
    BOOST_STATIC_ASSERT_MSG(has_block_split<Engine>::value, "This engine does not provide block splitting");
    if (end - begin <= 0) return;
    typename Engine::state_type s(begin->state());
    ++begin;
    for (Iterator it=begin; it!=end; ++it)
    {
        detail::randskipahead(size, &s[0], (typename Engine::internal_type*)0);
        it->state() = s;
    }
}

/** @brief Traits class to inquire whether engine can be used with leap-frogging.
 *  @tparam Engine ACML engine.
 */
template <class Engine>
struct has_leap_frog : public detail::has_leap_frog_impl<Engine::genid>::type {};

/** @brief Makes engines independent by leap-frogging.
 *  @tparam Engine   ACML engine.
 *  @tparam Iterator Iterator class. 
 *  @param begin     Points to the first engine.
 *  @param end       Points past-the-end of the last engine.
 *  @return          Independent engines (by leap-frogging).
 */
template <class Engine, class Iterator>
void make_independent_engines_by_leap_frog(Iterator begin, Iterator end)
{
    BOOST_STATIC_ASSERT_MSG(has_leap_frog<Engine>::value, "This engine does not provide leap-frogging");
    long n(end - begin);
    if (n <= 0) return;
    typename Engine::state_type s(begin->state());
    typename Engine::state_type s2;
    long k(1);
    for (Iterator it=begin; it!=end; ++it, ++k)
    {
        s2 = s;
        detail::randleapfrog(n, k, &s2[0], (typename Engine::internal_type*)0);
        it->state() = s2;
    }
}

/** @typedef nag
 *  NAG basic generator: linear congruential generator, period is approx. 2^57
 */
typedef engine<1,false,1> nag;

/** @typedef wh
 *  A set of 273 Wichmann-Hill combined multiplicative congruential generators.
 */
typedef engine<2,false,1> wh;

/** @typedef mt19937
  * A Mersenne Twister pseudorandom number generator.
  */
typedef engine<3,false,1> mt19937;

/** @typedef mrg32k3a
  * A combined multiple recursive generator with two components of order 3.
  */
typedef engine<4,false,1> mrg32k3a;

// * @typedef bbs
//  * Blum-Blum-Shub pseudo random number generator is cryptologically secure under the
//  * assumption that the quadratic residuosity problem is intractable
//  *
//typedef engine<5,false,1> bbs;


} // acml
} // random
} // boost

#endif // BOOST_RANDOM_ACML_ENGINE_HPP

