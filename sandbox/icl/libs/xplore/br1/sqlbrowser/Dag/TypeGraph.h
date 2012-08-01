/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include "Dag/DbType.h"
#include "Dag/DbBasedGraph.h"

class QSqlQuery;

namespace dag { namespace db
{

class TypeGraph : public dag::db::DbBasedGraph<TypeGraph, db::ObjectType, db::EdgeType>
{
};

}} // namespace db dag

