#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graph_utility.hpp>

#include "StringVisitor2.h"

#include "Dag/TypeGraph.h"

//using namespace dag::db;

dag::db::tString dag::db::TypeGraph::depthFirstString()
{
    QString tygraAsString;

    boost::depth_first_search(
        m_aGraph
      , boost::visitor(make_dfs_visitor(boost::make_list(
                                              StringVisitor2::OnDiscoverVertex(&tygraAsString, m_aVertexDecoMap)
                                            , StringVisitor2::OnExamineEdge   (&tygraAsString, m_aVertexDecoMap)
                                            , StringVisitor2::OnFinishVertex  (&tygraAsString, m_aVertexDecoMap)
                                            )
                      ))
    );

    return tygraAsString;

}
