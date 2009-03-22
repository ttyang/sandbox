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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GEBAL_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GEBAL_HPP

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
    inline void gebal( char const job, integer_t const n, float* a,
            integer_t const lda, integer_t& ilo, integer_t& ihi, float* scale,
            integer_t& info ) {
        LAPACK_SGEBAL( &job, &n, a, &lda, &ilo, &ihi, scale, &info );
    }
    inline void gebal( char const job, integer_t const n, double* a,
            integer_t const lda, integer_t& ilo, integer_t& ihi,
            double* scale, integer_t& info ) {
        LAPACK_DGEBAL( &job, &n, a, &lda, &ilo, &ihi, scale, &info );
    }
    inline void gebal( char const job, integer_t const n,
            traits::complex_f* a, integer_t const lda, integer_t& ilo,
            integer_t& ihi, float* scale, integer_t& info ) {
        LAPACK_CGEBAL( &job, &n, traits::complex_ptr(a), &lda, &ilo, &ihi,
                scale, &info );
    }
    inline void gebal( char const job, integer_t const n,
            traits::complex_d* a, integer_t const lda, integer_t& ilo,
            integer_t& ihi, double* scale, integer_t& info ) {
        LAPACK_ZGEBAL( &job, &n, traits::complex_ptr(a), &lda, &ilo, &ihi,
                scale, &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct gebal_impl{};

// real specialization
template< typename ValueType >
struct gebal_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixA, typename VectorSCALE >
    static void invoke( char const job, MatrixA& a, integer_t& ilo,
            integer_t& ihi, VectorSCALE& scale, integer_t& info ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorSCALE >::value_type >::value) );
        BOOST_ASSERT( job == 'N' || job == 'P' || job == 'S' || job == 'B' );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_columns(a)) );
        detail::gebal( job, traits::matrix_num_columns(a),
                traits::matrix_storage(a), traits::leading_dimension(a), ilo,
                ihi, traits::vector_storage(scale), info );
    }
};

// complex specialization
template< typename ValueType >
struct gebal_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixA, typename VectorSCALE >
    static void invoke( char const job, MatrixA& a, integer_t& ilo,
            integer_t& ihi, VectorSCALE& scale, integer_t& info ) {
        BOOST_ASSERT( job == 'N' || job == 'P' || job == 'S' || job == 'B' );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_columns(a)) );
        detail::gebal( job, traits::matrix_num_columns(a),
                traits::matrix_storage(a), traits::leading_dimension(a), ilo,
                ihi, traits::vector_storage(scale), info );
    }
};


// template function to call gebal
template< typename MatrixA, typename VectorSCALE >
inline integer_t gebal( char const job, MatrixA& a, integer_t& ilo,
        integer_t& ihi, VectorSCALE& scale ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    gebal_impl< value_type >::invoke( job, a, ilo, ihi, scale, info );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
