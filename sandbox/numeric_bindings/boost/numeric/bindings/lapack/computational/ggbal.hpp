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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GGBAL_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GGBAL_HPP

#include <boost/assert.hpp>
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
    inline void ggbal( char const job, integer_t const n, float* a,
            integer_t const lda, float* b, integer_t const ldb,
            integer_t& ilo, integer_t& ihi, float* lscale, float* rscale,
            float* work, integer_t& info ) {
        LAPACK_SGGBAL( &job, &n, a, &lda, b, &ldb, &ilo, &ihi, lscale, rscale,
                work, &info );
    }
    inline void ggbal( char const job, integer_t const n, double* a,
            integer_t const lda, double* b, integer_t const ldb,
            integer_t& ilo, integer_t& ihi, double* lscale, double* rscale,
            double* work, integer_t& info ) {
        LAPACK_DGGBAL( &job, &n, a, &lda, b, &ldb, &ilo, &ihi, lscale, rscale,
                work, &info );
    }
    inline void ggbal( char const job, integer_t const n,
            traits::complex_f* a, integer_t const lda, traits::complex_f* b,
            integer_t const ldb, integer_t& ilo, integer_t& ihi,
            float* lscale, float* rscale, float* work, integer_t& info ) {
        LAPACK_CGGBAL( &job, &n, traits::complex_ptr(a), &lda,
                traits::complex_ptr(b), &ldb, &ilo, &ihi, lscale, rscale,
                work, &info );
    }
    inline void ggbal( char const job, integer_t const n,
            traits::complex_d* a, integer_t const lda, traits::complex_d* b,
            integer_t const ldb, integer_t& ilo, integer_t& ihi,
            double* lscale, double* rscale, double* work, integer_t& info ) {
        LAPACK_ZGGBAL( &job, &n, traits::complex_ptr(a), &lda,
                traits::complex_ptr(b), &ldb, &ilo, &ihi, lscale, rscale,
                work, &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct ggbal_impl{};

// real specialization
template< typename ValueType >
struct ggbal_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
            typename VectorRSCALE, typename WORK >
    static void compute( char const job, integer_t const n, MatrixA& a,
            MatrixB& b, integer_t& ilo, integer_t& ihi, VectorLSCALE& lscale,
            VectorRSCALE& rscale, integer_t& info, detail::workspace1<
            WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorLSCALE >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorRSCALE >::value_type >::value) );
        BOOST_ASSERT( job == 'N' || job == 'P' || job == 'S' || job == 'B' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,n) );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,n) );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( $CALL_MIN_SIZE ));
        detail::ggbal( job, n, traits::matrix_storage(a),
                traits::leading_dimension(a), traits::matrix_storage(b),
                traits::leading_dimension(b), ilo, ihi,
                traits::vector_storage(lscale),
                traits::vector_storage(rscale),
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
            typename VectorRSCALE >
    static void compute( char const job, integer_t const n, MatrixA& a,
            MatrixB& b, integer_t& ilo, integer_t& ihi, VectorLSCALE& lscale,
            VectorRSCALE& rscale, integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        compute( job, n, a, b, ilo, ihi, lscale, rscale, info,
                workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
            typename VectorRSCALE >
    static void compute( char const job, integer_t const n, MatrixA& a,
            MatrixB& b, integer_t& ilo, integer_t& ihi, VectorLSCALE& lscale,
            VectorRSCALE& rscale, integer_t& info, optimal_workspace work ) {
        compute( job, n, a, b, ilo, ihi, lscale, rscale, info,
                minimal_workspace() );
    }

    static integer_t min_size_work( $ARGUMENTS ) {
        $MIN_SIZE
    }
};

// complex specialization
template< typename ValueType >
struct ggbal_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
            typename VectorRSCALE, typename WORK >
    static void compute( char const job, integer_t const n, MatrixA& a,
            MatrixB& b, integer_t& ilo, integer_t& ihi, VectorLSCALE& lscale,
            VectorRSCALE& rscale, integer_t& info, detail::workspace1<
            WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorLSCALE >::value_type, typename traits::vector_traits<
                VectorRSCALE >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_ASSERT( job == 'N' || job == 'P' || job == 'S' || job == 'B' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,n) );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,n) );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( $CALL_MIN_SIZE ));
        detail::ggbal( job, n, traits::matrix_storage(a),
                traits::leading_dimension(a), traits::matrix_storage(b),
                traits::leading_dimension(b), ilo, ihi,
                traits::vector_storage(lscale),
                traits::vector_storage(rscale),
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
            typename VectorRSCALE >
    static void compute( char const job, integer_t const n, MatrixA& a,
            MatrixB& b, integer_t& ilo, integer_t& ihi, VectorLSCALE& lscale,
            VectorRSCALE& rscale, integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        compute( job, n, a, b, ilo, ihi, lscale, rscale, info,
                workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
            typename VectorRSCALE >
    static void compute( char const job, integer_t const n, MatrixA& a,
            MatrixB& b, integer_t& ilo, integer_t& ihi, VectorLSCALE& lscale,
            VectorRSCALE& rscale, integer_t& info, optimal_workspace work ) {
        compute( job, n, a, b, ilo, ihi, lscale, rscale, info,
                minimal_workspace() );
    }

    static integer_t min_size_work( $ARGUMENTS ) {
        $MIN_SIZE
    }
};


// template function to call ggbal
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE, typename Workspace >
inline integer_t ggbal( char const job, integer_t const n, MatrixA& a,
        MatrixB& b, integer_t& ilo, integer_t& ihi, VectorLSCALE& lscale,
        VectorRSCALE& rscale, Workspace work = optimal_workspace() ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    ggbal_impl< value_type >::compute( job, n, a, b, ilo, ihi, lscale,
            rscale, info, work );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
