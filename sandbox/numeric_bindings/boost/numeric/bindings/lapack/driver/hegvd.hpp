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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_HEGVD_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_HEGVD_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/data_side.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
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
// Overloaded function for dispatching to complex<float> value-type.
//
template< typename UpLo >
inline void hegvd( fortran_int_t itype, char jobz, UpLo, fortran_int_t n,
        std::complex<float>* a, fortran_int_t lda, std::complex<float>* b,
        fortran_int_t ldb, float* w, std::complex<float>* work,
        fortran_int_t lwork, float* rwork, fortran_int_t lrwork,
        fortran_int_t* iwork, fortran_int_t liwork, fortran_int_t& info ) {
    LAPACK_CHEGVD( &itype, &jobz, &lapack_option< UpLo >::value, &n, a, &lda,
            b, &ldb, w, work, &lwork, rwork, &lrwork, iwork, &liwork, &info );
}

//
// Overloaded function for dispatching to complex<double> value-type.
//
template< typename UpLo >
inline void hegvd( fortran_int_t itype, char jobz, UpLo, fortran_int_t n,
        std::complex<double>* a, fortran_int_t lda, std::complex<double>* b,
        fortran_int_t ldb, double* w, std::complex<double>* work,
        fortran_int_t lwork, double* rwork, fortran_int_t lrwork,
        fortran_int_t* iwork, fortran_int_t liwork, fortran_int_t& info ) {
    LAPACK_ZHEGVD( &itype, &jobz, &lapack_option< UpLo >::value, &n, a, &lda,
            b, &ldb, w, work, &lwork, rwork, &lrwork, iwork, &liwork, &info );
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to hegvd.
//
template< typename Value >
struct hegvd_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename MatrixB, typename VectorW,
            typename WORK, typename RWORK, typename IWORK >
    static void invoke( const fortran_int_t itype, const char jobz,
            const fortran_int_t n, MatrixA& a, MatrixB& b, VectorW& w,
            fortran_int_t& info, detail::workspace3< WORK, RWORK,
            IWORK > work ) {
        typedef typename result_of::data_side< MatrixA >::type uplo;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixB >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorW >::value) );
        BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( size(work.select(fortran_int_t())) >=
                min_size_iwork( jobz, n ));
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_rwork( jobz,
                n ));
        BOOST_ASSERT( size(work.select(value_type())) >= min_size_work( jobz,
                n ));
        BOOST_ASSERT( size_minor(a) == 1 || stride_minor(a) == 1 );
        BOOST_ASSERT( size_minor(b) == 1 || stride_minor(b) == 1 );
        BOOST_ASSERT( stride_major(a) >= std::max< std::ptrdiff_t >(1,n) );
        BOOST_ASSERT( stride_major(b) >= std::max< std::ptrdiff_t >(1,n) );
        detail::hegvd( itype, jobz, uplo(), n, begin_value(a),
                stride_major(a), begin_value(b), stride_major(b),
                begin_value(w), begin_value(work.select(value_type())),
                size(work.select(value_type())),
                begin_value(work.select(real_type())),
                size(work.select(real_type())),
                begin_value(work.select(fortran_int_t())),
                size(work.select(fortran_int_t())), info );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename MatrixB, typename VectorW >
    static void invoke( const fortran_int_t itype, const char jobz,
            const fortran_int_t n, MatrixA& a, MatrixB& b, VectorW& w,
            fortran_int_t& info, minimal_workspace work ) {
        typedef typename result_of::data_side< MatrixA >::type uplo;
        bindings::detail::array< value_type > tmp_work( min_size_work( jobz,
                n ) );
        bindings::detail::array< real_type > tmp_rwork( min_size_rwork( jobz,
                n ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( jobz, n ) );
        invoke( itype, jobz, n, a, b, w, info, workspace( tmp_work, tmp_rwork,
                tmp_iwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename MatrixB, typename VectorW >
    static void invoke( const fortran_int_t itype, const char jobz,
            const fortran_int_t n, MatrixA& a, MatrixB& b, VectorW& w,
            fortran_int_t& info, optimal_workspace work ) {
        typedef typename result_of::data_side< MatrixA >::type uplo;
        value_type opt_size_work;
        real_type opt_size_rwork;
        fortran_int_t opt_size_iwork;
        detail::hegvd( itype, jobz, uplo(), n, begin_value(a),
                stride_major(a), begin_value(b), stride_major(b),
                begin_value(w), &opt_size_work, -1, &opt_size_rwork, -1,
                &opt_size_iwork, -1, info );
        bindings::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        bindings::detail::array< real_type > tmp_rwork(
                traits::detail::to_int( opt_size_rwork ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                opt_size_iwork );
        invoke( itype, jobz, n, a, b, w, info, workspace( tmp_work, tmp_rwork,
                tmp_iwork ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const char jobz,
            const std::ptrdiff_t n ) {
        if ( n < 2 )
            return 1;
        else {
            if ( jobz == 'N' )
                return n+1;
            else
                return 2*n + n*n;
        }
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array rwork.
    //
    static std::ptrdiff_t min_size_rwork( const char jobz,
            const std::ptrdiff_t n ) {
        if ( n < 2 )
            return 1;
        else {
            if ( jobz == 'N' )
                return n;
            else
                return 1 + 5*n + 2*n*n;
        }
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array iwork.
    //
    static std::ptrdiff_t min_size_iwork( const char jobz,
            const std::ptrdiff_t n ) {
        if ( jobz == 'N' || n < 2 )
            return 1;
        else
            return 3 + 5*n;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the hegvd_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for hegvd. Its overload differs for
// * MatrixA&
// * MatrixB&
// * VectorW&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorW,
        typename Workspace >
inline std::ptrdiff_t hegvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixA& a, MatrixB& b,
        VectorW& w, Workspace work ) {
    fortran_int_t info(0);
    hegvd_impl< typename value< MatrixA >::type >::invoke( itype, jobz,
            n, a, b, w, info, work );
    return info;
}

//
// Overloaded function for hegvd. Its overload differs for
// * MatrixA&
// * MatrixB&
// * VectorW&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorW >
inline std::ptrdiff_t hegvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixA& a, MatrixB& b,
        VectorW& w ) {
    fortran_int_t info(0);
    hegvd_impl< typename value< MatrixA >::type >::invoke( itype, jobz,
            n, a, b, w, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hegvd. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * VectorW&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorW,
        typename Workspace >
inline std::ptrdiff_t hegvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixA& a,
        MatrixB& b, VectorW& w, Workspace work ) {
    fortran_int_t info(0);
    hegvd_impl< typename value< MatrixA >::type >::invoke( itype, jobz,
            n, a, b, w, info, work );
    return info;
}

//
// Overloaded function for hegvd. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * VectorW&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorW >
inline std::ptrdiff_t hegvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixA& a,
        MatrixB& b, VectorW& w ) {
    fortran_int_t info(0);
    hegvd_impl< typename value< MatrixA >::type >::invoke( itype, jobz,
            n, a, b, w, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hegvd. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * VectorW&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorW,
        typename Workspace >
inline std::ptrdiff_t hegvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixA& a,
        const MatrixB& b, VectorW& w, Workspace work ) {
    fortran_int_t info(0);
    hegvd_impl< typename value< MatrixA >::type >::invoke( itype, jobz,
            n, a, b, w, info, work );
    return info;
}

//
// Overloaded function for hegvd. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * VectorW&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorW >
inline std::ptrdiff_t hegvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixA& a,
        const MatrixB& b, VectorW& w ) {
    fortran_int_t info(0);
    hegvd_impl< typename value< MatrixA >::type >::invoke( itype, jobz,
            n, a, b, w, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hegvd. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * VectorW&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorW,
        typename Workspace >
inline std::ptrdiff_t hegvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixA& a,
        const MatrixB& b, VectorW& w, Workspace work ) {
    fortran_int_t info(0);
    hegvd_impl< typename value< MatrixA >::type >::invoke( itype, jobz,
            n, a, b, w, info, work );
    return info;
}

//
// Overloaded function for hegvd. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * VectorW&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorW >
inline std::ptrdiff_t hegvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixA& a,
        const MatrixB& b, VectorW& w ) {
    fortran_int_t info(0);
    hegvd_impl< typename value< MatrixA >::type >::invoke( itype, jobz,
            n, a, b, w, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hegvd. Its overload differs for
// * MatrixA&
// * MatrixB&
// * const VectorW&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorW,
        typename Workspace >
inline std::ptrdiff_t hegvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixA& a, MatrixB& b,
        const VectorW& w, Workspace work ) {
    fortran_int_t info(0);
    hegvd_impl< typename value< MatrixA >::type >::invoke( itype, jobz,
            n, a, b, w, info, work );
    return info;
}

//
// Overloaded function for hegvd. Its overload differs for
// * MatrixA&
// * MatrixB&
// * const VectorW&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorW >
inline std::ptrdiff_t hegvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixA& a, MatrixB& b,
        const VectorW& w ) {
    fortran_int_t info(0);
    hegvd_impl< typename value< MatrixA >::type >::invoke( itype, jobz,
            n, a, b, w, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hegvd. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * const VectorW&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorW,
        typename Workspace >
inline std::ptrdiff_t hegvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixA& a,
        MatrixB& b, const VectorW& w, Workspace work ) {
    fortran_int_t info(0);
    hegvd_impl< typename value< MatrixA >::type >::invoke( itype, jobz,
            n, a, b, w, info, work );
    return info;
}

//
// Overloaded function for hegvd. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * const VectorW&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorW >
inline std::ptrdiff_t hegvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixA& a,
        MatrixB& b, const VectorW& w ) {
    fortran_int_t info(0);
    hegvd_impl< typename value< MatrixA >::type >::invoke( itype, jobz,
            n, a, b, w, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hegvd. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * const VectorW&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorW,
        typename Workspace >
inline std::ptrdiff_t hegvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixA& a,
        const MatrixB& b, const VectorW& w, Workspace work ) {
    fortran_int_t info(0);
    hegvd_impl< typename value< MatrixA >::type >::invoke( itype, jobz,
            n, a, b, w, info, work );
    return info;
}

//
// Overloaded function for hegvd. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * const VectorW&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorW >
inline std::ptrdiff_t hegvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixA& a,
        const MatrixB& b, const VectorW& w ) {
    fortran_int_t info(0);
    hegvd_impl< typename value< MatrixA >::type >::invoke( itype, jobz,
            n, a, b, w, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hegvd. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * const VectorW&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorW,
        typename Workspace >
inline std::ptrdiff_t hegvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixA& a,
        const MatrixB& b, const VectorW& w, Workspace work ) {
    fortran_int_t info(0);
    hegvd_impl< typename value< MatrixA >::type >::invoke( itype, jobz,
            n, a, b, w, info, work );
    return info;
}

//
// Overloaded function for hegvd. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * const VectorW&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorW >
inline std::ptrdiff_t hegvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixA& a,
        const MatrixB& b, const VectorW& w ) {
    fortran_int_t info(0);
    hegvd_impl< typename value< MatrixA >::type >::invoke( itype, jobz,
            n, a, b, w, info, optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
