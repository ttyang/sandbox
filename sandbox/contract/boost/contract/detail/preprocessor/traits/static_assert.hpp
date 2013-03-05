
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_STATIC_ASSERT_TRAITS_HPP_
#define BOOST_CONTRACT_DETAIL_PP_STATIC_ASSERT_TRAITS_HPP_

#include <boost/contract/detail/preprocessor/keyword/cxx11/static_assert.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

// Where static_assert_instruction is `static_assert(condition, error)`.
#define BOOST_CONTRACT_DETAIL_PP_STATIC_ASSERT_TRAITS( \
        static_assert_instruction) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_STATIC_ASSERT_REMOVE_FRONT( \
            static_assert_instruction)

#define BOOST_CONTRACT_DETAIL_PP_STATIC_ASSERT_TRAITS_CONDITION( \
        static_assert_traits) \
    BOOST_PP_TUPLE_ELEM(2, 0, static_assert_traits)
    
#define BOOST_CONTRACT_DETAIL_PP_STATIC_ASSERT_TRAITS_ERROR( \
        static_assert_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, static_assert_traits)

#endif // #include guard

