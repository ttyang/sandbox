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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_HBEV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_HBEV_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/bandwidth.hpp>
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
// The LAPACK-backend for hbev is the netlib-compatible backend.
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
inline std::ptrdiff_t hbev( const char jobz, UpLo, const fortran_int_t n,
        const fortran_int_t kd, std::complex<float>* ab,
        const fortran_int_t ldab, float* w, std::complex<float>* z,
        const fortran_int_t ldz, std::complex<float>* work, float* rwork ) {
    fortran_int_t info(0);
    LAPACK_CHBEV( &jobz, &lapack_option< UpLo >::value, &n, &kd, ab, &ldab, w,
            z, &ldz, work, rwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename UpLo >
inline std::ptrdiff_t hbev( const char jobz, UpLo, const fortran_int_t n,
        const fortran_int_t kd, std::complex<double>* ab,
        const fortran_int_t ldab, double* w, std::complex<double>* z,
        const fortran_int_t ldz, std::complex<double>* work, double* rwork ) {
    fortran_int_t info(0);
    LAPACK_ZHBEV( &jobz, &lapack_option< UpLo >::value, &n, &kd, ab, &ldab, w,
            z, &ldz, work, rwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to hbev.
//
template< typename Value >
struct hbev_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAB, typename VectorW, typename MatrixZ,
            typename WORK, typename RWORK >
    static std::ptrdiff_t invoke( const char jobz, MatrixAB& ab, VectorW& w,
            MatrixZ& z, detail::workspace2< WORK, RWORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::data_side< MatrixAB >::type uplo;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAB >::type >::type,
                typename remove_const< typename value<
                MatrixZ >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixAB >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorW >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixZ >::value) );
        BOOST_ASSERT( bindings::bandwidth(ab, uplo()) >= 0 );
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_rwork( bindings::size_column(ab) ));
        BOOST_ASSERT( bindings::size(work.select(value_type())) >=
                min_size_work( bindings::size_column(ab) ));
        BOOST_ASSERT( bindings::size_column(ab) >= 0 );
        BOOST_ASSERT( bindings::size_minor(ab) == 1 ||
                bindings::stride_minor(ab) == 1 );
        BOOST_ASSERT( bindings::size_minor(z) == 1 ||
                bindings::stride_minor(z) == 1 );
        BOOST_ASSERT( bindings::stride_major(ab) >= bindings::bandwidth(ab,
                uplo()) );
        BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
        return detail::hbev( jobz, uplo(), bindings::size_column(ab),
                bindings::bandwidth(ab, uplo()), bindings::begin_value(ab),
                bindings::stride_major(ab), bindings::begin_value(w),
                bindings::begin_value(z), bindings::stride_major(z),
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
    template< typename MatrixAB, typename VectorW, typename MatrixZ >
    static std::ptrdiff_t invoke( const char jobz, MatrixAB& ab, VectorW& w,
            MatrixZ& z, minimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::data_side< MatrixAB >::type uplo;
        bindings::detail::array< value_type > tmp_work( min_size_work(
                bindings::size_column(ab) ) );
        bindings::detail::array< real_type > tmp_rwork( min_size_rwork(
                bindings::size_column(ab) ) );
        return invoke( jobz, ab, w, z, workspace( tmp_work, tmp_rwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixAB, typename VectorW, typename MatrixZ >
    static std::ptrdiff_t invoke( const char jobz, MatrixAB& ab, VectorW& w,
            MatrixZ& z, optimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::data_side< MatrixAB >::type uplo;
        return invoke( jobz, ab, w, z, minimal_workspace() );
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
        return std::max< std::ptrdiff_t >(1,3*n-2);
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the hbev_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for hbev. Its overload differs for
// * MatrixAB&
// * VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorW, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t hbev( const char jobz, MatrixAB& ab, VectorW& w,
        MatrixZ& z, Workspace work ) {
    return hbev_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, w, z, work );
}

//
// Overloaded function for hbev. Its overload differs for
// * MatrixAB&
// * VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorW, typename MatrixZ >
inline std::ptrdiff_t hbev( const char jobz, MatrixAB& ab, VectorW& w,
        MatrixZ& z ) {
    return hbev_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, w, z, optimal_workspace() );
}

//
// Overloaded function for hbev. Its overload differs for
// * const MatrixAB&
// * VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorW, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t hbev( const char jobz, const MatrixAB& ab,
        VectorW& w, MatrixZ& z, Workspace work ) {
    return hbev_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, w, z, work );
}

//
// Overloaded function for hbev. Its overload differs for
// * const MatrixAB&
// * VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorW, typename MatrixZ >
inline std::ptrdiff_t hbev( const char jobz, const MatrixAB& ab,
        VectorW& w, MatrixZ& z ) {
    return hbev_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, w, z, optimal_workspace() );
}

//
// Overloaded function for hbev. Its overload differs for
// * MatrixAB&
// * const VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorW, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t hbev( const char jobz, MatrixAB& ab,
        const VectorW& w, MatrixZ& z, Workspace work ) {
    return hbev_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, w, z, work );
}

//
// Overloaded function for hbev. Its overload differs for
// * MatrixAB&
// * const VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorW, typename MatrixZ >
inline std::ptrdiff_t hbev( const char jobz, MatrixAB& ab,
        const VectorW& w, MatrixZ& z ) {
    return hbev_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, w, z, optimal_workspace() );
}

//
// Overloaded function for hbev. Its overload differs for
// * const MatrixAB&
// * const VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorW, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t hbev( const char jobz, const MatrixAB& ab,
        const VectorW& w, MatrixZ& z, Workspace work ) {
    return hbev_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, w, z, work );
}

//
// Overloaded function for hbev. Its overload differs for
// * const MatrixAB&
// * const VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorW, typename MatrixZ >
inline std::ptrdiff_t hbev( const char jobz, const MatrixAB& ab,
        const VectorW& w, MatrixZ& z ) {
    return hbev_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, w, z, optimal_workspace() );
}

//
// Overloaded function for hbev. Its overload differs for
// * MatrixAB&
// * VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorW, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t hbev( const char jobz, MatrixAB& ab, VectorW& w,
        const MatrixZ& z, Workspace work ) {
    return hbev_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, w, z, work );
}

//
// Overloaded function for hbev. Its overload differs for
// * MatrixAB&
// * VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorW, typename MatrixZ >
inline std::ptrdiff_t hbev( const char jobz, MatrixAB& ab, VectorW& w,
        const MatrixZ& z ) {
    return hbev_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, w, z, optimal_workspace() );
}

//
// Overloaded function for hbev. Its overload differs for
// * const MatrixAB&
// * VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorW, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t hbev( const char jobz, const MatrixAB& ab,
        VectorW& w, const MatrixZ& z, Workspace work ) {
    return hbev_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, w, z, work );
}

//
// Overloaded function for hbev. Its overload differs for
// * const MatrixAB&
// * VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorW, typename MatrixZ >
inline std::ptrdiff_t hbev( const char jobz, const MatrixAB& ab,
        VectorW& w, const MatrixZ& z ) {
    return hbev_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, w, z, optimal_workspace() );
}

//
// Overloaded function for hbev. Its overload differs for
// * MatrixAB&
// * const VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorW, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t hbev( const char jobz, MatrixAB& ab,
        const VectorW& w, const MatrixZ& z, Workspace work ) {
    return hbev_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, w, z, work );
}

//
// Overloaded function for hbev. Its overload differs for
// * MatrixAB&
// * const VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorW, typename MatrixZ >
inline std::ptrdiff_t hbev( const char jobz, MatrixAB& ab,
        const VectorW& w, const MatrixZ& z ) {
    return hbev_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, w, z, optimal_workspace() );
}

//
// Overloaded function for hbev. Its overload differs for
// * const MatrixAB&
// * const VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorW, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t hbev( const char jobz, const MatrixAB& ab,
        const VectorW& w, const MatrixZ& z, Workspace work ) {
    return hbev_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, w, z, work );
}

//
// Overloaded function for hbev. Its overload differs for
// * const MatrixAB&
// * const VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorW, typename MatrixZ >
inline std::ptrdiff_t hbev( const char jobz, const MatrixAB& ab,
        const VectorW& w, const MatrixZ& z ) {
    return hbev_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, w, z, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
