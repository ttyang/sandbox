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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GTTRS_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GTTRS_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/is_column_major.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The LAPACK-backend for gttrs is the netlib-compatible backend.
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
template< typename Trans >
inline std::ptrdiff_t gttrs( const Trans trans, const fortran_int_t n,
        const fortran_int_t nrhs, const float* dl, const float* d,
        const float* du, const float* du2, const fortran_int_t* ipiv,
        float* b, const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_SGTTRS( &lapack_option< Trans >::value, &n, &nrhs, dl, d, du, du2,
            ipiv, b, &ldb, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
template< typename Trans >
inline std::ptrdiff_t gttrs( const Trans trans, const fortran_int_t n,
        const fortran_int_t nrhs, const double* dl, const double* d,
        const double* du, const double* du2, const fortran_int_t* ipiv,
        double* b, const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_DGTTRS( &lapack_option< Trans >::value, &n, &nrhs, dl, d, du, du2,
            ipiv, b, &ldb, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
template< typename Trans >
inline std::ptrdiff_t gttrs( const Trans trans, const fortran_int_t n,
        const fortran_int_t nrhs, const std::complex<float>* dl,
        const std::complex<float>* d, const std::complex<float>* du,
        const std::complex<float>* du2, const fortran_int_t* ipiv,
        std::complex<float>* b, const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_CGTTRS( &lapack_option< Trans >::value, &n, &nrhs, dl, d, du, du2,
            ipiv, b, &ldb, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename Trans >
inline std::ptrdiff_t gttrs( const Trans trans, const fortran_int_t n,
        const fortran_int_t nrhs, const std::complex<double>* dl,
        const std::complex<double>* d, const std::complex<double>* du,
        const std::complex<double>* du2, const fortran_int_t* ipiv,
        std::complex<double>* b, const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_ZGTTRS( &lapack_option< Trans >::value, &n, &nrhs, dl, d, du, du2,
            ipiv, b, &ldb, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to gttrs.
//
template< typename Value >
struct gttrs_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorDL, typename VectorD, typename VectorDU,
            typename VectorDU2, typename VectorIPIV, typename MatrixB >
    static std::ptrdiff_t invoke( const VectorDL& dl, const VectorD& d,
            const VectorDU& du, const VectorDU2& du2, const VectorIPIV& ipiv,
            MatrixB& b ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef tag::column_major order;
        typedef typename result_of::trans_tag< VectorD, order >::type trans;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixB >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorD >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorDU >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorDU2 >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorDL >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixB >::value) );
        BOOST_ASSERT( bindings::size(d) >= bindings::size_column_op(d,
                trans()) );
        BOOST_ASSERT( bindings::size(dl) >= bindings::size_column_op(d,
                trans())-1 );
        BOOST_ASSERT( bindings::size(du) >= bindings::size_column_op(d,
                trans())-1 );
        BOOST_ASSERT( bindings::size(du2) >= bindings::size_column_op(d,
                trans())-2 );
        BOOST_ASSERT( bindings::size(ipiv) >= bindings::size_column_op(d,
                trans()) );
        BOOST_ASSERT( bindings::size_column(b) >= 0 );
        BOOST_ASSERT( bindings::size_minor(b) == 1 ||
                bindings::stride_minor(b) == 1 );
        BOOST_ASSERT( bindings::stride_major(b) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column_op(d, trans())) );
        return detail::gttrs( trans(), bindings::size_column_op(d, trans()),
                bindings::size_column(b), bindings::begin_value(dl),
                bindings::begin_value(d), bindings::begin_value(du),
                bindings::begin_value(du2), bindings::begin_value(ipiv),
                bindings::begin_value(b), bindings::stride_major(b) );
    }

};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the gttrs_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for gttrs. Its overload differs for
// * MatrixB&
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename VectorDU2, typename VectorIPIV, typename MatrixB >
inline std::ptrdiff_t gttrs( const VectorDL& dl, const VectorD& d,
        const VectorDU& du, const VectorDU2& du2, const VectorIPIV& ipiv,
        MatrixB& b ) {
    return gttrs_impl< typename bindings::value_type<
            VectorDL >::type >::invoke( dl, d, du, du2, ipiv, b );
}

//
// Overloaded function for gttrs. Its overload differs for
// * const MatrixB&
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename VectorDU2, typename VectorIPIV, typename MatrixB >
inline std::ptrdiff_t gttrs( const VectorDL& dl, const VectorD& d,
        const VectorDU& du, const VectorDU2& du2, const VectorIPIV& ipiv,
        const MatrixB& b ) {
    return gttrs_impl< typename bindings::value_type<
            VectorDL >::type >::invoke( dl, d, du, du2, ipiv, b );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
