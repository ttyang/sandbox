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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_GGQRF_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_GGQRF_HPP

#include <boost/numeric/bindings/lapack/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/detail/utils.hpp>
#include <boost/numeric/bindings/traits/is_complex.hpp>
#include <boost/numeric/bindings/traits/is_real.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/utility/enable_if.hpp>
#include <cassert>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void ggqrf( integer_t const n, integer_t const m,
            integer_t const p, float* a, integer_t const lda, float* taua,
            float* b, integer_t const ldb, float* taub, float* work,
            integer_t const lwork, integer_t& info ) {
        LAPACK_SGGQRF( &n, &m, &p, a, &lda, taua, b, &ldb, taub, work, &lwork,
                &info );
    }
    inline void ggqrf( integer_t const n, integer_t const m,
            integer_t const p, double* a, integer_t const lda, double* taua,
            double* b, integer_t const ldb, double* taub, double* work,
            integer_t const lwork, integer_t& info ) {
        LAPACK_DGGQRF( &n, &m, &p, a, &lda, taua, b, &ldb, taub, work, &lwork,
                &info );
    }
    inline void ggqrf( integer_t const n, integer_t const m,
            integer_t const p, traits::complex_f* a, integer_t const lda,
            traits::complex_f* taua, traits::complex_f* b,
            integer_t const ldb, traits::complex_f* taub,
            traits::complex_f* work, integer_t const lwork, integer_t& info ) {
        LAPACK_CGGQRF( &n, &m, &p, traits::complex_ptr(a), &lda,
                traits::complex_ptr(taua), traits::complex_ptr(b), &ldb,
                traits::complex_ptr(taub), traits::complex_ptr(work), &lwork,
                &info );
    }
    inline void ggqrf( integer_t const n, integer_t const m,
            integer_t const p, traits::complex_d* a, integer_t const lda,
            traits::complex_d* taua, traits::complex_d* b,
            integer_t const ldb, traits::complex_d* taub,
            traits::complex_d* work, integer_t const lwork, integer_t& info ) {
        LAPACK_ZGGQRF( &n, &m, &p, traits::complex_ptr(a), &lda,
                traits::complex_ptr(taua), traits::complex_ptr(b), &ldb,
                traits::complex_ptr(taub), traits::complex_ptr(work), &lwork,
                &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct ggqrf_impl{};

// real specialization
template< typename ValueType >
struct ggqrf_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename VectorTAUA, typename MatrixB,
            typename VectorTAUB, typename WORK >
    static void compute( MatrixA& a, VectorTAUA& taua, MatrixB& b,
            VectorTAUB& taub, integer_t& info,
            detail::workspace1< WORK > work ) {
#ifndef NDEBUG
        assert( traits::matrix_size1(b) >= 0 );
        assert( traits::matrix_size2(a) >= 0 );
        assert( traits::matrix_size2(b) >= 0 );
        assert( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_size1(b)) );
        assert( traits::vector_size(taua) >= std::min(traits::matrix_size1(b),
                traits::matrix_size2(a)) );
        assert( traits::leading_dimension(b) >= std::max(1,
                traits::matrix_size1(b)) );
        assert( traits::vector_size(taub) >= std::min(traits::matrix_size1(b),
                traits::matrix_size2(b)) );
        assert( traits::vector_size(work.select(real_type()) >= min_size_work(
                $CALL_MIN_SIZE )));
#endif
        detail::ggqrf( traits::matrix_size1(b), traits::matrix_size2(a),
                traits::matrix_size2(b), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(taua),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::vector_storage(taub),
                traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename VectorTAUA, typename MatrixB,
            typename VectorTAUB >
    static void compute( MatrixA& a, VectorTAUA& taua, MatrixB& b,
            VectorTAUB& taub, integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        compute( a, taua, b, taub, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename VectorTAUA, typename MatrixB,
            typename VectorTAUB >
    static void compute( MatrixA& a, VectorTAUA& taua, MatrixB& b,
            VectorTAUB& taub, integer_t& info, optimal_workspace work ) {
        real_type opt_size_work;
        detail::ggqrf( traits::matrix_size1(b), traits::matrix_size2(a),
                traits::matrix_size2(b), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(taua),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::vector_storage(taub), &opt_size_work, -1, info );
        traits::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        compute( a, taua, b, taub, info, workspace( tmp_work ) );
    }

    static integer_t min_size_work( $ARGUMENTS ) {
        $MIN_SIZE
    }
};

// complex specialization
template< typename ValueType >
struct ggqrf_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename VectorTAUA, typename MatrixB,
            typename VectorTAUB, typename WORK >
    static void compute( MatrixA& a, VectorTAUA& taua, MatrixB& b,
            VectorTAUB& taub, integer_t& info,
            detail::workspace1< WORK > work ) {
#ifndef NDEBUG
        assert( traits::matrix_size1(b) >= 0 );
        assert( traits::matrix_size2(a) >= 0 );
        assert( traits::matrix_size2(b) >= 0 );
        assert( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_size1(b)) );
        assert( traits::vector_size(taua) >= std::min(traits::matrix_size1(b),
                traits::matrix_size2(a)) );
        assert( traits::leading_dimension(b) >= std::max(1,
                traits::matrix_size1(b)) );
        assert( traits::vector_size(taub) >= std::min(traits::matrix_size1(b),
                traits::matrix_size2(b)) );
        assert( traits::vector_size(work.select(value_type()) >=
                min_size_work( $CALL_MIN_SIZE )));
#endif
        detail::ggqrf( traits::matrix_size1(b), traits::matrix_size2(a),
                traits::matrix_size2(b), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(taua),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::vector_storage(taub),
                traits::vector_storage(work.select(value_type())),
                traits::vector_size(work.select(value_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename VectorTAUA, typename MatrixB,
            typename VectorTAUB >
    static void compute( MatrixA& a, VectorTAUA& taua, MatrixB& b,
            VectorTAUB& taub, integer_t& info, minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        compute( a, taua, b, taub, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename VectorTAUA, typename MatrixB,
            typename VectorTAUB >
    static void compute( MatrixA& a, VectorTAUA& taua, MatrixB& b,
            VectorTAUB& taub, integer_t& info, optimal_workspace work ) {
        value_type opt_size_work;
        detail::ggqrf( traits::matrix_size1(b), traits::matrix_size2(a),
                traits::matrix_size2(b), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(taua),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::vector_storage(taub), &opt_size_work, -1, info );
        traits::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        compute( a, taua, b, taub, info, workspace( tmp_work ) );
    }

    static integer_t min_size_work( $ARGUMENTS ) {
        $MIN_SIZE
    }
};


// template function to call ggqrf
template< typename MatrixA, typename VectorTAUA, typename MatrixB,
        typename VectorTAUB, typename Workspace >
inline integer_t ggqrf( MatrixA& a, VectorTAUA& taua, MatrixB& b,
        VectorTAUB& taub, Workspace work = optimal_workspace() ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    ggqrf_impl< value_type >::compute( a, taua, b, taub, info, work );
    return info;
}


}}}} // namespace boost::numeric::bindings::lapack

#endif
