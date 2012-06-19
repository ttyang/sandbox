/****************************************************************************
**
**
****************************************************************************/

#pragma once

//std
//boost
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>
//qt
//local
#include "Dag/TypeGraph.h"

#include "data/concept/Selector.h"

namespace data
{

//! Given the Accessor is a QuerySelector, it allows to retirieve resultsets
//! from some Query objects, the function to make a typeGraph is generic for
//! all those Accessors
template<class Accessor>
typename boost::enable_if< IsQuerySelector<Accessor>, bool>::type
addEdgeData(Accessor& accessor, dag::db::TypeGraph& typeGraph)
{
    typedef typename Accessor::const_iterator const_iterator;
    typename Accessor::size_type edgeCount
        = select(accessor, createQuery<Accessor,dag::db::EdgeType>());

    for(const_iterator it = begin(accessor); it != end(accessor); ++it)
    {
        dag::db::EdgeType aEdge = create<Accessor,dag::db::EdgeType>(it);
        typeGraph.addEdge(create<Accessor,dag::db::EdgeType>(it)); //Moveable!
    }

    return true;
}

template<class Accessor>
typename boost::enable_if< IsQuerySelector<Accessor>, bool>::type
addVertexData(Accessor& accessor, dag::db::TypeGraph& typeGraph)
{
    typedef typename Accessor::const_iterator const_iterator;

    //add vertex properties.
    typedef dag::db::TypeGraph::tKey2Vertex_iterator tIterator;
    typedef typename Accessor::tQuery tQuery;

    typename Accessor::size_type vertexCount
            = select( accessor
                    , createQuery<Accessor,dag::db::ObjectType,tIterator>(typeGraph.keyVertexRange()));

    for(const_iterator it = begin(accessor); it != end(accessor); ++it)
    {
        dag::db::ObjectType objType = create<Accessor,dag::db::ObjectType,tIterator>(it);
        typeGraph.addVertexObject(objType);
    }

    return true;
}


bool makeTypeGraph(dag::db::TypeGraph& typeGraph, const QSqlDatabase& db);

} // namespace data
