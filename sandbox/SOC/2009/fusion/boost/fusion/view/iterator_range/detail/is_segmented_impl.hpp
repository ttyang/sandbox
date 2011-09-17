/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ITERATOR_RANGE_DETAIL_IS_SEGMENTED_HPP
#define BOOST_FUSION_ITERATOR_RANGE_DETAIL_IS_SEGMENTED_HPP

#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    template <typename Context>
    struct segmented_iterator;

    namespace extension
    {
        template <typename Tag>
        struct is_segmented_impl;

        // An iterator_range of segmented_iterators is segmented
        template <>
        struct is_segmented_impl<iterator_range_tag>
        {
        private:
            template <typename Iterator>
            struct is_segmented_iterator
              : mpl::false_
            {};

            template <typename Iterator>
            struct is_segmented_iterator<Iterator &>
              : is_segmented_iterator<Iterator>
            {};

#ifndef BOOST_FUSION_NO_RVALUE_REFERENCES
            template <typename Iterator>
            struct is_segmented_iterator<Iterator &&>
              : is_segmented_iterator<Iterator>
            {};
#endif

            template <typename Iterator>
            struct is_segmented_iterator<Iterator const>
              : is_segmented_iterator<Iterator>
            {};

            template <typename Context>
            struct is_segmented_iterator<segmented_iterator<Context> >
              : mpl::true_
            {};

        public:
            template <typename Seq>
            struct apply
              : is_segmented_iterator<typename detail::remove_reference<Seq>::type::begin_type>::type

            {
                typedef typename detail::remove_reference<Seq>::type seq;

                BOOST_FUSION_STATIC_ASSERT(
                    is_segmented_iterator<typename seq::begin_type>::value
                    ==
                    is_segmented_iterator<typename seq::end_type>::value)
            };
        };
    }
}}

#endif
