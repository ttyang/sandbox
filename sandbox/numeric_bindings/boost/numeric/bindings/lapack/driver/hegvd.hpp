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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_HEGVD_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_HEGVD_HPP

#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/detail/utils.hpp>
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

inline void hegvd( const integer_t itype, const char jobz, const char uplo,
        const integer_t n, traits::complex_f* a, const integer_t lda,
        traits::complex_f* b, const integer_t ldb, float* w,
        traits::complex_f* work, const integer_t lwork, float* rwork,
        const integer_t lrwork, integer_t* iwork, const integer_t liwork,
        integer_t& info ) {
    LAPACK_CHEGVD( &itype, &jobz, &uplo, &n, traits::complex_ptr(a), &lda,
            traits::complex_ptr(b), &ldb, w, traits::complex_ptr(work),
            &lwork, rwork, &lrwork, iwork, &liwork, &info );
}
inline void hegvd( const integer_t itype, const char jobz, const char uplo,
        const integer_t n, traits::complex_d* a, const integer_t lda,
        traits::complex_d* b, const integer_t ldb, double* w,
        traits::complex_d* work, const integer_t lwork, double* rwork,
        const integer_t lrwork, integer_t* iwork, const integer_t liwork,
        integer_t& info ) {
    LAPACK_ZHEGVD( &itype, &jobz, &uplo, &n, traits::complex_ptr(a), &lda,
            traits::complex_ptr(b), &ldb, w, traits::complex_ptr(work),
            &lwork, rwork, &lrwork, iwork, &liwork, &info );
}
} // namespace detail

// value-type based template
template< typename ValueType >
struct hegvd_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorW,
            typename WORK, typename RWORK, typename IWORK >
    static void invoke( const integer_t itype, const char jobz,
            const integer_t n, MatrixA& a, MatrixB& b, VectorW& w,
            integer_t& info, detail::workspace3< WORK, RWORK, IWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
        BOOST_ASSERT( traits::matrix_uplo_tag(a) == 'U' ||
                traits::matrix_uplo_tag(a) == 'L' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max<
                std::ptrdiff_t >(1,n) );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max<
                std::ptrdiff_t >(1,n) );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( jobz, n ));
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_rwork( jobz, n ));
        BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
                min_size_iwork( jobz, n ));
        detail::hegvd( itype, jobz, traits::matrix_uplo_tag(a), n,
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::vector_storage(w),
                traits::vector_storage(work.select(value_type())),
                traits::vector_size(work.select(value_type())),
                traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())),
                traits::vector_storage(work.select(integer_t())),
                traits::vector_size(work.select(integer_t())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorW >
    static void invoke( const integer_t itype, const char jobz,
            const integer_t n, MatrixA& a, MatrixB& b, VectorW& w,
            integer_t& info, minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work( jobz,
                n ) );
        traits::detail::array< real_type > tmp_rwork( min_size_rwork( jobz,
                n ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork( jobz,
                n ) );
        invoke( itype, jobz, n, a, b, w, info, workspace( tmp_work, tmp_rwork,
                tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorW >
    static void invoke( const integer_t itype, const char jobz,
            const integer_t n, MatrixA& a, MatrixB& b, VectorW& w,
            integer_t& info, optimal_workspace work ) {
        value_type opt_size_work;
        real_type opt_size_rwork;
        integer_t opt_size_iwork;
        detail::hegvd( itype, jobz, traits::matrix_uplo_tag(a), n,
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::vector_storage(w), &opt_size_work, -1,
                &opt_size_rwork, -1, &opt_size_iwork, -1, info );
        traits::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        traits::detail::array< real_type > tmp_rwork(
                traits::detail::to_int( opt_size_rwork ) );
        traits::detail::array< integer_t > tmp_iwork( opt_size_iwork );
        invoke( itype, jobz, n, a, b, w, info, workspace( tmp_work, tmp_rwork,
                tmp_iwork ) );
    }

    static integer_t min_size_work( const char jobz, const integer_t n ) {
        if ( n < 2 )
            return 1;
        else {
            if ( jobz == 'N' )
                return n+1;
            else
                return 2*n + n*n;
        }
    }

    static integer_t min_size_rwork( const char jobz, const integer_t n ) {
        if ( n < 2 )
            return 1;
        else {
            if ( jobz == 'N' )
                return n;
            else
                return 1 + 5*n + 2*n*n;
        }
    }

    static integer_t min_size_iwork( const char jobz, const integer_t n ) {
        if ( jobz == 'N' || n < 2 )
            return 1;
        else
            return 3 + 5*n;
    }
};


// template function to call hegvd
template< typename MatrixA, typename MatrixB, typename VectorW,
        typename Workspace >
inline integer_t hegvd( const integer_t itype, const char jobz,
        const integer_t n, MatrixA& a, MatrixB& b, VectorW& w,
        Workspace work ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    hegvd_impl< value_type >::invoke( itype, jobz, n, a, b, w, info,
            work );
    return info;
}

// template function to call hegvd, default workspace type
template< typename MatrixA, typename MatrixB, typename VectorW >
inline integer_t hegvd( const integer_t itype, const char jobz,
        const integer_t n, MatrixA& a, MatrixB& b, VectorW& w ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    hegvd_impl< value_type >::invoke( itype, jobz, n, a, b, w, info,
            optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
