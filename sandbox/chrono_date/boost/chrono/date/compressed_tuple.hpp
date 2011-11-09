//  compressed_tuple
//
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_COMPRESSED_TUPLE_HPP
#define BOOST_CHRONO_DATE_MONTH_NTH_HPP

#include <boost/cstdint.hpp>

namespace boost
{
  namespace compressed
  {

    template <typename T>
    struct width_bits : integral_constant<std::size, sizeof(T)> {};

    template <typename T>
    struct compress
    {
      static int64_t apply(T);
    };
    template <typename T>
    struct decompress
    {
      static T apply(int64_t);
    };

    template <typename T>
    struct Compressable {


    };


    template <typename T1, typename T2>
    class tuple2
    {
      typedef least<T1,T2>::type storage;
      storage value_;
    public:
      template <std::size N>
      void save(typename types<N>::type);
      template <std::size N>
      typename types<N>::type load();

      tuple2(T1 v1, T2 v2)
      {
        save<0>(v1);
        save<1>(v2);
      }

    };

  } // compressed

} // boost


#endif  // header
