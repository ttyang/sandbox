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
makeTypeGraph(Accessor& accessor, dag::db::TypeGraph& typeGraph)
{
    typedef typename Accessor::const_iterator const_iterator;
    typename Accessor::size_type edgeCount
        = select(accessor, createQuery<Accessor,dag::db::EdgeType>());

    QString check;
    for(const_iterator it = begin(accessor); it != end(accessor); ++it)
    {
        dag::db::EdgeType aEdge = create<Accessor,dag::db::EdgeType>(it);
        //boost::add_edge(aEdge.sourceType(), aEdge.targetType(), typeGraph);
        typeGraph.addEdge(create<Accessor,dag::db::EdgeType>(it)); //Moveable!

        check += aEdge.toString();
        check += "\n";
    }

    QMessageBox msgBox;
    QString msg = "Edges:\n";
    msg += check;
    msg += "\n";
    msg += typeGraph.edgesToString();
    msg += "\n";

    msgBox.setText(msg);
    msgBox.exec();

    return true;
}

template<class Accessor>
typename boost::enable_if< IsQuerySelector<Accessor>, bool>::type
makeTypeGraph2(Accessor& accessor, dag::db::TypeGraph& typeGraph)
{
    typedef typename Accessor::const_iterator const_iterator;

    //add vertex properties.
    //boost::iterator_range<std::set<int>::iterator> dummyRange;
    typedef dag::db::TypeGraph::tKey2Vertex_iterator tIterator;
    typedef typename Accessor::tQuery tQuery;
    //KeyBinding_SqlQuery<tIterator>
    //    kbQuery = createQuery<Accessor,dag::db::ObjectType,tIterator>(typeGraph.keyVertexRange());

    typename Accessor::size_type vertexCount
            = select( accessor
                    , createQuery<Accessor,dag::db::ObjectType,tIterator>(typeGraph.keyVertexRange()));

    QString check;
    for(const_iterator it = begin(accessor); it != end(accessor); ++it)
    {
        dag::db::ObjectType aObj = create<Accessor,dag::db::ObjectType,tIterator>(it);

        check += aObj.toString();
        check += "\n";
    }

    QMessageBox msgBox;
    QString msg = "Objects:\n";
    msg += check;

    msgBox.setText(msg);
    msgBox.exec();

    return true;
}

} // namespace data
