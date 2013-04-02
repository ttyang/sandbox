// Copyright Fabian Bösch 2012
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 *  @file 
 *  @brief This file contains a random number engine which wraps functions from the Intel MKL library.
 */

#ifndef BOOST_RANDOM_MKL_ENGINE_HPP
#define BOOST_RANDOM_MKL_ENGINE_HPP

#include <istream>
#include <ostream>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>
#include <boost/cstdint.hpp>
#include <limits>
#include <mkl_vsl.h>
#include "vsl_exception.hpp"
#include <boost/mpl/int.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/static_assert.hpp>
#include <boost/generate/generate.hpp>
#include <boost/random/detail/seed.hpp>
#include <cassert>

namespace boost {
namespace random {
namespace mkl {
namespace detail {

/** @brief Traits class for engine's @c result_type.
 *  @tparam BRNG index
 */
template<int brng> struct result_type_trait { typedef boost::uint32_t type;};

template<> struct result_type_trait<VSL_BRNG_MCG59>
{
    #ifndef BOOST_NO_INT64_T
    typedef boost::uint64_t type;
    #else
    typedef boost::uint32_t type;
    #endif
};

template<> struct result_type_trait<VSL_BRNG_SFMT19937>
{
    #ifndef BOOST_NO_INT64_T
    typedef boost::uint64_t type;
    #else
    typedef boost::uint32_t type;
    #endif
};

/// Maps BRNG index to property data structure.
std::map<int,VSLBRngProperties> property_map;

/** @brief Get BRNG property by index.
 *
 *  Stores property data structures in a map (@c property_map).
 *  @param brng BRNG index.
 *  @return property data structure.
 */
const VSLBRngProperties& get_properties(int brng)
{
    typename std::map<int,VSLBRngProperties>::iterator it = property_map.find(brng);
    if (it == property_map.end())
    {
        VSLBRngProperties properties;
        boost::random::mkl::check_errcode( vslGetBrngProperties(brng, &properties) );
        return (property_map[brng] = properties);
    } else return it->second;
}

/** @brief Get the number of words occupied by a single random value.
 *  @param brng BRNG index.
 *  @return Number of words.
 */
unsigned int word_size(int brng) {return get_properties(brng).WordSize;};

/** @brief Get the number of bits occupied by a single random value.
 *  @param brng BRNG index.
 *  @return Number of bits.
 */
unsigned int n_bits(int brng){return get_properties(brng).NBits;};

/** @brief Does the BRNG includes zero as output?
 *  @param brng BRNG index.
 *  @return Boolean value.
 */
unsigned int includes_zero(int brng){return get_properties(brng).IncludesZero;};

/** @brief Get the number of @c internal_type instances occupied by a single random value.
 *  @param brng BRNG index.
 *  @return Number of instances of type @c internal_type.
 */
unsigned int n_internal(int brng)
{
    const unsigned int ws(word_size(brng));
    const unsigned int s(sizeof(unsigned int));
    return ( ((ws - (ws/s)*s) == 0) ? (ws/s) : (ws/s+1) );
}

template <int brng>
struct has_block_split_impl : public
    boost::mpl::eval_if_c<
        brng == VSL_BRNG_MCG31 || brng == VSL_BRNG_MRG32K3A ||
        brng == VSL_BRNG_MCG59 || (brng >= VSL_BRNG_WH && brng < VSL_BRNG_WH+273) ||
        brng == VSL_BRNG_SOBOL || brng == VSL_BRNG_NIEDERR,
        boost::mpl::true_,
        boost::mpl::false_
    >::type
{};

template <int brng>
struct has_leap_frog_impl : public
boost::mpl::eval_if_c<
        brng == VSL_BRNG_MCG31 || brng == VSL_BRNG_MCG59 ||
        (brng >= VSL_BRNG_WH && brng < VSL_BRNG_WH+273) /*||
        brng == VSL_BRNG_SOBOL || brng == VSL_BRNG_NIEDERR*/,
        boost::mpl::true_,
        boost::mpl::false_
    >::type
{};

template <int brng>
struct n_seed_values : public
	boost::mpl::if_c<
		brng == VSL_BRNG_MCG31 || brng == VSL_BRNG_MT19937 || (brng >= VSL_BRNG_MT2203 && brng < VSL_BRNG_MT2203 + 6024) || brng == VSL_BRNG_SOBOL || brng == VSL_BRNG_NIEDERR || VSL_BRNG_SFMT19937,
		boost::mpl::int_<1>,
		typename boost::mpl::if_c<
			brng == VSL_BRNG_MCG59,
			boost::mpl::int_<2>,
			typename boost::mpl::if_c<
				(brng >= VSL_BRNG_WH && brng < VSL_BRNG_WH+273),
				boost::mpl::int_<4>,
				typename boost::mpl::if_c<
					brng == VSL_BRNG_MRG32K3A,
					boost::mpl::int_<6>,
					typename boost::mpl::if_c<
						brng == VSL_BRNG_R250,
						boost::mpl::int_<250>,
						boost::mpl::int_<1>
					>::type
				>::type
			>::type
		>::type	
	>::type
{};

}

/** @brief Class wrapping the intel MKL basic uniform random number generators (BRNG).
 *
 *  Implements the boost uniform random number generator concept.
 *  @tparam brng BRNG index.
 */
template <int brng = VSL_BRNG_MT19937>
class engine
{

    public: // typedefs

    /** @typedef result_type
      * Type of the resulting random value.
      */
    //typedef typename detail::result_type_trait<brng>::type result_type;
	typedef int result_type;

	/** @typedef seed_type
      * Type of the seed values.
      */
	typedef unsigned int seed_type;

    /** @typedef internal_type
      * Internal type used for storing random values.
      * Usually sizeof(internal_type) < sizeof(result_type). In order to
      * find out, how many internal_type values are required for representing
      * one random value, use @c n_internal() function.
      */
    typedef unsigned int internal_type;

	/** @typedef is_range_generator
      * Required for the engine to model a Range Generator.
      */
	typedef boost::range_generate::unit_stride_range_generator_type_checked<result_type> is_range_generator;


	public: // static members

	/// Intel MKL BRNG index.
    static const int id;

	static const unsigned int default_seed;


    public: // ctors

    /// Construct an instance with default parameters.
    engine()
    {
        check_errcode(vslNewStream(&stream, brng, default_seed));
    }

	/** @brief Construct with user defined seed value.
     *  @param value Seed value.
     */
	BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(engine, seed_type, value)
	//explicit engine(const seed_type& value) 
	{ 
		check_errcode(vslNewStream(&stream, brng, value)); 
		//check_errcode(vslNewStream(&stream, brng, value)); 
	}
    
	/** @brief Construct with seed sequence.
	 *  @tparam SeedSeq SeedSequence type.
     *  @param seq Seed sequence.
     */
	BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(engine, SeedSeq, seq)  
	//template<class SeedSeq>
    //explicit engine(SeedSeq& seq) 
	{
		check_errcode(vslNewStream(&stream, brng, default_seed));
		seed(seq);
	}                   

	/** @brief Construct from seed values.
     *  @tparam It Input iterator type.
	 *  @param  first Iterator pointing to the first seed value.
	 *  @param  last  Iterator pointing past-the-end of seed value sequence.
     */
	template<class It> 
	engine(It first, It last) 
	{ 
		check_errcode(vslNewStream(&stream, brng, default_seed));		
		seed(first,last); 
	}

    /** @brief Copy construct.
     *
     *  Internally copies random stream.
     *  @param e Instance to copy from.
     */
    engine(const engine& e)
    {
        check_errcode(vslCopyStream(&stream, e.stream));
    }

    /// Destruct
    ~engine()
    {
        vslDeleteStream(&stream);
    }


    public: // seed

	/// @brief Set default seed value.
	void seed() { seed(default_seed); }

    /** @brief Set seed value.
     *  @param s Seed value.
     */
	BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(engine, seed_type, s)
	//void seed(const seed_type& s) 
	{ 
		VSLStreamStatePtr new_stream;
		check_errcode(vslNewStream(&new_stream, brng, s));
        std::swap(stream,new_stream);
        check_errcode(vslDeleteStream(&new_stream));
    }

    /** @brief Set state by seed sequence.
     *  @tparam Sseq Seed sequence type.
     *  @param seq Seed seequence.
     */
	BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(engine, SeedSeq, seq)
    //template<class SeedSeq> 
    //void seed(SeedSeq& seq)
	{
		// generate as many seeds as needed
		const std::size_t n_seed = detail::n_seed_values<brng>::value;
		std::vector<typename SeedSeq::result_type> seed0(n_seed);
		std::vector<seed_type> seed_(n_seed);
		seq.generate(seed0.begin(), seed0.end());
		std::copy(seed0.begin(),seed0.end(),seed_.begin());
		VSLStreamStatePtr new_stream;
		check_errcode(vslNewStreamEx(&new_stream, brng, seed_.size(), &seed_[0]));
		std::swap(stream,new_stream);
        check_errcode(vslDeleteStream(&new_stream));
    }

	/** @brief Set state by sequence of seed values.
     *  @tparam It Input iterator type.
     *  @param first Iterator pointing to the first seed value.
	 *  @param  last  Iterator pointing past-the-end of seed value sequence.
     */
	template<class It>
    void seed(It first, It last)
	{
		std::vector<seed_type> seed_;
		while (first != last)
		{
			seed_.push_back(*first++);
		}
		VSLStreamStatePtr new_stream;
		check_errcode(vslNewStreamEx(&new_stream, brng, seed_.size(), &seed_[0]));
		std::swap(stream,new_stream);
        check_errcode(vslDeleteStream(&new_stream));
	}


    public: // assignment

    /** @brief Assignment operator.
     *
     *  Internally copies random stream.
     *  @param rhs Instance to copy from.
     *  @return Reference to this instance.
     */
    engine& operator=(engine rhs)
    {
        std::swap(rhs.stream,stream);
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
     *  @param  begin Start iterator.
     *  @param  end   Past-the-end iterator.
     */
    template <class UnitStrideIterator>
    inline void operator()(UnitStrideIterator begin, UnitStrideIterator end)
    {
		assert((boost::is_unit_stride_iterator<UnitStrideIterator>::type::value && boost::is_same<typename std::iterator_traits<UnitStrideIterator>::value_type, result_type>::type::value));
		const unsigned int n(end - begin);
		check_errcode(viRngUniform(VSL_RNG_METHOD_UNIFORM_STD, stream, n, &(*begin), min(), max()+1));
    }

    /** @brief Element function call.
     *  @return  A single random value.
     */
    inline result_type operator()()
    {
		result_type r;
		check_errcode(viRngUniform(VSL_RNG_METHOD_UNIFORM_STD, stream, 1u, &r, min(), max()+1));
		return r;
    }


    public: // info

    /** @brief Minimum random value.
     *  @return Minimum random value.
     */
    inline result_type min() const
    {
		return std::numeric_limits<result_type>::min();
    }

    /** @brief Maximum random value.
     *  @return Maximum random value.
     */
    inline result_type max() const
    {
		return std::numeric_limits<result_type>::max()-1;
    }


    public: // equality check

    /** @brief Equality operator.
     *
     *  Checks whether internal streams are in the same state.
	 *  @note Due to unitialized memory in the MKL this method will not rely on comparing 
	 *  MKL stream memory but rather compares the output of both engines for a fixed number of variates 
	 *  and thus is relatively slow. 
     *  @param a Left hand side instance.
     *  @param b Right hand side instance.
     *  @return Returns true if a and b are in the same state.
     */
    friend bool operator==(engine a, engine b)
    {
		const unsigned int n_checks = 50;
		std::vector<result_type> r1(n_checks), r2(n_checks);
		a(r1.begin(), r1.end());
		b(r2.begin(), r2.end()); 
		return std::equal(r1.begin(), r1.end(), r2.begin());
    }

	/** @brief Inequality operator.
     *
     *  Checks whether internal streams are not in the same state.
	 *  @note Due to unitialized memory in the MKL this method will not rely on comparing 
	 *  MKL stream memory but rather compares the output of both engines for a fixed number of variates 
	 *  and thus is relatively slow. 
     *  @param a Left hand side instance.
     *  @param b Right hand side instance.
     *  @return Returns true if a and b are not in the same state.
     */
    friend bool operator!=(const engine& a, const engine& b)
    {
		return !(a == b);
	}


    public: // io

    /** @brief Writes state to output stream.
     *  @param os Output stream instance.
     *  @param e Instance of engine.
     *  @return Reference to output stream.
     */
	template<class CharT, class Traits>
    friend std::basic_ostream<CharT,Traits>& operator<<(std::basic_ostream<CharT,Traits>& os, const engine& e)
    {
        const std::size_t memsize(vslGetStreamSize(e.stream));
		const std::size_t l_memsize( memsize/sizeof(CharT) );
		const std::size_t c_memsize( memsize - l_memsize*sizeof(CharT) > 0 ? l_memsize+1 : l_memsize );
        std::vector<char> data(memsize);
        check_errcode(vslSaveStreamM(e.stream, &data[0]));
        os.write(reinterpret_cast<const CharT*>(&data[0]), c_memsize);
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
        const std::size_t memsize(vslGetStreamSize(e.stream));
		const std::size_t l_memsize( memsize/sizeof(CharT) );
		const std::size_t c_memsize( memsize - l_memsize*sizeof(CharT) > 0 ? l_memsize+1 : l_memsize );
        std::vector<char> data(c_memsize*sizeof(CharT));
		is.read(reinterpret_cast<CharT*>(&data[0]), c_memsize);
		//data.resize(memsize);        
        VSLStreamStatePtr new_stream;
        check_errcode(vslLoadStreamM(&new_stream, &data[0]));
        std::swap(e.stream, new_stream);
        check_errcode(vslDeleteStream(&new_stream));
        return is;
    }

    public: // access

    /** @brief Get access to internal random stream object.
     *  @return VSL stream state pointer.
     */
    inline VSLStreamStatePtr& get_stream()
    {
        return stream;
    }

    private: // members

    /// Internal random stream.
    VSLStreamStatePtr stream;

};

//  A definition is required even for integral static constants
template <int brng>
const int engine<brng>::id = brng;
template <int brng>
const unsigned int engine<brng>::default_seed = 42u;

/** @brief Traits class to inquire whether engine can be used with block-splitting.
 *  @tparam Engine MKL engine.
 */
template <class Engine>
struct has_block_split : public detail::has_block_split_impl<Engine::id>::type {};

/** @brief Makes engines independent by block-splitting.
 *  @tparam Engine   MKL engine.
 *  @tparam Iterator Iterator class. 
 *  @param begin     Points to the first engine.
 *  @param end       Points past-the-end of the last engine.
 *  @param size      Maximum number of variates needed from a single engine.
 *  @return          Independent engines (by block-splitting).
 */
template <class Engine, class Iterator>
void make_independent_engines_by_block_split(Iterator begin, Iterator end, std::size_t size)
{
    BOOST_STATIC_ASSERT_MSG(has_block_split<Engine>::value, "This engine does not provide block splitting");
    if (end - begin <= 0) return;
    Engine& first = *begin;
    ++begin;
	long k(1);
    for (Iterator it=begin; it!=end; ++it, ++k)
    {
		*it = first;
		vslSkipAheadStream( it->get_stream(), size*k );
    }
}

/** @brief Traits class to inquire whether engine can be used with leap-frogging.
 *  @tparam Engine MKL engine.
 */
template <class Engine>
struct has_leap_frog : public detail::has_leap_frog_impl<Engine::id>::type {};

/** @brief Makes engines independent by leap-frogging.
 *  @tparam Engine   MKL engine.
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
    Engine first = *begin;
    long k(0);
    for (Iterator it=begin; it!=end; ++it, ++k)
    {
        *it = first;
		vslLeapfrogStream( it->get_stream(), k, n );
    }
}

/** @typedef mcg31
  * A 31-bit multiplicative congruential generator.
  */
typedef engine<VSL_BRNG_MCG31> mcg31;

/** @typedef r250
  * A generalized feedback shift register generator.
  */
typedef engine<VSL_BRNG_R250> r250;

/** @typedef mrg32k3a
  * A combined multiple recursive generator with two components of order 3.
  */
typedef engine<VSL_BRNG_MRG32K3A> mrg32k3a;

/** @typedef mcg59
  * A 59-bit multiplicative congruential generator.
  */
typedef engine<VSL_BRNG_MCG59> mcg59;

/**
  * @typedef wh
  * A set of 273 Wichmann-Hill combined multiplicative congruential generators.
  */
typedef engine<VSL_BRNG_WH> wh;

/** @typedef mt19937
  * A Mersenne Twister pseudorandom number generator.
  */
typedef engine<VSL_BRNG_MT19937> mt19937;

/** @typedef mt2203
  * A set of 6024 Mersenne Twister pseudorandom number generators.
  */
typedef engine<VSL_BRNG_MT2203> mt2203;

/** @typedef sfmt19937
  * A SIMD-oriented Fast Mersenne Twister pseudorandom number generator.
  */
typedef engine<VSL_BRNG_SFMT19937> sfmt19937;

/** @typedef sobol
  * A 32-bit Gray code-based generator producing low-discrepancy sequences for dimensions 1 ≤ s ≤ 40; user-defined dimensions are also available.
  */
typedef engine<VSL_BRNG_SOBOL> sobol;

/** @typedef niederr
  * A 32-bit Gray code-based generator producing low-discrepancy sequences for dimensions 1 ≤ s ≤ 318; user-defined dimensions are also available.
  */
typedef engine<VSL_BRNG_NIEDERR> niederr;

} // mkl
} // random
} // boost

#endif // BOOST_RANDOM_MKL_ENGINE_HPP

