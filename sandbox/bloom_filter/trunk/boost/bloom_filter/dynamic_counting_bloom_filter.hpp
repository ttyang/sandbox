//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Alejandro Cabrera 2011.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/bloom_filter for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_BLOOM_FILTER_DYNAMIC_COUNTING_BLOOM_FILTER_HPP
#define BOOST_BLOOM_FILTER_DYNAMIC_COUNTING_BLOOM_FILTER_HPP 1

#include <cmath>
#include <vector>

#include <boost/config.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/size.hpp>

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_unsigned.hpp>

#include <boost/bloom_filter/detail/counting_apply_hash.hpp>
#include <boost/bloom_filter/hash/default.hpp>

namespace boost {
  namespace bloom_filters {
    template <typename T,
	      size_t BitsPerBin = 4,
	      class HashFunctions = mpl::vector<boost_hash<T, 0> >,
	      typename Block = size_t,
	      typename Allocator = std::allocator<Block> >
    class dynamic_counting_bloom_filter {

      // Block needs to be an integral type
      BOOST_STATIC_ASSERT( boost::is_integral<Block>::value == true);

      // Block needs to be an unsigned type
      BOOST_STATIC_ASSERT( boost::is_unsigned<Block>::value == true);

      // BitsPerBin needs to be greater than 0
      BOOST_STATIC_ASSERT( BitsPerBin > 0);

      // it doesn't make sense to ever support using a BitsPerBin value larger
      // than the number of bits per Block. In that case, the user shouldn't
      // be using a Bloom filter to represent their data.
      BOOST_STATIC_ASSERT( (BitsPerBin < (sizeof(Block) * 8) ) );

      // because of the nature of this implementation, the Bloom filter
      // can have internal fragmentation if the calculation for 
      // bins_per_slot has a remainder. The severity of the  internal
      // fragmentation is equal to the remainder * the number of slots.
      // This check prevents internal fragmentation.
      // This also necessarily limits to bin sizes to one of:
      // [1,2,4,8,16,32(64-bit system only)] bits
      BOOST_STATIC_ASSERT( ((sizeof(Block) * 8) % BitsPerBin) == 0);

    public:
      typedef T value_type;
      typedef T key_type;
      typedef HashFunctions hash_function_type;
      typedef Block block_type;
      typedef Allocator allocator_type;
      typedef dynamic_counting_bloom_filter<T, BitsPerBin, 
					    HashFunctions, 
					    Block, Allocator> this_type;

      typedef std::vector<Block, Allocator> bucket_type;
      typedef typename bucket_type::iterator bucket_iterator;
      typedef typename bucket_type::const_iterator bucket_const_iterator;

      static const slot_bits = sizeof(block_type) * 8;
      static const size_t default_num_bins = 10000;

    private:
      size_t bucket_size(const size_t num_bins) const {
	const size_t bin_bits = num_bins * this->bits_per_bin();
	return bin_bits / slot_bits + 1;
      }

    public:
      //! constructors
      dynamic_counting_bloom_filter() 
	: bits(bucket_size(default_num_bins))
      {
	this->clear();
      }

      explicit dynamic_counting_bloom_filter(const size_t num_bins)
	: bits(bucket_size(num_bins))
      {
	this->clear();
      }

      template <typename InputIterator>
      dynamic_counting_bloom_filter(const InputIterator start, 
				    const InputIterator end) 
	: bits(bucket_size(std::distance(start, end) * 4))
      {
	this->clear();

	for (InputIterator i = start; i != end; ++i)
	  this->insert(*i);
      }

      //! meta functions
      size_t num_bins() const
      {
	return NumBins;
      }

      static BOOST_CONSTEXPR size_t bits_per_bin()
      {
	return BitsPerBin;
      }

      static BOOST_CONSTEXPR size_t bins_per_slot()
      {
	return sizeof(block_type) * 8 / BitsPerBin;
      }

      static BOOST_CONSTEXPR size_t mask()
      {
	return static_cast<Block>(0 - 1) >> (sizeof(Block) * 8 - BitsPerBin);
      }

      size_t bit_capacity() const
      {
        return this->num_bins() * BitsPerBin;
      }

      static BOOST_CONSTEXPR size_t num_hash_functions() 
      {
        return mpl::size<HashFunctions>::value;
      }

      double false_positive_rate() const 
      {
        const double n = static_cast<double>(this->count());
        static const double k = static_cast<double>(num_hash_functions());
        static const double m = static_cast<double>(NumBins);
        static const double e =
	  2.718281828459045235360287471352662497757247093699959574966;
        return std::pow(1 - std::pow(e, -k * n / m), k);
      }

      //? returns the number of bins that have at least 1 bit set
      size_t count() const 
      {
	size_t ret = 0;

	for (bucket_const_iterator i = this->bits.begin(), 
	       end = this->bits.end(); 
	     i != end; ++i) {
	  for (size_t bin = 0; bin < this->bins_per_slot(); ++bin) {
	    const size_t offset_bits = bin * BitsPerBin;
	    const size_t target_bits = (*i >> offset_bits) & this->mask();

	    if (target_bits > 0)
	      ++ret;
	  }
	}

        return ret;
      }

      bool empty() const
      {
	return this->count() == 0;
      }

      //! core ops
      void insert(const T& t)
      {
	static const unsigned N = boost::mpl::size<hash_function_type>::value - 1;
	detail::counting_apply_hash<N, this_type>::insert(t, this->bits);
      }

      template <typename InputIterator>
      void insert(const InputIterator start, const InputIterator end)
      {
	for (InputIterator i = start; i != end; ++i) {
	  this->insert(*i);
	}
      }

      void remove(const T& t)
      {
	static const unsigned N = boost::mpl::size<hash_function_type>::value - 1;
	detail::counting_apply_hash<N, this_type>::remove(t, this->bits);
      }

      template <typename InputIterator>
      void remove(const InputIterator start, const InputIterator end)
      {
	for (InputIterator i = start; i != end; ++i) {
	  this->remove(*i);
	}
      }

      bool probably_contains(const T& t) const
      {
	static const unsigned N = mpl::size<HashFunctions>::value - 1;
	return detail::counting_apply_hash<N, this_type>::contains(t,
								   this->bits);
      }

      //! auxiliary ops
      void clear()
      {
	this->bits.clear();
      }

      void swap(counting_bloom_filter& other)
      {
	counting_bloom_filter tmp = other;
	other = *this;
	*this = tmp;
      }

      //! pairwise ops
      counting_bloom_filter&
      experimental_union_assign(const counting_bloom_filter& rhs)
      {
	if (this->bit_capacity() != rhs.bit_capacity())
	  throw detail::incompatible_size_exception();

	bucket_iterator this_end = this->bits.end();
	bucket_iterator this_start = this->bits.begin();
	bucket_const_iterator rhs_start = rhs.bits.begin();

	for (; this_start != this_end; ++this_start, ++rhs_start) {
	  *this_start |= *rhs_start;
	}

	return *this;
      }

      counting_bloom_filter&
      experimental_intersect_assign(const counting_bloom_filter& rhs)
      {
	if (this->bit_capacity() != rhs.bit_capacity())
	  throw detail::incompatible_size_exception();

	bucket_iterator this_end = this->bits.end();
	bucket_iterator this_start = this->bits.begin();
	bucket_const_iterator rhs_start = rhs.bits.begin();

	for (; this_start != this_end; ++this_start, ++rhs_start) {
	  *this_start &= *rhs_start;
	}

	return *this;
      }

      // equality comparison operators
      template <typename _T, size_t _BitsPerBin,
		typename _HashFns, typename _Block, typename _Allocator>
      friend bool
      operator==(const dynamic_counting_bloom_filter<_T, _BitsPerBin,
						     _HashFns, _Block,
						     _Allocator>& lhs,
		 const dynamic_counting_bloom_filter<_T, _BitsPerBin,
						     _HashFns, _Block,
						     _Allocator>& rhs);

      template <typename _T, size_t _BitsPerBin,
		typename _HashFns, typename _Block, typename _Allocator>
      friend bool
      operator!=(const dynamic_counting_bloom_filter<_T, _BitsPerBin,
						     _HashFns, _Block,
						     _Allocator>& lhs,
		 const dynamic_counting_bloom_filter<_T, _BitsPerBin,
						     _HashFns, _Block,
						     _Allocator>& rhs);


    private:
      bucket_type bits;
    };

    // union
    template<class T, size_t BitsPerBin, class HashFunctions,
	     typename Block, typename Allocator>
    dynamic_counting_bloom_filter<T, BitsPerBin, 
				  HashFunctions, Block, Allocator>
    experimental_union(const dynamic_counting_bloom_filter<T, BitsPerBin, 
							   HashFunctions, 
							   Block,
							   Allocator>& lhs,
		       const dynamic_counting_bloom_filter<T, BitsPerBin,
							   HashFunctions, 
							   Block,
							   Allocator>& rhs)
    {
      dynamic_counting_bloom_filter<T, BitsPerBin, 
				    HashFunctions, Block,
				    Allocator> ret(lhs);
      ret.experimental_union_assign(rhs);
      return ret;
    }

    // intersection
    template<class T, size_t BitsPerBin, class HashFunctions,
	     typename Block, typename Allocator>
    dynamic_counting_bloom_filter<T, BitsPerBin, HashFunctions, 
				  Block, Allocator>
    experimental_intersect(const dynamic_counting_bloom_filter<T, BitsPerBin, 
							       HashFunctions, 
							       Block,
							       Allocator>& lhs,
			   const dynamic_counting_bloom_filter<T, BitsPerBin,
							       HashFunctions, 
							       Block,
							       Allocator>& rhs)
    {
      dynamic_counting_bloom_filter<T, BitsPerBin, 
				    HashFunctions, Block,
				    Allocator> ret(lhs);
      ret.experimental_intersect_assign(rhs);
      return ret;
    }

    template<class T, size_t BitsPerBin, class HashFunctions,
	     typename Block, typename Allocator>
    void
    swap(dynamic_counting_bloom_filter<T, BitsPerBin, 
				       HashFunctions, Block,
				       Allocator>& lhs,
	 dynamic_counting_bloom_filter<T, BitsPerBin,
				       HashFunctions, Block,
				       Allocator>& rhs)

    {
      lhs.swap(rhs);
    }

    template<class T, size_t BitsPerBin, class HashFunctions,
	     typename Block, typename Allocator>
    bool
    operator==(const dynamic_counting_bloom_filter<T, BitsPerBin, 
						   HashFunctions, 
						   Block,
						   Allocator>& lhs,
	       const dynamic_counting_bloom_filter<T, BitsPerBin,
						   HashFunctions, 
						   Block,
						   Allocator>& rhs)
    {
      if (lhs.bit_capacity() != rhs.bit_capacity())
	throw detail::incompatible_size_exception();

      return (lhs.bits == rhs.bits);
    }

    template<class T, size_t BitsPerBin, class HashFunctions,
	     typename Block, typename Allocator>
    bool
    operator!=(const dynamic_counting_bloom_filter<T, BitsPerBin, 
						   HashFunctions, 
						   Block,
						   Allocator>& lhs,
	       const dynamic_counting_bloom_filter<T, BitsPerBin,
						   HashFunctions, 
						   Block,
						   Allocator>& rhs)
    {
      if (lhs.bit_capacity() != rhs.bit_capacity())
	throw detail::incompatible_size_exception();

      return !(lhs == rhs);
    }

  } // namespace bloom_filter
} // namespace boost
#endif
