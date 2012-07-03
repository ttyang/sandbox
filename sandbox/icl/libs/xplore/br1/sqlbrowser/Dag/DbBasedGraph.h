/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include <boost/range.hpp>

#include "Dag/Decoration.h"
#include "Dag/DecoratedGraph.h"

#include "Dag/DbType.h"
#include "StringVisitor2.h"

class QSqlQuery;

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
    typedef typename tDbBasedGraph::vertex_descriptor vertex_descriptor;
    typedef typename tDbBasedGraph::edge_descriptor   edge_descriptor;
    typedef typename tDbBasedGraph::tVertex2Depth     tVertex2Depth;

    typedef std::map<tKey, vertex_descriptor> tKey2Vertex;
    typedef typename tKey2Vertex::iterator tKey2Vertex_iterator;
    typedef boost::iterator_range<tKey2Vertex_iterator> tKeyVertexRange;

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
        tVertex2Depth vertexDepth;
        QString tygraAsString;

        boost::depth_first_search(
            m_aGraph
          , boost::visitor(make_dfs_visitor(boost::make_list(
                                                  StringVisitor2<DbBasedGraph>::OnDiscoverVertex(&tygraAsString, vertexDepth)
                                                , StringVisitor2<DbBasedGraph>::OnExamineEdge   (&tygraAsString, vertexDepth)
                                                , StringVisitor2<DbBasedGraph>::OnFinishVertex  (&tygraAsString, vertexDepth)
                                                )
                          ))
        );

        return tygraAsString;
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

