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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_LATRS_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_LATRS_HPP

#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
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

inline void latrs( const char uplo, const char trans, const char diag,
        const char normin, const integer_t n, const float* a,
        const integer_t lda, float* x, float& scale, float* cnorm,
        integer_t& info ) {
    LAPACK_SLATRS( &uplo, &trans, &diag, &normin, &n, a, &lda, x, &scale,
            cnorm, &info );
}
inline void latrs( const char uplo, const char trans, const char diag,
        const char normin, const integer_t n, const double* a,
        const integer_t lda, double* x, double& scale, double* cnorm,
        integer_t& info ) {
    LAPACK_DLATRS( &uplo, &trans, &diag, &normin, &n, a, &lda, x, &scale,
            cnorm, &info );
}
inline void latrs( const char uplo, const char trans, const char diag,
        const char normin, const integer_t n, const traits::complex_f* a,
        const integer_t lda, traits::complex_f* x, float& scale, float* cnorm,
        integer_t& info ) {
    LAPACK_CLATRS( &uplo, &trans, &diag, &normin, &n, traits::complex_ptr(a),
            &lda, traits::complex_ptr(x), &scale, cnorm, &info );
}
inline void latrs( const char uplo, const char trans, const char diag,
        const char normin, const integer_t n, const traits::complex_d* a,
        const integer_t lda, traits::complex_d* x, double& scale,
        double* cnorm, integer_t& info ) {
    LAPACK_ZLATRS( &uplo, &trans, &diag, &normin, &n, traits::complex_ptr(a),
            &lda, traits::complex_ptr(x), &scale, cnorm, &info );
}
} // namespace detail

// value-type based template
template< typename ValueType, typename Enable = void >
struct latrs_impl{};

// real specialization
template< typename ValueType >
struct latrs_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixA, typename VectorX, typename VectorCNORM >
    static void invoke( const char uplo, const char trans, const char diag,
            const char normin, const MatrixA& a, VectorX& x, real_type& scale,
            VectorCNORM& cnorm, integer_t& info ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorX >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorCNORM >::value_type >::value) );
        BOOST_ASSERT( uplo == 'U' || uplo == 'L' );
        BOOST_ASSERT( trans == 'N' || trans == 'T' || trans == 'C' );
        BOOST_ASSERT( diag == 'N' || diag == 'U' );
        BOOST_ASSERT( normin == 'Y' || normin == 'N' );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= ?MAX );
        BOOST_ASSERT( traits::vector_size(x) >=
                traits::matrix_num_columns(a) );
        detail::latrs( uplo, trans, diag, normin,
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(x),
                scale, traits::vector_storage(cnorm), info );
    }
};

// complex specialization
template< typename ValueType >
struct latrs_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixA, typename VectorX, typename VectorCNORM >
    static void invoke( const char uplo, const char trans, const char diag,
            const char normin, const MatrixA& a, VectorX& x, real_type& scale,
            VectorCNORM& cnorm, integer_t& info ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorX >::value_type >::value) );
        BOOST_ASSERT( uplo == 'U' || uplo == 'L' );
        BOOST_ASSERT( trans == 'N' || trans == 'T' || trans == 'C' );
        BOOST_ASSERT( diag == 'N' || diag == 'U' );
        BOOST_ASSERT( normin == 'Y' || normin == 'N' );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= ?MAX );
        BOOST_ASSERT( traits::vector_size(x) >=
                traits::matrix_num_columns(a) );
        detail::latrs( uplo, trans, diag, normin,
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(x),
                scale, traits::vector_storage(cnorm), info );
    }
};


// template function to call latrs
template< typename MatrixA, typename VectorX, typename VectorCNORM >
inline integer_t latrs( const char uplo, const char trans,
        const char diag, const char normin, const MatrixA& a, VectorX& x,
        typename traits::type_traits< typename traits::matrix_traits<
        MatrixA >::value_type >::real_type& scale, VectorCNORM& cnorm ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    latrs_impl< value_type >::invoke( uplo, trans, diag, normin, a, x,
            scale, cnorm, info );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
