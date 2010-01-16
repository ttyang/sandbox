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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_SYGV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_SYGV_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/traits/detail/utils.hpp>
#include <boost/numeric/bindings/uplo_tag.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The LAPACK-backend for sygv is the netlib-compatible backend.
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
template< typename UpLo >
inline std::ptrdiff_t sygv( const fortran_int_t itype, const char jobz, UpLo,
        const fortran_int_t n, float* a, const fortran_int_t lda, float* b,
        const fortran_int_t ldb, float* w, float* work,
        const fortran_int_t lwork ) {
    fortran_int_t info(0);
    LAPACK_SSYGV( &itype, &jobz, &lapack_option< UpLo >::value, &n, a, &lda,
            b, &ldb, w, work, &lwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
template< typename UpLo >
inline std::ptrdiff_t sygv( const fortran_int_t itype, const char jobz, UpLo,
        const fortran_int_t n, double* a, const fortran_int_t lda, double* b,
        const fortran_int_t ldb, double* w, double* work,
        const fortran_int_t lwork ) {
    fortran_int_t info(0);
    LAPACK_DSYGV( &itype, &jobz, &lapack_option< UpLo >::value, &n, a, &lda,
            b, &ldb, w, work, &lwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to sygv.
//
template< typename Value >
struct sygv_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename MatrixB, typename VectorW,
            typename WORK >
    static std::ptrdiff_t invoke( const fortran_int_t itype,
            const char jobz, MatrixA& a, MatrixB& b, VectorW& w,
            detail::workspace1< WORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixA >::type uplo;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                VectorW >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixB >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorW >::value) );
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work( bindings::size_column(a) ));
        BOOST_ASSERT( bindings::size_column(a) >= 0 );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        BOOST_ASSERT( bindings::size_minor(b) == 1 ||
                bindings::stride_minor(b) == 1 );
        BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        BOOST_ASSERT( bindings::stride_major(b) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
        return detail::sygv( itype, jobz, uplo(), bindings::size_column(a),
                bindings::begin_value(a), bindings::stride_major(a),
                bindings::begin_value(b), bindings::stride_major(b),
                bindings::begin_value(w),
                bindings::begin_value(work.select(real_type())),
                bindings::size(work.select(real_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename MatrixB, typename VectorW >
    static std::ptrdiff_t invoke( const fortran_int_t itype,
            const char jobz, MatrixA& a, MatrixB& b, VectorW& w,
            minimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixA >::type uplo;
        bindings::detail::array< real_type > tmp_work( min_size_work(
                bindings::size_column(a) ) );
        return invoke( itype, jobz, a, b, w, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename MatrixB, typename VectorW >
    static std::ptrdiff_t invoke( const fortran_int_t itype,
            const char jobz, MatrixA& a, MatrixB& b, VectorW& w,
            optimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixA >::type uplo;
        real_type opt_size_work;
        detail::sygv( itype, jobz, uplo(), bindings::size_column(a),
                bindings::begin_value(a), bindings::stride_major(a),
                bindings::begin_value(b), bindings::stride_major(b),
                bindings::begin_value(w), &opt_size_work, -1 );
        bindings::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        return invoke( itype, jobz, a, b, w, workspace( tmp_work ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return std::max< std::ptrdiff_t >( 1, 3*n-1 );
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the sygv_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for sygv. Its overload differs for
// * MatrixA&
// * MatrixB&
// * VectorW&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorW,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
sygv( const fortran_int_t itype, const char jobz, MatrixA& a,
        MatrixB& b, VectorW& w, Workspace work ) {
    return sygv_impl< typename value< MatrixA >::type >::invoke( itype,
            jobz, a, b, w, work );
}

//
// Overloaded function for sygv. Its overload differs for
// * MatrixA&
// * MatrixB&
// * VectorW&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorW >
inline typename boost::disable_if< detail::is_workspace< VectorW >,
        std::ptrdiff_t >::type
sygv( const fortran_int_t itype, const char jobz, MatrixA& a,
        MatrixB& b, VectorW& w ) {
    return sygv_impl< typename value< MatrixA >::type >::invoke( itype,
            jobz, a, b, w, optimal_workspace() );
}

//
// Overloaded function for sygv. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * VectorW&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorW,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
sygv( const fortran_int_t itype, const char jobz, const MatrixA& a,
        MatrixB& b, VectorW& w, Workspace work ) {
    return sygv_impl< typename value< MatrixA >::type >::invoke( itype,
            jobz, a, b, w, work );
}

//
// Overloaded function for sygv. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * VectorW&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorW >
inline typename boost::disable_if< detail::is_workspace< VectorW >,
        std::ptrdiff_t >::type
sygv( const fortran_int_t itype, const char jobz, const MatrixA& a,
        MatrixB& b, VectorW& w ) {
    return sygv_impl< typename value< MatrixA >::type >::invoke( itype,
            jobz, a, b, w, optimal_workspace() );
}

//
// Overloaded function for sygv. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * VectorW&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorW,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
sygv( const fortran_int_t itype, const char jobz, MatrixA& a,
        const MatrixB& b, VectorW& w, Workspace work ) {
    return sygv_impl< typename value< MatrixA >::type >::invoke( itype,
            jobz, a, b, w, work );
}

//
// Overloaded function for sygv. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * VectorW&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorW >
inline typename boost::disable_if< detail::is_workspace< VectorW >,
        std::ptrdiff_t >::type
sygv( const fortran_int_t itype, const char jobz, MatrixA& a,
        const MatrixB& b, VectorW& w ) {
    return sygv_impl< typename value< MatrixA >::type >::invoke( itype,
            jobz, a, b, w, optimal_workspace() );
}

//
// Overloaded function for sygv. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * VectorW&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorW,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
sygv( const fortran_int_t itype, const char jobz, const MatrixA& a,
        const MatrixB& b, VectorW& w, Workspace work ) {
    return sygv_impl< typename value< MatrixA >::type >::invoke( itype,
            jobz, a, b, w, work );
}

//
// Overloaded function for sygv. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * VectorW&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorW >
inline typename boost::disable_if< detail::is_workspace< VectorW >,
        std::ptrdiff_t >::type
sygv( const fortran_int_t itype, const char jobz, const MatrixA& a,
        const MatrixB& b, VectorW& w ) {
    return sygv_impl< typename value< MatrixA >::type >::invoke( itype,
            jobz, a, b, w, optimal_workspace() );
}

//
// Overloaded function for sygv. Its overload differs for
// * MatrixA&
// * MatrixB&
// * const VectorW&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorW,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
sygv( const fortran_int_t itype, const char jobz, MatrixA& a,
        MatrixB& b, const VectorW& w, Workspace work ) {
    return sygv_impl< typename value< MatrixA >::type >::invoke( itype,
            jobz, a, b, w, work );
}

//
// Overloaded function for sygv. Its overload differs for
// * MatrixA&
// * MatrixB&
// * const VectorW&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorW >
inline typename boost::disable_if< detail::is_workspace< VectorW >,
        std::ptrdiff_t >::type
sygv( const fortran_int_t itype, const char jobz, MatrixA& a,
        MatrixB& b, const VectorW& w ) {
    return sygv_impl< typename value< MatrixA >::type >::invoke( itype,
            jobz, a, b, w, optimal_workspace() );
}

//
// Overloaded function for sygv. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * const VectorW&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorW,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
sygv( const fortran_int_t itype, const char jobz, const MatrixA& a,
        MatrixB& b, const VectorW& w, Workspace work ) {
    return sygv_impl< typename value< MatrixA >::type >::invoke( itype,
            jobz, a, b, w, work );
}

//
// Overloaded function for sygv. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * const VectorW&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorW >
inline typename boost::disable_if< detail::is_workspace< VectorW >,
        std::ptrdiff_t >::type
sygv( const fortran_int_t itype, const char jobz, const MatrixA& a,
        MatrixB& b, const VectorW& w ) {
    return sygv_impl< typename value< MatrixA >::type >::invoke( itype,
            jobz, a, b, w, optimal_workspace() );
}

//
// Overloaded function for sygv. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * const VectorW&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorW,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
sygv( const fortran_int_t itype, const char jobz, MatrixA& a,
        const MatrixB& b, const VectorW& w, Workspace work ) {
    return sygv_impl< typename value< MatrixA >::type >::invoke( itype,
            jobz, a, b, w, work );
}

//
// Overloaded function for sygv. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * const VectorW&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorW >
inline typename boost::disable_if< detail::is_workspace< VectorW >,
        std::ptrdiff_t >::type
sygv( const fortran_int_t itype, const char jobz, MatrixA& a,
        const MatrixB& b, const VectorW& w ) {
    return sygv_impl< typename value< MatrixA >::type >::invoke( itype,
            jobz, a, b, w, optimal_workspace() );
}

//
// Overloaded function for sygv. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * const VectorW&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorW,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
sygv( const fortran_int_t itype, const char jobz, const MatrixA& a,
        const MatrixB& b, const VectorW& w, Workspace work ) {
    return sygv_impl< typename value< MatrixA >::type >::invoke( itype,
            jobz, a, b, w, work );
}

//
// Overloaded function for sygv. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * const VectorW&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorW >
inline typename boost::disable_if< detail::is_workspace< VectorW >,
        std::ptrdiff_t >::type
sygv( const fortran_int_t itype, const char jobz, const MatrixA& a,
        const MatrixB& b, const VectorW& w ) {
    return sygv_impl< typename value< MatrixA >::type >::invoke( itype,
            jobz, a, b, w, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
