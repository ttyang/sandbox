//
// Copyright (c) 2009 Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_NUMERIC_BINDINGS_NOOP_HPP
#define BOOST_NUMERIC_BINDINGS_NOOP_HPP

#include <boost/numeric/bindings/detail/adaptable_type.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/end.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/ref.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace detail {

template< typename T >
struct noop_wrapper:
        adaptable_type< noop_wrapper<T> >,
        reference_wrapper<T> {
    noop_wrapper( T& t ): reference_wrapper<T>( t ) {}
};

template< typename T, typename Id, typename Enable >
struct adaptor< noop_wrapper<T>, Id, Enable > {

    typedef adaptor< typename boost::remove_const<T>::type, T > underlying_adaptor;
    typedef typename underlying_adaptor::property_map property_map;

    static typename result_of::size<T,1>::type size1( const Id& id ) {
        return size<1>( id.get() );
    }

    static typename result_of::begin_value< T >::type begin_value( Id& id ) {
        return bindings::begin_value( id.get() );
    }

    static typename result_of::end_value< T >::type end_value( Id& id ) {
        return bindings::end_value( id.get() );
    }

};

} // namespace detail

namespace result_of {

template< typename T >
struct noop {
    typedef detail::noop_wrapper<T> type;
};

} // namespace result_of

template< typename T >
detail::noop_wrapper<T> noop( T& underlying ) {
    return detail::noop_wrapper<T>( underlying );
}

template< typename T >
detail::noop_wrapper<const T> noop( const T& underlying ) {
    return detail::noop_wrapper<const T>( underlying );
}

} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
