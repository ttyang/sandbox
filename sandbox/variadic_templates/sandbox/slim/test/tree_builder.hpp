#ifndef TREE_BUILDER_HPP_INCLUDED
#define TREE_BUILDER_HPP_INCLUDED
//OriginalSource:
//  2012-10-25.1521 CST
//    Copied code from unrolled_tuple.cpp from:
//      https://github.com/ericniebler/home/tree/master/src/tuple
//
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2012 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "./make_tuple.hpp"
#include <boost/preprocessor/repetition/enum.hpp>

#ifndef TUPLE_SIZE
#define TUPLE_SIZE 2
#endif

#ifndef TREE_DEPTH
#define TREE_DEPTH 5
#endif

template<int I>
struct tree_builder
{
    #define M0(Z, N, D) ::make_tuple( static_cast<T &&>(t), std::integral_constant<int, N>())
    #define M1(Z, N, D) auto BOOST_PP_CAT(tmp, N) = ::get<N>(res);

    template<typename T>
    static auto make_tree(T &&t)
      -> decltype(tree_builder<I+1>::make_tree(::make_tuple(BOOST_PP_ENUM(TUPLE_SIZE, M0, ~))))
    {
        auto res = tree_builder<I+1>::make_tree(::make_tuple(BOOST_PP_ENUM(TUPLE_SIZE, M0, ~)));
        // Get each element of the tuple.
        BOOST_PP_REPEAT(TUPLE_SIZE, M1, ~)
        return res;
    }

    #undef M1
    #undef M0
};

template<>
struct tree_builder<TREE_DEPTH+1>
{
    template<typename T>
    static T make_tree(T &&t)
    {
        return static_cast<T &&>(t);
    }
};

#endif
