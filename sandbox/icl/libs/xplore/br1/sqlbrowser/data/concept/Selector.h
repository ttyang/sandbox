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
    typedef QSqlCreator<dag::db::EdgeType,Accessor> tCreator;
    typedef typename Accessor::const_iterator const_iterator;
    //DataSelectorConcept<Accessor>::
    //    select(accessor, CreatorConcept<Object,Accessor>::createQuery());

    //JODO transform(accessor, typeGraph, CreatorConcept<TypeEdge,AccessorT>);
    //for(iterator it = accessor.begin(); it != accessor.end(); ++it)

    QString ObjSql = CreatorTraits<dag::db::EdgeType,tCreator>::createQuery();

    QMessageBox msgBox;
    QString msg = "Insertion. ";
    msg += ObjSql;
    msgBox.setText(msg);
    msgBox.exec();


    return true;
}

} // namespace data
