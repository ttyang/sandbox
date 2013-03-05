
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_BODY_TRAITS_HPP_
#define BOOST_CONTRACT_DETAIL_PP_BODY_TRAITS_HPP_

// PRIVATE //
        
// Precondition: name_sign starts with alphanumeric token (i.e., not `~dtor`).
#define BOOST_CONTRACT_DETAIL_PP_BODY_TRAITS_MAYBE_OPERATOR_(body_name_sign) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_OPERATOR_FRONT( \
            body_name_sign), \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_WITH_OPERATOR \
    , \
        ( (0, ()) , body_name_sign ) BOOST_PP_TUPLE_EAT(1) \
    )( \
        body_name_sign \
        /* NIL padding for func params and expected last NIL */ \
        (BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL) \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL \
    )

// PUBLIC //

// body_name_sign: ctor | ~dtor | f | operator ... (usual operator sign).
#define BOOST_CONTRACT_DETAIL_PP_BODY_TRAITS( \
        is_constructor01, is_destructor01, body_name_sign) \
    BOOST_PP_IIF(BOOST_PP_BITOR(is_constructor01, is_destructor01), \
        ( (0, ()) , body_name_sign ) BOOST_PP_TUPLE_EAT(1) \
    , \
        BOOST_CONTRACT_DETAIL_PP_BODY_TRAITS_MAYBE_OPERATOR_ \
    )(body_name_sign)

// Expand to `(n, (token1, ...))` (array to handle commas within operator
// symbol token, 0-size if not an operator).
#define BOOST_CONTRACT_DETAIL_PP_BODY_TRAITS_OPERATOR(body_name_traits) \
    BOOST_PP_TUPLE_ELEM(2, 0, body_name_traits)

// Expand to alphanumeric function, constructor, operator name or to
// (non-alphanumeric) `~name` for destructor.
#define BOOST_CONTRACT_DETAIL_PP_BODY_TRAITS_NAME(body_name_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, body_name_traits)

// Input is not a trait but the class_type signature (possibly with extra
// parenthesis to wrap commas). Expand to `(n, (token1, ...))` (array to handle
// commas within class type for class templates, etc).
#define BOOST_CONTRACT_DETAIL_PP_BODY_TRAITS_CLASS_TYPE(class_type_sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA(BOOST_PP_TUPLE_REM(1), \
            class_type_sign)

#endif // #include guard

