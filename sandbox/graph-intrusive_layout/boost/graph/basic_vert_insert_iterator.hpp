// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_BASIC_VERT_INSERT_ITERATOR_HPP
#define BOOST_GRAPH_BASIC_VERT_INSERT_ITERATOR_HPP

#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/iterator/iterator_facade.hpp>

#ifndef BOOST_NO_SFINAE
#include <boost/tr1/type_traits.hpp>
#include <boost/utility/enable_if.hpp>
#endif

//[reference__basic_vertex_insert_iterator__definition
namespace boost {

    template <typename Graph>
    class basic_vertex_insert_iterator
      : public ::boost::iterator_facade<
            basic_vertex_insert_iterator<Graph>
          , typename graph_traits<Graph>::vertex_descriptor
          , forward_traversal_tag
        >
    {
        //<-
#ifndef BOOST_NO_SFINAE
        struct enabler
        {
        };
#endif

        mutable Graph& _graph;
        mutable typename graph_traits<Graph>::vertex_descriptor _vertex;
        //->

     public:
        explicit basic_vertex_insert_iterator(Graph& graph);

        template <typename OtherGraph>
        basic_vertex_insert_iterator(
            basic_vertex_insert_iterator<OtherGraph> const& other
//<-
#ifndef BOOST_NO_SFINAE
          , typename ::boost::enable_if<
                ::std::tr1::is_convertible<OtherGraph&,Graph&>
              , enabler
            >::type = enabler()
#endif
//->
        );

        //<-
#if !BOOST_WORKAROUND(__GNUC__, == 2)
     private:
        friend class ::boost::iterator_core_access;
#endif

        typename graph_traits<Graph>::vertex_descriptor& dereference() const;

        void increment();
        //->
    };

    //<-
    template <typename Graph>
    basic_vertex_insert_iterator<Graph>::basic_vertex_insert_iterator(
        Graph& graph
    ) : _graph(graph), _vertex(graph_traits<Graph>::null_vertex())
    {
    }

    template <typename Graph>
    template <typename OtherGraph>
    basic_vertex_insert_iterator<Graph>::basic_vertex_insert_iterator(
        basic_vertex_insert_iterator<OtherGraph> const& other
#ifndef BOOST_NO_SFINAE
      , typename ::boost::enable_if<
            ::std::tr1::is_convertible<OtherGraph&,Graph&>
          , enabler
        >::type
#endif
    ) : _graph(other._graph), _vertex(other._vertex)
    {
    }

    template <typename Graph>
    inline typename graph_traits<Graph>::vertex_descriptor&
        basic_vertex_insert_iterator<Graph>::dereference() const
    {
        return _vertex = add_vertex(_graph);
    }

    template <typename Graph>
    inline void basic_vertex_insert_iterator<Graph>::increment()
    {
    }
    //->
}  // namespace boost
//]

//[reference__basic_vertex_inserter__prototype
namespace boost {

    template <typename Graph>
    basic_vertex_insert_iterator<Graph> basic_vertex_inserter(Graph& graph);

    //<-
    template <typename Graph>
    inline basic_vertex_insert_iterator<Graph>
        basic_vertex_inserter(Graph& graph)
    {
        return basic_vertex_insert_iterator<Graph>(graph);
    }
    //->
}  // namespace boost
//]

#endif  // BOOST_GRAPH_BASIC_VERT_INSERT_ITERATOR_HPP

