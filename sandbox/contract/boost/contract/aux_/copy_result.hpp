
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_COPY_RESULT_HPP_
#define BOOST_CONTRACT_AUX_COPY_RESULT_HPP_

#include <boost/contract/config.hpp>
#include <boost/contract/copy.hpp>
#include <boost/contract/aux_/result_const.hpp> // For void_result.
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/type_traits/add_reference.hpp>

#define BOOST_CONTRACT_comma_typename_Arg(z, n, unused) \
    , typename BOOST_PP_CAT(Arg, n)
#define BOOST_CONTRACT_comma_arg_param(z, n, unused) \
    /* NOTE: this param type must be a ref to avoid copying the arg (which */ \
    /* might not have a copy cons, ref is OK because caller always uses a */ \
    /* var to hold this param) plus add_reference can't be used otherwise */ \
    /* Arg type cannot be deduced (and cons cannot specify tparams) */ \
    , BOOST_PP_CAT(Arg, n) & \
    BOOST_PP_CAT(arg, n)
#define BOOST_CONTRACT_arg(z, n, unused) \
    BOOST_PP_CAT(arg, n)

#define BOOST_CONTRACT_call_func(z, n, is_member) \
    BOOST_PP_IIF(is_member, \
        (obj->*func) \
    , \
        (*func) \
    )( \
        BOOST_PP_ENUM_ ## z(n, BOOST_CONTRACT_arg, ~) \
    )

#define BOOST_CONTRACT_cons_decl(z, n, is_member) \
    template< typename Func \
        BOOST_PP_REPEAT_ ## z(n, BOOST_CONTRACT_comma_typename_Arg, ~) \
    > \
    explicit copy_result(Func const func \
        BOOST_PP_COMMA_IF(is_member) \
        BOOST_PP_EXPR_IIF(is_member, CVQualifiedObj const obj) \
        BOOST_PP_REPEAT_ ## z(n, BOOST_CONTRACT_comma_arg_param, ~) \
    )
#define BOOST_CONTRACT_cons(z, n, is_member) \
    BOOST_CONTRACT_cons_decl(z, n, is_member) \
        : result_(BOOST_CONTRACT_call_func(z, n, is_member)) {}
#define BOOST_CONTRACT_void_cons(z, n, is_member) \
    BOOST_CONTRACT_cons_decl(z, n, is_member) \
        { BOOST_CONTRACT_call_func(z, n, is_member) ; }

namespace boost { namespace contract { namespace aux {

// Copy result of non-void non-static mem func.
template< typename Result, class CVQualifiedObj = void >
struct copy_result {
    BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_CONTRACT_CONFIG_FUNCTION_ARITY_MAX),
            BOOST_CONTRACT_cons, 1 /* member */) // INC(ARITY) for no arg.

    typename copy<Result>::const_reference_type value() const
        { return result_.value(); }
    typename copy<Result>::const_reference_type param() const
        { return result_.value(); }
private:
    copy<Result> const result_; // Use copy<> so user can customize.
};

// Copy result of non-void free func and static member func.
template< typename Result >
struct copy_result< Result, void > {
    BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_CONTRACT_CONFIG_FUNCTION_ARITY_MAX),
            BOOST_CONTRACT_cons, 0 /* not member */) // INC(ARITY) for no arg.

    typename copy<Result>::const_reference_type value() const
        { return result_.value(); }
    typename copy<Result>::const_reference_type param() const
        { return result_.value(); }
private:
    copy<Result> const result_; // Use copy<> so user can customize.
};

// Handle Void Result //

// Copy result of void non-static member func.
template< class CVQualifiedObj >
struct copy_result< void, CVQualifiedObj > {
    BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_CONTRACT_CONFIG_FUNCTION_ARITY_MAX),
            BOOST_CONTRACT_void_cons, 1 /* member */) // INC(ARITY) for no arg.

    void value() const {} // There is no result to return (return void).
    void_result param() const { return void_result(); }
};

// Copy result of void non-static member func.
template< >
struct copy_result< void, void > {
    BOOST_PP_REPEAT( // INC(ARITY) for no arg.
          BOOST_PP_INC(BOOST_CONTRACT_CONFIG_FUNCTION_ARITY_MAX) 
        , BOOST_CONTRACT_void_cons
        , 0 /* not member */
    )

    void value() const {} // There is no result to return (return void).
    void_result param() const { return void_result(); }
};

} } } // namespace

#undef BOOST_CONTRACT_comma_typename_Arg
#undef BOOST_CONTRACT_comma_arg_param
#undef BOOST_CONTRACT_arg
#undef BOOST_CONTRACT_call_func
#undef BOOST_CONTRACT_cons_decl
#undef BOOST_CONTRACT_cons
#undef BOOST_CONTRACT_void_cons

#endif // #include guard

