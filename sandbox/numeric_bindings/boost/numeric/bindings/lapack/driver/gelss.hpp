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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_GELSS_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_GELSS_HPP

#include <boost/numeric/bindings/lapack/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/detail/utils.hpp>
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
    inline void gelss( integer_t const m, integer_t const n,
            integer_t const nrhs, float* a, integer_t const lda, float* b,
            integer_t const ldb, float* s, float const rcond, integer_t& rank,
            float* work, integer_t const lwork, integer_t& info ) {
        LAPACK_SGELSS( &m, &n, &nrhs, a, &lda, b, &ldb, s, &rcond, &rank,
                work, &lwork, &info );
    }
    inline void gelss( integer_t const m, integer_t const n,
            integer_t const nrhs, double* a, integer_t const lda, double* b,
            integer_t const ldb, double* s, double const rcond,
            integer_t& rank, double* work, integer_t const lwork,
            integer_t& info ) {
        LAPACK_DGELSS( &m, &n, &nrhs, a, &lda, b, &ldb, s, &rcond, &rank,
                work, &lwork, &info );
    }
    inline void gelss( integer_t const m, integer_t const n,
            integer_t const nrhs, traits::complex_f* a, integer_t const lda,
            traits::complex_f* b, integer_t const ldb, float* s,
            float const rcond, integer_t& rank, traits::complex_f* work,
            integer_t const lwork, float* rwork, integer_t& info ) {
        LAPACK_CGELSS( &m, &n, &nrhs, traits::complex_ptr(a), &lda,
                traits::complex_ptr(b), &ldb, s, &rcond, &rank,
                traits::complex_ptr(work), &lwork, rwork, &info );
    }
    inline void gelss( integer_t const m, integer_t const n,
            integer_t const nrhs, traits::complex_d* a, integer_t const lda,
            traits::complex_d* b, integer_t const ldb, double* s,
            double const rcond, integer_t& rank, traits::complex_d* work,
            integer_t const lwork, double* rwork, integer_t& info ) {
        LAPACK_ZGELSS( &m, &n, &nrhs, traits::complex_ptr(a), &lda,
                traits::complex_ptr(b), &ldb, s, &rcond, &rank,
                traits::complex_ptr(work), &lwork, rwork, &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct gelss_impl{};

// real specialization
template< typename ValueType >
struct gelss_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorS,
            typename WORK >
    static void compute( MatrixA& a, MatrixB& b, VectorS& s,
            real_type const rcond, integer_t& rank, integer_t& info,
            detail::workspace1< WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorS >::value_type >::value) );
#ifndef NDEBUG
        assert( traits::matrix_size1(a) >= 0 );
        assert( traits::matrix_size2(a) >= 0 );
        assert( traits::matrix_size2(b) >= 0 );
        assert( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_size1(a)) );
        assert( traits::leading_dimension(b) >= std::max(1,
                std::max(traits::matrix_size1(a),traits::matrix_size2(a))) );
        assert( traits::vector_size(s) >= std::min(traits::matrix_size1(a),
                traits::matrix_size2(a)) );
        assert( traits::vector_size(work.select(real_type()) >= min_size_work(
                traits::matrix_size1(a), traits::matrix_size2(a),
                traits::matrix_size2(b) )));
#endif
        detail::gelss( traits::matrix_size1(a), traits::matrix_size2(a),
                traits::matrix_size2(b), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::matrix_storage(b),
                traits::leading_dimension(b), traits::vector_storage(s),
                rcond, rank, traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorS >
    static void compute( MatrixA& a, MatrixB& b, VectorS& s,
            real_type const rcond, integer_t& rank, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work(
                traits::matrix_size1(a), traits::matrix_size2(a),
                traits::matrix_size2(b) ) );
        compute( a, b, s, rcond, rank, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorS >
    static void compute( MatrixA& a, MatrixB& b, VectorS& s,
            real_type const rcond, integer_t& rank, integer_t& info,
            optimal_workspace work ) {
        real_type opt_size_work;
        detail::gelss( traits::matrix_size1(a), traits::matrix_size2(a),
                traits::matrix_size2(b), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::matrix_storage(b),
                traits::leading_dimension(b), traits::vector_storage(s),
                rcond, rank, &opt_size_work, -1, info );
        traits::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        compute( a, b, s, rcond, rank, info, workspace( tmp_work ) );
    }

    static integer_t min_size_work( integer_t const m, integer_t const n,
            integer_t const nrhs ) {
        integer_t minmn = std::min( m, n );
        return std::max( 1, 3*minmn + std::max( std::max( 2*minmn, std::max(m,
                n) ), nrhs ) );
    }
};

// complex specialization
template< typename ValueType >
struct gelss_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorS,
            typename WORK, typename RWORK >
    static void compute( MatrixA& a, MatrixB& b, VectorS& s,
            real_type const rcond, integer_t& rank, integer_t& info,
            detail::workspace2< WORK, RWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        integer_t minmn = std::min( traits::matrix_size1(a),
                traits::matrix_size2(a) );
#ifndef NDEBUG
        assert( traits::matrix_size1(a) >= 0 );
        assert( traits::matrix_size2(a) >= 0 );
        assert( traits::matrix_size2(b) >= 0 );
        assert( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_size1(a)) );
        assert( traits::leading_dimension(b) >= std::max(1,
                std::max(traits::matrix_size1(a),traits::matrix_size2(a))) );
        assert( traits::vector_size(s) >= std::min(traits::matrix_size1(a),
                traits::matrix_size2(a)) );
        assert( traits::vector_size(work.select(value_type()) >=
                min_size_work( traits::matrix_size1(a),
                traits::matrix_size2(a), traits::matrix_size2(b), minmn )));
        assert( traits::vector_size(work.select(real_type()) >=
                min_size_rwork( minmn )));
#endif
        detail::gelss( traits::matrix_size1(a), traits::matrix_size2(a),
                traits::matrix_size2(b), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::matrix_storage(b),
                traits::leading_dimension(b), traits::vector_storage(s),
                rcond, rank,
                traits::vector_storage(work.select(value_type())),
                traits::vector_size(work.select(value_type())),
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorS >
    static void compute( MatrixA& a, MatrixB& b, VectorS& s,
            real_type const rcond, integer_t& rank, integer_t& info,
            minimal_workspace work ) {
        integer_t minmn = std::min( traits::matrix_size1(a),
                traits::matrix_size2(a) );
        traits::detail::array< value_type > tmp_work( min_size_work(
                traits::matrix_size1(a), traits::matrix_size2(a),
                traits::matrix_size2(b), minmn ) );
        traits::detail::array< real_type > tmp_rwork( min_size_rwork(
                minmn ) );
        compute( a, b, s, rcond, rank, info, workspace( tmp_work,
                tmp_rwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorS >
    static void compute( MatrixA& a, MatrixB& b, VectorS& s,
            real_type const rcond, integer_t& rank, integer_t& info,
            optimal_workspace work ) {
        integer_t minmn = std::min( traits::matrix_size1(a),
                traits::matrix_size2(a) );
        value_type opt_size_work;
        traits::detail::array< real_type > tmp_rwork( min_size_rwork(
                minmn ) );
        detail::gelss( traits::matrix_size1(a), traits::matrix_size2(a),
                traits::matrix_size2(b), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::matrix_storage(b),
                traits::leading_dimension(b), traits::vector_storage(s),
                rcond, rank, &opt_size_work, -1,
                traits::vector_storage(tmp_rwork), info );
        traits::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        compute( a, b, s, rcond, rank, info, workspace( tmp_work,
                tmp_rwork ) );
    }

    static integer_t min_size_work( integer_t const m, integer_t const n,
            integer_t const nrhs, integer_t const minmn ) {
        return std::max( 1, 2*minmn + std::max( std::max( m,n ), nrhs ) );
    }

    static integer_t min_size_rwork( integer_t const minmn ) {
        return 5*minmn;
    }
};


// template function to call gelss
template< typename MatrixA, typename MatrixB, typename VectorS,
        typename Workspace >
inline integer_t gelss( MatrixA& a, MatrixB& b, VectorS& s,
        typename traits::matrix_traits< MatrixA >::value_type const rcond,
        integer_t& rank, Workspace work = optimal_workspace() ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    gelss_impl< value_type >::compute( a, b, s, rcond, rank, info, work );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
