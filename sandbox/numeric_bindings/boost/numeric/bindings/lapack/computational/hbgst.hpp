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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_HBGST_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_HBGST_HPP

#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {

inline void hbgst( const char vect, const char uplo, const integer_t n,
        const integer_t ka, const integer_t kb, traits::complex_f* ab,
        const integer_t ldab, const traits::complex_f* bb,
        const integer_t ldbb, traits::complex_f* x, const integer_t ldx,
        traits::complex_f* work, float* rwork, integer_t& info ) {
    LAPACK_CHBGST( &vect, &uplo, &n, &ka, &kb, traits::complex_ptr(ab), &ldab,
            traits::complex_ptr(bb), &ldbb, traits::complex_ptr(x), &ldx,
            traits::complex_ptr(work), rwork, &info );
}

inline void hbgst( const char vect, const char uplo, const integer_t n,
        const integer_t ka, const integer_t kb, traits::complex_d* ab,
        const integer_t ldab, const traits::complex_d* bb,
        const integer_t ldbb, traits::complex_d* x, const integer_t ldx,
        traits::complex_d* work, double* rwork, integer_t& info ) {
    LAPACK_ZHBGST( &vect, &uplo, &n, &ka, &kb, traits::complex_ptr(ab), &ldab,
            traits::complex_ptr(bb), &ldbb, traits::complex_ptr(x), &ldx,
            traits::complex_ptr(work), rwork, &info );
}

} // namespace detail

// value-type based template
template< typename ValueType >
struct hbgst_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixAB, typename MatrixBB, typename MatrixX,
            typename WORK, typename RWORK >
    static void invoke( const char vect, const integer_t n,
            const integer_t ka, const integer_t kb, MatrixAB& ab,
            const MatrixBB& bb, MatrixX& x, integer_t& info,
            detail::workspace2< WORK, RWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixAB >::value_type, typename traits::matrix_traits<
                MatrixBB >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixAB >::value_type, typename traits::matrix_traits<
                MatrixX >::value_type >::value) );
        BOOST_ASSERT( vect == 'N' || vect == 'V' );
        BOOST_ASSERT( traits::matrix_uplo_tag(a) == 'U' ||
                traits::matrix_uplo_tag(a) == 'L' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( ka >= 0 );
        BOOST_ASSERT( kb >= kb );
        BOOST_ASSERT( traits::leading_dimension(ab) >= ka+1 );
        BOOST_ASSERT( traits::leading_dimension(bb) >= kb+1 );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( n ));
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_rwork( n ));
        detail::hbgst( vect, traits::matrix_uplo_tag(a), n, ka, kb,
                traits::matrix_storage(ab), traits::leading_dimension(ab),
                traits::matrix_storage(bb), traits::leading_dimension(bb),
                traits::matrix_storage(x), traits::leading_dimension(x),
                traits::vector_storage(work.select(value_type())),
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixAB, typename MatrixBB, typename MatrixX >
    static void invoke( const char vect, const integer_t n,
            const integer_t ka, const integer_t kb, MatrixAB& ab,
            const MatrixBB& bb, MatrixX& x, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work( n ) );
        traits::detail::array< real_type > tmp_rwork( min_size_rwork( n ) );
        invoke( vect, n, ka, kb, ab, bb, x, info, workspace( tmp_work,
                tmp_rwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixAB, typename MatrixBB, typename MatrixX >
    static void invoke( const char vect, const integer_t n,
            const integer_t ka, const integer_t kb, MatrixAB& ab,
            const MatrixBB& bb, MatrixX& x, integer_t& info,
            optimal_workspace work ) {
        invoke( vect, n, ka, kb, ab, bb, x, info, minimal_workspace() );
    }

    static integer_t min_size_work( const integer_t n ) {
        return n;
    }

    static integer_t min_size_rwork( const integer_t n ) {
        return n;
    }
};


// template function to call hbgst
template< typename MatrixAB, typename MatrixBB, typename MatrixX,
        typename Workspace >
inline integer_t hbgst( const char vect, const integer_t n,
        const integer_t ka, const integer_t kb, MatrixAB& ab,
        const MatrixBB& bb, MatrixX& x, Workspace work ) {
    typedef typename traits::matrix_traits< MatrixAB >::value_type value_type;
    integer_t info(0);
    hbgst_impl< value_type >::invoke( vect, n, ka, kb, ab, bb, x, info,
            work );
    return info;
}

// template function to call hbgst, default workspace type
template< typename MatrixAB, typename MatrixBB, typename MatrixX >
inline integer_t hbgst( const char vect, const integer_t n,
        const integer_t ka, const integer_t kb, MatrixAB& ab,
        const MatrixBB& bb, MatrixX& x ) {
    typedef typename traits::matrix_traits< MatrixAB >::value_type value_type;
    integer_t info(0);
    hbgst_impl< value_type >::invoke( vect, n, ka, kb, ab, bb, x, info,
            optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
