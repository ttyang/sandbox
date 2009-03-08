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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_HBGVD_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_HBGVD_HPP

#include <boost/numeric/bindings/lapack/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/detail/utils.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <cassert>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void hbgvd( char const jobz, char const uplo, integer_t const n,
            integer_t const ka, integer_t const kb, traits::complex_f* ab,
            integer_t const ldab, traits::complex_f* bb, integer_t const ldbb,
            float* w, traits::complex_f* z, integer_t const ldz,
            traits::complex_f* work, integer_t const lwork, float* rwork,
            integer_t const lrwork, integer_t* iwork, integer_t const liwork,
            integer_t& info ) {
        LAPACK_CHBGVD( &jobz, &uplo, &n, &ka, &kb, traits::complex_ptr(ab),
                &ldab, traits::complex_ptr(bb), &ldbb, w,
                traits::complex_ptr(z), &ldz, traits::complex_ptr(work),
                &lwork, rwork, &lrwork, iwork, &liwork, &info );
    }
    inline void hbgvd( char const jobz, char const uplo, integer_t const n,
            integer_t const ka, integer_t const kb, traits::complex_d* ab,
            integer_t const ldab, traits::complex_d* bb, integer_t const ldbb,
            double* w, traits::complex_d* z, integer_t const ldz,
            traits::complex_d* work, integer_t const lwork, double* rwork,
            integer_t const lrwork, integer_t* iwork, integer_t const liwork,
            integer_t& info ) {
        LAPACK_ZHBGVD( &jobz, &uplo, &n, &ka, &kb, traits::complex_ptr(ab),
                &ldab, traits::complex_ptr(bb), &ldbb, w,
                traits::complex_ptr(z), &ldz, traits::complex_ptr(work),
                &lwork, rwork, &lrwork, iwork, &liwork, &info );
    }
}

// value-type based template
template< typename ValueType >
struct hbgvd_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixAB, typename MatrixBB, typename VectorW,
            typename MatrixZ, typename WORK, typename RWORK, typename IWORK >
    static void compute( char const jobz, integer_t const n,
            integer_t const ka, integer_t const kb, MatrixAB& ab,
            MatrixBB& bb, VectorW& w, MatrixZ& z, integer_t& info,
            detail::workspace3< WORK, RWORK, IWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixAB >::value_type, typename traits::matrix_traits<
                MatrixBB >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixAB >::value_type, typename traits::matrix_traits<
                MatrixZ >::value_type >::value) );
#ifndef NDEBUG
        assert( jobz == 'N' || jobz == 'V' );
        assert( traits::matrix_uplo_tag(ab) == 'U' ||
                traits::matrix_uplo_tag(ab) == 'L' );
        assert( n >= 0 );
        assert( ka >= 0 );
        assert( kb >= 0 );
        assert( traits::leading_dimension(ab) >= ka+1 );
        assert( traits::leading_dimension(bb) >= kb+1 );
        assert( traits::vector_size(work.select(value_type()) >=
                min_size_work( jobz, n )));
        assert( traits::vector_size(work.select(real_type()) >=
                min_size_rwork( jobz, n )));
        assert( traits::vector_size(work.select(integer_t()) >=
                min_size_iwork( jobz, n )));
#endif
        detail::hbgvd( jobz, traits::matrix_uplo_tag(ab), n, ka, kb,
                traits::matrix_storage(ab), traits::leading_dimension(ab),
                traits::matrix_storage(bb), traits::leading_dimension(bb),
                traits::vector_storage(w), traits::matrix_storage(z),
                traits::leading_dimension(z),
                traits::vector_storage(work.select(value_type())),
                traits::vector_size(work.select(value_type())),
                traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())),
                traits::vector_storage(work.select(integer_t())),
                traits::vector_size(work.select(integer_t())), info );
    }

    // minimal workspace specialization
    template< typename MatrixAB, typename MatrixBB, typename VectorW,
            typename MatrixZ >
    static void compute( char const jobz, integer_t const n,
            integer_t const ka, integer_t const kb, MatrixAB& ab,
            MatrixBB& bb, VectorW& w, MatrixZ& z, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work( jobz,
                n ) );
        traits::detail::array< real_type > tmp_rwork( min_size_rwork( jobz,
                n ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork( jobz,
                n ) );
        compute( jobz, n, ka, kb, ab, bb, w, z, info, workspace( tmp_work,
                tmp_rwork, tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixAB, typename MatrixBB, typename VectorW,
            typename MatrixZ >
    static void compute( char const jobz, integer_t const n,
            integer_t const ka, integer_t const kb, MatrixAB& ab,
            MatrixBB& bb, VectorW& w, MatrixZ& z, integer_t& info,
            optimal_workspace work ) {
        value_type opt_size_work;
        real_type opt_size_rwork;
        integer_t opt_size_iwork;
        detail::hbgvd( jobz, traits::matrix_uplo_tag(ab), n, ka, kb,
                traits::matrix_storage(ab), traits::leading_dimension(ab),
                traits::matrix_storage(bb), traits::leading_dimension(bb),
                traits::vector_storage(w), traits::matrix_storage(z),
                traits::leading_dimension(z), &opt_size_work, -1,
                &opt_size_rwork, -1, &opt_size_iwork, -1, info );
        traits::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        traits::detail::array< real_type > tmp_rwork(
                traits::detail::to_int( opt_size_rwork ) );
        traits::detail::array< integer_t > tmp_iwork( opt_size_iwork );
        compute( jobz, n, ka, kb, ab, bb, w, z, info, workspace( tmp_work,
                tmp_rwork, tmp_iwork ) );
    }

    static integer_t min_size_work( char const jobz, integer_t const n ) {
        if ( n < 2 )
            return 1;
        else {
            if ( jobz == 'N' )
                return n;
            else
                return 2*n*n;
        }
    }

    static integer_t min_size_rwork( char const jobz, integer_t const n ) {
        if ( n < 2 )
            return 1;
        else {
            if ( jobz == 'N' )
                return n;
            else
                return 1 + 5*n + 2*n*n;
        }
    }

    static integer_t min_size_iwork( char const jobz, integer_t const n ) {
        if ( jobz == 'N' || n < 2 )
            return 1;
        else
            return 3 + 5*n;
    }
};


// template function to call hbgvd
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ, typename Workspace >
inline integer_t hbgvd( char const jobz, integer_t const n,
        integer_t const ka, integer_t const kb, MatrixAB& ab, MatrixBB& bb,
        VectorW& w, MatrixZ& z, Workspace work = optimal_workspace() ) {
    typedef typename traits::matrix_traits< MatrixAB >::value_type value_type;
    integer_t info(0);
    hbgvd_impl< value_type >::compute( jobz, n, ka, kb, ab, bb, w, z,
            info, work );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
