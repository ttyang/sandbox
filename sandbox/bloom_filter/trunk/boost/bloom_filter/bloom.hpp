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

#ifndef BOOST_BLOOM_FILTER_BLOOM_HPP
#define BOOST_BLOOM_FILTER_BLOOM_HPP 1
/**
 * \author Alejandro Cabrera
 * \brief A generic Bloom filter providing compile-time unrolling
 *        of hash function application.
 */
#include <cmath>
#include <bitset>

#include <boost/config.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/size.hpp>

#include <boost/bloom_filter/detail/apply_hash.hpp>
#include <boost/bloom_filter/hash/default.hpp>

namespace boost {
  namespace bloom_filter {
    template <typename T,
	      size_t Size,
	      class HashFunctions = mpl::vector<boost_hash<T, 3>,
						boost_hash<T, 37> > >
    class bloom_filter {
    public:
      typedef T value_type;
      typedef T key_type;

    public:
      bloom_filter() {}

      static BOOST_CONSTEXPR size_t size() const {
        return Size;
      }

      static BOOST_CONSTEXPR size_t num_hash_functions() const {
        return mpl::size<HashFunctions>::value;
      };

      double false_positive_rate() const {
        const double n = static_cast<double>(this->bits.count());
        static const double k = static_cast<double>(num_hash_functions());
        static const double m = static_cast<double>(Size);
        static const double e =
	  2.718281828459045235360287471352662497757247093699959574966;
        return std::pow(1 - std::pow(e, -k * n / m), k);
      };

      size_t count() const {
        return this->bits.count();
      };

      void insert(const T& t) {
        static const unsigned N = mpl::size<HashFunctions>::value - 1;
        detail::apply_hash<N, T, Size, HashFunctions>::insert(t, bits);
      }

      bool contains(const T& t) const {
        static const unsigned N = mpl::size<HashFunctions>::value - 1;
        return detail::apply_hash<N, T, Size, HashFunctions>::contains(t, bits);
      }

      void clear() {
        this->bits.reset();
      }

      bloom_filter& operator|=(const bloom_filter& rhs) {
        this->bits |= rhs.bits;
        return *this;
      }

      bloom_filter& operator&=(const bloom_filter& rhs) {
        this->bits &= rhs.bits;
        return *this;
      }

    private:
      std::bitset<Size> bits;
    };

    template<class _T, size_t _Size, class _HashFunctions>
    bloom_filter<_T, _Size, _HashFunctions>
    operator|(const bloom_filter<_T, _Size, _HashFunctions>& lhs,
	      const bloom_filter<_T, _Size, _HashFunctions>& rhs)
    {
      bloom_filter<_T, _Size, _HashFunctions> ret(lhs);
      ret |= rhs;
      return ret;
    }

    template<class _T, size_t _Size, class _HashFunctions>
    bloom_filter<_T, _Size, _HashFunctions>
    operator&(const bloom_filter<_T, _Size, _HashFunctions>& lhs,
	      const bloom_filter<_T, _Size, _HashFunctions>& rhs)
    {
      bloom_filter<_T, _Size, _HashFunctions> ret(lhs);
      ret &= rhs;
      return ret;
    }
  } // namespace bloom_filter
} // namespace boost
#endif
