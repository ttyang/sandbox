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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_HPTRS_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_HPTRS_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/uplo_tag.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The LAPACK-backend for hptrs is the netlib-compatible backend.
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
inline std::ptrdiff_t hptrs( UpLo, const fortran_int_t n,
        const fortran_int_t nrhs, const std::complex<float>* ap,
        const fortran_int_t* ipiv, std::complex<float>* b,
        const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_CHPTRS( &lapack_option< UpLo >::value, &n, &nrhs, ap, ipiv, b,
            &ldb, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename UpLo >
inline std::ptrdiff_t hptrs( UpLo, const fortran_int_t n,
        const fortran_int_t nrhs, const std::complex<double>* ap,
        const fortran_int_t* ipiv, std::complex<double>* b,
        const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_ZHPTRS( &lapack_option< UpLo >::value, &n, &nrhs, ap, ipiv, b,
            &ldb, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to hptrs.
//
template< typename Value >
struct hptrs_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAP, typename VectorIPIV, typename MatrixB >
    static std::ptrdiff_t invoke( const MatrixAP& ap, const VectorIPIV& ipiv,
            MatrixB& b ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixAP >::type uplo;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAP >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixB >::value) );
        BOOST_ASSERT( bindings::size(ipiv) >= bindings::size_column(ap) );
        BOOST_ASSERT( bindings::size_column(ap) >= 0 );
        BOOST_ASSERT( bindings::size_column(b) >= 0 );
        BOOST_ASSERT( bindings::size_minor(b) == 1 ||
                bindings::stride_minor(b) == 1 );
        BOOST_ASSERT( bindings::stride_major(b) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(ap)) );
        return detail::hptrs( uplo(), bindings::size_column(ap),
                bindings::size_column(b), bindings::begin_value(ap),
                bindings::begin_value(ipiv), bindings::begin_value(b),
                bindings::stride_major(b) );
    }

};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the hptrs_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for hptrs. Its overload differs for
// * MatrixB&
//
template< typename MatrixAP, typename VectorIPIV, typename MatrixB >
inline std::ptrdiff_t hptrs( const MatrixAP& ap, const VectorIPIV& ipiv,
        MatrixB& b ) {
    return hptrs_impl< typename value< MatrixAP >::type >::invoke( ap,
            ipiv, b );
}

//
// Overloaded function for hptrs. Its overload differs for
// * const MatrixB&
//
template< typename MatrixAP, typename VectorIPIV, typename MatrixB >
inline std::ptrdiff_t hptrs( const MatrixAP& ap, const VectorIPIV& ipiv,
        const MatrixB& b ) {
    return hptrs_impl< typename value< MatrixAP >::type >::invoke( ap,
            ipiv, b );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
