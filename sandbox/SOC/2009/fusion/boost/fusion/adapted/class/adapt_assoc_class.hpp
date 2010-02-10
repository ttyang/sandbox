/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_CLASS_ADAPT_ASSOC_CLASS_HPP
#define BOOST_FUSION_ADAPTED_CLASS_ADAPT_ASSOC_CLASS_HPP

#include <boost/fusion/support/internal/ref.hpp>
#include <boost/preprocessor/empty.hpp>

#include <boost/fusion/adapted/detail/class/extension.hpp>
#include <boost/fusion/adapted/detail/class/adapt_base.hpp>
#include <boost/fusion/adapted/detail/class/at_impl.hpp>
#include <boost/fusion/adapted/detail/class/is_view_impl.hpp>
#include <boost/fusion/adapted/detail/class/is_sequence_impl.hpp>
#include <boost/fusion/adapted/detail/class/value_at_impl.hpp>
#include <boost/fusion/adapted/detail/class/category_of_impl.hpp>
#include <boost/fusion/adapted/detail/class/size_impl.hpp>
#include <boost/fusion/adapted/detail/class/begin_impl.hpp>
#include <boost/fusion/adapted/detail/class/end_impl.hpp>
#include <boost/fusion/adapted/detail/class/value_of_impl.hpp>
#include <boost/fusion/adapted/detail/class/deref_impl.hpp>
#include <boost/fusion/adapted/detail/class/deref_data_impl.hpp>
#include <boost/fusion/adapted/detail/class/key_of_impl.hpp>
#include <boost/fusion/adapted/detail/class/value_of_data_impl.hpp>

#define BOOST_FUSION_ADAPT_ASSOC_CLASS_FILLER_0(A, B, C, D, E)\
    ((A, B, C, D, E)) BOOST_FUSION_ADAPT_ASSOC_CLASS_FILLER_1
#define BOOST_FUSION_ADAPT_ASSOC_CLASS_FILLER_1(A, B, C, D, E)\
    ((A, B, C, D, E)) BOOST_FUSION_ADAPT_ASSOC_CLASS_FILLER_0
#define BOOST_FUSION_ADAPT_ASSOC_CLASS_FILLER_0_END
#define BOOST_FUSION_ADAPT_ASSOC_CLASS_FILLER_1_END

#define BOOST_FUSION_ADAPT_ASSOC_CLASS_C(                                       \
    TEMPLATE_PARAMS_SEQ, NAME_SEQ, I, ATTRIBUTE)                                \
                                                                                \
    BOOST_FUSION_ADAPT_CLASS_C_BASE(TEMPLATE_PARAMS_SEQ,NAME_SEQ,I,ATTRIBUTE,5) \
                                                                                \
    template<                                                                   \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS(TEMPLATE_PARAMS_SEQ)   \
    >                                                                           \
    struct struct_assoc_key<BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ), I> \
    {                                                                           \
        typedef BOOST_PP_TUPLE_ELEM(5, 4, ATTRIBUTE) type;                      \
    };

#define BOOST_FUSION_ADAPT_ASSOC_TPL_CLASS(                                     \
    TEMPLATE_PARAMS_SEQ, NAME_SEQ, ATTRIBUTES)                                  \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (1)TEMPLATE_PARAMS_SEQ,                                                 \
        (1)NAME_SEQ,                                                            \
        assoc_class_tag,                                                        \
        BOOST_PP_CAT(BOOST_FUSION_ADAPT_ASSOC_CLASS_FILLER_0 ATTRIBUTES,_END),  \
        BOOST_FUSION_ADAPT_ASSOC_CLASS_C)

#define BOOST_FUSION_ADAPT_ASSOC_CLASS(NAME, ATTRIBUTES)                        \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (0),                                                                    \
        (0)(NAME),                                                              \
        assoc_class_tag,                                                        \
        BOOST_PP_CAT(BOOST_FUSION_ADAPT_ASSOC_CLASS_FILLER_0 ATTRIBUTES,_END),  \
        BOOST_FUSION_ADAPT_ASSOC_CLASS_C)

#endif
