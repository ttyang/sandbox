
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_PP_ITERATION_PARAMS_HPP_
#define BOOST_CONTRACT_AUX_PP_ITERATION_PARAMS_HPP_

#include <boost/contract/config.hpp>

#define BOOST_CONTRACT_AUX_PP_ITERATION_PARAMS_ARITY(file) \
    (3, (0, BOOST_CONTRACT_CONFIG_FUNCTION_ARITY_MAX, file))

#define BOOST_CONTRACT_AUX_PP_ITERATION_PARAMS_CV_MEMBER(file) \
    (3, (0, 4, file))

#endif // #include guard

