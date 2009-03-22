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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_CGESV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_CGESV_HPP

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
    inline void cgesv( integer_t const n, integer_t const nrhs,
            traits::complex_d* a, integer_t const lda, integer_t* ipiv,
            traits::complex_d* b, integer_t const ldb, traits::complex_d* x,
            integer_t const ldx, traits::complex_d* work,
            traits::complex_f* swork, integer_t& iter, integer_t& info ) {
        LAPACK_ZCGESV( &n, &nrhs, traits::complex_ptr(a), &lda, ipiv,
                traits::complex_ptr(b), &ldb, traits::complex_ptr(x), &ldx,
                traits::complex_ptr(work), traits::complex_ptr(swork), &iter,
                &info );
    }
}

// value-type based template
template< typename ValueType >
struct cgesv_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename VectorIPIV, typename MatrixB,
            typename MatrixX, typename WORK, typename SWORK >
    static void invoke( MatrixA& a, VectorIPIV& ipiv, MatrixB& b, MatrixX& x,
            integer_t& iter, integer_t& info, detail::workspace2< WORK,
            SWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixX >::value_type >::value) );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(b) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(ipiv) >=
                traits::matrix_num_columns(a) );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::leading_dimension(x) >= std::max(1,
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( $CALL_MIN_SIZE ));
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_swork( traits::matrix_num_columns(a),
                traits::matrix_num_columns(b) ));
        detail::cgesv( traits::matrix_num_columns(a),
                traits::matrix_num_columns(b), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(ipiv),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::matrix_storage(x), traits::leading_dimension(x),
                traits::matrix_storage(work),
                traits::vector_storage(work.select(value_type())), iter,
                info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename VectorIPIV, typename MatrixB,
            typename MatrixX >
    static void invoke( MatrixA& a, VectorIPIV& ipiv, MatrixB& b, MatrixX& x,
            integer_t& iter, integer_t& info, minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        traits::detail::array< value_type > tmp_swork( min_size_swork(
                traits::matrix_num_columns(a),
                traits::matrix_num_columns(b) ) );
        invoke( a, ipiv, b, x, iter, info, workspace( tmp_work, tmp_swork ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename VectorIPIV, typename MatrixB,
            typename MatrixX >
    static void invoke( MatrixA& a, VectorIPIV& ipiv, MatrixB& b, MatrixX& x,
            integer_t& iter, integer_t& info, optimal_workspace work ) {
        invoke( a, ipiv, b, x, iter, info, minimal_workspace() );
    }

    static integer_t min_size_work( $ARGUMENTS ) {
        return n*nrhs;
    }

    static integer_t min_size_swork( integer_t const n,
            integer_t const nrhs ) {
        return n*(n+nrhs);
    }
};


// template function to call cgesv
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename Workspace >
inline integer_t cgesv( MatrixA& a, VectorIPIV& ipiv, MatrixB& b,
        MatrixX& x, integer_t& iter, Workspace work ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    cgesv_impl< value_type >::invoke( a, ipiv, b, x, iter, info, work );
    return info;
}

// template function to call cgesv, default workspace type
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX >
inline integer_t cgesv( MatrixA& a, VectorIPIV& ipiv, MatrixB& b,
        MatrixX& x, integer_t& iter ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    cgesv_impl< value_type >::invoke( a, ipiv, b, x, iter, info,
            optimal_workspace() );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
