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
    typedef tTypeGraph::vertex_descriptor vertex_descriptor;
    typedef tTypeGraph::edge_descriptor   edge_descriptor;

    void add(const dag::db::EdgeType& aEdge)
    {
        tKey srcVertexKey = aEdge.sourceType();
        tKey trgVertexKey = aEdge.targetType();

        vertex_descriptor srcVertex = boost::add_vertex(m_aGraph);
        vertex_descriptor trgVertex = boost::add_vertex(m_aGraph);

        bool added;
        edge_descriptor edge;
        boost::tie(edge, added) = boost::add_edge(srcVertex, trgVertex, m_aGraph);

        m_aVertexDecoMap[srcVertex] = tTypeVertexDeco(srcVertexKey, tString("JODO srcT name"));
        m_aVertexDecoMap[trgVertex] = tTypeVertexDeco(trgVertexKey, tString("JODO trgT name"));
    }

private:
    //==========================================================================
    //= boost::graph
    tTypeGraph::type           m_aGraph;
    tTypeGraph::tVertexDecoMap m_aVertexDecoMap;
    tTypeGraph::tEdgeDecoMap   m_aEdgeDecoMap;

};

void getTypeGraph(TypeGraph& tygr, const QSqlQuery& query);


}} // namespace dag::db

