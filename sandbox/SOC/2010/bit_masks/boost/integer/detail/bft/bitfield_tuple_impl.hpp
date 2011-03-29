//  Copyright 2010 Brian Bartman.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_BITFIELD_TUPLE_IMPL_HPP
#define BOOST_BITFIELD_TUPLE_IMPL_HPP

// Integer Includes.
#include <boost/integer/bits_mask.hpp>
#include <boost/integer/bit_width.hpp>

// std includes
#include <cstddef>

// Other boost includes.
#include <boost/static_assert.hpp>

// implementation header files.
#include <boost/integer/detail/bft/bitfield_element.hpp>
#include <boost/integer/detail/bft/arg_parse_impl.hpp>
#include <boost/integer/detail/bft/deduce_storage.hpp>

namespace boost { namespace bitfields{ namespace detail {

// The following preprocessor MACRO only used for writing clarity, it's only 
// used once and then undef'ed before the end of this file.
#define BOOST_BFT_ARG_PROCESSING      \
        detail::bft_arg_parse_impl<\
            T0, \
            mpl::void_,\
            mpl::vector<>,\
            mpl::size_t<0u>\
        >\
        BOOST_BFT_UNPACK_PARAMS()

/** bitfield_tuple base class
 *  The bitfield_tuple_base class is responsible for preforming static assertions on some 
 *  preconditions and dealing with the parsed arguments. This is the base class 
 *  for bitfield_tuple.
 *
 *  Base Class preconditions.
 *
 *  1) The bitfields specified must not exceed the bitwidth of the storage type.
 *      Enforced. Not going any where, but may be redefined or altered based
 *          on if I allow the supplied storage type to be an array.
 */
template <  BOOST_BFT_BASE_TEMPLATE_PARAMS() >
struct bitfield_tuple_base {

    
    typedef typename BOOST_BFT_ARG_PROCESSING   processed_args;

    // extracting te Arguments from processed_args relating to 
    // the storage policy. Also preforming static assertios 
    // where they can be done.
    typedef typename processed_args::storage_policy     processed_storage_type;
    typedef typename processed_args::field_vector       field_vector;
    typedef typename processed_args::offset             offset;

    // deducing storage type
    typedef typename mpl::if_<
        is_same<
            processed_storage_type,
            mpl::void_
        >,
        typename detail::deduce_storage_type<offset>::type,
        processed_storage_type
    >::type                                             storage_type;

    // Precondition: the offet at the end of everything must be the
    // the same as or less then the bit_width of the storage type.
    BOOST_STATIC_ASSERT((
        offset::value
            <=
        bit_width< storage_type >::value
    ));

};

}}} // end boost::detail

#undef BOOST_BFT_ARG_PROCESSING

#endif