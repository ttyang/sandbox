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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_PTEQR_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_PTEQR_HPP

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
    inline void pteqr( const char compz, const integer_t n, float* d,
            float* e, float* z, const integer_t ldz, float* work,
            integer_t& info ) {
        LAPACK_SPTEQR( &compz, &n, d, e, z, &ldz, work, &info );
    }
    inline void pteqr( const char compz, const integer_t n, double* d,
            double* e, double* z, const integer_t ldz, double* work,
            integer_t& info ) {
        LAPACK_DPTEQR( &compz, &n, d, e, z, &ldz, work, &info );
    }
    inline void pteqr( const char compz, const integer_t n, float* d,
            float* e, traits::complex_f* z, const integer_t ldz, float* work,
            integer_t& info ) {
        LAPACK_CPTEQR( &compz, &n, d, e, traits::complex_ptr(z), &ldz, work,
                &info );
    }
    inline void pteqr( const char compz, const integer_t n, double* d,
            double* e, traits::complex_d* z, const integer_t ldz,
            double* work, integer_t& info ) {
        LAPACK_ZPTEQR( &compz, &n, d, e, traits::complex_ptr(z), &ldz, work,
                &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct pteqr_impl{};

// real specialization
template< typename ValueType >
struct pteqr_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename VectorD, typename VectorE, typename MatrixZ,
            typename WORK >
    static void invoke( const char compz, const integer_t n, VectorD& d,
            VectorE& e, MatrixZ& z, integer_t& info, detail::workspace1<
            WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::vector_traits<
                VectorE >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::matrix_traits<
                MatrixZ >::value_type >::value) );
        BOOST_ASSERT( compz == 'N' || compz == 'V' || compz == 'I' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( traits::vector_size(d) >= n );
        BOOST_ASSERT( traits::vector_size(e) >= n-1 );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( n ));
        detail::pteqr( compz, n, traits::vector_storage(d),
                traits::vector_storage(e), traits::matrix_storage(z),
                traits::leading_dimension(z),
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename VectorD, typename VectorE, typename MatrixZ >
    static void invoke( const char compz, const integer_t n, VectorD& d,
            VectorE& e, MatrixZ& z, integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work( n ) );
        invoke( compz, n, d, e, z, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename VectorD, typename VectorE, typename MatrixZ >
    static void invoke( const char compz, const integer_t n, VectorD& d,
            VectorE& e, MatrixZ& z, integer_t& info, optimal_workspace work ) {
        invoke( compz, n, d, e, z, info, minimal_workspace() );
    }

    static integer_t min_size_work( const integer_t n ) {
        return 4*n;
    }
};

// complex specialization
template< typename ValueType >
struct pteqr_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename VectorD, typename VectorE, typename MatrixZ,
            typename WORK >
    static void invoke( const char compz, const integer_t n, VectorD& d,
            VectorE& e, MatrixZ& z, integer_t& info, detail::workspace1<
            WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::vector_traits<
                VectorE >::value_type >::value) );
        BOOST_ASSERT( compz == 'N' || compz == 'V' || compz == 'I' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( traits::vector_size(d) >= n );
        BOOST_ASSERT( traits::vector_size(e) >= n-1 );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( n ));
        detail::pteqr( compz, n, traits::vector_storage(d),
                traits::vector_storage(e), traits::matrix_storage(z),
                traits::leading_dimension(z),
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename VectorD, typename VectorE, typename MatrixZ >
    static void invoke( const char compz, const integer_t n, VectorD& d,
            VectorE& e, MatrixZ& z, integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work( n ) );
        invoke( compz, n, d, e, z, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename VectorD, typename VectorE, typename MatrixZ >
    static void invoke( const char compz, const integer_t n, VectorD& d,
            VectorE& e, MatrixZ& z, integer_t& info, optimal_workspace work ) {
        invoke( compz, n, d, e, z, info, minimal_workspace() );
    }

    static integer_t min_size_work( const integer_t n ) {
        return 4*n;
    }
};


// template function to call pteqr
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline integer_t pteqr( const char compz, const integer_t n, VectorD& d,
        VectorE& e, MatrixZ& z, Workspace work ) {
    typedef typename traits::matrix_traits< MatrixZ >::value_type value_type;
    integer_t info(0);
    pteqr_impl< value_type >::invoke( compz, n, d, e, z, info, work );
    return info;
}

// template function to call pteqr, default workspace type
template< typename VectorD, typename VectorE, typename MatrixZ >
inline integer_t pteqr( const char compz, const integer_t n, VectorD& d,
        VectorE& e, MatrixZ& z ) {
    typedef typename traits::matrix_traits< MatrixZ >::value_type value_type;
    integer_t info(0);
    pteqr_impl< value_type >::invoke( compz, n, d, e, z, info,
            optimal_workspace() );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
