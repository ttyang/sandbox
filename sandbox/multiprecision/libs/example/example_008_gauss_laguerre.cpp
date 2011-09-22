
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <iostream>
#include <vector>

#include <boost/multiprecision/mp_float.hpp>
#include <boost/multiprecision/mp_float_functions.hpp>

#include "examples.h"

#include <boost/multiprecision/utility/util_digit_scale.hpp>
#include <boost/multiprecision/utility/util_find_root_newton_raphson.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/noncopyable.hpp>
#include <boost/multiprecision/utility/util_point.hpp>

using boost::multiprecision::mp_float;

namespace examples
{
  namespace nr_008
  {
    class GaussQuadAbscissasAndWeights : private boost::noncopyable
    {
    protected:

      const boost::int32_t N;
      std::vector<mp_float> xi;
      std::vector<mp_float> wi;

    protected:

      GaussQuadAbscissasAndWeights(const boost::int32_t n) : N (n),
                                                    xi(0u),
                                                    wi(0u) { }

    public:

      virtual ~GaussQuadAbscissasAndWeights() { }

    public:

      const std::vector<mp_float>& abscissas(void) const { return xi; }
      const std::vector<mp_float>& weights  (void) const { return wi; }
    };

    class GuassLaguerreAbscissasAndWeights : public GaussQuadAbscissasAndWeights
    {
    private:

      const mp_float alpha;

    public:

      GuassLaguerreAbscissasAndWeights(const boost::int32_t n, const mp_float& a = boost::multiprecision::zero());

      virtual ~GuassLaguerreAbscissasAndWeights() { }

    private:

      class FindRootLaguerre : public boost::multiprecision::utility::find_root_newton_raphson<mp_float>
      {
      private:

        static const mp_float& my_tol(void)
        {
          static const mp_float val = mp_float("1E-" + boost::lexical_cast<std::string>(boost::multiprecision::tol() - static_cast<boost::int64_t>(3)));
          return val;
        }

        const   boost::int32_t   N;
        const   mp_float alpha;
        mutable mp_float my_d;
        mutable mp_float my_p2;

      public:

        FindRootLaguerre(const boost::int32_t    n,
                         const mp_float& a,
                         const mp_float& lo,
                         const mp_float& hi) : boost::multiprecision::utility::find_root_newton_raphson<mp_float>(lo, hi, my_tol()),
                                              N    (n),
                                              alpha(a),
                                              my_d (static_cast<boost::uint32_t>(0u)),
                                              my_p2(static_cast<boost::uint32_t>(0u)) { }

        virtual ~FindRootLaguerre() { }

        const mp_float& poly_p2(void) const { return my_p2; }

      private:

        virtual void my_function_derivative(const mp_float& x, mp_float& f, mp_float& d) const;

        virtual mp_float my_function(const mp_float& x) const;
      };

      mp_float my_laguerre(const mp_float& x) const
      {
        static const FindRootLaguerre rl(N, alpha, boost::multiprecision::zero(), boost::multiprecision::million());
        return rl.function(x);
      }
    };
  }
}

examples::nr_008::GuassLaguerreAbscissasAndWeights::GuassLaguerreAbscissasAndWeights(const boost::int32_t n,
                                                                                     const mp_float& a) : GaussQuadAbscissasAndWeights(n),
                                                                                                         alpha(a)
{
  // Walk through the function using a step-size of dynamic width
  // to find the zero crossings of the Laguerre function.
  // Store these zero crossings as bracketed root estimates.
  std::vector<boost::multiprecision::utility::point<mp_float> > xlo_xhi_points;

  // Estimate first Laguerre zero using the approximation of x1
  // from Stroud and Secrest.
  const double alf = to_double(alpha);
  const double x1 = ((1.0 + alf) * (3.0 + (0.92 * alf))) / (1.0 + (2.4 * static_cast<double>(N)) + (1.8 * alf));

  mp_float delta(x1 / 10.0);
  mp_float x = delta;

  bool bo_is_neg = isneg(my_laguerre(boost::multiprecision::zero()));

  std::cout << "finding approximate roots..." << std::endl;

  while(static_cast<boost::int32_t>(xlo_xhi_points.size()) < N)
  {
    x += delta;

    if(isneg(my_laguerre(x)) != bo_is_neg)
    {
      // Refine the approximate root with 16 bisection iteration steps.
      mp_float dx;
      mp_float rt;
      mp_float hi = x;
      mp_float lo = x - delta;

      if(my_laguerre(lo) < boost::multiprecision::zero())
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
      for(boost::uint32_t j = static_cast<boost::uint32_t>(0u); j < static_cast<boost::uint32_t>(16u); j++)
      {
        dx /= static_cast<boost::int32_t>(2);

        const mp_float x_mid = rt + dx;
        const mp_float f_mid = my_laguerre(x_mid);

        if(f_mid <= boost::multiprecision::zero())
        {
          rt = x_mid;
        }
      }

      // Store the refined approximate root as a bracketed point.
      xlo_xhi_points.push_back(boost::multiprecision::utility::point<mp_float>(rt - dx, rt + dx));

      if(xlo_xhi_points.size() > static_cast<std::size_t>(1u))
      {
        const mp_float new_delta2 =   (xlo_xhi_points.end() - static_cast<std::size_t>(1u))->x
                                   - (xlo_xhi_points.end() - static_cast<std::size_t>(2u))->x;

        // Dynamically adjust and set the new step-size.
        delta = new_delta2 / static_cast<boost::int32_t>(2);
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
    const mp_float ri = rooti.operation();

    if(!rooti.success())
    {
      break;
    }

    // Calculate the weights.
    mp_float f;
    mp_float d;
    rooti.function_derivative(ri, f, d);

    // Store abscissas and weights.
    xi.push_back(ri);

    if(iszero(alpha))
    {
      wi.push_back(-boost::multiprecision::one() / ((d * N) * rooti.poly_p2()));
    }
    else
    {
      const mp_float norm_g = boost::multiprecision::gamma(alpha + N) / boost::multiprecision::factorial(static_cast<boost::uint32_t>(N - static_cast<boost::int32_t>(1)));
      wi.push_back(-norm_g / ((d * N) * rooti.poly_p2()));
    }
  }
}

void examples::nr_008::GuassLaguerreAbscissasAndWeights::FindRootLaguerre::my_function_derivative(const mp_float& x, mp_float& f, mp_float& d) const
{
  f = my_function(x);
  d = my_d;
}

mp_float examples::nr_008::GuassLaguerreAbscissasAndWeights::FindRootLaguerre::my_function(const mp_float& x) const
{
  mp_float p1(1);
  mp_float p2(0);

  for(boost::int32_t j = static_cast<boost::int32_t>(0); j < N; j++)
  {
    const mp_float p3(p2);
    p2 = p1;

    const boost::int32_t j_plus_one     = static_cast<boost::int32_t>(j + static_cast<boost::int32_t>(1));
    const boost::int32_t two_j_plus_one = static_cast<boost::int32_t>(j + j_plus_one);

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
    struct GaussLaguerreAi : public boost::multiprecision::utility::function_base<mp_float>
    {
    private:

      const mp_float x;
      const mp_float zeta;
      const mp_float one_over_zeta;
            mp_float factor;

    public:

      GaussLaguerreAi(const mp_float& X) : x(X),
                                          zeta(boost::multiprecision::two_third() * (boost::multiprecision::sqrt(x) * x)),
                                          one_over_zeta(boost::multiprecision::one() / zeta),
                                          factor(0u)
      {
        const mp_float zeta_times_48_pow_sixth = rootn(zeta * static_cast<boost::int32_t>(48), static_cast<boost::int32_t>(6));
        factor = boost::multiprecision::one() / ((boost::multiprecision::sqrt_pi() * zeta_times_48_pow_sixth) * (exp(zeta) * boost::multiprecision::gamma(boost::multiprecision::five() / static_cast<boost::int32_t>(6))));
      }

      virtual ~GaussLaguerreAi() { }

    private:

      virtual mp_float my_function(const mp_float& t) const
      {
        return factor / boost::multiprecision::rootn(boost::multiprecision::two() + (t * one_over_zeta), static_cast<boost::int32_t>(6));
      }
    };
  }
}

mp_float examples::nr_008::gauss_laguerre_airy_a(const mp_float& x)
{
  static const boost::int32_t n_terms = static_cast<boost::int32_t>(boost::multiprecision::utility::digit_scale() * 400.0);

  static const GuassLaguerreAbscissasAndWeights aw(n_terms, -boost::multiprecision::one() / static_cast<boost::int32_t>(6));

  static const std::size_t sz = aw.weights().size();

  const GaussLaguerreAi ai(x);

  mp_float sum(0);

  for(std::size_t i = static_cast<std::size_t>(0u); i < sz; i++)
  {
    const mp_float fi = ai.function(aw.abscissas()[i]);
    const mp_float wi = aw.weights()[i];

    const mp_float term = wi * fi;

    const boost::int64_t order_check = static_cast<boost::int64_t>(term.order() - sum.order());

    if((i > static_cast<boost::int32_t>(20)) && (order_check < -boost::multiprecision::tol()))
    {
      break;
    }

    sum += term;
  }

  return sum;
}
