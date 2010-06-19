//
// Copyright (c) 2002--2010
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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GTRFS_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GTRFS_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_column_major.hpp>
#include <boost/numeric/bindings/is_complex.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/is_real.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

//
// The LAPACK-backend for gtrfs is the netlib-compatible backend.
//
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/detail/lapack_option.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//
// The detail namespace contains value-type-overloaded functions that
// dispatch to the appropriate back-end LAPACK-routine.
//
namespace detail {

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * float value-type.
//
template< typename Trans >
inline std::ptrdiff_t gtrfs( const Trans trans, const fortran_int_t n,
        const fortran_int_t nrhs, const float* dl, const float* d,
        const float* du, const float* dlf, const float* df, const float* duf,
        const float* du2, const fortran_int_t* ipiv, const float* b,
        const fortran_int_t ldb, float* x, const fortran_int_t ldx,
        float* ferr, float* berr, float* work, fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_SGTRFS( &lapack_option< Trans >::value, &n, &nrhs, dl, d, du, dlf,
            df, duf, du2, ipiv, b, &ldb, x, &ldx, ferr, berr, work, iwork,
            &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
template< typename Trans >
inline std::ptrdiff_t gtrfs( const Trans trans, const fortran_int_t n,
        const fortran_int_t nrhs, const double* dl, const double* d,
        const double* du, const double* dlf, const double* df,
        const double* duf, const double* du2, const fortran_int_t* ipiv,
        const double* b, const fortran_int_t ldb, double* x,
        const fortran_int_t ldx, double* ferr, double* berr, double* work,
        fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_DGTRFS( &lapack_option< Trans >::value, &n, &nrhs, dl, d, du, dlf,
            df, duf, du2, ipiv, b, &ldb, x, &ldx, ferr, berr, work, iwork,
            &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
template< typename Trans >
inline std::ptrdiff_t gtrfs( const Trans trans, const fortran_int_t n,
        const fortran_int_t nrhs, const std::complex<float>* dl,
        const std::complex<float>* d, const std::complex<float>* du,
        const std::complex<float>* dlf, const std::complex<float>* df,
        const std::complex<float>* duf, const std::complex<float>* du2,
        const fortran_int_t* ipiv, const std::complex<float>* b,
        const fortran_int_t ldb, std::complex<float>* x,
        const fortran_int_t ldx, float* ferr, float* berr,
        std::complex<float>* work, float* rwork ) {
    fortran_int_t info(0);
    LAPACK_CGTRFS( &lapack_option< Trans >::value, &n, &nrhs, dl, d, du, dlf,
            df, duf, du2, ipiv, b, &ldb, x, &ldx, ferr, berr, work, rwork,
            &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename Trans >
inline std::ptrdiff_t gtrfs( const Trans trans, const fortran_int_t n,
        const fortran_int_t nrhs, const std::complex<double>* dl,
        const std::complex<double>* d, const std::complex<double>* du,
        const std::complex<double>* dlf, const std::complex<double>* df,
        const std::complex<double>* duf, const std::complex<double>* du2,
        const fortran_int_t* ipiv, const std::complex<double>* b,
        const fortran_int_t ldb, std::complex<double>* x,
        const fortran_int_t ldx, double* ferr, double* berr,
        std::complex<double>* work, double* rwork ) {
    fortran_int_t info(0);
    LAPACK_ZGTRFS( &lapack_option< Trans >::value, &n, &nrhs, dl, d, du, dlf,
            df, duf, du2, ipiv, b, &ldb, x, &ldx, ferr, berr, work, rwork,
            &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to gtrfs.
//
template< typename Value, typename Enable = void >
struct gtrfs_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct gtrfs_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorDL, typename VectorD, typename VectorDU,
            typename VectorDLF, typename VectorDF, typename VectorDUF,
            typename VectorDU2, typename VectorIPIV, typename MatrixB,
            typename MatrixX, typename VectorFERR, typename VectorBERR,
            typename WORK, typename IWORK >
    static std::ptrdiff_t invoke( const fortran_int_t n,
            const VectorDL& dl, const VectorD& d, const VectorDU& du,
            const VectorDLF& dlf, const VectorDF& df, const VectorDUF& duf,
            const VectorDU2& du2, const VectorIPIV& ipiv, const MatrixB& b,
            MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            detail::workspace2< WORK, IWORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixB >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixX >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorD >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorDU >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorDLF >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorDF >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorDUF >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorDU2 >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixX >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorFERR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorBERR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixX >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorFERR >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorBERR >::value) );
        BOOST_ASSERT( bindings::size(berr) >= bindings::size_column(b) );
        BOOST_ASSERT( bindings::size(d) >= n );
        BOOST_ASSERT( bindings::size(df) >= n );
        BOOST_ASSERT( bindings::size(dl) >= n-1 );
        BOOST_ASSERT( bindings::size(dlf) >= n-1 );
        BOOST_ASSERT( bindings::size(du) >= n-1 );
        BOOST_ASSERT( bindings::size(du2) >= n-2 );
        BOOST_ASSERT( bindings::size(duf) >= n-1 );
        BOOST_ASSERT( bindings::size(ipiv) >= n );
        BOOST_ASSERT( bindings::size(work.select(fortran_int_t())) >=
                min_size_iwork( n ));
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work( n ));
        BOOST_ASSERT( bindings::size_column(b) >= 0 );
        BOOST_ASSERT( bindings::size_minor(b) == 1 ||
                bindings::stride_minor(b) == 1 );
        BOOST_ASSERT( bindings::size_minor(x) == 1 ||
                bindings::stride_minor(x) == 1 );
        BOOST_ASSERT( bindings::stride_major(b) >= std::max< std::ptrdiff_t >(1,
                n) );
        BOOST_ASSERT( bindings::stride_major(x) >= std::max< std::ptrdiff_t >(1,
                n) );
        BOOST_ASSERT( n >= 0 );
        return detail::gtrfs( trans(), n, bindings::size_column(b),
                bindings::begin_value(dl), bindings::begin_value(d),
                bindings::begin_value(du), bindings::begin_value(dlf),
                bindings::begin_value(df), bindings::begin_value(duf),
                bindings::begin_value(du2), bindings::begin_value(ipiv),
                bindings::begin_value(b), bindings::stride_major(b),
                bindings::begin_value(x), bindings::stride_major(x),
                bindings::begin_value(ferr), bindings::begin_value(berr),
                bindings::begin_value(work.select(real_type())),
                bindings::begin_value(work.select(fortran_int_t())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename VectorDL, typename VectorD, typename VectorDU,
            typename VectorDLF, typename VectorDF, typename VectorDUF,
            typename VectorDU2, typename VectorIPIV, typename MatrixB,
            typename MatrixX, typename VectorFERR, typename VectorBERR >
    static std::ptrdiff_t invoke( const fortran_int_t n,
            const VectorDL& dl, const VectorD& d, const VectorDU& du,
            const VectorDLF& dlf, const VectorDF& df, const VectorDUF& duf,
            const VectorDU2& du2, const VectorIPIV& ipiv, const MatrixB& b,
            MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            minimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< real_type > tmp_work( min_size_work( n ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( n ) );
        return invoke( n, dl, d, du, dlf, df, duf, du2, ipiv, b, x, ferr,
                berr, workspace( tmp_work, tmp_iwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename VectorDL, typename VectorD, typename VectorDU,
            typename VectorDLF, typename VectorDF, typename VectorDUF,
            typename VectorDU2, typename VectorIPIV, typename MatrixB,
            typename MatrixX, typename VectorFERR, typename VectorBERR >
    static std::ptrdiff_t invoke( const fortran_int_t n,
            const VectorDL& dl, const VectorD& d, const VectorDU& du,
            const VectorDLF& dlf, const VectorDF& df, const VectorDUF& duf,
            const VectorDU2& du2, const VectorIPIV& ipiv, const MatrixB& b,
            MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            optimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        return invoke( n, dl, d, du, dlf, df, duf, du2, ipiv, b, x, ferr,
                berr, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return 3*n;
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array iwork.
    //
    static std::ptrdiff_t min_size_iwork( const std::ptrdiff_t n ) {
        return n;
    }
};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct gtrfs_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorDL, typename VectorD, typename VectorDU,
            typename VectorDLF, typename VectorDF, typename VectorDUF,
            typename VectorDU2, typename VectorIPIV, typename MatrixB,
            typename MatrixX, typename VectorFERR, typename VectorBERR,
            typename WORK, typename RWORK >
    static std::ptrdiff_t invoke( const fortran_int_t n,
            const VectorDL& dl, const VectorD& d, const VectorDU& du,
            const VectorDLF& dlf, const VectorDF& df, const VectorDUF& duf,
            const VectorDU2& du2, const VectorIPIV& ipiv, const MatrixB& b,
            MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            detail::workspace2< WORK, RWORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixB >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixX >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorFERR >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorBERR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorD >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorDU >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorDLF >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorDF >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorDUF >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorDU2 >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixX >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixX >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorFERR >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorBERR >::value) );
        BOOST_ASSERT( bindings::size(berr) >= bindings::size_column(b) );
        BOOST_ASSERT( bindings::size(d) >= n );
        BOOST_ASSERT( bindings::size(df) >= n );
        BOOST_ASSERT( bindings::size(dl) >= n-1 );
        BOOST_ASSERT( bindings::size(dlf) >= n-1 );
        BOOST_ASSERT( bindings::size(du) >= n-1 );
        BOOST_ASSERT( bindings::size(du2) >= n-2 );
        BOOST_ASSERT( bindings::size(duf) >= n-1 );
        BOOST_ASSERT( bindings::size(ipiv) >= n );
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_rwork( n ));
        BOOST_ASSERT( bindings::size(work.select(value_type())) >=
                min_size_work( n ));
        BOOST_ASSERT( bindings::size_column(b) >= 0 );
        BOOST_ASSERT( bindings::size_minor(b) == 1 ||
                bindings::stride_minor(b) == 1 );
        BOOST_ASSERT( bindings::size_minor(x) == 1 ||
                bindings::stride_minor(x) == 1 );
        BOOST_ASSERT( bindings::stride_major(b) >= std::max< std::ptrdiff_t >(1,
                n) );
        BOOST_ASSERT( bindings::stride_major(x) >= std::max< std::ptrdiff_t >(1,
                n) );
        BOOST_ASSERT( n >= 0 );
        return detail::gtrfs( trans(), n, bindings::size_column(b),
                bindings::begin_value(dl), bindings::begin_value(d),
                bindings::begin_value(du), bindings::begin_value(dlf),
                bindings::begin_value(df), bindings::begin_value(duf),
                bindings::begin_value(du2), bindings::begin_value(ipiv),
                bindings::begin_value(b), bindings::stride_major(b),
                bindings::begin_value(x), bindings::stride_major(x),
                bindings::begin_value(ferr), bindings::begin_value(berr),
                bindings::begin_value(work.select(value_type())),
                bindings::begin_value(work.select(real_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename VectorDL, typename VectorD, typename VectorDU,
            typename VectorDLF, typename VectorDF, typename VectorDUF,
            typename VectorDU2, typename VectorIPIV, typename MatrixB,
            typename MatrixX, typename VectorFERR, typename VectorBERR >
    static std::ptrdiff_t invoke( const fortran_int_t n,
            const VectorDL& dl, const VectorD& d, const VectorDU& du,
            const VectorDLF& dlf, const VectorDF& df, const VectorDUF& duf,
            const VectorDU2& du2, const VectorIPIV& ipiv, const MatrixB& b,
            MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            minimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< value_type > tmp_work( min_size_work( n ) );
        bindings::detail::array< real_type > tmp_rwork( min_size_rwork( n ) );
        return invoke( n, dl, d, du, dlf, df, duf, du2, ipiv, b, x, ferr,
                berr, workspace( tmp_work, tmp_rwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename VectorDL, typename VectorD, typename VectorDU,
            typename VectorDLF, typename VectorDF, typename VectorDUF,
            typename VectorDU2, typename VectorIPIV, typename MatrixB,
            typename MatrixX, typename VectorFERR, typename VectorBERR >
    static std::ptrdiff_t invoke( const fortran_int_t n,
            const VectorDL& dl, const VectorD& d, const VectorDU& du,
            const VectorDLF& dlf, const VectorDF& df, const VectorDUF& duf,
            const VectorDU2& du2, const VectorIPIV& ipiv, const MatrixB& b,
            MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            optimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        return invoke( n, dl, d, du, dlf, df, duf, du2, ipiv, b, x, ferr,
                berr, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return 2*n;
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array rwork.
    //
    static std::ptrdiff_t min_size_rwork( const std::ptrdiff_t n ) {
        return n;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the gtrfs_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for gtrfs. Its overload differs for
// * MatrixX&
// * User-defined workspace
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename VectorDLF, typename VectorDF, typename VectorDUF,
        typename VectorDU2, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename VectorFERR, typename VectorBERR,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
gtrfs( const fortran_int_t n, const VectorDL& dl, const VectorD& d,
        const VectorDU& du, const VectorDLF& dlf, const VectorDF& df,
        const VectorDUF& duf, const VectorDU2& du2, const VectorIPIV& ipiv,
        const MatrixB& b, MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
        Workspace work ) {
    return gtrfs_impl< typename bindings::value_type<
            VectorDL >::type >::invoke( n, dl, d, du, dlf, df, duf, du2, ipiv,
            b, x, ferr, berr, work );
}

//
// Overloaded function for gtrfs. Its overload differs for
// * MatrixX&
// * Default workspace-type (optimal)
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename VectorDLF, typename VectorDF, typename VectorDUF,
        typename VectorDU2, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename VectorFERR, typename VectorBERR >
inline typename boost::disable_if< detail::is_workspace< VectorBERR >,
        std::ptrdiff_t >::type
gtrfs( const fortran_int_t n, const VectorDL& dl, const VectorD& d,
        const VectorDU& du, const VectorDLF& dlf, const VectorDF& df,
        const VectorDUF& duf, const VectorDU2& du2, const VectorIPIV& ipiv,
        const MatrixB& b, MatrixX& x, VectorFERR& ferr, VectorBERR& berr ) {
    return gtrfs_impl< typename bindings::value_type<
            VectorDL >::type >::invoke( n, dl, d, du, dlf, df, duf, du2, ipiv,
            b, x, ferr, berr, optimal_workspace() );
}

//
// Overloaded function for gtrfs. Its overload differs for
// * const MatrixX&
// * User-defined workspace
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename VectorDLF, typename VectorDF, typename VectorDUF,
        typename VectorDU2, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename VectorFERR, typename VectorBERR,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
gtrfs( const fortran_int_t n, const VectorDL& dl, const VectorD& d,
        const VectorDU& du, const VectorDLF& dlf, const VectorDF& df,
        const VectorDUF& duf, const VectorDU2& du2, const VectorIPIV& ipiv,
        const MatrixB& b, const MatrixX& x, VectorFERR& ferr,
        VectorBERR& berr, Workspace work ) {
    return gtrfs_impl< typename bindings::value_type<
            VectorDL >::type >::invoke( n, dl, d, du, dlf, df, duf, du2, ipiv,
            b, x, ferr, berr, work );
}

//
// Overloaded function for gtrfs. Its overload differs for
// * const MatrixX&
// * Default workspace-type (optimal)
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename VectorDLF, typename VectorDF, typename VectorDUF,
        typename VectorDU2, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename VectorFERR, typename VectorBERR >
inline typename boost::disable_if< detail::is_workspace< VectorBERR >,
        std::ptrdiff_t >::type
gtrfs( const fortran_int_t n, const VectorDL& dl, const VectorD& d,
        const VectorDU& du, const VectorDLF& dlf, const VectorDF& df,
        const VectorDUF& duf, const VectorDU2& du2, const VectorIPIV& ipiv,
        const MatrixB& b, const MatrixX& x, VectorFERR& ferr,
        VectorBERR& berr ) {
    return gtrfs_impl< typename bindings::value_type<
            VectorDL >::type >::invoke( n, dl, d, du, dlf, df, duf, du2, ipiv,
            b, x, ferr, berr, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
