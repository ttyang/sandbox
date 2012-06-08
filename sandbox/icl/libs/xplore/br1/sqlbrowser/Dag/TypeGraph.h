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
    typedef boost::shared_ptr<db::ObjectType> tTypeVertexDeco;
    typedef boost::shared_ptr<db::EdgeType>   tTypeEdgeDeco;

    //! The TypeGraph is a DecoratedGraph
    typedef DecoratedGraph<tTypeVertexDeco, tTypeEdgeDeco> tTypeGraph;

    void add(const dag::db::EdgeType& aEdge)
    {
        tKey srcT = aEdge.sourceType(),
             trgT = aEdge.targetType();
        boost::add_edge(srcT, trgT, m_aGraph);
        //m_aVertexDecoMap[srcT] = "JODO srcT name";
        //m_aVertexDecoMap[trgT] = "JODO trgT name";
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

