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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TRSEN_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TRSEN_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/detail/utils.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void trsen( char const job, char const compq, logical_t* select,
            integer_t const n, traits::complex_f* t, integer_t const ldt,
            traits::complex_f* q, integer_t const ldq, traits::complex_f* w,
            integer_t& m, float& s, float& sep, traits::complex_f* work,
            integer_t const lwork, integer_t& info ) {
        LAPACK_CTRSEN( &job, &compq, select, &n, traits::complex_ptr(t), &ldt,
                traits::complex_ptr(q), &ldq, traits::complex_ptr(w), &m, &s,
                &sep, traits::complex_ptr(work), &lwork, &info );
    }
    inline void trsen( char const job, char const compq, logical_t* select,
            integer_t const n, traits::complex_d* t, integer_t const ldt,
            traits::complex_d* q, integer_t const ldq, traits::complex_d* w,
            integer_t& m, double& s, double& sep, traits::complex_d* work,
            integer_t const lwork, integer_t& info ) {
        LAPACK_ZTRSEN( &job, &compq, select, &n, traits::complex_ptr(t), &ldt,
                traits::complex_ptr(q), &ldq, traits::complex_ptr(w), &m, &s,
                &sep, traits::complex_ptr(work), &lwork, &info );
    }
}

// value-type based template
template< typename ValueType >
struct trsen_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
            typename VectorW, typename WORK >
    static void invoke( char const job, char const compq,
            VectorSELECT& select, MatrixT& t, MatrixQ& q, VectorW& w,
            integer_t& m, real_type& s, real_type& sep, integer_t& info,
            detail::workspace1< WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixT >::value_type, typename traits::matrix_traits<
                MatrixQ >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixT >::value_type, typename traits::vector_traits<
                VectorW >::value_type >::value) );
        BOOST_ASSERT( job == 'N' || job == 'E' || job == 'V' || job == 'B' );
        BOOST_ASSERT( compq == 'V' || compq == 'N' );
        BOOST_ASSERT( traits::vector_size(select) >=
                traits::matrix_num_columns(t) );
        BOOST_ASSERT( traits::matrix_num_columns(t) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(t) >= std::max(1,
                traits::matrix_num_columns(t)) );
        BOOST_ASSERT( traits::vector_size(w) >=
                traits::matrix_num_columns(t) );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( $CALL_MIN_SIZE ));
        detail::trsen( job, compq, traits::vector_storage(select),
                traits::matrix_num_columns(t), traits::matrix_storage(t),
                traits::leading_dimension(t), traits::matrix_storage(q),
                traits::leading_dimension(q), traits::vector_storage(w), m, s,
                sep, traits::vector_storage(work.select(value_type())),
                traits::vector_size(work.select(value_type())), info );
    }

    // minimal workspace specialization
    template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
            typename VectorW >
    static void invoke( char const job, char const compq,
            VectorSELECT& select, MatrixT& t, MatrixQ& q, VectorW& w,
            integer_t& m, real_type& s, real_type& sep, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        invoke( job, compq, select, t, q, w, m, s, sep, info,
                workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
            typename VectorW >
    static void invoke( char const job, char const compq,
            VectorSELECT& select, MatrixT& t, MatrixQ& q, VectorW& w,
            integer_t& m, real_type& s, real_type& sep, integer_t& info,
            optimal_workspace work ) {
        value_type opt_size_work;
        detail::trsen( job, compq, traits::vector_storage(select),
                traits::matrix_num_columns(t), traits::matrix_storage(t),
                traits::leading_dimension(t), traits::matrix_storage(q),
                traits::leading_dimension(q), traits::vector_storage(w), m, s,
                sep, &opt_size_work, -1, info );
        traits::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        invoke( job, compq, select, t, q, w, m, s, sep, info,
                workspace( tmp_work ) );
    }

    static integer_t min_size_work( $ARGUMENTS ) {
        $MIN_SIZE
    }
};


// template function to call trsen
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW, typename Workspace >
inline integer_t trsen( char const job, char const compq,
        VectorSELECT& select, MatrixT& t, MatrixQ& q, VectorW& w,
        integer_t& m, typename traits::vector_traits<
        VectorSELECT >::value_type& s, typename traits::vector_traits<
        VectorSELECT >::value_type& sep, Workspace work ) {
    typedef typename traits::vector_traits<
            VectorSELECT >::value_type value_type;
    integer_t info(0);
    trsen_impl< value_type >::invoke( job, compq, select, t, q, w, m, s,
            sep, info, work );
    return info;
}

// template function to call trsen, default workspace type
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW >
inline integer_t trsen( char const job, char const compq,
        VectorSELECT& select, MatrixT& t, MatrixQ& q, VectorW& w,
        integer_t& m, typename traits::vector_traits<
        VectorSELECT >::value_type& s, typename traits::vector_traits<
        VectorSELECT >::value_type& sep ) {
    typedef typename traits::vector_traits<
            VectorSELECT >::value_type value_type;
    integer_t info(0);
    trsen_impl< value_type >::invoke( job, compq, select, t, q, w, m, s,
            sep, info, optimal_workspace() );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
