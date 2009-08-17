// Copyright Christopher Schmidt 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FUSION_CONTAINER_SET_SET_HPP
#define BOOST_FUSION_CONTAINER_SET_SET_HPP

#include <boost/fusion/container/set/set_fwd.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/internal/ref.hpp>

#include <boost/mpl/bool.hpp>

#include <boost/fusion/container/set/detail/begin_impl.hpp>
#include <boost/fusion/container/set/detail/end_impl.hpp>
#include <boost/fusion/container/set/detail/deref_impl.hpp>
#include <boost/fusion/container/set/detail/value_of_impl.hpp>
#include <boost/fusion/container/set/detail/value_of_data_impl.hpp>
#include <boost/fusion/container/set/detail/deref_data_impl.hpp>
#include <boost/fusion/container/set/detail/key_of_impl.hpp>

#include <boost/fusion/container/detail/forward_ctor.hpp>

namespace boost { namespace fusion
{
    struct fusion_sequence_tag;

    VARIADIC_TEMPLATE(FUSION_MAX_SET_SIZE)
    struct set
      : sequence_base<set<EXPAND_TEMPLATE_ARGUMENTS(FUSION_MAX_SET_SIZE)> >
    {
        typedef set_category category;
        typedef set_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;

        typedef
            vector<EXPAND_TEMPLATE_ARGUMENTS(FUSION_MAX_SET_SIZE)>
        storage_type;
        typedef typename storage_type::size size;

        set()
        {}

#define BOOST_FUSION_SET_CTOR(COMBINATION,_)\
        set(set COMBINATION set_)\
          : data(BOOST_FUSION_FORWARD(set COMBINATION,set_).data)\
        {}

        BOOST_FUSION_ALL_CTOR_COMBINATIONS(BOOST_FUSION_SET_CTOR,_)

#undef BOOST_FUSION_SET_CTOR

#define BOOST_FUSION_SEQ_NAME set
#define BOOST_FUSION_MAX_SEQ_SIZE FUSION_MAX_SET_SIZE
#include <boost/fusion/container/detail/forward_ctor.hpp>
#undef BOOST_FUSION_MAX_SEQ_SIZE
#undef BOOST_FUSION_SEQ_NAME

        template <typename Seq>
        set&
        operator=(BOOST_FUSION_R_ELSE_CLREF(Seq) seq)
        {
            data = BOOST_FUSION_FORWARD(Seq, seq);
            return *this;
        }

        storage_type& get_data() { return data; }
        storage_type const& get_data() const { return data; }

    private:
        storage_type data;
    };
}}

#endif
