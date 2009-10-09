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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_HESVX_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_HESVX_HPP

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

inline void hesvx( const char fact, const char uplo, const integer_t n,
        const integer_t nrhs, const traits::complex_f* a, const integer_t lda,
        traits::complex_f* af, const integer_t ldaf, integer_t* ipiv,
        const traits::complex_f* b, const integer_t ldb, traits::complex_f* x,
        const integer_t ldx, float& rcond, float* ferr, float* berr,
        traits::complex_f* work, const integer_t lwork, float* rwork,
        integer_t& info ) {
    LAPACK_CHESVX( &fact, &uplo, &n, &nrhs, traits::complex_ptr(a), &lda,
            traits::complex_ptr(af), &ldaf, ipiv, traits::complex_ptr(b),
            &ldb, traits::complex_ptr(x), &ldx, &rcond, ferr, berr,
            traits::complex_ptr(work), &lwork, rwork, &info );
}
inline void hesvx( const char fact, const char uplo, const integer_t n,
        const integer_t nrhs, const traits::complex_d* a, const integer_t lda,
        traits::complex_d* af, const integer_t ldaf, integer_t* ipiv,
        const traits::complex_d* b, const integer_t ldb, traits::complex_d* x,
        const integer_t ldx, double& rcond, double* ferr, double* berr,
        traits::complex_d* work, const integer_t lwork, double* rwork,
        integer_t& info ) {
    LAPACK_ZHESVX( &fact, &uplo, &n, &nrhs, traits::complex_ptr(a), &lda,
            traits::complex_ptr(af), &ldaf, ipiv, traits::complex_ptr(b),
            &ldb, traits::complex_ptr(x), &ldx, &rcond, ferr, berr,
            traits::complex_ptr(work), &lwork, rwork, &info );
}
} // namespace detail

// value-type based template
template< typename ValueType >
struct hesvx_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
            typename MatrixB, typename MatrixX, typename VectorFERR,
            typename VectorBERR, typename WORK, typename RWORK >
    static void invoke( const char fact, const MatrixA& a, MatrixAF& af,
            VectorIPIV& ipiv, const MatrixB& b, MatrixX& x, real_type& rcond,
            VectorFERR& ferr, VectorBERR& berr, integer_t& info,
            detail::workspace2< WORK, RWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorFERR >::value_type, typename traits::vector_traits<
                VectorBERR >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixAF >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixX >::value_type >::value) );
        BOOST_ASSERT( fact == 'F' || fact == 'N' );
        BOOST_ASSERT( traits::matrix_uplo_tag(a) == 'U' ||
                traits::matrix_uplo_tag(a) == 'L' );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(x) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max<
                std::ptrdiff_t >(1,traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::leading_dimension(af) >= std::max<
                std::ptrdiff_t >(1,traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max<
                std::ptrdiff_t >(1,traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::leading_dimension(x) >= std::max<
                std::ptrdiff_t >(1,traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(berr) >=
                traits::matrix_num_columns(x) );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( traits::matrix_num_columns(a) ));
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_rwork( traits::matrix_num_columns(a) ));
        detail::hesvx( fact, traits::matrix_uplo_tag(a),
                traits::matrix_num_columns(a), traits::matrix_num_columns(x),
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(af), traits::leading_dimension(af),
                traits::vector_storage(ipiv), traits::matrix_storage(b),
                traits::leading_dimension(b), traits::matrix_storage(x),
                traits::leading_dimension(x), rcond,
                traits::vector_storage(ferr), traits::vector_storage(berr),
                traits::vector_storage(work.select(value_type())),
                traits::vector_size(work.select(value_type())),
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
            typename MatrixB, typename MatrixX, typename VectorFERR,
            typename VectorBERR >
    static void invoke( const char fact, const MatrixA& a, MatrixAF& af,
            VectorIPIV& ipiv, const MatrixB& b, MatrixX& x, real_type& rcond,
            VectorFERR& ferr, VectorBERR& berr, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work(
                traits::matrix_num_columns(a) ) );
        traits::detail::array< real_type > tmp_rwork( min_size_rwork(
                traits::matrix_num_columns(a) ) );
        invoke( fact, a, af, ipiv, b, x, rcond, ferr, berr, info,
                workspace( tmp_work, tmp_rwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
            typename MatrixB, typename MatrixX, typename VectorFERR,
            typename VectorBERR >
    static void invoke( const char fact, const MatrixA& a, MatrixAF& af,
            VectorIPIV& ipiv, const MatrixB& b, MatrixX& x, real_type& rcond,
            VectorFERR& ferr, VectorBERR& berr, integer_t& info,
            optimal_workspace work ) {
        value_type opt_size_work;
        traits::detail::array< real_type > tmp_rwork( min_size_rwork(
                traits::matrix_num_columns(a) ) );
        detail::hesvx( fact, traits::matrix_uplo_tag(a),
                traits::matrix_num_columns(a), traits::matrix_num_columns(x),
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(af), traits::leading_dimension(af),
                traits::vector_storage(ipiv), traits::matrix_storage(b),
                traits::leading_dimension(b), traits::matrix_storage(x),
                traits::leading_dimension(x), rcond,
                traits::vector_storage(ferr), traits::vector_storage(berr),
                &opt_size_work, -1, traits::vector_storage(tmp_rwork), info );
        traits::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        invoke( fact, a, af, ipiv, b, x, rcond, ferr, berr, info,
                workspace( tmp_work, tmp_rwork ) );
    }

    static integer_t min_size_work( const integer_t n ) {
        return std::max( 1, 2*n );
    }

    static integer_t min_size_rwork( const integer_t n ) {
        return n;
    }
};


// template function to call hesvx
template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
        typename MatrixB, typename MatrixX, typename VectorFERR,
        typename VectorBERR, typename Workspace >
inline integer_t hesvx( const char fact, const MatrixA& a, MatrixAF& af,
        VectorIPIV& ipiv, const MatrixB& b, MatrixX& x,
        typename traits::type_traits< typename traits::matrix_traits<
        MatrixA >::value_type >::real_type& rcond, VectorFERR& ferr,
        VectorBERR& berr, Workspace work ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    hesvx_impl< value_type >::invoke( fact, a, af, ipiv, b, x, rcond,
            ferr, berr, info, work );
    return info;
}

// template function to call hesvx, default workspace type
template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
        typename MatrixB, typename MatrixX, typename VectorFERR,
        typename VectorBERR >
inline integer_t hesvx( const char fact, const MatrixA& a, MatrixAF& af,
        VectorIPIV& ipiv, const MatrixB& b, MatrixX& x,
        typename traits::type_traits< typename traits::matrix_traits<
        MatrixA >::value_type >::real_type& rcond, VectorFERR& ferr,
        VectorBERR& berr ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    hesvx_impl< value_type >::invoke( fact, a, af, ipiv, b, x, rcond,
            ferr, berr, info, optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
