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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_HESV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_HESV_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_column_major.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/traits/detail/utils.hpp>
#include <boost/numeric/bindings/uplo_tag.hpp>
#include <boost/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The LAPACK-backend for hesv is the netlib-compatible backend.
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
inline std::ptrdiff_t hesv( const UpLo uplo, const fortran_int_t n,
        const fortran_int_t nrhs, std::complex<float>* a,
        const fortran_int_t lda, fortran_int_t* ipiv, std::complex<float>* b,
        const fortran_int_t ldb, std::complex<float>* work,
        const fortran_int_t lwork ) {
    fortran_int_t info(0);
    LAPACK_CHESV( &lapack_option< UpLo >::value, &n, &nrhs, a, &lda, ipiv, b,
            &ldb, work, &lwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename UpLo >
inline std::ptrdiff_t hesv( const UpLo uplo, const fortran_int_t n,
        const fortran_int_t nrhs, std::complex<double>* a,
        const fortran_int_t lda, fortran_int_t* ipiv, std::complex<double>* b,
        const fortran_int_t ldb, std::complex<double>* work,
        const fortran_int_t lwork ) {
    fortran_int_t info(0);
    LAPACK_ZHESV( &lapack_option< UpLo >::value, &n, &nrhs, a, &lda, ipiv, b,
            &ldb, work, &lwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to hesv.
//
template< typename Value >
struct hesv_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename VectorIPIV, typename MatrixB,
            typename WORK >
    static std::ptrdiff_t invoke( MatrixA& a, VectorIPIV& ipiv, MatrixB& b,
            detail::workspace1< WORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixA >::type uplo;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixB >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorIPIV >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixB >::value) );
        BOOST_ASSERT( bindings::size(work.select(value_type())) >=
                min_size_work());
        BOOST_ASSERT( bindings::size_column(a) >= 0 );
        BOOST_ASSERT( bindings::size_column(b) >= 0 );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        BOOST_ASSERT( bindings::size_minor(b) == 1 ||
                bindings::stride_minor(b) == 1 );
        BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        BOOST_ASSERT( bindings::stride_major(b) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        return detail::hesv( uplo(), bindings::size_column(a),
                bindings::size_column(b), bindings::begin_value(a),
                bindings::stride_major(a), bindings::begin_value(ipiv),
                bindings::begin_value(b), bindings::stride_major(b),
                bindings::begin_value(work.select(value_type())),
                bindings::size(work.select(value_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename VectorIPIV, typename MatrixB >
    static std::ptrdiff_t invoke( MatrixA& a, VectorIPIV& ipiv, MatrixB& b,
            minimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixA >::type uplo;
        bindings::detail::array< value_type > tmp_work( min_size_work() );
        return invoke( a, ipiv, b, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename VectorIPIV, typename MatrixB >
    static std::ptrdiff_t invoke( MatrixA& a, VectorIPIV& ipiv, MatrixB& b,
            optimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixA >::type uplo;
        value_type opt_size_work;
        detail::hesv( uplo(), bindings::size_column(a),
                bindings::size_column(b), bindings::begin_value(a),
                bindings::stride_major(a), bindings::begin_value(ipiv),
                bindings::begin_value(b), bindings::stride_major(b),
                &opt_size_work, -1 );
        bindings::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        return invoke( a, ipiv, b, workspace( tmp_work ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work() {
        return 1;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the hesv_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for hesv. Its overload differs for
// * MatrixA&
// * MatrixB&
// * User-defined workspace
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
hesv( MatrixA& a, VectorIPIV& ipiv, MatrixB& b, Workspace work ) {
    return hesv_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, ipiv, b, work );
}

//
// Overloaded function for hesv. Its overload differs for
// * MatrixA&
// * MatrixB&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB >
inline typename boost::disable_if< detail::is_workspace< MatrixB >,
        std::ptrdiff_t >::type
hesv( MatrixA& a, VectorIPIV& ipiv, MatrixB& b ) {
    return hesv_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, ipiv, b, optimal_workspace() );
}

//
// Overloaded function for hesv. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * User-defined workspace
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
hesv( const MatrixA& a, VectorIPIV& ipiv, MatrixB& b, Workspace work ) {
    return hesv_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, ipiv, b, work );
}

//
// Overloaded function for hesv. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB >
inline typename boost::disable_if< detail::is_workspace< MatrixB >,
        std::ptrdiff_t >::type
hesv( const MatrixA& a, VectorIPIV& ipiv, MatrixB& b ) {
    return hesv_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, ipiv, b, optimal_workspace() );
}

//
// Overloaded function for hesv. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * User-defined workspace
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
hesv( MatrixA& a, VectorIPIV& ipiv, const MatrixB& b, Workspace work ) {
    return hesv_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, ipiv, b, work );
}

//
// Overloaded function for hesv. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB >
inline typename boost::disable_if< detail::is_workspace< MatrixB >,
        std::ptrdiff_t >::type
hesv( MatrixA& a, VectorIPIV& ipiv, const MatrixB& b ) {
    return hesv_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, ipiv, b, optimal_workspace() );
}

//
// Overloaded function for hesv. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * User-defined workspace
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
hesv( const MatrixA& a, VectorIPIV& ipiv, const MatrixB& b,
        Workspace work ) {
    return hesv_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, ipiv, b, work );
}

//
// Overloaded function for hesv. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB >
inline typename boost::disable_if< detail::is_workspace< MatrixB >,
        std::ptrdiff_t >::type
hesv( const MatrixA& a, VectorIPIV& ipiv, const MatrixB& b ) {
    return hesv_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, ipiv, b, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
