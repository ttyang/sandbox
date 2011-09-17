/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_SEGMENTED_ITERATOR_DETAIL_SEGMENTED_ITERATOR_HPP
#define BOOST_FUSION_SEGMENTED_ITERATOR_DETAIL_SEGMENTED_ITERATOR_HPP

#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/deref_data.hpp>
#include <boost/fusion/iterator/key_of.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>
#include <boost/fusion/iterator/detail/segmented_equal_to.hpp>

namespace boost { namespace fusion
{
    struct nil;
    struct forward_traversal_tag;

    namespace detail
    {
        template <typename Stack>
        struct segmented_next_impl;
    }

    // A segmented iterator wraps a "context", which is a cons list
    // of ranges, the frontmost is range over values and the rest
    // are ranges over internal segments.
    template <typename Context>
    struct segmented_iterator
      : iterator_facade<segmented_iterator<Context>, forward_traversal_tag>
    {
        explicit segmented_iterator(Context const& ctx)
          : context(ctx)
        {}

        //auto deref(it)
        //{
        //  return deref(begin(car(it.context)))
        //}
        template <typename It>
        struct deref
        {
            typedef typename detail::remove_reference<It>::type it;
            typedef
                typename result_of::deref<
                    typename it::context_type::car_type::begin_type
                >::type
            type;

            static type call(It it)
            {
                return *it.context.car.first;
            }
        };

        //auto deref_data(it)
        //{
        //  return deref_data(begin(car(it.context)))
        //}
        template <typename It>
        struct deref_data
        {
            typedef typename detail::remove_reference<It>::type it;
            typedef
                typename result_of::deref_data<
                    typename It::context_type::car_type::begin_type
                >::type
            type;

            static type call(It it)
            {
                return fusion::deref_data(it.context.car.first);
            }
        };

        //auto key_of(it)
        //{
        //  return key_of(begin(car(it.context)))
        //}
        template <typename It>
        struct key_of
          : result_of::key_of<typename detail::remove_reference<It>::type::context_type::car_type::begin_type>
        {};

        //auto value_of(it)
        //{
        //  return value_of(begin(car(it.context)))
        //}
        template <typename It>
        struct value_of
          : result_of::value_of<typename detail::remove_reference<It>::type::context_type::car_type::begin_type>
        {};

        //auto value_of_data(it)
        //{
        //  return value_of_data(begin(car(it.context)))
        //}
        template <typename It>
        struct value_of_data
          : result_of::value_of_data<typename detail::remove_reference<It>::type::context_type::car_type::begin_type>
        {};

        // Compare all the segment iterators in each stack, starting with
        // the bottom-most.
        template <
            typename It1
          , typename It2
          , int Size1 = detail::remove_reference<It1>::type::context_type::size::value
          , int Size2 = detail::remove_reference<It2>::type::context_type::size::value
        >
        struct equal_to
          : mpl::false_
        {};

        template <typename It1, typename It2, int Size>
        struct equal_to<It1, It2, Size, Size>
          : detail::segmented_equal_to<
                typename detail::remove_reference<It1>::type::context_type
              , typename detail::remove_reference<It2>::type::context_type
            >
        {};

        template <typename It>
        struct next
        {
            typedef detail::segmented_next_impl<typename detail::remove_reference<It>::type::context_type> impl;
            typedef segmented_iterator<typename impl::type> type;

            static type call(It it)
            {
                return type(impl::call(it.context));
            }
        };

        typedef Context context_type;
        context_type context;
    };

}}

#endif
