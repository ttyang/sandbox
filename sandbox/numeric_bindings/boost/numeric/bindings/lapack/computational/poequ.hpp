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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_POEQU_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_POEQU_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/lapack/lapack.h>
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
    inline void poequ( integer_t const n, float* a, integer_t const lda,
            float* s, float& scond, float& amax, integer_t& info ) {
        LAPACK_SPOEQU( &n, a, &lda, s, &scond, &amax, &info );
    }
    inline void poequ( integer_t const n, double* a, integer_t const lda,
            double* s, double& scond, double& amax, integer_t& info ) {
        LAPACK_DPOEQU( &n, a, &lda, s, &scond, &amax, &info );
    }
    inline void poequ( integer_t const n, traits::complex_f* a,
            integer_t const lda, float* s, float& scond, float& amax,
            integer_t& info ) {
        LAPACK_CPOEQU( &n, traits::complex_ptr(a), &lda, s, &scond, &amax,
                &info );
    }
    inline void poequ( integer_t const n, traits::complex_d* a,
            integer_t const lda, double* s, double& scond, double& amax,
            integer_t& info ) {
        LAPACK_ZPOEQU( &n, traits::complex_ptr(a), &lda, s, &scond, &amax,
                &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct poequ_impl{};

// real specialization
template< typename ValueType >
struct poequ_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixA, typename VectorS >
    static void compute( MatrixA& a, VectorS& s, real_type& scond,
            real_type& amax, integer_t& info ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorS >::value_type >::value) );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_columns(a)) );
        detail::poequ( traits::matrix_num_columns(a),
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::vector_storage(s), scond, amax, info );
    }
};

// complex specialization
template< typename ValueType >
struct poequ_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixA, typename VectorS >
    static void compute( MatrixA& a, VectorS& s, real_type& scond,
            real_type& amax, integer_t& info ) {
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_columns(a)) );
        detail::poequ( traits::matrix_num_columns(a),
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::vector_storage(s), scond, amax, info );
    }
};


// template function to call poequ
template< typename MatrixA, typename VectorS >
inline integer_t poequ( MatrixA& a, VectorS& s,
        typename traits::matrix_traits< MatrixA >::value_type& scond,
        typename traits::matrix_traits< MatrixA >::value_type& amax ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    poequ_impl< value_type >::compute( a, s, scond, amax, info );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
