// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_ELEMENT_TYPE_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_ELEMENT_TYPE_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace detail {

    template <typename T>
    struct element_type
    {
        typedef typename T::element_type type;

        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,element_type,(T))
    };
}}  // namespace boost::detail

#endif  // BOOST_DETAIL_METAFUNCTION_ELEMENT_TYPE_HPP_INCLUDED

