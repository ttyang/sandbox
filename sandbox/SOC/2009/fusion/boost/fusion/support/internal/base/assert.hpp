/*==============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_SUPPORT_INTERNAL_BASE_ASSERT_HPP
#define BOOST_FUSION_SUPPORT_INTERNAL_BASE_ASSERT_HPP

#ifdef BOOST_FUSION_ENABLE_STATIC_ASSERTS
#   include <boost/type_traits/is_base_of.hpp>

#   ifdef BOOST_NO_STATIC_ASSERT
#       include <boost/mpl/assert.hpp>
#       include <boost/static_assert.hpp>

#       define BOOST_FUSION_MPL_ASSERT(PRED)\
            BOOST_MPL_ASSERT(PRED);
#       define BOOST_FUSION_MPL_ASSERT_NOT(PRED)\
            BOOST_MPL_ASSERT_NOT(PRED);
#       define BOOST_FUSION_STATIC_ASSERT(PRED)\
            BOOST_STATIC_ASSERT(PRED);
#       define BOOST_FUSION_MPL_ASSERT_MSG(PRED,MESSAGE)\
            BOOST_FUSION_MPL_ASSERT(PRED)
#       define BOOST_FUSION_MPL_ASSERT_NOT_MSG(PRED,MESSAGE)\
            BOOST_FUSION_MPL_ASSERT_NOT(PRED)
#       define BOOST_FUSION_STATIC_ASSERT_MSG(PRED,MESSAGE)\
            BOOST_FUSION_STATIC_ASSERT(PRED)
#   else
#       include <boost/fusion/support/internal/small_big_type.hpp>

#       include <boost/preprocessor/stringize.hpp>
#       include <boost/mpl/if.hpp>

namespace boost { namespace fusion { namespace detail
{
    template<typename Pred>
    typename mpl::if_<Pred,small_type,big_type>::type
    evaluate_pred(void(*)(Pred));
}}}

#       define BOOST_FUSION_MPL_ASSERT(PRED)\
            static_assert(\
                sizeof(detail::evaluate_pred(\
                    reinterpret_cast<void (*) PRED>(0)))==\
                sizeof(detail::small_type)\
              , "assert failed: " BOOST_PP_STRINGIZE(PRED));
#       define BOOST_FUSION_MPL_ASSERT_NOT(PRED)\
            static_assert(\
                sizeof(detail::evaluate_pred(\
                    reinterpret_cast<void (*) PRED>(0)))==\
                sizeof(detail::big_type)\
              , "assert failed: " BOOST_PP_STRINGIZE(PRED));
#       define BOOST_FUSION_STATIC_ASSERT(PRED)\
            static_assert(\
                PRED\
              , "assert failed: " BOOST_PP_STRINGIZE(PRED));
#       define BOOST_FUSION_MPL_ASSERT_MSG(PRED,MESSAGE)\
            static_assert(\
                sizeof(detail::evaluate_pred(\
                    reinterpret_cast<void (*) PRED>(0)))==\
                sizeof(detail::small_type)\
              , "assert failed: " MESSAGE\
                " - assert expression: " BOOST_PP_STRINGIZE(PRED));
#       define BOOST_FUSION_MPL_ASSERT_NOT_MSG(PRED,MESSAGE)\
            static_assert(\
                sizeof(detail::evaluate_pred(\
                    reinterpret_cast<void (*) PRED>(0)))!=\
              , sizeof(detail::small_type)\
              , "assert failed: " MESSAGE\
                " - assert expression: " BOOST_PP_STRINGIZE(PRED));
#       define BOOST_FUSION_STATIC_ASSERT_MSG(PRED,MESSAGE)\
            static_assert(\
                PRED\
              , "assert failed: " MESSAGE\
                " - assert expression: " BOOST_PP_STRINGIZE(PRED));
#   endif
#else
#   define BOOST_FUSION_MPL_ASSERT(PRED)
#   define BOOST_FUSION_MPL_ASSERT_NOT(PRED)
#   define BOOST_FUSION_STATIC_ASSERT(PRED)
#   define BOOST_FUSION_MPL_ASSERT_MSG(PRED,MESSAGE)
#   define BOOST_FUSION_MPL_ASSERT_NOT_MSG(PRED,MESSAGE)
#   define BOOST_FUSION_STATIC_ASSERT_MSG(PRED,MESSAGE)
#endif

#define BOOST_FUSION_INDEX_CHECK(INDEX,MAX)                                     \
    BOOST_FUSION_STATIC_ASSERT_MSG(                                             \
        (INDEX) >= 0 &&                                                         \
            static_cast<unsigned int>(INDEX) < static_cast<unsigned int>(MAX),  \
        "Index (" BOOST_PP_STRINGIZE(INDEX) ") out of range "                   \
            "( [0..." BOOST_PP_STRINGIZE(MAX) ") )"                             \
    )
#define BOOST_FUSION_TAG_CHECK(TYPE,TAG)                                        \
    BOOST_FUSION_MPL_ASSERT((is_same<typename traits::tag_of<TYPE>::type,TAG>))

#ifdef BOOST_FUSION_ENABLE_STATIC_ASSERTS
#   include <boost/fusion/support/tag_of_fwd.hpp>
#   include <boost/mpl/and.hpp>
#   include <boost/mpl/or.hpp>
#   include <boost/mpl/not.hpp>
#   include <boost/mpl/equal_to.hpp>
#   include <boost/type_traits/is_convertible.hpp>
#   include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    namespace traits
    {
        template<typename T>
        struct is_sequence;

        template<typename T>
        struct is_view;

        template<typename T>
        struct is_iterator;

        template<typename T>
        struct is_associative;

        template<typename T>
        struct is_forward;

        template<typename T>
        struct is_bidirectional;

        template<typename T>
        struct is_random_access;
    }

    namespace result_of
    {
        template<typename Seq>
        struct size;

        template<typename Seq>
        struct empty;
    }
}}

#   include <boost/fusion/support/tag_of.hpp>
#   include <boost/fusion/support/category_of.hpp>
#   include <boost/fusion/support/is_iterator.hpp>
#   include <boost/fusion/support/is_sequence.hpp>
#   include <boost/fusion/support/is_view.hpp>
#   include <boost/fusion/sequence/intrinsic/size.hpp>
#   include <boost/fusion/sequence/intrinsic/empty.hpp>
#endif

#endif