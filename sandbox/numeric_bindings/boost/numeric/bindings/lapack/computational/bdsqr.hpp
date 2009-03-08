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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_BDSQR_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_BDSQR_HPP

#include <boost/numeric/bindings/lapack/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/is_complex.hpp>
#include <boost/numeric/bindings/traits/is_real.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <cassert>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void bdsqr( char const uplo, integer_t const n,
            integer_t const ncvt, integer_t const nru, integer_t const ncc,
            float* d, float* e, float* vt, integer_t const ldvt, float* u,
            integer_t const ldu, float* c, integer_t const ldc, float* work,
            integer_t& info ) {
        LAPACK_SBDSQR( &uplo, &n, &ncvt, &nru, &ncc, d, e, vt, &ldvt, u, &ldu,
                c, &ldc, work, &info );
    }
    inline void bdsqr( char const uplo, integer_t const n,
            integer_t const ncvt, integer_t const nru, integer_t const ncc,
            double* d, double* e, double* vt, integer_t const ldvt, double* u,
            integer_t const ldu, double* c, integer_t const ldc, double* work,
            integer_t& info ) {
        LAPACK_DBDSQR( &uplo, &n, &ncvt, &nru, &ncc, d, e, vt, &ldvt, u, &ldu,
                c, &ldc, work, &info );
    }
    inline void bdsqr( char const uplo, integer_t const n,
            integer_t const ncvt, integer_t const nru, integer_t const ncc,
            float* d, float* e, traits::complex_f* vt, integer_t const ldvt,
            traits::complex_f* u, integer_t const ldu, traits::complex_f* c,
            integer_t const ldc, float* rwork, integer_t& info ) {
        LAPACK_CBDSQR( &uplo, &n, &ncvt, &nru, &ncc, d, e,
                traits::complex_ptr(vt), &ldvt, traits::complex_ptr(u), &ldu,
                traits::complex_ptr(c), &ldc, rwork, &info );
    }
    inline void bdsqr( char const uplo, integer_t const n,
            integer_t const ncvt, integer_t const nru, integer_t const ncc,
            double* d, double* e, traits::complex_d* vt, integer_t const ldvt,
            traits::complex_d* u, integer_t const ldu, traits::complex_d* c,
            integer_t const ldc, double* rwork, integer_t& info ) {
        LAPACK_ZBDSQR( &uplo, &n, &ncvt, &nru, &ncc, d, e,
                traits::complex_ptr(vt), &ldvt, traits::complex_ptr(u), &ldu,
                traits::complex_ptr(c), &ldc, rwork, &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct bdsqr_impl{};

// real specialization
template< typename ValueType >
struct bdsqr_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename VectorD, typename VectorE, typename MatrixVT,
            typename MatrixU, typename MatrixC, typename WORK >
    static void compute( char const uplo, integer_t const n, VectorD& d,
            VectorE& e, MatrixVT& vt, MatrixU& u, MatrixC& c, integer_t& info,
            detail::workspace1< WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::vector_traits<
                VectorE >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::matrix_traits<
                MatrixVT >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::matrix_traits<
                MatrixU >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::matrix_traits<
                MatrixC >::value_type >::value) );
#ifndef NDEBUG
        assert( uplo == 'U' || uplo == 'L' );
        assert( n >= 0 );
        assert( traits::matrix_num_columns(vt) >= 0 );
        assert( traits::matrix_num_rows(u) >= 0 );
        assert( traits::matrix_num_columns(c) >= 0 );
        assert( traits::leading_dimension(u) >= std::max(1,
                traits::matrix_num_rows(u)) );
        assert( traits::vector_size(work.select(real_type())) >=
                min_size_work( n, traits::matrix_num_columns(vt),
                traits::matrix_num_rows(u), traits::matrix_num_columns(c) ));
#endif
        detail::bdsqr( uplo, n, traits::matrix_num_columns(vt),
                traits::matrix_num_rows(u), traits::matrix_num_columns(c),
                traits::vector_storage(d), traits::vector_storage(e),
                traits::matrix_storage(vt), traits::leading_dimension(vt),
                traits::matrix_storage(u), traits::leading_dimension(u),
                traits::matrix_storage(c), traits::leading_dimension(c),
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename VectorD, typename VectorE, typename MatrixVT,
            typename MatrixU, typename MatrixC >
    static void compute( char const uplo, integer_t const n, VectorD& d,
            VectorE& e, MatrixVT& vt, MatrixU& u, MatrixC& c, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work( n,
                traits::matrix_num_columns(vt), traits::matrix_num_rows(u),
                traits::matrix_num_columns(c) ) );
        compute( uplo, n, d, e, vt, u, c, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename VectorD, typename VectorE, typename MatrixVT,
            typename MatrixU, typename MatrixC >
    static void compute( char const uplo, integer_t const n, VectorD& d,
            VectorE& e, MatrixVT& vt, MatrixU& u, MatrixC& c, integer_t& info,
            optimal_workspace work ) {
        compute( uplo, n, d, e, vt, u, c, info, minimal_workspace() );
    }

    static integer_t min_size_work( integer_t const n, integer_t const ncvt,
            integer_t const nru, integer_t const ncc ) {
        if ( ncvt == 0 && nru == 0 && ncc == 0 )
            return 2*n;
        else
            return std::max(1, 4*n);
    }
};

// complex specialization
template< typename ValueType >
struct bdsqr_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename VectorD, typename VectorE, typename MatrixVT,
            typename MatrixU, typename MatrixC, typename RWORK >
    static void compute( char const uplo, integer_t const n, VectorD& d,
            VectorE& e, MatrixVT& vt, MatrixU& u, MatrixC& c, integer_t& info,
            detail::workspace1< RWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::vector_traits<
                VectorE >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixVT >::value_type, typename traits::matrix_traits<
                MatrixU >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixVT >::value_type, typename traits::matrix_traits<
                MatrixC >::value_type >::value) );
#ifndef NDEBUG
        assert( uplo == 'U' || uplo == 'L' );
        assert( n >= 0 );
        assert( traits::matrix_num_columns(vt) >= 0 );
        assert( traits::matrix_num_rows(u) >= 0 );
        assert( traits::matrix_num_columns(c) >= 0 );
        assert( traits::leading_dimension(u) >= std::max(1,
                traits::matrix_num_rows(u)) );
        assert( traits::vector_size(work.select(real_type())) >=
                min_size_rwork( n, traits::matrix_num_columns(vt),
                traits::matrix_num_rows(u), traits::matrix_num_columns(c) ));
#endif
        detail::bdsqr( uplo, n, traits::matrix_num_columns(vt),
                traits::matrix_num_rows(u), traits::matrix_num_columns(c),
                traits::vector_storage(d), traits::vector_storage(e),
                traits::matrix_storage(vt), traits::leading_dimension(vt),
                traits::matrix_storage(u), traits::leading_dimension(u),
                traits::matrix_storage(c), traits::leading_dimension(c),
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename VectorD, typename VectorE, typename MatrixVT,
            typename MatrixU, typename MatrixC >
    static void compute( char const uplo, integer_t const n, VectorD& d,
            VectorE& e, MatrixVT& vt, MatrixU& u, MatrixC& c, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< real_type > tmp_rwork( min_size_rwork( n,
                traits::matrix_num_columns(vt), traits::matrix_num_rows(u),
                traits::matrix_num_columns(c) ) );
        compute( uplo, n, d, e, vt, u, c, info, workspace( tmp_rwork ) );
    }

    // optimal workspace specialization
    template< typename VectorD, typename VectorE, typename MatrixVT,
            typename MatrixU, typename MatrixC >
    static void compute( char const uplo, integer_t const n, VectorD& d,
            VectorE& e, MatrixVT& vt, MatrixU& u, MatrixC& c, integer_t& info,
            optimal_workspace work ) {
        compute( uplo, n, d, e, vt, u, c, info, minimal_workspace() );
    }

    static integer_t min_size_rwork( integer_t const n, integer_t const ncvt,
            integer_t const nru, integer_t const ncc ) {
        if ( ncvt == 0 && nru == 0 && ncc == 0 )
            return 2*n;
        else
            return std::max(1, 4*n-4);
    }
};


// template function to call bdsqr
template< typename VectorD, typename VectorE, typename MatrixVT,
        typename MatrixU, typename MatrixC, typename Workspace >
inline integer_t bdsqr( char const uplo, integer_t const n, VectorD& d,
        VectorE& e, MatrixVT& vt, MatrixU& u, MatrixC& c,
        Workspace work = optimal_workspace() ) {
    typedef typename traits::vector_traits< VectorD >::value_type value_type;
    integer_t info(0);
    bdsqr_impl< value_type >::compute( uplo, n, d, e, vt, u, c, info,
            work );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
