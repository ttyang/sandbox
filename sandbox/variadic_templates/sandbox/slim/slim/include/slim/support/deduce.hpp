/*==============================================================================
    Copyright (c) 2007 Tobias Schwinger
    Copyright (c) 2009-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef SLIM_SUPPORT_DEDUCE_HPP
#define SLIM_SUPPORT_DEDUCE_HPP

#include <slim/support/internal/base.hpp>
#include <slim/support/internal/result_of.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#ifndef SLIM_NO_RVALUE_REFERENCES
#   include <boost/mpl/not.hpp>
#   include <boost/type_traits/is_array.hpp>
#endif
#include <boost/type_traits/is_same.hpp>
#include <boost/ref.hpp>

namespace slim
{
    namespace traits
    {
#if BOOST_WORKAROUND(BOOST_MSVC,==1600)
        template<typename T>
        struct deduce_stage2
        {
            typedef T type;
        };

        template<typename T>
        struct deduce
          : deduce_stage2<T>
        {};
#else
        template<typename T>
        struct deduce
        {
            typedef T type;
        };
#endif

        template<typename T>
        struct deduce<boost::reference_wrapper<T> >
        {
            typedef T& type;
        };

#define SLIM_DEDUCE_CV_REF_SPECIALIZATION(MODIFIER,DEDUCE)                      \
        template<typename T>                                                    \
        struct DEDUCE<T MODIFIER>                                               \
        {                                                                       \
            typedef detail::is_po_callable<T MODIFIER> is_po_callable;          \
                                                                                \
            typedef typename                                                    \
                boost::mpl::eval_if_c<                                          \
                    is_po_callable::type::value                                 \
                  , boost::mpl::if_c<                                           \
                        is_po_callable::is_pointer::value                       \
                      , T                                                       \
                      , T MODIFIER                                              \
                    >                                                           \
                  , deduce<T>                                                   \
                >::type                                                         \
            type;                                                               \
        };                                                                      \
                                                                                \
        template<typename T>                                                    \
        struct deduce<boost::reference_wrapper<T> MODIFIER>                     \
        {                                                                       \
            typedef T& type;                                                    \
        };

        SLIM_DEDUCE_CV_REF_SPECIALIZATION(volatile&,deduce)
        SLIM_DEDUCE_CV_REF_SPECIALIZATION(const volatile&,deduce)

#if BOOST_WORKAROUND(BOOST_MSVC,==1600)
        SLIM_DEDUCE_CV_REF_SPECIALIZATION(volatile&&,deduce_stage2)
        SLIM_DEDUCE_CV_REF_SPECIALIZATION(
            const volatile&&,deduce_stage2)

        SLIM_DEDUCE_CV_REF_SPECIALIZATION(&,deduce)
        SLIM_DEDUCE_CV_REF_SPECIALIZATION(const&,deduce)
        SLIM_DEDUCE_CV_REF_SPECIALIZATION(&&,deduce_stage2)
        SLIM_DEDUCE_CV_REF_SPECIALIZATION(const&&,deduce_stage2)
#else
#   ifndef SLIM_NO_RVALUE_REFERENCES
        SLIM_DEDUCE_CV_REF_SPECIALIZATION(volatile&&,deduce)
        SLIM_DEDUCE_CV_REF_SPECIALIZATION(const volatile&&,deduce)
#   endif
        SLIM_ALL_CV_REF_COMBINATIONS(
            SLIM_DEDUCE_CV_REF_SPECIALIZATION,deduce)
#endif

#undef SLIM_DEDUCE_CV_REF_SPECIALIZATION

#define SLIM_DEDUCE_ARRAY_SPECIALIZATION(MODIFIER1,MODIFIER2,MODIFIER3)         \
        template<typename T, int N>                                             \
        struct deduce<T MODIFIER1[N]>                                           \
        {                                                                       \
            typedef T MODIFIER2(MODIFIER3 type)[N];                             \
        };

        SLIM_DEDUCE_ARRAY_SPECIALIZATION(BOOST_PP_EMPTY(),const,&)
        SLIM_DEDUCE_ARRAY_SPECIALIZATION(const,const,&)
        SLIM_DEDUCE_ARRAY_SPECIALIZATION(volatile,volatile,&)
        SLIM_DEDUCE_ARRAY_SPECIALIZATION(
            const volatile,const volatile,&)

        SLIM_DEDUCE_ARRAY_SPECIALIZATION((&),BOOST_PP_EMPTY(),&)
        SLIM_DEDUCE_ARRAY_SPECIALIZATION(const(&),const,&)
        SLIM_DEDUCE_ARRAY_SPECIALIZATION(volatile(&),volatile,&)
        SLIM_DEDUCE_ARRAY_SPECIALIZATION(
            const volatile(&),const volatile,&)

#ifndef SLIM_NO_RVALUE_REFERENCES
        SLIM_DEDUCE_ARRAY_SPECIALIZATION((&&),BOOST_PP_EMPTY(),&&)
        SLIM_DEDUCE_ARRAY_SPECIALIZATION(const(&&),const,&&)
        SLIM_DEDUCE_ARRAY_SPECIALIZATION(volatile(&&),volatile,&&)
        SLIM_DEDUCE_ARRAY_SPECIALIZATION(
            const volatile(&&),const volatile,&&)
#endif
    }

    namespace detail
    {
        template<typename T>
        struct deduce_ref
        {
            typedef typename traits::deduce<T>::type deduced;
            typedef
                boost::mpl::and_<
                    is_lrref<T>
                  , boost::is_same<typename identity<T>::type,deduced>
                >
            is_regular_reference;

#ifdef SLIM_NO_RVALUE_REFERENCES
            typedef typename
                boost::mpl::if_c<
                    is_regular_reference::value
                  , T
                  , typename add_lref<deduced>::type
                >::type
            type;
#else
            //8.5.3p5...
            typedef typename
                boost::mpl::eval_if_c<
                    is_regular_reference::value
                  , boost::mpl::if_c<
                        boost::mpl::or_<
                            boost::mpl::not_<is_rref<T> >
                          , boost::is_class<deduced>
                          , boost::is_array<deduced>
                        >::value
                      , T
                      , deduced&
                    >
                  , add_lref<deduced>
                >::type
            type;
#endif
        };
    }
}

#endif
