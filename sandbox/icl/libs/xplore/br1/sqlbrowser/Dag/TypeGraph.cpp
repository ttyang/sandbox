#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graph_utility.hpp>

#include <boost/property_map/property_map.hpp>

#include "StringVisitor2.h"

#include "Dag/TypeGraph.h"

//using namespace dag::db;
struct VertexProps { //CL...
  boost::default_color_type color;
  std::size_t discover_time;
};

template<class Key, class Val>
struct proper
{
    typedef Key key_type;
    typedef Val value_type;
    typedef boost::lvalue_property_map_tag category;
};

namespace boost
{

template<class Key, class Val>
struct property_traits< proper<Key,Val> >
{
    typedef Key key_type;
    typedef Val value_type;
};

}

template<class Key, class Val>
typename proper<Key,Val>::value_type get(const proper<Key,Val>& pro, typename proper<Key,Val>::key_type key)
{
    typedef typename proper<Key,Val>::key_type KeyType;
    return KeyType();
}

template<class Key, class Val>
void put(const proper<Key,Val>& pro, typename proper<Key,Val>::key_type key, typename proper<Key,Val>::value_type val)
{
    ;
}


dag::db::tString dag::db::TypeGraph::depthFirstString()
{
    typedef dag::db::TypeGraph::vertex_descriptor vertex_descriptor;
    typedef dag::db::TypeGraph::tVertex2Depth     tVertex2Depth;

    tVertex2Depth vertexDepth;
    QString tygraAsString;

    typedef  std::map<vertex_descriptor, boost::default_color_type> tColorMap;
    std::map<vertex_descriptor, boost::default_color_type> colorMap0;
    //boost::associative_property_map< tColorMap > colorMap( colorMap0 );

    typedef  std::map<vertex_descriptor, int> tColorMapV;
    std::vector<boost::default_color_type> colorMapV( boost::num_vertices(m_aGraph) );

    //boost::property_map<dag::db::TypeGraph, boost::default_color_type>::type colorMap2 = get(&VertexProps::color, m_aGraph);
    proper<vertex_descriptor, boost::default_color_type> colorMap;

    boost::depth_first_search(
        m_aGraph
      , boost::visitor(make_dfs_visitor(boost::make_list(
                                              StringVisitor2::OnDiscoverVertex(&tygraAsString, vertexDepth)
                                            , StringVisitor2::OnExamineEdge   (&tygraAsString, vertexDepth)
                                            , StringVisitor2::OnFinishVertex  (&tygraAsString, vertexDepth)
                                            )
                      ))
      , colorMap
    );

    return tygraAsString;

}
