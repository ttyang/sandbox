/****************************************************************************
**
**
****************************************************************************/

#pragma once

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

    void add(const dag::db::ObjectType& aVertex)
    {

    }

    tString edgesToString()
    {
        using namespace boost;
        tString edgesRep = tString("+----- edges -----+\n");
        typedef boost::graph_traits<tGraph>::edge_iterator edge_iter;
        edge_iter edge_, edges_end;

        for(tie(edge_, edges_end)=edges(m_aGraph); edge_!=edges_end; ++edge_)
        {
            edgesRep += m_aEdgeDecoMap[*edge_].toString();
            edgesRep += "\n";
        }

        edgesRep += tString("+----- segde -----+\n");
        return edgesRep;
    }

    void resize(std::size_t edgeCount)
    {
        m_aGraph = tTypeGraph::type(edgeCount);
    }

    const tKey2Vertex& getKey2Vertex()const { return m_aKey2Vertex; }

private:
    //==========================================================================
    //= boost::graph
    tTypeGraph::type           m_aGraph;
    tTypeGraph::tVertexDecoMap m_aVertexDecoMap;
    tTypeGraph::tEdgeDecoMap   m_aEdgeDecoMap;

    tKey2Vertex                m_aKey2Vertex;
};

void getTypeGraph(TypeGraph& tygr, const QSqlQuery& query);


}} // namespace dag::db

