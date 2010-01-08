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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TRRFS_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TRRFS_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/data_side.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/diag_tag.hpp>
#include <boost/numeric/bindings/is_complex.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/is_real.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/detail/lapack_option.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/trans_tag.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

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
// Overloaded function for dispatching to float value-type.
//
template< typename Trans, typename Diag >
inline void trrfs( char uplo, Trans, Diag, fortran_int_t n,
        fortran_int_t nrhs, const float* a, fortran_int_t lda, const float* b,
        fortran_int_t ldb, const float* x, fortran_int_t ldx, float* ferr,
        float* berr, float* work, fortran_int_t* iwork, fortran_int_t& info ) {
    LAPACK_STRRFS( &uplo, &lapack_option< Trans >::value, &lapack_option<
            Diag >::value, &n, &nrhs, a, &lda, b, &ldb, x, &ldx, ferr, berr,
            work, iwork, &info );
}

//
// Overloaded function for dispatching to double value-type.
//
template< typename Trans, typename Diag >
inline void trrfs( char uplo, Trans, Diag, fortran_int_t n,
        fortran_int_t nrhs, const double* a, fortran_int_t lda,
        const double* b, fortran_int_t ldb, const double* x,
        fortran_int_t ldx, double* ferr, double* berr, double* work,
        fortran_int_t* iwork, fortran_int_t& info ) {
    LAPACK_DTRRFS( &uplo, &lapack_option< Trans >::value, &lapack_option<
            Diag >::value, &n, &nrhs, a, &lda, b, &ldb, x, &ldx, ferr, berr,
            work, iwork, &info );
}

//
// Overloaded function for dispatching to complex<float> value-type.
//
template< typename Trans, typename Diag >
inline void trrfs( char uplo, Trans, Diag, fortran_int_t n,
        fortran_int_t nrhs, const std::complex<float>* a, fortran_int_t lda,
        const std::complex<float>* b, fortran_int_t ldb,
        const std::complex<float>* x, fortran_int_t ldx, float* ferr,
        float* berr, std::complex<float>* work, float* rwork,
        fortran_int_t& info ) {
    LAPACK_CTRRFS( &uplo, &lapack_option< Trans >::value, &lapack_option<
            Diag >::value, &n, &nrhs, a, &lda, b, &ldb, x, &ldx, ferr, berr,
            work, rwork, &info );
}

//
// Overloaded function for dispatching to complex<double> value-type.
//
template< typename Trans, typename Diag >
inline void trrfs( char uplo, Trans, Diag, fortran_int_t n,
        fortran_int_t nrhs, const std::complex<double>* a, fortran_int_t lda,
        const std::complex<double>* b, fortran_int_t ldb,
        const std::complex<double>* x, fortran_int_t ldx, double* ferr,
        double* berr, std::complex<double>* work, double* rwork,
        fortran_int_t& info ) {
    LAPACK_ZTRRFS( &uplo, &lapack_option< Trans >::value, &lapack_option<
            Diag >::value, &n, &nrhs, a, &lda, b, &ldb, x, &ldx, ferr, berr,
            work, rwork, &info );
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to trrfs.
//
template< typename Value, typename Enable = void >
struct trrfs_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct trrfs_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename MatrixB, typename MatrixX,
            typename VectorFERR, typename VectorBERR, typename WORK,
            typename IWORK >
    static void invoke( const char uplo, const MatrixA& a, const MatrixB& b,
            const MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            fortran_int_t& info, detail::workspace2< WORK, IWORK > work ) {
        typedef typename result_of::trans_tag< MatrixA, order >::type trans;
        typedef typename result_of::diag_tag< MatrixA >::type diag;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixX >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                VectorFERR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                VectorBERR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorFERR >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorBERR >::value) );
        BOOST_ASSERT( size(berr) >= size_column(x) );
        BOOST_ASSERT( size(work.select(fortran_int_t())) >=
                min_size_iwork( size_column_op(a, trans()) ));
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_work(
                size_column_op(a, trans()) ));
        BOOST_ASSERT( size_column(x) >= 0 );
        BOOST_ASSERT( size_column_op(a, trans()) >= 0 );
        BOOST_ASSERT( size_minor(a) == 1 || stride_minor(a) == 1 );
        BOOST_ASSERT( size_minor(b) == 1 || stride_minor(b) == 1 );
        BOOST_ASSERT( size_minor(x) == 1 || stride_minor(x) == 1 );
        BOOST_ASSERT( stride_major(a) >= std::max< std::ptrdiff_t >(1,
                size_column_op(a, trans())) );
        BOOST_ASSERT( stride_major(b) >= std::max< std::ptrdiff_t >(1,
                size_column_op(a, trans())) );
        BOOST_ASSERT( stride_major(x) >= std::max< std::ptrdiff_t >(1,
                size_column_op(a, trans())) );
        detail::trrfs( uplo, trans(), diag(), size_column_op(a, trans()),
                size_column(x), begin_value(a), stride_major(a),
                begin_value(b), stride_major(b), begin_value(x),
                stride_major(x), begin_value(ferr), begin_value(berr),
                begin_value(work.select(real_type())),
                begin_value(work.select(fortran_int_t())), info );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename MatrixB, typename MatrixX,
            typename VectorFERR, typename VectorBERR >
    static void invoke( const char uplo, const MatrixA& a, const MatrixB& b,
            const MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            fortran_int_t& info, minimal_workspace work ) {
        typedef typename result_of::trans_tag< MatrixA, order >::type trans;
        typedef typename result_of::diag_tag< MatrixA >::type diag;
        bindings::detail::array< real_type > tmp_work( min_size_work(
                size_column_op(a, trans()) ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( size_column_op(a, trans()) ) );
        invoke( uplo, a, b, x, ferr, berr, info, workspace( tmp_work,
                tmp_iwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename MatrixB, typename MatrixX,
            typename VectorFERR, typename VectorBERR >
    static void invoke( const char uplo, const MatrixA& a, const MatrixB& b,
            const MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            fortran_int_t& info, optimal_workspace work ) {
        typedef typename result_of::trans_tag< MatrixA, order >::type trans;
        typedef typename result_of::diag_tag< MatrixA >::type diag;
        invoke( uplo, a, b, x, ferr, berr, info, minimal_workspace() );
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
struct trrfs_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename MatrixB, typename MatrixX,
            typename VectorFERR, typename VectorBERR, typename WORK,
            typename RWORK >
    static void invoke( const char uplo, const MatrixA& a, const MatrixB& b,
            const MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            fortran_int_t& info, detail::workspace2< WORK, RWORK > work ) {
        typedef typename result_of::trans_tag< MatrixA, order >::type trans;
        typedef typename result_of::diag_tag< MatrixA >::type diag;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< VectorFERR >::type >::type,
                typename remove_const< typename value<
                VectorBERR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixX >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorFERR >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorBERR >::value) );
        BOOST_ASSERT( size(berr) >= size_column(x) );
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_rwork(
                size_column_op(a, trans()) ));
        BOOST_ASSERT( size(work.select(value_type())) >= min_size_work(
                size_column_op(a, trans()) ));
        BOOST_ASSERT( size_column(x) >= 0 );
        BOOST_ASSERT( size_column_op(a, trans()) >= 0 );
        BOOST_ASSERT( size_minor(a) == 1 || stride_minor(a) == 1 );
        BOOST_ASSERT( size_minor(b) == 1 || stride_minor(b) == 1 );
        BOOST_ASSERT( size_minor(x) == 1 || stride_minor(x) == 1 );
        BOOST_ASSERT( stride_major(a) >= std::max< std::ptrdiff_t >(1,
                size_column_op(a, trans())) );
        BOOST_ASSERT( stride_major(b) >= std::max< std::ptrdiff_t >(1,
                size_column_op(a, trans())) );
        BOOST_ASSERT( stride_major(x) >= std::max< std::ptrdiff_t >(1,
                size_column_op(a, trans())) );
        detail::trrfs( uplo, trans(), diag(), size_column_op(a, trans()),
                size_column(x), begin_value(a), stride_major(a),
                begin_value(b), stride_major(b), begin_value(x),
                stride_major(x), begin_value(ferr), begin_value(berr),
                begin_value(work.select(value_type())),
                begin_value(work.select(real_type())), info );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename MatrixB, typename MatrixX,
            typename VectorFERR, typename VectorBERR >
    static void invoke( const char uplo, const MatrixA& a, const MatrixB& b,
            const MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            fortran_int_t& info, minimal_workspace work ) {
        typedef typename result_of::trans_tag< MatrixA, order >::type trans;
        typedef typename result_of::diag_tag< MatrixA >::type diag;
        bindings::detail::array< value_type > tmp_work( min_size_work(
                size_column_op(a, trans()) ) );
        bindings::detail::array< real_type > tmp_rwork( min_size_rwork(
                size_column_op(a, trans()) ) );
        invoke( uplo, a, b, x, ferr, berr, info, workspace( tmp_work,
                tmp_rwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename MatrixB, typename MatrixX,
            typename VectorFERR, typename VectorBERR >
    static void invoke( const char uplo, const MatrixA& a, const MatrixB& b,
            const MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            fortran_int_t& info, optimal_workspace work ) {
        typedef typename result_of::trans_tag< MatrixA, order >::type trans;
        typedef typename result_of::diag_tag< MatrixA >::type diag;
        invoke( uplo, a, b, x, ferr, berr, info, minimal_workspace() );
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
// Calls to these functions are passed to the trrfs_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for trrfs. Its overload differs for
// * VectorFERR&
// * VectorBERR&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR, typename Workspace >
inline std::ptrdiff_t trrfs( const char uplo, const MatrixA& a,
        const MatrixB& b, const MatrixX& x, VectorFERR& ferr,
        VectorBERR& berr, Workspace work ) {
    fortran_int_t info(0);
    trrfs_impl< typename value< MatrixA >::type >::invoke( uplo, a, b, x,
            ferr, berr, info, work );
    return info;
}

//
// Overloaded function for trrfs. Its overload differs for
// * VectorFERR&
// * VectorBERR&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR >
inline std::ptrdiff_t trrfs( const char uplo, const MatrixA& a,
        const MatrixB& b, const MatrixX& x, VectorFERR& ferr,
        VectorBERR& berr ) {
    fortran_int_t info(0);
    trrfs_impl< typename value< MatrixA >::type >::invoke( uplo, a, b, x,
            ferr, berr, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for trrfs. Its overload differs for
// * const VectorFERR&
// * VectorBERR&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR, typename Workspace >
inline std::ptrdiff_t trrfs( const char uplo, const MatrixA& a,
        const MatrixB& b, const MatrixX& x, const VectorFERR& ferr,
        VectorBERR& berr, Workspace work ) {
    fortran_int_t info(0);
    trrfs_impl< typename value< MatrixA >::type >::invoke( uplo, a, b, x,
            ferr, berr, info, work );
    return info;
}

//
// Overloaded function for trrfs. Its overload differs for
// * const VectorFERR&
// * VectorBERR&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR >
inline std::ptrdiff_t trrfs( const char uplo, const MatrixA& a,
        const MatrixB& b, const MatrixX& x, const VectorFERR& ferr,
        VectorBERR& berr ) {
    fortran_int_t info(0);
    trrfs_impl< typename value< MatrixA >::type >::invoke( uplo, a, b, x,
            ferr, berr, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for trrfs. Its overload differs for
// * VectorFERR&
// * const VectorBERR&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR, typename Workspace >
inline std::ptrdiff_t trrfs( const char uplo, const MatrixA& a,
        const MatrixB& b, const MatrixX& x, VectorFERR& ferr,
        const VectorBERR& berr, Workspace work ) {
    fortran_int_t info(0);
    trrfs_impl< typename value< MatrixA >::type >::invoke( uplo, a, b, x,
            ferr, berr, info, work );
    return info;
}

//
// Overloaded function for trrfs. Its overload differs for
// * VectorFERR&
// * const VectorBERR&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR >
inline std::ptrdiff_t trrfs( const char uplo, const MatrixA& a,
        const MatrixB& b, const MatrixX& x, VectorFERR& ferr,
        const VectorBERR& berr ) {
    fortran_int_t info(0);
    trrfs_impl< typename value< MatrixA >::type >::invoke( uplo, a, b, x,
            ferr, berr, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for trrfs. Its overload differs for
// * const VectorFERR&
// * const VectorBERR&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR, typename Workspace >
inline std::ptrdiff_t trrfs( const char uplo, const MatrixA& a,
        const MatrixB& b, const MatrixX& x, const VectorFERR& ferr,
        const VectorBERR& berr, Workspace work ) {
    fortran_int_t info(0);
    trrfs_impl< typename value< MatrixA >::type >::invoke( uplo, a, b, x,
            ferr, berr, info, work );
    return info;
}

//
// Overloaded function for trrfs. Its overload differs for
// * const VectorFERR&
// * const VectorBERR&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR >
inline std::ptrdiff_t trrfs( const char uplo, const MatrixA& a,
        const MatrixB& b, const MatrixX& x, const VectorFERR& ferr,
        const VectorBERR& berr ) {
    fortran_int_t info(0);
    trrfs_impl< typename value< MatrixA >::type >::invoke( uplo, a, b, x,
            ferr, berr, info, optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
