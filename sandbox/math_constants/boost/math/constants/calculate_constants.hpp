//  Copyright John Maddock 2010.
//  Copyright Paul A. Bristow 2011.

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_CALCULATE_CONSTANTS_CONSTANTS_INCLUDED
#define BOOST_MATH_CALCULATE_CONSTANTS_CONSTANTS_INCLUDED

namespace boost{ namespace math{ namespace constants{ namespace detail{

template <class T, int N> 
inline T calculate_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING

   return ldexp(acos(T(0)), 1);

   /*
   // Although this code works well, it's usually more accurate to just call acos
   // and access the numner types own representation of PI which is usually calculated
   // at slightly higher precision...

   T result;
   T a = 1;
   T b;
   T A(a);
   T B = 0.5f;
   T D = 0.25f;

   T lim;
   lim = boost::math::tools::epsilon<T>();

   unsigned k = 1;

   do
   {
      result = A + B;
      result = ldexp(result, -2);
      b = sqrt(B);
      a += b;
      a = ldexp(a, -1);
      A = a * a;
      B = A - result;
      B = ldexp(B, 1);
      result = A - B;
      bool neg = boost::math::sign(result) < 0;
      if(neg)
         result = -result;
      if(result <= lim)
         break;
      if(neg)
         result = -result;
      result = ldexp(result, k - 1);
      D -= result;
      ++k;
      lim = ldexp(lim, 1);
   }
   while(true);

   result = B / D;
   return result;
   */
}

template <class T, int N> 
inline T calculate_two_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   return 2 * pi<T, policies::policy<policies::digits2<N> > >();
}

template <class T, int N> 
inline T calculate_one_div_two_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   return 1 / two_pi<T, policies::policy<policies::digits2<N> > >();
}

template <class T, int N> 
inline T calculate_root_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return sqrt(pi<T, policies::policy<policies::digits2<N> > >());
}

template <class T, int N> 
inline T calculate_root_half_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return sqrt(pi<T, policies::policy<policies::digits2<N> > >() / 2);
}

template <class T, int N> 
inline T calculate_root_two_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return sqrt(two_pi<T, policies::policy<policies::digits2<N> > >());
}

template <class T, int N> 
inline T calculate_root_ln_four(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return sqrt(log(static_cast<T>(4)));
}

template <class T, int N> 
inline T calculate_e(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   //
   // Although we can clearly calculate this from first principles, this hooks into
   // T's own notion of e, which hopefully will more accurate than one calculated to
   // a few epsilon:
   //
   BOOST_MATH_STD_USING
   return exp(static_cast<T>(1));
}

template <class T, int N> 
inline T calculate_half(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   return static_cast<T>(1) / static_cast<T>(2);
}

template <class T, int N> 
inline T calculate_euler(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   //
   // This is the method described in:
   // "Some New Algorithms for High-Precision Computation of Euler's Constant"
   // Richard P Brent and Edwin M McMillan.
   // Mathematics of Comnputation, Volume 34, Number 149, Jan 1980, pages 305-312.
   // See equation 17 with p = 2.
   //
   T n = 3 + boost::math::tools::digits<T>() / 4;
   T lnn = log(n);
   T term = 1;
   T N = -lnn;
   T D = 1;
   T Hk = 0;
   T one = 1;

   for(unsigned k = 1;; ++k)
   {
      term *= n * n;
      term /= k * k;
      Hk += one / k;
      N += term * (Hk - lnn);
      D += term;

      if(term < D * boost::math::tools::epsilon<T>())
         break;
   }
   return N / D;
}

template <class T, int N> 
inline T calculate_root_two(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return sqrt(static_cast<T>(2));
}


template <class T, int N> 
inline T calculate_root_three(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return sqrt(static_cast<T>(3));
}

template <class T, int N> 
inline T calculate_half_root_two(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return sqrt(static_cast<T>(2)) / 2;
}

template <class T, int N> 
inline T calculate_ln_two(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   //
   // Although there are good ways to calculate this from scratch, this hooks into
   // T's own notion of log(2) which will hopefully be accurate to the full precision
   // of T:
   //
   BOOST_MATH_STD_USING
   return log(static_cast<T>(2));
}

template <class T, int N> 
inline T calculate_ln_ln_two(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return log(log(static_cast<T>(2)));
}

template <class T, int N> 
inline T calculate_third(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return static_cast<T>(1) / static_cast<T>(3);
}

template <class T, int N> 
inline T calculate_twothirds(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return static_cast<T>(2) / static_cast<T>(3);
}

template <class T, int N> 
inline T calculate_two_thirds(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return static_cast<T>(2) / static_cast<T>(3);
}

template <class T, int N> 
inline T calculate_three_quarters(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return static_cast<T>(3) / static_cast<T>(4);
}

template <class T, int N> 
inline T calculate_pi_minus_three(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   return pi<T, policies::policy<policies::digits2<N> > >() - static_cast<T>(3);
}

template <class T, int N> 
inline T calculate_four_minus_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   return static_cast<T>(4) - pi<T, policies::policy<policies::digits2<N> > >();
}

template <class T, int N> 
inline T calculate_pow23_four_minus_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return pow(four_minus_pi<T, policies::policy<policies::digits2<N> > >(), static_cast<T>(1.5));
}

template <class T, int N> 
inline T calculate_exp_minus_half(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return exp(static_cast<T>(-0.5));
}

// Pi
template <class T, int N> 
inline T calculate_one_div_root_two(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   return static_cast<T>(1) / root_two<T, policies::policy<policies::digits2<N> > >();
}

template <class T, int N> 
inline T calculate_one_div_root_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   return static_cast<T>(1) / root_pi<T, policies::policy<policies::digits2<N> > >();
}

template <class T, int N> 
inline T calculate_one_div_root_two_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   return static_cast<T>(1) / root_two_pi<T, policies::policy<policies::digits2<N> > >();
}

template <class T, int N> 
inline T calculate_root_one_div_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   return sqrt(static_cast<T>(1) / pi<T, policies::policy<policies::digits2<N> > >());
}


template <class T, int N> 
inline T calculate_four_thirds_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return pi<T, policies::policy<policies::digits2<N> > >() * static_cast<T>(4) / static_cast<T>(3);
}

template <class T, int N> 
inline T calculate_half_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return pi<T, policies::policy<policies::digits2<N> > >()  / static_cast<T>(2);
}


template <class T, int N> 
inline T calculate_third_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return pi<T, policies::policy<policies::digits2<N> > >()  / static_cast<T>(3);
}

template <class T, int N> 
inline T calculate_sixth_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return pi<T, policies::policy<policies::digits2<N> > >()  / static_cast<T>(6);
}

template <class T, int N> 
inline T calculate_two_thirds_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return pi<T, policies::policy<policies::digits2<N> > >() * static_cast<T>(2) / static_cast<T>(3);
}

template <class T, int N> 
inline T calculate_three_quarters_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return pi<T, policies::policy<policies::digits2<N> > >() * static_cast<T>(3) / static_cast<T>(4);
}

template <class T, int N> 
inline T calculate_pi_pow_e(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return pow(pi<T, policies::policy<policies::digits2<N> > >(), e<T, policies::policy<policies::digits2<N> > >()); // 
}

template <class T, int N> 
inline T calculate_pi_sqr(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return pi<T, policies::policy<policies::digits2<N> > >()
   *      pi<T, policies::policy<policies::digits2<N> > >() ; // 
}

template <class T, int N> 
inline T calculate_pi_sqr_div_six(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return pi<T, policies::policy<policies::digits2<N> > >()
   *      pi<T, policies::policy<policies::digits2<N> > >()
   / static_cast<T>(6); // 
}


template <class T, int N> 
inline T calculate_pi_cubed(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return pi<T, policies::policy<policies::digits2<N> > >()
   *      pi<T, policies::policy<policies::digits2<N> > >()
   *      pi<T, policies::policy<policies::digits2<N> > >()
   ; // 
}

template <class T, int N> 
inline T calculate_cbrt_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return pow(pi<T, policies::policy<policies::digits2<N> > >(), static_cast<T>(-3));
}

template <class T, int N> 
inline T calculate_one_div_cbrt_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return static_cast<T>(1)
   / pow(pi<T, policies::policy<policies::digits2<N> > >(), static_cast<T>(-3));
}

// Euler's e

template <class T, int N> 
inline T calculate_e_pow_pi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return pow(e<T, policies::policy<policies::digits2<N> > >(), pi<T, policies::policy<policies::digits2<N> > >()); // 
}

template <class T, int N> 
inline T calculate_root_e(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return sqrt(e<T, policies::policy<policies::digits2<N> > >());
}

template <class T, int N> 
inline T calculate_log10_e(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return log10(e<T, policies::policy<policies::digits2<N> > >());
}

template <class T, int N> 
inline T calculate_one_div_log10_e(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return  static_cast<T>(1) /
     log10(e<T, policies::policy<policies::digits2<N> > >());
}

// Trigonometric

template <class T, int N> 
inline T calculate_degree(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return pi<T, policies::policy<policies::digits2<N> > >()
   / static_cast<T>(180) 
   ; // 
}

template <class T, int N> 
inline T calculate_radian(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return static_cast<T>(180)
   / pi<T, policies::policy<policies::digits2<N> > >()
   ; // 
}

template <class T, int N> 
inline T calculate_sin_one(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return sin(static_cast<T>(1)) ; // 
}

template <class T, int N> 
inline T calculate_cos_one(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return cos(static_cast<T>(1)) ; // 
}

template <class T, int N> 
inline T calculate_sinh_one(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return sinh(static_cast<T>(1)) ; // 
}

template <class T, int N> 
inline T calculate_cosh_one(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return cosh(static_cast<T>(1)) ; // 
}

template <class T, int N> 
inline T calculate_phi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return (static_cast<T>(1) + sqrt(static_cast<T>(5)) )/static_cast<T>(2) ; // 
}

template <class T, int N> 
inline T calculate_log_phi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   //return  log(phi<T, policies::policy<policies::digits2<N> > >()); // ???
   return log((static_cast<T>(1) + sqrt(static_cast<T>(5)) )/static_cast<T>(2) );
}
template <class T, int N> 
inline T calculate_one_div_log_phi(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
   return static_cast<T>(1) /
     log((static_cast<T>(1) + sqrt(static_cast<T>(5)) )/static_cast<T>(2) );
}

// Euler-Mascheroni's Gamma Constant

//http://en.wikipedia.org/wiki/Euler%E2%80%93Mascheroni_constant

//http://en.wikipedia.org/wiki/Gamma_function

template <class T, int N> 
inline T calculate_gamma(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
     // 1000 digits from http://www.wolframalpha.com
 T gamma(
  "0.577215664901532860606512090082402431042159335939923598805767234884867726"
 "777664670936947063291746749514631447249807082480960504014486542836224173"
 "997644923536253500333742937337737673942792595258247094916008735203948165"
 "670853233151776611528621199501507984793745085705740029921354786146694029"
 "604325421519058775535267331399254012967420513754139549111685102807984234"
 "877587205038431093997361372553060889331267600172479537836759271351577226"
 "102734929139407984301034177717780881549570661075010161916633401522789358"
 "679654972520362128792265559536696281763887927268013243101047650596370394"
 "739495763890657296792960100901512519595092224350140934987122824794974719"
 "564697631850667612906381105182419744486783638086174945516989279230187739"
 "107294578155431600500218284409605377243420328547836701517739439870030237"
 "033951832869000155819398804270741154222781971652301107356583396734871765"
 "049194181230004065469314299929777956930310050308630341856980323108369164"
 "0025892970890985486825777364288253954925873629596133298574739302"
);
 //    T gamma("0.57721566490153286060651209008240243104215933593992");
     return gamma;
       // TODO calculate this - JM has code.

}

template <class T, int N> 
inline T calculate_one_div_gamma(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING

     return static_cast<T>(1) 
     / gamma<T, policies::policy<policies::digits2<N> > >();
}


template <class T, int N> 
inline T calculate_gamma_sqr(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING

     return gamma<T, policies::policy<policies::digits2<N> > >()
     * gamma<T, policies::policy<policies::digits2<N> > >();
}

// Continued fraction
template <class T, int N> 
inline T calculate_cf10(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
    // TODO calculate this.
   BOOST_MATH_STD_USING
     T cf10("1.030640834100712935881776094116936840925");
     return cf10;
}

//Zeta

template <class T, int N> 
inline T calculate_zeta_two(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   BOOST_MATH_STD_USING
    
     return pi<T, policies::policy<policies::digits2<N> > >()
     *  pi<T, policies::policy<policies::digits2<N> > >()
     /static_cast<T>(6);
}

template <class T, int N> 
inline T calculate_zeta_three(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   // http://mathworld.wolfram.com/AperysConstant.html
   // http://en.wikipedia.org/wiki/Mathematical_constant

   // http://oeis.org/A002117/constant
   //T zeta3("1.20205690315959428539973816151144999076"
   // "4986292340498881792271555341838205786313"
   // "09018645587360933525814619915");

  //"1.202056903159594285399738161511449990, 76498629234049888179227155534183820578631309018645587360933525814619915"  A002117
  // 1.202056903159594285399738161511449990, 76498629234049888179227155534183820578631309018645587360933525814619915780, +00);
  //"1.2020569031595942 double
  // http://www.spaennare.se/SSPROG/ssnum.pdf  // section 11, Algorithmfor Apery’s constant zeta(3).
  // Programs to Calculate some Mathematical Constants to Large Precision, Document Version 1.50
 
  // by Stefan Spannare  September 19, 2007
  // zeta(3) = 1/64 * sum 
   T n_fact=static_cast<T>(1); // build n! for n = 0.
   T sum = static_cast<double>(77); // Start with n = 0 case.
   // for n = 0, (77/1) /64 = 1.203125
   //double lim = std::numeric_limits<double>::epsilon();
   T lim = boost::math::tools::epsilon<T>();
   for(unsigned int n = 1; n < 40; ++n)
   { // three to five decimal digits per term, so 40 should be plenty for 100 decimal digits.
      //cout << "n = " << n << endl;
      n_fact *= n; // n!
      T n_fact_p10 = n_fact * n_fact * n_fact * n_fact * n_fact * n_fact * n_fact * n_fact * n_fact * n_fact; // (n!)^10
      T num = ((205 * n * n) + (250 * n) + 77) * n_fact_p10; // 205n^2 + 250n + 77
      // int nn = (2 * n + 1);
      // T d = factorial(nn); // inline factorial.
      T d = 1;
      for(unsigned int i = 1; i <= (n+n + 1); ++i) // (2n + 1)
      {
        d *= i;
      }
      T den = d * d * d * d * d; // [(2n+1)!]^5
      //cout << "den = " << den << endl;
      T term = num/den;
      if (n % 2 != 0)
      { //term *= -1;
        sum -= term;
      }
      else
      {
        sum += term;
      }
      //cout << "term = " << term << endl;
      //cout << "sum/64  = " << sum/64 << endl;
      if(abs(term) < lim)
      {
         break;
      }
   }
   return sum / 64;
}

template <class T, int N> 
inline T calculate_catalan(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{ // http://oeis.org/A006752/constant
  //T c("0.915965594177219015054603514932384110774"
 //"149374281672134266498119621763019776254769479356512926115106248574");

  // 9.159655941772190150546035149323841107, 74149374281672134266498119621763019776254769479356512926115106248574422619, -01);

   // This is equation (entry) 31 from
   // http://www-2.cs.cmu.edu/~adamchik/articles/catalan/catalan.htm
   // See also http://www.mpfr.org/algorithms.pdf
   T k_fact = 1;
   T tk_fact = 1;
   T sum = 1;
   T term;
   T lim = boost::math::tools::epsilon<T>();

   for(unsigned k = 1;; ++k)
   {
      k_fact *= k;
      tk_fact *= (2 * k) * (2 * k - 1);
      term = k_fact * k_fact / (tk_fact * (2 * k + 1) * (2 * k + 1));
      sum += term;
      if(term < lim)
      {
         break;
      }
   }
   return boost::math::constants::pi<T, boost::math::policies::policy<> >()
      * log(2 + boost::math::constants::root_three<T, boost::math::policies::policy<> >())
       / 8
      + 3 * sum / 8;
}


template <class T, int N> 
inline T calculate_khinchin(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{ // from e_float constants.cpp
  // http://mathworld.wolfram.com/KhinchinsConstant.html
  // TODO calculate this.
  T k( "2.6854520010653064453097148354817956938203822939944629530511523455572188595371520028011411749318476979"
"9515346590528809008289767771641096305179253348325966838185231542133211949962603932852204481940961806"
"8664166428930847788062036073705350103367263357728904990427070272345170262523702354581068631850103237"
"4655803775026442524852869468234189949157306618987207994137235500057935736698933950879021244642075289"
"7414591476930184490506017934993852254704042033779856398310157090222339100002207725096513324604444391"
"9169146085968234821283246228292710126906974182348477675457348986254203392662351862086778136650969658"
"3146995271837448054012195366666049648269890827548115254721177330319675947383719393578106059230401890"
"7113496246737068412217946810740608918276695667117166837405904739368809534504899970471763904513432323"
"7715103219651503824698888324870935399469608264781812056634946712578436664579740977848366204977774868"
"2765697087163192938512899314199518611673792654620563505951385713761697126872299805327673278710513763"
"9563719023145289003058136910904799672757571385043565050641590820999623402779053834180985121278529455");
 return k;
}

template <class T, int N> 
inline T calculate_extreme_value_skewness(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{ // from e_float constants.cpp
  // Mathematica: N[12 Sqrt[6]  Zeta[3]/Pi^3, 1101]
  // TODO Calculate this.

T ev(
"1.1395470994046486574927930193898461120875997958365518247216557100852480077060706857071875468869385150"
"1894272048688553376986765366075828644841024041679714157616857834895702411080704529137366329462558680"
"2015498788776135705587959418756809080074611906006528647805347822929577145038743873949415294942796280"
"0895597703063466053535550338267721294164578901640163603544404938283861127819804918174973533694090594"
"3094963822672055237678432023017824416203652657301470473548274848068762500300316769691474974950757965"
"8640779777748741897542093874605477776538884083378029488863880220988107155275203245233994097178778984"
"3488995668362387892097897322246698071290011857605809901090220903955815127463328974447572119951192970"
"3684453635456559086126406960279692862247058250100678008419431185138019869693206366891639436908462809"
"9756051372711251054914491837034685476095423926553367264355374652153595857163724698198860485357368964"
"3807049634423621246870868566707915720704996296083373077647528285782964567312903914752617978405994377"
"9064157147206717895272199736902453130842229559980076472936976287378945035706933650987259357729800315");

return ev;
}

template <class T, int N> 
inline T calculate_glaisher(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{ // from http://mpmath.googlecode.com/svn/data/glaisher.txt
  // 20,000 digits of the Glaisher-Kinkelin constant A = exp(1/2 - zeta'(-1))
  // Computed using A = exp((6 (-zeta(2))/pi^2 + log 2 pi + gamma)/12)
  // with Euler-Maclaurin summation for zeta'(2).
  // TODO calculate this.

  T g(
"1.282427129100622636875342568869791727767688927325001192063740021740406308858826"
"46112973649195820237439420646120399000748933157791362775280404159072573861727522"
"14334327143439787335067915257366856907876561146686449997784962754518174312394652"
"76128213808180219264516851546143919901083573730703504903888123418813674978133050"
"93770833682222494115874837348064399978830070125567001286994157705432053927585405"
"81731588155481762970384743250467775147374600031616023046613296342991558095879293"
"36343887288701988953460725233184702489001091776941712153569193674967261270398013"
"52652668868978218897401729375840750167472114895288815996668743164513890306962645"
"59870469543740253099606800842447417554061490189444139386196089129682173528798629"
"88434220366989900606980888785849587494085307347117090132667567503310523405221054"
"14176776156308191919997185237047761312315374135304725819814797451761027540834943"
"14384965234139453373065832325673954957601692256427736926358821692159870775858274"
"69575162841550648585890834128227556209547002918593263079373376942077522290940187");

  return g;
}

template <class T, int N> 
inline T calculate_rayleigh_skewness(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{  // From e_float
  // 1100 digits of the Rayleigh distribution skewness
  // Mathematica: N[2 Sqrt[Pi] (Pi - 3)/((4 - Pi)^(3/2)), 1100]
  // TODO Calculate this using pi_minus_three etc.

T rs(  
  "0.6311106578189371381918993515442277798440422031347194976580945856929268196174737254599050270325373067"
  "9440004726436754739597525250317640394102954301685809920213808351450851396781817932734836994829371322"
  "5797376021347531983451654130317032832308462278373358624120822253764532674177325950686466133508511968"
  "2389168716630349407238090652663422922072397393006683401992961569208109477307776249225072042971818671"
  "4058887072693437217879039875871765635655476241624825389439481561152126886932506682176611183750503553"
  "1218982627032068396407180216351425758181396562859085306247387212297187006230007438534686340210168288"
  "8956816965453815849613622117088096547521391672977226658826566757207615552041767516828171274858145957"
  "6137539156656005855905288420585194082284972984285863898582313048515484073396332610565441264220790791"
  "0194897267890422924599776483890102027823328602965235306539844007677157873140562950510028206251529523"
  "7428049693650605954398446899724157486062545281504433364675815915402937209673727753199567661561209251"
  "4695589950526053470201635372590001578503476490223746511106018091907936826431407434894024396366284848");  ;
  return rs;
}

template <class T, int N> 
inline T calculate_rayleigh_kurtosis_excess(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{ // - (6 Pi^2 - 24 Pi + 16)/((Pi - 4)^2)
    // TODO Calculate this using pi_minus_four etc.
   return - (((static_cast<T>(6) * pi<T, policies::policy<policies::digits2<N> > >()
        * pi<T, policies::policy<policies::digits2<N> > >())
   - (static_cast<T>(24) * pi<T, policies::policy<policies::digits2<N> > >()) + static_cast<T>(16) )
   /
   ((pi<T, policies::policy<policies::digits2<N> > >() - static_cast<T>(4))
   * (pi<T, policies::policy<policies::digits2<N> > >() - static_cast<T>(4)))
   );
}

template <class T, int N> 
inline T calculate_rayleigh_kurtosis(const mpl::int_<N>&BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{ // 3 - (6 Pi^2 - 24 Pi + 16)/((Pi - 4)^2)
   // TODO Calculate this using pi_minus_four etc.
   return static_cast<T>(3) - (((static_cast<T>(6) * pi<T, policies::policy<policies::digits2<N> > >()
        * pi<T, policies::policy<policies::digits2<N> > >())
   - (static_cast<T>(24) * pi<T, policies::policy<policies::digits2<N> > >()) + static_cast<T>(16) )
   /
   ((pi<T, policies::policy<policies::digits2<N> > >() - static_cast<T>(4))
   * (pi<T, policies::policy<policies::digits2<N> > >() - static_cast<T>(4)))
   );
}


}}}} // namespaces

#endif // BOOST_MATH_CALCULATE_CONSTANTS_CONSTANTS_INCLUDED
