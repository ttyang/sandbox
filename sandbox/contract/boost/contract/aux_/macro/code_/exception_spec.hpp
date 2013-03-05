
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_CODE_EXCEPTION_SPEC_HPP_
#define BOOST_CONTRACT_AUX_CODE_EXCEPTION_SPEC_HPP_

// PRIVATE //

#define BOOST_CONTRACT_AUX_CODE_EXCEPTION_SPEC_COMMA_(r, unused, i, exception) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_PP_ARRAY_ENUM(exception)

#define BOOST_CONTRACT_AUX_CODE_EXCEPTION_SPEC_(id, tpl, k, f) \
    throw( \
        /* exception list will be empty for no-throw specification */ \
        BOOST_PP_LIST_FOR_EACH_I(BOOST_CONTRACT_AUX_CODE_EXCEPTION_SPEC_COMMA_,\
        ~, BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_EXCEPTIONS(f)) \
    )

// PUBLIC //

#define BOOST_CONTRACT_AUX_CODE_EXCEPTION_SPEC(id, tpl, k, f) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_HAS_EXCEPTION_SPEC(f), \
        BOOST_CONTRACT_AUX_CODE_EXCEPTION_SPEC_ \
    , \
        BOOST_PP_TUPLE_EAT(4) /* nothing if no specification */ \
    )(id, tpl, k, f)

#endif // #include guard

