//
// Copyright (c) 2003--2009
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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_STEIN_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_STEIN_HPP

#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/is_complex.hpp>
#include <boost/numeric/bindings/traits/is_real.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {

inline void stein( const integer_t n, const float* d, const float* e,
        const integer_t m, const float* w, const integer_t* iblock,
        const integer_t* isplit, float* z, const integer_t ldz, float* work,
        integer_t* iwork, integer_t* ifail, integer_t& info ) {
    LAPACK_SSTEIN( &n, d, e, &m, w, iblock, isplit, z, &ldz, work, iwork,
            ifail, &info );
}
inline void stein( const integer_t n, const double* d, const double* e,
        const integer_t m, const double* w, const integer_t* iblock,
        const integer_t* isplit, double* z, const integer_t ldz, double* work,
        integer_t* iwork, integer_t* ifail, integer_t& info ) {
    LAPACK_DSTEIN( &n, d, e, &m, w, iblock, isplit, z, &ldz, work, iwork,
            ifail, &info );
}
inline void stein( const integer_t n, const float* d, const float* e,
        const integer_t m, const float* w, const integer_t* iblock,
        const integer_t* isplit, traits::complex_f* z, const integer_t ldz,
        float* work, integer_t* iwork, integer_t* ifail, integer_t& info ) {
    LAPACK_CSTEIN( &n, d, e, &m, w, iblock, isplit, traits::complex_ptr(z),
            &ldz, work, iwork, ifail, &info );
}
inline void stein( const integer_t n, const double* d, const double* e,
        const integer_t m, const double* w, const integer_t* iblock,
        const integer_t* isplit, traits::complex_d* z, const integer_t ldz,
        double* work, integer_t* iwork, integer_t* ifail, integer_t& info ) {
    LAPACK_ZSTEIN( &n, d, e, &m, w, iblock, isplit, traits::complex_ptr(z),
            &ldz, work, iwork, ifail, &info );
}
} // namespace detail

// value-type based template
template< typename ValueType, typename Enable = void >
struct stein_impl{};

// real specialization
template< typename ValueType >
struct stein_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename VectorD, typename VectorE, typename VectorW,
            typename VectorIBLOCK, typename VectorISPLIT, typename MatrixZ,
            typename VectorIFAIL, typename WORK, typename IWORK >
    static void invoke( const integer_t n, const VectorD& d, const VectorE& e,
            const integer_t m, const VectorW& w, const VectorIBLOCK& iblock,
            const VectorISPLIT& isplit, MatrixZ& z, VectorIFAIL& ifail,
            integer_t& info, detail::workspace2< WORK, IWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::vector_traits<
                VectorE >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::vector_traits<
                VectorW >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::matrix_traits<
                MatrixZ >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorIBLOCK >::value_type, typename traits::vector_traits<
                VectorISPLIT >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorIBLOCK >::value_type, typename traits::vector_traits<
                VectorIFAIL >::value_type >::value) );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( traits::vector_size(d) >= n );
        BOOST_ASSERT( traits::vector_size(e) >= n-1 );
        BOOST_ASSERT( traits::vector_size(w) >= n );
        BOOST_ASSERT( traits::vector_size(isplit) >= n );
        BOOST_ASSERT( traits::leading_dimension(z) >= std::max<
                std::ptrdiff_t >(1,n) );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( n ));
        BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
                min_size_iwork( n ));
        detail::stein( n, traits::vector_storage(d),
                traits::vector_storage(e), m, traits::vector_storage(w),
                traits::vector_storage(iblock),
                traits::vector_storage(isplit), traits::matrix_storage(z),
                traits::leading_dimension(z),
                traits::vector_storage(work.select(real_type())),
                traits::vector_storage(work.select(integer_t())),
                traits::vector_storage(ifail), info );
    }

    // minimal workspace specialization
    template< typename VectorD, typename VectorE, typename VectorW,
            typename VectorIBLOCK, typename VectorISPLIT, typename MatrixZ,
            typename VectorIFAIL >
    static void invoke( const integer_t n, const VectorD& d, const VectorE& e,
            const integer_t m, const VectorW& w, const VectorIBLOCK& iblock,
            const VectorISPLIT& isplit, MatrixZ& z, VectorIFAIL& ifail,
            integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work( n ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork( n ) );
        invoke( n, d, e, m, w, iblock, isplit, z, ifail, info,
                workspace( tmp_work, tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename VectorD, typename VectorE, typename VectorW,
            typename VectorIBLOCK, typename VectorISPLIT, typename MatrixZ,
            typename VectorIFAIL >
    static void invoke( const integer_t n, const VectorD& d, const VectorE& e,
            const integer_t m, const VectorW& w, const VectorIBLOCK& iblock,
            const VectorISPLIT& isplit, MatrixZ& z, VectorIFAIL& ifail,
            integer_t& info, optimal_workspace work ) {
        invoke( n, d, e, m, w, iblock, isplit, z, ifail, info,
                minimal_workspace() );
    }

    static integer_t min_size_work( const integer_t n ) {
        return 5*n;
    }

    static integer_t min_size_iwork( const integer_t n ) {
        return n;
    }
};

// complex specialization
template< typename ValueType >
struct stein_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename VectorD, typename VectorE, typename VectorW,
            typename VectorIBLOCK, typename VectorISPLIT, typename MatrixZ,
            typename VectorIFAIL, typename WORK, typename IWORK >
    static void invoke( const integer_t n, const VectorD& d, const VectorE& e,
            const integer_t m, const VectorW& w, const VectorIBLOCK& iblock,
            const VectorISPLIT& isplit, MatrixZ& z, VectorIFAIL& ifail,
            integer_t& info, detail::workspace2< WORK, IWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::vector_traits<
                VectorE >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::vector_traits<
                VectorW >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorIBLOCK >::value_type, typename traits::vector_traits<
                VectorISPLIT >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorIBLOCK >::value_type, typename traits::vector_traits<
                VectorIFAIL >::value_type >::value) );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( traits::vector_size(d) >= n );
        BOOST_ASSERT( traits::vector_size(e) >= n-1 );
        BOOST_ASSERT( traits::vector_size(w) >= n );
        BOOST_ASSERT( traits::vector_size(isplit) >= n );
        BOOST_ASSERT( traits::leading_dimension(z) >= std::max<
                std::ptrdiff_t >(1,n) );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( n ));
        BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
                min_size_iwork( n ));
        detail::stein( n, traits::vector_storage(d),
                traits::vector_storage(e), m, traits::vector_storage(w),
                traits::vector_storage(iblock),
                traits::vector_storage(isplit), traits::matrix_storage(z),
                traits::leading_dimension(z),
                traits::vector_storage(work.select(real_type())),
                traits::vector_storage(work.select(integer_t())),
                traits::vector_storage(ifail), info );
    }

    // minimal workspace specialization
    template< typename VectorD, typename VectorE, typename VectorW,
            typename VectorIBLOCK, typename VectorISPLIT, typename MatrixZ,
            typename VectorIFAIL >
    static void invoke( const integer_t n, const VectorD& d, const VectorE& e,
            const integer_t m, const VectorW& w, const VectorIBLOCK& iblock,
            const VectorISPLIT& isplit, MatrixZ& z, VectorIFAIL& ifail,
            integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work( n ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork( n ) );
        invoke( n, d, e, m, w, iblock, isplit, z, ifail, info,
                workspace( tmp_work, tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename VectorD, typename VectorE, typename VectorW,
            typename VectorIBLOCK, typename VectorISPLIT, typename MatrixZ,
            typename VectorIFAIL >
    static void invoke( const integer_t n, const VectorD& d, const VectorE& e,
            const integer_t m, const VectorW& w, const VectorIBLOCK& iblock,
            const VectorISPLIT& isplit, MatrixZ& z, VectorIFAIL& ifail,
            integer_t& info, optimal_workspace work ) {
        invoke( n, d, e, m, w, iblock, isplit, z, ifail, info,
                minimal_workspace() );
    }

    static integer_t min_size_work( const integer_t n ) {
        return 5*n;
    }

    static integer_t min_size_iwork( const integer_t n ) {
        return n;
    }
};


// template function to call stein
template< typename VectorD, typename VectorE, typename VectorW,
        typename VectorIBLOCK, typename VectorISPLIT, typename MatrixZ,
        typename VectorIFAIL, typename Workspace >
inline integer_t stein( const integer_t n, const VectorD& d,
        const VectorE& e, const integer_t m, const VectorW& w,
        const VectorIBLOCK& iblock, const VectorISPLIT& isplit, MatrixZ& z,
        VectorIFAIL& ifail, Workspace work ) {
    typedef typename traits::matrix_traits< MatrixZ >::value_type value_type;
    integer_t info(0);
    stein_impl< value_type >::invoke( n, d, e, m, w, iblock, isplit, z,
            ifail, info, work );
    return info;
}

// template function to call stein, default workspace type
template< typename VectorD, typename VectorE, typename VectorW,
        typename VectorIBLOCK, typename VectorISPLIT, typename MatrixZ,
        typename VectorIFAIL >
inline integer_t stein( const integer_t n, const VectorD& d,
        const VectorE& e, const integer_t m, const VectorW& w,
        const VectorIBLOCK& iblock, const VectorISPLIT& isplit, MatrixZ& z,
        VectorIFAIL& ifail ) {
    typedef typename traits::matrix_traits< MatrixZ >::value_type value_type;
    integer_t info(0);
    stein_impl< value_type >::invoke( n, d, e, m, w, iblock, isplit, z,
            ifail, info, optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
