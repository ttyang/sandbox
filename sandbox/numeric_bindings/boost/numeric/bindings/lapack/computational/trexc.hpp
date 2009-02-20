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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_TREXC_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_TREXC_HPP

#include <boost/numeric/bindings/lapack/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/is_complex.hpp>
#include <boost/numeric/bindings/traits/is_real.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/utility/enable_if.hpp>
#include <cassert>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void trexc( char const compq, integer_t const n, float* t,
            integer_t const ldt, float* q, integer_t const ldq,
            integer_t& ifst, integer_t& ilst, float* work, integer_t& info ) {
        LAPACK_STREXC( &compq, &n, t, &ldt, q, &ldq, &ifst, &ilst, work,
                &info );
    }
    inline void trexc( char const compq, integer_t const n, double* t,
            integer_t const ldt, double* q, integer_t const ldq,
            integer_t& ifst, integer_t& ilst, double* work, integer_t& info ) {
        LAPACK_DTREXC( &compq, &n, t, &ldt, q, &ldq, &ifst, &ilst, work,
                &info );
    }
    inline void trexc( char const compq, integer_t const n,
            traits::complex_f* t, integer_t const ldt, traits::complex_f* q,
            integer_t const ldq, integer_t const ifst, integer_t const ilst,
            integer_t& info ) {
        LAPACK_CTREXC( &compq, &n, traits::complex_ptr(t), &ldt,
                traits::complex_ptr(q), &ldq, &ifst, &ilst, &info );
    }
    inline void trexc( char const compq, integer_t const n,
            traits::complex_d* t, integer_t const ldt, traits::complex_d* q,
            integer_t const ldq, integer_t const ifst, integer_t const ilst,
            integer_t& info ) {
        LAPACK_ZTREXC( &compq, &n, traits::complex_ptr(t), &ldt,
                traits::complex_ptr(q), &ldq, &ifst, &ilst, &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct trexc_impl{};

// real specialization
template< typename ValueType >
struct trexc_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixT, typename MatrixQ >
    static void compute( char const compq, MatrixT& t, MatrixQ& q,
            integer_t& ifst, integer_t& ilst, integer_t& info ) {
#ifndef NDEBUG
        assert( compq == 'V' || compq == 'N' );
        assert( traits::matrix_size2(t) >= 0 );
        assert( traits::leading_dimension(t) >= std::max(1,
                traits::matrix_size2(t)) );
        assert( traits::leading_dimension(q) >= std::max(1,
                traits::matrix_size2(t)) );
        assert( traits::vector_size(work.select(real_type()) >= min_size_work(
                traits::matrix_size2(t) )));
#endif
        detail::trexc( compq, traits::matrix_size2(t),
                traits::matrix_storage(t), traits::leading_dimension(t),
                traits::matrix_storage(q), traits::leading_dimension(q), ifst,
                ilst, traits::vector_storage(work.select(real_type())), info );
    }
};

// complex specialization
template< typename ValueType >
struct trexc_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixT, typename MatrixQ, $WORKSPACE_TYPENAMES >
    static void compute( char const compq, MatrixT& t, MatrixQ& q,
            integer_t const ifst, integer_t const ilst, integer_t& info,
            detail::workspace$WORKSPACE_SIZE< $WORKSPACE_TYPES > work ) {
#ifndef NDEBUG
        assert( compq == 'V' || compq == 'N' );
        assert( traits::matrix_size2(t) >= 0 );
        assert( traits::leading_dimension(t) >= std::max(1,
                traits::matrix_size2(t)) );
        assert( traits::leading_dimension(q) >= std::max(1,
                traits::matrix_size2(t)) );
#endif
        detail::trexc( compq, traits::matrix_size2(t),
                traits::matrix_storage(t), traits::leading_dimension(t),
                traits::matrix_storage(q), traits::leading_dimension(q), ifst,
                ilst, info );
    }

    // minimal workspace specialization
    template< typename MatrixT, typename MatrixQ >
    static void compute( char const compq, MatrixT& t, MatrixQ& q,
            integer_t const ifst, integer_t const ilst, integer_t& info,
            minimal_workspace work ) {
$SETUP_MIN_WORKARRAYS_POST
        compute( compq, t, q, ifst, ilst, info, workspace( $TMP_WORKARRAYS ) );
    }

    // optimal workspace specialization
    template< typename MatrixT, typename MatrixQ >
    static void compute( char const compq, MatrixT& t, MatrixQ& q,
            integer_t const ifst, integer_t const ilst, integer_t& info,
            optimal_workspace work ) {
$OPT_WORKSPACE_FUNC
    }

$MIN_SIZE_FUNCS
};


// template function to call trexc
template< typename MatrixT, typename MatrixQ >
inline integer_t trexc( char const compq, MatrixT& t, MatrixQ& q,
        integer_t& ifst, integer_t& ilst ) {
    typedef typename traits::matrix_traits< MatrixT >::value_type value_type;
    integer_t info(0);
    trexc_impl< value_type >::compute( compq, t, q, ifst, ilst, info );
    return info;
}

// template function to call trexc
template< typename MatrixT, typename MatrixQ, typename Workspace >
inline integer_t trexc( char const compq, MatrixT& t, MatrixQ& q,
        integer_t const ifst, integer_t const ilst,
        Workspace work = optimal_workspace() ) {
    typedef typename traits::matrix_traits< MatrixT >::value_type value_type;
    integer_t info(0);
    trexc_impl< value_type >::compute( compq, t, q, ifst, ilst, info,
            work );
    return info;
}


}}}} // namespace boost::numeric::bindings::lapack

#endif
