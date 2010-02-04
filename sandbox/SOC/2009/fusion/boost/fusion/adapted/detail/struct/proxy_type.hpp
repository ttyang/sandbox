/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_DETAIL_STRUCT_PROXY_TYPE_HPP
#define BOOST_FUSION_ADAPTED_DETAIL_STRUCT_PROXY_TYPE_HPP

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#define BOOST_FUSION_PROXY_TYPE_NS_BEGIN(R,DATA,ELEM) namespace ELEM {
#define BOOST_FUSION_PROXY_TYPE_NS_END(Z,I,DATA) }
#define BOOST_FUSION_NAMESPACE_DECLARATION_I(Z,I,ELEM) ELEM::

#define BOOST_FUSION_DEFINE_PROXY_TYPE(WRAPPED_TYPE,NAMESPACE,NAME)             \
    BOOST_PP_SEQ_FOR_EACH_R(1, BOOST_FUSION_PROXY_TYPE_NS_BEGIN, _, NAMESPACE)  \
                                                                                \
    struct NAME                                                                 \
    {                                                                           \
        NAME(WRAPPED_TYPE& obj)                                                 \
          : obj(obj)                                                            \
        {}                                                                      \
                                                                                \
        WRAPPED_TYPE& obj;                                                      \
    };                                                                          \
                                                                                \
    BOOST_PP_REPEAT_1(BOOST_PP_SEQ_SIZE(NAMESPACE),                             \
        BOOST_FUSION_PROXY_TYPE_NS_END,                                         \
        _)

#define BOOST_FUSION_NAMESPACE_DECLARATION(NAMESPACE)\
    BOOST_PP_SEQ_FOR_EACH_R(\
                    1,\
                    BOOST_FUSION_NAMESPACE_DECLARATION_I,\
                    _,\
                    NAMESPACE)

#endif
