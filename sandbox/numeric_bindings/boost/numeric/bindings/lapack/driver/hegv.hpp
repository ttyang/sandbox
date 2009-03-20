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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_HEGV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_HEGV_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/detail/utils.hpp>
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
    inline void hegv( integer_t const itype, char const jobz, char const uplo,
            integer_t const n, traits::complex_f* a, integer_t const lda,
            traits::complex_f* b, integer_t const ldb, float* w,
            traits::complex_f* work, integer_t const lwork, float* rwork,
            integer_t& info ) {
        LAPACK_CHEGV( &itype, &jobz, &uplo, &n, traits::complex_ptr(a), &lda,
                traits::complex_ptr(b), &ldb, w, traits::complex_ptr(work),
                &lwork, rwork, &info );
    }
    inline void hegv( integer_t const itype, char const jobz, char const uplo,
            integer_t const n, traits::complex_d* a, integer_t const lda,
            traits::complex_d* b, integer_t const ldb, double* w,
            traits::complex_d* work, integer_t const lwork, double* rwork,
            integer_t& info ) {
        LAPACK_ZHEGV( &itype, &jobz, &uplo, &n, traits::complex_ptr(a), &lda,
                traits::complex_ptr(b), &ldb, w, traits::complex_ptr(work),
                &lwork, rwork, &info );
    }
}

// value-type based template
template< typename ValueType >
struct hegv_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorW,
            typename WORK, typename RWORK >
    static void invoke( integer_t const itype, char const jobz,
            integer_t const n, MatrixA& a, MatrixB& b, VectorW& w,
            integer_t& info, detail::workspace2< WORK, RWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
        BOOST_ASSERT( traits::matrix_uplo_tag(a) == 'U' ||
                traits::matrix_uplo_tag(a) == 'L' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,n) );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,n) );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( n ));
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_rwork( n ));
        detail::hegv( itype, jobz, traits::matrix_uplo_tag(a), n,
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::vector_storage(w),
                traits::vector_storage(work.select(value_type())),
                traits::vector_size(work.select(value_type())),
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorW >
    static void invoke( integer_t const itype, char const jobz,
            integer_t const n, MatrixA& a, MatrixB& b, VectorW& w,
            integer_t& info, minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work( n ) );
        traits::detail::array< real_type > tmp_rwork( min_size_rwork( n ) );
        invoke( itype, jobz, n, a, b, w, info, workspace( tmp_work,
                tmp_rwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorW >
    static void invoke( integer_t const itype, char const jobz,
            integer_t const n, MatrixA& a, MatrixB& b, VectorW& w,
            integer_t& info, optimal_workspace work ) {
        value_type opt_size_work;
        traits::detail::array< real_type > tmp_rwork( min_size_rwork( n ) );
        detail::hegv( itype, jobz, traits::matrix_uplo_tag(a), n,
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::vector_storage(w), &opt_size_work, -1,
                traits::vector_storage(tmp_rwork), info );
        traits::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        invoke( itype, jobz, n, a, b, w, info, workspace( tmp_work,
                tmp_rwork ) );
    }

    static integer_t min_size_work( integer_t const n ) {
        return std::max( 1, 2*n-1 );
    }

    static integer_t min_size_rwork( integer_t const n ) {
        return std::max( 1, 3*n-2 );
    }
};


// template function to call hegv
template< typename MatrixA, typename MatrixB, typename VectorW,
        typename Workspace >
inline integer_t hegv( integer_t const itype, char const jobz,
        integer_t const n, MatrixA& a, MatrixB& b, VectorW& w,
        Workspace work ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    hegv_impl< value_type >::invoke( itype, jobz, n, a, b, w, info,
            work );
    return info;
}

// template function to call hegv, default workspace type
template< typename MatrixA, typename MatrixB, typename VectorW >
inline integer_t hegv( integer_t const itype, char const jobz,
        integer_t const n, MatrixA& a, MatrixB& b, VectorW& w ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    hegv_impl< value_type >::invoke( itype, jobz, n, a, b, w, info,
            optimal_workspace() );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
