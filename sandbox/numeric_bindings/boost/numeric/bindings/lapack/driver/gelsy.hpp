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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GELSY_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GELSY_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_complex.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/is_real.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/detail/lapack_option.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/traits/detail/utils.hpp>
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
inline void gelsy( fortran_int_t m, fortran_int_t n, fortran_int_t nrhs,
        float* a, fortran_int_t lda, float* b, fortran_int_t ldb,
        fortran_int_t* jpvt, float rcond, fortran_int_t& rank, float* work,
        fortran_int_t lwork, fortran_int_t& info ) {
    LAPACK_SGELSY( &m, &n, &nrhs, a, &lda, b, &ldb, jpvt, &rcond, &rank, work,
            &lwork, &info );
}

//
// Overloaded function for dispatching to double value-type.
//
inline void gelsy( fortran_int_t m, fortran_int_t n, fortran_int_t nrhs,
        double* a, fortran_int_t lda, double* b, fortran_int_t ldb,
        fortran_int_t* jpvt, double rcond, fortran_int_t& rank, double* work,
        fortran_int_t lwork, fortran_int_t& info ) {
    LAPACK_DGELSY( &m, &n, &nrhs, a, &lda, b, &ldb, jpvt, &rcond, &rank, work,
            &lwork, &info );
}

//
// Overloaded function for dispatching to complex<float> value-type.
//
inline void gelsy( fortran_int_t m, fortran_int_t n, fortran_int_t nrhs,
        std::complex<float>* a, fortran_int_t lda, std::complex<float>* b,
        fortran_int_t ldb, fortran_int_t* jpvt, float rcond,
        fortran_int_t& rank, std::complex<float>* work, fortran_int_t lwork,
        float* rwork, fortran_int_t& info ) {
    LAPACK_CGELSY( &m, &n, &nrhs, a, &lda, b, &ldb, jpvt, &rcond, &rank, work,
            &lwork, rwork, &info );
}

//
// Overloaded function for dispatching to complex<double> value-type.
//
inline void gelsy( fortran_int_t m, fortran_int_t n, fortran_int_t nrhs,
        std::complex<double>* a, fortran_int_t lda, std::complex<double>* b,
        fortran_int_t ldb, fortran_int_t* jpvt, double rcond,
        fortran_int_t& rank, std::complex<double>* work, fortran_int_t lwork,
        double* rwork, fortran_int_t& info ) {
    LAPACK_ZGELSY( &m, &n, &nrhs, a, &lda, b, &ldb, jpvt, &rcond, &rank, work,
            &lwork, rwork, &info );
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to gelsy.
//
template< typename Value, typename Enable = void >
struct gelsy_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct gelsy_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename MatrixB, typename VectorJPVT,
            typename WORK >
    static void invoke( MatrixA& a, MatrixB& b, VectorJPVT& jpvt,
            const real_type rcond, fortran_int_t& rank,
            fortran_int_t& info, detail::workspace1< WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixB >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorJPVT >::value) );
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_work(
                size_row(a), size_column(a), size_column(b) ));
        BOOST_ASSERT( size_column(a) >= 0 );
        BOOST_ASSERT( size_column(b) >= 0 );
        BOOST_ASSERT( size_minor(a) == 1 || stride_minor(a) == 1 );
        BOOST_ASSERT( size_minor(b) == 1 || stride_minor(b) == 1 );
        BOOST_ASSERT( size_row(a) >= 0 );
        BOOST_ASSERT( stride_major(a) >= std::max< std::ptrdiff_t >(1,
                size_row(a)) );
        BOOST_ASSERT( stride_major(b) >= std::max< std::ptrdiff_t >(1,std::max<
                std::ptrdiff_t >(size_row(a),size_column(a))) );
        detail::gelsy( size_row(a), size_column(a), size_column(b),
                begin_value(a), stride_major(a), begin_value(b),
                stride_major(b), begin_value(jpvt), rcond, rank,
                begin_value(work.select(real_type())),
                size(work.select(real_type())), info );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename MatrixB, typename VectorJPVT >
    static void invoke( MatrixA& a, MatrixB& b, VectorJPVT& jpvt,
            const real_type rcond, fortran_int_t& rank,
            fortran_int_t& info, minimal_workspace work ) {
        bindings::detail::array< real_type > tmp_work( min_size_work(
                size_row(a), size_column(a), size_column(b) ) );
        invoke( a, b, jpvt, rcond, rank, info, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename MatrixB, typename VectorJPVT >
    static void invoke( MatrixA& a, MatrixB& b, VectorJPVT& jpvt,
            const real_type rcond, fortran_int_t& rank,
            fortran_int_t& info, optimal_workspace work ) {
        real_type opt_size_work;
        detail::gelsy( size_row(a), size_column(a), size_column(b),
                begin_value(a), stride_major(a), begin_value(b),
                stride_major(b), begin_value(jpvt), rcond, rank,
                &opt_size_work, -1, info );
        bindings::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        invoke( a, b, jpvt, rcond, rank, info, workspace( tmp_work ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t m,
            const std::ptrdiff_t n, const std::ptrdiff_t nrhs ) {
        std::ptrdiff_t minmn = std::min< std::ptrdiff_t >( m, n );
        return std::max< std::ptrdiff_t >( 1, std::max< std::ptrdiff_t >( minmn+
                3*n+1, 2*minmn+nrhs ));
    }
};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct gelsy_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename MatrixB, typename VectorJPVT,
            typename WORK, typename RWORK >
    static void invoke( MatrixA& a, MatrixB& b, VectorJPVT& jpvt,
            const real_type rcond, fortran_int_t& rank,
            fortran_int_t& info, detail::workspace2< WORK, RWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixB >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorJPVT >::value) );
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_rwork(
                size_column(a) ));
        BOOST_ASSERT( size(work.select(value_type())) >= min_size_work(
                size_row(a), size_column(a), size_column(b) ));
        BOOST_ASSERT( size_column(a) >= 0 );
        BOOST_ASSERT( size_column(b) >= 0 );
        BOOST_ASSERT( size_minor(a) == 1 || stride_minor(a) == 1 );
        BOOST_ASSERT( size_minor(b) == 1 || stride_minor(b) == 1 );
        BOOST_ASSERT( size_row(a) >= 0 );
        BOOST_ASSERT( stride_major(a) >= std::max< std::ptrdiff_t >(1,
                size_row(a)) );
        BOOST_ASSERT( stride_major(b) >= std::max< std::ptrdiff_t >(1,std::max<
                std::ptrdiff_t >(size_row(a),size_column(a))) );
        detail::gelsy( size_row(a), size_column(a), size_column(b),
                begin_value(a), stride_major(a), begin_value(b),
                stride_major(b), begin_value(jpvt), rcond, rank,
                begin_value(work.select(value_type())),
                size(work.select(value_type())),
                begin_value(work.select(real_type())), info );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename MatrixB, typename VectorJPVT >
    static void invoke( MatrixA& a, MatrixB& b, VectorJPVT& jpvt,
            const real_type rcond, fortran_int_t& rank,
            fortran_int_t& info, minimal_workspace work ) {
        bindings::detail::array< value_type > tmp_work( min_size_work(
                size_row(a), size_column(a), size_column(b) ) );
        bindings::detail::array< real_type > tmp_rwork( min_size_rwork(
                size_column(a) ) );
        invoke( a, b, jpvt, rcond, rank, info, workspace( tmp_work,
                tmp_rwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename MatrixB, typename VectorJPVT >
    static void invoke( MatrixA& a, MatrixB& b, VectorJPVT& jpvt,
            const real_type rcond, fortran_int_t& rank,
            fortran_int_t& info, optimal_workspace work ) {
        value_type opt_size_work;
        bindings::detail::array< real_type > tmp_rwork( min_size_rwork(
                size_column(a) ) );
        detail::gelsy( size_row(a), size_column(a), size_column(b),
                begin_value(a), stride_major(a), begin_value(b),
                stride_major(b), begin_value(jpvt), rcond, rank,
                &opt_size_work, -1, begin_value(tmp_rwork), info );
        bindings::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        invoke( a, b, jpvt, rcond, rank, info, workspace( tmp_work,
                tmp_rwork ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t m,
            const std::ptrdiff_t n, const std::ptrdiff_t nrhs ) {
        std::ptrdiff_t minmn = std::min< std::ptrdiff_t >( m, n );
        return std::max< std::ptrdiff_t >( 1, std::max<
                std::ptrdiff_t >( std::max< std::ptrdiff_t >( 2*minmn, n+1 ),
                minmn+nrhs ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array rwork.
    //
    static std::ptrdiff_t min_size_rwork( const std::ptrdiff_t n ) {
        return 2*n;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the gelsy_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for gelsy. Its overload differs for
// * MatrixA&
// * MatrixB&
// * VectorJPVT&
// * fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT,
        typename Workspace >
inline std::ptrdiff_t gelsy( MatrixA& a, MatrixB& b, VectorJPVT& jpvt,
        const typename remove_imaginary< typename value<
        MatrixA >::type >::type rcond, fortran_int_t& rank,
        Workspace work ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, work );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * MatrixA&
// * MatrixB&
// * VectorJPVT&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT >
inline std::ptrdiff_t gelsy( MatrixA& a, MatrixB& b, VectorJPVT& jpvt,
        const typename remove_imaginary< typename value<
        MatrixA >::type >::type rcond, fortran_int_t& rank ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * VectorJPVT&
// * fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT,
        typename Workspace >
inline std::ptrdiff_t gelsy( const MatrixA& a, MatrixB& b,
        VectorJPVT& jpvt, const typename remove_imaginary< typename value<
        MatrixA >::type >::type rcond, fortran_int_t& rank,
        Workspace work ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, work );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * VectorJPVT&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT >
inline std::ptrdiff_t gelsy( const MatrixA& a, MatrixB& b,
        VectorJPVT& jpvt, const typename remove_imaginary< typename value<
        MatrixA >::type >::type rcond, fortran_int_t& rank ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * VectorJPVT&
// * fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT,
        typename Workspace >
inline std::ptrdiff_t gelsy( MatrixA& a, const MatrixB& b,
        VectorJPVT& jpvt, const typename remove_imaginary< typename value<
        MatrixA >::type >::type rcond, fortran_int_t& rank,
        Workspace work ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, work );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * VectorJPVT&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT >
inline std::ptrdiff_t gelsy( MatrixA& a, const MatrixB& b,
        VectorJPVT& jpvt, const typename remove_imaginary< typename value<
        MatrixA >::type >::type rcond, fortran_int_t& rank ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * VectorJPVT&
// * fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT,
        typename Workspace >
inline std::ptrdiff_t gelsy( const MatrixA& a, const MatrixB& b,
        VectorJPVT& jpvt, const typename remove_imaginary< typename value<
        MatrixA >::type >::type rcond, fortran_int_t& rank,
        Workspace work ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, work );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * VectorJPVT&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT >
inline std::ptrdiff_t gelsy( const MatrixA& a, const MatrixB& b,
        VectorJPVT& jpvt, const typename remove_imaginary< typename value<
        MatrixA >::type >::type rcond, fortran_int_t& rank ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * MatrixA&
// * MatrixB&
// * const VectorJPVT&
// * fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT,
        typename Workspace >
inline std::ptrdiff_t gelsy( MatrixA& a, MatrixB& b,
        const VectorJPVT& jpvt, const typename remove_imaginary<
        typename value< MatrixA >::type >::type rcond,
        fortran_int_t& rank, Workspace work ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, work );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * MatrixA&
// * MatrixB&
// * const VectorJPVT&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT >
inline std::ptrdiff_t gelsy( MatrixA& a, MatrixB& b,
        const VectorJPVT& jpvt, const typename remove_imaginary<
        typename value< MatrixA >::type >::type rcond,
        fortran_int_t& rank ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * const VectorJPVT&
// * fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT,
        typename Workspace >
inline std::ptrdiff_t gelsy( const MatrixA& a, MatrixB& b,
        const VectorJPVT& jpvt, const typename remove_imaginary<
        typename value< MatrixA >::type >::type rcond,
        fortran_int_t& rank, Workspace work ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, work );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * const VectorJPVT&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT >
inline std::ptrdiff_t gelsy( const MatrixA& a, MatrixB& b,
        const VectorJPVT& jpvt, const typename remove_imaginary<
        typename value< MatrixA >::type >::type rcond,
        fortran_int_t& rank ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * const VectorJPVT&
// * fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT,
        typename Workspace >
inline std::ptrdiff_t gelsy( MatrixA& a, const MatrixB& b,
        const VectorJPVT& jpvt, const typename remove_imaginary<
        typename value< MatrixA >::type >::type rcond,
        fortran_int_t& rank, Workspace work ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, work );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * const VectorJPVT&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT >
inline std::ptrdiff_t gelsy( MatrixA& a, const MatrixB& b,
        const VectorJPVT& jpvt, const typename remove_imaginary<
        typename value< MatrixA >::type >::type rcond,
        fortran_int_t& rank ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * const VectorJPVT&
// * fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT,
        typename Workspace >
inline std::ptrdiff_t gelsy( const MatrixA& a, const MatrixB& b,
        const VectorJPVT& jpvt, const typename remove_imaginary<
        typename value< MatrixA >::type >::type rcond,
        fortran_int_t& rank, Workspace work ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, work );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * const VectorJPVT&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT >
inline std::ptrdiff_t gelsy( const MatrixA& a, const MatrixB& b,
        const VectorJPVT& jpvt, const typename remove_imaginary<
        typename value< MatrixA >::type >::type rcond,
        fortran_int_t& rank ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * MatrixA&
// * MatrixB&
// * VectorJPVT&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT,
        typename Workspace >
inline std::ptrdiff_t gelsy( MatrixA& a, MatrixB& b, VectorJPVT& jpvt,
        const typename remove_imaginary< typename value<
        MatrixA >::type >::type rcond, const fortran_int_t& rank,
        Workspace work ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, work );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * MatrixA&
// * MatrixB&
// * VectorJPVT&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT >
inline std::ptrdiff_t gelsy( MatrixA& a, MatrixB& b, VectorJPVT& jpvt,
        const typename remove_imaginary< typename value<
        MatrixA >::type >::type rcond, const fortran_int_t& rank ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * VectorJPVT&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT,
        typename Workspace >
inline std::ptrdiff_t gelsy( const MatrixA& a, MatrixB& b,
        VectorJPVT& jpvt, const typename remove_imaginary< typename value<
        MatrixA >::type >::type rcond, const fortran_int_t& rank,
        Workspace work ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, work );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * VectorJPVT&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT >
inline std::ptrdiff_t gelsy( const MatrixA& a, MatrixB& b,
        VectorJPVT& jpvt, const typename remove_imaginary< typename value<
        MatrixA >::type >::type rcond, const fortran_int_t& rank ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * VectorJPVT&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT,
        typename Workspace >
inline std::ptrdiff_t gelsy( MatrixA& a, const MatrixB& b,
        VectorJPVT& jpvt, const typename remove_imaginary< typename value<
        MatrixA >::type >::type rcond, const fortran_int_t& rank,
        Workspace work ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, work );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * VectorJPVT&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT >
inline std::ptrdiff_t gelsy( MatrixA& a, const MatrixB& b,
        VectorJPVT& jpvt, const typename remove_imaginary< typename value<
        MatrixA >::type >::type rcond, const fortran_int_t& rank ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * VectorJPVT&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT,
        typename Workspace >
inline std::ptrdiff_t gelsy( const MatrixA& a, const MatrixB& b,
        VectorJPVT& jpvt, const typename remove_imaginary< typename value<
        MatrixA >::type >::type rcond, const fortran_int_t& rank,
        Workspace work ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, work );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * VectorJPVT&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT >
inline std::ptrdiff_t gelsy( const MatrixA& a, const MatrixB& b,
        VectorJPVT& jpvt, const typename remove_imaginary< typename value<
        MatrixA >::type >::type rcond, const fortran_int_t& rank ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * MatrixA&
// * MatrixB&
// * const VectorJPVT&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT,
        typename Workspace >
inline std::ptrdiff_t gelsy( MatrixA& a, MatrixB& b,
        const VectorJPVT& jpvt, const typename remove_imaginary<
        typename value< MatrixA >::type >::type rcond,
        const fortran_int_t& rank, Workspace work ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, work );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * MatrixA&
// * MatrixB&
// * const VectorJPVT&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT >
inline std::ptrdiff_t gelsy( MatrixA& a, MatrixB& b,
        const VectorJPVT& jpvt, const typename remove_imaginary<
        typename value< MatrixA >::type >::type rcond,
        const fortran_int_t& rank ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * const VectorJPVT&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT,
        typename Workspace >
inline std::ptrdiff_t gelsy( const MatrixA& a, MatrixB& b,
        const VectorJPVT& jpvt, const typename remove_imaginary<
        typename value< MatrixA >::type >::type rcond,
        const fortran_int_t& rank, Workspace work ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, work );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * const VectorJPVT&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT >
inline std::ptrdiff_t gelsy( const MatrixA& a, MatrixB& b,
        const VectorJPVT& jpvt, const typename remove_imaginary<
        typename value< MatrixA >::type >::type rcond,
        const fortran_int_t& rank ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * const VectorJPVT&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT,
        typename Workspace >
inline std::ptrdiff_t gelsy( MatrixA& a, const MatrixB& b,
        const VectorJPVT& jpvt, const typename remove_imaginary<
        typename value< MatrixA >::type >::type rcond,
        const fortran_int_t& rank, Workspace work ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, work );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * const VectorJPVT&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT >
inline std::ptrdiff_t gelsy( MatrixA& a, const MatrixB& b,
        const VectorJPVT& jpvt, const typename remove_imaginary<
        typename value< MatrixA >::type >::type rcond,
        const fortran_int_t& rank ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * const VectorJPVT&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT,
        typename Workspace >
inline std::ptrdiff_t gelsy( const MatrixA& a, const MatrixB& b,
        const VectorJPVT& jpvt, const typename remove_imaginary<
        typename value< MatrixA >::type >::type rcond,
        const fortran_int_t& rank, Workspace work ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, work );
    return info;
}

//
// Overloaded function for gelsy. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * const VectorJPVT&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorJPVT >
inline std::ptrdiff_t gelsy( const MatrixA& a, const MatrixB& b,
        const VectorJPVT& jpvt, const typename remove_imaginary<
        typename value< MatrixA >::type >::type rcond,
        const fortran_int_t& rank ) {
    fortran_int_t info(0);
    gelsy_impl< typename value< MatrixA >::type >::invoke( a, b, jpvt,
            rcond, rank, info, optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
