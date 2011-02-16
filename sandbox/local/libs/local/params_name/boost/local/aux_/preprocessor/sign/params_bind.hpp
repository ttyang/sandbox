
#ifndef BOOST_LOCAL_AUX_PP_SIGN_PARAMS_BIND_HPP_
#define BOOST_LOCAL_AUX_PP_SIGN_PARAMS_BIND_HPP_

#include "parsed_params_/index.hpp"
#include <boost/preprocessor/tuple/elem.hpp>

#define BOOST_LOCAL_AUX_PP_SIGN_PARAMS_BIND(params) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_AUX_PP_SIGN_PARSED_PARAMS_INDEX_MAX, \
            BOOST_LOCAL_AUX_PP_SIGN_PARSED_PARAMS_INDEX_BIND, \
            params)

#define BOOST_LOCAL_AUX_PP_SIGN_PARAMS_HAS_BIND(params) \
    BOOST_PP_GREATER(BOOST_PP_SEQ_SIZE( /* size > 1 because nil-seq */ \
            BOOST_LOCAL_AUX_PP_SIGN_PARAMS_BIND(params)), 1)

#define BOOST_LOCAL_AUX_PP_SIGN_PARAMS_BIND_THIS_COUNT(params) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_AUX_PP_SIGN_PARSED_PARAMS_INDEX_MAX, \
            BOOST_LOCAL_AUX_PP_SIGN_PARSED_PARAMS_INDEX_BIND_THIS_COUNT, \
            params)

#define BOOST_LOCAL_AUX_PP_SIGN_PARAMS_HAS_BIND_THIS(params) \
    BOOST_PP_GREATER(BOOST_LOCAL_AUX_PP_SIGN_PARAMS_BIND_THIS_COUNT( \
            params), 0)

#endif // #include guard

