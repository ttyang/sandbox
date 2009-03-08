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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_GTRFS_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_GTRFS_HPP

#include <boost/numeric/bindings/lapack/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/is_complex.hpp>
#include <boost/numeric/bindings/traits/is_real.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <cassert>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void gtrfs( char const trans, integer_t const n,
            integer_t const nrhs, float* dl, float* d, float* du, float* dlf,
            float* df, float* duf, float* du2, integer_t* ipiv, float* b,
            integer_t const ldb, float* x, integer_t const ldx, float* ferr,
            float* berr, float* work, integer_t* iwork, integer_t& info ) {
        LAPACK_SGTRFS( &trans, &n, &nrhs, dl, d, du, dlf, df, duf, du2, ipiv,
                b, &ldb, x, &ldx, ferr, berr, work, iwork, &info );
    }
    inline void gtrfs( char const trans, integer_t const n,
            integer_t const nrhs, double* dl, double* d, double* du,
            double* dlf, double* df, double* duf, double* du2,
            integer_t* ipiv, double* b, integer_t const ldb, double* x,
            integer_t const ldx, double* ferr, double* berr, double* work,
            integer_t* iwork, integer_t& info ) {
        LAPACK_DGTRFS( &trans, &n, &nrhs, dl, d, du, dlf, df, duf, du2, ipiv,
                b, &ldb, x, &ldx, ferr, berr, work, iwork, &info );
    }
    inline void gtrfs( char const trans, integer_t const n,
            integer_t const nrhs, traits::complex_f* dl, traits::complex_f* d,
            traits::complex_f* du, traits::complex_f* dlf,
            traits::complex_f* df, traits::complex_f* duf,
            traits::complex_f* du2, integer_t* ipiv, traits::complex_f* b,
            integer_t const ldb, traits::complex_f* x, integer_t const ldx,
            float* ferr, float* berr, traits::complex_f* work, float* rwork,
            integer_t& info ) {
        LAPACK_CGTRFS( &trans, &n, &nrhs, traits::complex_ptr(dl),
                traits::complex_ptr(d), traits::complex_ptr(du),
                traits::complex_ptr(dlf), traits::complex_ptr(df),
                traits::complex_ptr(duf), traits::complex_ptr(du2), ipiv,
                traits::complex_ptr(b), &ldb, traits::complex_ptr(x), &ldx,
                ferr, berr, traits::complex_ptr(work), rwork, &info );
    }
    inline void gtrfs( char const trans, integer_t const n,
            integer_t const nrhs, traits::complex_d* dl, traits::complex_d* d,
            traits::complex_d* du, traits::complex_d* dlf,
            traits::complex_d* df, traits::complex_d* duf,
            traits::complex_d* du2, integer_t* ipiv, traits::complex_d* b,
            integer_t const ldb, traits::complex_d* x, integer_t const ldx,
            double* ferr, double* berr, traits::complex_d* work,
            double* rwork, integer_t& info ) {
        LAPACK_ZGTRFS( &trans, &n, &nrhs, traits::complex_ptr(dl),
                traits::complex_ptr(d), traits::complex_ptr(du),
                traits::complex_ptr(dlf), traits::complex_ptr(df),
                traits::complex_ptr(duf), traits::complex_ptr(du2), ipiv,
                traits::complex_ptr(b), &ldb, traits::complex_ptr(x), &ldx,
                ferr, berr, traits::complex_ptr(work), rwork, &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct gtrfs_impl{};

// real specialization
template< typename ValueType >
struct gtrfs_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename VectorDL, typename VectorD, typename VectorDU,
            typename VectorDLF, typename VectorDF, typename VectorDUF,
            typename VectorDU2, typename VectorIPIV, typename MatrixB,
            typename MatrixX, typename VectorFERR, typename VectorBERR,
            typename WORK, typename IWORK >
    static void compute( char const trans, integer_t const n, VectorDL& dl,
            VectorD& d, VectorDU& du, VectorDLF& dlf, VectorDF& df,
            VectorDUF& duf, VectorDU2& du2, VectorIPIV& ipiv, MatrixB& b,
            MatrixX& x, VectorFERR& ferr, VectorBERR& berr, integer_t& info,
            detail::workspace2< WORK, IWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::vector_traits<
                VectorD >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::vector_traits<
                VectorDU >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::vector_traits<
                VectorDLF >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::vector_traits<
                VectorDF >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::vector_traits<
                VectorDUF >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::vector_traits<
                VectorDU2 >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::matrix_traits<
                MatrixX >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::vector_traits<
                VectorFERR >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::vector_traits<
                VectorBERR >::value_type >::value) );
#ifndef NDEBUG
        assert( trans == 'N' || trans == 'T' || trans == 'C' );
        assert( n >= 0 );
        assert( traits::matrix_size2(b) >= 0 );
        assert( traits::vector_size(dl) >= n-1 );
        assert( traits::vector_size(d) >= n );
        assert( traits::vector_size(du) >= n-1 );
        assert( traits::vector_size(dlf) >= n-1 );
        assert( traits::vector_size(df) >= n );
        assert( traits::vector_size(duf) >= n-1 );
        assert( traits::vector_size(du2) >= n-2 );
        assert( traits::vector_size(ipiv) >= n );
        assert( traits::leading_dimension(b) >= std::max(1,n) );
        assert( traits::leading_dimension(x) >= std::max(1,n) );
        assert( traits::vector_size(berr) >= traits::matrix_size2(b) );
        assert( traits::vector_size(work.select(real_type()) >= min_size_work(
                n )));
        assert( traits::vector_size(work.select(integer_t()) >=
                min_size_iwork( n )));
#endif
        detail::gtrfs( trans, n, traits::matrix_size2(b),
                traits::vector_storage(dl), traits::vector_storage(d),
                traits::vector_storage(du), traits::vector_storage(dlf),
                traits::vector_storage(df), traits::vector_storage(duf),
                traits::vector_storage(du2), traits::vector_storage(ipiv),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::matrix_storage(x), traits::leading_dimension(x),
                traits::vector_storage(ferr), traits::vector_storage(berr),
                traits::vector_storage(work.select(real_type())),
                traits::vector_storage(work.select(integer_t())), info );
    }

    // minimal workspace specialization
    template< typename VectorDL, typename VectorD, typename VectorDU,
            typename VectorDLF, typename VectorDF, typename VectorDUF,
            typename VectorDU2, typename VectorIPIV, typename MatrixB,
            typename MatrixX, typename VectorFERR, typename VectorBERR >
    static void compute( char const trans, integer_t const n, VectorDL& dl,
            VectorD& d, VectorDU& du, VectorDLF& dlf, VectorDF& df,
            VectorDUF& duf, VectorDU2& du2, VectorIPIV& ipiv, MatrixB& b,
            MatrixX& x, VectorFERR& ferr, VectorBERR& berr, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work( n ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork( n ) );
        compute( trans, n, dl, d, du, dlf, df, duf, du2, ipiv, b, x, ferr,
                berr, info, workspace( tmp_work, tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename VectorDL, typename VectorD, typename VectorDU,
            typename VectorDLF, typename VectorDF, typename VectorDUF,
            typename VectorDU2, typename VectorIPIV, typename MatrixB,
            typename MatrixX, typename VectorFERR, typename VectorBERR >
    static void compute( char const trans, integer_t const n, VectorDL& dl,
            VectorD& d, VectorDU& du, VectorDLF& dlf, VectorDF& df,
            VectorDUF& duf, VectorDU2& du2, VectorIPIV& ipiv, MatrixB& b,
            MatrixX& x, VectorFERR& ferr, VectorBERR& berr, integer_t& info,
            optimal_workspace work ) {
        compute( trans, n, dl, d, du, dlf, df, duf, du2, ipiv, b, x, ferr,
                berr, info, minimal_workspace() );
    }

    static integer_t min_size_work( integer_t const n ) {
        return 3*n;
    }

    static integer_t min_size_iwork( integer_t const n ) {
        return n;
    }
};

// complex specialization
template< typename ValueType >
struct gtrfs_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename VectorDL, typename VectorD, typename VectorDU,
            typename VectorDLF, typename VectorDF, typename VectorDUF,
            typename VectorDU2, typename VectorIPIV, typename MatrixB,
            typename MatrixX, typename VectorFERR, typename VectorBERR,
            typename WORK, typename RWORK >
    static void compute( char const trans, integer_t const n, VectorDL& dl,
            VectorD& d, VectorDU& du, VectorDLF& dlf, VectorDF& df,
            VectorDUF& duf, VectorDU2& du2, VectorIPIV& ipiv, MatrixB& b,
            MatrixX& x, VectorFERR& ferr, VectorBERR& berr, integer_t& info,
            detail::workspace2< WORK, RWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorFERR >::value_type, typename traits::vector_traits<
                VectorBERR >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::vector_traits<
                VectorD >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::vector_traits<
                VectorDU >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::vector_traits<
                VectorDLF >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::vector_traits<
                VectorDF >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::vector_traits<
                VectorDUF >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::vector_traits<
                VectorDU2 >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::matrix_traits<
                MatrixX >::value_type >::value) );
#ifndef NDEBUG
        assert( trans == 'N' || trans == 'T' || trans == 'C' );
        assert( n >= 0 );
        assert( traits::matrix_size2(b) >= 0 );
        assert( traits::vector_size(dl) >= n-1 );
        assert( traits::vector_size(d) >= n );
        assert( traits::vector_size(du) >= n-1 );
        assert( traits::vector_size(dlf) >= n-1 );
        assert( traits::vector_size(df) >= n );
        assert( traits::vector_size(duf) >= n-1 );
        assert( traits::vector_size(du2) >= n-2 );
        assert( traits::vector_size(ipiv) >= n );
        assert( traits::leading_dimension(b) >= std::max(1,n) );
        assert( traits::leading_dimension(x) >= std::max(1,n) );
        assert( traits::vector_size(berr) >= traits::matrix_size2(b) );
        assert( traits::vector_size(work.select(value_type()) >=
                min_size_work( n )));
        assert( traits::vector_size(work.select(real_type()) >=
                min_size_rwork( n )));
#endif
        detail::gtrfs( trans, n, traits::matrix_size2(b),
                traits::vector_storage(dl), traits::vector_storage(d),
                traits::vector_storage(du), traits::vector_storage(dlf),
                traits::vector_storage(df), traits::vector_storage(duf),
                traits::vector_storage(du2), traits::vector_storage(ipiv),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::matrix_storage(x), traits::leading_dimension(x),
                traits::vector_storage(ferr), traits::vector_storage(berr),
                traits::vector_storage(work.select(value_type())),
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename VectorDL, typename VectorD, typename VectorDU,
            typename VectorDLF, typename VectorDF, typename VectorDUF,
            typename VectorDU2, typename VectorIPIV, typename MatrixB,
            typename MatrixX, typename VectorFERR, typename VectorBERR >
    static void compute( char const trans, integer_t const n, VectorDL& dl,
            VectorD& d, VectorDU& du, VectorDLF& dlf, VectorDF& df,
            VectorDUF& duf, VectorDU2& du2, VectorIPIV& ipiv, MatrixB& b,
            MatrixX& x, VectorFERR& ferr, VectorBERR& berr, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work( n ) );
        traits::detail::array< real_type > tmp_rwork( min_size_rwork( n ) );
        compute( trans, n, dl, d, du, dlf, df, duf, du2, ipiv, b, x, ferr,
                berr, info, workspace( tmp_work, tmp_rwork ) );
    }

    // optimal workspace specialization
    template< typename VectorDL, typename VectorD, typename VectorDU,
            typename VectorDLF, typename VectorDF, typename VectorDUF,
            typename VectorDU2, typename VectorIPIV, typename MatrixB,
            typename MatrixX, typename VectorFERR, typename VectorBERR >
    static void compute( char const trans, integer_t const n, VectorDL& dl,
            VectorD& d, VectorDU& du, VectorDLF& dlf, VectorDF& df,
            VectorDUF& duf, VectorDU2& du2, VectorIPIV& ipiv, MatrixB& b,
            MatrixX& x, VectorFERR& ferr, VectorBERR& berr, integer_t& info,
            optimal_workspace work ) {
        compute( trans, n, dl, d, du, dlf, df, duf, du2, ipiv, b, x, ferr,
                berr, info, minimal_workspace() );
    }

    static integer_t min_size_work( integer_t const n ) {
        return 2*n;
    }

    static integer_t min_size_rwork( integer_t const n ) {
        return n;
    }
};


// template function to call gtrfs
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename VectorDLF, typename VectorDF, typename VectorDUF,
        typename VectorDU2, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename VectorFERR, typename VectorBERR,
        typename Workspace >
inline integer_t gtrfs( char const trans, integer_t const n,
        VectorDL& dl, VectorD& d, VectorDU& du, VectorDLF& dlf, VectorDF& df,
        VectorDUF& duf, VectorDU2& du2, VectorIPIV& ipiv, MatrixB& b,
        MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
        Workspace work = optimal_workspace() ) {
    typedef typename traits::vector_traits< VectorDL >::value_type value_type;
    integer_t info(0);
    gtrfs_impl< value_type >::compute( trans, n, dl, d, du, dlf, df, duf,
            du2, ipiv, b, x, ferr, berr, info, work );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
