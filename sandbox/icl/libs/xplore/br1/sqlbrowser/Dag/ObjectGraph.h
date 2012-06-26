/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include "Dag/DbBasedGraph.h"

class QSqlQuery;

namespace dag { namespace db
{

class ObjectGraph : public DbBasedGraph<TypeGraph, db::Object<ObjectType>, db::Edge >
{
};

}} // namespace db dag

