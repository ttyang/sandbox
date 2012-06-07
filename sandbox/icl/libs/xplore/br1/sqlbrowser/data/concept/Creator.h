/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>

#include "data/concept/IsQuerySelector.h"

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
typename boost::enable_if< IsQuerySelector<Accessor>, tString>::type
createQuery()
{
    typedef typename GetCreator<DomainObject,Accessor>::type tCreator;
    return CreatorTraits<DomainObject,tCreator>::createQuery();
}


} // namespace data
