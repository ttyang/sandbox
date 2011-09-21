
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <algorithm>

#include <boost/multiprecision/mp_float_functions.hpp>
#include "prime_factors.h"

namespace Primes
{
  std::deque<boost::uint32_t>& Data(void);

  static bool IsPrimeFactor(boost::uint32_t& np, const boost::uint32_t p)
  {
    const boost::uint32_t q = static_cast<boost::uint32_t>(np / p);
    const boost::uint32_t r = static_cast<boost::uint32_t>(np - static_cast<boost::uint32_t>(q * p));

    const bool is_prime_factor = (r == static_cast<boost::uint32_t>(0u));

    if(is_prime_factor)
    {
      np = q;
    }
    
    return is_prime_factor;
  }

  static void Factors(const boost::uint32_t n, std::deque<boost::multiprecision::utility::point<boost::uint32_t> >& pf)
  {
    // Compute the prime factors of the unsigned integer n. Use the divide algorithm of
    // "The Art of Computer Programming Volume 2 Semi-numerical Algorithms Third Edition",
    // Donald Knuth (Algorithm A, Chapter 4.5.4, page 380 and pages 378-417).
    static const std::size_t sz = Data().size();

    pf.clear();

    const boost::uint32_t sqrt_n = static_cast<boost::uint32_t>(static_cast<boost::uint64_t>(::sqrt(static_cast<double>(n)) + 0.5));

    boost::uint32_t np = n;

    for(std::size_t i = static_cast<std::size_t>(0u); i < sz; i++)
    {
      const boost::uint32_t p = Data()[i];

      if(IsPrimeFactor(np, p))
      {
        boost::multiprecision::utility::point<boost::uint32_t> ip(p, static_cast<boost::uint32_t>(1u));

        while(IsPrimeFactor(np, p))
        {
          ++ip.y;
        }

        pf.push_back(ip);
      }

      if(static_cast<boost::uint32_t>(np / p) <= p)
      {
        pf.push_back(boost::multiprecision::utility::point<boost::uint32_t>(np, static_cast<boost::uint32_t>(1u)));

        break;
      }

      if((np == static_cast<boost::uint32_t>(1u)) || (p >= sqrt_n))
      {
        break;
      }
    }
  }
}

void boost::multiprecision::prime_factors(const boost::uint32_t n, std::deque<boost::multiprecision::utility::point<boost::uint32_t> >& pf)
{
  // Factor the input integer into a list of primes. For small inputs less than 10,000
  // use the tabulated prime factors list. Calculate the prime factors for larger inputs
  // above 10,000.
  static std::vector<std::deque<boost::multiprecision::utility::point<boost::uint32_t> > > prime_factors_list;

  if(prime_factors_list.empty())
  {
    // Generate a table of the sets of the first 10,000 integer prime factorizations.
    prime_factors_list.resize(static_cast<std::size_t>(10000u));

    prime_factors_list[static_cast<std::size_t>(0u)] = std::deque<boost::multiprecision::utility::point<boost::uint32_t> >(static_cast<std::size_t>(1u), boost::multiprecision::utility::point<boost::uint32_t>(static_cast<boost::uint32_t>(0u), static_cast<boost::uint32_t>(1u)));
    prime_factors_list[static_cast<std::size_t>(1u)] = std::deque<boost::multiprecision::utility::point<boost::uint32_t> >(static_cast<std::size_t>(1u), boost::multiprecision::utility::point<boost::uint32_t>(static_cast<boost::uint32_t>(1u), static_cast<boost::uint32_t>(1u)));
    prime_factors_list[static_cast<std::size_t>(2u)] = std::deque<boost::multiprecision::utility::point<boost::uint32_t> >(static_cast<std::size_t>(1u), boost::multiprecision::utility::point<boost::uint32_t>(static_cast<boost::uint32_t>(2u), static_cast<boost::uint32_t>(1u)));
    prime_factors_list[static_cast<std::size_t>(3u)] = std::deque<boost::multiprecision::utility::point<boost::uint32_t> >(static_cast<std::size_t>(1u), boost::multiprecision::utility::point<boost::uint32_t>(static_cast<boost::uint32_t>(3u), static_cast<boost::uint32_t>(1u)));

    static const boost::uint32_t n_five = static_cast<boost::uint32_t>(5u);

    std::deque<boost::uint32_t>::const_iterator it_next_prime = std::find(Primes::Data().begin(), Primes::Data().end(), n_five);

    for(std::size_t i = static_cast<std::size_t>(4u); i < prime_factors_list.size(); i++)
    {
      if((it_next_prime != Primes::Data().end()) && (static_cast<boost::uint32_t>(i) == *it_next_prime))
      {
        ++it_next_prime;

        prime_factors_list[i] = std::deque<boost::multiprecision::utility::point<boost::uint32_t> >(static_cast<std::size_t>(1u),
                                                                 boost::multiprecision::utility::point<boost::uint32_t>(static_cast<boost::uint32_t>(i),
                                                                 static_cast<boost::uint32_t>(1u)));
      }
      else
      {
        Primes::Factors(static_cast<boost::uint32_t>(i), prime_factors_list[i]);
      }
    }
  }

  if(static_cast<std::size_t>(n) < prime_factors_list.size())
  {
    pf = prime_factors_list[static_cast<std::size_t>(n)];
  }
  else
  {
    Primes::Factors(n, pf);
  }
}
