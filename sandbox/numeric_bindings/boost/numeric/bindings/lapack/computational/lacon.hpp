//
// Copyright (c) 2003--2009
// Toon Knapen, Karl Meerbergen, Kresimir Fresl,
// Thomas Klimpel and Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// THIS FILE IS AUTOMATICALLY GENERATED
// PLEASE DO NOT EDIT!
//

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_LACON_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_LACON_HPP

#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/is_complex.hpp>
#include <boost/numeric/bindings/traits/is_real.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void lacon( integer_t const n, float* v, float* x, integer_t* isgn,
            float& est, integer_t& kase ) {
        LAPACK_SLACON( &n, v, x, isgn, &est, &kase );
    }
    inline void lacon( integer_t const n, double* v, double* x,
            integer_t* isgn, double& est, integer_t& kase ) {
        LAPACK_DLACON( &n, v, x, isgn, &est, &kase );
    }
    inline void lacon( integer_t const n, traits::complex_f* v,
            traits::complex_f* x, float& est, integer_t& kase ) {
        LAPACK_CLACON( &n, traits::complex_ptr(v), traits::complex_ptr(x),
                &est, &kase );
    }
    inline void lacon( integer_t const n, traits::complex_d* v,
            traits::complex_d* x, double& est, integer_t& kase ) {
        LAPACK_ZLACON( &n, traits::complex_ptr(v), traits::complex_ptr(x),
                &est, &kase );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct lacon_impl{};

// real specialization
template< typename ValueType >
struct lacon_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename VectorX, typename V, typename ISGN >
    static void invoke( integer_t const n, VectorX& x, real_type& est,
            integer_t& kase, detail::workspace2< V, ISGN > work ) {
        BOOST_ASSERT( n >= 1 );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_v( n ));
        BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
                min_size_isgn( n ));
        detail::lacon( n, traits::vector_storage(work.select(real_type())),
                traits::vector_storage(x),
                traits::vector_storage(work.select(integer_t())), est, kase );
    }

    // minimal workspace specialization
    template< typename VectorX >
    static void invoke( integer_t const n, VectorX& x, real_type& est,
            integer_t& kase, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_v( min_size_v( n ) );
        traits::detail::array< integer_t > tmp_isgn( min_size_isgn( n ) );
        invoke( n, x, est, kase, workspace( tmp_v, tmp_isgn ) );
    }

    // optimal workspace specialization
    template< typename VectorX >
    static void invoke( integer_t const n, VectorX& x, real_type& est,
            integer_t& kase, optimal_workspace work ) {
        invoke( n, x, est, kase, minimal_workspace() );
    }

    static integer_t min_size_v( integer_t const n ) {
        return n;
    }

    static integer_t min_size_isgn( integer_t const n ) {
        return n;
    }
};

// complex specialization
template< typename ValueType >
struct lacon_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename VectorX, typename V >
    static void invoke( integer_t const n, VectorX& x, real_type& est,
            integer_t& kase, detail::workspace1< V > work ) {
        BOOST_ASSERT( n >= 1 );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_v( n ));
        detail::lacon( n, traits::vector_storage(work.select(value_type())),
                traits::vector_storage(x), est, kase );
    }

    // minimal workspace specialization
    template< typename VectorX >
    static void invoke( integer_t const n, VectorX& x, real_type& est,
            integer_t& kase, minimal_workspace work ) {
        traits::detail::array< value_type > tmp_v( min_size_v( n ) );
        invoke( n, x, est, kase, workspace( tmp_v ) );
    }

    // optimal workspace specialization
    template< typename VectorX >
    static void invoke( integer_t const n, VectorX& x, real_type& est,
            integer_t& kase, optimal_workspace work ) {
        invoke( n, x, est, kase, minimal_workspace() );
    }

    static integer_t min_size_v( integer_t const n ) {
        return n;
    }
};


// template function to call lacon
template< typename VectorX, typename Workspace >
inline integer_t lacon( integer_t const n, VectorX& x,
        typename traits::vector_traits< VectorX >::value_type& est,
        integer_t& kase, Workspace work ) {
    typedef typename traits::vector_traits< VectorX >::value_type value_type;
    integer_t info(0);
    lacon_impl< value_type >::invoke( n, x, est, kase, work );
    return info;
}

// template function to call lacon, default workspace type
template< typename VectorX >
inline integer_t lacon( integer_t const n, VectorX& x,
        typename traits::vector_traits< VectorX >::value_type& est,
        integer_t& kase ) {
    typedef typename traits::vector_traits< VectorX >::value_type value_type;
    integer_t info(0);
    lacon_impl< value_type >::invoke( n, x, est, kase,
            optimal_workspace() );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
