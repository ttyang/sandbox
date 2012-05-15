/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include "Dag/DbType.h"

namespace data
{

typedef dag::db::tString tString;

//==============================================================================
//= Concept: data::Creator Traits
//==============================================================================
template<class Object, class Accessor>
struct CreatorTraits
{
    typedef typename Accessor::const_iterator const_iterator;
    typedef typename Accessor::tQuery   tQuery;

    static tString createQuery();
    static Object create(const_iterator);
};

} // namespace data
