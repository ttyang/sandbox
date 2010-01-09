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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GGBAL_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GGBAL_HPP

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
inline void ggbal( char job, fortran_int_t n, float* a, fortran_int_t lda,
        float* b, fortran_int_t ldb, fortran_int_t& ilo, fortran_int_t& ihi,
        float* lscale, float* rscale, float* work, fortran_int_t& info ) {
    LAPACK_SGGBAL( &job, &n, a, &lda, b, &ldb, &ilo, &ihi, lscale, rscale,
            work, &info );
}

//
// Overloaded function for dispatching to double value-type.
//
inline void ggbal( char job, fortran_int_t n, double* a, fortran_int_t lda,
        double* b, fortran_int_t ldb, fortran_int_t& ilo, fortran_int_t& ihi,
        double* lscale, double* rscale, double* work, fortran_int_t& info ) {
    LAPACK_DGGBAL( &job, &n, a, &lda, b, &ldb, &ilo, &ihi, lscale, rscale,
            work, &info );
}

//
// Overloaded function for dispatching to complex<float> value-type.
//
inline void ggbal( char job, fortran_int_t n, std::complex<float>* a,
        fortran_int_t lda, std::complex<float>* b, fortran_int_t ldb,
        fortran_int_t& ilo, fortran_int_t& ihi, float* lscale, float* rscale,
        float* work, fortran_int_t& info ) {
    LAPACK_CGGBAL( &job, &n, a, &lda, b, &ldb, &ilo, &ihi, lscale, rscale,
            work, &info );
}

//
// Overloaded function for dispatching to complex<double> value-type.
//
inline void ggbal( char job, fortran_int_t n, std::complex<double>* a,
        fortran_int_t lda, std::complex<double>* b, fortran_int_t ldb,
        fortran_int_t& ilo, fortran_int_t& ihi, double* lscale,
        double* rscale, double* work, fortran_int_t& info ) {
    LAPACK_ZGGBAL( &job, &n, a, &lda, b, &ldb, &ilo, &ihi, lscale, rscale,
            work, &info );
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to ggbal.
//
template< typename Value, typename Enable = void >
struct ggbal_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct ggbal_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
            typename VectorRSCALE, typename WORK >
    static void invoke( const char job, const fortran_int_t n, MatrixA& a,
            MatrixB& b, fortran_int_t& ilo, fortran_int_t& ihi,
            VectorLSCALE& lscale, VectorRSCALE& rscale,
            fortran_int_t& info, detail::workspace1< WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                VectorLSCALE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                VectorRSCALE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixB >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorLSCALE >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorRSCALE >::value) );
        BOOST_ASSERT( job == 'N' || job == 'P' || job == 'S' || job == 'B' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_work(
                $CALL_MIN_SIZE ));
        BOOST_ASSERT( size_minor(a) == 1 || stride_minor(a) == 1 );
        BOOST_ASSERT( size_minor(b) == 1 || stride_minor(b) == 1 );
        BOOST_ASSERT( stride_major(a) >= std::max< std::ptrdiff_t >(1,n) );
        BOOST_ASSERT( stride_major(b) >= std::max< std::ptrdiff_t >(1,n) );
        detail::ggbal( job, n, begin_value(a), stride_major(a),
                begin_value(b), stride_major(b), ilo, ihi,
                begin_value(lscale), begin_value(rscale),
                begin_value(work.select(real_type())), info );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
            typename VectorRSCALE >
    static void invoke( const char job, const fortran_int_t n, MatrixA& a,
            MatrixB& b, fortran_int_t& ilo, fortran_int_t& ihi,
            VectorLSCALE& lscale, VectorRSCALE& rscale,
            fortran_int_t& info, minimal_workspace work ) {
        bindings::detail::array< real_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        invoke( job, n, a, b, ilo, ihi, lscale, rscale, info,
                workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
            typename VectorRSCALE >
    static void invoke( const char job, const fortran_int_t n, MatrixA& a,
            MatrixB& b, fortran_int_t& ilo, fortran_int_t& ihi,
            VectorLSCALE& lscale, VectorRSCALE& rscale,
            fortran_int_t& info, optimal_workspace work ) {
        invoke( job, n, a, b, ilo, ihi, lscale, rscale, info,
                minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( $ARGUMENTS ) {
        $MIN_SIZE
    }
};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct ggbal_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
            typename VectorRSCALE, typename WORK >
    static void invoke( const char job, const fortran_int_t n, MatrixA& a,
            MatrixB& b, fortran_int_t& ilo, fortran_int_t& ihi,
            VectorLSCALE& lscale, VectorRSCALE& rscale,
            fortran_int_t& info, detail::workspace1< WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< VectorLSCALE >::type >::type,
                typename remove_const< typename value<
                VectorRSCALE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixB >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorLSCALE >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorRSCALE >::value) );
        BOOST_ASSERT( job == 'N' || job == 'P' || job == 'S' || job == 'B' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_work(
                $CALL_MIN_SIZE ));
        BOOST_ASSERT( size_minor(a) == 1 || stride_minor(a) == 1 );
        BOOST_ASSERT( size_minor(b) == 1 || stride_minor(b) == 1 );
        BOOST_ASSERT( stride_major(a) >= std::max< std::ptrdiff_t >(1,n) );
        BOOST_ASSERT( stride_major(b) >= std::max< std::ptrdiff_t >(1,n) );
        detail::ggbal( job, n, begin_value(a), stride_major(a),
                begin_value(b), stride_major(b), ilo, ihi,
                begin_value(lscale), begin_value(rscale),
                begin_value(work.select(real_type())), info );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
            typename VectorRSCALE >
    static void invoke( const char job, const fortran_int_t n, MatrixA& a,
            MatrixB& b, fortran_int_t& ilo, fortran_int_t& ihi,
            VectorLSCALE& lscale, VectorRSCALE& rscale,
            fortran_int_t& info, minimal_workspace work ) {
        bindings::detail::array< real_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        invoke( job, n, a, b, ilo, ihi, lscale, rscale, info,
                workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
            typename VectorRSCALE >
    static void invoke( const char job, const fortran_int_t n, MatrixA& a,
            MatrixB& b, fortran_int_t& ilo, fortran_int_t& ihi,
            VectorLSCALE& lscale, VectorRSCALE& rscale,
            fortran_int_t& info, optimal_workspace work ) {
        invoke( job, n, a, b, ilo, ihi, lscale, rscale, info,
                minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( $ARGUMENTS ) {
        $MIN_SIZE
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the ggbal_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for ggbal. Its overload differs for
// * MatrixA&
// * MatrixB&
// * VectorLSCALE&
// * VectorRSCALE&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE, typename Workspace >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        MatrixA& a, MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, VectorLSCALE& lscale, VectorRSCALE& rscale,
        Workspace work ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, work );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * MatrixA&
// * MatrixB&
// * VectorLSCALE&
// * VectorRSCALE&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        MatrixA& a, MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, VectorLSCALE& lscale, VectorRSCALE& rscale ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * VectorLSCALE&
// * VectorRSCALE&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE, typename Workspace >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        const MatrixA& a, MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, VectorLSCALE& lscale, VectorRSCALE& rscale,
        Workspace work ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, work );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * VectorLSCALE&
// * VectorRSCALE&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        const MatrixA& a, MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, VectorLSCALE& lscale, VectorRSCALE& rscale ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * VectorLSCALE&
// * VectorRSCALE&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE, typename Workspace >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        MatrixA& a, const MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, VectorLSCALE& lscale, VectorRSCALE& rscale,
        Workspace work ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, work );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * VectorLSCALE&
// * VectorRSCALE&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        MatrixA& a, const MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, VectorLSCALE& lscale, VectorRSCALE& rscale ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * VectorLSCALE&
// * VectorRSCALE&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE, typename Workspace >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        const MatrixA& a, const MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, VectorLSCALE& lscale, VectorRSCALE& rscale,
        Workspace work ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, work );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * VectorLSCALE&
// * VectorRSCALE&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        const MatrixA& a, const MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, VectorLSCALE& lscale, VectorRSCALE& rscale ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * MatrixA&
// * MatrixB&
// * const VectorLSCALE&
// * VectorRSCALE&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE, typename Workspace >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        MatrixA& a, MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, const VectorLSCALE& lscale,
        VectorRSCALE& rscale, Workspace work ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, work );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * MatrixA&
// * MatrixB&
// * const VectorLSCALE&
// * VectorRSCALE&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        MatrixA& a, MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, const VectorLSCALE& lscale,
        VectorRSCALE& rscale ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * const VectorLSCALE&
// * VectorRSCALE&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE, typename Workspace >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        const MatrixA& a, MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, const VectorLSCALE& lscale,
        VectorRSCALE& rscale, Workspace work ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, work );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * const VectorLSCALE&
// * VectorRSCALE&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        const MatrixA& a, MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, const VectorLSCALE& lscale,
        VectorRSCALE& rscale ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * const VectorLSCALE&
// * VectorRSCALE&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE, typename Workspace >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        MatrixA& a, const MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, const VectorLSCALE& lscale,
        VectorRSCALE& rscale, Workspace work ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, work );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * const VectorLSCALE&
// * VectorRSCALE&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        MatrixA& a, const MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, const VectorLSCALE& lscale,
        VectorRSCALE& rscale ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * const VectorLSCALE&
// * VectorRSCALE&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE, typename Workspace >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        const MatrixA& a, const MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, const VectorLSCALE& lscale,
        VectorRSCALE& rscale, Workspace work ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, work );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * const VectorLSCALE&
// * VectorRSCALE&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        const MatrixA& a, const MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, const VectorLSCALE& lscale,
        VectorRSCALE& rscale ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * MatrixA&
// * MatrixB&
// * VectorLSCALE&
// * const VectorRSCALE&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE, typename Workspace >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        MatrixA& a, MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, VectorLSCALE& lscale,
        const VectorRSCALE& rscale, Workspace work ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, work );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * MatrixA&
// * MatrixB&
// * VectorLSCALE&
// * const VectorRSCALE&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        MatrixA& a, MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, VectorLSCALE& lscale,
        const VectorRSCALE& rscale ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * VectorLSCALE&
// * const VectorRSCALE&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE, typename Workspace >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        const MatrixA& a, MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, VectorLSCALE& lscale,
        const VectorRSCALE& rscale, Workspace work ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, work );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * VectorLSCALE&
// * const VectorRSCALE&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        const MatrixA& a, MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, VectorLSCALE& lscale,
        const VectorRSCALE& rscale ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * VectorLSCALE&
// * const VectorRSCALE&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE, typename Workspace >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        MatrixA& a, const MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, VectorLSCALE& lscale,
        const VectorRSCALE& rscale, Workspace work ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, work );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * VectorLSCALE&
// * const VectorRSCALE&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        MatrixA& a, const MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, VectorLSCALE& lscale,
        const VectorRSCALE& rscale ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * VectorLSCALE&
// * const VectorRSCALE&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE, typename Workspace >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        const MatrixA& a, const MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, VectorLSCALE& lscale,
        const VectorRSCALE& rscale, Workspace work ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, work );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * VectorLSCALE&
// * const VectorRSCALE&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        const MatrixA& a, const MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, VectorLSCALE& lscale,
        const VectorRSCALE& rscale ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * MatrixA&
// * MatrixB&
// * const VectorLSCALE&
// * const VectorRSCALE&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE, typename Workspace >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        MatrixA& a, MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, const VectorLSCALE& lscale,
        const VectorRSCALE& rscale, Workspace work ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, work );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * MatrixA&
// * MatrixB&
// * const VectorLSCALE&
// * const VectorRSCALE&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        MatrixA& a, MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, const VectorLSCALE& lscale,
        const VectorRSCALE& rscale ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * const VectorLSCALE&
// * const VectorRSCALE&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE, typename Workspace >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        const MatrixA& a, MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, const VectorLSCALE& lscale,
        const VectorRSCALE& rscale, Workspace work ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, work );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * const VectorLSCALE&
// * const VectorRSCALE&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        const MatrixA& a, MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, const VectorLSCALE& lscale,
        const VectorRSCALE& rscale ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * const VectorLSCALE&
// * const VectorRSCALE&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE, typename Workspace >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        MatrixA& a, const MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, const VectorLSCALE& lscale,
        const VectorRSCALE& rscale, Workspace work ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, work );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * const VectorLSCALE&
// * const VectorRSCALE&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        MatrixA& a, const MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, const VectorLSCALE& lscale,
        const VectorRSCALE& rscale ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * const VectorLSCALE&
// * const VectorRSCALE&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE, typename Workspace >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        const MatrixA& a, const MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, const VectorLSCALE& lscale,
        const VectorRSCALE& rscale, Workspace work ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, work );
    return info;
}

//
// Overloaded function for ggbal. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * const VectorLSCALE&
// * const VectorRSCALE&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorLSCALE,
        typename VectorRSCALE >
inline std::ptrdiff_t ggbal( const char job, const fortran_int_t n,
        const MatrixA& a, const MatrixB& b, fortran_int_t& ilo,
        fortran_int_t& ihi, const VectorLSCALE& lscale,
        const VectorRSCALE& rscale ) {
    fortran_int_t info(0);
    ggbal_impl< typename value< MatrixA >::type >::invoke( job, n, a, b,
            ilo, ihi, lscale, rscale, info, optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
