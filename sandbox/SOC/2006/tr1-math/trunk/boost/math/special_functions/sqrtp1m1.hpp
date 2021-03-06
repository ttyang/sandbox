//  (C) Copyright John Maddock 2006.
//
//  This code may be used under either of the following two licences:
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE. OF SUCH DAMAGE.
//
//  Or:
//
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SQRTP1M1
#define BOOST_MATH_SQRTP1M1

#include <boost/math/tools/series.hpp>
#include <boost/math/tools/precision.hpp>

//
// This algorithm computes sqrt(1+x)-1 for small x only:
//

namespace boost{ namespace math{ namespace detail{

template <class T>
struct sqrtp1m1_series
{
   typedef T result_type;
   sqrtp1m1_series(T z_) : result(z_/2), z(z_), k(1){}
   T operator()()
   {
      T r = result;
      result *= z * (k - T(0.5));
      ++k;
      result /= -k;
      return r;
   }
private:
   T result, z;
   int k;
};

} // namespace detail

template <class T>
T sqrtp1m1(const T& val)
{
   using namespace std;

   if(fabs(val) > 0.75)
      return sqrt(1 + val) - 1;
   detail::sqrtp1m1_series<T> gen(val);
   return tools::kahan_sum_series(gen, ::boost::math::tools::digits<T>());
}

} } // namespaces

#endif // BOOST_MATH_SQRTP1M1



