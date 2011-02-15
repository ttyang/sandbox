
#ifndef BOOST_LOCAL_AUX_PP_SIGN_PARAMS_BIND_HPP_
#define BOOST_LOCAL_AUX_PP_SIGN_PARAMS_BIND_HPP_

#include "../parsed_/params/index.hpp"
#include <boost/preprocessor/tuple/elem.hpp>

#define BOOST_LOCAL_AUX_PP_SIGN_PARAMS_BIND(params) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_AUX_PP_SIGN_PARSED_PARAMS_INDEX_MAX, \
            BOOST_LOCAL_AUX_PP_SIGN_PARSED_PARAMS_INDEX_BIND, \
            params)

#define BOOST_LOCAL_AUX_PP_SIGN_PARAMS_BIND_THIS_COUNT(params) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_AUX_PP_SIGN_PARSED_PARAMS_INDEX_MAX, \
            BOOST_LOCAL_AUX_PP_SIGN_PARSED_PARAMS_INDEX_BIND_THIS_COUNT, \
            params)

#endif // #include guard

