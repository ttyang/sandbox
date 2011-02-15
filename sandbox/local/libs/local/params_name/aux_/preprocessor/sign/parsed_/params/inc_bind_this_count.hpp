
#ifndef BOOST_LOCAL_AUX_PP_SIGN_PARSED_PARAMS_INC_BIND_THIS_COUNT_HPP_
#define BOOST_LOCAL_AUX_PP_SIGN_PARSED_PARAMS_INC_BIND_THIS_COUNT_HPP_

#include "../../params/unbind.hpp"
#include "../../params/bind.hpp"
#include "../../params/const_bind.hpp"
#include <boost/preprocessor/arithmentic/inc.hpp>

#define BOOST_LOCAL_AUX_PP_SIGN_PARSED_PARAMS_INC_BIND_THIS_COUNT(params) \
    ( /* unbind params and defaults */ \
        BOOST_LOCAL_AUX_PP_SIGN_PARAMS_UNBIND(params) \
    , /* const-bind names */ \
        BOOST_LOCAL_AUX_PP_SIGN_PARAMS_CONST_BIND(params) \
    , /* const-bind `this` count */ \
        BOOST_LOCAL_AUX_PP_SIGN_PARAMS_CONST_BIND_THIS_COUNT(params) \
    , /* bind names */ \
        BOOST_LOCAL_AUX_PP_SIGN_PARAMS_BIND(params) \
    , /* bind `this` count */ \
        BOOST_PP_INC(BOOST_LOCAL_AUX_PP_SIGN_PARAMS_BIND_THIS_COUNT( \
                params)) /* increment */ \
    , /* error message (if any) */ \
        BOOST_LOCAL_AUX_PP_SIGN_PARAMS_ERROR(params) \
    ) 

#endif // #include guard

