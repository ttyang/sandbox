/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include "Dag/Decoration.h"
#include "Dag/DecoratedGraph.h"

#include "Dag/DbType.h"

class QSqlQuery;

namespace dag namespace db {
{


class TypeGraph
{
public:
    typedef boost::shared_ptr<db::ObjectType> tTypeVertexDeco;
    typedef boost::shared_ptr<db::EdgeType>   tTypeEdgeDeco;

    //! The TypeGraph is a DecoratedGraph
    typedef DecoratedGraph<tTypeVertexDeco, tTypeEdgeDeco> tTypeGraph;

private:
    //==========================================================================
    //= boost::graph
    tTypeGraph::type           m_aGraph;
    tTypeGraph::tVertexDecoMap m_aVertexDecoMap;
    tTypeGraph::tEdgeDecoMap   m_aEdgeDecoMap;

};

void getTypeGraph(TypeGraph& tygr, const QSqlQuery& query);

//! Data Access layer. May be sql, xml etc.
class TypeGraphSqlAccessor // implements DataAccessor
{
public:
    // The DataAccessor interface (generic)
    bool prepareGet();
    bool next();

    // Interface specific to TypeGraph
    EdgeType edge();

private:
    static tString s_aTypeEdgesQuery;
    static bool    m_bInitialized;

    int m_Edge_Key_Idx;
    int m_Object_Key_Idx;
};


}} // dag::db

