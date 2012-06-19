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


class TypeGraph
{
public:
    typedef db::ObjectType tTypeVertexDeco;
    typedef db::EdgeType   tTypeEdgeDeco;

    //! The TypeGraph is a DecoratedGraph
    typedef DecoratedGraph<tTypeVertexDeco, tTypeEdgeDeco> tTypeGraph;
    typedef DecoratedGraph<tTypeVertexDeco, tTypeEdgeDeco>::type tGraph;
    typedef tTypeGraph::vertex_descriptor vertex_descriptor;
    typedef tTypeGraph::edge_descriptor   edge_descriptor;

    typedef std::map<tKey, vertex_descriptor> tKey2Vertex;
    typedef tKey2Vertex::iterator tKey2Vertex_iterator;
    typedef boost::iterator_range<tKey2Vertex_iterator> tKeyVertexRange;

    typedef tTypeGraph::tVertexDecoMap tVertexDecoMap;
    typedef tTypeGraph::tEdgeDecoMap   tEdgeDecoMap;

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

    void addEdge(const dag::db::EdgeType& aEdge)
    {
        tKey srcVertexKey = aEdge.sourceType();
        tKey trgVertexKey = aEdge.targetType();

        vertex_descriptor srcVertex = add_vertex(srcVertexKey);
        vertex_descriptor trgVertex = add_vertex(trgVertexKey);

        bool edge_added;
        edge_descriptor edge;
        boost::tie(edge, edge_added) = boost::add_edge(srcVertex, trgVertex, m_aGraph);

        if(edge_added)
            m_aEdgeDecoMap[edge] = aEdge;

        //CL m_aVertexDecoMap[srcVertex] = tTypeVertexDeco(srcVertexKey, tString("JODO srcT name"));
        //CL m_aVertexDecoMap[trgVertex] = tTypeVertexDeco(trgVertexKey, tString("JODO trgT name"));

    }

    void addVertexObject(const dag::db::ObjectType& objType)
    {
        Q_ASSERT( m_aKey2Vertex.find(objType.key()) != m_aKey2Vertex.end() );
        m_aVertexDecoMap[m_aKey2Vertex[objType.key()]] = objType;
    }


    void resize(std::size_t edgeCount)
    {
        m_aGraph = tTypeGraph::type(edgeCount);
    }

    const tKey2Vertex& getKey2Vertex()const { return m_aKey2Vertex; }

    tKeyVertexRange keyVertexRange(){ return tKeyVertexRange(m_aKey2Vertex.begin(), m_aKey2Vertex.end()); }

    tString toString()const
    {
        using namespace boost;
        tString edgesRep = tString("+----- TypeGraph -----+\n");
        typedef boost::graph_traits<tGraph>::edge_iterator edge_iter;
        edge_iter edge_, edges_end;

        for(tie(edge_, edges_end)=edges(m_aGraph); edge_!=edges_end; ++edge_)
        {
            edge_descriptor   edge         = *edge_;
            vertex_descriptor sourceVertex = source(edge, m_aGraph);
            vertex_descriptor targetVertex = target(edge, m_aGraph);

            edgesRep += (m_aEdgeDecoMap[*edge_].toString() + " "   );
            edgesRep += (m_aVertexDecoMap[sourceVertex].toString()+ " ");
            edgesRep += (m_aVertexDecoMap[targetVertex].toString());
            edgesRep += "\n";
        }

        return edgesRep;
    }

    tString depthFirstString();

private:
    //==========================================================================
    //= boost::graph
    tTypeGraph::type m_aGraph;
    tVertexDecoMap   m_aVertexDecoMap;
    tEdgeDecoMap     m_aEdgeDecoMap;

    tKey2Vertex      m_aKey2Vertex;
};

void getTypeGraph(TypeGraph& tygr, const QSqlQuery& query);


}} // namespace dag::db

