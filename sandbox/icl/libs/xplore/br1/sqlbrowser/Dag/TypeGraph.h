/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include "Dag/DbBasedGraph.h"

class QSqlQuery;

namespace dag { namespace db
{

class TypeGraph : public DbBasedGraph<TypeGraph, db::ObjectType, db::EdgeType>
{
};

}} // namespace db dag

