// Boost.bimap
//
// Copyright 2006 Matias Capeletto
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/bimap for library home page.

/// \file container_adaptor/detail/key_comparison_adaptor.hpp
/// \brief Key comparison adaptor.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_KEY_COMPARISON_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_KEY_COMPARISON_ADAPTOR_HPP

#include <boost/call_traits.hpp>
#include <functional>

namespace boost {
namespace bimap {
namespace container_adaptor {
namespace detail {

/// \brief Value comparison adaptor
/**

A simple adaptor.
                                                                                    **/

// TODO
// * The key comparison adaptor can be optimized for NewKey equal to KeyCompare::argument_type
// * Use ConceptCheck to ensure the validity of KeyCompare
// * This class can be fusioned with value_comparison adaptor in a more general one

template < class KeyCompare, class NewKey, class KeyConverter >
struct key_comparison_adaptor : std::binary_function<NewKey,NewKey,bool>
{
    key_comparison_adaptor( KeyCompare c, KeyConverter conv ) : comp(c), converter(conv) {}

    bool operator()( typename call_traits<NewKey>::param_type x,
                     typename call_traits<NewKey>::param_type y)
    {
        return comp(
            converter(x),
            converter(y)
        );
    }

    private:

    // TODO
    // Apply EBO optimization

    KeyCompare comp;
    KeyConverter converter;
};

} // namespace detail
} // namespace container_adaptor
} // namespace bimap
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_KEY_COMPARISON_ADAPTOR_HPP


