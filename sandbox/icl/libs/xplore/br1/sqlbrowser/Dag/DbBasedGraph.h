/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graph_utility.hpp>

#include <boost/range.hpp>

#include "Dag/Decoration.h"
#include "Dag/DecoratedGraph.h"

#include "Dag/DbType.h"
#include "StringVisitor2.h"
#include "CreatorVisitor2.h"

class QSqlQuery;
class DagModel2;

namespace dag { namespace db
{

template<class Derived, class VertexDeco, class EdgeDeco>
class DbBasedGraph
{
public:
    typedef Derived    tDerived;
    typedef VertexDeco tVertexDeco;
    typedef EdgeDeco   tEdgeDeco;
    typedef DbBasedGraph<tDerived, tVertexDeco, tEdgeDeco> type;

    //! The DbBasedGraph is a DecoratedGraph
    typedef DecoratedGraph<tVertexDeco, tEdgeDeco> tDbBasedGraph;
    typedef typename DecoratedGraph<tVertexDeco, tEdgeDeco>::type tGraph;
    typedef typename tDbBasedGraph::vertex_descriptor   vertex_descriptor;
    typedef typename tDbBasedGraph::edge_descriptor     edge_descriptor;
    typedef typename tDbBasedGraph::adjacency_iterator  adjacency_iterator;
    typedef typename tDbBasedGraph::out_edge_iterator   out_edge_iterator;
    typedef typename tDbBasedGraph::in_edge_iterator    in_edge_iterator;
    typedef typename tDbBasedGraph::vertex_iterator     vertex_iterator;
    typedef typename tDbBasedGraph::edge_iterator       edge_iterator;

    typedef typename tDbBasedGraph::directed_category      directed_category;
    typedef typename tDbBasedGraph::edge_parallel_category edge_parallel_category;
    typedef typename tDbBasedGraph::traversal_category     traversal_category;

    typedef typename tDbBasedGraph::vertices_size_type     vertices_size_type;
    typedef typename tDbBasedGraph::edges_size_type        edges_size_type;
    typedef typename tDbBasedGraph::degree_size_type       degree_size_type;

    typedef typename tDbBasedGraph::tVertex2Depth       tVertex2Depth;

    typedef std::map<tKey, vertex_descriptor> tKey2Vertex;
    typedef typename tKey2Vertex::iterator tKey2Vertex_iterator;
    typedef boost::iterator_range<tKey2Vertex_iterator> tKeyVertexRange;

    //--------------------------------------------------------------------------
    typedef std::map<vertex_descriptor, VertexAttributes> Vertex2AttributesMap;

    //--------------------------------------------------------------------------
    // Functions progagated from DbBasedGraph.
    edges_size_type num_edges()const { return boost::num_edges(m_aGraph); }

    std::pair<edge_descriptor, bool> add_edge(vertex_descriptor source, vertex_descriptor target)
    { return boost::add_edge(source, target, m_aGraph); }

    void clear() { m_aGraph.clear(); }
    //--------------------------------------------------------------------------

    vertex_descriptor addVertex(tKey key)
    {
        Q_ASSERT(key > 0);
        tKey2Vertex::iterator vertex_ = m_aKey2Vertex.find(key);
        if(vertex_ != m_aKey2Vertex.end())
            return (*vertex_).second;
        else
        {
            vertex_descriptor newVertex = boost::add_vertex(m_aGraph);
            m_aKey2Vertex.insert(std::make_pair(key, newVertex));
            return newVertex;
        }
    }

    void addEdge(const tEdgeDeco& aEdge)
    {
        tKey srcVertexKey = aEdge.sourceKey();
        tKey trgVertexKey = aEdge.targetKey();

        vertex_descriptor srcVertex = addVertex(srcVertexKey);
        vertex_descriptor trgVertex = addVertex(trgVertexKey);

        bool edge_added;
        edge_descriptor edge;
        boost::tie(edge, edge_added) = boost::add_edge(srcVertex, trgVertex, m_aGraph);

        if(edge_added)
            m_aGraph[edge] = aEdge;
    }

    void addVertexObject(const tVertexDeco& objType)
    {
        Q_ASSERT( m_aKey2Vertex.find(objType.key()) != m_aKey2Vertex.end() );
        m_aGraph[m_aKey2Vertex[objType.key()]] = objType;
    }

    const tKey2Vertex& getKey2Vertex()const { return m_aKey2Vertex; }

    tKeyVertexRange keyVertexRange(){ return tKeyVertexRange(m_aKey2Vertex.begin(), m_aKey2Vertex.end()); }

    tString toString()const
    {
        using namespace boost;
        tString edgesRep = tString("+----- DbBasedGraph -----+\n");
        typedef boost::graph_traits<tGraph>::edge_iterator edge_iter;
        edge_iter edge_, edges_end;

        for(tie(edge_, edges_end)=edges(m_aGraph); edge_!=edges_end; ++edge_)
        {
            edge_descriptor   edge         = *edge_;
            vertex_descriptor sourceVertex = source(edge, m_aGraph);
            vertex_descriptor targetVertex = target(edge, m_aGraph);

            edgesRep += (m_aGraph[*edge_].toString() + " "   );
            edgesRep += (m_aGraph[sourceVertex].toString()+ " ");
            edgesRep += (m_aGraph[targetVertex].toString());
            edgesRep += "\n";
        }

        return edgesRep;
    }

    tString depthFirstString()
    {
        typedef DbBasedGraph::vertex_descriptor vertex_descriptor;
        //Add an associative color map type.
        typedef std::map<vertex_descriptor, boost::default_color_type> color_map_t;
        color_map_t color_map; //Declare a container

        tVertex2Depth vertexDepth;
        QString tygraAsString;
        vertex_descriptor start_vertex;

        BGL_FORALL_VERTICES(vtx, m_aGraph, DbBasedGraph) {
          color_map[vtx] = boost::white_color;
          if(m_aGraph[vtx].key() == 32)
              start_vertex = vtx;
        }

        //Generate an assoc property map
        boost::associative_property_map<color_map_t> pm_color(color_map);

        boost::depth_first_search(
            m_aGraph
          , make_dfs_visitor(boost::make_list(
                                                  StringVisitor2<DbBasedGraph>::OnDiscoverVertex    (&tygraAsString, vertexDepth)
                                                , StringVisitor2<DbBasedGraph>::OnExamineEdge       (&tygraAsString, vertexDepth)
                                                , StringVisitor2<DbBasedGraph>::OnForwardOrCrossEdge(&tygraAsString, vertexDepth)
                                                , StringVisitor2<DbBasedGraph>::OnFinishVertex      (&tygraAsString, vertexDepth)
                                                )
                          )
          , pm_color
          , start_vertex

        );

        return tygraAsString;
    }

    tString makeDagModel(DagModel2* dagmo)
    {
        typedef DbBasedGraph::vertex_descriptor vertex_descriptor;
        //Add an associative color map type.
        typedef std::map<vertex_descriptor, boost::default_color_type> color_map_t;
        color_map_t color_map; //Declare a container

        CreatorVisitor2<DbBasedGraph>::Vertex2AttributesMap vertex2AttrMap;
        QString graphAsString;
        DagItem* modelRoot = dagmo->rootItem();

        vertex_descriptor start_vertex;

        BGL_FORALL_VERTICES(vtx, m_aGraph, DbBasedGraph) {
          color_map[vtx] = boost::white_color;
          if(m_aGraph[vtx].key() == 32)
              start_vertex = vtx;
        }


        modelRoot->setData(dag::node::posId,   QVariant(m_aGraph[start_vertex].key()));
        modelRoot->setData(dag::node::posName, QVariant(m_aGraph[start_vertex].name()));

        vertex2AttrMap[start_vertex].setDagItem(modelRoot);
        vertex2AttrMap[start_vertex].setParentItem(0); //Root has no parent.

        //Generate an assoc property map
        boost::associative_property_map<color_map_t> pm_color(color_map);

        boost::depth_first_search(
            m_aGraph
          , make_dfs_visitor(boost::make_list(
                                                  CreatorVisitor2<DbBasedGraph>::OnDiscoverVertex    (modelRoot, &graphAsString, vertex2AttrMap)
                                                , CreatorVisitor2<DbBasedGraph>::OnExamineEdge       (modelRoot, &graphAsString, vertex2AttrMap)
                                           //   , CreatorVisitor2<DbBasedGraph>::OnForwardOrCrossEdge(modelRoot, &graphAsString, vertex2AttrMap)
                                                , CreatorVisitor2<DbBasedGraph>::OnFinishVertex      (modelRoot, &graphAsString, vertex2AttrMap)
                                                )
                          )
          , pm_color
          , start_vertex
        );

        return graphAsString;
    }

protected:
          tDerived* derived()      { return static_cast<tDerived*>(this); }
    const tDerived* derived()const { return static_cast<const tDerived*>(this); }

protected:
    //==========================================================================
    //= boost::graph
    tGraph      m_aGraph;
    tKey2Vertex m_aKey2Vertex;
};


}} // namespace dag::db

