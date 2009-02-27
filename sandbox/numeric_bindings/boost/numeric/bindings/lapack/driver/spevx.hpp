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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_SPEVX_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_SPEVX_HPP

#include <boost/numeric/bindings/lapack/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp
#include <boost/type_traits/is_same.hpp>
#include <cassert>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void spevx( char const jobz, char const range, char const uplo,
            integer_t const n, float* ap, float const vl, float const vu,
            integer_t const il, integer_t const iu, float const abstol,
            integer_t& m, float* w, float* z, integer_t const ldz,
            float* work, integer_t* iwork, integer_t* ifail,
            integer_t& info ) {
        LAPACK_SSPEVX( &jobz, &range, &uplo, &n, ap, &vl, &vu, &il, &iu,
                &abstol, &m, w, z, &ldz, work, iwork, ifail, &info );
    }
    inline void spevx( char const jobz, char const range, char const uplo,
            integer_t const n, double* ap, double const vl, double const vu,
            integer_t const il, integer_t const iu, double const abstol,
            integer_t& m, double* w, double* z, integer_t const ldz,
            double* work, integer_t* iwork, integer_t* ifail,
            integer_t& info ) {
        LAPACK_DSPEVX( &jobz, &range, &uplo, &n, ap, &vl, &vu, &il, &iu,
                &abstol, &m, w, z, &ldz, work, iwork, ifail, &info );
    }
}

// value-type based template
template< typename ValueType >
struct spevx_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixAP, typename VectorW, typename MatrixZ,
            typename VectorIFAIL, typename WORK, typename IWORK >
    static void compute( char const jobz, char const range, integer_t const n,
            MatrixAP& ap, real_type const vl, real_type const vu,
            integer_t const il, integer_t const iu, real_type const abstol,
            integer_t& m, VectorW& w, MatrixZ& z, VectorIFAIL& ifail,
            integer_t& info, detail::workspace2< WORK, IWORK > work ) {
        BOOST_STATIC_ASSERT( boost::is_same< typename traits::matrix_traits<
                MatrixAP >::value_type, typename traits::vector_traits<
                VectorW >::value_type > );
        BOOST_STATIC_ASSERT( boost::is_same< typename traits::matrix_traits<
                MatrixAP >::value_type, typename traits::matrix_traits<
                MatrixZ >::value_type > );
#ifndef NDEBUG
        assert( jobz == 'N' || jobz == 'V' );
        assert( range == 'A' || range == 'V' || range == 'I' );
        assert( traits::matrix_uplo_tag(ap) == 'U' ||
                traits::matrix_uplo_tag(ap) == 'L' );
        assert( n >= 0 );
        assert( traits::vector_size(work.select(real_type()) >= min_size_work(
                n )));
        assert( traits::vector_size(work.select(integer_t()) >=
                min_size_iwork( n )));
#endif
        detail::spevx( jobz, range, traits::matrix_uplo_tag(ap), n,
                traits::matrix_storage(ap), vl, vu, il, iu, abstol, m,
                traits::vector_storage(w), traits::matrix_storage(z),
                traits::leading_dimension(z),
                traits::vector_storage(work.select(real_type())),
                traits::vector_storage(work.select(integer_t())),
                traits::vector_storage(ifail), info );
    }

    // minimal workspace specialization
    template< typename MatrixAP, typename VectorW, typename MatrixZ,
            typename VectorIFAIL >
    static void compute( char const jobz, char const range, integer_t const n,
            MatrixAP& ap, real_type const vl, real_type const vu,
            integer_t const il, integer_t const iu, real_type const abstol,
            integer_t& m, VectorW& w, MatrixZ& z, VectorIFAIL& ifail,
            integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work( n ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork( n ) );
        compute( jobz, range, n, ap, vl, vu, il, iu, abstol, m, w, z, ifail,
                info, workspace( tmp_work, tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixAP, typename VectorW, typename MatrixZ,
            typename VectorIFAIL >
    static void compute( char const jobz, char const range, integer_t const n,
            MatrixAP& ap, real_type const vl, real_type const vu,
            integer_t const il, integer_t const iu, real_type const abstol,
            integer_t& m, VectorW& w, MatrixZ& z, VectorIFAIL& ifail,
            integer_t& info, optimal_workspace work ) {
        compute( jobz, range, n, ap, vl, vu, il, iu, abstol, m, w, z, ifail,
                info, minimal_workspace() );
    }

    static integer_t min_size_work( integer_t const n ) {
        return 8*n;
    }

    static integer_t min_size_iwork( integer_t const n ) {
        return 5*n;
    }
};


// template function to call spevx
template< typename MatrixAP, typename VectorW, typename MatrixZ,
        typename VectorIFAIL, typename Workspace >
inline integer_t spevx( char const jobz, char const range,
        integer_t const n, MatrixAP& ap, typename traits::matrix_traits<
        MatrixAP >::value_type const vl, typename traits::matrix_traits<
        MatrixAP >::value_type const vu, integer_t const il,
        integer_t const iu, typename traits::matrix_traits<
        MatrixAP >::value_type const abstol, integer_t& m, VectorW& w,
        MatrixZ& z, VectorIFAIL& ifail,
        Workspace work = optimal_workspace() ) {
    typedef typename traits::matrix_traits< MatrixAP >::value_type value_type;
    integer_t info(0);
    spevx_impl< value_type >::compute( jobz, range, n, ap, vl, vu, il,
            iu, abstol, m, w, z, ifail, info, work );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
