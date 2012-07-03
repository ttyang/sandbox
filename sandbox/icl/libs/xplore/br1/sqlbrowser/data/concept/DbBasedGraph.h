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
template<class Accessor, class DbGraph>
typename boost::enable_if< IsQuerySelector<Accessor>, bool>::type
addEdgeData(Accessor& accessor, DbGraph& aGraph)
{
    typedef typename Accessor::const_iterator const_iterator;
    typedef typename DbGraph::tEdgeDeco tEdgeDeco;
    typename Accessor::size_type edgeCount
        = select(accessor, createQuery<Accessor,tEdgeDeco>());

    for(const_iterator it = begin(accessor); it != end(accessor); ++it)
    {
        tEdgeDeco aEdge = create<Accessor,tEdgeDeco>(it);
        aGraph.addEdge(create<Accessor,tEdgeDeco>(it)); //JODO Moveable!
    }
    return true;
}

template<class Accessor, class DbGraph>
typename boost::enable_if< IsQuerySelector<Accessor>, bool>::type
addVertexData(Accessor& accessor, DbGraph& aGraph)
{
    typedef typename Accessor::const_iterator const_iterator;
    typedef typename DbGraph::tVertexDeco tVertexDeco;

    //add vertex properties.
    typedef typename DbGraph::tKey2Vertex_iterator tIterator;
    typedef typename Accessor::tQuery tQuery;

    typename Accessor::size_type vertexCount
            = select( accessor
                    , createQuery<Accessor,tVertexDeco,tIterator>(aGraph.keyVertexRange()));

    for(const_iterator it = begin(accessor); it != end(accessor); ++it)
    {
        tVertexDeco dbg_CL_deco = create<Accessor,tVertexDeco,tIterator>(it);
        aGraph.addVertexObject(create<Accessor,tVertexDeco,tIterator>(it));
    }

    return true;
}


template<class DbGraph>
bool makeDbGraph(DbGraph& aGraph, const QSqlDatabase& db)
{
    typedef typename DbGraph::tKey2Vertex_iterator tKey2Vertex_iterator;
    data::QSqlSelector selector;
    selector.setDatabase(db);

    if(!addEdgeData(selector, aGraph))
        return false;

    data::KeyBinding_QSqlSelector<tKey2Vertex_iterator> keyBindingSelector;
    keyBindingSelector.setDatabase(db);

    if(!addVertexData(keyBindingSelector, aGraph))
        return false;

    return true;
}


} // namespace data
