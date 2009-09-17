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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_PBCON_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_PBCON_HPP

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
    inline void pbcon( const char uplo, const integer_t n, const integer_t kd,
            const float* ab, const integer_t ldab, const float anorm,
            float& rcond, float* work, integer_t* iwork, integer_t& info ) {
        LAPACK_SPBCON( &uplo, &n, &kd, ab, &ldab, &anorm, &rcond, work, iwork,
                &info );
    }
    inline void pbcon( const char uplo, const integer_t n, const integer_t kd,
            const double* ab, const integer_t ldab, const double anorm,
            double& rcond, double* work, integer_t* iwork, integer_t& info ) {
        LAPACK_DPBCON( &uplo, &n, &kd, ab, &ldab, &anorm, &rcond, work, iwork,
                &info );
    }
    inline void pbcon( const char uplo, const integer_t n, const integer_t kd,
            const traits::complex_f* ab, const integer_t ldab,
            const float anorm, float& rcond, traits::complex_f* work,
            float* rwork, integer_t& info ) {
        LAPACK_CPBCON( &uplo, &n, &kd, traits::complex_ptr(ab), &ldab, &anorm,
                &rcond, traits::complex_ptr(work), rwork, &info );
    }
    inline void pbcon( const char uplo, const integer_t n, const integer_t kd,
            const traits::complex_d* ab, const integer_t ldab,
            const double anorm, double& rcond, traits::complex_d* work,
            double* rwork, integer_t& info ) {
        LAPACK_ZPBCON( &uplo, &n, &kd, traits::complex_ptr(ab), &ldab, &anorm,
                &rcond, traits::complex_ptr(work), rwork, &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct pbcon_impl{};

// real specialization
template< typename ValueType >
struct pbcon_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixAB, typename WORK, typename IWORK >
    static void invoke( const char uplo, const integer_t n,
            const integer_t kd, const MatrixAB& ab, const real_type anorm,
            real_type& rcond, integer_t& info, detail::workspace2< WORK,
            IWORK > work ) {
        BOOST_ASSERT( uplo == 'U' || uplo == 'L' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( kd >= 0 );
        BOOST_ASSERT( traits::leading_dimension(ab) >= kd+1 );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( n ));
        BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
                min_size_iwork( n ));
        detail::pbcon( uplo, n, kd, traits::matrix_storage(ab),
                traits::leading_dimension(ab), anorm, rcond,
                traits::vector_storage(work.select(real_type())),
                traits::vector_storage(work.select(integer_t())), info );
    }

    // minimal workspace specialization
    template< typename MatrixAB >
    static void invoke( const char uplo, const integer_t n,
            const integer_t kd, const MatrixAB& ab, const real_type anorm,
            real_type& rcond, integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work( n ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork( n ) );
        invoke( uplo, n, kd, ab, anorm, rcond, info, workspace( tmp_work,
                tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixAB >
    static void invoke( const char uplo, const integer_t n,
            const integer_t kd, const MatrixAB& ab, const real_type anorm,
            real_type& rcond, integer_t& info, optimal_workspace work ) {
        invoke( uplo, n, kd, ab, anorm, rcond, info, minimal_workspace() );
    }

    static integer_t min_size_work( const integer_t n ) {
        return 3*n;
    }

    static integer_t min_size_iwork( const integer_t n ) {
        return n;
    }
};

// complex specialization
template< typename ValueType >
struct pbcon_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixAB, typename WORK, typename RWORK >
    static void invoke( const char uplo, const integer_t n,
            const integer_t kd, const MatrixAB& ab, const real_type anorm,
            real_type& rcond, integer_t& info, detail::workspace2< WORK,
            RWORK > work ) {
        BOOST_ASSERT( uplo == 'U' || uplo == 'L' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( kd >= 0 );
        BOOST_ASSERT( traits::leading_dimension(ab) >= kd+1 );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( n ));
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_rwork( n ));
        detail::pbcon( uplo, n, kd, traits::matrix_storage(ab),
                traits::leading_dimension(ab), anorm, rcond,
                traits::vector_storage(work.select(value_type())),
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixAB >
    static void invoke( const char uplo, const integer_t n,
            const integer_t kd, const MatrixAB& ab, const real_type anorm,
            real_type& rcond, integer_t& info, minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work( n ) );
        traits::detail::array< real_type > tmp_rwork( min_size_rwork( n ) );
        invoke( uplo, n, kd, ab, anorm, rcond, info, workspace( tmp_work,
                tmp_rwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixAB >
    static void invoke( const char uplo, const integer_t n,
            const integer_t kd, const MatrixAB& ab, const real_type anorm,
            real_type& rcond, integer_t& info, optimal_workspace work ) {
        invoke( uplo, n, kd, ab, anorm, rcond, info, minimal_workspace() );
    }

    static integer_t min_size_work( const integer_t n ) {
        return 2*n;
    }

    static integer_t min_size_rwork( const integer_t n ) {
        return n;
    }
};


// template function to call pbcon
template< typename MatrixAB, typename Workspace >
inline integer_t pbcon( const char uplo, const integer_t n,
        const integer_t kd, const MatrixAB& ab,
        const typename traits::type_traits< typename traits::matrix_traits<
        MatrixAB >::value_type >::real_type anorm,
        typename traits::type_traits< typename traits::matrix_traits<
        MatrixAB >::value_type >::real_type& rcond, Workspace work ) {
    typedef typename traits::matrix_traits< MatrixAB >::value_type value_type;
    integer_t info(0);
    pbcon_impl< value_type >::invoke( uplo, n, kd, ab, anorm, rcond,
            info, work );
    return info;
}

// template function to call pbcon, default workspace type
template< typename MatrixAB >
inline integer_t pbcon( const char uplo, const integer_t n,
        const integer_t kd, const MatrixAB& ab,
        const typename traits::type_traits< typename traits::matrix_traits<
        MatrixAB >::value_type >::real_type anorm,
        typename traits::type_traits< typename traits::matrix_traits<
        MatrixAB >::value_type >::real_type& rcond ) {
    typedef typename traits::matrix_traits< MatrixAB >::value_type value_type;
    integer_t info(0);
    pbcon_impl< value_type >::invoke( uplo, n, kd, ab, anorm, rcond,
            info, optimal_workspace() );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
