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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GEBRD_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GEBRD_HPP

#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/detail/utils.hpp>
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
    inline void gebrd( integer_t const m, integer_t const n, float* a,
            integer_t const lda, float* d, float* e, float* tauq, float* taup,
            float* work, integer_t const lwork, integer_t& info ) {
        LAPACK_SGEBRD( &m, &n, a, &lda, d, e, tauq, taup, work, &lwork,
                &info );
    }
    inline void gebrd( integer_t const m, integer_t const n, double* a,
            integer_t const lda, double* d, double* e, double* tauq,
            double* taup, double* work, integer_t const lwork,
            integer_t& info ) {
        LAPACK_DGEBRD( &m, &n, a, &lda, d, e, tauq, taup, work, &lwork,
                &info );
    }
    inline void gebrd( integer_t const m, integer_t const n,
            traits::complex_f* a, integer_t const lda, float* d, float* e,
            traits::complex_f* tauq, traits::complex_f* taup,
            traits::complex_f* work, integer_t const lwork, integer_t& info ) {
        LAPACK_CGEBRD( &m, &n, traits::complex_ptr(a), &lda, d, e,
                traits::complex_ptr(tauq), traits::complex_ptr(taup),
                traits::complex_ptr(work), &lwork, &info );
    }
    inline void gebrd( integer_t const m, integer_t const n,
            traits::complex_d* a, integer_t const lda, double* d, double* e,
            traits::complex_d* tauq, traits::complex_d* taup,
            traits::complex_d* work, integer_t const lwork, integer_t& info ) {
        LAPACK_ZGEBRD( &m, &n, traits::complex_ptr(a), &lda, d, e,
                traits::complex_ptr(tauq), traits::complex_ptr(taup),
                traits::complex_ptr(work), &lwork, &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct gebrd_impl{};

// real specialization
template< typename ValueType >
struct gebrd_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename VectorD, typename VectorE,
            typename VectorTAUQ, typename VectorTAUP, typename WORK >
    static void invoke( MatrixA& a, VectorD& d, VectorE& e, VectorTAUQ& tauq,
            VectorTAUP& taup, integer_t& info, detail::workspace1<
            WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorD >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorE >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorTAUQ >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorTAUP >::value_type >::value) );
        BOOST_ASSERT( traits::matrix_num_rows(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_rows(a)) );
        BOOST_ASSERT( traits::vector_size(d) >=
                std::min(traits::matrix_num_rows(a),
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(tauq) >=
                std::min(traits::matrix_num_rows(a),
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(taup) >=
                std::min(traits::matrix_num_rows(a),
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a) ));
        detail::gebrd( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(d),
                traits::vector_storage(e), traits::vector_storage(tauq),
                traits::vector_storage(taup),
                traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename VectorD, typename VectorE,
            typename VectorTAUQ, typename VectorTAUP >
    static void invoke( MatrixA& a, VectorD& d, VectorE& e, VectorTAUQ& tauq,
            VectorTAUP& taup, integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work(
                traits::matrix_num_rows(a), traits::matrix_num_columns(a) ) );
        invoke( a, d, e, tauq, taup, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename VectorD, typename VectorE,
            typename VectorTAUQ, typename VectorTAUP >
    static void invoke( MatrixA& a, VectorD& d, VectorE& e, VectorTAUQ& tauq,
            VectorTAUP& taup, integer_t& info, optimal_workspace work ) {
        real_type opt_size_work;
        detail::gebrd( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(d),
                traits::vector_storage(e), traits::vector_storage(tauq),
                traits::vector_storage(taup), &opt_size_work, -1, info );
        traits::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        invoke( a, d, e, tauq, taup, info, workspace( tmp_work ) );
    }

    static integer_t min_size_work( integer_t const m, integer_t const n ) {
        return std::max( 1, std::max( m, n ) );
    }
};

// complex specialization
template< typename ValueType >
struct gebrd_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename VectorD, typename VectorE,
            typename VectorTAUQ, typename VectorTAUP, typename WORK >
    static void invoke( MatrixA& a, VectorD& d, VectorE& e, VectorTAUQ& tauq,
            VectorTAUP& taup, integer_t& info, detail::workspace1<
            WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::vector_traits<
                VectorE >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorTAUQ >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorTAUP >::value_type >::value) );
        BOOST_ASSERT( traits::matrix_num_rows(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_rows(a)) );
        BOOST_ASSERT( traits::vector_size(d) >=
                std::min(traits::matrix_num_rows(a),
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(tauq) >=
                std::min(traits::matrix_num_rows(a),
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(taup) >=
                std::min(traits::matrix_num_rows(a),
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a) ));
        detail::gebrd( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(d),
                traits::vector_storage(e), traits::vector_storage(tauq),
                traits::vector_storage(taup),
                traits::vector_storage(work.select(value_type())),
                traits::vector_size(work.select(value_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename VectorD, typename VectorE,
            typename VectorTAUQ, typename VectorTAUP >
    static void invoke( MatrixA& a, VectorD& d, VectorE& e, VectorTAUQ& tauq,
            VectorTAUP& taup, integer_t& info, minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work(
                traits::matrix_num_rows(a), traits::matrix_num_columns(a) ) );
        invoke( a, d, e, tauq, taup, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename VectorD, typename VectorE,
            typename VectorTAUQ, typename VectorTAUP >
    static void invoke( MatrixA& a, VectorD& d, VectorE& e, VectorTAUQ& tauq,
            VectorTAUP& taup, integer_t& info, optimal_workspace work ) {
        value_type opt_size_work;
        detail::gebrd( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(d),
                traits::vector_storage(e), traits::vector_storage(tauq),
                traits::vector_storage(taup), &opt_size_work, -1, info );
        traits::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        invoke( a, d, e, tauq, taup, info, workspace( tmp_work ) );
    }

    static integer_t min_size_work( integer_t const m, integer_t const n ) {
        return std::max( 1, std::max( m, n ) );
    }
};


// template function to call gebrd
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAUQ, typename VectorTAUP, typename Workspace >
inline integer_t gebrd( MatrixA& a, VectorD& d, VectorE& e,
        VectorTAUQ& tauq, VectorTAUP& taup, Workspace work ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    gebrd_impl< value_type >::invoke( a, d, e, tauq, taup, info, work );
    return info;
}

// template function to call gebrd, default workspace type
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAUQ, typename VectorTAUP >
inline integer_t gebrd( MatrixA& a, VectorD& d, VectorE& e,
        VectorTAUQ& tauq, VectorTAUP& taup ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    gebrd_impl< value_type >::invoke( a, d, e, tauq, taup, info,
            optimal_workspace() );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
