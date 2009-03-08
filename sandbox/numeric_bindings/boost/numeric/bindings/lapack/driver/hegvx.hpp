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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_HEGVX_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_HEGVX_HPP

#include <boost/numeric/bindings/lapack/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/detail/utils.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <cassert>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void hegvx( integer_t const itype, char const jobz,
            char const range, char const uplo, integer_t const n,
            traits::complex_f* a, integer_t const lda, traits::complex_f* b,
            integer_t const ldb, float const vl, float const vu,
            integer_t const il, integer_t const iu, float const abstol,
            integer_t& m, float* w, traits::complex_f* z, integer_t const ldz,
            traits::complex_f* work, integer_t const lwork, float* rwork,
            integer_t* iwork, integer_t* ifail, integer_t& info ) {
        LAPACK_CHEGVX( &itype, &jobz, &range, &uplo, &n,
                traits::complex_ptr(a), &lda, traits::complex_ptr(b), &ldb,
                &vl, &vu, &il, &iu, &abstol, &m, w, traits::complex_ptr(z),
                &ldz, traits::complex_ptr(work), &lwork, rwork, iwork, ifail,
                &info );
    }
    inline void hegvx( integer_t const itype, char const jobz,
            char const range, char const uplo, integer_t const n,
            traits::complex_d* a, integer_t const lda, traits::complex_d* b,
            integer_t const ldb, double const vl, double const vu,
            integer_t const il, integer_t const iu, double const abstol,
            integer_t& m, double* w, traits::complex_d* z,
            integer_t const ldz, traits::complex_d* work,
            integer_t const lwork, double* rwork, integer_t* iwork,
            integer_t* ifail, integer_t& info ) {
        LAPACK_ZHEGVX( &itype, &jobz, &range, &uplo, &n,
                traits::complex_ptr(a), &lda, traits::complex_ptr(b), &ldb,
                &vl, &vu, &il, &iu, &abstol, &m, w, traits::complex_ptr(z),
                &ldz, traits::complex_ptr(work), &lwork, rwork, iwork, ifail,
                &info );
    }
}

// value-type based template
template< typename ValueType >
struct hegvx_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorW,
            typename MatrixZ, typename VectorIFAIL, typename WORK,
            typename RWORK, typename IWORK >
    static void compute( integer_t const itype, char const jobz,
            char const range, integer_t const n, MatrixA& a, MatrixB& b,
            real_type const vl, real_type const vu, integer_t const il,
            integer_t const iu, real_type const abstol, integer_t& m,
            VectorW& w, MatrixZ& z, VectorIFAIL& ifail, integer_t& info,
            detail::workspace3< WORK, RWORK, IWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixZ >::value_type >::value) );
#ifndef NDEBUG
        assert( jobz == 'N' || jobz == 'V' );
        assert( range == 'A' || range == 'V' || range == 'I' );
        assert( traits::matrix_uplo_tag(a) == 'U' ||
                traits::matrix_uplo_tag(a) == 'L' );
        assert( n >= 0 );
        assert( traits::leading_dimension(a) >= std::max(1,n) );
        assert( traits::leading_dimension(b) >= std::max(1,n) );
        assert( traits::vector_size(w) >= n );
        assert( traits::vector_size(work.select(value_type()) >=
                min_size_work( n )));
        assert( traits::vector_size(work.select(real_type()) >=
                min_size_rwork( n )));
        assert( traits::vector_size(work.select(integer_t()) >=
                min_size_iwork( n )));
#endif
        detail::hegvx( itype, jobz, range, traits::matrix_uplo_tag(a), n,
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(b), traits::leading_dimension(b), vl,
                vu, il, iu, abstol, m, traits::vector_storage(w),
                traits::matrix_storage(z), traits::leading_dimension(z),
                traits::vector_storage(work.select(value_type())),
                traits::vector_size(work.select(value_type())),
                traits::vector_storage(work.select(real_type())),
                traits::vector_storage(work.select(integer_t())),
                traits::vector_storage(ifail), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorW,
            typename MatrixZ, typename VectorIFAIL >
    static void compute( integer_t const itype, char const jobz,
            char const range, integer_t const n, MatrixA& a, MatrixB& b,
            real_type const vl, real_type const vu, integer_t const il,
            integer_t const iu, real_type const abstol, integer_t& m,
            VectorW& w, MatrixZ& z, VectorIFAIL& ifail, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work( n ) );
        traits::detail::array< real_type > tmp_rwork( min_size_rwork( n ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork( n ) );
        compute( itype, jobz, range, n, a, b, vl, vu, il, iu, abstol, m, w, z,
                ifail, info, workspace( tmp_work, tmp_rwork, tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorW,
            typename MatrixZ, typename VectorIFAIL >
    static void compute( integer_t const itype, char const jobz,
            char const range, integer_t const n, MatrixA& a, MatrixB& b,
            real_type const vl, real_type const vu, integer_t const il,
            integer_t const iu, real_type const abstol, integer_t& m,
            VectorW& w, MatrixZ& z, VectorIFAIL& ifail, integer_t& info,
            optimal_workspace work ) {
        value_type opt_size_work;
        traits::detail::array< real_type > tmp_rwork( min_size_rwork( n ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork( n ) );
        detail::hegvx( itype, jobz, range, traits::matrix_uplo_tag(a), n,
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(b), traits::leading_dimension(b), vl,
                vu, il, iu, abstol, m, traits::vector_storage(w),
                traits::matrix_storage(z), traits::leading_dimension(z),
                &opt_size_work, -1, traits::vector_storage(tmp_rwork),
                traits::vector_storage(tmp_iwork),
                traits::vector_storage(ifail), info );
        traits::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        compute( itype, jobz, range, n, a, b, vl, vu, il, iu, abstol, m, w, z,
                ifail, info, workspace( tmp_work, tmp_rwork, tmp_iwork ) );
    }

    static integer_t min_size_work( integer_t const n ) {
        return std::max( 1, 2*n );
    }

    static integer_t min_size_rwork( integer_t const n ) {
        return 7*n;
    }

    static integer_t min_size_iwork( integer_t const n ) {
        return 5*n;
    }
};


// template function to call hegvx
template< typename MatrixA, typename MatrixB, typename VectorW,
        typename MatrixZ, typename VectorIFAIL, typename Workspace >
inline integer_t hegvx( integer_t const itype, char const jobz,
        char const range, integer_t const n, MatrixA& a, MatrixB& b,
        typename traits::matrix_traits< MatrixA >::value_type const vl,
        typename traits::matrix_traits< MatrixA >::value_type const vu,
        integer_t const il, integer_t const iu,
        typename traits::matrix_traits< MatrixA >::value_type const abstol,
        integer_t& m, VectorW& w, MatrixZ& z, VectorIFAIL& ifail,
        Workspace work = optimal_workspace() ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    hegvx_impl< value_type >::compute( itype, jobz, range, n, a, b, vl,
            vu, il, iu, abstol, m, w, z, ifail, info, work );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
