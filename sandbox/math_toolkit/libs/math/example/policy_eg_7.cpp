//  Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Note that this file contains quickbook markup as well as code
// and comments, don't change any of the special comment markups!

#include <iostream>

//[policy_eg_7

#include <boost/math/distributions.hpp>

namespace {

using namespace boost::math::policies;

typedef policy<
   // return infinity and set errno rather than throw:
   overflow_error<errno_on_error>,
   // Don't promote double -> long double internally:
   promote_double<false>,
   // Return the closest integer result for discrete quantiles:
   discrete_quantile<integer_nearest>
> my_policy;

BOOST_MATH_DECLARE_DISTRIBUTIONS(double, my_policy)

} // close namespace my_namespace

int main()
{
   //
   // Start with something we know will overflow:
   //
   normal norm(10, 2);
   errno = 0;
   std::cout << "Result of quantile(norm, 0) is: " 
      << quantile(norm, 0) << std::endl;
   std::cout << "errno = " << errno << std::endl;
   errno = 0;
   std::cout << "Result of quantile(norm, 1) is: " 
      << quantile(norm, 1) << std::endl;
   std::cout << "errno = " << errno << std::endl;
   //
   // Now try a discrete distribution:
   //
   binomial binom(20, 0.25);
   std::cout << "Result of quantile(binom, 0.05) is: " 
      << quantile(binom, 0.05) << std::endl;
   std::cout << "Result of quantile(complement(binom, 0.05)) is: " 
      << quantile(complement(binom, 0.05)) << std::endl;
}

/*`

Which outputs:

[pre
Result of quantile(norm, 0) is: -1.#INF
errno = 34
Result of quantile(norm, 1) is: 1.#INF
errno = 34
Result of quantile(binom, 0.05) is: 1
Result of quantile(complement(binom, 0.05)) is: 8
]

This mechanism is particularly useful when we want to define a 
project-wide policy, and don't want to modify the Boost source
or set - possibly fragile and easy to forget - project wide 
build macros.

*/ //] ends quickbook imported section

