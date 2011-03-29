//  Copyright 2010 Brian Bartman.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_POINTER_MEMBER_FIELD_HPP
#define BOOST_POINTER_MEMBER_FIELD_HPP
#include <cstddef>
#include <boost/integer/detail/bft/arg_parsing_meta_functions.hpp>
#include <boost/integer/high_bits_mask.hpp>
#include <boost/integer/bit_width.hpp>


namespace boost {
namespace bitfields {

/** ReturnType in this case is the type that is having a pointer made to it.
 *      so putting int* will make the structure return int** to you because 
 *      that wound indecate pointer to a pointer.
 *  Name - same as member and flag.
 *  Mask - This is the mask that returns the pointer itself and tells
 *      the user which parts of the pointer are to be stored/retrieved for
 *      stroage.
 */
template <
    typename ReturnType,
    typename Name,
    typename Mask = high_bits_mask<
        detail::ptr_mask_type,
        bit_width< detail::ptr_mask_type >::value - 2
    >
>
struct pointer;

}} // end boost::bitfields

#endif