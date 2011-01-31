/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef PHOENIX_DEFINE_OPERATOR_HPP
#define PHOENIX_DEFINE_OPERATOR_HPP

#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

#define PHOENIX_UNARY_RULE(__, ___, name)                                       \
    struct name                                                                 \
        : proto::unary_expr<proto::tag::name, proto::_>                         \
    {};                                                                         \
/**/

#define PHOENIX_BINARY_RULE(__, ___, name)                                      \
    struct name                                                                 \
        : proto::binary_expr<proto::tag::name, proto::_, proto::_>              \
    {};                                                                         \
/**/

#define PHOENIX_GRAMMAR(_, __, name)                                            \
    template <typename Dummy>                                                   \
    struct meta_grammar::case_<proto::tag::name, Dummy>                         \
        : proto::when<rule::name, proto::external_transform>                    \
    {};                                                                         \
/**/

#define PHOENIX_UNARY_OPERATORS(ops)                                            \
    namespace rule {                                                            \
        BOOST_PP_SEQ_FOR_EACH(PHOENIX_UNARY_RULE, _, ops)                       \
    }                                                                           \
    BOOST_PP_SEQ_FOR_EACH(PHOENIX_GRAMMAR, _, ops)                              \
/**/

#define PHOENIX_BINARY_OPERATORS(ops)                                           \
    namespace rule {                                                            \
        BOOST_PP_SEQ_FOR_EACH(PHOENIX_BINARY_RULE, _, ops)                      \
    }                                                                           \
    BOOST_PP_SEQ_FOR_EACH(PHOENIX_GRAMMAR, _, ops)                              \
/**/

#endif
