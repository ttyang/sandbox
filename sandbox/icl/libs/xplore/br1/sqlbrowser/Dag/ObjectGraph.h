/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include <boost/range.hpp>

#include "Dag/Decoration.h"
#include "Dag/DecoratedGraph.h"

#include "Dag/DbType.h"

class QSqlQuery;

namespace dag { namespace db
{


class ObjectGraph
{
public:
    typedef db::Object tTypeVertexDeco;
    typedef db::Edge   tTypeEdgeDeco;

    //! The ObjectGraph is a DecoratedGraph
    typedef DecoratedGraph<tTypeVertexDeco, tTypeEdgeDeco> tObjectGraph;
    typedef DecoratedGraph<tTypeVertexDeco, tTypeEdgeDeco>::type tGraph;
    typedef tObjectGraph::vertex_descriptor vertex_descriptor;
    typedef tObjectGraph::edge_descriptor   edge_descriptor;
    typedef tObjectGraph::tVertex2Depth     tVertex2Depth;

    typedef std::map<tKey, vertex_descriptor> tKey2Vertex;
    typedef tKey2Vertex::iterator tKey2Vertex_iterator;
    typedef boost::iterator_range<tKey2Vertex_iterator> tKeyVertexRange;

    vertex_descriptor add_vertex(tKey key)
    {
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

    void addEdge(const dag::db::Edge& aEdge)
    {
        tKey srcVertexKey = aEdge.sourceObject();
        tKey trgVertexKey = aEdge.targetObject();

        vertex_descriptor srcVertex = add_vertex(srcVertexKey);
        vertex_descriptor trgVertex = add_vertex(trgVertexKey);

        bool edge_added;
        edge_descriptor edge;
        boost::tie(edge, edge_added) = boost::add_edge(srcVertex, trgVertex, m_aGraph);

        if(edge_added)
            m_aGraph[edge] = aEdge;

    }

    /*
    void addVertexObject(const dag::db::ObjectType& objType)
    {
        Q_ASSERT( m_aKey2Vertex.find(objType.key()) != m_aKey2Vertex.end() );
        m_aGraph[m_aKey2Vertex[objType.key()]] = objType;
    }

    const tKey2Vertex& getKey2Vertex()const { return m_aKey2Vertex; }

    tKeyVertexRange keyVertexRange(){ return tKeyVertexRange(m_aKey2Vertex.begin(), m_aKey2Vertex.end()); }

    tString toString()const
    {
        using namespace boost;
        tString edgesRep = tString("+----- ObjectGraph -----+\n");
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

    tString depthFirstString();

private:
    //==========================================================================
    //= boost::graph
    tObjectGraph::type m_aGraph;

    tKey2Vertex      m_aKey2Vertex;
    */
};

void getObjectGraph(ObjectGraph& ogra, const QSqlQuery& query);


}} // namespace dag::db

