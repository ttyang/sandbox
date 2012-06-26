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

/*CL
dag::db::tString dag::db::TypeGraph::depthFirstString()
{
    typedef dag::db::TypeGraph::vertex_descriptor vertex_descriptor;
    typedef dag::db::TypeGraph::tVertex2Depth     tVertex2Depth;

    tVertex2Depth vertexDepth;
    QString tygraAsString;

    boost::depth_first_search(
        m_aGraph
      , boost::visitor(make_dfs_visitor(boost::make_list(
                                              StringVisitor2::OnDiscoverVertex(&tygraAsString, vertexDepth)
                                            , StringVisitor2::OnExamineEdge   (&tygraAsString, vertexDepth)
                                            , StringVisitor2::OnFinishVertex  (&tygraAsString, vertexDepth)
                                            )
                      ))
    );

    return tygraAsString;
}
*/

