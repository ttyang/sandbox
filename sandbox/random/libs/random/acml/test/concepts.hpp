// Copyright Fabian Bösch 2013
//
// Used this: boost/libs/random/test/concepts.hpp Copyright Steven Watanabe 2011
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_RANDOM_ACML_TEST_CONCEPTS_HPP
#define BOOST_RANDOM_ACML_TEST_CONCEPTS_HPP

#include <boost/config.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4100)
#endif

#include <boost/concept_check.hpp>

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/mpl/bool.hpp>

#include <boost/concept_archetype.hpp>
#include <boost/concept/requires.hpp>
#include <boost/cstdint.hpp>
#include <istream>
#include <ostream>
#include <vector>
#include <boost/generate/generate.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4510)
#pragma warning(disable:4610)
#endif

// check concepts
// copy constructible
// assignable
// equality comparable
// associated types
// streamable
// min/max
// operator()
// range generator
// empty constructor
// all constructors have also seed with same signature

namespace boost {
namespace random {
namespace acml {
namespace test {


template<class T>
struct Streamable
{
public:
    BOOST_CONCEPT_USAGE(Streamable)
    {
        os << x;
        is >> v;
        wos << x;
        wis >> v;
    }
private:
    const T x;
    T v;

    std::istream is;
    std::ostream os;
    std::wistream wis;
    std::wostream wos;
};

template<class Base = null_archetype<> >
struct seed_seq_archetype : Base
{
	typedef boost::uint32_t result_type;
    template<class Iter>
    BOOST_CONCEPT_REQUIRES(
        ((Mutable_RandomAccessIterator<Iter>))
        ((UnsignedInteger<typename Mutable_RandomAccessIterator<Iter>::value_type>)),
    (void))
    generate(Iter, Iter) {}
};

template<class SSeq>
struct SeedSeq
{
public:
	typedef typename SSeq::result_type result_type;
    BOOST_CONCEPT_USAGE(SeedSeq)
    {
        q.generate(rb, re);
    }
private:
    SSeq q;
    mutable_random_access_iterator_archetype<result_type> rb, re;
};


// Type deduction will fail unless the arguments have the same type.
template <typename T>
void same_type(T const&, T const&) {}


template <class G, class Iterator>
struct RangeGenerator
{
	public:
	//typedef typename G::is_vectorizable is_vectorizable;

	//typedef typename std::vector<result_type>::iterator It;

	//typedef typename is_vectorizable::template apply<It>::type R;

	typedef typename boost::is_range_generator<G,Iterator>::type R;

	BOOST_CONCEPT_USAGE(RangeGenerator)
	{
		boost::mpl::bool_<R::value> r;
		same_type(r,boost::mpl::bool_<true>());

		g(a,b);
	}

	private:
	
	G g;
	Iterator a,b;
};

template <class E>
struct PseudoRandomNumberEngine
: Assignable<E>, 
  EqualityComparable<E>,
  CopyConstructible<E>,
  DefaultConstructible<E>,
  Streamable<E>, 
  RangeGenerator<E,typename E::result_type*>
{

	public:

    typedef typename E::result_type result_type;
	typedef typename E::seed_type seed_type;

    BOOST_CONCEPT_ASSERT((Integer<result_type>));
        
    BOOST_CONCEPT_USAGE(PseudoRandomNumberEngine)
    {
        same_type(e(),r); 
        same_type((e.min)(),r);
		same_type((e.max)(),r);

		(void)E();
        (void)E(s);
        (void)E(q);

        e.seed();
        e.seed(s);
        e.seed(q);

        e.discard(z);

        // extension
        (void)E(sb, se);
        e.seed(sb, se);

    }
    
 private:
    E e;
	const E u;
    result_type r;
	seed_type s;
    seed_seq_archetype<> q;
	unsigned long long z;
	input_iterator_archetype<result_type> sb, se;
};

}
}
}
}



#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

// default construct 
// check equality

// construct with seed value
// check equality

// construct with seed sequence
// check equality

// construct with iterators
// check equality

// assign
// check equality

// generate((
// check equality

// range generate
// check equaliy

// advance
// check equality

// default seed
// check equality

// seed value
// check equality

// seed sequence
// check equality

// ostream
// check equality

// istream
// check equality

#endif // BOOST_RANDOM_ACML_TEST_CONCEPTS_HPP

