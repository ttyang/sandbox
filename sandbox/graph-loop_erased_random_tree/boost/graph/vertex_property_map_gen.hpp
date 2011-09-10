// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_VERTEX_PROPERTY_MAP_GEN_HPP
#define BOOST_GRAPH_VERTEX_PROPERTY_MAP_GEN_HPP

#include <deque>
#include <map>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>

//[reference__vertex_property_map_gen
namespace boost {

    template <typename Graph, typename Value>
    class vertex_property_map_gen
    {
        //<-
        typedef typename property_map<Graph,vertex_index_t>::const_type
                index_map;
        typedef typename property_traits<index_map>::value_type
                index_value;

        class yes_type : public put_get_helper<Value&,yes_type>
        {
            typedef ::std::deque<Value>                             values;

         public:
            typedef typename graph_traits<Graph>::vertex_descriptor key_type;
            typedef Value                                           value_type;
            typedef Value&                                          reference;
            typedef lvalue_property_map_tag                         category;

         private:
            values _values;
            index_map _i_map;
            iterator_property_map<
                typename values::iterator
              , index_map
              , value_type
              , reference
            > _map;

         public:
            inline yes_type(Graph const& g)
              : _values(num_vertices(g))
              , _i_map(get(vertex_index, g))
              , _map(_values.begin(), _i_map)
            {
            }

            inline yes_type(yes_type const& copy)
              : _values(copy._values)
              , _i_map(copy._i_map)
              , _map(_values.begin(), _i_map)
            {
            }

            inline reference operator[](key_type const& key) const
            {
                return _map[key];
            }
        };

        class no_type : public put_get_helper<Value&,no_type>
        {
         public:
            typedef typename graph_traits<Graph>::vertex_descriptor key_type;
            typedef Value                                           value_type;
            typedef Value&                                          reference;
            typedef lvalue_property_map_tag                         category;

         private:
            typedef ::std::map<key_type,value_type>                 under_map;

            under_map                           _under_map;
            associative_property_map<under_map> _map;

         public:
            inline no_type(Graph const& g) : _under_map(), _map(_under_map)
            {
            }

            inline no_type(no_type const& copy)
              : _under_map(copy._under_map), _map(_under_map)
            {
            }

            inline reference operator[](key_type const& key) const
            {
                return _map[key];
            }
        };
        //->

     public:
        typedef // implementation_defined
                //<-
                typename ::boost::mpl::if_<
                    ::std::tr1::is_integral<index_value>
                  , yes_type
                  , no_type
                >::type
                //->
                type;
    };
}  // namespace boost
//]

//[reference__make_vertex_property_map
namespace boost {

    template <typename Value, typename Graph>
    typename vertex_property_map_gen<Graph,Value>::type
        make_vertex_property_map(Graph const& g);

    //<-
    template <typename Value, typename Graph>
    inline typename vertex_property_map_gen<Graph,Value>::type
        make_vertex_property_map(Graph const& g)
    {
        return typename vertex_property_map_gen<Graph,Value>::type(g);
    }
    //->
}  // namespace boost
//]

//[reference__make_vertex_property_map__with_value
namespace boost {

    template <typename Graph, typename Value>
    typename vertex_property_map_gen<Graph,Value>::type
        make_vertex_property_map(Graph const& g, Value);

    //<-
    template <typename Graph, typename Value>
    inline typename vertex_property_map_gen<Graph,Value>::type
        make_vertex_property_map(Graph const& g, Value)
    {
        return typename vertex_property_map_gen<Graph,Value>::type(g);
    }
    //->
}  // namespace boost
//]

//[reference__make_vertex_predecessor_map
namespace boost {

    template <typename Graph>
    typename vertex_property_map_gen<
        Graph
      , typename graph_traits<Graph>::vertex_descriptor
    >::type
        make_vertex_predecessor_map(Graph const& g);

    //<-
    template <typename Graph>
    inline typename vertex_property_map_gen<
        Graph
      , typename graph_traits<Graph>::vertex_descriptor
    >::type
        make_vertex_predecessor_map(Graph const& g)
    {
        return typename vertex_property_map_gen<
            Graph
          , typename graph_traits<Graph>::vertex_descriptor
        >::type(g);
    }
    //->
}  // namespace boost
//]

#endif  // BOOST_GRAPH_VERTEX_PROPERTY_MAP_GEN_HPP

