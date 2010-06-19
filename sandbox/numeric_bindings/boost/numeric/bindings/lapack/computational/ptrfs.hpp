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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_PTRFS_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_PTRFS_HPP

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
#include <boost/numeric/bindings/uplo_tag.hpp>
#include <boost/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

//
// The LAPACK-backend for ptrfs is the netlib-compatible backend.
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
inline std::ptrdiff_t ptrfs( const fortran_int_t n, const fortran_int_t nrhs,
        const float* d, const float* e, const float* df, const float* ef,
        const float* b, const fortran_int_t ldb, float* x,
        const fortran_int_t ldx, float* ferr, float* berr, float* work ) {
    fortran_int_t info(0);
    LAPACK_SPTRFS( &n, &nrhs, d, e, df, ef, b, &ldb, x, &ldx, ferr, berr,
            work, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t ptrfs( const fortran_int_t n, const fortran_int_t nrhs,
        const double* d, const double* e, const double* df, const double* ef,
        const double* b, const fortran_int_t ldb, double* x,
        const fortran_int_t ldx, double* ferr, double* berr, double* work ) {
    fortran_int_t info(0);
    LAPACK_DPTRFS( &n, &nrhs, d, e, df, ef, b, &ldb, x, &ldx, ferr, berr,
            work, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
inline std::ptrdiff_t ptrfs( const char uplo, const fortran_int_t n,
        const fortran_int_t nrhs, const float* d,
        const std::complex<float>* e, const float* df,
        const std::complex<float>* ef, const std::complex<float>* b,
        const fortran_int_t ldb, std::complex<float>* x,
        const fortran_int_t ldx, float* ferr, float* berr,
        std::complex<float>* work, float* rwork ) {
    fortran_int_t info(0);
    LAPACK_CPTRFS( &uplo, &n, &nrhs, d, e, df, ef, b, &ldb, x, &ldx, ferr,
            berr, work, rwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
inline std::ptrdiff_t ptrfs( const char uplo, const fortran_int_t n,
        const fortran_int_t nrhs, const double* d,
        const std::complex<double>* e, const double* df,
        const std::complex<double>* ef, const std::complex<double>* b,
        const fortran_int_t ldb, std::complex<double>* x,
        const fortran_int_t ldx, double* ferr, double* berr,
        std::complex<double>* work, double* rwork ) {
    fortran_int_t info(0);
    LAPACK_ZPTRFS( &uplo, &n, &nrhs, d, e, df, ef, b, &ldb, x, &ldx, ferr,
            berr, work, rwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to ptrfs.
//
template< typename Value, typename Enable = void >
struct ptrfs_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct ptrfs_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorD, typename VectorE, typename VectorDF,
            typename VectorEF, typename MatrixB, typename MatrixX,
            typename VectorFERR, typename VectorBERR, typename WORK >
    static std::ptrdiff_t invoke( const VectorD& d, const VectorE& e,
            const VectorDF& df, const VectorEF& ef, const MatrixB& b,
            MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            detail::workspace1< WORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixB >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixX >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorDF >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorEF >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixX >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorFERR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorBERR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixX >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorFERR >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorBERR >::value) );
        BOOST_ASSERT( bindings::size(berr) >= bindings::size_column(b) );
        BOOST_ASSERT( bindings::size(d) >= bindings::size(d) );
        BOOST_ASSERT( bindings::size(d) >= 0 );
        BOOST_ASSERT( bindings::size(df) >= bindings::size(d) );
        BOOST_ASSERT( bindings::size(e) >= bindings::size(d)-1 );
        BOOST_ASSERT( bindings::size(ef) >= bindings::size(d)-1 );
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work( bindings::size(d) ));
        BOOST_ASSERT( bindings::size_column(b) >= 0 );
        BOOST_ASSERT( bindings::size_minor(b) == 1 ||
                bindings::stride_minor(b) == 1 );
        BOOST_ASSERT( bindings::size_minor(x) == 1 ||
                bindings::stride_minor(x) == 1 );
        BOOST_ASSERT( bindings::stride_major(b) >= std::max< std::ptrdiff_t >(1,
                bindings::size(d)) );
        BOOST_ASSERT( bindings::stride_major(x) >= std::max< std::ptrdiff_t >(1,
                bindings::size(d)) );
        return detail::ptrfs( bindings::size(d), bindings::size_column(b),
                bindings::begin_value(d), bindings::begin_value(e),
                bindings::begin_value(df), bindings::begin_value(ef),
                bindings::begin_value(b), bindings::stride_major(b),
                bindings::begin_value(x), bindings::stride_major(x),
                bindings::begin_value(ferr), bindings::begin_value(berr),
                bindings::begin_value(work.select(real_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename VectorD, typename VectorE, typename VectorDF,
            typename VectorEF, typename MatrixB, typename MatrixX,
            typename VectorFERR, typename VectorBERR >
    static std::ptrdiff_t invoke( const VectorD& d, const VectorE& e,
            const VectorDF& df, const VectorEF& ef, const MatrixB& b,
            MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            minimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< real_type > tmp_work( min_size_work(
                bindings::size(d) ) );
        return invoke( d, e, df, ef, b, x, ferr, berr, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename VectorD, typename VectorE, typename VectorDF,
            typename VectorEF, typename MatrixB, typename MatrixX,
            typename VectorFERR, typename VectorBERR >
    static std::ptrdiff_t invoke( const VectorD& d, const VectorE& e,
            const VectorDF& df, const VectorEF& ef, const MatrixB& b,
            MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            optimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        return invoke( d, e, df, ef, b, x, ferr, berr, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return 2*n;
    }
};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct ptrfs_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorD, typename VectorE, typename VectorDF,
            typename VectorEF, typename MatrixB, typename MatrixX,
            typename VectorFERR, typename VectorBERR, typename WORK,
            typename RWORK >
    static std::ptrdiff_t invoke( const char uplo, const VectorD& d,
            const VectorE& e, const VectorDF& df, const VectorEF& ef,
            const MatrixB& b, MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            detail::workspace2< WORK, RWORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixB >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixX >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorDF >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorFERR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorBERR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorE >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorEF >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorE >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorE >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixX >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixX >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorFERR >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorBERR >::value) );
        BOOST_ASSERT( bindings::size(berr) >= bindings::size_column(b) );
        BOOST_ASSERT( bindings::size(d) >= bindings::size(d) );
        BOOST_ASSERT( bindings::size(d) >= 0 );
        BOOST_ASSERT( bindings::size(df) >= bindings::size(d) );
        BOOST_ASSERT( bindings::size(e) >= bindings::size(d)-1 );
        BOOST_ASSERT( bindings::size(ef) >= bindings::size(d)-1 );
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_rwork( bindings::size(d) ));
        BOOST_ASSERT( bindings::size(work.select(value_type())) >=
                min_size_work( bindings::size(d) ));
        BOOST_ASSERT( bindings::size_column(b) >= 0 );
        BOOST_ASSERT( bindings::size_minor(b) == 1 ||
                bindings::stride_minor(b) == 1 );
        BOOST_ASSERT( bindings::size_minor(x) == 1 ||
                bindings::stride_minor(x) == 1 );
        BOOST_ASSERT( bindings::stride_major(b) >= std::max< std::ptrdiff_t >(1,
                bindings::size(d)) );
        BOOST_ASSERT( bindings::stride_major(x) >= std::max< std::ptrdiff_t >(1,
                bindings::size(d)) );
        return detail::ptrfs( uplo, bindings::size(d),
                bindings::size_column(b), bindings::begin_value(d),
                bindings::begin_value(e), bindings::begin_value(df),
                bindings::begin_value(ef), bindings::begin_value(b),
                bindings::stride_major(b), bindings::begin_value(x),
                bindings::stride_major(x), bindings::begin_value(ferr),
                bindings::begin_value(berr),
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
    template< typename VectorD, typename VectorE, typename VectorDF,
            typename VectorEF, typename MatrixB, typename MatrixX,
            typename VectorFERR, typename VectorBERR >
    static std::ptrdiff_t invoke( const char uplo, const VectorD& d,
            const VectorE& e, const VectorDF& df, const VectorEF& ef,
            const MatrixB& b, MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            minimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< value_type > tmp_work( min_size_work(
                bindings::size(d) ) );
        bindings::detail::array< real_type > tmp_rwork( min_size_rwork(
                bindings::size(d) ) );
        return invoke( uplo, d, e, df, ef, b, x, ferr, berr,
                workspace( tmp_work, tmp_rwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename VectorD, typename VectorE, typename VectorDF,
            typename VectorEF, typename MatrixB, typename MatrixX,
            typename VectorFERR, typename VectorBERR >
    static std::ptrdiff_t invoke( const char uplo, const VectorD& d,
            const VectorE& e, const VectorDF& df, const VectorEF& ef,
            const MatrixB& b, MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            optimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        return invoke( uplo, d, e, df, ef, b, x, ferr, berr,
                minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return n;
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
// Calls to these functions are passed to the ptrfs_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for ptrfs. Its overload differs for
// * MatrixX&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename VectorDF,
        typename VectorEF, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
ptrfs( const VectorD& d, const VectorE& e, const VectorDF& df,
        const VectorEF& ef, const MatrixB& b, MatrixX& x, VectorFERR& ferr,
        VectorBERR& berr, Workspace work ) {
    return ptrfs_impl< typename bindings::value_type<
            VectorE >::type >::invoke( d, e, df, ef, b, x, ferr, berr, work );
}

//
// Overloaded function for ptrfs. Its overload differs for
// * MatrixX&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename VectorDF,
        typename VectorEF, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR >
inline typename boost::disable_if< detail::is_workspace< VectorBERR >,
        std::ptrdiff_t >::type
ptrfs( const VectorD& d, const VectorE& e, const VectorDF& df,
        const VectorEF& ef, const MatrixB& b, MatrixX& x, VectorFERR& ferr,
        VectorBERR& berr ) {
    return ptrfs_impl< typename bindings::value_type<
            VectorE >::type >::invoke( d, e, df, ef, b, x, ferr, berr,
            optimal_workspace() );
}

//
// Overloaded function for ptrfs. Its overload differs for
// * const MatrixX&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename VectorDF,
        typename VectorEF, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
ptrfs( const VectorD& d, const VectorE& e, const VectorDF& df,
        const VectorEF& ef, const MatrixB& b, const MatrixX& x,
        VectorFERR& ferr, VectorBERR& berr, Workspace work ) {
    return ptrfs_impl< typename bindings::value_type<
            VectorE >::type >::invoke( d, e, df, ef, b, x, ferr, berr, work );
}

//
// Overloaded function for ptrfs. Its overload differs for
// * const MatrixX&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename VectorDF,
        typename VectorEF, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR >
inline typename boost::disable_if< detail::is_workspace< VectorBERR >,
        std::ptrdiff_t >::type
ptrfs( const VectorD& d, const VectorE& e, const VectorDF& df,
        const VectorEF& ef, const MatrixB& b, const MatrixX& x,
        VectorFERR& ferr, VectorBERR& berr ) {
    return ptrfs_impl< typename bindings::value_type<
            VectorE >::type >::invoke( d, e, df, ef, b, x, ferr, berr,
            optimal_workspace() );
}
//
// Overloaded function for ptrfs. Its overload differs for
// * MatrixX&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename VectorDF,
        typename VectorEF, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
ptrfs( const char uplo, const VectorD& d, const VectorE& e,
        const VectorDF& df, const VectorEF& ef, const MatrixB& b, MatrixX& x,
        VectorFERR& ferr, VectorBERR& berr, Workspace work ) {
    return ptrfs_impl< typename bindings::value_type<
            VectorE >::type >::invoke( uplo, d, e, df, ef, b, x, ferr, berr,
            work );
}

//
// Overloaded function for ptrfs. Its overload differs for
// * MatrixX&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename VectorDF,
        typename VectorEF, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR >
inline typename boost::disable_if< detail::is_workspace< VectorBERR >,
        std::ptrdiff_t >::type
ptrfs( const char uplo, const VectorD& d, const VectorE& e,
        const VectorDF& df, const VectorEF& ef, const MatrixB& b, MatrixX& x,
        VectorFERR& ferr, VectorBERR& berr ) {
    return ptrfs_impl< typename bindings::value_type<
            VectorE >::type >::invoke( uplo, d, e, df, ef, b, x, ferr, berr,
            optimal_workspace() );
}

//
// Overloaded function for ptrfs. Its overload differs for
// * const MatrixX&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename VectorDF,
        typename VectorEF, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
ptrfs( const char uplo, const VectorD& d, const VectorE& e,
        const VectorDF& df, const VectorEF& ef, const MatrixB& b,
        const MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
        Workspace work ) {
    return ptrfs_impl< typename bindings::value_type<
            VectorE >::type >::invoke( uplo, d, e, df, ef, b, x, ferr, berr,
            work );
}

//
// Overloaded function for ptrfs. Its overload differs for
// * const MatrixX&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename VectorDF,
        typename VectorEF, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR >
inline typename boost::disable_if< detail::is_workspace< VectorBERR >,
        std::ptrdiff_t >::type
ptrfs( const char uplo, const VectorD& d, const VectorE& e,
        const VectorDF& df, const VectorEF& ef, const MatrixB& b,
        const MatrixX& x, VectorFERR& ferr, VectorBERR& berr ) {
    return ptrfs_impl< typename bindings::value_type<
            VectorE >::type >::invoke( uplo, d, e, df, ef, b, x, ferr, berr,
            optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
