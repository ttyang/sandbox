
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_OLDOF_TRAITS_ASSIGNMENT_HPP_
#define BOOST_CONTRACT_DETAIL_PP_OLDOF_TRAITS_ASSIGNMENT_HPP_

#include <boost/preprocessor/array/elem.hpp>

// PUBLIC //

// Expand to `variable =`.
#define BOOST_CONTRACT_DETAIL_PP_OLDOF_TRAITS_ASSIGNMENT(oldof_traits) \
    BOOST_PP_ARRAY_ELEM(1, oldof_traits)

#endif // #include guard

