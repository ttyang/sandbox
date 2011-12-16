
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_AUX_PP_DECL_TRAITS_HPP_
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_HPP_

#include <boost/closure/aux_/preprocessor/traits/decl_sign_/is_void.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_sign_/seq.hpp>
#include <boost/closure/aux_/preprocessor/triats/decl_/nil.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// PUBLIC //

// declaration_seq can be empty ``, or `void`, or `(void)` for no params.
// Or, `{([auto | register] param_type param_name)[(default default_value)] 
// | ([const] bind [&] bind_name)}+ [(return result_type)]` where `bind_name`
// can be `this_` (but not `&this_` as usual in C++).
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS(declaration_seq) \
    BOOST_PP_IIF(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_IS_VOID( \
            declaration_seq), \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_NIL \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_SEQ \
    )(declaration_seq)

#endif // #include guard

