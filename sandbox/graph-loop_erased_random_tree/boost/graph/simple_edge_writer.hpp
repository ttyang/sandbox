// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_SIMPLE_EDGE_WRITER_HPP
#define BOOST_GRAPH_SIMPLE_EDGE_WRITER_HPP

#include <boost/tuple/tuple_io.hpp>
#include <boost/fusion/support/pair.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>

//[reference__simple_edge_writer
namespace boost {

    template <
        typename VertexPropertyMap
      , typename OutputStream
      , typename CharT
      , typename Filter
    >
    class simple_edge_writer
    {
        //<-
        VertexPropertyMap _property_map;
        OutputStream&     _os;
        CharT const*      _suffix;
        //->

     public:
        typedef Filter event_filter;

        simple_edge_writer(
            VertexPropertyMap property_map
          , OutputStream& os
          , CharT const* suffix
        );

        simple_edge_writer(simple_edge_writer const& copy);

        template <typename Graph>
        void
            operator()(
                typename graph_traits<Graph>::edge_descriptor e
              , Graph const& g
            );
    };

    //<-
    template <
        typename VertexPropertyMap
      , typename OutputStream
      , typename CharT
      , typename Filter
    >
    simple_edge_writer<
        VertexPropertyMap
      , OutputStream
      , CharT
      , Filter
    >::simple_edge_writer(
        VertexPropertyMap property_map
      , OutputStream& os
      , CharT const* suffix
    ) : _property_map(property_map), _os(os), _suffix(suffix)
    {
    }

    template <
        typename VertexPropertyMap
      , typename OutputStream
      , typename CharT
      , typename Filter
    >
    simple_edge_writer<
        VertexPropertyMap
      , OutputStream
      , CharT
      , Filter
    >::simple_edge_writer(simple_edge_writer const& copy)
      : _property_map(copy._property_map), _os(copy._os), _suffix(copy._suffix)
    {
    }

    template <
        typename VertexPropertyMap
      , typename OutputStream
      , typename CharT
      , typename Filter
    >
    template <typename Graph>
    inline void
        simple_edge_writer<
            VertexPropertyMap
          , OutputStream
          , CharT
          , Filter
        >::operator()(
            typename graph_traits<Graph>::edge_descriptor e
          , Graph const& g
        )
    {
        _os << ::boost::make_tuple(
            get(_property_map, source(e, g))
          , get(_property_map, target(e, g))
        ) << _suffix;
    }
    //->
}  // namespace boost
//]

//[reference__make_simple_edge_writer
namespace boost {

    template <
        typename VertexPropertyMap
      , typename OutputStream
      , typename CharT
      , typename Filter
    >
    simple_edge_writer<VertexPropertyMap,OutputStream,CharT,Filter>
        make_simple_edge_writer(
            VertexPropertyMap property_map
          , OutputStream& os
          , CharT const* suffix
          , Filter
        );

    //<-
    template <
        typename VertexPropertyMap
      , typename OutputStream
      , typename CharT
      , typename Filter
    >
    inline simple_edge_writer<VertexPropertyMap,OutputStream,CharT,Filter>
        make_simple_edge_writer(
            VertexPropertyMap property_map
          , OutputStream& os
          , CharT const* suffix
          , Filter
        )
    {
        return simple_edge_writer<VertexPropertyMap,OutputStream,CharT,Filter>(
            property_map
          , os
          , suffix
        );
    }
    //->
}  // namespace boost
//]

//[reference__fuse_simple_edge_writer
namespace boost {

    template <
        typename Filter
      , typename VertexPropertyMap
      , typename OutputStream
      , typename CharT
    >
    ::boost::fusion::pair<
        Filter
      , simple_edge_writer<VertexPropertyMap,OutputStream,CharT,Filter>
    >
        fuse_simple_edge_writer(
            VertexPropertyMap property_map
          , OutputStream& os
          , CharT const* suffix
        );

    //<-
    template <
        typename Filter
      , typename VertexPropertyMap
      , typename OutputStream
      , typename CharT
    >
    inline ::boost::fusion::pair<
        Filter
      , simple_edge_writer<VertexPropertyMap,OutputStream,CharT,Filter>
    >
        fuse_simple_edge_writer(
            VertexPropertyMap property_map
          , OutputStream& os
          , CharT const* suffix
        )
    {
        return ::boost::fusion::pair<
            Filter
          , simple_edge_writer<VertexPropertyMap,OutputStream,CharT,Filter>
        >(
            simple_edge_writer<VertexPropertyMap,OutputStream,CharT,Filter>(
                property_map
              , os
              , suffix
            )
        );
    }
    //->
}  // namespace boost
//]

#endif  // BOOST_GRAPH_SIMPLE_EDGE_WRITER_HPP

