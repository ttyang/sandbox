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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_SBGST_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_SBGST_HPP

#include <boost/numeric/bindings/lapack/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <cassert>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void sbgst( char const vect, char const uplo, integer_t const n,
            integer_t const ka, integer_t const kb, float* ab,
            integer_t const ldab, float* bb, integer_t const ldbb, float* x,
            integer_t const ldx, float* work, integer_t& info ) {
        LAPACK_SSBGST( &vect, &uplo, &n, &ka, &kb, ab, &ldab, bb, &ldbb, x,
                &ldx, work, &info );
    }
    inline void sbgst( char const vect, char const uplo, integer_t const n,
            integer_t const ka, integer_t const kb, double* ab,
            integer_t const ldab, double* bb, integer_t const ldbb, double* x,
            integer_t const ldx, double* work, integer_t& info ) {
        LAPACK_DSBGST( &vect, &uplo, &n, &ka, &kb, ab, &ldab, bb, &ldbb, x,
                &ldx, work, &info );
    }
}

// value-type based template
template< typename ValueType >
struct sbgst_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixAB, typename MatrixBB, typename MatrixX,
            typename WORK >
    static void compute( char const vect, integer_t const n,
            integer_t const ka, integer_t const kb, MatrixAB& ab,
            MatrixBB& bb, MatrixX& x, integer_t& info,
            detail::workspace1< WORK > work ) {
#ifndef NDEBUG
        assert( vect == 'N' || vect == 'V' );
        assert( traits::matrix_uplo_tag(a) == 'U' ||
                traits::matrix_uplo_tag(a) == 'L' );
        assert( n >= 0 );
        assert( ka >= 0 );
        assert( kb >= kb );
        assert( traits::leading_dimension(ab) >= ka+1 );
        assert( traits::leading_dimension(bb) >= kb+1 );
        assert( traits::vector_size(work.select(real_type()) >= min_size_work(
                n )));
#endif
        detail::sbgst( vect, traits::matrix_uplo_tag(a), n, ka, kb,
                traits::matrix_storage(ab), traits::leading_dimension(ab),
                traits::matrix_storage(bb), traits::leading_dimension(bb),
                traits::matrix_storage(x), traits::leading_dimension(x),
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixAB, typename MatrixBB, typename MatrixX >
    static void compute( char const vect, integer_t const n,
            integer_t const ka, integer_t const kb, MatrixAB& ab,
            MatrixBB& bb, MatrixX& x, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work( n ) );
        compute( vect, n, ka, kb, ab, bb, x, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixAB, typename MatrixBB, typename MatrixX >
    static void compute( char const vect, integer_t const n,
            integer_t const ka, integer_t const kb, MatrixAB& ab,
            MatrixBB& bb, MatrixX& x, integer_t& info,
            optimal_workspace work ) {
        compute( vect, n, ka, kb, ab, bb, x, info, minimal_workspace() );
    }

    static integer_t min_size_work( integer_t const n ) {
        return 2*n;
    }
};


// template function to call sbgst
template< typename MatrixAB, typename MatrixBB, typename MatrixX,
        typename Workspace >
inline integer_t sbgst( char const vect, integer_t const n,
        integer_t const ka, integer_t const kb, MatrixAB& ab, MatrixBB& bb,
        MatrixX& x, Workspace work = optimal_workspace() ) {
    typedef typename traits::matrix_traits< MatrixAB >::value_type value_type;
    integer_t info(0);
    sbgst_impl< value_type >::compute( vect, n, ka, kb, ab, bb, x, info,
            work );
    return info;
}


}}}} // namespace boost::numeric::bindings::lapack

#endif
