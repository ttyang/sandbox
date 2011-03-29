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

#ifndef BOOST_MATH_TOOLS_RATIONAL_HPP
#define BOOST_MATH_TOOLS_RATIONAL_HPP

namespace boost{ namespace math{ namespace tools{

template <class T, class U>
U evaluate_polynomial(const T* poly, U z, std::size_t count)
{
   U sum = static_cast<U>(poly[count - 1]);
   for(int i = static_cast<int>(count) - 2; i >= 0; --i)
   {
      sum *= z;
      sum += static_cast<U>(poly[i]);
   }
   return sum;
}

template <class T, class U>
inline U evaluate_even_polynomial(const T* poly, U z, std::size_t count)
{
   return evaluate_polynomial(poly, z*z, count);
}

template <class T, class U>
inline U evaluate_odd_polynomial(const T* poly, U z, std::size_t count)
{
   return poly[0] + z * evaluate_polynomial(poly+1, z*z, count-1);
}

template <class T, class U, class V>
V evaluate_rational(const T* num, const U* denom, V z, std::size_t count)
{
   V s1, s2;
   if(z <= 1)
   {
      s1 = num[count-1];
      s2 = denom[count-1];
      for(int i = (int)count - 2; i >= 0; --i)
      {
         s1 *= z;
         s2 *= z;
         s1 += num[i];
         s2 += denom[i];
      }
   }
   else
   {
      z = 1 / z;
      s1 = num[0];
      s2 = denom[0];
      for(unsigned i = 1; i < count; ++i)
      {
         s1 *= z;
         s2 *= z;
         s1 += num[i];
         s2 += denom[i];
      }
   }
   return s1 / s2;
}


}}} // namespaces

#endif // BOOST_MATH_TOOLS_RATIONAL_HPP


