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
//! A creator creates (Domain)Objects for a Given Accessor
//! The Accessor encapsulates the Access to a file or data base.
template<class Object, class Accessor>
struct CreatorTraits
{
    typedef typename Accessor::const_iterator const_iterator;
    typedef typename Accessor::tQuery   tQuery;

    //! Creates a Query to access domain Objects
    static tString createQuery();

    //! Creates a domain Object from an Accessor's const_iterator
    static Object create(const_iterator);
};

} // namespace data
