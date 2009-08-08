/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ITERATOR_DEREF_DATA_HPP
#define BOOST_FUSION_ITERATOR_DEREF_DATA_HPP

#include <boost/fusion/support/ref.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_facade_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_data_impl;

        template <>
        struct deref_data_impl<iterator_facade_tag>
        {
            template <typename ItRef>
            struct apply
              : detail::remove_reference<ItRef>::type::
                    template deref_data<ItRef>
            {};
       };
    }

    namespace result_of
    {
        template <typename It>
        struct deref_data
          : extension::deref_data_impl<typename traits::tag_of<It>::type>::
                template apply<typename detail::add_lref<It>::type>
        {};
    }

    template <typename It>
    typename result_of::deref_data<It const&>::type
    deref_data(It const& it)
    {
        return result_of::deref_data<It const&>::call(it);
    }
}}

#endif
