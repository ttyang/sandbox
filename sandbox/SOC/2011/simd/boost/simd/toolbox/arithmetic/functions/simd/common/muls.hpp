//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_MULS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_MULS_HPP_INCLUDED
#include <boost/simd/include/functions/is_eqz.hpp>
#include <boost/simd/include/functions/is_ltz.hpp>
#include <boost/simd/include/functions/abs.hpp>
#include <boost/simd/include/functions/select.hpp>
#include <boost/simd/include/functions/rdivide.hpp>
// /////////////////////////////////////////////////////////////////////////////
// // Implementation when type A0 is int 32 8 64
// /////////////////////////////////////////////////////////////////////////////
// BOOST_SIMD_REGISTER_DISPATCH(boost::simd::tag::muls_, tag::cpu_,
//                        (A0)(X),
//                        ((simd_<integer_<A0>,X>))((simd_<integer_<A0>,X>))
//                       );
// namespace boost { namespace simd { namespace ext
// {
//   template<class X, class Dummy>
//   struct call<boost::simd::tag::muls_(tag::simd_<tag::integer_, X> ,
// 			 boost::simd::tag::simd_<tag::integer_, X>),
//               boost::simd::tag::cpu_, Dummy> : callable
//   {
//     template<class Sig> struct result;
//     template<class This,class A0>
//     struct result<This(A0, A0)> : meta::strip<A0>{};
//     BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
//     {
//       typedef typename dispatch::meta::as_integer<A0, unsigned>::type untype; 
//       A0 sign = b_xor(is_ltz(a0), is_ltz(a1));
//       untype aa0 = simd::native_cast<untype>(boost::simd::abs(a0));
//       untype aa1 = simd::native_cast<untype>(boost::simd::abs(a1));
//       untype ga =  boost::simd::max(aa0, aa1);
//       untype la =  boost::simd::min(aa0, aa1);
// //       std::cout << "a0 "<< a0 << std::endl;
// //       std::cout << "a1 "<< a1 << std::endl;
// //       std::cout << "aa0 "<< aa0 << std::endl;
// //       std::cout << "aa1 "<< aa1 << std::endl;
// //       std::cout << "ga  "<< ga  << std::endl;
// //       std::cout << "la  "<< la  << std::endl;
// //       std::cout << "sgn "<< sign<< std::endl;
// //       std::cout << "rd  "<< rdivide(simd::native_cast<untype>(Valmax<A0>()), ga)<< std::endl;
// //       std::cout << "is_ltz(a0) " << is_ltz(a0)<< std::endl;
// //       std::cout << "is_ltz(a1) " << is_ltz(a1)<< std::endl;
// //       std::cout << "rdivide(simd::native_cast<untype>(Valmax<A0>()), ga)  " << rdivide(simd::native_cast<untype>(Valmax<A0>()), aa0)<< std::endl;
// //       std::cout << "aa1  " << aa1 << std::endl;
// //       std::cout << "lt(rdivide(simd::native_cast<untype>(Valmax<A0>()), aa0), aa1)  " << lt(rdivide(simd::native_cast<untype>(Valmax<A0>()), aa0), aa1)<< std::endl;
//       return sel( lt(rdivide(simd::native_cast<untype>(Valmax<A0>()), ga), la),
// 		  sel(sign, Valmin<A0>(), Valmax<A0>()),
// 		  a0*a1
// 		 ); 
//     }
//   };
// } } }
// /////////////////////////////////////////////////////////////////////////////
// // Implementation when type A0 is uint 32 8 64
// /////////////////////////////////////////////////////////////////////////////
// BOOST_SIMD_REGISTER_DISPATCH(boost::simd::tag::muls_, tag::cpu_,
//                        (A0)(X),
//                        ((simd_<unsigned_<A0>,X>))((simd_<unsigned_<A0>,X>))
//                       );
// namespace boost { namespace simd { namespace ext
// {
//   template<class X, class Dummy>
//   struct call<boost::simd::tag::muls_(tag::simd_<tag::unsigned_, X> ,
// 			 boost::simd::tag::simd_<tag::unsigned_, X>),
//               boost::simd::tag::cpu_, Dummy> : callable
//   {
//     template<class Sig> struct result;
//     template<class This,class A0>
//     struct result<This(A0, A0)> : meta::strip<A0>{};
//     BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
//     {
//       return sel( lt(rdivide(Valmax<A0>(), a0), a1),
// 		  Valmax<A0>(),
// 		  a0*a1
// 		 ); 
//     }
//   };
// } } }
#endif
