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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GGRQF_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GGRQF_HPP

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

inline void ggrqf( const integer_t m, const integer_t p, const integer_t n,
        float* a, const integer_t lda, float* taua, float* b,
        const integer_t ldb, float* taub, float* work, const integer_t lwork,
        integer_t& info ) {
    LAPACK_SGGRQF( &m, &p, &n, a, &lda, taua, b, &ldb, taub, work, &lwork,
            &info );
}

inline void ggrqf( const integer_t m, const integer_t p, const integer_t n,
        double* a, const integer_t lda, double* taua, double* b,
        const integer_t ldb, double* taub, double* work,
        const integer_t lwork, integer_t& info ) {
    LAPACK_DGGRQF( &m, &p, &n, a, &lda, taua, b, &ldb, taub, work, &lwork,
            &info );
}

inline void ggrqf( const integer_t m, const integer_t p, const integer_t n,
        traits::complex_f* a, const integer_t lda, traits::complex_f* taua,
        traits::complex_f* b, const integer_t ldb, traits::complex_f* taub,
        traits::complex_f* work, const integer_t lwork, integer_t& info ) {
    LAPACK_CGGRQF( &m, &p, &n, traits::complex_ptr(a), &lda,
            traits::complex_ptr(taua), traits::complex_ptr(b), &ldb,
            traits::complex_ptr(taub), traits::complex_ptr(work), &lwork,
            &info );
}

inline void ggrqf( const integer_t m, const integer_t p, const integer_t n,
        traits::complex_d* a, const integer_t lda, traits::complex_d* taua,
        traits::complex_d* b, const integer_t ldb, traits::complex_d* taub,
        traits::complex_d* work, const integer_t lwork, integer_t& info ) {
    LAPACK_ZGGRQF( &m, &p, &n, traits::complex_ptr(a), &lda,
            traits::complex_ptr(taua), traits::complex_ptr(b), &ldb,
            traits::complex_ptr(taub), traits::complex_ptr(work), &lwork,
            &info );
}

} // namespace detail

// value-type based template
template< typename ValueType, typename Enable = void >
struct ggrqf_impl{};

// real specialization
template< typename ValueType >
struct ggrqf_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename VectorTAUA, typename MatrixB,
            typename VectorTAUB, typename WORK >
    static void invoke( MatrixA& a, VectorTAUA& taua, MatrixB& b,
            VectorTAUB& taub, integer_t& info, detail::workspace1<
            WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorTAUA >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorTAUB >::value_type >::value) );
        BOOST_ASSERT( traits::matrix_num_rows(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_rows(b) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(b) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_rows(a)) );
        BOOST_ASSERT( traits::vector_size(taua) >=
                std::min(traits::matrix_num_rows(a),
                traits::matrix_num_columns(b)) );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,
                traits::matrix_num_rows(b)) );
        BOOST_ASSERT( traits::vector_size(taub) >=
                std::min(traits::matrix_num_rows(b),
                traits::matrix_num_columns(b)) );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( $CALL_MIN_SIZE ));
        detail::ggrqf( traits::matrix_num_rows(a), traits::matrix_num_rows(b),
                traits::matrix_num_columns(b), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(taua),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::vector_storage(taub),
                traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename VectorTAUA, typename MatrixB,
            typename VectorTAUB >
    static void invoke( MatrixA& a, VectorTAUA& taua, MatrixB& b,
            VectorTAUB& taub, integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        invoke( a, taua, b, taub, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename VectorTAUA, typename MatrixB,
            typename VectorTAUB >
    static void invoke( MatrixA& a, VectorTAUA& taua, MatrixB& b,
            VectorTAUB& taub, integer_t& info, optimal_workspace work ) {
        real_type opt_size_work;
        detail::ggrqf( traits::matrix_num_rows(a),
                traits::matrix_num_rows(b), traits::matrix_num_columns(b),
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::vector_storage(taua), traits::matrix_storage(b),
                traits::leading_dimension(b), traits::vector_storage(taub),
                &opt_size_work, -1, info );
        traits::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        invoke( a, taua, b, taub, info, workspace( tmp_work ) );
    }

    static integer_t min_size_work( $ARGUMENTS ) {
        $MIN_SIZE
    }
};

// complex specialization
template< typename ValueType >
struct ggrqf_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename VectorTAUA, typename MatrixB,
            typename VectorTAUB, typename WORK >
    static void invoke( MatrixA& a, VectorTAUA& taua, MatrixB& b,
            VectorTAUB& taub, integer_t& info, detail::workspace1<
            WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorTAUA >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorTAUB >::value_type >::value) );
        BOOST_ASSERT( traits::matrix_num_rows(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_rows(b) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(b) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_rows(a)) );
        BOOST_ASSERT( traits::vector_size(taua) >=
                std::min(traits::matrix_num_rows(a),
                traits::matrix_num_columns(b)) );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,
                traits::matrix_num_rows(b)) );
        BOOST_ASSERT( traits::vector_size(taub) >=
                std::min(traits::matrix_num_rows(b),
                traits::matrix_num_columns(b)) );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( $CALL_MIN_SIZE ));
        detail::ggrqf( traits::matrix_num_rows(a), traits::matrix_num_rows(b),
                traits::matrix_num_columns(b), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(taua),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::vector_storage(taub),
                traits::vector_storage(work.select(value_type())),
                traits::vector_size(work.select(value_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename VectorTAUA, typename MatrixB,
            typename VectorTAUB >
    static void invoke( MatrixA& a, VectorTAUA& taua, MatrixB& b,
            VectorTAUB& taub, integer_t& info, minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        invoke( a, taua, b, taub, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename VectorTAUA, typename MatrixB,
            typename VectorTAUB >
    static void invoke( MatrixA& a, VectorTAUA& taua, MatrixB& b,
            VectorTAUB& taub, integer_t& info, optimal_workspace work ) {
        value_type opt_size_work;
        detail::ggrqf( traits::matrix_num_rows(a),
                traits::matrix_num_rows(b), traits::matrix_num_columns(b),
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::vector_storage(taua), traits::matrix_storage(b),
                traits::leading_dimension(b), traits::vector_storage(taub),
                &opt_size_work, -1, info );
        traits::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        invoke( a, taua, b, taub, info, workspace( tmp_work ) );
    }

    static integer_t min_size_work( $ARGUMENTS ) {
        $MIN_SIZE
    }
};


// template function to call ggrqf
template< typename MatrixA, typename VectorTAUA, typename MatrixB,
        typename VectorTAUB, typename Workspace >
inline integer_t ggrqf( MatrixA& a, VectorTAUA& taua, MatrixB& b,
        VectorTAUB& taub, Workspace work ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    ggrqf_impl< value_type >::invoke( a, taua, b, taub, info, work );
    return info;
}

// template function to call ggrqf, default workspace type
template< typename MatrixA, typename VectorTAUA, typename MatrixB,
        typename VectorTAUB >
inline integer_t ggrqf( MatrixA& a, VectorTAUA& taua, MatrixB& b,
        VectorTAUB& taub ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    ggrqf_impl< value_type >::invoke( a, taua, b, taub, info,
            optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
