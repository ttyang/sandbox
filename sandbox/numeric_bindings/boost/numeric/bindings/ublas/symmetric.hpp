//
// Copyright (c) 2009 Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_NUMERIC_BINDINGS_UBLAS_SYMMETRIC_HPP
#define BOOST_NUMERIC_BINDINGS_UBLAS_SYMMETRIC_HPP

#include <boost/numeric/bindings/detail/adaptor.hpp>
#include <boost/numeric/bindings/ublas/detail/to_bindings_tag.hpp>
#include <boost/numeric/ublas/symmetric.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace detail {

template< typename T, typename F1, typename F2, typename A, typename Id, typename Enable >
struct adaptor< ublas::symmetric_matrix< T, F1, F2, A >, Id, Enable > {

    typedef typename copy_const< Id, T >::type value_type;
    typedef mpl::map<
        mpl::pair< tag::value_type, value_type >,
        mpl::pair< tag::entity, tag::matrix >,
        mpl::pair< tag::matrix_type, tag::symmetric >,
        mpl::pair< tag::data_structure, tag::triangular_array >,
        mpl::pair< tag::data_side, typename to_bindings_tag<F1>::type >,
        mpl::pair< tag::data_order, typename to_bindings_tag<F2>::type >
    > property_map;

    static std::ptrdiff_t size1( Id const& t ) {
        return t.size1();
    }

    static std::ptrdiff_t size2( Id const& t ) {
        return t.size2();
    }

};

} // namespace detail
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
