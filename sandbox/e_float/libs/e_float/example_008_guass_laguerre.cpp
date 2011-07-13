
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} � ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <vector>

#include <e_float/e_float.hpp>
#include <e_float/e_float_functions.hpp>

#include "examples.h"
#include "../src/utility/util_digit_scale.h"
#include "../src/utility/util_find_root_newton_raphson.h"
#include "../src/utility/util_lexical_cast.h"
#include "../src/utility/util_noncopyable.h"
#include "../src/utility/util_point.h"

namespace examples
{
  namespace nr_008
  {
    class GaussQuadAbscissasAndWeights : private Util::noncopyable
    {
    protected:

      const INT32 N;
      std::vector<e_float> xi;
      std::vector<e_float> wi;

    protected:

      GaussQuadAbscissasAndWeights(const INT32 n) : N (n),
                                                    xi(0u),
                                                    wi(0u) { }

    public:

      virtual ~GaussQuadAbscissasAndWeights() { }

    public:

      const std::vector<e_float>& abscissas(void) const { return xi; }
      const std::vector<e_float>& weights  (void) const { return wi; }
    };

    class GuassLaguerreAbscissasAndWeights : public GaussQuadAbscissasAndWeights
    {
    private:

      const e_float alpha;

    public:

      GuassLaguerreAbscissasAndWeights(const INT32 n, const e_float& a = ef::zero());

      virtual ~GuassLaguerreAbscissasAndWeights() { }

    private:

      class FindRootLaguerre : public Util::FindRootNewtonRaphson<e_float>
      {
      private:

        static const e_float& my_tol(void)
        {
          static const e_float val = e_float("1E-" + Util::lexical_cast(ef::tol() - static_cast<INT64>(3)));
          return val;
        }

        const   INT32   N;
        const   e_float alpha;
        mutable e_float my_d;
        mutable e_float my_p2;

      public:

        FindRootLaguerre(const INT32    n,
                         const e_float& a,
                         const e_float& lo,
                         const e_float& hi) : Util::FindRootNewtonRaphson<e_float>(lo, hi, my_tol()),
                                              N    (n),
                                              alpha(a),
                                              my_d (static_cast<UINT32>(0u)),
                                              my_p2(static_cast<UINT32>(0u)) { }

        virtual ~FindRootLaguerre() { }

        const e_float& poly_p2(void) const { return my_p2; }

      private:

        virtual void my_function_derivative(const e_float& x, e_float& f, e_float& d) const;

        virtual e_float my_function(const e_float& x) const;
      };

      e_float my_laguerre(const e_float& x) const
      {
        static const FindRootLaguerre rl(N, alpha, ef::zero(), ef::million());
        return rl.function(x);
      }
    };
  }
}

examples::nr_008::GuassLaguerreAbscissasAndWeights::GuassLaguerreAbscissasAndWeights(const INT32 n,
                                                                                     const e_float& a) : GaussQuadAbscissasAndWeights(n),
                                                                                                         alpha(a)
{
  // Walk through the function using a step-size of dynamic width
  // to find the zero crossings of the Laguerre function.
  // Store these zero crossings as bracketed root estimates.
  std::vector<Util::point<e_float> > xlo_xhi_points;

  // Estimate first Laguerre zero using the approximation of x1
  // from Stroud and Secrest.
  const double alf = ef::to_double(alpha);
  const double x1 = ((1.0 + alf) * (3.0 + (0.92 * alf))) / (1.0 + (2.4 * static_cast<double>(N)) + (1.8 * alf));

  e_float delta(x1 / 10.0);
  e_float x = delta;

  bool bo_is_neg = ef::isneg(my_laguerre(ef::zero()));

  std::cout << "finding approximate roots..." << std::endl;

  while(static_cast<INT32>(xlo_xhi_points.size()) < N)
  {
    x += delta;

    if(ef::isneg(my_laguerre(x)) != bo_is_neg)
    {
      // Refine the approximate root with 16 bisection iteration steps.
      e_float dx;
      e_float rt;
      e_float hi = x;
      e_float lo = x - delta;

      if(my_laguerre(lo) < ef::zero())
      {
        dx = hi - lo;
        rt = lo;
      }
      else
      {
        dx = lo - hi;
        rt = hi;
      }

      // Here are the 16 bisection iteration steps.
      for(UINT32 j = static_cast<UINT32>(0u); j < static_cast<UINT32>(16u); j++)
      {
        dx /= static_cast<INT32>(2);

        const e_float x_mid = rt + dx;
        const e_float f_mid = my_laguerre(x_mid);

        if(f_mid <= ef::zero())
        {
          rt = x_mid;
        }
      }

      // Store the refined approximate root as a bracketed point.
      xlo_xhi_points.push_back(Util::point<e_float>(rt - dx, rt + dx));

      if(xlo_xhi_points.size() > static_cast<std::size_t>(1u))
      {
        const e_float new_delta2 =   (xlo_xhi_points.end() - static_cast<std::size_t>(1u))->x
                                   - (xlo_xhi_points.end() - static_cast<std::size_t>(2u))->x;

        // Dynamically adjust and set the new step-size.
        delta = new_delta2 / static_cast<INT32>(2);
      }

      bo_is_neg = !bo_is_neg;
    }
  }

  // Calculate the abscissas and weights to full precision.
  for(std::size_t i = static_cast<std::size_t>(0u); i < xlo_xhi_points.size(); i++)
  {
    std::cout << "calculating abscissa and weight for index: " << i << std::endl;

    // Find the abscissas using Newton-Raphson iteration.
    const FindRootLaguerre rooti(N, alpha, xlo_xhi_points[i].x, xlo_xhi_points[i].y);
    const e_float ri = rooti.operation();

    if(!rooti.success())
    {
      break;
    }

    // Calculate the weights.
    e_float f;
    e_float d;
    rooti.function_derivative(ri, f, d);

    // Store abscissas and weights.
    xi.push_back(ri);

    if(ef::iszero(alpha))
    {
      wi.push_back(-ef::one() / ((d * N) * rooti.poly_p2()));
    }
    else
    {
      const e_float norm_g = ef::gamma(alpha + N) / ef::factorial(static_cast<UINT32>(N - static_cast<INT32>(1)));
      wi.push_back(-norm_g / ((d * N) * rooti.poly_p2()));
    }
  }
}

void examples::nr_008::GuassLaguerreAbscissasAndWeights::FindRootLaguerre::my_function_derivative(const e_float& x, e_float& f, e_float& d) const
{
  f = my_function(x);
  d = my_d;
}

e_float examples::nr_008::GuassLaguerreAbscissasAndWeights::FindRootLaguerre::my_function(const e_float& x) const
{
  e_float p1(1);
  e_float p2(0);

  for(INT32 j = static_cast<INT32>(0); j < N; j++)
  {
    const e_float p3(p2);
    p2 = p1;

    const INT32 j_plus_one     = static_cast<INT32>(j + static_cast<INT32>(1));
    const INT32 two_j_plus_one = static_cast<INT32>(j + j_plus_one);

    p1 = (((two_j_plus_one + (alpha - x)) * p2) - ((j + alpha) * p3)) / j_plus_one;
  }

  my_d  = ((N * p1) - ((N + alpha) * p2)) / x;
  my_p2 = p2;

  return p1;
}

namespace examples
{
  namespace nr_008
  {
    struct GaussLaguerreAi : public Util::Function<e_float>
    {
    private:

      const e_float x;
      const e_float zeta;
      const e_float one_over_zeta;
            e_float factor;

    public:

      GaussLaguerreAi(const e_float& X) : x(X),
                                          zeta(ef::two_third() * (ef::sqrt(x) * x)),
                                          one_over_zeta(ef::one() / zeta),
                                          factor(0u)
      {
        const e_float zeta_times_48_pow_sixth = ef::rootn(zeta * static_cast<INT32>(48), static_cast<INT32>(6));
        factor = ef::one() / ((ef::sqrt_pi() * zeta_times_48_pow_sixth) * (ef::exp(zeta) * ef::gamma(ef::five() / static_cast<INT32>(6))));
      }

      virtual ~GaussLaguerreAi() { }

    private:

      virtual e_float my_function(const e_float& t) const
      {
        return factor / ef::rootn(ef::two() + (t * one_over_zeta), static_cast<INT32>(6));
      }
    };
  }
}

e_float examples::nr_008::gauss_laguerre_airy_a(const e_float& x)
{
  static const INT32 n_terms = static_cast<INT32>(Util::DigitScale() * 400.0);

  static const GuassLaguerreAbscissasAndWeights aw(n_terms, -ef::one() / static_cast<INT32>(6));

  static const std::size_t sz = aw.weights().size();

  const GaussLaguerreAi ai(x);

  e_float sum(0);

  for(std::size_t i = static_cast<std::size_t>(0u); i < sz; i++)
  {
    const e_float fi = ai.function(aw.abscissas()[i]);
    const e_float wi = aw.weights()[i];

    const e_float term = wi * fi;

    const INT64 order_check = static_cast<INT64>(term.order() - sum.order());

    if((i > static_cast<INT32>(20)) && (order_check < -ef::tol()))
    {
      break;
    }

    sum += term;
  }

  return sum;
}
