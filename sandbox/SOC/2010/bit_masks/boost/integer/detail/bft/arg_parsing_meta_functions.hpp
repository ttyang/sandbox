//  Copyright 2010 Brian Bartman.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_BITFIELD_TUPLE_POINTER_PARSING_HELPERS_HPP
#define BOOST_BITFIELD_TUPLE_POINTER_PARSING_HELPERS_HPP

#include <boost/cstdint.hpp>
#include <boost/integer/bits_mask.hpp>
#include <cstddef>
#include <boost/mpl/size_t.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/mpl/if.hpp>

/** This file contains metafunctions which are used to do complex operations
 *  on the Mask provided by the user.
 */
namespace boost { namespace detail {

/** This is an integral type which is the same size as a pointer on a 32 or 64
 *  bit system
 */ 
typedef mpl::if_c<(4<sizeof(void*)),uint64_t,uint32_t>::type ptr_mask_type;

namespace pointer_member {

// this is ugly but I would like it for organizational purposes.
namespace ptr_detail {

// Count leading zeros helper
// basically recurse until the true false condition is evaluated as false.
template <
    typename Mask,
    typename IndexingMask = bits_mask<
        typename make_unsigned<
            typename Mask::value_type
        >::type,
        bit_width<
            typename Mask::value_type
        >::value - 1
    >,
    std::size_t ZeroCount = 0,
    bool = true
>
struct clz_helper;

/** Continued recursive case. */
template <
    typename Mask,
    typename IndexingMask,
    std::size_t ZeroCount
>
struct clz_helper<Mask,IndexingMask,ZeroCount,true>
    :clz_helper<
        Mask,
        bits_mask<
            typename IndexingMask::value_type,
            IndexingMask::offset - 1
        >,
        ZeroCount + 1,
        ((IndexingMask::value & Mask::value) == 0)
          &&
        (IndexingMask::offset >= 0)
    >
{ };

/** Recursive Termination Case. */ 
template <
    typename Mask,
    typename IndexingMask,
    std::size_t ZeroCount
>
struct clz_helper<Mask,IndexingMask,ZeroCount,false> {
    typedef mpl::size_t<ZeroCount - 1> type;
};


template <
    typename Mask,
    typename IndexingMask = bits_mask<
        typename make_unsigned< typename Mask::value_type >::type,
        0
    >,
    std::size_t ZeroCount = 0,
    bool = true
>
struct ctz_helper;

/** Recursive loop. */

template <
    typename Mask,
    typename IndexingMask,
    std::size_t ZeroCount
>
struct ctz_helper<Mask,IndexingMask,ZeroCount,true>
    :ctz_helper<
        Mask,
        bits_mask<
            typename IndexingMask::value_type,
            IndexingMask::offset + 1
        >,
        ZeroCount + 1,
       bool(((IndexingMask::value & Mask::value) == 0)
         &&
       bool(mpl::less< mpl::size_t< IndexingMask::offset > , mpl::size_t< bit_width< typename Mask::value_type >::value > >::type::value ))
    >
{ };

/** Recursive tremination. */
template <
    typename Mask,
    typename IndexingMask,
    std::size_t ZeroCount
>
struct ctz_helper<Mask,IndexingMask,ZeroCount,false> {
    typedef mpl::size_t<ZeroCount - 1 >  type;
};

} // end ptr_detail

template <typename Mask>
struct count_leading_zeros {
    typedef typename ptr_detail::clz_helper<Mask>::type type;
};


template <typename Mask>
struct count_trailing_zeros {
    typedef typename ptr_detail::ctz_helper<Mask>::type type;
};

}}} // end boost::detail::pointer_member

#endif
