// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_CALL_VISITORS_HPP
#define BOOST_GRAPH_CALL_VISITORS_HPP

#include <boost/config.hpp>
#include <boost/graph/visitors.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <utility>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/pair.hpp>
#include <boost/fusion/view/filter_view.hpp>
#include <boost/fusion/iterator.hpp>
#endif

namespace boost {
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  namespace detail {

    // Invoked when itr is past-the-end.
    template <
        typename Iterator
      , typename EndIterator
      , typename T
      , typename InputGraph
    >
    inline void
        call_visitors_impl(
            Iterator itr
          , EndIterator itr_end
          , T t
          , InputGraph& input_graph
          , ::boost::mpl::true_
        )
    {
    }

    // Invoked when itr is not past-the-end.
    template <
        typename Iterator
      , typename EndIterator
      , typename T
      , typename InputGraph
    >
    inline void
        call_visitors_impl(
            Iterator itr
          , EndIterator itr_end
          , T t
          , InputGraph& input_graph
          , ::boost::mpl::false_
        )
    {
        ::boost::fusion::deref(itr).second(t, input_graph);
        call_visitors_impl(
            ::boost::fusion::next(itr)
          , itr_end
          , t
          , input_graph
          , ::boost::mpl::equal_to<
                ::boost::mpl::int_<0>
              , typename ::boost::fusion::result_of::distance<
                    typename ::boost::fusion::result_of::next<Iterator>::type
                  , EndIterator
                >::type
            >()
        );
    }

    template <typename Filter>
    struct matches_event_filter
    {
        template <typename Pair>
        struct apply
        {
            typedef ::std::tr1::is_same<
                        Filter
                      , typename Pair::first_type
                    >
                    type;
        };
    };

    // Invoked if std::pair is used as a Boost.Fusion Sequence.
    template <
        typename Filter
      , typename FirstFilter
      , typename FirstVisitor
      , typename SecondFilter
      , typename SecondVisitor
      , typename T
      , typename InputGraph
    >
    inline void
        call_visitors_dispatch2(
            ::std::pair<
                ::boost::fusion::pair<FirstFilter,FirstVisitor>
              , ::boost::fusion::pair<SecondFilter,SecondVisitor>
            >& visitors
          , T t
          , InputGraph& input_graph
        )
    {
        typedef ::boost::fusion::filter_view<
                    ::std::pair<
                        ::boost::fusion::pair<FirstFilter,FirstVisitor>
                      , ::boost::fusion::pair<SecondFilter,SecondVisitor>
                    >
                  , matches_event_filter<Filter>
                >
                Listeners;

        Listeners listeners(visitors);

        call_visitors_impl(
            ::boost::fusion::begin(listeners)
          , ::boost::fusion::end(listeners)
          , t
          , input_graph
          , ::boost::mpl::equal_to<
                ::boost::mpl::int_<0>
              , typename ::boost::fusion::result_of::distance<
                    typename ::boost::fusion::result_of::begin<Listeners>::type
                  , typename ::boost::fusion::result_of::end<Listeners>::type
                >::type
            >()
        );
    }

    // Invoked for Event Visitor Lists.
    template <
        typename Filter
      , typename First
      , typename Second
      , typename T
      , typename InputGraph
    >
    inline void
        call_visitors_dispatch2(
            ::std::pair<First,Second>& visitors
          , T t
          , InputGraph& input_graph
        )
    {
        invoke_visitors(visitors, t, input_graph, Filter());
    }

    // Invoked for other Boost.Fusion sequences.
    template <
        typename Filter
      , typename VisitorList
      , typename T
      , typename InputGraph
    >
    inline void
        call_visitors_dispatch2(
            VisitorList& visitors
          , T t
          , InputGraph& input_graph
        )
    {
        typedef ::boost::fusion::filter_view<
                    VisitorList
                  , matches_event_filter<Filter>
                >
                Listeners;

        Listeners listeners(visitors);

        call_visitors_impl(
            ::boost::fusion::begin(listeners)
          , ::boost::fusion::end(listeners)
          , t
          , input_graph
          , ::boost::mpl::equal_to<
                ::boost::mpl::int_<0>
              , typename ::boost::fusion::result_of::distance<
                    typename ::boost::fusion::result_of::begin<Listeners>::type
                  , typename ::boost::fusion::result_of::end<Listeners>::type
                >::type
            >()
        );
    }

    // So we know that VisitorList is a Boost.Fusion Sequence, but we still
    // need to know whether or not it's a std::pair and, if so, whether it's
    // being used as a Boost.Fusion Sequence or as an Event Visitor List.
    template <
        typename Filter
      , typename VisitorList
      , typename T
      , typename InputGraph
    >
    inline void
        call_visitors_dispatch(
            VisitorList& visitors
          , T t
          , InputGraph& input_graph
          , ::boost::mpl::true_
        )
    {
        call_visitors_dispatch2<Filter>(
            visitors
          , t
          , input_graph
        );
    }

    // Invoked if std::pair is not recognized as a Boost.Fusion Sequence.
    template <
        typename Filter
      , typename VisitorList
      , typename T
      , typename InputGraph
    >
    inline void
        call_visitors_dispatch(
            VisitorList& visitors
          , T t
          , InputGraph& input_graph
          , ::boost::mpl::false_
        )
    {
        invoke_visitors(visitors, t, input_graph, Filter());
    }
  }  // namespace detail
#endif  // !BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    //[reference__call_visitors
    template <
        typename Filter
      , typename VisitorList
      , typename T
      , typename InputGraph
    >
    void
        call_visitors(
            VisitorList& visitors
          , T t
          , InputGraph& input_graph
        );
    //]

    template <
        typename Filter
      , typename VisitorList
      , typename T
      , typename InputGraph
    >
    inline void
        call_visitors(
            VisitorList& visitors
          , T t
          , InputGraph& input_graph
        )
    {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        invoke_visitors(visitors, t, input_graph, Filter());
#else
        detail::call_visitors_dispatch<Filter>(
            visitors
          , t
          , input_graph
          , typename ::boost::fusion::traits::is_sequence<VisitorList>::type()
        );
#endif
    }
}  // namespace boost

#endif  // BOOST_GRAPH_CALL_VISITORS_HPP

