// Copyright John Maddock 2010.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/math/constants/generate.hpp>

int main()
{
   BOOST_CONSTANTS_GENERATE(pi);
   BOOST_CONSTANTS_GENERATE(two_pi);
   BOOST_CONSTANTS_GENERATE(one_div_two_pi);
   BOOST_CONSTANTS_GENERATE(root_pi);
   BOOST_CONSTANTS_GENERATE(root_half_pi);
   BOOST_CONSTANTS_GENERATE(root_two_pi);
   BOOST_CONSTANTS_GENERATE(root_ln_four);
   BOOST_CONSTANTS_GENERATE(e);
   BOOST_CONSTANTS_GENERATE(euler);
   BOOST_CONSTANTS_GENERATE(root_two);
   BOOST_CONSTANTS_GENERATE(half_root_two);
   BOOST_CONSTANTS_GENERATE(ln_two);
   BOOST_CONSTANTS_GENERATE(ln_ln_two);
   BOOST_CONSTANTS_GENERATE(third);
   BOOST_CONSTANTS_GENERATE(twothirds);
   BOOST_CONSTANTS_GENERATE(pi_minus_three);
   BOOST_CONSTANTS_GENERATE(four_minus_pi);
   BOOST_CONSTANTS_GENERATE(pow23_four_minus_pi);
   BOOST_CONSTANTS_GENERATE(exp_minus_half);
   BOOST_CONSTANTS_GENERATE(one_div_root_two);
   BOOST_CONSTANTS_GENERATE(one_div_root_two_pi);
   return 0;
}

