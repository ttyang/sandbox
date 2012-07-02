/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include "Dag/DbBasedGraph.h"

class QSqlQuery;

namespace dag { namespace db
{

template<class ObjectType, class EdgeType>
class ObjectGraph : public DbBasedGraph<TypeGraph, db::Object<ObjectType>, db::Edge<EdgeType> >
{
};

}} // namespace db dag

