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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_SYEVR_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_SYEVR_HPP

#include <boost/numeric/bindings/lapack/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/detail/utils.hpp>
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
    inline void syevr( char const jobz, char const range, char const uplo,
            integer_t const n, float* a, integer_t const lda, float const vl,
            float const vu, integer_t const il, integer_t const iu,
            float const abstol, integer_t& m, float* w, float* z,
            integer_t const ldz, integer_t* isuppz, float* work,
            integer_t const lwork, integer_t* iwork, integer_t const liwork,
            integer_t& info ) {
        LAPACK_SSYEVR( &jobz, &range, &uplo, &n, a, &lda, &vl, &vu, &il, &iu,
                &abstol, &m, w, z, &ldz, isuppz, work, &lwork, iwork, &liwork,
                &info );
    }
    inline void syevr( char const jobz, char const range, char const uplo,
            integer_t const n, double* a, integer_t const lda,
            double const vl, double const vu, integer_t const il,
            integer_t const iu, double const abstol, integer_t& m, double* w,
            double* z, integer_t const ldz, integer_t* isuppz, double* work,
            integer_t const lwork, integer_t* iwork, integer_t const liwork,
            integer_t& info ) {
        LAPACK_DSYEVR( &jobz, &range, &uplo, &n, a, &lda, &vl, &vu, &il, &iu,
                &abstol, &m, w, z, &ldz, isuppz, work, &lwork, iwork, &liwork,
                &info );
    }
}

// value-type based template
template< typename ValueType >
struct syevr_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename VectorW, typename MatrixZ,
            typename VectorISUPPZ, typename WORK, typename IWORK >
    static void compute( char const jobz, char const range, MatrixA& a,
            real_type const vl, real_type const vu, integer_t const il,
            integer_t const iu, real_type const abstol, integer_t& m,
            VectorW& w, MatrixZ& z, VectorISUPPZ& isuppz, integer_t& info,
            detail::workspace2< WORK, IWORK > work ) {
#ifndef NDEBUG
        assert( jobz == 'N' || jobz == 'V' );
        assert( range == 'A' || range == 'V' || range == 'I' );
        assert( traits::matrix_uplo_tag(a) == 'U' ||
                traits::matrix_uplo_tag(a) == 'L' );
        assert( traits::matrix_size2(a) >= 0 );
        assert( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_size2(a)) );
        assert( traits::vector_size(w) >= traits::matrix_size2(a) );
        assert( traits::vector_size(isuppz) >= 2*std::max(1,m) );
        assert( traits::vector_size(work.select(real_type()) >= min_size_work(
                traits::matrix_size2(a) )));
        assert( traits::vector_size(work.select(integer_t()) >=
                min_size_iwork( traits::matrix_size2(a) )));
#endif
        detail::syevr( jobz, range, traits::matrix_uplo_tag(a),
                traits::matrix_size2(a), traits::matrix_storage(a),
                traits::leading_dimension(a), vl, vu, il, iu, abstol, m,
                traits::vector_storage(w), traits::matrix_storage(z),
                traits::leading_dimension(z), traits::vector_storage(isuppz),
                traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())),
                traits::vector_storage(work.select(integer_t())),
                traits::vector_size(work.select(integer_t())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename VectorW, typename MatrixZ,
            typename VectorISUPPZ >
    static void compute( char const jobz, char const range, MatrixA& a,
            real_type const vl, real_type const vu, integer_t const il,
            integer_t const iu, real_type const abstol, integer_t& m,
            VectorW& w, MatrixZ& z, VectorISUPPZ& isuppz, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work(
                traits::matrix_size2(a) ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork(
                traits::matrix_size2(a) ) );
        compute( jobz, range, a, vl, vu, il, iu, abstol, m, w, z, isuppz,
                info, workspace( tmp_work, tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename VectorW, typename MatrixZ,
            typename VectorISUPPZ >
    static void compute( char const jobz, char const range, MatrixA& a,
            real_type const vl, real_type const vu, integer_t const il,
            integer_t const iu, real_type const abstol, integer_t& m,
            VectorW& w, MatrixZ& z, VectorISUPPZ& isuppz, integer_t& info,
            optimal_workspace work ) {
        real_type opt_size_work;
        integer_t opt_size_iwork;
        detail::syevr( jobz, range, traits::matrix_uplo_tag(a),
                traits::matrix_size2(a), traits::matrix_storage(a),
                traits::leading_dimension(a), vl, vu, il, iu, abstol, m,
                traits::vector_storage(w), traits::matrix_storage(z),
                traits::leading_dimension(z), traits::vector_storage(isuppz),
                &opt_size_work, -1, &opt_size_iwork, -1, info );
        traits::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        traits::detail::array< integer_t > tmp_iwork( opt_size_iwork );
        compute( jobz, range, a, vl, vu, il, iu, abstol, m, w, z, isuppz,
                info, workspace( tmp_work, tmp_iwork ) );
    }

    static integer_t min_size_work( integer_t const n ) {
        return std::max( 1, 26*n );
    }

    static integer_t min_size_iwork( integer_t const n ) {
        return std::max( 1, 10*n );
    }
};


// template function to call syevr
template< typename MatrixA, typename VectorW, typename MatrixZ,
        typename VectorISUPPZ, typename Workspace >
inline integer_t syevr( char const jobz, char const range, MatrixA& a,
        typename traits::matrix_traits< MatrixA >::value_type const vl,
        typename traits::matrix_traits< MatrixA >::value_type const vu,
        integer_t const il, integer_t const iu,
        typename traits::matrix_traits< MatrixA >::value_type const abstol,
        integer_t& m, VectorW& w, MatrixZ& z, VectorISUPPZ& isuppz,
        Workspace work = optimal_workspace() ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    syevr_impl< value_type >::compute( jobz, range, a, vl, vu, il, iu,
            abstol, m, w, z, isuppz, info, work );
    return info;
}


}}}} // namespace boost::numeric::bindings::lapack

#endif
