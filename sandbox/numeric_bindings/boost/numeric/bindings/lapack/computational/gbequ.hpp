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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GBEQU_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GBEQU_HPP

#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
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

inline void gbequ( const integer_t m, const integer_t n, const integer_t kl,
        const integer_t ku, const float* ab, const integer_t ldab, float* r,
        float* c, float& rowcnd, float& colcnd, float& amax,
        integer_t& info ) {
    LAPACK_SGBEQU( &m, &n, &kl, &ku, ab, &ldab, r, c, &rowcnd, &colcnd, &amax,
            &info );
}

inline void gbequ( const integer_t m, const integer_t n, const integer_t kl,
        const integer_t ku, const double* ab, const integer_t ldab, double* r,
        double* c, double& rowcnd, double& colcnd, double& amax,
        integer_t& info ) {
    LAPACK_DGBEQU( &m, &n, &kl, &ku, ab, &ldab, r, c, &rowcnd, &colcnd, &amax,
            &info );
}

inline void gbequ( const integer_t m, const integer_t n, const integer_t kl,
        const integer_t ku, const traits::complex_f* ab, const integer_t ldab,
        float* r, float* c, float& rowcnd, float& colcnd, float& amax,
        integer_t& info ) {
    LAPACK_CGBEQU( &m, &n, &kl, &ku, traits::complex_ptr(ab), &ldab, r, c,
            &rowcnd, &colcnd, &amax, &info );
}

inline void gbequ( const integer_t m, const integer_t n, const integer_t kl,
        const integer_t ku, const traits::complex_d* ab, const integer_t ldab,
        double* r, double* c, double& rowcnd, double& colcnd, double& amax,
        integer_t& info ) {
    LAPACK_ZGBEQU( &m, &n, &kl, &ku, traits::complex_ptr(ab), &ldab, r, c,
            &rowcnd, &colcnd, &amax, &info );
}

} // namespace detail

// value-type based template
template< typename ValueType, typename Enable = void >
struct gbequ_impl{};

// real specialization
template< typename ValueType >
struct gbequ_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixAB, typename VectorR, typename VectorC >
    static void invoke( const integer_t m, const integer_t n,
            const integer_t kl, const integer_t ku, const MatrixAB& ab,
            VectorR& r, VectorC& c, real_type& rowcnd, real_type& colcnd,
            real_type& amax, integer_t& info ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixAB >::value_type, typename traits::vector_traits<
                VectorR >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixAB >::value_type, typename traits::vector_traits<
                VectorC >::value_type >::value) );
        BOOST_ASSERT( m >= 0 );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( kl >= 0 );
        BOOST_ASSERT( ku >= 0 );
        BOOST_ASSERT( traits::leading_dimension(ab) >= kl+ku+1 );
        detail::gbequ( m, n, kl, ku, traits::matrix_storage(ab),
                traits::leading_dimension(ab), traits::vector_storage(r),
                traits::vector_storage(c), rowcnd, colcnd, amax, info );
    }
};

// complex specialization
template< typename ValueType >
struct gbequ_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixAB, typename VectorR, typename VectorC >
    static void invoke( const integer_t m, const integer_t n,
            const integer_t kl, const integer_t ku, const MatrixAB& ab,
            VectorR& r, VectorC& c, real_type& rowcnd, real_type& colcnd,
            real_type& amax, integer_t& info ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorR >::value_type, typename traits::vector_traits<
                VectorC >::value_type >::value) );
        BOOST_ASSERT( m >= 0 );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( kl >= 0 );
        BOOST_ASSERT( ku >= 0 );
        BOOST_ASSERT( traits::leading_dimension(ab) >= kl+ku+1 );
        detail::gbequ( m, n, kl, ku, traits::matrix_storage(ab),
                traits::leading_dimension(ab), traits::vector_storage(r),
                traits::vector_storage(c), rowcnd, colcnd, amax, info );
    }
};


// template function to call gbequ
template< typename MatrixAB, typename VectorR, typename VectorC >
inline integer_t gbequ( const integer_t m, const integer_t n,
        const integer_t kl, const integer_t ku, const MatrixAB& ab,
        VectorR& r, VectorC& c, typename traits::type_traits<
        typename traits::matrix_traits<
        MatrixAB >::value_type >::real_type& rowcnd,
        typename traits::type_traits< typename traits::matrix_traits<
        MatrixAB >::value_type >::real_type& colcnd,
        typename traits::type_traits< typename traits::matrix_traits<
        MatrixAB >::value_type >::real_type& amax ) {
    typedef typename traits::matrix_traits< MatrixAB >::value_type value_type;
    integer_t info(0);
    gbequ_impl< value_type >::invoke( m, n, kl, ku, ab, r, c, rowcnd,
            colcnd, amax, info );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
