/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include "Dag/DbBasedGraph.h"

class QSqlQuery;

namespace dag { namespace db
{

class ObjectGraph : public DbBasedGraph<TypeGraph, db::Object, db::Edge>
{
};

}} // namespace db dag

