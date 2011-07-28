
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _E_FLOAT_ELEMENTARY_TRANS_HPP_
  #define _E_FLOAT_ELEMENTARY_TRANS_HPP_

  #include <deque>

  namespace ef
  {
    e_float pow2    (const INT64 p);
    e_float pown    (const e_float& x, const INT64 p);
    e_float inv     (const e_float& x);
    e_float sqrt    (const e_float& x);
    e_float cbrt    (const e_float& x);
    e_float rootn   (const e_float& x, const INT32 p);
    e_float exp     (const e_float& x);
    e_float log     (const e_float& x);
    e_float log10   (const e_float& x);
    e_float loga    (const e_float& a, const e_float& x);
    e_float log1p   (const e_float& x);
    e_float log1p1m2(const e_float& x);
    e_float pow     (const e_float& x, const e_float& a);
    void    sinhcosh(const e_float& x, e_float* const p_sin, e_float* const p_cos);
    e_float sinh    (const e_float& x);
    e_float cosh    (const e_float& x);
    e_float tanh    (const e_float& x);
    e_float asinh   (const e_float& x);
    e_float acosh   (const e_float& x);
    e_float atanh   (const e_float& x);
  }

  namespace ef
  {
    void    sincos  (const e_float& x, e_float* const p_sin, e_float* const p_cos);
    e_float sin     (const e_float& x);
    e_float cos     (const e_float& x);
    e_float tan     (const e_float& x);
    e_float csc     (const e_float& x);
    e_float sec     (const e_float& x);
    e_float cot     (const e_float& x);
    e_float asin    (const e_float& x);
    e_float acos    (const e_float& x);
    e_float atan    (const e_float& x);
    e_float atan2   (const e_float& y, const e_float& x);
  }

  namespace ef
  {
    e_float hyp0F0(const e_float& x);
    e_float hyp0F1(const e_float& b, const e_float& x);
    e_float hyp1F0(const e_float& a, const e_float& x);
    e_float hyp1F1(const e_float& a, const e_float& b, const e_float& x);
    e_float hyp2F0(const e_float& a, const e_float& b, const e_float& x);
    e_float hyp2F1(const e_float& a, const e_float& b, const e_float& c, const e_float& x);
    e_float hypPFQ(const std::deque<e_float>& a, const  std::deque<e_float>& b, const e_float& x);
  }

#endif // _E_FLOAT_ELEMENTARY_TRANS_HPP_
