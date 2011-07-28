
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _GENERIC_FUNCTIONS_CONSTANTS_2011_06_18_H_
  #define _GENERIC_FUNCTIONS_CONSTANTS_2011_06_18_H_

  #include <e_float/e_float_constants.hpp>

  namespace generic_functions
  {
    template<typename T> const T& pi         (void);
    template<typename T> const T& ln2        (void);
    template<typename T> const T& euler_gamma(void);

    template<> const float&       pi<float>      (void) { static const float val(3.14159265359f); return val; }
    template<> const double&      pi<double>     (void) { static const double val(3.1415926535897932384626433832795028841971693993751); return val; }
    template<> const long double& pi<long double>(void) { static const long double val(3.1415926535897932384626433832795028841971693993751); return val; }
    template<> const e_float&     pi<e_float>    (void) { return ef::pi(); }

    template<> const float&       ln2<float>      (void) { static const float val(0.693147180560f); return val; }
    template<> const double&      ln2<double>     (void) { static const double val(0.69314718055994530941723212145817656807550013436026); return val; }
    template<> const long double& ln2<long double>(void) { static const long double val(0.69314718055994530941723212145817656807550013436026); return val; }
    template<> const e_float&     ln2<e_float>    (void) { return ef::ln2(); }

    template<> const float&       euler_gamma<float>      (void) { static const float val(0.577215664902f); return val; }
    template<> const double&      euler_gamma<double>     (void) { static const double val(0.57721566490153286060651209008240243104215933593992); return val; }
    template<> const long double& euler_gamma<long double>(void) { static const long double val(0.57721566490153286060651209008240243104215933593992); return val; }
    template<> const e_float&     euler_gamma<e_float>    (void) { return ef::euler_gamma(); }

    template<typename T> const T& pi(void)
    {
      static bool is_init = false;

      static T val;

      if(!is_init)
      {
        is_init = true;

        // Compute pi using a quadratically convergent AGM method.
        // Caution: This is slow, in particular since the generic
        // square root implementation is slow.
        T a (1u);
        T bB(T(1u) / static_cast<INT32>(2));
        T s (bB);
        T t (T(3u) / static_cast<INT32>(8));

        for(INT32 k = static_cast<INT32>(1); k < static_cast<INT32>(64); k++)
        {
          bB   = generic_functions::sqrt<T>(bB);
          a   += bB;
          a   /= static_cast<INT32>(2);
          val  = a;
          val *= a;
          bB   = val;
          bB  -= t;
          bB  *= static_cast<INT32>(2);

          T iterate_term(bB);
          iterate_term -= val;
          iterate_term *= static_cast<INT32>(1u << k);

          s  += iterate_term;

          INT64  ne = static_cast<INT64>(0);
          const double dd = generic_functions::frexp10<T>(iterate_term, &ne);
          static_cast<void>(dd);

          // Test the significant digits of the last iteration change.
          // If the iteration change is small enough, then the calculation
          // of pi is finished.
          if(static_cast<int>(ne) < -std::numeric_limits<T>::digits10 / 2)
          {
            break;
          }

          t   = val;
          t  += bB;
          t  /= static_cast<INT32>(4);
        }

        val += bB;
        val /= s;
      }

      // This is pi.
      return val;
    }

    template<typename T> const T& ln2(void)
    {
      static bool is_init = false;

      static T val;

      if(!is_init)
      {
        is_init = true;

        // ln2 = pi / [2m * AGM(1, 4 / 2^m)], where m is chosen such that m > n / 2
        // and n is the number of bits of precision required in the result.
        // Chose m > N / (2 * log10(2)), in other words m > N * 1.661,
        // where N is the number of decimal digits of precision.

        // Choose m > N * 1.661
        const INT32 m = static_cast<INT32>(1.7 * static_cast<double>(std::numeric_limits<T>::digits10));

        // Set a0 = 1.
        // Set b0 = 4 / (2^m) = 1 / 2^(m - 2)
        T ak(1u);
        T bk = static_cast<INT32>(4) / generic_functions::pown<T>(T(2), static_cast<INT64>(m));

        for(INT32 k = static_cast<INT32>(0); k < static_cast<INT32>(64); k++)
        {
          const T a = ak;
          ak += bk;
          ak /= static_cast<INT32>(2);
          bk *= a;
          bk  = generic_functions::sqrt<T>(bk);

          const T delta = ak - bk;

          // Check for the number of significant digits.
          if(   (k > static_cast<INT32>(4))
             && (generic_functions::fabs<T>(delta) < (std::numeric_limits<T>::min)())
            )
          {
            break;
          }
        }

        // The iteration is finished.
        // Compute ln2 = pi / [2m * AGM(1, 4 / 2^m)].
        // Note that a = b = AGM(...).

        // Get pi, invert a and divide by 2m.
        val = generic_functions::pi<T>() / (ak * static_cast<INT32>(static_cast<INT32>(2) * m));
      }

      // This is ln2.
      return val;
    }

    template<typename T> const T& euler_gamma(void)
    {
      // TBD: Need a generic algorithm for Euler's gamma.
      // TBD: This is difficult without a precomputed value or binary splitting.
      // TBD: Consider Gauss' harmonic series.
      static const T val(0u);
      return val;
    }
  }

#endif // _GENERIC_FUNCTIONS_CONSTANTS_2011_06_18_H_
