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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_HERFS_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_HERFS_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/data_side.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The LAPACK-backend for herfs is the netlib-compatible backend.
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
// * complex<float> value-type.
//
template< typename UpLo >
inline std::ptrdiff_t herfs( UpLo, const fortran_int_t n,
        const fortran_int_t nrhs, const std::complex<float>* a,
        const fortran_int_t lda, const std::complex<float>* af,
        const fortran_int_t ldaf, const fortran_int_t* ipiv,
        const std::complex<float>* b, const fortran_int_t ldb,
        std::complex<float>* x, const fortran_int_t ldx, float* ferr,
        float* berr, std::complex<float>* work, float* rwork ) {
    fortran_int_t info(0);
    LAPACK_CHERFS( &lapack_option< UpLo >::value, &n, &nrhs, a, &lda, af,
            &ldaf, ipiv, b, &ldb, x, &ldx, ferr, berr, work, rwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename UpLo >
inline std::ptrdiff_t herfs( UpLo, const fortran_int_t n,
        const fortran_int_t nrhs, const std::complex<double>* a,
        const fortran_int_t lda, const std::complex<double>* af,
        const fortran_int_t ldaf, const fortran_int_t* ipiv,
        const std::complex<double>* b, const fortran_int_t ldb,
        std::complex<double>* x, const fortran_int_t ldx, double* ferr,
        double* berr, std::complex<double>* work, double* rwork ) {
    fortran_int_t info(0);
    LAPACK_ZHERFS( &lapack_option< UpLo >::value, &n, &nrhs, a, &lda, af,
            &ldaf, ipiv, b, &ldb, x, &ldx, ferr, berr, work, rwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to herfs.
//
template< typename Value >
struct herfs_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
            typename MatrixB, typename MatrixX, typename VectorFERR,
            typename VectorBERR, typename WORK, typename RWORK >
    static std::ptrdiff_t invoke( const MatrixA& a, const MatrixAF& af,
            const VectorIPIV& ipiv, const MatrixB& b, MatrixX& x,
            VectorFERR& ferr, VectorBERR& berr, detail::workspace2< WORK,
            RWORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::data_side< MatrixA >::type uplo;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< VectorFERR >::type >::type,
                typename remove_const< typename value<
                VectorBERR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixAF >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixX >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixX >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorFERR >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorBERR >::value) );
        BOOST_ASSERT( bindings::size(berr) >= bindings::size_column(b) );
        BOOST_ASSERT( bindings::size(ipiv) >= bindings::size_column(a) );
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_rwork( bindings::size_column(a) ));
        BOOST_ASSERT( bindings::size(work.select(value_type())) >=
                min_size_work( bindings::size_column(a) ));
        BOOST_ASSERT( bindings::size_column(a) >= 0 );
        BOOST_ASSERT( bindings::size_column(b) >= 0 );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        BOOST_ASSERT( bindings::size_minor(af) == 1 ||
                bindings::stride_minor(af) == 1 );
        BOOST_ASSERT( bindings::size_minor(b) == 1 ||
                bindings::stride_minor(b) == 1 );
        BOOST_ASSERT( bindings::size_minor(x) == 1 ||
                bindings::stride_minor(x) == 1 );
        BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        BOOST_ASSERT( bindings::stride_major(af) >= std::max<
                std::ptrdiff_t >(1,bindings::size_column(a)) );
        BOOST_ASSERT( bindings::stride_major(b) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        BOOST_ASSERT( bindings::stride_major(x) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        return detail::herfs( uplo(), bindings::size_column(a),
                bindings::size_column(b), bindings::begin_value(a),
                bindings::stride_major(a), bindings::begin_value(af),
                bindings::stride_major(af), bindings::begin_value(ipiv),
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
    template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
            typename MatrixB, typename MatrixX, typename VectorFERR,
            typename VectorBERR >
    static std::ptrdiff_t invoke( const MatrixA& a, const MatrixAF& af,
            const VectorIPIV& ipiv, const MatrixB& b, MatrixX& x,
            VectorFERR& ferr, VectorBERR& berr, minimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::data_side< MatrixA >::type uplo;
        bindings::detail::array< value_type > tmp_work( min_size_work(
                bindings::size_column(a) ) );
        bindings::detail::array< real_type > tmp_rwork( min_size_rwork(
                bindings::size_column(a) ) );
        return invoke( a, af, ipiv, b, x, ferr, berr, workspace( tmp_work,
                tmp_rwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
            typename MatrixB, typename MatrixX, typename VectorFERR,
            typename VectorBERR >
    static std::ptrdiff_t invoke( const MatrixA& a, const MatrixAF& af,
            const VectorIPIV& ipiv, const MatrixB& b, MatrixX& x,
            VectorFERR& ferr, VectorBERR& berr, optimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::data_side< MatrixA >::type uplo;
        return invoke( a, af, ipiv, b, x, ferr, berr, minimal_workspace() );
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
// Calls to these functions are passed to the herfs_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for herfs. Its overload differs for
// * MatrixX&
// * VectorFERR&
// * VectorBERR&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
        typename MatrixB, typename MatrixX, typename VectorFERR,
        typename VectorBERR, typename Workspace >
inline std::ptrdiff_t herfs( const MatrixA& a, const MatrixAF& af,
        const VectorIPIV& ipiv, const MatrixB& b, MatrixX& x,
        VectorFERR& ferr, VectorBERR& berr, Workspace work ) {
    return herfs_impl< typename value< MatrixA >::type >::invoke( a, af,
            ipiv, b, x, ferr, berr, work );
}

//
// Overloaded function for herfs. Its overload differs for
// * MatrixX&
// * VectorFERR&
// * VectorBERR&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
        typename MatrixB, typename MatrixX, typename VectorFERR,
        typename VectorBERR >
inline std::ptrdiff_t herfs( const MatrixA& a, const MatrixAF& af,
        const VectorIPIV& ipiv, const MatrixB& b, MatrixX& x,
        VectorFERR& ferr, VectorBERR& berr ) {
    return herfs_impl< typename value< MatrixA >::type >::invoke( a, af,
            ipiv, b, x, ferr, berr, optimal_workspace() );
}

//
// Overloaded function for herfs. Its overload differs for
// * const MatrixX&
// * VectorFERR&
// * VectorBERR&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
        typename MatrixB, typename MatrixX, typename VectorFERR,
        typename VectorBERR, typename Workspace >
inline std::ptrdiff_t herfs( const MatrixA& a, const MatrixAF& af,
        const VectorIPIV& ipiv, const MatrixB& b, const MatrixX& x,
        VectorFERR& ferr, VectorBERR& berr, Workspace work ) {
    return herfs_impl< typename value< MatrixA >::type >::invoke( a, af,
            ipiv, b, x, ferr, berr, work );
}

//
// Overloaded function for herfs. Its overload differs for
// * const MatrixX&
// * VectorFERR&
// * VectorBERR&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
        typename MatrixB, typename MatrixX, typename VectorFERR,
        typename VectorBERR >
inline std::ptrdiff_t herfs( const MatrixA& a, const MatrixAF& af,
        const VectorIPIV& ipiv, const MatrixB& b, const MatrixX& x,
        VectorFERR& ferr, VectorBERR& berr ) {
    return herfs_impl< typename value< MatrixA >::type >::invoke( a, af,
            ipiv, b, x, ferr, berr, optimal_workspace() );
}

//
// Overloaded function for herfs. Its overload differs for
// * MatrixX&
// * const VectorFERR&
// * VectorBERR&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
        typename MatrixB, typename MatrixX, typename VectorFERR,
        typename VectorBERR, typename Workspace >
inline std::ptrdiff_t herfs( const MatrixA& a, const MatrixAF& af,
        const VectorIPIV& ipiv, const MatrixB& b, MatrixX& x,
        const VectorFERR& ferr, VectorBERR& berr, Workspace work ) {
    return herfs_impl< typename value< MatrixA >::type >::invoke( a, af,
            ipiv, b, x, ferr, berr, work );
}

//
// Overloaded function for herfs. Its overload differs for
// * MatrixX&
// * const VectorFERR&
// * VectorBERR&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
        typename MatrixB, typename MatrixX, typename VectorFERR,
        typename VectorBERR >
inline std::ptrdiff_t herfs( const MatrixA& a, const MatrixAF& af,
        const VectorIPIV& ipiv, const MatrixB& b, MatrixX& x,
        const VectorFERR& ferr, VectorBERR& berr ) {
    return herfs_impl< typename value< MatrixA >::type >::invoke( a, af,
            ipiv, b, x, ferr, berr, optimal_workspace() );
}

//
// Overloaded function for herfs. Its overload differs for
// * const MatrixX&
// * const VectorFERR&
// * VectorBERR&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
        typename MatrixB, typename MatrixX, typename VectorFERR,
        typename VectorBERR, typename Workspace >
inline std::ptrdiff_t herfs( const MatrixA& a, const MatrixAF& af,
        const VectorIPIV& ipiv, const MatrixB& b, const MatrixX& x,
        const VectorFERR& ferr, VectorBERR& berr, Workspace work ) {
    return herfs_impl< typename value< MatrixA >::type >::invoke( a, af,
            ipiv, b, x, ferr, berr, work );
}

//
// Overloaded function for herfs. Its overload differs for
// * const MatrixX&
// * const VectorFERR&
// * VectorBERR&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
        typename MatrixB, typename MatrixX, typename VectorFERR,
        typename VectorBERR >
inline std::ptrdiff_t herfs( const MatrixA& a, const MatrixAF& af,
        const VectorIPIV& ipiv, const MatrixB& b, const MatrixX& x,
        const VectorFERR& ferr, VectorBERR& berr ) {
    return herfs_impl< typename value< MatrixA >::type >::invoke( a, af,
            ipiv, b, x, ferr, berr, optimal_workspace() );
}

//
// Overloaded function for herfs. Its overload differs for
// * MatrixX&
// * VectorFERR&
// * const VectorBERR&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
        typename MatrixB, typename MatrixX, typename VectorFERR,
        typename VectorBERR, typename Workspace >
inline std::ptrdiff_t herfs( const MatrixA& a, const MatrixAF& af,
        const VectorIPIV& ipiv, const MatrixB& b, MatrixX& x,
        VectorFERR& ferr, const VectorBERR& berr, Workspace work ) {
    return herfs_impl< typename value< MatrixA >::type >::invoke( a, af,
            ipiv, b, x, ferr, berr, work );
}

//
// Overloaded function for herfs. Its overload differs for
// * MatrixX&
// * VectorFERR&
// * const VectorBERR&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
        typename MatrixB, typename MatrixX, typename VectorFERR,
        typename VectorBERR >
inline std::ptrdiff_t herfs( const MatrixA& a, const MatrixAF& af,
        const VectorIPIV& ipiv, const MatrixB& b, MatrixX& x,
        VectorFERR& ferr, const VectorBERR& berr ) {
    return herfs_impl< typename value< MatrixA >::type >::invoke( a, af,
            ipiv, b, x, ferr, berr, optimal_workspace() );
}

//
// Overloaded function for herfs. Its overload differs for
// * const MatrixX&
// * VectorFERR&
// * const VectorBERR&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
        typename MatrixB, typename MatrixX, typename VectorFERR,
        typename VectorBERR, typename Workspace >
inline std::ptrdiff_t herfs( const MatrixA& a, const MatrixAF& af,
        const VectorIPIV& ipiv, const MatrixB& b, const MatrixX& x,
        VectorFERR& ferr, const VectorBERR& berr, Workspace work ) {
    return herfs_impl< typename value< MatrixA >::type >::invoke( a, af,
            ipiv, b, x, ferr, berr, work );
}

//
// Overloaded function for herfs. Its overload differs for
// * const MatrixX&
// * VectorFERR&
// * const VectorBERR&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
        typename MatrixB, typename MatrixX, typename VectorFERR,
        typename VectorBERR >
inline std::ptrdiff_t herfs( const MatrixA& a, const MatrixAF& af,
        const VectorIPIV& ipiv, const MatrixB& b, const MatrixX& x,
        VectorFERR& ferr, const VectorBERR& berr ) {
    return herfs_impl< typename value< MatrixA >::type >::invoke( a, af,
            ipiv, b, x, ferr, berr, optimal_workspace() );
}

//
// Overloaded function for herfs. Its overload differs for
// * MatrixX&
// * const VectorFERR&
// * const VectorBERR&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
        typename MatrixB, typename MatrixX, typename VectorFERR,
        typename VectorBERR, typename Workspace >
inline std::ptrdiff_t herfs( const MatrixA& a, const MatrixAF& af,
        const VectorIPIV& ipiv, const MatrixB& b, MatrixX& x,
        const VectorFERR& ferr, const VectorBERR& berr, Workspace work ) {
    return herfs_impl< typename value< MatrixA >::type >::invoke( a, af,
            ipiv, b, x, ferr, berr, work );
}

//
// Overloaded function for herfs. Its overload differs for
// * MatrixX&
// * const VectorFERR&
// * const VectorBERR&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
        typename MatrixB, typename MatrixX, typename VectorFERR,
        typename VectorBERR >
inline std::ptrdiff_t herfs( const MatrixA& a, const MatrixAF& af,
        const VectorIPIV& ipiv, const MatrixB& b, MatrixX& x,
        const VectorFERR& ferr, const VectorBERR& berr ) {
    return herfs_impl< typename value< MatrixA >::type >::invoke( a, af,
            ipiv, b, x, ferr, berr, optimal_workspace() );
}

//
// Overloaded function for herfs. Its overload differs for
// * const MatrixX&
// * const VectorFERR&
// * const VectorBERR&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
        typename MatrixB, typename MatrixX, typename VectorFERR,
        typename VectorBERR, typename Workspace >
inline std::ptrdiff_t herfs( const MatrixA& a, const MatrixAF& af,
        const VectorIPIV& ipiv, const MatrixB& b, const MatrixX& x,
        const VectorFERR& ferr, const VectorBERR& berr, Workspace work ) {
    return herfs_impl< typename value< MatrixA >::type >::invoke( a, af,
            ipiv, b, x, ferr, berr, work );
}

//
// Overloaded function for herfs. Its overload differs for
// * const MatrixX&
// * const VectorFERR&
// * const VectorBERR&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixAF, typename VectorIPIV,
        typename MatrixB, typename MatrixX, typename VectorFERR,
        typename VectorBERR >
inline std::ptrdiff_t herfs( const MatrixA& a, const MatrixAF& af,
        const VectorIPIV& ipiv, const MatrixB& b, const MatrixX& x,
        const VectorFERR& ferr, const VectorBERR& berr ) {
    return herfs_impl< typename value< MatrixA >::type >::invoke( a, af,
            ipiv, b, x, ferr, berr, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
