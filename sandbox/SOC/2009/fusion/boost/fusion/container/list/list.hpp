/*=============================================================================
    Copyright (c) 2005 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_LIST_LIST_HPP
#define BOOST_FUSION_CONTAINER_LIST_LIST_HPP

#include <boost/fusion/container/list/list_fwd.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/ref.hpp>

#include <boost/type_traits/is_convertible.hpp>

#include <boost/fusion/container/list/detail/list/begin_impl.hpp>
#include <boost/fusion/container/list/detail/list/end_impl.hpp>
#include <boost/fusion/container/list/detail/list/at_impl.hpp>
#include <boost/fusion/container/list/detail/list/value_at_impl.hpp>

namespace boost { namespace fusion
{
    struct list_tag;
    struct fusion_sequence_tag;
#ifndef BOOST_NO_VARIADIC_TEMPLATES
    struct void_;
#endif

    VARIADIC_TEMPLATE(FUSION_MAX_LIST_SIZE)
    struct list
      : sequence_base<list<EXPAND_ARGUMENTS(FUSION_MAX_LIST_SIZE)> >
    {
        typedef forward_traversal_tag category;

        typedef list_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::false_ is_view;

        typedef vector<EXPAND_ARGUMENTS(FUSION_MAX_LIST_SIZE)> storage_type;
        typedef typename storage_type::size size;

        list()
          : data()
        {}

        template<typename List>
        list(BOOST_FUSION_R_ELSE_CLREF(List) list_,
               typename enable_if<is_convertible<
                   typename detail::remove_reference<List>::type*
                 , list const volatile*> >::type* =NULL)
          : data(BOOST_FUSION_FORWARD(List,list_).data)
        {
        }

#ifdef BOOST_NO_VARIADIC_TEMPLATES
        template <typename Arg>
        list(BOOST_FUSION_R_ELSE_CLREF(Arg) arg)
            : data(BOOST_FUSION_FORWARD(Arg,arg))
        {}

#   include <boost/fusion/container/list/detail/list/pp/list_forward_ctor.hpp>
#else
        template <typename... OtherArguments>
        list(BOOST_FUSION_R_ELSE_CLREF(OtherArguments)... other_arguments)
            : data(BOOST_FUSION_FORWARD(OtherArguments,other_arguments)...)
        {}
#endif

        template <typename T>
        list&
        operator=(BOOST_FUSION_R_ELSE_CLREF(T) rhs)
        {
            data = BOOST_FUSION_FORWARD(T, rhs);
            return *this;
        }

        storage_type& get_data() { return data; }
        storage_type const& get_data() const { return data; }

    private:

        storage_type data;
    };
}}

#endif
