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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_HEEVR_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_HEEVR_HPP

#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
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

inline void heevr( const char jobz, const char range, const char uplo,
        const integer_t n, traits::complex_f* a, const integer_t lda,
        const float vl, const float vu, const integer_t il,
        const integer_t iu, const float abstol, integer_t& m, float* w,
        traits::complex_f* z, const integer_t ldz, integer_t* isuppz,
        traits::complex_f* work, const integer_t lwork, float* rwork,
        const integer_t lrwork, integer_t* iwork, const integer_t liwork,
        integer_t& info ) {
    LAPACK_CHEEVR( &jobz, &range, &uplo, &n, traits::complex_ptr(a), &lda,
            &vl, &vu, &il, &iu, &abstol, &m, w, traits::complex_ptr(z), &ldz,
            isuppz, traits::complex_ptr(work), &lwork, rwork, &lrwork, iwork,
            &liwork, &info );
}
inline void heevr( const char jobz, const char range, const char uplo,
        const integer_t n, traits::complex_d* a, const integer_t lda,
        const double vl, const double vu, const integer_t il,
        const integer_t iu, const double abstol, integer_t& m, double* w,
        traits::complex_d* z, const integer_t ldz, integer_t* isuppz,
        traits::complex_d* work, const integer_t lwork, double* rwork,
        const integer_t lrwork, integer_t* iwork, const integer_t liwork,
        integer_t& info ) {
    LAPACK_ZHEEVR( &jobz, &range, &uplo, &n, traits::complex_ptr(a), &lda,
            &vl, &vu, &il, &iu, &abstol, &m, w, traits::complex_ptr(z), &ldz,
            isuppz, traits::complex_ptr(work), &lwork, rwork, &lrwork, iwork,
            &liwork, &info );
}
} // namespace detail

// value-type based template
template< typename ValueType >
struct heevr_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename VectorW, typename MatrixZ,
            typename VectorISUPPZ, typename WORK, typename RWORK,
            typename IWORK >
    static void invoke( const char jobz, const char range, MatrixA& a,
            const real_type vl, const real_type vu, const integer_t il,
            const integer_t iu, const real_type abstol, integer_t& m,
            VectorW& w, MatrixZ& z, VectorISUPPZ& isuppz, integer_t& info,
            detail::workspace3< WORK, RWORK, IWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixZ >::value_type >::value) );
        BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
        BOOST_ASSERT( range == 'A' || range == 'V' || range == 'I' );
        BOOST_ASSERT( traits::matrix_uplo_tag(a) == 'U' ||
                traits::matrix_uplo_tag(a) == 'L' );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max<
                std::ptrdiff_t >(1,traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(w) >=
                traits::matrix_num_columns(a) );
        BOOST_ASSERT( traits::vector_size(isuppz) >= 2*std::max<
                std::ptrdiff_t >(1,m) );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( traits::matrix_num_columns(a) ));
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_rwork( traits::matrix_num_columns(a) ));
        BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
                min_size_iwork( traits::matrix_num_columns(a) ));
        detail::heevr( jobz, range, traits::matrix_uplo_tag(a),
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), vl, vu, il, iu, abstol, m,
                traits::vector_storage(w), traits::matrix_storage(z),
                traits::leading_dimension(z), traits::vector_storage(isuppz),
                traits::vector_storage(work.select(value_type())),
                traits::vector_size(work.select(value_type())),
                traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())),
                traits::vector_storage(work.select(integer_t())),
                traits::vector_size(work.select(integer_t())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename VectorW, typename MatrixZ,
            typename VectorISUPPZ >
    static void invoke( const char jobz, const char range, MatrixA& a,
            const real_type vl, const real_type vu, const integer_t il,
            const integer_t iu, const real_type abstol, integer_t& m,
            VectorW& w, MatrixZ& z, VectorISUPPZ& isuppz, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work(
                traits::matrix_num_columns(a) ) );
        traits::detail::array< real_type > tmp_rwork( min_size_rwork(
                traits::matrix_num_columns(a) ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork(
                traits::matrix_num_columns(a) ) );
        invoke( jobz, range, a, vl, vu, il, iu, abstol, m, w, z, isuppz, info,
                workspace( tmp_work, tmp_rwork, tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename VectorW, typename MatrixZ,
            typename VectorISUPPZ >
    static void invoke( const char jobz, const char range, MatrixA& a,
            const real_type vl, const real_type vu, const integer_t il,
            const integer_t iu, const real_type abstol, integer_t& m,
            VectorW& w, MatrixZ& z, VectorISUPPZ& isuppz, integer_t& info,
            optimal_workspace work ) {
        value_type opt_size_work;
        real_type opt_size_rwork;
        integer_t opt_size_iwork;
        detail::heevr( jobz, range, traits::matrix_uplo_tag(a),
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), vl, vu, il, iu, abstol, m,
                traits::vector_storage(w), traits::matrix_storage(z),
                traits::leading_dimension(z), traits::vector_storage(isuppz),
                &opt_size_work, -1, &opt_size_rwork, -1, &opt_size_iwork, -1,
                info );
        traits::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        traits::detail::array< real_type > tmp_rwork(
                traits::detail::to_int( opt_size_rwork ) );
        traits::detail::array< integer_t > tmp_iwork( opt_size_iwork );
        invoke( jobz, range, a, vl, vu, il, iu, abstol, m, w, z, isuppz, info,
                workspace( tmp_work, tmp_rwork, tmp_iwork ) );
    }

    static integer_t min_size_work( const integer_t n ) {
        return std::max( 1, 2*n );
    }

    static integer_t min_size_rwork( const integer_t n ) {
        return std::max( 1, 24*n );
    }

    static integer_t min_size_iwork( const integer_t n ) {
        return std::max( 1, 10*n );
    }
};


// template function to call heevr
template< typename MatrixA, typename VectorW, typename MatrixZ,
        typename VectorISUPPZ, typename Workspace >
inline integer_t heevr( const char jobz, const char range, MatrixA& a,
        const typename traits::type_traits< typename traits::matrix_traits<
        MatrixA >::value_type >::real_type vl,
        const typename traits::type_traits< typename traits::matrix_traits<
        MatrixA >::value_type >::real_type vu, const integer_t il,
        const integer_t iu, const typename traits::type_traits<
        typename traits::matrix_traits<
        MatrixA >::value_type >::real_type abstol, integer_t& m, VectorW& w,
        MatrixZ& z, VectorISUPPZ& isuppz, Workspace work ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    heevr_impl< value_type >::invoke( jobz, range, a, vl, vu, il, iu,
            abstol, m, w, z, isuppz, info, work );
    return info;
}

// template function to call heevr, default workspace type
template< typename MatrixA, typename VectorW, typename MatrixZ,
        typename VectorISUPPZ >
inline integer_t heevr( const char jobz, const char range, MatrixA& a,
        const typename traits::type_traits< typename traits::matrix_traits<
        MatrixA >::value_type >::real_type vl,
        const typename traits::type_traits< typename traits::matrix_traits<
        MatrixA >::value_type >::real_type vu, const integer_t il,
        const integer_t iu, const typename traits::type_traits<
        typename traits::matrix_traits<
        MatrixA >::value_type >::real_type abstol, integer_t& m, VectorW& w,
        MatrixZ& z, VectorISUPPZ& isuppz ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    heevr_impl< value_type >::invoke( jobz, range, a, vl, vu, il, iu,
            abstol, m, w, z, isuppz, info, optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
