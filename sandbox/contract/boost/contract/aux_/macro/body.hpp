
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_BODY_HPP_
#define BOOST_CONTRACT_AUX_BODY_HPP_

#include <boost/contract/detail/preprocessor/traits/body.hpp>

// PRIVATE //

#define BOOST_CONTRACT_AUX_BODY_FUNCTION_(body_traits) \
    BOOST_CONTRACT_AUX_CODE_NAME( \
            BOOST_CONTRACT_DETAIL_PP_BODY_TRAITS_OPERATOR(body_traits), \
            BOOST_CONTRACT_DETAIL_PP_BODY_TRAITS_NAME(body_traits))

#define BOOST_CONTRACT_AUX_BODY_FUNCTION_BOOST_CONTRACTED_(body_traits) \
    BOOST_CONTRACT_AUX_CODE_NAME_POSTFIXED( \
            0, /* not constructor */ \
            0, /* not destructor */ \
            BOOST_CONTRACT_DETAIL_PP_BODY_TRAITS_OPERATOR(body_traits), \
            BOOST_CONTRACT_DETAIL_PP_BODY_TRAITS_NAME(body_traits), \
            (body))

// PUBLIC //

#define BOOST_CONTRACT_AUX_BODY_CLASS_TYPE(class_type) \
    /* handle possible extra parenthesis to wrap commas within class_type */ \
    BOOST_PP_ARRAY_ENUM(BOOST_CONTRACT_DETAIL_PP_BODY_TRAITS_CLASS_TYPE( \
            class_type))

#define BOOST_CONTRACT_AUX_BODY_FUNCTION(name) \
    BOOST_CONTRACT_AUX_BODY_FUNCTION_(BOOST_CONTRACT_DETAIL_PP_BODY_TRAITS( \
            0 /* not constructor */, 0 /* not destructor */, name))

#define BOOST_CONTRACT_AUX_BODY_FUNCTION_BOOST_CONTRACTED(name) \
    BOOST_CONTRACT_AUX_BODY_FUNCTION_BOOST_CONTRACTED_( \
            BOOST_CONTRACT_DETAIL_PP_BODY_TRAITS(0 /* not constructor */, \
                    0 /* not destructor */, name))

#define BOOST_CONTRACT_AUX_BODY_CONSTRUCTOR_BOOST_CONTRACTED(body_traits) \
    BOOST_CONTRACT_AUX_CODE_NAME_POSTFIXED( \
            1, /* constructor */ \
            0, /* not destructor */ \
            (0, ()), /* no operator traits */ \
            BOOST_PP_EMPTY, /* no name traits */ \
            (body))

#define BOOST_CONTRACT_AUX_BODY_DESTRUCTOR_BOOST_CONTRACTED(body_traits) \
    BOOST_CONTRACT_AUX_CODE_NAME_POSTFIXED( \
            0, /* constructor */ \
            1, /* not destructor */ \
            (0, ()), /* no operator traits */ \
            BOOST_PP_EMPTY, /* no name traits */ \
            (body))

// Only body of functions with named parameters can be deferred (because
// constructor body cannot be deferred without delegating constructors, and
// destructors have no parameter so no named parameter). The class type is
// pulled out so the same macro can be used for both free and member functions.
#define BOOST_CONTRACT_AUX_BODY_PARAMETER_FUNCTION_BOOST_CONTRACTED(func_name) \
    BOOST_CONTRACT_AUX_CODE_NAME_POSTFIXED( \
            0, /* not constructor */ \
            0, /* not destructor */ \
            (0, ()), /* not operator (named params n/a for operators now) */ \
            func_name, \
            (body))

#endif // #include guard

