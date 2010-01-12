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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_PBSTF_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_PBSTF_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/bandwidth.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/data_side.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The LAPACK-backend for pbstf is the netlib-compatible backend.
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
inline std::ptrdiff_t pbstf( UpLo, const fortran_int_t n,
        const fortran_int_t kd, float* ab, const fortran_int_t ldab ) {
    fortran_int_t info(0);
    LAPACK_SPBSTF( &lapack_option< UpLo >::value, &n, &kd, ab, &ldab, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
template< typename UpLo >
inline std::ptrdiff_t pbstf( UpLo, const fortran_int_t n,
        const fortran_int_t kd, double* ab, const fortran_int_t ldab ) {
    fortran_int_t info(0);
    LAPACK_DPBSTF( &lapack_option< UpLo >::value, &n, &kd, ab, &ldab, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
template< typename UpLo >
inline std::ptrdiff_t pbstf( UpLo, const fortran_int_t n,
        const fortran_int_t kd, std::complex<float>* ab,
        const fortran_int_t ldab ) {
    fortran_int_t info(0);
    LAPACK_CPBSTF( &lapack_option< UpLo >::value, &n, &kd, ab, &ldab, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename UpLo >
inline std::ptrdiff_t pbstf( UpLo, const fortran_int_t n,
        const fortran_int_t kd, std::complex<double>* ab,
        const fortran_int_t ldab ) {
    fortran_int_t info(0);
    LAPACK_ZPBSTF( &lapack_option< UpLo >::value, &n, &kd, ab, &ldab, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to pbstf.
//
template< typename Value >
struct pbstf_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAB >
    static std::ptrdiff_t invoke( const fortran_int_t n, MatrixAB& ab ) {
        BOOST_STATIC_ASSERT( (is_mutable< MatrixAB >::value) );
        BOOST_ASSERT( bandwidth_upper(ab) >= 0 );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( size_minor(ab) == 1 || stride_minor(ab) == 1 );
        BOOST_ASSERT( stride_major(ab) >= bandwidth_upper(ab)+1 );
        return detail::pbstf( uplo(), n, bandwidth_upper(ab), begin_value(ab),
                stride_major(ab) );
    }

};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the pbstf_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for pbstf. Its overload differs for
// * MatrixAB&
//
template< typename MatrixAB >
inline std::ptrdiff_t pbstf( const fortran_int_t n, MatrixAB& ab ) {
    return pbstf_impl< typename value< MatrixAB >::type >::invoke( n,
            ab );
}

//
// Overloaded function for pbstf. Its overload differs for
// * const MatrixAB&
//
template< typename MatrixAB >
inline std::ptrdiff_t pbstf( const fortran_int_t n,
        const MatrixAB& ab ) {
    return pbstf_impl< typename value< MatrixAB >::type >::invoke( n,
            ab );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
