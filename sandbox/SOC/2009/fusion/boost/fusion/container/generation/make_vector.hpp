/*==============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_GENERATION_MAKE_VECTOR_HPP
#define BOOST_FUSION_CONTAINER_GENERATION_MAKE_VECTOR_HPP

#include <boost/fusion/support/internal/base.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#ifdef BOOST_NO_VARIADIC_TEMPLATES
#   include <boost/preprocessor/cat.hpp>

#   define BOOST_FUSION_SEQ_NAME(N) BOOST_PP_CAT(vector,N)
#else
#   define BOOST_FUSION_SEQ_NAME vector
#endif
#define BOOST_FUSION_FUNCTION_NAME make_vector
#define BOOST_FUSION_MAX_SEQ_SIZE FUSION_MAX_VECTOR_SIZE
#include <boost/fusion/container/generation/detail/make_seq.hpp>
#undef BOOST_FUSION_MAX_SEQ_SIZE
#undef BOOST_FUSION_FUNCTION_NAME
#undef BOOST_FUSION_SEQ_NAME

#endif