/****************************************************************************
**
**
****************************************************************************/

#pragma once

//std
//boost
#include <boost/utility/enable_if.hpp>
//qt
//local
#include "Dag/TypeGraph.h"

#include "data/concept/IsQuerySelector.h"
//CL #include "data/qsql/QSqlSelector.h"

namespace data
{

// If it is an SqlAccessor, make the type-graph like so:
template<class Accessor>
typename boost::enable_if< isQuerySelector<Accessor>, void>::type
makeTypeGraph(Accessor& accessor, TypeGraph& typeGraph)
{
    typedef typename Accessor::iterator iterator;
    DataSelectorConcept<Accessor>::
        select(accessor, CreatorConcept<Object,Accessor>::createQuery());

    //JODO transform(accessor, typeGraph, CreatorConcept<TypeEdge,AccessorT>);
    //for(iterator it = accessor.begin(); it != accessor.end(); ++it)
}

} // namespace data
