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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_HPEV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_HPEV_HPP

#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
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
    inline void hpev( char const jobz, char const uplo, integer_t const n,
            traits::complex_f* ap, float* w, traits::complex_f* z,
            integer_t const ldz, traits::complex_f* work, float* rwork,
            integer_t& info ) {
        LAPACK_CHPEV( &jobz, &uplo, &n, traits::complex_ptr(ap), w,
                traits::complex_ptr(z), &ldz, traits::complex_ptr(work),
                rwork, &info );
    }
    inline void hpev( char const jobz, char const uplo, integer_t const n,
            traits::complex_d* ap, double* w, traits::complex_d* z,
            integer_t const ldz, traits::complex_d* work, double* rwork,
            integer_t& info ) {
        LAPACK_ZHPEV( &jobz, &uplo, &n, traits::complex_ptr(ap), w,
                traits::complex_ptr(z), &ldz, traits::complex_ptr(work),
                rwork, &info );
    }
}

// value-type based template
template< typename ValueType >
struct hpev_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixAP, typename VectorW, typename MatrixZ,
            typename WORK, typename RWORK >
    static void invoke( char const jobz, integer_t const n, MatrixAP& ap,
            VectorW& w, MatrixZ& z, integer_t& info, detail::workspace2< WORK,
            RWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixAP >::value_type, typename traits::matrix_traits<
                MatrixZ >::value_type >::value) );
        BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
        BOOST_ASSERT( traits::matrix_uplo_tag(ap) == 'U' ||
                traits::matrix_uplo_tag(ap) == 'L' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( n ));
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_rwork( n ));
        detail::hpev( jobz, traits::matrix_uplo_tag(ap), n,
                traits::matrix_storage(ap), traits::vector_storage(w),
                traits::matrix_storage(z), traits::leading_dimension(z),
                traits::vector_storage(work.select(value_type())),
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixAP, typename VectorW, typename MatrixZ >
    static void invoke( char const jobz, integer_t const n, MatrixAP& ap,
            VectorW& w, MatrixZ& z, integer_t& info, minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work( n ) );
        traits::detail::array< real_type > tmp_rwork( min_size_rwork( n ) );
        invoke( jobz, n, ap, w, z, info, workspace( tmp_work, tmp_rwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixAP, typename VectorW, typename MatrixZ >
    static void invoke( char const jobz, integer_t const n, MatrixAP& ap,
            VectorW& w, MatrixZ& z, integer_t& info, optimal_workspace work ) {
        invoke( jobz, n, ap, w, z, info, minimal_workspace() );
    }

    static integer_t min_size_work( integer_t const n ) {
        return std::max(1,2*n-1);
    }

    static integer_t min_size_rwork( integer_t const n ) {
        return std::max(1,3*n-2);
    }
};


// template function to call hpev
template< typename MatrixAP, typename VectorW, typename MatrixZ,
        typename Workspace >
inline integer_t hpev( char const jobz, integer_t const n, MatrixAP& ap,
        VectorW& w, MatrixZ& z, Workspace work ) {
    typedef typename traits::matrix_traits< MatrixAP >::value_type value_type;
    integer_t info(0);
    hpev_impl< value_type >::invoke( jobz, n, ap, w, z, info, work );
    return info;
}

// template function to call hpev, default workspace type
template< typename MatrixAP, typename VectorW, typename MatrixZ >
inline integer_t hpev( char const jobz, integer_t const n, MatrixAP& ap,
        VectorW& w, MatrixZ& z ) {
    typedef typename traits::matrix_traits< MatrixAP >::value_type value_type;
    integer_t info(0);
    hpev_impl< value_type >::invoke( jobz, n, ap, w, z, info,
            optimal_workspace() );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
