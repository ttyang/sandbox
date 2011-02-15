
#ifndef BOOST_LOCAL_AUX_PP_SIGN_PARSED_APPEND_UNBIND_HPP_
#define BOOST_LOCAL_AUX_PP_SIGN_PARSED_APPEND_UNBIND_HPP_

#include "../../params/unbind.hpp"
#include "../../params/bind.hpp"
#include "../../params/const_bind.hpp"
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/pop_back.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/size.hpp>

// Private API.

#define BOOST_LOCAL_AUX_PP_SIGN_PARSED_PARAMS_APPEND_UNBIND_DEFAULT_( \
        unbind_nilseq, default_value) \
    BOOST_PP_SEQ_POP_BACK(unbind_nilseq) \
    (( /* seq of 2-tuple params */ \
        /* last appended classifier type and name */ \
        BOOST_LOCAL_AUX_PP_SIGN_PARAMS_UNBIND_PARAM(BOOST_PP_SEQ_ELEM( \
                /* nil-seq so can always safely decrement size */ \
                BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(unbind_nilseq)), \
                unbind_nilseq)) \
    , \
        /* trailing EMPTY because defaults are optional */ \
        default_value BOOST_PP_EMPTY \
    ))

// Public API.

// default_value: a valid parameter default value (`-1`, etc)
#define BOOST_LOCAL_AUX_PP_SIGN_PARSED_PARAMS_APPEND_UNBIND_DEFAULT( \
        params, default_value) \
    ( /* unbind params and defaults */ \
        BOOST_LOCAL_AUX_PP_SIGN_PARSED_PARAMS_APPEND_UNBIND_DEFAULT_( \
                BOOST_LOCAL_AUX_PP_SIGN_PARAMS_UNBIND(params), \
                default_value) /* append default to last added param */ \
    , /* const-bind names */ \
        BOOST_LOCAL_AUX_PP_PARAMS_CONST_BIND(params) \
    , /* const-bind `this` count */ \
        BOOST_LOCAL_AUX_PP_PARAMS_CONST_BIND_THIS_COUNT(params) \
    , /* bind names */ \
        BOOST_LOCAL_AUX_PP_PARAMS_BIND(params) \
    , /* bind `this` count */ \
        BOOST_LOCAL_AUX_PP_PARAMS_BIND_THIS_COUNT(params) \
    , /* error message (if any) */ \
        BOOST_LOCAL_AUX_PP_PARAMS_ERROR(params) \
    )

// unbind_classified_type_and_name: [auto | register] type name
#define BOOST_LOCAL_AUX_PP_SIGN_PARSED_PARAMS_APPEND_UNBIND( \
        params, unbind_classified_type_and_name) \
    ( /* unbind params and defaults */ \
        BOOST_LOCAL_AUX_PP_PARAMS_UNBIND(params) \
        /* append param (with no default -- EMPTY) */ \
        ((unbind_classified_type_and_name, BOOST_PP_EMPTY)) \
    , /* const-bind names */ \
        BOOST_LOCAL_AUX_PP_PARAMS_CONST_BIND(params) \
    , /* const-bind `this` count */ \
        BOOST_LOCAL_AUX_PP_PARAMS_CONST_BIND_THIS_COUNT(params) \
    , /* bind names */ \
        BOOST_LOCAL_AUX_PP_PARAMS_BIND(params) \
    , /* bind `this` count */ \
        BOOST_LOCAL_AUX_PP_PARAMS_BIND_THIS_COUNT(params) \
    , /* error message (if any) */ \
        BOOST_LOCAL_AUX_PP_PARAMS_ERROR(params) \
    )

#endif // #include guard

