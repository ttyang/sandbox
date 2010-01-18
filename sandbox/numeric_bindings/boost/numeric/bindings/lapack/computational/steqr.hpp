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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_STEQR_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_STEQR_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_complex.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/is_real.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

//
// The LAPACK-backend for steqr is the netlib-compatible backend.
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
inline std::ptrdiff_t steqr( const char compz, const fortran_int_t n, float* d,
        float* e, float* z, const fortran_int_t ldz, float* work ) {
    fortran_int_t info(0);
    LAPACK_SSTEQR( &compz, &n, d, e, z, &ldz, work, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t steqr( const char compz, const fortran_int_t n,
        double* d, double* e, double* z, const fortran_int_t ldz,
        double* work ) {
    fortran_int_t info(0);
    LAPACK_DSTEQR( &compz, &n, d, e, z, &ldz, work, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
inline std::ptrdiff_t steqr( const char compz, const fortran_int_t n, float* d,
        float* e, std::complex<float>* z, const fortran_int_t ldz,
        float* work ) {
    fortran_int_t info(0);
    LAPACK_CSTEQR( &compz, &n, d, e, z, &ldz, work, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
inline std::ptrdiff_t steqr( const char compz, const fortran_int_t n,
        double* d, double* e, std::complex<double>* z,
        const fortran_int_t ldz, double* work ) {
    fortran_int_t info(0);
    LAPACK_ZSTEQR( &compz, &n, d, e, z, &ldz, work, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to steqr.
//
template< typename Value, typename Enable = void >
struct steqr_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct steqr_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorD, typename VectorE, typename MatrixZ,
            typename WORK >
    static std::ptrdiff_t invoke( const char compz, VectorD& d, VectorE& e,
            MatrixZ& z, detail::workspace1< WORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixZ >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorD >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorE >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixZ >::value) );
        BOOST_ASSERT( bindings::size(d) >= 0 );
        BOOST_ASSERT( bindings::size(e) >= bindings::size(d)-1 );
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work( bindings::size(d), compz ));
        BOOST_ASSERT( bindings::size_minor(z) == 1 ||
                bindings::stride_minor(z) == 1 );
        BOOST_ASSERT( compz == 'N' || compz == 'V' || compz == 'I' );
        return detail::steqr( compz, bindings::size(d),
                bindings::begin_value(d), bindings::begin_value(e),
                bindings::begin_value(z), bindings::stride_major(z),
                bindings::begin_value(work.select(real_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename VectorD, typename VectorE, typename MatrixZ >
    static std::ptrdiff_t invoke( const char compz, VectorD& d, VectorE& e,
            MatrixZ& z, minimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< real_type > tmp_work( min_size_work(
                bindings::size(d), compz ) );
        return invoke( compz, d, e, z, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename VectorD, typename VectorE, typename MatrixZ >
    static std::ptrdiff_t invoke( const char compz, VectorD& d, VectorE& e,
            MatrixZ& z, optimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        return invoke( compz, d, e, z, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n,
            const char compz ) {
        if ( compz == 'N' ) {
            return 1;
        } else {
            return std::max< std::ptrdiff_t >( 1, 2*n-2 );
        }
    }
};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct steqr_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorD, typename VectorE, typename MatrixZ,
            typename WORK >
    static std::ptrdiff_t invoke( const char compz, VectorD& d, VectorE& e,
            MatrixZ& z, detail::workspace1< WORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorD >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorE >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixZ >::value) );
        BOOST_ASSERT( bindings::size(d) >= 0 );
        BOOST_ASSERT( bindings::size(e) >= bindings::size(d)-1 );
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work( bindings::size(d), compz ));
        BOOST_ASSERT( bindings::size_minor(z) == 1 ||
                bindings::stride_minor(z) == 1 );
        BOOST_ASSERT( compz == 'N' || compz == 'V' || compz == 'I' );
        return detail::steqr( compz, bindings::size(d),
                bindings::begin_value(d), bindings::begin_value(e),
                bindings::begin_value(z), bindings::stride_major(z),
                bindings::begin_value(work.select(real_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename VectorD, typename VectorE, typename MatrixZ >
    static std::ptrdiff_t invoke( const char compz, VectorD& d, VectorE& e,
            MatrixZ& z, minimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< real_type > tmp_work( min_size_work(
                bindings::size(d), compz ) );
        return invoke( compz, d, e, z, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename VectorD, typename VectorE, typename MatrixZ >
    static std::ptrdiff_t invoke( const char compz, VectorD& d, VectorE& e,
            MatrixZ& z, optimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        return invoke( compz, d, e, z, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n,
            const char compz ) {
        if ( compz == 'N' ) {
            return 1;
        } else {
            return std::max< std::ptrdiff_t >( 1, 2*n-2 );
        }
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the steqr_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for steqr. Its overload differs for
// * VectorD&
// * VectorE&
// * MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
steqr( const char compz, VectorD& d, VectorE& e, MatrixZ& z,
        Workspace work ) {
    return steqr_impl< typename bindings::value_type<
            MatrixZ >::type >::invoke( compz, d, e, z, work );
}

//
// Overloaded function for steqr. Its overload differs for
// * VectorD&
// * VectorE&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
steqr( const char compz, VectorD& d, VectorE& e, MatrixZ& z ) {
    return steqr_impl< typename bindings::value_type<
            MatrixZ >::type >::invoke( compz, d, e, z, optimal_workspace() );
}

//
// Overloaded function for steqr. Its overload differs for
// * const VectorD&
// * VectorE&
// * MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
steqr( const char compz, const VectorD& d, VectorE& e, MatrixZ& z,
        Workspace work ) {
    return steqr_impl< typename bindings::value_type<
            MatrixZ >::type >::invoke( compz, d, e, z, work );
}

//
// Overloaded function for steqr. Its overload differs for
// * const VectorD&
// * VectorE&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
steqr( const char compz, const VectorD& d, VectorE& e, MatrixZ& z ) {
    return steqr_impl< typename bindings::value_type<
            MatrixZ >::type >::invoke( compz, d, e, z, optimal_workspace() );
}

//
// Overloaded function for steqr. Its overload differs for
// * VectorD&
// * const VectorE&
// * MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
steqr( const char compz, VectorD& d, const VectorE& e, MatrixZ& z,
        Workspace work ) {
    return steqr_impl< typename bindings::value_type<
            MatrixZ >::type >::invoke( compz, d, e, z, work );
}

//
// Overloaded function for steqr. Its overload differs for
// * VectorD&
// * const VectorE&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
steqr( const char compz, VectorD& d, const VectorE& e, MatrixZ& z ) {
    return steqr_impl< typename bindings::value_type<
            MatrixZ >::type >::invoke( compz, d, e, z, optimal_workspace() );
}

//
// Overloaded function for steqr. Its overload differs for
// * const VectorD&
// * const VectorE&
// * MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
steqr( const char compz, const VectorD& d, const VectorE& e, MatrixZ& z,
        Workspace work ) {
    return steqr_impl< typename bindings::value_type<
            MatrixZ >::type >::invoke( compz, d, e, z, work );
}

//
// Overloaded function for steqr. Its overload differs for
// * const VectorD&
// * const VectorE&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
steqr( const char compz, const VectorD& d, const VectorE& e,
        MatrixZ& z ) {
    return steqr_impl< typename bindings::value_type<
            MatrixZ >::type >::invoke( compz, d, e, z, optimal_workspace() );
}

//
// Overloaded function for steqr. Its overload differs for
// * VectorD&
// * VectorE&
// * const MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
steqr( const char compz, VectorD& d, VectorE& e, const MatrixZ& z,
        Workspace work ) {
    return steqr_impl< typename bindings::value_type<
            MatrixZ >::type >::invoke( compz, d, e, z, work );
}

//
// Overloaded function for steqr. Its overload differs for
// * VectorD&
// * VectorE&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
steqr( const char compz, VectorD& d, VectorE& e, const MatrixZ& z ) {
    return steqr_impl< typename bindings::value_type<
            MatrixZ >::type >::invoke( compz, d, e, z, optimal_workspace() );
}

//
// Overloaded function for steqr. Its overload differs for
// * const VectorD&
// * VectorE&
// * const MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
steqr( const char compz, const VectorD& d, VectorE& e, const MatrixZ& z,
        Workspace work ) {
    return steqr_impl< typename bindings::value_type<
            MatrixZ >::type >::invoke( compz, d, e, z, work );
}

//
// Overloaded function for steqr. Its overload differs for
// * const VectorD&
// * VectorE&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
steqr( const char compz, const VectorD& d, VectorE& e,
        const MatrixZ& z ) {
    return steqr_impl< typename bindings::value_type<
            MatrixZ >::type >::invoke( compz, d, e, z, optimal_workspace() );
}

//
// Overloaded function for steqr. Its overload differs for
// * VectorD&
// * const VectorE&
// * const MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
steqr( const char compz, VectorD& d, const VectorE& e, const MatrixZ& z,
        Workspace work ) {
    return steqr_impl< typename bindings::value_type<
            MatrixZ >::type >::invoke( compz, d, e, z, work );
}

//
// Overloaded function for steqr. Its overload differs for
// * VectorD&
// * const VectorE&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
steqr( const char compz, VectorD& d, const VectorE& e,
        const MatrixZ& z ) {
    return steqr_impl< typename bindings::value_type<
            MatrixZ >::type >::invoke( compz, d, e, z, optimal_workspace() );
}

//
// Overloaded function for steqr. Its overload differs for
// * const VectorD&
// * const VectorE&
// * const MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
steqr( const char compz, const VectorD& d, const VectorE& e,
        const MatrixZ& z, Workspace work ) {
    return steqr_impl< typename bindings::value_type<
            MatrixZ >::type >::invoke( compz, d, e, z, work );
}

//
// Overloaded function for steqr. Its overload differs for
// * const VectorD&
// * const VectorE&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
steqr( const char compz, const VectorD& d, const VectorE& e,
        const MatrixZ& z ) {
    return steqr_impl< typename bindings::value_type<
            MatrixZ >::type >::invoke( compz, d, e, z, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
