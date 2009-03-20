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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_LABRD_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_LABRD_HPP

#include <boost/assert.hpp>
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
    inline void labrd( integer_t const m, integer_t const n,
            integer_t const nb, float* a, integer_t const lda, float* d,
            float* e, float* tauq, float* taup, float* x, integer_t const ldx,
            float* y, integer_t const ldy ) {
        LAPACK_SLABRD( &m, &n, &nb, a, &lda, d, e, tauq, taup, x, &ldx, y,
                &ldy );
    }
    inline void labrd( integer_t const m, integer_t const n,
            integer_t const nb, double* a, integer_t const lda, double* d,
            double* e, double* tauq, double* taup, double* x,
            integer_t const ldx, double* y, integer_t const ldy ) {
        LAPACK_DLABRD( &m, &n, &nb, a, &lda, d, e, tauq, taup, x, &ldx, y,
                &ldy );
    }
    inline void labrd( integer_t const m, integer_t const n,
            integer_t const nb, traits::complex_f* a, integer_t const lda,
            float* d, float* e, traits::complex_f* tauq,
            traits::complex_f* taup, traits::complex_f* x,
            integer_t const ldx, traits::complex_f* y, integer_t const ldy ) {
        LAPACK_CLABRD( &m, &n, &nb, traits::complex_ptr(a), &lda, d, e,
                traits::complex_ptr(tauq), traits::complex_ptr(taup),
                traits::complex_ptr(x), &ldx, traits::complex_ptr(y), &ldy );
    }
    inline void labrd( integer_t const m, integer_t const n,
            integer_t const nb, traits::complex_d* a, integer_t const lda,
            double* d, double* e, traits::complex_d* tauq,
            traits::complex_d* taup, traits::complex_d* x,
            integer_t const ldx, traits::complex_d* y, integer_t const ldy ) {
        LAPACK_ZLABRD( &m, &n, &nb, traits::complex_ptr(a), &lda, d, e,
                traits::complex_ptr(tauq), traits::complex_ptr(taup),
                traits::complex_ptr(x), &ldx, traits::complex_ptr(y), &ldy );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct labrd_impl{};

// real specialization
template< typename ValueType >
struct labrd_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

$INCLUDE_TEMPLATES
    // templated specialization
    template< typename MatrixA, typename VectorD, typename VectorE,
            typename VectorTAUQ, typename VectorTAUP, typename MatrixX,
            typename MatrixY >
    static void invoke( MatrixA& a, VectorD& d, VectorE& e, VectorTAUQ& tauq,
            VectorTAUP& taup, MatrixX& x, MatrixY& y ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorD >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorE >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorTAUQ >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorTAUP >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixX >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixY >::value_type >::value) );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_rows(a)) );
        BOOST_ASSERT( traits::vector_size(d) >=
                traits::matrix_num_columns(a) );
        BOOST_ASSERT( traits::vector_size(e) >=
                traits::matrix_num_columns(a) );
        BOOST_ASSERT( traits::vector_size(tauq) >=
                traits::matrix_num_columns(a) );
        BOOST_ASSERT( traits::vector_size(taup) >=
                traits::matrix_num_columns(a) );
        BOOST_ASSERT( traits::leading_dimension(x) >=
                traits::matrix_num_rows(a) );
        BOOST_ASSERT( traits::leading_dimension(y) >=
                traits::matrix_num_columns(a) );
        detail::labrd( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_num_columns(a),
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::vector_storage(d), traits::vector_storage(e),
                traits::vector_storage(tauq), traits::vector_storage(taup),
                traits::matrix_storage(x), traits::leading_dimension(x),
                traits::matrix_storage(y), traits::leading_dimension(y) );
    }
};

// complex specialization
template< typename ValueType >
struct labrd_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

$INCLUDE_TEMPLATES
    // templated specialization
    template< typename MatrixA, typename VectorD, typename VectorE,
            typename VectorTAUQ, typename VectorTAUP, typename MatrixX,
            typename MatrixY >
    static void invoke( MatrixA& a, VectorD& d, VectorE& e, VectorTAUQ& tauq,
            VectorTAUP& taup, MatrixX& x, MatrixY& y ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::vector_traits<
                VectorE >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorTAUQ >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorTAUP >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixX >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixY >::value_type >::value) );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_rows(a)) );
        BOOST_ASSERT( traits::vector_size(d) >=
                traits::matrix_num_columns(a) );
        BOOST_ASSERT( traits::vector_size(e) >=
                traits::matrix_num_columns(a) );
        BOOST_ASSERT( traits::vector_size(tauq) >=
                traits::matrix_num_columns(a) );
        BOOST_ASSERT( traits::vector_size(taup) >=
                traits::matrix_num_columns(a) );
        BOOST_ASSERT( traits::leading_dimension(x) >= std::max(1,
                traits::matrix_num_rows(a)) );
        BOOST_ASSERT( traits::leading_dimension(y) >= std::max(1,
                traits::matrix_num_columns(a)) );
        detail::labrd( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_num_columns(a),
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::vector_storage(d), traits::vector_storage(e),
                traits::vector_storage(tauq), traits::vector_storage(taup),
                traits::matrix_storage(x), traits::leading_dimension(x),
                traits::matrix_storage(y), traits::leading_dimension(y) );
    }
};


// template function to call labrd
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAUQ, typename VectorTAUP, typename MatrixX,
        typename MatrixY >
inline integer_t labrd( MatrixA& a, VectorD& d, VectorE& e,
        VectorTAUQ& tauq, VectorTAUP& taup, MatrixX& x, MatrixY& y ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    labrd_impl< value_type >::invoke( a, d, e, tauq, taup, x, y );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
