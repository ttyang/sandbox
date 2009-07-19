/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_FUSION_CONTAINER_VECTOR_DETAIL_PP_VECTOR_FORWARD_CTOR_HPP
#define BOOST_FUSION_CONTAINER_VECTOR_DETAIL_PP_VECTOR_FORWARD_CTOR_HPP

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/container/vector/detail/pp/vector_forward_ctor.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_VECTOR_SIZE)
#include BOOST_PP_ITERATE()

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define N BOOST_PP_ITERATION()

#if N == 1
    explicit
#endif
    vector(BOOST_PP_ENUM_BINARY_PARAMS(N, const T,& _))
      : vec(BOOST_PP_ENUM_PARAMS(N, _)) {}

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)
