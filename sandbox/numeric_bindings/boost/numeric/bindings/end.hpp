//
// Copyright (c) 2009 Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_NUMERIC_BINDINGS_END_HPP
#define BOOST_NUMERIC_BINDINGS_END_HPP

#include <boost/numeric/bindings/detail/adaptor.hpp>
#include <boost/numeric/bindings/detail/dense_iterator.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace result_of {

template< typename T >
struct end {
    typedef detail::dense_iterator< typename value_type<T>::type > type;
};

} // namespace result_of

template< typename T >
detail::dense_iterator< typename value_type<T>::type > end( T& t ) {
    return detail::dense_iterator< typename value_type<T>::type >(
        detail::adaptor_access<T>::data( t ) ) + tensor_size1( t );
}

template< typename T >
detail::dense_iterator< typename value_type<T const>::type > end( T const& t ) {
    return detail::dense_iterator< typename value_type<T const>::type >(
        detail::adaptor_access<T const>::data( t ) ) + tensor_size1( t );
}

} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
