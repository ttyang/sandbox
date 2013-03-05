
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_DEFAULT_HPP_
#define BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_DEFAULT_HPP_

#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

// Expand to `(comma_n, (default_value_token1, ...))` (array for unwrapped
// commas, 0-size array if no default value).
#define BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_DEFAULT(tparam) \
    BOOST_PP_TUPLE_ELEM(2, 1, tparam)

#endif // #include guard

