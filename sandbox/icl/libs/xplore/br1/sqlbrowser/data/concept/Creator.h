/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>

#include "data/concept/QueryTraits.h"
#include "data/concept/IsQuerySelector.h"
#include "data/qsql/QSqlCreator.h"
#include "data/qsql/QSqlSelector.h"

namespace data
{

//==============================================================================
//= concept Creator
//==============================================================================
template<class Accessor, class DomainObject>
typename boost::enable_if< IsQuerySelector<Accessor>, DomainObject>::type
create(typename Accessor::const_iterator it)
{
    typedef typename GetCreator<DomainObject,Accessor>::type tCreator;
    return CreatorTraits<DomainObject,tCreator>::create(it);
}

template<class Accessor, class DomainObject>
typename boost::enable_if< IsQuerySelector<Accessor>, SqlQuery::tRepr>::type
createQuery()
{
    typedef typename GetCreator<DomainObject,Accessor>::type tCreator;
    return CreatorTraits<DomainObject,tCreator>::createQuery();
}


template<class Accessor, class DomainObject, class KeyIterator>
typename boost::enable_if< IsQuerySelector<Accessor>
                         , DomainObject>::type
create(typename Accessor::const_iterator it)
{
    //typedef typename Get_KeyBinding_Creator<DomainObject,Accessor>::type tCreator;
    typedef typename KeyBinding_QSqlCreator<DomainObject,        Accessor,KeyIterator>::type tCreator;
    return KeyBinding_CreatorTraits<DomainObject,tCreator,KeyIterator>::create(it);
}

template<class Accessor, class DomainObject, class KeyIterator>
typename boost::enable_if< IsQuerySelector<Accessor>
                         , KeyBinding_SqlQuery<KeyIterator> >::type
createQuery(const boost::iterator_range<KeyIterator>& keyRange)
{
    //typedef typename Get_KeyBinding_Creator<DomainObject,Accessor>::type tCreator;
    typedef typename KeyBinding_QSqlCreator<DomainObject,Accessor,KeyIterator>::type tCreator;
    return KeyBinding_CreatorTraits<DomainObject,tCreator,KeyIterator>::createQuery(keyRange);
}


} // namespace data
