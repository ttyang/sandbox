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

#include "data/concept/Creator.h"
#include "data/concept/IsQuerySelector.h"
#include "data/qsql/QSqlCreator.h"

namespace data
{

//==============================================================================
//= concept Selector
//==============================================================================
template<class Accessor>
typename boost::enable_if< IsQuerySelector<Accessor>, typename Accessor::size_type>::type
select(Accessor& accessor, const typename Accessor::tQuery& query)
{
    return SelectorTraits<Accessor>::select(accessor, query);
}

template<class Accessor>
typename boost::enable_if< IsQuerySelector<Accessor>, typename Accessor::const_iterator>::type
begin(const Accessor& accessor)
{
    return SelectorTraits<Accessor>::begin(accessor);
}

template<class Accessor>
typename boost::enable_if< IsQuerySelector<Accessor>, typename Accessor::const_iterator>::type
end(const Accessor& accessor)
{
    return SelectorTraits<Accessor>::end(accessor);
}


} // namespace data
