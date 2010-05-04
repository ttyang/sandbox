
//
// Copyright 2010 Scott McMurray.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_HASH_PACK_HPP
#define BOOST_HASH_PACK_HPP

#include <boost/assert.hpp>
#include <boost/hash/stream_endian.hpp>
#include <boost/hash/detail/exploder.hpp>
#include <boost/hash/detail/imploder.hpp>
#include <boost/static_assert.hpp>

#ifndef BOOST_HASH_NO_OPTIMIZATION
#include <boost/detail/endian.hpp>
#endif

namespace boost {
namespace hash {

template <typename Endianness,
          int InputBits, int OutputBits,
          bool Explode = (InputBits > OutputBits),
          bool Implode = (InputBits < OutputBits)>
struct real_packer;

template <typename Endianness,
          int Bits>
struct real_packer<Endianness,
                   Bits, Bits,
                   false, false> {

    template <typename InputType, typename OutputType>
    static void pack_n(InputType const *in, size_t in_n,
                       OutputType *out) {
        unsigned i = 0;
        for (unsigned j = 0; j < in_n; ++j) {
            out[i++] = in[j];
        }
    }

    template <typename IterT1, typename IterT2>
    void pack(IterT1 b1, IterT1 e1, IterT2 b2) {
        while (b1 != e1) *b2++ = *b1++;
    }

};

template <typename Endianness,
          int InputBits, int OutputBits>
struct real_packer<Endianness,
                   InputBits, OutputBits,
                   true, false> {

    BOOST_STATIC_ASSERT(InputBits % OutputBits == 0);

    template <typename InIter, typename OutIter>
    static void pack_n(InIter in, size_t in_n,
                       OutIter out) {
        for (unsigned j = 0; j < in_n; ++j) {
            typedef typename std::iterator_traits<InIter>::value_type InValue;
            InValue const value = *in++;
            detail::exploder<Endianness, InputBits, OutputBits>
             ::explode(value, out);
        }
    }

    template <typename InIter, typename OutIter>
    static void pack(InIter in, InIter in_e,
                     OutIter out) {
        while (in != in_e) {
            typedef typename std::iterator_traits<InIter>::value_type InValue;
            InValue const value = *in++;
            detail::exploder<Endianness, InputBits, OutputBits>
             ::explode(value, out);
        }
    }

};

template <typename Endianness,
          int InputBits, int OutputBits>
struct real_packer<Endianness,
                   InputBits, OutputBits,
                   false, true> {

    BOOST_STATIC_ASSERT(OutputBits % InputBits == 0);

    template <typename InIter, typename OutIter>
    static void pack_n(InIter in, size_t in_n,
                       OutIter out) {
        size_t out_n = in_n/(OutputBits/InputBits);
        for (unsigned j = 0; j < out_n; ++j) {
            typedef typename std::iterator_traits<OutIter>::value_type OutValue;
            OutValue value = OutValue();
            detail::imploder<Endianness, InputBits, OutputBits>
             ::implode(in, value);
            *out++ = value;
        }
    }

    template <typename InIter, typename OutIter>
    static void pack(InIter in, InIter in_e,
                     OutIter out) {
        while (in != in_e) {
            typedef typename std::iterator_traits<OutIter>::value_type OutValue;
            OutValue value = OutValue();
            detail::imploder<Endianness, InputBits, OutputBits>
             ::implode(in, value);
            *out++ = value;
        }
    }

};

template <typename Endianness,
          int InputBits, int OutputBits,
          bool BytesOnly = !(InputBits % CHAR_BIT) && !(OutputBits % CHAR_BIT)>
struct packer : real_packer<Endianness, InputBits, OutputBits> {};

template <typename Endianness,
          int InValueBits, int OutValueBits,
          typename IterT1, typename IterT2>
void pack_n(IterT1 in, size_t in_n, 
            IterT2 out) {
    typedef packer<Endianness, InValueBits, OutValueBits> packer_type;
    packer_type::pack_n(in, in_n, out);
}

template <typename Endianness,
          int InValueBits, int OutValueBits,
          typename IterT1, typename IterT2>
void pack_n(IterT1 in, size_t in_n, 
            IterT2 out, size_t out_n) {
    BOOST_ASSERT(in_n*InValueBits == out_n*OutValueBits);
    pack_n<Endianness, InValueBits, OutValueBits>(in, in_n, out);
}

template <typename Endianness,
          int InValueBits, int OutValueBits,
          typename IterT1, typename IterT2>
void pack(IterT1 b1, IterT1 e1, std::random_access_iterator_tag,
          IterT2 b2) {
    pack_n<Endianness, InValueBits, OutValueBits>(b1, e1-b1, b2);
}

template <typename Endianness,
          int InValueBits, int OutValueBits,
          typename IterT1, typename CatT1,
          typename IterT2>
void pack(IterT1 b1, IterT1 e1, CatT1,
          IterT2 b2) {
    typedef packer<Endianness, InValueBits, OutValueBits> packer_type;
    packer_type::pack(b1, e1, b2);
}

template <typename Endianness,
          int InValueBits, int OutValueBits,
          typename IterT1, typename IterT2>
void pack(IterT1 b1, IterT1 e1,
          IterT2 b2) {
    typedef typename std::iterator_traits<IterT1>::iterator_category cat1;
    pack<Endianness, InValueBits, OutValueBits>(b1, e1, cat1(), b2);
}

template <typename Endianness,
          int InValueBits, int OutValueBits,
          typename IterT1, typename IterT2>
void pack(IterT1 b1, IterT1 e1, std::random_access_iterator_tag,
          IterT2 b2, IterT2 e2, std::random_access_iterator_tag) {
    pack_n<Endianness, InValueBits, OutValueBits>(b1, e1-b1, b2, e2-b2);
}

template <typename Endianness,
          int InValueBits, int OutValueBits,
          typename IterT1, typename CatT1,
          typename IterT2, typename CatT2>
void pack(IterT1 b1, IterT1 e1, CatT1,
          IterT2 b2, IterT2, CatT2) {
    pack<Endianness, InValueBits, OutValueBits>(b1, e1, b2);
}

template <typename Endianness,
          int InValueBits, int OutValueBits,
          typename IterT1, typename IterT2>
void pack(IterT1 b1, IterT1 e1,
          IterT2 b2, IterT2 e2) {
    typedef typename std::iterator_traits<IterT1>::iterator_category cat1;
    typedef typename std::iterator_traits<IterT2>::iterator_category cat2;
    pack<Endianness, InValueBits, OutValueBits>(b1, e1, cat1(), b2, e2, cat2());
}

template <typename Endianness,
          int InValueBits, int OutValueBits,
          typename InputType, typename OutputType>
void pack(InputType const &in, OutputType &out) {
    BOOST_STATIC_ASSERT(InputType::static_size*InValueBits ==
                        OutputType::static_size*OutValueBits);
    pack_n<Endianness, InValueBits, OutValueBits>(&in[0], in.size(),
                                                  &out[0], out.size());
}

} // namespace hash
} // namespace boost

#endif // BOOST_HASH_PACK_HPP
