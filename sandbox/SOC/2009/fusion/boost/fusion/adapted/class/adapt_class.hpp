/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_ADAPT_STRUCT_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_ADAPT_STRUCT_HPP

#include <boost/fusion/support/internal/ref.hpp>
#include <boost/preprocessor/cat.hpp>

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

#define BOOST_FUSION_ADAPT_CLASS_FILLER_0(A, B, C, D)\
    ((A, B, C, D)) BOOST_FUSION_ADAPT_CLASS_FILLER_1
#define BOOST_FUSION_ADAPT_CLASS_FILLER_1(A, B, C, D)\
    ((A, B, C, D)) BOOST_FUSION_ADAPT_CLASS_FILLER_0
#define BOOST_FUSION_ADAPT_CLASS_FILLER_0_END
#define BOOST_FUSION_ADAPT_CLASS_FILLER_1_END

#define BOOST_FUSION_ADAPT_CLASS(NAME, SEQ)\
    BOOST_FUSION_ADAPT_STRUCT_BASE(\
        NAME,\
        class_tag,\
        BOOST_PP_CAT(BOOST_FUSION_ADAPT_CLASS_FILLER_0 SEQ,_END),\
        BOOST_FUSION_ADAPT_CLASS_C)

#define BOOST_FUSION_ADAPT_CLASS_C(R, NAME, I, XY)\
    BOOST_FUSION_ADAPT_CLASS_C_BASE(NAME, I, XY, 4)

#endif
