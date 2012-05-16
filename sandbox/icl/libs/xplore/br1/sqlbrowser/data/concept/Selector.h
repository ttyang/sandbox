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

#include "data/concept/IsQuerySelector.h"
#include "data/qsql/QSqlCreator.h"

namespace data
{
// If it is an SqlAccessor, make the type-graph like so:
template<class Accessor>
typename boost::enable_if< IsQuerySelector<Accessor>, bool>::type
makeTypeGraph(Accessor& accessor, dag::db::TypeGraph& typeGraph)
{
    typedef typename GetCreator<dag::db::EdgeType,Accessor>::type tCreator;
    typedef typename Accessor::const_iterator const_iterator;
    typedef typename CreatorTraits<dag::db::EdgeType,tCreator> tCreatorInstance;

    SelectorTraits<Accessor>::
        select(accessor,
               CreatorTraits<dag::db::EdgeType,tCreator>::createQuery());

    QString check;
    for(const_iterator it = accessor.begin(); it != accessor.end(); ++it)
    {
        //check += it->field(4).value().toString();
        dag::db::EdgeType aEdge
                = CreatorTraits<dag::db::EdgeType,tCreator>::create(it);
        check += aEdge.toString();
        check += "\n";
    }


    QMessageBox msgBox;
    QString msg = "Edges:\n";
    msg += check;
    msgBox.setText(msg);
    msgBox.exec();


    return true;
}

} // namespace data
