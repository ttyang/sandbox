
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_BODY_HPP_
#define BOOST_CONTRACT_BODY_HPP_

/** @file
@brief Macros used to program body definitions separately from the contract
declarations (this header is automatically include by <c>contract.hpp</c>).
*/

#include <boost/contract/aux_/config.hpp>
#include <boost/contract/aux_/symbol.hpp>
#include <boost/contract/aux_/macro/body.hpp>

// PRIVATE //

#ifndef DOXYGEN

#define BOOST_CONTRACT_BODY_CTOR_DTOR_( \
        contracted_body_macro, class_type, constructor_name, contracted01) \
    BOOST_PP_EXPR_IF(contracted01, void) \
    BOOST_CONTRACT_AUX_BODY_CLASS_TYPE(class_type) :: \
    BOOST_PP_IIF(contracted01, \
        contracted_body_macro \
    , \
        BOOST_PP_TUPLE_REM(1) \
    )(constructor_name)

#endif // DOXYGEN

// PUBLIC //

/**
@brief Macro used to name the body of free functions and free function
operators.

This macro is used to name the body of free functions and free function
operators when the body is defined separately from the contract declaration.
Free functions and free function operators with contracts are declared
using the @RefMacro{BOOST_CONTRACT_FUNCTION} macro.

@Params
@Param{function_name,
The syntax for free function and free function operator names is explained in
the @RefSect{grammar\, Grammar} section.
}
@EndParams

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
#define BOOST_CONTRACT_FREE_BODY(function_name) \
    BOOST_PP_IIF( \
            BOOST_PP_BITOR( \
                  BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01 \
                , BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 \
            ), \
        BOOST_CONTRACT_AUX_BODY_FUNCTION_BOOST_CONTRACTED \
    , \
        BOOST_CONTRACT_AUX_BODY_FUNCTION \
    )(function_name)

/**
@brief Macro used to name the body of member functions and member function
operators.

This macro is used to name the body of member functions and member function
operators when the body is defined separately from the contract declaration.
Member functions and member function operators with contracts are declared
using the @RefMacro{BOOST_CONTRACT_FUNCTION} macro.

@Params
@Param{function_name,
The syntax for function and operator names is explained in the
@RefSect{grammar\, Grammar} section.
}
@EndParams

@Warning This macro must also be used when a virtual function invokes the
overridden function from one of its base classes (see the
@RefSect{tutorial, Tutorial} section).

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
#define BOOST_CONTRACT_MEMBER_BODY(function_name) \
    /* NOTE: this must be a different macro from FREE_BODY because it */ \
    /* expands also if invariants (not just pre and post) */ \
    /* class type is specified so this macro API is same as ctor and dtor */ \
    BOOST_PP_IIF( \
            BOOST_PP_BITOR( \
                  BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01 \
                , BOOST_PP_BITOR( \
                      BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 \
                    , BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 \
                  ) \
            ), \
        BOOST_CONTRACT_AUX_BODY_FUNCTION_BOOST_CONTRACTED \
    , \
        BOOST_CONTRACT_AUX_BODY_FUNCTION \
    )(function_name)

/**
@brief Macro used to name the body of constructors.

This macro is used to name the body of constructors when the body is defined
separately from the contract declaration.
Constructors with contracts are declared using the
@RefMacro{BOOST_CONTRACT_CONSTRUCTOR} macro.

@Params
@Param{class_type,
The syntax for the class type is explained in the @RefSect{grammar\, Grammar}
section (for class templates\, this type is qualified with the template
parameters).
}
@Param{constructor_name,
This is the class name and its syntax is explained in the
@RefSect{grammar\, Grammar} section (for class templates\, this name is
<em>not</em> qualified with the template parameters).
}
@EndParams

@Warning The body of constructors with member initializers should always be
defined together with the constructor declaration and its contract.

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
// class_type: `vect<T>`, `(vect<T, A>)`, or `comma(1)(vect<T, A>)`.
#define BOOST_CONTRACT_CONSTRUCTOR_BODY(class_type, constructor_name) \
    BOOST_CONTRACT_BODY_CTOR_DTOR_( \
          BOOST_CONTRACT_AUX_BODY_CONSTRUCTOR_BOOST_CONTRACTED \
        , class_type, constructor_name \
        , BOOST_PP_BITOR( \
              BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01 \
            , BOOST_PP_BITOR( \
                  BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 \
                , BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 \
              ) \
          ) \
    )

/**
@brief Macro used to name the body of destructors.

This macro is used to name the body of destructors when the body is defined
separately from the contract declaration.
Destructors with contracts are declared using the
@RefMacro{BOOST_CONTRACT_DESTRUCTOR} macro.

@Params
@Param{class_type,
The syntax for the class type is explained in the @RefSect{grammar\, Grammar}
section (for class templates\, this type is qualified with the template
parameters).
}
@Param{destructor_name,
This is the class name prefixed by the tilde symbol <c>~</c> and its syntax is
explained in the @RefSect{grammar\, Grammar} section (for class templates\,
this name is <em>not</em> qualified with the template parameters).
}
@EndParams

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
// class_type: `vect<T>`, `(vect<T, A>)`, or `comma(1)(vect<T, A>)`.
#define BOOST_CONTRACT_DESTRUCTOR_BODY(class_type, destructor_name) \
    BOOST_CONTRACT_BODY_CTOR_DTOR_( \
          BOOST_CONTRACT_AUX_BODY_DESTRUCTOR_BOOST_CONTRACTED \
        , class_type, destructor_name \
        , BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 \
    )

#endif // #include guard

