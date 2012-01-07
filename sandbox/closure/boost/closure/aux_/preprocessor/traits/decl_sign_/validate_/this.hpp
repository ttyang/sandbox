
#ifndef BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_HPP_
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_HPP_

#include <boost/closure/detail/preprocessor/keyword/this.hpp>
#include <boost/closure/detail/preprocessor/keyword/const.hpp>
#include <boost/closure/detail/preprocessor/keyword/bind.hpp>
#include <boost/closure/detail/preprocessor/keyword/const_bind.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>

// PRIVATE //

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_VAR_( \
        s, error, elem) \
    BOOST_PP_IIF(BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_THIS_BACK( \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_BIND_REMOVE_FRONT( \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_CONST_REMOVE_FRONT(elem))), \
        ERROR_use_this_underscore_instead_of_this BOOST_PP_EMPTY \
    , \
        error \
    )

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_(s, error, elem) \
    BOOST_PP_IIF(BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_BIND_FRONT(elem), \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_VAR_ \
    , BOOST_PP_IIF(BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_CONST_BIND_FRONT(elem), \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_VAR_ \
    , \
        error BOOST_PP_TUPLE_EAT(3) \
    ))(s, error, elem)

// PUBLIC //

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS(sign) \
    BOOST_PP_SEQ_FOLD_LEFT( \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_, \
            BOOST_PP_EMPTY, sign)

#endif // #include guard

